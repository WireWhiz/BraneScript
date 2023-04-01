//
// Created by wirewhiz on 15/10/22.
//

#include "scriptRuntime.h"
#include "asmjit/core/globals.h"
#include "irScript.h"
#include "linker.h"
#include "script.h"
#include "structDefinition.h"
#include "valueIndex.h"

#include <cassert>
#include <cstdio>
#include <stdexcept>
#include "asmjit/asmjit.h"

namespace BraneScript
{
    using namespace asmjit::x86;

    class JitErrorHandler : public asmjit::ErrorHandler
    {
      public:
        void handleError(asmjit::Error err, const char* message, asmjit::BaseEmitter* origin) override
        {
            printf("AsmJit error: %s\n", message);
            fflush(stdout);
            throw std::runtime_error("JIT error assembling script: " + std::string(message));
        }
    };

    asmjit::TypeId valueToASMType(const Value& value)
    {
        switch(value.valueType)
        {
            case ValueType::Bool:
                return asmjit::TypeId::kUInt8;
            case ValueType::Int32:
                return asmjit::TypeId::kInt32;
            case ValueType::Float32:
                return asmjit::TypeId::kFloat32;
            case ValueType::Struct:
                return asmjit::TypeId::kIntPtr;
            default:
                throw std::runtime_error("Unimplemented type");
        }
    }

    asmjit::TypeId strToASMType(std::string_view str)
    {
        if(str == "void")
            return asmjit::TypeId::kVoid;
        if(str == "char")
            return asmjit::TypeId::kUInt8;
        if(str == "bool")
            return asmjit::TypeId::kUInt8;
        if(str == "uint")
            return asmjit::TypeId::kUInt32;
        if(str == "uint64")
            return asmjit::TypeId::kUInt64;
        if(str == "int")
            return asmjit::TypeId::kInt32;
        if(str == "int64")
            return asmjit::TypeId::kInt64;
        if(str == "float")
            return asmjit::TypeId::kFloat32;
        if(str == "double")
            return asmjit::TypeId::kFloat64;
        return asmjit::TypeId::kIntPtr;
    }

    enum class ValueRegType : uint8_t
    {
        gp = 0,
        xmm = 1,
        mem = 2
    };

    enum OperationType
    {
        gp_gp,
        gp_xmm,
        gp_mem,
        xmm_xmm,
        xmm_gp,
        xmm_mem,
        mem_gp,
        mem_xmm,
        mem_mem
    };

    ValueRegType getValueRegType(const Value& value)
    {
        switch(value.storageType)
        {
            case ValueStorageType_Reg:
                break; // goto next switch statement
            case ValueStorageType_Ptr:
            case ValueStorageType_GlobalPtr:
            case ValueStorageType_Global:
                return ValueRegType::gp;
            case ValueStorageType_DerefPtr:
            case ValueStorageType_Const:
                return ValueRegType::mem;
            default:
                assert(false);
        }
        switch(value.valueType)
        {
            case ValueType::Bool:
            case ValueType::Char:
            case ValueType::UInt32:
            case ValueType::UInt64:
            case ValueType::Int32:
            case ValueType::Int64:
                return ValueRegType::gp;
            case ValueType::Float32:
            case ValueType::Float64:
                return ValueRegType::xmm;
            case ValueType::Struct:
                return ValueRegType::mem;
        }
        assert(false);
    }

    OperationType getOperationType(const Value& a, const Value& b)
    {
        const OperationType gpMap[] = {gp_gp, gp_xmm, gp_mem};
        const OperationType xmmMap[] = {xmm_gp, xmm_xmm, xmm_mem};
        const OperationType memMap[] = {mem_gp, mem_xmm, mem_mem};
        const OperationType* typeMap;
        switch(getValueRegType(a))
        {
            case ValueRegType::gp:
                typeMap = gpMap;
                break;
            case ValueRegType::xmm:
                typeMap = xmmMap;
                break;
            case ValueRegType::mem:
                typeMap = memMap;
                break;
        }
        assert(typeMap);

        return typeMap[(uint8_t)getValueRegType(b)];
    }

    struct AssemblyCtx
    {
        size_t iptr = 0;

        IRFunction* currentFunction = nullptr;
        IRScript* currentScript = nullptr;

        asmjit::x86::Gp globalsPtr;
        std::vector<asmjit::x86::Reg> registers;
        std::vector<asmjit::x86::Mem> constants;
        std::vector<asmjit::Label> labels;

        size_t stackSize = 0;

        template<typename T>
        T readCode()
        {
            return currentFunction->readCode<T>(iptr);
        }

        bool endOfCode() const { return iptr >= currentFunction->code.size(); }

        template<class RT>
        RT getReg(Value value)
        {
            if constexpr(std::is_same<RT, Mem>())
            {
                if(value.storageType == ValueStorageType_Const)
                {
                    assert(value.index < constants.size());
                    return constants[value.index];
                }
                // If this isn't a constant, it's safe to assume that it's a dereferenced pointer
                assert(value.storageType == ValueStorageType_DerefPtr);
                assert(value.index < registers.size());
                assert(registers[value.index].isGp());
                return asmjit::x86::ptr(registers[value.index].as<Gp>(), value.offset);
            }
            else
            {

                assert(value.index < registers.size());
                if constexpr(std::is_same<RT, Gp>())
                {
                    if(value.storageType == ValueStorageType_Global)
                        return globalsPtr;
                    assert(registers[value.index].isGp());
                }
                if constexpr(std::is_same<RT, Xmm>())
                    assert(registers[value.index].isXmm());
                return registers[value.index].as<RT>();
            }
        }

        asmjit::Label getLabel(uint32_t index, Compiler& cc)
        {
            while(index >= labels.size())
                labels.push_back(cc.newLabel());
            return labels[index];
        }
    };

#ifndef NDEBUG
    int scriptMallocDiff = 0;
#endif

    void* scriptAlloc(uint16_t size)
    {
#ifndef NDEBUG
        scriptMallocDiff++;
#endif
        return ::operator new(size);
    }

    void scriptDealoc(void* data)
    {
#ifndef NDEBUG
        scriptMallocDiff--;
#endif
        ::operator delete(data);
    }

    Script* ScriptRuntime::assembleScript(IRScript* irScript)
    {
        assert(irScript);
        auto script = std::make_unique<Script>();

        // Generate local struct typedefs
        std::vector<std::unique_ptr<StructDef>> localStructs;
        for(auto& s : irScript->localStructs)
        {
            assert(_linker);
            auto def = std::make_unique<StructDef>(s.name);
            for(auto& m : s.members)
            {
                auto type = _linker->getType(m.type);
                if(!type)
                {
                    for(auto& ls : localStructs)
                    {
                        if(ls->name() == m.type)
                        {
                            type = ls.get();
                            break;
                        }
                    }
                }
                assert(type);
                def->addMemberVar(m.type, type, m.offset);
            }
            localStructs.push_back(std::move(def));
        }

        // Link external struct typedefs
        std::vector<const StructDef*> linkedStructs;
        for(auto& s : irScript->linkedStructs)
        {
            assert(_linker);
            auto def = dynamic_cast<const StructDef*>(_linker->getType(s));
            assert(def);
            linkedStructs.push_back(def);
        }

        // Find linked functions
        std::vector<const FunctionData*> linkedFunctions;
        for(auto& func : irScript->linkedFunctions)
        {
            assert(_linker);
            auto funcData = _linker->getFunction(func);
            if(!funcData)
                throw std::runtime_error("Could not resolve linked function: " + func);
            linkedFunctions.push_back(funcData);
        }

        // Allocate memory for globals
        if(irScript->globalVarAllocSize > 0)
            script->globalVars.resize(irScript->globalVarAllocSize);

        JitErrorHandler errorHandler;
        for(auto& func : irScript->localFunctions)
        {
            if(script->functionNames.contains(func.sig))
                throw std::runtime_error("Attempted to load function with signature that is already in use");

            AssemblyCtx ctx;
            asmjit::CodeHolder ch;
            ctx.currentFunction = &func;
            ctx.currentScript = irScript;

            ch.init(_runtime.environment());
            ch.setErrorHandler(&errorHandler);
            Compiler cc(&ch);
            cc.addDiagnosticOptions(asmjit::DiagnosticOptions::kValidateAssembler |
                                    asmjit::DiagnosticOptions::kRADebugAll);
            cc.addEncodingOptions(asmjit::EncodingOptions::kOptimizedAlign);

            printf("Assembling function: %s\n", ctx.currentFunction->sig.c_str());

            ctx.registers.resize(func.maxRegs);
            ctx.constants.resize(func.maxMemLocations);

            asmjit::FuncSignatureBuilder sigBuilder;
            std::vector<asmjit::TypeId> argTypes;
            sigBuilder.setCallConvId(asmjit::CallConvId::kCDecl);
            for(auto& arg : func.arguments)
            {
                asmjit::TypeId type;
                if(!arg.isRef)
                    type = strToASMType(arg.type);
                else
                    type = asmjit::TypeId::kIntPtr;
                sigBuilder.addArg(type);
                argTypes.push_back(type);
            }
            auto retType = strToASMType(func.returnType.type);
            sigBuilder.setRet(retType);
            auto* f = cc.addFunc(sigBuilder);

            auto globalsPtr = script->globalVars.data();
            auto globalsMem = cc.newConst(asmjit::ConstPoolScope::kGlobal, &globalsPtr, sizeof(globalsPtr));
            ctx.globalsPtr = cc.newIntPtr();
            cc.mov(ctx.globalsPtr, globalsMem);

            for(size_t i = 0; i < func.arguments.size(); ++i)
            {
                switch(argTypes[i])
                {
                    case asmjit::TypeId::kUInt8:
                        ctx.registers[i] = cc.newGpb();
                        break;
                    case asmjit::TypeId::kUInt32:
                        ctx.registers[i] = cc.newUInt32();
                        break;
                    case asmjit::TypeId::kUInt64:
                        ctx.registers[i] = cc.newUInt64();
                        break;
                    case asmjit::TypeId::kInt32:
                        ctx.registers[i] = cc.newInt32();
                        break;
                    case asmjit::TypeId::kInt64:
                        ctx.registers[i] = cc.newInt64();
                        break;
                    case asmjit::TypeId::kFloat32:
                        ctx.registers[i] = cc.newXmmSs();
                        break;
                    case asmjit::TypeId::kFloat64:
                        ctx.registers[i] = cc.newXmmSd();
                        break;
                    case asmjit::TypeId::kIntPtr:
                        ctx.registers[i] = cc.newIntPtr();
                        break;
                    default:
                        assert(false);
                }
                f->setArg(i, ctx.registers[i]);
            }

            auto& code = func.code;

            while(!ctx.endOfCode())
            {
                auto op = ctx.readCode<Operand>();
                switch(op)
                {
                    case RET:
                        printf("RET\n");
                        if(func.returnType.type != "void")
                            throw std::runtime_error("cannot return nothing from non-void functions");
                        cc.ret();
                        break;
                    case RETV:
                    {
                        auto valIndex = ctx.readCode<Value>();
                        assert(valIndex.storageType == ValueStorageType_Reg ||
                               valIndex.storageType == ValueStorageType_Ptr);
                        printf("RETV r%hu\n", valIndex.index);
                        auto& ret = ctx.registers[valIndex.index];
                        cc.ret(ret);
                        break;
                    }
                    case INITR:
                    {
                        auto valIndex = ctx.readCode<Value>();
                        assert(valIndex.storageType == ValueStorageType_Reg ||
                               valIndex.storageType == ValueStorageType_Ptr);
                        if(valIndex.index >= ctx.registers.size())
                            throw std::runtime_error("Undefined register index");

                        printf("INITR reg%hu ", valIndex.index);

                        if(valIndex.storageType == ValueStorageType_Ptr)
                        {
                            printf("ptr\n");
                            ctx.registers[valIndex.index] = cc.newIntPtr();
                            break;
                        }

                        Reg newReg;
                        switch(valIndex.valueType)
                        {
                            case ValueType::Bool:
                            case ValueType::Char:
                                printf("uint8");
                                newReg = cc.newUInt8();
                                break;
                            case ValueType::UInt32:
                                printf("uint32");
                                newReg = cc.newUInt32();
                                break;
                            case ValueType::Int32:
                                printf("int32");
                                newReg = cc.newInt32();
                                break;
                            case ValueType::UInt64:
                                printf("uint64");
                                newReg = cc.newUInt64();
                                break;
                            case ValueType::Int64:
                                printf("int64");
                                newReg = cc.newInt64();
                                break;
                            case ValueType::Float32:
                                printf("float");
                                newReg = cc.newXmmSs();
                                break;
                            case ValueType::Float64:
                                printf("double");
                                newReg = cc.newXmmSd();
                                break;
                            case ValueType::Struct:
                                printf("ptr");
                                newReg = cc.newIntPtr();
                                break;
                            default:
                                throw std::runtime_error("Unimplemented type");
                        }
                        printf("\n");
                        ctx.registers[valIndex.index] = newReg;
                        break;
                    }
                    case ALLOC:
                    {
                        auto valIndex = ctx.readCode<Value>();
                        assert(valIndex.storageType == ValueStorageType_Ptr);
                        auto allocSize = ctx.readCode<uint16_t>();
                        printf("ALLOC gp%hu, %hubytes\n", valIndex.index, allocSize);
                        ctx.stackSize += allocSize;
                        if(ctx.stackSize > maxStackSize)
                            throw std::runtime_error("Attempted to compile function that requires more stack memory than the set maximum stack size");
                        auto stackMem = cc.newStack(allocSize, 4);
                        cc.lea(ctx.getReg<Gp>(valIndex), stackMem);
                        break;
                    }
                    case MALLOC:
                    {
                        auto valIndex = ctx.readCode<Value>();
                        assert(valIndex.storageType == ValueStorageType_Ptr);
                        auto allocSize = ctx.readCode<uint16_t>();
                        printf("EXMALLOC gp%hu, %hubytes\n", valIndex.index, allocSize);

                        asmjit::InvokeNode* in;
                        cc.invoke(&in, &scriptAlloc, asmjit::FuncSignatureT<void*, uint16_t>());

                        in->setRet(0, ctx.getReg<Gp>(valIndex));
                        in->setArg(0, asmjit::Imm(allocSize));
                        break;
                    }
                    case FREE:
                    {
                        auto valIndex = ctx.readCode<Value>();
                        asmjit::InvokeNode* in;
                        cc.invoke(&in, &scriptDealoc, asmjit::FuncSignatureT<void, void*>());
                        in->setArg(0, ctx.getReg<Gp>(valIndex));
                        break;
                    }
                    case LOADC:
                    {
                        Value constant = ctx.readCode<Value>();
                        printf("LOADC mem%hu ", constant.index);
                        if(ctx.constants.size() <= constant.index)
                            throw std::runtime_error("attempted to use unallocated memory locations");
                        switch(constant.valueType)
                        {
                            case ValueType::Char:
                            case ValueType::Bool:
                            {
                                auto val = ctx.readCode<uint8_t>();
                                printf("uint8 (char/bool) %u\n", val);
                                ctx.constants[constant.index] = cc.newByteConst(asmjit::ConstPoolScope::kLocal, val);
                                break;
                            }
                            case ValueType::UInt32:
                            {
                                auto val = ctx.readCode<uint32_t>();
                                printf("uint32 %u\n", val);
                                ctx.constants[constant.index] = cc.newUInt32Const(asmjit::ConstPoolScope::kLocal, val);
                                break;
                            }
                            case ValueType::Int32:
                            {
                                auto val = ctx.readCode<int32_t>();
                                printf("int32 %i\n", val);
                                ctx.constants[constant.index] = cc.newInt32Const(asmjit::ConstPoolScope::kLocal, val);
                                break;
                            }
                            case ValueType::UInt64:
                            {
                                auto val = ctx.readCode<uint64_t>();
                                printf("uint64 %llu\n", val);
                                ctx.constants[constant.index] = cc.newUInt64Const(asmjit::ConstPoolScope::kLocal, val);
                                break;
                            }
                            case ValueType::Int64:
                            {
                                auto val = ctx.readCode<int64_t>();
                                printf("int64 %lli\n", val);
                                ctx.constants[constant.index] = cc.newInt64Const(asmjit::ConstPoolScope::kLocal, val);
                                break;
                            }
                            case ValueType::Float32:
                            {
                                auto val = ctx.readCode<float>();
                                printf("float %f\n", val);
                                ctx.constants[constant.index] = cc.newFloatConst(asmjit::ConstPoolScope::kLocal, val);
                                break;
                            }
                            case ValueType::Float64:
                            {
                                auto val = ctx.readCode<double>();
                                printf("double %f\n", val);
                                ctx.constants[constant.index] = cc.newDoubleConst(asmjit::ConstPoolScope::kLocal, val);
                                break;
                            }
                            default:
                                assert(false);
                        }

                        break;
                    }
                    case LOADS:
                    {
                        auto value = ctx.readCode<Value>();
                        auto size = ctx.readCode<uint32_t>();
                        auto* text = new std::string();
                        text->resize(size);
                        for(char& c : *text)
                            c = ctx.readCode<char>();

                        printf("LOADS mem%hu %s\n", value.index, text->c_str());
                        script->constStrings.push_back(std::unique_ptr<std::string>(text));
                        ctx.constants[value.index] = cc.newConst(asmjit::ConstPoolScope::kLocal, &text, sizeof(text));
                    }
                    break;
                    case MARK:
                    {
                        auto markIndex = ctx.readCode<uint32_t>();
                        printf("MARK mark%u\n", markIndex);
                        cc.bind(ctx.getLabel(markIndex, cc));
                        break;
                    }
                    case CMP:
                    {
                        auto a = ctx.readCode<Value>();
                        auto b = ctx.readCode<Value>();
                        printf("CMP ");
                        switch(getOperationType(a, b))
                        {
                            case gp_gp:
                            {
                                printf("gp%hu gp%hu\n", a.index, b.index);
                                auto ar = ctx.getReg<Gpd>(a);
                                auto br = ctx.getReg<Gpd>(b);
                                cc.cmp(ar, br);
                            }
                            break;
                            case gp_mem:
                            {
                                printf("gp%hu mem%hu\n", a.index, b.index);
                                auto ar = ctx.getReg<Gpd>(a);
                                auto br = ctx.constants[b.index];
                                cc.cmp(ar, br);
                            }
                            break;
                            case xmm_xmm:
                            {
                                printf("xmm%hu xmm%hu\n", a.index, b.index);
                                auto ar = ctx.getReg<Xmm>(a);
                                auto br = ctx.getReg<Xmm>(b);
                                cc.ucomiss(ar, br);
                            }
                            break;
                            case xmm_mem:
                            {
                                printf("xmm%hu mem%hu\n", a.index, b.index);
                                auto ar = ctx.getReg<Xmm>(a);
                                auto br = ctx.constants[b.index];
                                cc.ucomiss(ar, br);
                            }
                            break;
                            default:
                                assert(false);
                        }
                        break;
                    }
                    case TEST:
                    {
                        auto a = ctx.readCode<Value>();
                        printf("TEST ");
                        switch(getValueRegType(a))
                        {
                            case ValueRegType::gp:
                                printf("gp%hu\n", a.index);
                                cc.test(ctx.getReg<Gp>(a), ctx.getReg<Gp>(a));
                                break;
                            default:
                                assert(false);
                        }
                        break;
                    }
                    case JMP:
                    {
                        auto markIndex = ctx.readCode<uint32_t>();
                        printf("JMP mark%u\n", markIndex);
                        cc.jmp(ctx.getLabel(markIndex, cc));
                        break;
                    }
                    case JE:
                    {
                        auto markIndex = ctx.readCode<uint32_t>();
                        printf("JE mark%u\n", markIndex);
                        cc.je(ctx.getLabel(markIndex, cc));
                        break;
                    }
                    case JNE:
                    {
                        auto markIndex = ctx.readCode<uint32_t>();
                        printf("JNE mark%u\n", markIndex);
                        cc.jne(ctx.getLabel(markIndex, cc));
                        break;
                    }
                    case JA:
                    {
                        auto markIndex = ctx.readCode<uint32_t>();
                        printf("JA mark%u\n", markIndex);
                        cc.ja(ctx.getLabel(markIndex, cc));
                        break;
                    }
                    case JB:
                    {
                        auto markIndex = ctx.readCode<uint32_t>();
                        printf("JB mark%u\n", markIndex);
                        cc.jb(ctx.getLabel(markIndex, cc));
                        break;
                    }
                    case JG:
                    {
                        auto markIndex = ctx.readCode<uint32_t>();
                        printf("JG mark%u\n", markIndex);
                        cc.jg(ctx.getLabel(markIndex, cc));
                        break;
                    }
                    case JL:
                    {
                        auto markIndex = ctx.readCode<uint32_t>();
                        printf("JL mark%u\n", markIndex);
                        cc.jl(ctx.getLabel(markIndex, cc));
                        break;
                    }
                    case JAE:
                    {
                        auto markIndex = ctx.readCode<uint32_t>();
                        printf("JAE mark%u\n", markIndex);
                        cc.jae(ctx.getLabel(markIndex, cc));
                        break;
                    }
                    case JBE:
                    {
                        auto markIndex = ctx.readCode<uint32_t>();
                        printf("JBE mark%u\n", markIndex);
                        cc.jbe(ctx.getLabel(markIndex, cc));
                        break;
                    }
                    case JGE:
                    {
                        auto markIndex = ctx.readCode<uint32_t>();
                        printf("JGE mark%u\n", markIndex);
                        cc.jge(ctx.getLabel(markIndex, cc));
                        break;
                    }
                    case JLE:
                    {
                        auto markIndex = ctx.readCode<uint32_t>();
                        printf("JLE mark%u\n", markIndex);
                        cc.jle(ctx.getLabel(markIndex, cc));
                        break;
                    }
                    case CALL:
                    {
                        auto fIndex = ctx.readCode<int16_t>();
                        asmjit::FuncSignatureBuilder sb;
                        sb.setCallConvId(asmjit::CallConvId::kCDecl);
                        printf("CALL ");
                        if(fIndex >= 0)
                        {
                            // Internal func call
                            auto& function = irScript->localFunctions[fIndex];
                            assert(fIndex < irScript->localFunctions.size());

                            sb.setRet(strToASMType(function.returnType.type));
                            for(auto& arg : function.arguments)
                                sb.addArg(strToASMType(arg.type));

                            asmjit::InvokeNode* in;
                            assert(fIndex <= script->functions.size());
                            if(fIndex < script->functions.size())
                                cc.invoke(&in, script->functions[fIndex], sb);
                            else
                                cc.invoke(&in, f->label(), sb);

                            printf("%s %s(", function.returnType.type.c_str(), function.sig.c_str());
                            if(function.returnType.type != "void")
                            {
                                auto retVal = ctx.readCode<Value>();
                                in->setRet(0, ctx.getReg<Reg>(retVal));
                            }
                            for(uint32_t i = 0; i < function.arguments.size(); ++i)
                            {
                                auto argVal = ctx.readCode<Value>();
                                in->setArg(i, ctx.getReg<Reg>(argVal));
                                printf("reg%hu = %s", argVal.index,  function.arguments[i].type.c_str());
                                if(i != function.arguments.size() - 1)
                                    printf(", ");
                            }
                            printf(")\n");
                            break;
                        }

                        // External func call
                        fIndex = -1 - fIndex;
                        assert(fIndex < linkedFunctions.size());
                        auto function = linkedFunctions[fIndex];

                        if(function->ret != "void")
                            sb.setRet(strToASMType(function->ret));
                        else
                            sb.setRet(asmjit::TypeId::kVoid);
                        for(size_t arg = 0; arg < function->argCount; ++arg)
                            sb.addArg(strToASMType(function->def.argType(arg)));

                        asmjit::InvokeNode* in;
                        cc.invoke(&in, function->pointer, sb);

                        if(function->ret != "void")
                        {
                            auto retVal = ctx.readCode<Value>();
                            in->setRet(0, ctx.getReg<Reg>(retVal));
                        }
                        for(uint32_t i = 0; i < function->argCount; ++i)
                        {
                            auto argVal = ctx.readCode<Value>();
                            in->setArg(i, ctx.getReg<Reg>(argVal));
                        }
                        printf("%s %s\n", function->ret.c_str(), function->name.c_str());
                        break;
                    }
                    case MOV:
                    {
                        auto dest = ctx.readCode<Value>();
                        auto src = ctx.readCode<Value>();

                        printf("MOV ");
                        switch(getOperationType(dest, src))
                        {
                            case gp_gp:
                            {
                                printf("gp%hu gp%hu\n", dest.index, src.index);
                                auto destReg = ctx.getReg<Gp>(dest);
                                auto srcReg = ctx.getReg<Gp>(src);
                                cc.mov(destReg, srcReg);
                            }
                            break;
                            case gp_mem:
                            {
                                printf("gp%hu mem%hu (+%hu)\n", dest.index, src.index, src.offset);
                                auto srcMem = ctx.getReg<Mem>(src);
                                auto destReg = ctx.getReg<Gp>(dest);
                                cc.mov(destReg, srcMem);
                            }
                            break;
                            case mem_gp:
                            {
                                printf("mem%hu (+%hu) gp%hu\n", dest.index, dest.offset, src.index);
                                auto srcReg = ctx.getReg<Gp>(src);
                                auto destMem = ctx.getReg<Mem>(dest);
                                cc.mov(destMem, srcReg);
                            }
                            break;
                            case xmm_xmm:
                            {
                                printf("xmm%hu xmm%hu\n", dest.index, src.index);
                                auto destReg = ctx.getReg<Xmm>(dest);
                                auto srcReg = ctx.getReg<Xmm>(src);
                                if(dest.valueType == ValueType::Float32)
                                    cc.movss(destReg, srcReg);
                                else
                                    cc.movsd(destReg, srcReg);
                            }
                            break;
                            case xmm_mem:
                            {
                                printf("xmm%hu mem%hu (+%hu)\n", dest.index, src.index, src.offset);
                                auto destReg = ctx.getReg<Xmm>(dest);
                                auto srcMem = ctx.getReg<Mem>(src);
                                if(dest.valueType == ValueType::Float32)
                                    cc.movss(destReg, srcMem);
                                else
                                    cc.movsd(destReg, srcMem);
                            }
                            break;
                            case mem_xmm:
                            {
                                printf("mem%hu (+%hu) xmm%hu\n", dest.index, dest.offset, src.index);
                                auto destMem = ctx.getReg<Mem>(dest);
                                auto srcReg = ctx.getReg<Xmm>(src);
                                if(src.valueType == ValueType::Float32)
                                    cc.movss(destMem, srcReg);
                                else
                                    cc.movsd(destMem, srcReg);
                                break;
                            }
                            case mem_mem:
                            {
                                auto destMem = ctx.getReg<Mem>(dest);
                                auto srcMem = ctx.getReg<Mem>(src);
                                printf("mem%hu (+%hu) mem%hu (+%hu)\n", dest.index, dest.offset, src.index, src.offset);
                                Gp tempReg;
                                switch(src.valueType)
                                {
                                    case ValueType::Bool:
                                    case ValueType::Char:
                                        tempReg = cc.newGpb();
                                        break;
                                    case ValueType::UInt32:
                                    case ValueType::Int32:
                                    case ValueType::Float32:
                                        tempReg = cc.newGpd();
                                        break;
                                    case ValueType::UInt64:
                                    case ValueType::Int64:
                                    case ValueType::Float64:
                                        tempReg = cc.newGpq();
                                        break;
                                    default:
                                        assert(false);
                                }
                                cc.mov(tempReg, srcMem);
                                cc.mov(destMem, tempReg);
                                break;
                            }
                            default:
                                throw std::runtime_error("Invalid mov operands");
                        }
                        break;
                    }
                    case MOVI:
                    {
                        auto dest = ctx.readCode<Value>();
                        assert(dest.storageType == ValueStorageType_Reg || dest.storageType == ValueStorageType_Ptr);

                        printf("MOVI \n");
                        switch(dest.valueType)
                        {
                            case ValueType::Char:
                            case ValueType::Bool:
                                cc.mov(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<uint8_t>()));
                                break;
                            case ValueType::Int32:
                                cc.mov(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<int32_t>()));
                                break;
                            case ValueType::Int64:
                                cc.mov(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<int64_t>()));
                                break;
                            case ValueType::Float32:
                            {
                                auto d = cc.newFloatConst(asmjit::ConstPoolScope::kLocal, ctx.readCode<float>());
                                cc.movss(ctx.getReg<Xmm>(dest), d);
                            }
                            break;
                            case ValueType::Float64:
                            {
                                auto d = cc.newDoubleConst(asmjit::ConstPoolScope::kLocal, ctx.readCode<double>());
                                cc.movss(ctx.getReg<Xmm>(dest), d);
                            }
                            break;
                            case ValueType::Struct:
                                cc.mov(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<int32_t>()));
                                break;
                            default:
                                assert(false);
                        }
                        break;
                    }
                    case CI64I32:
                    {
                        auto dest = ctx.readCode<Value>();
                        auto src = ctx.readCode<Value>();

                        printf("CI64I32 gp%hu gp%hu\n", dest.index, src.index);
                        auto destReg = ctx.getReg<Gp>(dest);
                        auto srcReg = ctx.getReg<Gpq>(src);
                        srcReg.setRegT<asmjit::RegType::kGp32>(srcReg.id());
                        cc.mov(destReg, srcReg);
                        srcReg.setRegT<asmjit::RegType::kGp64>(srcReg.id());
                    }
                    break;
                    case CI32I64:
                    {
                        auto dest = ctx.readCode<Value>();
                        auto src = ctx.readCode<Value>();

                        printf("CI32I64 gp%hu gp%hu\n", dest.index, src.index);
                        auto destReg = ctx.getReg<Gpq>(dest);
                        auto srcReg = ctx.getReg<Gp>(src);

                        destReg.setRegT<asmjit::RegType::kGp32>(destReg.id());
                        cc.movsxd(destReg, srcReg);
                        destReg.setRegT<asmjit::RegType::kGp64>(destReg.id());
                        break;
                    }
                    case CU32U64:
                    {
                        auto dest = ctx.readCode<Value>();
                        auto src = ctx.readCode<Value>();

                        printf("CU32U64 gp%hu gp%hu\n", dest.index, src.index);
                        auto destReg = ctx.getReg<Gpq>(dest);
                        auto srcReg = ctx.getReg<Gp>(src);

                        destReg.setRegT<asmjit::RegType::kGp32>(destReg.id());
                        cc.mov(destReg, srcReg);
                        destReg.setRegT<asmjit::RegType::kGp64>(destReg.id());
                        break;
                    }
                    case CU32I32:
                    {
                        auto dest = ctx.readCode<Value>();
                        auto src = ctx.readCode<Value>();

                        printf("CU32I32 gp%hu gp%hu\n", dest.index, src.index);
                        auto destReg = ctx.getReg<Gpd>(dest);
                        auto srcReg = ctx.getReg<Gpw>(src);

                        srcReg.setRegT<asmjit::RegType::kGp16>(srcReg.id());
                        cc.movzx(destReg, srcReg);
                        srcReg.setRegT<asmjit::RegType::kGp32>(srcReg.id());

                        break;
                    }
                    case CU64I64:
                    {
                        auto dest = ctx.readCode<Value>();
                        auto src = ctx.readCode<Value>();

                        printf("CU64I64 gp%hu gp%hu\n", dest.index, src.index);
                        auto destReg = ctx.getReg<Gp>(dest);
                        auto srcReg = ctx.getReg<Gp>(src);

                        srcReg.setRegT<asmjit::RegType::kGp32>(srcReg.id());
                        destReg.setRegT<asmjit::RegType::kGp32>(destReg.id());
                        cc.mov(destReg, srcReg);
                        srcReg.setRegT<asmjit::RegType::kGp64>(srcReg.id());
                        destReg.setRegT<asmjit::RegType::kGp64>(destReg.id());
                        break;
                    }
                    case CF32I32:
                    {
                        auto dest = ctx.readCode<Value>();
                        auto src = ctx.readCode<Value>();

                        printf("CF32I32 gp%hu xmm%hu\n", dest.index, src.index);
                        auto destReg = ctx.getReg<Gp>(dest);
                        auto srcReg = ctx.getReg<Xmm>(src);
                        cc.cvttss2si(destReg, srcReg);
                    }
                    break;
                    case CF64I32:
                    {
                        auto dest = ctx.readCode<Value>();
                        auto src = ctx.readCode<Value>();

                        printf("CF64I32 gp%hu xmm%hu\n", dest.index, src.index);
                        auto destReg = ctx.getReg<Gp>(dest);
                        auto srcReg = ctx.getReg<Xmm>(src);
                        cc.cvttsd2si(destReg, srcReg);
                    }
                    break;
                    case CI32F32:
                    {
                        auto dest = ctx.readCode<Value>();
                        auto src = ctx.readCode<Value>();

                        printf("CI32F32 xmm%hu gp%hu\n", dest.index, src.index);
                        auto destReg = ctx.getReg<Xmm>(dest);
                        auto srcReg = ctx.getReg<Gp>(src);
                        cc.cvtsi2ss(destReg, srcReg);
                    }
                    break;
                    case CI32F64:
                    {
                        auto dest = ctx.readCode<Value>();
                        auto src = ctx.readCode<Value>();

                        printf("CI32F64 xmm%hu gp%hu\n", dest.index, src.index);
                        auto destReg = ctx.getReg<Xmm>(dest);
                        auto srcReg = ctx.getReg<Gp>(src);
                        cc.cvtsi2sd(destReg, srcReg);
                    }
                    break;
                    case CF32F64:
                    {
                        auto dest = ctx.readCode<Value>();
                        auto src = ctx.readCode<Value>();

                        printf("CF32F64 xmm%hu xmm%hu\n", dest.index, src.index);
                        auto destReg = ctx.getReg<Xmm>(dest);
                        auto srcReg = ctx.getReg<Xmm>(src);

                        cc.cvtss2sd(destReg, srcReg);
                    }
                    break;
                    case CF64F32:
                    {
                        auto dest = ctx.readCode<Value>();
                        auto src = ctx.readCode<Value>();

                        printf("CF64F32 xmm%hu xmm%hu\n", dest.index, src.index);
                        auto destReg = ctx.getReg<Xmm>(dest);
                        auto srcReg = ctx.getReg<Xmm>(src);

                        cc.cvtsd2ss(destReg, srcReg);
                    }
                    break;
                    case SETE:
                    {
                        auto regIndex = ctx.readCode<Value>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        printf("SETE gp%hu\n", regIndex.index);
                        cc.sete(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETNE:
                    {
                        auto regIndex = ctx.readCode<Value>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        printf("SETNE gp%hu\n", regIndex.index);
                        cc.sete(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETA:
                    {
                        auto regIndex = ctx.readCode<Value>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        printf("SETA gp%hu\n", regIndex.index);
                        cc.seta(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETG:
                    {
                        auto regIndex = ctx.readCode<Value>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        printf("SETG gp%hu\n", regIndex.index);
                        cc.setg(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETAE:
                    {
                        auto regIndex = ctx.readCode<Value>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        printf("SETAE gp%hu\n", regIndex.index);
                        cc.setae(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETGE:
                    {
                        auto regIndex = ctx.readCode<Value>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        printf("SETGE gp%hu\n", regIndex.index);
                        cc.setge(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case ADD:
                    {
                        auto a = ctx.readCode<Value>();
                        auto b = ctx.readCode<Value>();
                        printf("ADD ");
                        switch(getOperationType(a, b))
                        {
                            case gp_gp:
                            {
                                printf("gp%hu gp%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Gp>(a);
                                auto bReg = ctx.getReg<Gp>(b);
                                cc.add(aReg, bReg);
                            }
                            break;
                            case gp_mem:
                            {
                                printf("gp%hu mem%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Gp>(a);
                                auto mem = ctx.getReg<Mem>(b);
                                cc.add(aReg, mem);
                            }
                            break;
                            case xmm_xmm:
                            {
                                printf("xmm%hu xmm%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Xmm>(a);
                                auto bReg = ctx.getReg<Xmm>(b);
                                if(a.valueType == ValueType::Float32)
                                    cc.addss(aReg, bReg);
                                else
                                    cc.addsd(aReg, bReg);
                            }
                            break;
                            case xmm_mem:
                            {
                                printf("xmm%hu mem%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Xmm>(a);
                                auto mem = ctx.getReg<Mem>(b);
                                if(a.valueType == ValueType::Float32)
                                    cc.addss(aReg, mem);
                                else
                                    cc.addsd(aReg, mem);
                            }
                            break;
                            default:
                                throw std::runtime_error("Invalid add operands");
                        }
                        break;
                    }
                    case ADDI:
                    {
                        auto dest = ctx.readCode<Value>();
                        assert(dest.storageType == ValueStorageType_Reg || dest.storageType == ValueStorageType_Ptr);

                        printf("ADDI \n");
                        switch(dest.valueType)
                        {
                            case ValueType::Int32:
                                cc.add(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<int32_t>()));
                                break;
                            case ValueType::Int64:
                                cc.add(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<int64_t>()));
                                break;
                            case ValueType::Float32:
                            {
                                auto d = cc.newFloatConst(asmjit::ConstPoolScope::kLocal, ctx.readCode<float>());
                                cc.addss(ctx.getReg<Xmm>(dest), d);
                            }
                            break;
                            case ValueType::Float64:
                            {
                                auto d = cc.newDoubleConst(asmjit::ConstPoolScope::kLocal, ctx.readCode<double>());
                                cc.addss(ctx.getReg<Xmm>(dest), d);
                            }
                            break;
                            case ValueType::Struct:
                                cc.add(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<int32_t>()));
                                break;
                            default:
                                assert(false);
                        }
                        break;
                    }
                    case SUB:
                    {
                        auto a = ctx.readCode<Value>();
                        auto b = ctx.readCode<Value>();
                        printf("SUB ");
                        switch(getOperationType(a, b))
                        {
                            case gp_gp:
                            {
                                printf("gp%hu gp%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Gp>(a);
                                auto bReg = ctx.getReg<Gp>(b);
                                cc.sub(aReg, bReg);
                            }
                            break;
                            case gp_mem:
                            {
                                printf("gp%hu mem%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Gp>(a);
                                auto mem = ctx.getReg<Mem>(b);
                                cc.sub(aReg, mem);
                            }
                            break;
                            case xmm_xmm:
                            {
                                printf("xmm%hu xmm%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Xmm>(a);
                                auto bReg = ctx.getReg<Xmm>(b);
                                if(a.valueType == ValueType::Float32)
                                    cc.subss(aReg, bReg);
                                else
                                    cc.subsd(aReg, bReg);
                            }
                            break;
                            case xmm_mem:
                            {
                                printf("xmm%hu mem%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Xmm>(a);
                                auto mem = ctx.getReg<Mem>(b);
                                if(a.valueType == ValueType::Float32)
                                    cc.subss(aReg, mem);
                                else
                                    cc.subsd(aReg, mem);
                            }
                            break;
                            default:
                                throw std::runtime_error("Invalid sub operands");
                        }
                        break;
                    }
                    case MUL:
                    {
                        auto a = ctx.readCode<Value>();
                        auto b = ctx.readCode<Value>();
                        printf("MUL ");
                        switch(getOperationType(a, b))
                        {
                            case gp_gp:
                            {
                                printf("gp%hu gp%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Gp>(a);
                                auto bReg = ctx.getReg<Gp>(b);
                                switch(a.valueType)
                                {
                                    case ValueType::UInt32:
                                    {
                                        auto upper = cc.newUInt32();
                                        cc.xor_(upper, upper);
                                        cc.mul(upper, aReg, bReg);
                                    }
                                    break;
                                    case ValueType::UInt64:
                                    {
                                        auto upper = cc.newUInt64();
                                        cc.xor_(upper, upper);
                                        cc.mul(upper, aReg, bReg);
                                    }
                                    break;
                                    case ValueType::Int32:
                                    {
                                        auto upper = cc.newInt32();
                                        cc.cdq(upper, aReg);
                                        cc.imul(upper, aReg, bReg);
                                    }
                                    break;
                                    case ValueType::Int64:
                                    {
                                        auto upper = cc.newInt64();
                                        cc.cqo(upper, aReg);
                                        cc.imul(aReg, bReg);
                                    }
                                    break;
                                    default:
                                        assert(false);
                                        break;
                                }
                            }
                            break;
                            case gp_mem:
                            {
                                printf("gp%hu mem%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Gp>(a);
                                auto mem = ctx.getReg<Mem>(b);
                                switch(a.valueType)
                                {
                                    case ValueType::UInt32:
                                    {
                                        auto upper = cc.newUInt32();
                                        cc.xor_(upper, upper);
                                        cc.mul(upper, aReg, mem);
                                    }
                                    break;
                                    case ValueType::UInt64:
                                    {
                                        auto upper = cc.newUInt64();
                                        cc.xor_(upper, upper);
                                        cc.mul(upper, aReg, mem);
                                    }
                                    break;
                                    case ValueType::Int32:
                                    {
                                        auto upper = cc.newInt32();
                                        cc.cdq(upper, aReg);
                                        cc.imul(upper, aReg, mem);
                                    }
                                    break;
                                    case ValueType::Int64:
                                    {
                                        auto upper = cc.newInt64();
                                        cc.cqo(upper, aReg);
                                        cc.imul(aReg, mem);
                                    }
                                    break;
                                    default:
                                        assert(false);
                                        break;
                                }
                            }
                            break;
                            case xmm_xmm:
                            {
                                printf("xmm%hu xmm%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Xmm>(a);
                                auto bReg = ctx.getReg<Xmm>(b);
                                if(a.valueType == ValueType::Float32)
                                    cc.mulss(aReg, bReg);
                                else
                                    cc.mulsd(aReg, bReg);
                            }
                            break;
                            case xmm_mem:
                            {
                                printf("xmm%hu mem%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Xmm>(a);
                                auto mem = ctx.getReg<Mem>(b);
                                if(a.valueType == ValueType::Float32)
                                    cc.mulss(aReg, mem);
                                else
                                    cc.mulsd(aReg, mem);
                            }
                            break;
                            default:
                                throw std::runtime_error("Invalid mul operands");
                        }
                        break;
                    }
                    case DIV:
                    {
                        auto a = ctx.readCode<Value>();
                        auto b = ctx.readCode<Value>();
                        printf("DIV ");
                        switch(getOperationType(a, b))
                        {
                            case gp_gp:
                            {
                                printf("gp%hu gp%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Gp>(a);
                                auto bReg = ctx.getReg<Gp>(b);
                                switch(a.valueType)
                                {
                                    case ValueType::UInt32:
                                    {
                                        auto remainder = cc.newUInt32();
                                        cc.xor_(remainder, remainder);
                                        cc.div(remainder, aReg, bReg);
                                    }
                                    break;
                                    case ValueType::UInt64:
                                    {
                                        auto remainder = cc.newUInt64();
                                        cc.xor_(remainder, remainder);
                                        cc.div(remainder, aReg, bReg);
                                    }
                                    break;
                                    case ValueType::Int32:
                                    {
                                        auto remainder = cc.newInt32();
                                        cc.cdq(remainder, aReg);
                                        cc.idiv(remainder, aReg, bReg);
                                    }
                                    break;
                                    case ValueType::Int64:
                                    {
                                        auto remainder = cc.newInt64();
                                        cc.cqo(remainder, aReg);
                                        cc.idiv(remainder, aReg, bReg);
                                    }
                                    break;
                                    default:
                                        assert(false);
                                }
                            }
                            break;
                            case gp_mem:
                            {
                                printf("gp%hu mem%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Gp>(a);
                                auto mem = ctx.getReg<Mem>(b);
                                switch(a.valueType)
                                {
                                    case ValueType::UInt32:
                                    {
                                        auto remainder = cc.newUInt32();
                                        cc.xor_(remainder, remainder);
                                        cc.div(remainder, aReg, mem);
                                    }
                                    break;
                                    case ValueType::UInt64:
                                    {
                                        auto remainder = cc.newUInt64();
                                        cc.xor_(remainder, remainder);
                                        cc.div(remainder, aReg, mem);
                                    }
                                    break;
                                    case ValueType::Int32:
                                    {
                                        auto remainder = cc.newInt32();
                                        cc.cdq(remainder, aReg);
                                        cc.idiv(remainder, aReg, mem);
                                    }
                                    break;
                                    case ValueType::Int64:
                                    {
                                        auto remainder = cc.newInt64();
                                        cc.cqo(remainder, aReg);
                                        cc.idiv(remainder, aReg, mem);
                                    }
                                    break;
                                    default:
                                        assert(false);
                                }
                            }
                            break;
                            case xmm_xmm:
                            {
                                printf("xmm%hu xmm%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Xmm>(a);
                                auto bReg = ctx.getReg<Xmm>(b);
                                if(a.valueType == ValueType::Float32)
                                    cc.divss(aReg, bReg);
                                else
                                    cc.divsd(aReg, bReg);
                            }
                            break;
                            case xmm_mem:
                            {
                                printf("xmm%hu mem%hu\n", a.index, b.index);
                                auto aReg = ctx.getReg<Xmm>(a);
                                auto mem = ctx.getReg<Mem>(b);
                                if(a.valueType == ValueType::Float32)
                                    cc.divss(aReg, mem);
                                else
                                    cc.divsd(aReg, mem);
                            }
                            break;
                            default:
                                throw std::runtime_error("Invalid div operands");
                        }
                        break;
                    }
                    default:
                        throw std::runtime_error("unknown op code " + std::to_string(op));
                }
            }
            cc.endFunc();
            cc.finalize();
            void* fPtr = nullptr;
            _runtime.add(&fPtr, &ch);

            script->functionNames.insert({func.sig, script->functions.size()});
            script->functions.push_back(fPtr);
        }

        auto scriptPtr = script.get();
        _scripts.push_back(std::move(script));

        scriptPtr->init();
        return scriptPtr;
    }

    void ScriptRuntime::setLinker(Linker* linker)
    {
        assert(linker);
        _linker = linker;
    }
} // namespace BraneScript
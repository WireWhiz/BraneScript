//
// Created by wirewhiz on 15/10/22.
//

#include "scriptRuntime.h"
#include "script.h"
#include "irScript.h"
#include "valueIndex.h"
#include "asmjit/core/globals.h"
#include "library.h"
#include "linker.h"
#include "structDefinition.h"

#include "asmjit/asmjit.h"
#include <cstdio>
#include <stdexcept>
#include <cassert>

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
        switch (value.valueType)
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
        if (str == "void") return asmjit::TypeId::kVoid;
        if (str == "bool") return asmjit::TypeId::kUInt8;
        if (str == "int") return asmjit::TypeId::kInt32;
        if (str == "float") return asmjit::TypeId::kFloat32;
        if (str == "uint") return asmjit::TypeId::kUInt32;
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
                break; //goto next switch statement
            case ValueStorageType_Ptr:
                return ValueRegType::gp;
            case ValueStorageType_DerefPtr:
            case ValueStorageType_Const:
                return ValueRegType::mem;
            default:
                assert(false);
        }
        switch (value.valueType)
        {
            case Bool:
            case Int32:
            case Int64:
                return ValueRegType::gp;
            case Float32:
            case Float64:
                return ValueRegType::xmm;
            case Struct:
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
        switch (getValueRegType(a))
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

        std::vector<asmjit::x86::Reg> registers;
        std::vector<asmjit::x86::Mem> constants;
        std::vector<asmjit::Label> labels;

        template<typename T>
        T readCode()
        {
            return currentFunction->readCode<T>(iptr);
        }

        inline std::string readString()
        {
            return currentFunction->readString(iptr);
        }

        bool endOfCode() const
        {
            return iptr >= currentFunction->code.size();
        }

        void verifyValue(Value value, Compiler& cc)
        {
            if (value.index < registers.size())
                return;
            if (value.index != registers.size())
                throw std::runtime_error("Can only create next register index in sequence");
            switch (value.valueType)
            {
                case ValueType::Bool:
                    registers.push_back(cc.newUInt8());
                    break;
                case ValueType::Int32:
                    registers.push_back(cc.newInt32());
                    break;
                case ValueType::Float32:
                    registers.push_back(cc.newXmmSs());
                    break;
                case ValueType::Struct:
                    registers.push_back(cc.newIntPtr());
                    break;
                default:
                    throw std::runtime_error("Unimplemented type");
            }
        }

        template<class RT>
        RT getReg(Value value)
        {
            if constexpr (std::is_same<RT, Mem>())
            {
                if(value.storageType == ValueStorageType_Const)
                {
                    assert(value.index < constants.size());
                    return constants[value.index];
                }
                //If this isn't a constant, it's safe to assume that it's a dereferenced pointer
                assert(value.storageType == ValueStorageType_DerefPtr);
                assert(value.index < registers.size());
                return asmjit::x86::ptr(registers[value.index].as<Gp>(), value.offset);
            }
            else
            {
                assert(value.index < registers.size());
                if constexpr (std::is_same<RT, Gp>())
                    assert(registers[value.index].isGp());
                if constexpr (std::is_same<RT, Xmm>())
                    assert(registers[value.index].isXmm());
                return registers[value.index].as<RT>();
            }
        }

        asmjit::Label getLabel(uint32_t index, Compiler& cc)
        {
            while (index >= labels.size())
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

        //Generate local struct typedefs
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

        //Link external struct typedefs
        std::vector<const StructDef*> linkedStructs;
        for(auto& s : irScript->linkedStructs)
        {
            assert(_linker);
            auto def = dynamic_cast<const StructDef*>(_linker->getType(s));
            assert(def);
            linkedStructs.push_back(def);
        }

        //Find linked libraries
        std::vector<const Library*> linkedLibraries;
        for(auto& lib : irScript->linkedLibraries)
        {
            assert(_linker);
            auto libPtr = _linker->getLibrary(lib);
            if(!libPtr)
            {
                //TODO error system for script runtime;
                assert(false);
                return nullptr;
            }
            linkedLibraries.push_back(libPtr);
        }

        //Find linked functions
        std::vector<const FunctionData*> linkedFunctions;
        for(auto& func : irScript->linkedFunctions)
        {
            assert(_linker);
            auto funcData = _linker->getFunction(func);
            if(!funcData)
            {
                //TODO runtime assertion system
                assert(false);
                return nullptr;
            }
            linkedFunctions.push_back(funcData);
        }

        JitErrorHandler errorHandler;
        for (auto& func: irScript->localFunctions)
        {
            AssemblyCtx ctx;
            asmjit::CodeHolder ch;
            ctx.currentFunction = &func;

            ch.init(_runtime.environment());
            ch.setErrorHandler(&errorHandler);
            Compiler cc(&ch);
            cc.addDiagnosticOptions(
                    asmjit::DiagnosticOptions::kValidateAssembler | asmjit::DiagnosticOptions::kRADebugAll);
            cc.addEncodingOptions(asmjit::EncodingOptions::kOptimizedAlign);

            printf("Assembling function: %s\n", ctx.currentFunction->name.c_str());

            asmjit::FuncSignatureBuilder sigBuilder;
            std::vector<asmjit::TypeId> argTypes;
            sigBuilder.setCallConvId(asmjit::CallConvId::kCDecl);
            for (auto& arg: func.arguments)
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

            for (size_t i = 0; i < func.arguments.size(); ++i)
            {
                switch (argTypes[i])
                {
                    case asmjit::TypeId::kUInt8:
                        ctx.registers.push_back(cc.newGpb());
                        break;
                    case asmjit::TypeId::kInt32:
                        ctx.registers.push_back(cc.newInt32());
                        break;
                    case asmjit::TypeId::kFloat32:
                        ctx.registers.push_back(cc.newXmmSs());
                        break;
                    case asmjit::TypeId::kIntPtr:
                        ctx.registers.push_back(cc.newIntPtr());
                        break;
                    default:
                        assert(false);
                }
                f->setArg(i, ctx.registers[i]);
            }

            auto& code = func.code;

            while (!ctx.endOfCode())
            {
                auto op = ctx.readCode<Operand>();
                switch (op)
                {
                    case RET:
                        printf("RET\n");
                        if (func.returnType.type != "void")
                            throw std::runtime_error("cannot return nothing from non-void functions");
                        cc.ret();
                        break;
                    case RETV:
                    {
                        auto valIndex = ctx.readCode<Value>();
                        assert(valIndex.storageType == ValueStorageType_Reg || valIndex.storageType == ValueStorageType_Ptr);
                        printf("RETV r%hu\n", valIndex.index);
                        auto& ret = ctx.registers[valIndex.index];
                        cc.ret(ret);

                        break;
                    }
                    case ALLOC:
                    {
                        auto valIndex = ctx.readCode<Value>();
                        assert(valIndex.storageType == ValueStorageType_Ptr);
                        auto structIndex = ctx.readCode<int16_t>();
                        if(structIndex >= 0)
                        {
                            //Local struct alloc
                            assert(structIndex < localStructs.size());
                            auto& structDef = localStructs[structIndex];
                            printf("ALLOC gp%hu, %s\n", valIndex.index, structDef->name());

                            ctx.verifyValue(valIndex, cc);
                            auto stackMem = cc.newStack(structDef->size(), 4);
                            cc.lea(ctx.getReg<Gp>(valIndex), stackMem);
                            break;
                        }
                        //External struct alloc
                        structIndex = -structIndex -int16_t{1};
                        assert(structIndex < linkedStructs.size());
                        auto& structDef = linkedStructs[structIndex];
                        printf("EXALLOC gp%hu, %s\n", valIndex.index, structDef->name());

                        ctx.verifyValue(valIndex, cc);
                        auto size = structDef->size();
                        auto stackMem = cc.newStack(size, 4);
                        cc.lea(ctx.getReg<Gp>(valIndex), stackMem);
                        break;
                        break;
                    }
                    case MALLOC:
                    {
                        auto valIndex = ctx.readCode<Value>();
                        assert(valIndex.storageType == ValueStorageType_Ptr);
                        int16_t structIndex = ctx.readCode<int16_t>();
                        if(structIndex >= 0)
                        {
                            //Internal struct malloc
                            assert(structIndex < localStructs.size());
                            auto& structDef = localStructs[structIndex];
                            printf("MALLOC gp%hu, %s\n", valIndex.index, structDef->name());

                            asmjit::InvokeNode* in;
                            cc.invoke(&in, &scriptAlloc, asmjit::FuncSignatureT<void*, uint16_t>());

                            ctx.verifyValue(valIndex, cc);
                            in->setRet(0, ctx.getReg<Gp>(valIndex));
                            in->setArg(0, asmjit::Imm((uint16_t)structDef->size()));
                            break;
                        }
                        // External struct malloc
                        structIndex = - structIndex - int16_t{1};
                        assert(structIndex < linkedStructs.size());
                        auto& structDef = linkedStructs[structIndex];
                        printf("EXMALLOC gp%hu, %s\n", valIndex.index, structDef->name());

                        asmjit::InvokeNode* in;
                        cc.invoke(&in, &scriptAlloc, asmjit::FuncSignatureT<void*, uint16_t>());

                        ctx.verifyValue(valIndex, cc);
                        in->setRet(0, ctx.getReg<Gp>(valIndex));
                        in->setArg(0, asmjit::Imm((uint16_t)structDef->size()));
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
                        assert(ctx.constants.size() == constant.index);
                        switch (constant.valueType)
                        {
                            case Bool:
                            {
                                int32_t val = ctx.readCode<uint8_t>();
                                printf("bool %i\n", val);
                                ctx.constants.push_back(cc.newByteConst(asmjit::ConstPoolScope::kLocal, val));
                                break;
                            }
                            case Int32:
                            {
                                int32_t val = ctx.readCode<int32_t>();
                                printf("int %i\n", val);
                                ctx.constants.push_back(cc.newInt32Const(asmjit::ConstPoolScope::kLocal, val));
                            }
                                break;
                            case Float32:
                            {
                                float val = ctx.readCode<float>();
                                printf("float %f\n", val);
                                ctx.constants.push_back(cc.newFloatConst(asmjit::ConstPoolScope::kLocal, val));
                            }
                                break;
                            default:
                                assert(false);
                        }

                        break;
                    }
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
                        switch (getOperationType(a, b))
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
                        switch (getValueRegType(a))
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
                            //Internal func call
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

                            if(function.returnType.type != "void")
                            {
                                auto retVal = ctx.readCode<Value>();
                                ctx.verifyValue(retVal, cc);
                                in->setRet(0, ctx.getReg<Reg>(retVal));
                            }
                            for(uint32_t i = 0; i < function.arguments.size(); ++i)
                            {
                                auto argVal = ctx.readCode<Value>();
                                in->setArg(i, ctx.getReg<Reg>(argVal));
                            }
                            printf("%s %s\n", function.returnType.type.c_str(), function.name.c_str());
                            break;
                        }

                        //External func call
                        fIndex = -1 - fIndex;
                        assert(fIndex < linkedFunctions.size());
                        auto function = linkedFunctions[fIndex];

                        if(function->ret != "void")
                            sb.setRet(strToASMType(function->ret));
                        else
                            sb.setRet(asmjit::TypeId::kVoid);
                        for(size_t arg = 0; arg < function->def.argCount(); ++arg)
                            sb.addArg(strToASMType(function->def.argType(arg)));

                        asmjit::InvokeNode* in;
                        cc.invoke(&in, function->pointer, sb);

                        if(function->ret != "void")
                        {
                            auto retVal = ctx.readCode<Value>();
                            ctx.verifyValue(retVal, cc);
                            in->setRet(0, ctx.getReg<Reg>(retVal));
                        }
                        for(uint32_t i = 0; i < function->def.argCount(); ++i)
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
                        ctx.verifyValue(dest, cc);

                        printf("MOV ");
                        switch (getOperationType(dest, src))
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
                            case gp_xmm:
                            {
                                printf("gp%hu xmm%hu\n", dest.index, src.index);
                                auto destReg = ctx.getReg<Gp>(dest);
                                auto srcReg = ctx.getReg<Xmm>(src);
                                cc.cvttss2si(destReg, srcReg);
                            }
                                break;
                            case xmm_xmm:
                            {
                                printf("xmm%hu xmm%hu\n", dest.index, src.index);
                                auto destReg = ctx.getReg<Xmm>(dest);
                                auto srcReg = ctx.getReg<Xmm>(src);
                                cc.movss(destReg, srcReg);
                            }
                                break;
                            case xmm_gp:
                            {
                                printf("xmm%hu gp%hu\n", dest.index, src.index);
                                auto destReg = ctx.getReg<Xmm>(dest);
                                auto srcReg = ctx.getReg<Gp>(src);
                                cc.cvtsi2ss(destReg, srcReg);
                            }
                                break;
                            case xmm_mem:
                            {
                                printf("xmm%hu mem%hu (+%hu)\n", dest.index, src.index, src.offset);
                                auto destReg = ctx.getReg<Xmm>(dest);
                                auto srcMem = ctx.getReg<Mem>(src);
                                cc.movss(destReg, srcMem);
                            }
                                break;
                            case mem_xmm:
                            {
                                printf("mem%hu (+%hu) xmm%hu\n", dest.index, dest.offset, src.index);
                                auto destMem = ctx.getReg<Mem>(dest);
                                auto srcReg = ctx.getReg<Xmm>(src);
                                cc.movss(destMem, srcReg);
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
                                    case Bool:
                                        tempReg = cc.newGpb();
                                        break;
                                    case Int32:
                                    case Float32:
                                        tempReg = cc.newGpd();
                                        break;
                                    case Int64:
                                    case Float64:
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
                        ctx.verifyValue(dest, cc);

                        printf("MOVI \n");
                        switch(dest.valueType)
                        {
                            case Bool:
                                cc.mov(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<uint8_t>()));
                                break;
                            case Int32:
                                cc.mov(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<int32_t>()));
                                break;
                            case Int64:
                                cc.mov(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<int64_t>()));
                                break;
                            case Float32:
                            {
                                auto d = cc.newFloatConst(asmjit::ConstPoolScope::kLocal, ctx.readCode<float>());
                                cc.movss(ctx.getReg<Xmm>(dest), d);
                            }
                                break;
                            case Float64:
                            {
                                auto d = cc.newDoubleConst(asmjit::ConstPoolScope::kLocal, ctx.readCode<double>());
                                cc.movss(ctx.getReg<Xmm>(dest), d);
                            }
                                break;
                            case Struct:
                                cc.mov(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<int32_t>()));
                                break;
                            default:
                                assert(false);
                        }
                        break;
                    }
                    case SETE:
                    {
                        auto regIndex = ctx.readCode<Value>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        ctx.verifyValue(regIndex, cc);
                        printf("SETE %hu", regIndex.index);
                        cc.sete(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETNE:
                    {
                        auto regIndex = ctx.readCode<Value>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        ctx.verifyValue(regIndex, cc);
                        printf("SETNE %hu", regIndex.index);
                        cc.sete(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETA:
                    {
                        auto regIndex = ctx.readCode<Value>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        ctx.verifyValue(regIndex, cc);
                        printf("SETA %hu", regIndex.index);
                        cc.seta(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETG:
                    {
                        auto regIndex = ctx.readCode<Value>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        ctx.verifyValue(regIndex, cc);
                        printf("SETG %hu", regIndex.index);
                        cc.setg(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETAE:
                    {
                        auto regIndex = ctx.readCode<Value>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        ctx.verifyValue(regIndex, cc);
                        printf("SETAE %hu", regIndex.index);
                        cc.setae(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETGE:
                    {
                        auto regIndex = ctx.readCode<Value>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        ctx.verifyValue(regIndex, cc);
                        printf("SETGE %hu", regIndex.index);
                        cc.setge(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case ADD:
                    {
                        auto a = ctx.readCode<Value>();
                        auto b = ctx.readCode<Value>();
                        printf("ADD ");
                        switch (getOperationType(a, b))
                        {
                            case gp_gp:
                            {
                                printf("gp%hu gp%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Gp>(a);
                                auto srcReg = ctx.getReg<Gp>(b);
                                cc.add(destReg, srcReg);
                            }
                                break;
                            case gp_mem:
                            {
                                printf("gp%hu mem%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Gp>(a);
                                auto srcMem = ctx.getReg<Mem>(b);
                                cc.add(destReg, srcMem);
                            }
                                break;
                            case xmm_xmm:
                            {
                                printf("xmm%hu xmm%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Xmm>(a);
                                auto srcReg = ctx.getReg<Xmm>(b);
                                cc.addss(destReg, srcReg);
                            }
                                break;
                            case xmm_mem:
                            {
                                printf("xmm%hu mem%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Xmm>(a);
                                auto srcReg = ctx.getReg<Mem>(b);
                                cc.addss(destReg, srcReg);
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
                        ctx.verifyValue(dest, cc);

                        printf("ADDI \n");
                        switch(dest.valueType)
                        {
                            case Int32:
                                cc.add(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<int32_t>()));
                                break;
                            case Int64:
                                cc.add(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<int64_t>()));
                                break;
                            case Float32:
                            {
                                auto d = cc.newFloatConst(asmjit::ConstPoolScope::kLocal, ctx.readCode<float>());
                                cc.addss(ctx.getReg<Xmm>(dest), d);
                            }
                                break;
                            case Float64:
                            {
                                auto d = cc.newDoubleConst(asmjit::ConstPoolScope::kLocal, ctx.readCode<double>());
                                cc.addss(ctx.getReg<Xmm>(dest), d);
                            }
                                break;
                            case Struct:
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
                        switch (getOperationType(a, b))
                        {
                            case gp_gp:
                            {
                                printf("gp%hu gp%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Gp>(a);
                                auto srcReg = ctx.getReg<Gp>(b);
                                cc.sub(destReg, srcReg);
                            }
                                break;
                            case gp_mem:
                            {
                                printf("gp%hu mem%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Gp>(a);
                                auto srcMem = ctx.getReg<Mem>(b);
                                cc.sub(destReg, srcMem);
                            }
                                break;
                            case xmm_xmm:
                            {
                                printf("xmm%hu xmm%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Xmm>(a);
                                auto srcReg = ctx.getReg<Xmm>(b);
                                cc.subss(destReg, srcReg);
                            }
                                break;
                            case xmm_mem:
                            {
                                printf("xmm%hu mem%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Xmm>(a);
                                auto srcMem = ctx.getReg<Mem>(b);
                                cc.subss(destReg, srcMem);
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
                        switch (getOperationType(a, b))
                        {
                            case gp_gp:
                            {
                                printf("gp%hu gp%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Gp>(a);
                                auto srcReg = ctx.getReg<Gp>(b);
                                cc.imul(destReg, srcReg);
                            }
                                break;
                            case gp_mem:
                            {
                                printf("gp%hu mem%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Gp>(a);
                                auto srcMem = ctx.getReg<Mem>(b);
                                cc.imul(destReg, srcMem);
                            }
                                break;
                            case xmm_xmm:
                            {
                                printf("xmm%hu xmm%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Xmm>(a);
                                auto srcReg = ctx.getReg<Xmm>(b);
                                cc.mulss(destReg, srcReg);
                            }
                                break;
                            case xmm_mem:
                            {
                                printf("xmm%hu mem%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Xmm>(a);
                                auto srcMem = ctx.getReg<Mem>(b);
                                cc.mulss(destReg, srcMem);
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
                        switch (getOperationType(a, b))
                        {
                            case gp_gp:
                            {
                                printf("gp%hu gp%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Gp>(a);
                                auto srcReg = ctx.getReg<Gp>(b);
                                auto remainder = cc.newInt32();
                                cc.cdq(remainder, destReg);
                                cc.idiv(remainder, destReg, srcReg);
                            }
                                break;
                            case gp_mem:
                            {
                                printf("gp%hu mem%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Gp>(a);
                                auto srcMem = ctx.getReg<Mem>(b);
                                auto remainder = cc.newInt32();
                                cc.cdq(remainder, destReg);
                                cc.idiv(remainder, destReg, srcMem);
                            }
                                break;
                            case xmm_xmm:
                            {
                                printf("xmm%hu xmm%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Xmm>(a);
                                auto srcReg = ctx.getReg<Xmm>(b);
                                cc.divss(destReg, srcReg);
                            }
                                break;
                            case xmm_mem:
                            {
                                printf("xmm%hu mem%hu\n", a.index, b.index);
                                auto destReg = ctx.getReg<Xmm>(a);
                                auto srcMem = ctx.getReg<Mem>(b);
                                cc.divss(destReg, srcMem);
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

            script->functionNames.insert({func.name, script->functions.size()});
            script->functions.push_back(fPtr);
        }

        auto scriptPtr = script.get();
        _scripts.push_back(std::move(script));
        return scriptPtr;
    }

    void ScriptRuntime::setLinker(Linker* linker)
    {
        assert(linker);
        _linker = linker;
    }
}
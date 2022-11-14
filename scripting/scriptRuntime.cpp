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

    asmjit::TypeId valueToASMType(const ValueIndex& value)
    {
        switch (value.valueType)
        {
            case ValueType::Bool:
                return asmjit::TypeId::kUInt8;
            case ValueType::Int32:
                return asmjit::TypeId::kInt32;
            case ValueType::Float32:
                return asmjit::TypeId::kFloat32;
            case ValueType::ObjectRef:
                return asmjit::TypeId::kIntPtr;
            default:
                throw std::runtime_error("Unimplemented type");
        }
    }

    asmjit::TypeId strToASMType(const std::string& str)
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

    ValueRegType getValueRegType(const ValueIndex& value)
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
            case ObjectRef:
                return ValueRegType::mem;
        }
        assert(false);
    }

    OperationType getOperationType(const ValueIndex& a, const ValueIndex& b)
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

        ScriptFunction* currentFunction = nullptr;

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

        void verifyValue(ValueIndex value, Compiler& cc)
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
                case ValueType::ObjectRef:
                    registers.push_back(cc.newIntPtr());
                    break;
                default:
                    throw std::runtime_error("Unimplemented type");
            }
        }

        template<class RT>
        RT getReg(ValueIndex value)
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

    void* scriptAlloc(uint16_t size)
    {
        return new uint8_t[size];
    }

    void scriptDealoc(void* data)
    {
        delete[] data;
    }

    Script* ScriptRuntime::assembleScript(IRScript* irScript)
    {
        assert(irScript);
        auto script = std::make_unique<Script>();
        std::vector<Library*> linkedLibraries;
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
                auto type = strToASMType(arg);
                sigBuilder.addArg(type);
                argTypes.push_back(type);
            }
            auto retType = strToASMType(func.returnType);
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
                        if (func.returnType != "void")
                            throw std::runtime_error("cannot return nothing from non-void functions");
                        cc.ret();
                        break;
                    case RETV:
                    {
                        auto valIndex = ctx.readCode<ValueIndex>();
                        assert(valIndex.storageType == ValueStorageType_Reg || valIndex.storageType == ValueStorageType_Ptr);
                        printf("RETV r%hu\n", valIndex.index);
                        auto& ret = ctx.registers[valIndex.index];
                        cc.ret(ret);

                        break;
                    }
                    case ALLOC:
                    {
                        auto valIndex = ctx.readCode<ValueIndex>();
                        auto structSize = ctx.readCode<uint32_t>();
                        asmjit::InvokeNode* in;
                        cc.invoke(&in, &scriptAlloc, asmjit::FuncSignatureT<void*, uint32_t>());

                        ctx.verifyValue(valIndex, cc);
                        in->setRet(0, ctx.getReg<Gp>(valIndex));
                        in->setArg(0, asmjit::Imm(structSize));
                        break;
                    }
                    case FREE:
                    {
                        auto valIndex = ctx.readCode<ValueIndex>();
                        asmjit::InvokeNode* in;
                        cc.invoke(&in, &scriptDealoc, asmjit::FuncSignatureT<void, void*>());

                        ctx.verifyValue(valIndex, cc);
                        in->setArg(0, ctx.getReg<Gp>(valIndex));
                        break;
                    }
                    case LOADC:
                    {
                        ValueIndex constant = ctx.readCode<ValueIndex>();
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
                        auto a = ctx.readCode<ValueIndex>();
                        auto b = ctx.readCode<ValueIndex>();
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
                        auto a = ctx.readCode<ValueIndex>();
                        printf("TEST\n");
                        switch (getValueRegType(a))
                        {
                            case ValueRegType::gp:
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
                        auto fIndex = ctx.readCode<uint32_t>();

                        auto& function = irScript->localFunctions[fIndex];
                        assert(fIndex < irScript->localFunctions.size());
                        asmjit::FuncSignatureBuilder sb;
                        sb.setCallConvId(asmjit::CallConvId::kCDecl);

                        sb.setRet(strToASMType(function.returnType));
                        for(auto& arg : function.arguments)
                            sb.addArg(strToASMType(arg));

                        asmjit::InvokeNode* in;
                        assert(fIndex <= script->functions.size());
                        if(fIndex < script->functions.size())
                            cc.invoke(&in, script->functions[fIndex], sb);
                        else
                            cc.invoke(&in, f->label(), sb);

                        if(function.returnType != "void")
                        {
                            auto retVal = ctx.readCode<ValueIndex>();
                            ctx.verifyValue(retVal, cc);
                            in->setRet(0, ctx.getReg<Reg>(retVal));
                        }
                        for(uint32_t i = 0; i < function.arguments.size(); ++i)
                        {
                            auto argVal = ctx.readCode<ValueIndex>();
                            in->setArg(i, ctx.getReg<Reg>(argVal));
                        }
                        break;
                    }
                    case EXCALL:
                    {
                        auto libIndex = ctx.readCode<uint32_t>();
                        assert(libIndex < linkedLibraries.size());
                        auto& library = *linkedLibraries[libIndex];

                        std::string funcDecl = ctx.readString();
                        auto argFlags = ctx.readCode<uint8_t>();
                        bool hasRet = argFlags & (1 << 7);
                        uint8_t argCount = argFlags & ~(1 << 7);

                        std::vector<ValueIndex> values;
                        values.reserve(argCount + (uint8_t)hasRet);
                        if(hasRet)
                            values.push_back(ctx.readCode<ValueIndex>());
                        for(uint8_t i = 0; i < argCount; ++i)
                            values.push_back(ctx.readCode<ValueIndex>());

                        auto* function = library.getFunction(funcDecl);
                        assert(function);

                        asmjit::FuncSignatureBuilder sb;
                        sb.setCallConvId(asmjit::CallConvId::kCDecl);

                        if(hasRet)
                            sb.setRet(valueToASMType(values[0]));
                        else
                            sb.setRet(asmjit::TypeId::kVoid);
                        for(uint8_t arg = hasRet; arg < values.size(); ++arg)
                            sb.addArg(valueToASMType(values[arg]));

                        asmjit::InvokeNode* in;
                        cc.invoke(&in, function, sb);

                        if(hasRet)
                        {
                            ctx.verifyValue(values[0], cc);
                            in->setRet(0, ctx.getReg<Reg>(values[0]));
                        }
                        for(uint8_t arg = hasRet; arg < values.size(); ++arg)
                            in->setArg(arg, ctx.getReg<Reg>(values[arg]));
                        break;
                    }
                    case MOV:
                    {
                        auto dest = ctx.readCode<ValueIndex>();
                        auto src = ctx.readCode<ValueIndex>();
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
                                printf("gp%hu mem%hu\n", dest.index, src.index);
                                auto srcMem = ctx.getReg<Mem>(src);
                                auto destReg = ctx.getReg<Gp>(dest);
                                cc.mov(destReg, srcMem);
                            }
                                break;
                            case mem_gp:
                            {
                                printf("mem%hu gp%hu\n", dest.index, src.index);
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
                                printf("xmm%hu mem%hu\n", dest.index, src.index);
                                auto destReg = ctx.getReg<Xmm>(dest);
                                auto srcMem = ctx.getReg<Mem>(src);
                                cc.movss(destReg, srcMem);
                            }
                                break;
                            case mem_xmm:
                            {
                                printf("mem%hu xmm%hu\n", dest.index, src.index);
                                auto destMem = ctx.getReg<Mem>(dest);
                                auto srcReg = ctx.getReg<Xmm>(src);
                                cc.movss(destMem, srcReg);
                                break;
                            }
                            case mem_mem:
                            {
                                auto destMem = ctx.getReg<Mem>(dest);
                                auto srcMem = ctx.getReg<Mem>(src);
                                Gp tempReg;
                                switch(srcMem.size())
                                {
                                    case 1:
                                        tempReg = cc.newGpb();
                                        break;
                                    case 4:
                                        tempReg = cc.newGpd();
                                        break;
                                    case 8:
                                        tempReg = cc.newGpq();
                                        break;
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
                        auto dest = ctx.readCode<ValueIndex>();
                        ctx.verifyValue(dest, cc);

                        printf("MOVI ");
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
                            case ObjectRef:
                                cc.mov(ctx.getReg<Gp>(dest), asmjit::imm(ctx.readCode<int32_t>()));
                                break;
                            default:
                                assert(false);
                        }
                        break;
                    }
                    case SETE:
                    {
                        auto regIndex = ctx.readCode<ValueIndex>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        ctx.verifyValue(regIndex, cc);
                        printf("SETE %hu", regIndex.index);
                        cc.sete(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETNE:
                    {
                        auto regIndex = ctx.readCode<ValueIndex>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        ctx.verifyValue(regIndex, cc);
                        printf("SETNE %hu", regIndex.index);
                        cc.sete(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETA:
                    {
                        auto regIndex = ctx.readCode<ValueIndex>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        ctx.verifyValue(regIndex, cc);
                        printf("SETA %hu", regIndex.index);
                        cc.seta(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETG:
                    {
                        auto regIndex = ctx.readCode<ValueIndex>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        ctx.verifyValue(regIndex, cc);
                        printf("SETG %hu", regIndex.index);
                        cc.setg(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETAE:
                    {
                        auto regIndex = ctx.readCode<ValueIndex>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        ctx.verifyValue(regIndex, cc);
                        printf("SETAE %hu", regIndex.index);
                        cc.setae(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case SETGE:
                    {
                        auto regIndex = ctx.readCode<ValueIndex>();
                        assert(regIndex.storageType == ValueStorageType_Reg);

                        ctx.verifyValue(regIndex, cc);
                        printf("SETGE %hu", regIndex.index);
                        cc.setge(ctx.getReg<Gp>(regIndex));
                        break;
                    }
                    case ADD:
                    {
                        auto a = ctx.readCode<ValueIndex>();
                        auto b = ctx.readCode<ValueIndex>();
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
                    case SUB:
                    {
                        auto a = ctx.readCode<ValueIndex>();
                        auto b = ctx.readCode<ValueIndex>();
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
                        auto a = ctx.readCode<ValueIndex>();
                        auto b = ctx.readCode<ValueIndex>();
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
                        auto a = ctx.readCode<ValueIndex>();
                        auto b = ctx.readCode<ValueIndex>();
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
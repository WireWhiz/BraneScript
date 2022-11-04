//
// Created by wirewhiz on 15/10/22.
//

#include "scriptRuntime.h"
#include "script.h"
#include "irScript.h"
#include "valueIndex.h"
#include "asmjit/core/globals.h"

#include "asmjit/asmjit.h"
#include <cstdio>
#include <stdexcept>
#include <cassert>

using namespace asmjit::x86;

class JitErrorHandler : public asmjit::ErrorHandler {
public:
    void handleError(asmjit::Error err, const char* message, asmjit::BaseEmitter* origin) override {
        printf("AsmJit error: %s\n", message);
        fflush(stdout);
        throw std::runtime_error("JIT error assembling script: " + std::string(message));
    }
};

asmjit::TypeId strToType(const std::string& str)
{
    if(str == "void") return asmjit::TypeId::kVoid;
    if(str == "bool") return asmjit::TypeId::kInt8;
    if(str == "int") return asmjit::TypeId::kInt32;
    if(str == "float") return asmjit::TypeId::kFloat32;
    if(str == "uint") return asmjit::TypeId::kUInt32;
    return asmjit::TypeId::kVoid;
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
    mem_xmm
};

ValueRegType getValueRegType(const ValueIndex& value)
{
    if(value.storageType == ValueStorageType::ValueStorageType_Mem)
        return ValueRegType::mem;
    switch(value.valueType)
    {
        case Bool:
        case Int32:
        case Int64:
        case Ptr:
            return ValueRegType::gp;
        case Float32:
        case Float64:
            return ValueRegType::xmm;
    }
}

OperationType getOperationType(const ValueIndex& a, const ValueIndex& b)
{
    const OperationType gpMap[] = {gp_gp, gp_xmm, gp_mem};
    const OperationType xmmMap[] = {xmm_gp, xmm_xmm, xmm_mem};
    const OperationType memMap[] = {mem_gp, mem_xmm};
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

    ScriptFunction* currentFunction = nullptr;

    std::vector<asmjit::x86::Reg> registers;
    std::vector<asmjit::x86::Mem> constants;
    std::vector<asmjit::Label> labels;

    template<typename T>
    T readCode()
    {
        return currentFunction->readCode<T>(iptr);
    }

    bool endOfCode() const
    {
        return iptr >= currentFunction->code.size();
    }

    void verifyValue(ValueIndex value, Compiler& cc)
    {
        if(value.index < registers.size())
            return;
        if(value.index != registers.size())
            throw std::runtime_error("Can only create next register index in sequence");
        switch(value.valueType)
        {
            case ValueType::Bool:
                registers.push_back(cc.newInt8());
                break;
            case ValueType::Int32:
                registers.push_back(cc.newInt32());
                break;
            case ValueType::Float32:
                registers.push_back(cc.newXmmSs());
                break;
            default:
                throw std::runtime_error("Unimplemented type");
        }
    }

    template<class RT>
    RT& getReg(ValueIndex value)
    {
        assert(value.index < registers.size());
        return registers[value.index].as<RT>();
    }

    asmjit::Label getLabel(uint32_t index, Compiler& cc)
    {
        while(index >= labels.size())
            labels.push_back(cc.newLabel());
        return labels[index];
    }
};

Script* ScriptRuntime::assembleScript(IRScript* irScript)
{
    auto* script = new Script();
    JitErrorHandler errorHandler;;
    for(auto& func : irScript->localFunctions)
    {
        AssemblyCtx ctx;
        asmjit::CodeHolder ch;
        ctx.currentFunction = &func;

        ch.init(_runtime.environment());
        ch.setErrorHandler(&errorHandler);
        Compiler cc(&ch);
        cc.addDiagnosticOptions(asmjit::DiagnosticOptions::kValidateAssembler | asmjit::DiagnosticOptions::kRADebugAll);
        cc.addEncodingOptions(asmjit::EncodingOptions::kOptimizedAlign);

        printf("Assembling function: %s\n", ctx.currentFunction->name.c_str());

        asmjit::FuncSignatureBuilder sigBuilder;
        std::vector<asmjit::TypeId> argTypes;
        sigBuilder.setCallConvId(asmjit::CallConvId::kCDecl);
        for(auto& arg : func.arguments)
        {
            auto type = strToType(arg);
            sigBuilder.addArg(type);
            argTypes.push_back(type);
        }
        auto retType = strToType(func.returnType);
        sigBuilder.setRet(retType);
        auto* f = cc.addFunc(sigBuilder);

        for (size_t i = 0; i < func.arguments.size(); ++i)
        {
            switch(argTypes[i])
            {
                case asmjit::TypeId::kInt32:
                    ctx.registers.push_back(cc.newInt32());
                    break;
                case asmjit::TypeId::kFloat32:
                    ctx.registers.push_back(cc.newXmmSs());
                    break;
                default:
                    assert(false);
            }
            f->setArg(i, ctx.registers[i]);
        }

        auto& code = func.code;

        while(!ctx.endOfCode())
        {
            auto op = ctx.readCode<ScriptFunction::Operand>();
            switch(op)
            {
                case ScriptFunction::RET:
                    printf("RET\n");
                    if(func.returnType != "void")
                        throw std::runtime_error("cannot return nothing from non-void functions");
                    cc.ret();
                    break;
                case ScriptFunction::RETV:
                {
                    auto valIndex = ctx.readCode<ValueIndex>();
                    assert(valIndex.storageType == ValueStorageType_Reg);
                    printf("RETV r%hu\n", valIndex.index);
                    auto& ret = ctx.registers[valIndex.index];
                    cc.ret(ret);
                    break;
                }
                case ScriptFunction::LOADC:
                {
                    ValueIndex constant = ctx.readCode<ValueIndex>();
                    printf("LOADC mem%hu ", constant.index);
                    assert(ctx.constants.size() == constant.index);
                    switch(constant.valueType)
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
                case ScriptFunction::MARK:
                {
                    auto markIndex = ctx.readCode<uint32_t>();
                    printf("MARK mark%u\n", markIndex);
                    cc.bind(ctx.getLabel(markIndex, cc));
                    break;
                }
                case ScriptFunction::CMP:
                {
                    auto a = ctx.readCode<ValueIndex>();
                    auto b = ctx.readCode<ValueIndex>();
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
                case ScriptFunction::TEST:
                {
                    auto a = ctx.readCode<ValueIndex>();
                    printf("TEST\n");
                    switch(getValueRegType(a))
                    {
                        case ValueRegType::gp:
                            cc.test(ctx.getReg<Gp>(a), ctx.getReg<Gp>(a));
                            break;
                        default:
                            assert(false);
                    }
                    break;
                }
                case ScriptFunction::JMP:
                {
                    auto markIndex = ctx.readCode<uint32_t>();
                    printf("JMP mark%u\n", markIndex);
                    cc.jmp(ctx.getLabel(markIndex, cc));
                    break;
                }
                case ScriptFunction::JE:
                {
                    auto markIndex = ctx.readCode<uint32_t>();
                    printf("JE mark%u\n", markIndex);
                    cc.je(ctx.getLabel(markIndex, cc));
                    break;
                }
                case ScriptFunction::JNE:
                {
                    auto markIndex = ctx.readCode<uint32_t>();
                    printf("JNE mark%u\n", markIndex);
                    cc.jne(ctx.getLabel(markIndex, cc));
                    break;
                }
                case ScriptFunction::JA:
                {
                    auto markIndex = ctx.readCode<uint32_t>();
                    printf("JA mark%u\n", markIndex);
                    cc.ja(ctx.getLabel(markIndex, cc));
                    break;
                }
                case ScriptFunction::JB:
                {
                    auto markIndex = ctx.readCode<uint32_t>();
                    printf("JB mark%u\n", markIndex);
                    cc.jb(ctx.getLabel(markIndex, cc));
                    break;
                }
                case ScriptFunction::JG:
                {
                    auto markIndex = ctx.readCode<uint32_t>();
                    printf("JG mark%u\n", markIndex);
                    cc.jg(ctx.getLabel(markIndex, cc));
                    break;
                }
                case ScriptFunction::JL:
                {
                    auto markIndex = ctx.readCode<uint32_t>();
                    printf("JL mark%u\n", markIndex);
                    cc.jl(ctx.getLabel(markIndex, cc));
                    break;
                }
                case ScriptFunction::JAE:
                {
                    auto markIndex = ctx.readCode<uint32_t>();
                    printf("JAE mark%u\n", markIndex);
                    cc.jae(ctx.getLabel(markIndex, cc));
                    break;
                }
                case ScriptFunction::JBE:
                {
                    auto markIndex = ctx.readCode<uint32_t>();
                    printf("JBE mark%u\n", markIndex);
                    cc.jbe(ctx.getLabel(markIndex, cc));
                    break;
                }
                case ScriptFunction::JGE:
                {
                    auto markIndex = ctx.readCode<uint32_t>();
                    printf("JGE mark%u\n", markIndex);
                    cc.jge(ctx.getLabel(markIndex, cc));
                    break;
                }
                case ScriptFunction::JLE:
                {
                    auto markIndex = ctx.readCode<uint32_t>();
                    printf("JLE mark%u\n", markIndex);
                    cc.jle(ctx.getLabel(markIndex, cc));
                    break;
                }
                case ScriptFunction::MOV:
                {
                    auto dest = ctx.readCode<ValueIndex>();
                    auto src = ctx.readCode<ValueIndex>();
                    assert(dest.storageType == ValueStorageType_Reg);

                    ctx.verifyValue(dest, cc);
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
                            printf("gp%hu mem%hu\n", dest.index, src.index);
                            auto srcMem = ctx.constants[src.index];
                            auto destReg = ctx.getReg<Gp>(dest);
                            cc.mov(destReg, srcMem);
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
                            auto srcMem = ctx.constants[src.index];
                            cc.movss(destReg, srcMem);
                        }
                            break;
                        default:
                            throw std::runtime_error("Invalid mov operands");
                    }
                    break;
                }
                case ScriptFunction::SETE:
                {
                    auto regIndex = ctx.readCode<ValueIndex>();
                    assert(regIndex.storageType == ValueStorageType_Reg);

                    ctx.verifyValue(regIndex, cc);
                    printf("SETE %hu", regIndex.index);
                    cc.sete(ctx.getReg<Gp>(regIndex));
                    break;
                }
                case ScriptFunction::SETNE:
                {
                    auto regIndex = ctx.readCode<ValueIndex>();
                    assert(regIndex.storageType == ValueStorageType_Reg);

                    ctx.verifyValue(regIndex, cc);
                    printf("SETNE %hu", regIndex.index);
                    cc.sete(ctx.getReg<Gp>(regIndex));
                    break;
                }
                case ScriptFunction::SETA:
                {
                    auto regIndex = ctx.readCode<ValueIndex>();
                    assert(regIndex.storageType == ValueStorageType_Reg);

                    ctx.verifyValue(regIndex, cc);
                    printf("SETA %hu", regIndex.index);
                    cc.seta(ctx.getReg<Gp>(regIndex));
                    break;
                }
                case ScriptFunction::SETG:
                {
                    auto regIndex = ctx.readCode<ValueIndex>();
                    assert(regIndex.storageType == ValueStorageType_Reg);

                    ctx.verifyValue(regIndex, cc);
                    printf("SETG %hu", regIndex.index);
                    cc.setg(ctx.getReg<Gp>(regIndex));
                    break;
                }
                case ScriptFunction::SETAE:
                {
                    auto regIndex = ctx.readCode<ValueIndex>();
                    assert(regIndex.storageType == ValueStorageType_Reg);

                    ctx.verifyValue(regIndex, cc);
                    printf("SETAE %hu", regIndex.index);
                    cc.setae(ctx.getReg<Gp>(regIndex));
                    break;
                }
                case ScriptFunction::SETGE:
                {
                    auto regIndex = ctx.readCode<ValueIndex>();
                    assert(regIndex.storageType == ValueStorageType_Reg);

                    ctx.verifyValue(regIndex, cc);
                    printf("SETGE %hu", regIndex.index);
                    cc.setge(ctx.getReg<Gp>(regIndex));
                    break;
                }
                case ScriptFunction::ADD:
                {
                    auto a = ctx.readCode<ValueIndex>();
                    auto b = ctx.readCode<ValueIndex>();
                    printf("ADD ");
                    switch(getOperationType(a, b))
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
                            auto srcMem = ctx.constants[b.index];
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
                            auto srcReg = ctx.constants[b.index];
                            cc.addss(destReg, srcReg);
                        }
                            break;
                        default:
                            throw std::runtime_error("Invalid add operands");
                    }
                    break;
                }
                case ScriptFunction::SUB:
                {
                    auto a = ctx.readCode<ValueIndex>();
                    auto b = ctx.readCode<ValueIndex>();
                    printf("SUB ");
                    switch(getOperationType(a, b))
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
                            auto srcMem = ctx.constants[b.index];
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
                            auto srcMem = ctx.constants[b.index];
                            cc.subss(destReg, srcMem);
                        }
                            break;
                        default:
                            throw std::runtime_error("Invalid sub operands");
                    }
                    break;
                }
                case ScriptFunction::MUL:
                {
                    auto a = ctx.readCode<ValueIndex>();
                    auto b = ctx.readCode<ValueIndex>();
                    printf("MUL ");
                    switch(getOperationType(a, b))
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
                            auto srcMem = ctx.constants[b.index];
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
                            auto srcMem = ctx.constants[b.index];
                            cc.mulss(destReg, srcMem);
                        }
                            break;
                        default:
                            throw std::runtime_error("Invalid mul operands");
                    }
                    break;
                }
                case ScriptFunction::DIV:
                {
                    auto a = ctx.readCode<ValueIndex>();
                    auto b = ctx.readCode<ValueIndex>();
                    printf("DIV ");
                    switch(getOperationType(a, b))
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
                            auto srcMem = ctx.constants[b.index];
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
                            auto srcMem = ctx.constants[b.index];
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


    return script;
}

//
// Created by wirewhiz on 15/10/22.
//

#include "scriptRuntime.h"
#include "script.h"
#include "irScript.h"
#include "valueIndex.h"
#include "asmjit/asmjit.h"
#include <cstdio>
#include <stdexcept>
#include <cassert>

using namespace asmjit::x86;

void chkErr(asmjit::Error err)
{
    if(err)
        throw std::runtime_error("Compile error " + (std::string)asmjit::DebugUtils::errorAsString(err));
}

class JitErrorHandler : public asmjit::ErrorHandler {
public:
    void handleError(asmjit::Error err, const char* message, asmjit::BaseEmitter* origin) override {
        printf("AsmJit error: %s\n", message);
    }
};

asmjit::TypeId strToType(const std::string& str)
{
    if(str == "void") return asmjit::TypeId::kVoid;
    if(str == "int") return asmjit::TypeId::kInt32;
    if(str == "float") return asmjit::TypeId::kFloat32;
    if(str == "uint") return asmjit::TypeId::kUInt32;
    return asmjit::TypeId::kVoid;
}

asmjit::TypeId typeToAsmType(ValueType type)
{
    switch(type)
    {
        case Int32:
            return asmjit::TypeId::kInt32;
        case Int64:
            return asmjit::TypeId::kInt32;
        case Ptr:
            return asmjit::TypeId::kIntPtr;
        case Float32:
            return asmjit::TypeId::kFloat32;
        case Float64:
            return asmjit::TypeId::kFloat64;
    }
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
    if(value.flags & ValueIndexFlags_Mem)
        return ValueRegType::mem;
    switch(value.valueType)
    {
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

template<class RT>
RT& getReg(uint16_t index, asmjit::TypeId type, std::vector<Reg>& registers, Compiler& cc)
{
    if(registers.size() == index)
        registers.push_back(cc.newReg(type));
    return registers[index].as<RT>();
}

Script* ScriptRuntime::assembleScript(IRScript* irScript)
{
    auto* script = new Script();
    JitErrorHandler errorHandler;
    std::unordered_map<uint16_t, asmjit::x86::Mem> constants;
    for(auto& func : irScript->localFunctions)
    {
        asmjit::CodeHolder ch;

        ch.init(_runtime.environment());
        ch.setErrorHandler(&errorHandler);
        Compiler cc(&ch);
        cc.addDiagnosticOptions(asmjit::DiagnosticOptions::kValidateAssembler);

        std::vector<asmjit::Label> labels;
        std::vector<asmjit::x86::Reg> registers;

        asmjit::FuncSignatureBuilder sigBuilder;
        std::vector<asmjit::TypeId> argTypes;
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
            registers.push_back(cc.newReg(argTypes[i]));
            f->setArg(i, registers[i]);
        }

        size_t iptr = 0;
        auto& code = func.code;

        while(iptr < code.size())
        {
            switch(func.readCode<ScriptFunction::Operand>(iptr))
            {
                case ScriptFunction::RET:
                    printf("RET\n");
                    if(func.returnType != "void")
                        throw std::runtime_error("cannot return nothing from non-void functions");
                    chkErr(cc.ret());
                    break;
                case ScriptFunction::RETV:
                {
                    auto valIndex = func.readCode<ValueIndex>(iptr);
                    assert(valIndex.flags & ValueIndexFlags_Reg);
                    printf("RETV r%hu\n", valIndex.index);
                    auto& ret = registers[valIndex.index];
                    chkErr(cc.ret(ret));
                    break;
                }
                case ScriptFunction::LOADC:
                {
                    ValueIndex constant = func.readCode<ValueIndex>(iptr);
                    printf("LOADC m%hu ", constant.index);
                    assert(!constants.count(constant.index));
                    switch(constant.valueType)
                    {
                        case Int32:
                        {
                            int32_t val = func.readCode<int32_t>(iptr);
                            printf("int %i\n", val);
                            constants[constant.index] = cc.newInt32Const(asmjit::ConstPoolScope::kLocal, val);
                        }
                            break;
                        case Float32:
                        {
                            float val = func.readCode<float>(iptr);
                            printf("float %f\n", val);
                            constants[constant.index] = cc.newFloatConst(asmjit::ConstPoolScope::kLocal, val);
                        }
                            break;
                        default:
                            assert(false);
                    }

                    break;
                }
                case ScriptFunction::MOV:
                {
                    auto dest = func.readCode<ValueIndex>(iptr);
                    auto src = func.readCode<ValueIndex>(iptr);
                    assert(dest.flags & ValueIndexFlags_Reg);
                    printf("MOV ");
                    switch(getOperationType(dest, src))
                    {
                        case gp_gp:
                        {
                            printf("r%hu r%hu\n", dest.index, src.index);
                            auto destReg = getReg<Gp>(dest.index, typeToAsmType(dest.valueType), registers, cc);
                            auto srcReg = getReg<Gp>(src.index, typeToAsmType(src.valueType), registers, cc);
                            chkErr(cc.mov(destReg, srcReg));
                        }
                        break;
                        case gp_mem:
                        {
                            printf("r%hu m%hu\n", dest.index, src.index);
                            auto destReg = getReg<Gp>(dest.index, typeToAsmType(dest.valueType), registers, cc);
                            auto srcMem = constants.at(src.index);
                            chkErr(cc.mov(destReg, srcMem));
                        }
                            break;
                        case gp_xmm:
                        {
                            printf("gp%hu xmm%hu\n", dest.index, src.index);
                            auto destReg = getReg<Gp>(dest.index, typeToAsmType(dest.valueType), registers, cc);
                            auto srcReg = getReg<Xmm>(src.index, typeToAsmType(src.valueType), registers, cc);
                            chkErr(cc.cvttss2si(destReg, srcReg));
                        }
                            break;
                        case xmm_xmm:
                        {
                            printf("xmm%hu xmm%hu\n", dest.index, src.index);
                            auto destReg = getReg<Xmm>(dest.index, typeToAsmType(dest.valueType), registers, cc);
                            auto srcReg = getReg<Xmm>(src.index, typeToAsmType(src.valueType), registers, cc);
                            chkErr(cc.movss(destReg, srcReg));
                        }
                            break;
                        case xmm_gp:
                        {
                            printf("xmm%hu gp%hu\n", dest.index, src.index);
                            auto destReg = getReg<Xmm>(dest.index, typeToAsmType(dest.valueType), registers, cc);
                            auto srcReg = getReg<Gp>(src.index, typeToAsmType(src.valueType), registers, cc);
                            chkErr(cc.cvtsi2ss(destReg, srcReg));
                        }
                            break;
                        case xmm_mem:
                        {
                            printf("xmm%hu gp%hu\n", dest.index, src.index);
                            auto destReg = getReg<Xmm>(dest.index, typeToAsmType(dest.valueType), registers, cc);
                            auto srcMem = constants.at(src.index);
                            chkErr(cc.movss(destReg, srcMem));
                        }
                            break;
                        default:
                            throw std::runtime_error("Invalid mov operands");
                    }
                    break;
                }
                case ScriptFunction::ADD:
                {
                    auto a = func.readCode<ValueIndex>(iptr);
                    auto b = func.readCode<ValueIndex>(iptr);
                    printf("ADD ");
                    switch(getOperationType(a, b))
                    {
                        case gp_gp:
                        {
                            printf("gp%hu gp%hu\n", a.index, b.index);
                            auto destReg = getReg<Gp>(a.index, typeToAsmType(a.valueType), registers, cc);
                            auto srcReg = getReg<Gp>(b.index, typeToAsmType(b.valueType), registers, cc);
                            chkErr(cc.add(destReg, srcReg));
                        }
                            break;
                        case gp_mem:
                        {
                            printf("gp%hu m%hu\n", a.index, b.index);
                            auto destReg = getReg<Gp>(a.index, typeToAsmType(a.valueType), registers, cc);
                            auto srcMem = constants.at(b.index);
                            chkErr(cc.add(destReg, srcMem));
                        }
                            break;
                        case xmm_xmm:
                        {
                            printf("xmm%hu xmm%hu\n", a.index, b.index);
                            auto destReg = getReg<Xmm>(a.index, typeToAsmType(a.valueType), registers, cc);
                            auto srcReg = getReg<Xmm>(b.index, typeToAsmType(b.valueType), registers, cc);
                            chkErr(cc.addss(destReg, srcReg));
                        }
                            break;
                        case xmm_mem:
                        {
                            printf("xmm%hu m%hu\n", a.index, b.index);
                            auto destReg = getReg<Xmm>(a.index, typeToAsmType(a.valueType), registers, cc);
                            auto srcReg = constants.at(b.index);
                            chkErr(cc.addss(destReg, srcReg));
                        }
                            break;
                        default:
                            throw std::runtime_error("Invalid add operands");
                    }
                    break;
                }
                case ScriptFunction::SUB:
                {
                    auto a = func.readCode<ValueIndex>(iptr);
                    auto b = func.readCode<ValueIndex>(iptr);
                    printf("SUB ");
                    switch(getOperationType(a, b))
                    {
                        case gp_gp:
                        {
                            printf("r%hu r%hu\n", a.index, b.index);
                            auto destReg = getReg<Gp>(a.index, typeToAsmType(a.valueType), registers, cc);
                            auto srcReg = getReg<Gp>(b.index, typeToAsmType(b.valueType), registers, cc);
                            chkErr(cc.sub(destReg, srcReg));
                        }
                            break;
                        case gp_mem:
                        {
                            printf("r%hu m%hu\n", a.index, b.index);
                            auto destReg = getReg<Gp>(a.index, typeToAsmType(a.valueType), registers, cc);
                            auto srcMem = constants.at(b.index);
                            chkErr(cc.sub(destReg, srcMem));
                        }
                            break;
                        default:
                            throw std::runtime_error("Invalid sub operands");
                    }
                    break;
                }
                case ScriptFunction::MUL:
                {
                    auto a = func.readCode<ValueIndex>(iptr);
                    auto b = func.readCode<ValueIndex>(iptr);
                    printf("MUL ");
                    switch(getOperationType(a, b))
                    {
                        case gp_gp:
                        {
                            printf("r%hu r%hu\n", a.index, b.index);
                            auto destReg = getReg<Gp>(a.index, typeToAsmType(a.valueType), registers, cc);
                            auto srcReg = getReg<Gp>(b.index, typeToAsmType(b.valueType), registers, cc);
                            chkErr(cc.imul(destReg, srcReg));
                        }
                            break;
                        case gp_mem:
                        {
                            printf("r%hu m%hu\n", a.index, b.index);
                            auto destReg = getReg<Gp>(a.index, typeToAsmType(a.valueType), registers, cc);
                            auto srcMem = constants.at(b.index);
                            chkErr(cc.imul(destReg, srcMem));
                        }
                            break;
                        default:
                            throw std::runtime_error("Invalid mul operands");
                    }
                    break;
                }
                case ScriptFunction::DIV:
                {
                    auto a = func.readCode<ValueIndex>(iptr);
                    auto b = func.readCode<ValueIndex>(iptr);
                    printf("DIV ");
                    switch(getOperationType(a, b))
                    {
                        case gp_gp:
                        {
                            printf("r%hu r%hu\n", a.index, b.index);
                            auto destReg = getReg<Gp>(a.index, typeToAsmType(a.valueType), registers, cc);
                            auto srcReg = getReg<Gp>(b.index, typeToAsmType(b.valueType), registers, cc);
                            chkErr(cc.idiv(cc.newInt32(),destReg, srcReg));
                        }
                            break;
                        case gp_mem:
                        {
                            printf("r%hu m%hu\n", a.index, b.index);
                            auto destReg = getReg<Gp>(a.index, typeToAsmType(a.valueType), registers, cc);
                            auto srcMem = constants.at(b.index);
                            chkErr(cc.idiv(cc.newInt32(),destReg, srcMem));
                        }
                            break;
                        default:
                            throw std::runtime_error("Invalid div operands");
                    }
                    break;
                }
                default:
                    throw std::runtime_error("unknown op: " + std::to_string(code[iptr]));
            }
        }
        chkErr(cc.endFunc());
        chkErr(cc.finalize());
        void* fPtr = nullptr;
        chkErr(_runtime.add(&fPtr, &ch));

        script->functionNames.insert({func.name, script->functions.size()});
        script->functions.push_back(fPtr);
    }


    return script;
}

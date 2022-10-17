//
// Created by wirewhiz on 15/10/22.
//

#include "scriptRuntime.h"
#include "script.h"
#include "irScript.h"
#include "asmjit/asmjit.h"
#include <cstdio>
#include <stdexcept>

using namespace asmjit::x86;

void chkErr(asmjit::Error err)
{
    if(err)
        throw std::runtime_error("Compile error " + (std::string)asmjit::DebugUtils::errorAsString(err));
}

asmjit::TypeId strToType(const std::string& str)
{
    if(str == "void") return asmjit::TypeId::kVoid;
    if(str == "int") return asmjit::TypeId::kInt32;
    if(str == "float") return asmjit::TypeId::kMmx32;
    if(str == "uint") return asmjit::TypeId::kUInt32;
    return asmjit::TypeId::kVoid;
}

template<class RT>
RT& getReg(uint32_t index, asmjit::TypeId type, std::vector<Reg>& registers, Compiler& cc)
{
    if(registers.size() == index)
        registers.push_back(cc.newReg(type));
    return registers[index].as<RT>();
}

class JitErrorHandler : public asmjit::ErrorHandler {
public:
    void handleError(asmjit::Error err, const char* message, asmjit::BaseEmitter* origin) override {
        printf("AsmJit error: %s\n", message);
    }
};

Script* ScriptRuntime::assembleScript(IRScript* irScript)
{
    auto* script = new Script();
    JitErrorHandler errorHandler;

    for(auto& func : irScript->localFunctions)
    {
        asmjit::CodeHolder ch;

        ch.init(_runtime.environment());
        ch.setErrorHandler(&errorHandler);
        Compiler cc(&ch);

        std::vector<asmjit::Label> labels;
        std::vector<asmjit::x86::Reg> registers;

        asmjit::FuncSignatureBuilder sigBuilder;
        for(auto& arg : func.arguments)
        {
            auto type = strToType(arg);
            sigBuilder.addArg(type);
            registers.push_back(cc.newReg(type));
        }
        auto retType = strToType(func.returnType);
        sigBuilder.setRet(retType);
        auto* f = cc.addFunc(sigBuilder);

        for (size_t i = 0; i < func.arguments.size(); ++i)
            f->setArg(i, registers[i]);

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
                    auto valIndex = func.readCode<uint32_t>(iptr);
                    printf("RETV %u\n", valIndex);
                    chkErr(cc.ret(getReg<Reg>(valIndex, asmjit::TypeId::kInt32, registers, cc)));
                    break;
                }
                case ScriptFunction::MOV:
                {
                    auto i1 = func.readCode<uint32_t>(iptr);
                    auto i2 = func.readCode<uint32_t>(iptr);
                    printf("MOV %u %u\n", i1, i2);
                    auto des = getReg<Gp>(i1, asmjit::TypeId::kInt32, registers, cc);
                    auto src = getReg<Gp>(i2, asmjit::TypeId::kInt32, registers, cc);
                    chkErr(cc.mov(des, src));
                    break;
                }
                case ScriptFunction::MOVC:
                {
                    auto i1 = func.readCode<uint32_t>(iptr);
                    auto i2 = func.readCode<uint32_t>(iptr);
                    printf("MOVC %u %u\n", i1, i2);
                    auto des = getReg<Gp>(i1, asmjit::TypeId::kInt32, registers, cc);
                    chkErr(cc.mov(des, cc.newInt32Const(asmjit::ConstPoolScope::kLocal, func.constants.ints[i2])));
                    break;
                }
                case ScriptFunction::ADD:
                {
                    auto i1 = func.readCode<uint32_t>(iptr);
                    auto i2 = func.readCode<uint32_t>(iptr);
                    printf("ADD %u %u\n", i1, i2);
                    auto a = getReg<Gp>(i1, asmjit::TypeId::kInt32, registers, cc);
                    auto b = getReg<Gp>(i2, asmjit::TypeId::kInt32, registers, cc);
                    chkErr(cc.add(a, b));
                    break;
                }
                case ScriptFunction::SUB:
                {
                    auto i1 = func.readCode<uint32_t>(iptr);
                    auto i2 = func.readCode<uint32_t>(iptr);
                    printf("SUB %u %u\n", i1, i2);
                    auto a = getReg<Gp>(i1, asmjit::TypeId::kInt32, registers, cc);;
                    auto b = getReg<Gp>(i2, asmjit::TypeId::kInt32, registers, cc);;
                    chkErr(cc.sub(a, b));
                    break;
                }
                case ScriptFunction::MUL:
                {
                    auto i1 = func.readCode<uint32_t>(iptr);
                    auto i2 = func.readCode<uint32_t>(iptr);
                    auto a = getReg<Gp>(i1, asmjit::TypeId::kInt32, registers, cc);
                    auto b = getReg<Gp>(i2, asmjit::TypeId::kInt32, registers, cc);
                    printf("MUL %u %u\n", i1, i2);
                    chkErr(cc.imul(a, b));
                    break;
                }
                case ScriptFunction::DIV:
                {
                    auto i1 = func.readCode<uint32_t>(iptr);
                    auto i2 = func.readCode<uint32_t>(iptr);
                    printf("DIV %u %u\n", i1, i2);
                    auto a = getReg<Gp>(i1, asmjit::TypeId::kInt32, registers, cc);
                    auto b = getReg<Gp>(i2, asmjit::TypeId::kInt32, registers, cc);
                    chkErr(cc.idiv(a, b));
                    break;
                }
                default:
                    throw std::runtime_error("unknown op: " + std::to_string(code[iptr]));
            }
        }

        if(!f->hasRet())
            chkErr(cc.ret());
        chkErr(cc.endFunc());

        chkErr(cc.finalize());
        void* fPtr = nullptr;
        chkErr(_runtime.add(&fPtr, &ch));

        script->functionNames.insert({func.name, script->functions.size()});
        script->functions.push_back(fPtr);
    }


    return script;
}

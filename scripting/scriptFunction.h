//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_SCRIPTFUNCTION_H
#define BRANESCRIPT_SCRIPTFUNCTION_H

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include "baseTypes.h"

class ScriptFunction
{
public:
    enum Operand : uint8_t
    {
        RET=0,  //Exit function
        RETV=1, // (uin32_t register) Return int32 value
        LOADC=2,  // (uint32_t register, uint32_t constantIndex) load constant defined by byte array into the register

        MOV=3,   // (uin32_t register,  uin32_t register) move gp register to another register.
        ADD=4,   // (uin32_t register,  uin32_t register) add registers.
        SUB=5,   // (uin32_t register,  uin32_t register) subtract registers.
        INC=6,   // (uin32_t register)  increment register.
        DEC=7,   // (uint32_t register) decrement register.
        MUL=8,   // (uin32_t register,  uin32_t register) multiply registers.
        DIV=9,   // (uin32_t register,  uin32_t register) divide registers.
    };

    std::vector<uint8_t> code;
    std::vector<std::string> arguments;
    std::string returnType = "void";
    std::string name;

    void appendCode(Operand op);
    template<typename A>
    void appendCode(Operand op, A a)
    {
        size_t index = code.size();
        code.resize(code.size() + sizeof(op) + sizeof(a));
        code[index] = op;
        index += sizeof(Operand);
        *(A*)(code.data() + index) = a;
    }

    template<typename A, typename B>
    void appendCode(Operand op, A a, B b)
    {
        size_t index = code.size();
        code.resize(code.size() + sizeof(op) + sizeof(a) + sizeof(b));
        code[index] = op;
        index += sizeof(Operand);
        *(A*)(code.data() + index) = a;
        index += sizeof(A);
        *(B*)(code.data() + index) = b;
    }

    template<typename T>
    T readCode(size_t& index)
    {
        T value = *(T*)&code[index];
        index += sizeof(T);
        return value;
    }
};


#endif //BRANESCRIPT_SCRIPTFUNCTION_H

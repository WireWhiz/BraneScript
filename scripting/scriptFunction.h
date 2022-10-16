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
        RET,  //Exit function
        RETV, // (uin32_t register) Return value

        MOV,   // (uin32_t register,  uin32_t register) move register to another register.
        MOVC,  // (uint32_t register, uint32_t constantIndex) load constant defined by byte array into the register
        ADD,   // (uin32_t register,  uin32_t register) add registers.
        SUB,   // (uin32_t register,  uin32_t register) subtract registers.
        INC,   // (uin32_t register)  increment register.
        DEC,   // (uint32_t register) decrement register.
        MUL,   // (uin32_t register,  uin32_t register) multiply registers.
        DIV,   // (uin32_t register,  uin32_t register) divide registers.
    };

    struct Constants
    {
        std::vector<int> ints;
    };
    Constants constants;

    std::vector<uint8_t> code;
    std::vector<std::string> arguments;
    std::string returnType = "void";
    std::string name;

    uint32_t registerConstant(int value);

    template<typename A, typename B>
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
};


#endif //BRANESCRIPT_SCRIPTFUNCTION_H

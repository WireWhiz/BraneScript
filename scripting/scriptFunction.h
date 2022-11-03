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
#include "aotNode/aotNode.h"

class ScriptFunction
{
public:
    enum Operand : uint8_t
    {
        RET,  //Exit function
        RETV, // (uin32_t value) Return int32 value
        LOADC,  // (uint32_t value, uint32_t constantIndex) load constant defined by byte array into the value

        SETE,
        SETNE,
        SETA,
        SETG,
        SETAE,
        SETGE,

        CMP,
        TEST0,
        MARK,
        JMP,
        JE,
        JNE,
        JA,
        JB,
        JG,
        JL,
        JAE,
        JBE,
        JGE,
        JLE,

        MOV,   // (uin32_t value,  uin32_t value) move value to another value.

        ADD,   // (uin32_t value,  uin32_t value) add values.
        SUB,   // (uin32_t value,  uin32_t value) subtract values.
        INC,   // (uin32_t value)  increment value.
        DEC,   // (uint32_t value) decrement value.
        MUL,   // (uin32_t value,  uin32_t value) multiply values.
        DIV,   // (uin32_t value,  uin32_t value) divide values.
    };

    std::vector<uint8_t> code;
    std::vector<std::string> arguments;
    std::string returnType = "void";
    std::string name;

    void appendCode(Operand op);
    template<typename A>
    void appendCode(Operand op, A a)
    {
        static_assert(!std::is_same<A, AotNode>());
        size_t index = code.size();
        code.resize(code.size() + sizeof(op) + sizeof(a));
        code[index] = op;
        index += sizeof(Operand);
        *(A*)(code.data() + index) = a;
    }

    template<typename A, typename B>
    void appendCode(Operand op, A a, B b)
    {
        static_assert(!std::is_same<A, AotNode>() && !std::is_same<B, AotNode>());
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

//
// Created by eli on 11/4/2022.
//

#ifndef BRANESCRIPT_OPERANDS_H
#define BRANESCRIPT_OPERANDS_H

#include <cstdint>

namespace BraneScript
{

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
        TEST,
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
}
#endif //BRANESCRIPT_OPERANDS_H

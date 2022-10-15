//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_BYTECODE_H
#define BRANESCRIPT_BYTECODE_H

#include <cstdint>

using Codebyte = uint8_t;

namespace Bytecode
{
    enum Operand : Codebyte
    {
        RET,
        PUSH,
        POP,

        MOV,
        ADD,
        SUB,
        INC,
        DEC,

        AND,
        XOR,
        OR,
        TEST,

        CMP,

        JNE,
    };
};


#endif //BRANESCRIPT_BYTECODE_H

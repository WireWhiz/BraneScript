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
        // Waiting until we are near feature complete to manually set enum values
        RET,    //Exit function
        RETV,   // (ValueIndex value) Return int32 value
        LOADC,  // (ValueIndex value, uint32_t constantIndex) load constant defined by byte array into the value
        LINKL,  // (uint8_t nameSize, chararray) add library to function search
        LINKF,  // (uint8_t nameSize, chararray) link to external function, name in format of name(type, type, type, ...)

        SETE,  // (ValueIndex) set to 0 or 1 based on condition
        SETNE, // (ValueIndex) set to 0 or 1 based on condition
        SETA,  // (ValueIndex) set to 0 or 1 based on condition
        SETG,  // (ValueIndex) set to 0 or 1 based on condition
        SETAE, // (ValueIndex) set to 0 or 1 based on condition
        SETGE, // (ValueIndex) set to 0 or 1 based on condition

        CMP,  // Compare
        TEST, // Test if 0
        MARK, // Mark jump endpoint
        JMP,  // (uint32_t markIndex) jump to mark
        JE,   // (uint32_t markIndex) jump to mark on condition
        JNE,  // (uint32_t markIndex) jump to mark on condition
        JA,   // (uint32_t markIndex) jump to mark on condition
        JB,   // (uint32_t markIndex) jump to mark on condition
        JG,   // (uint32_t markIndex) jump to mark on condition
        JL,   // (uint32_t markIndex) jump to mark on condition
        JAE,  // (uint32_t markIndex) jump to mark on condition
        JBE,  // (uint32_t markIndex) jump to mark on condition
        JGE,  // (uint32_t markIndex) jump to mark on condition
        JLE,  // (uint32_t markIndex) jump to mark on condition

        CALL,  // (uint32_t function, ValueIndex returnValue, ValueIndex...) call to another function within the script

        MOV,   // (uin32_t value,  uin32_t value) move value to another value.

        INC,   // (ValueIndex value)  increment value.
        DEC,   // (ValueIndex value)  decrement value.
        ADD,   // (ValueIndex value, ValueIndex value) add values.
        SUB,   // (ValueIndex value, ValueIndex value) subtract values.
        MUL,   // (ValueIndex value, ValueIndex value) multiply values.
        DIV,   // (ValueIndex value, ValueIndex value) divide values.
    };
}
#endif //BRANESCRIPT_OPERANDS_H

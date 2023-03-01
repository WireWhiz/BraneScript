//
// Created by eli on 11/4/2022.
//

#ifndef BRANESCRIPT_OPERANDS_H
#define BRANESCRIPT_OPERANDS_H

#include <cstdint>

namespace BraneScript
{
    //When a signed index is present, negative values represent external indices
    enum Operand : uint8_t
    {
        // Waiting until we are near feature complete to manually set enum values
        RET,    //Exit function
        RETV,   // (Value value) Return int32 value
        INITR,  // (Value value) Initialize or reset a register to a type used by this value
        LOADC,  // (Value value, T constant) load constant defined by byte array into the value
        LOADS,  // (Value value, uint32_t index) load constant string ptr

        ALLOC,     // (Value ptr, uint16_t size) allocate local stack memory
        MALLOC,    // (Value ptr, uint16_t size) allocate local struct on the heap
        FREE,      // (Value ptr, uint16_t size) deallocate heap struct memory

        SETE,  // (Value) set to 0 or 1 based on condition
        SETNE, // (Value) set to 0 or 1 based on condition
        SETA,  // (Value) set to 0 or 1 based on condition
        SETG,  // (Value) set to 0 or 1 based on condition
        SETAE, // (Value) set to 0 or 1 based on condition
        SETGE, // (Value) set to 0 or 1 based on condition

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

        CALL,   // (int16_t function, Value returnValue, Value...) call to another function within the script

        MOV,   // (Value value, Value value) move value to another value.
        MOVI,  // (Value value, T value) move an immediate value into a register.

        ADD,   // (Value value, Value value) add values.
        ADDI,  // (Value value, T value) add immediate value to register
        SUB,   // (Value value, Value value) subtract values.
        MUL,   // (Value value, Value value) multiply values.
        DIV,   // (Value value, Value value) divide values.

        CI64I32, // (Value value, Value value) down cast 64 bit int to 32 bit int

        CU32I32, // (Value value, Value value) cast 32 bit unsigned int to 32 bit int
        CU64I64, // (Value value, Value value) cast 64 bit unsigned int to 64 bit int

        CI32I64, // (Value value, Value value) cast 32 bit int to 64 bit int
        CU32U64, // (Value value, Value value) cast 32 bit int to 64 bit int
        CF32F64, // (Value value, Value value) cast 32 bit int to 64 bit float
        CF64F32, // (Value value, Value value) cast 64 bit int to 32 bit float
        CI32F32, // (Value value, Value value) cast 32 bit int to 32 bit float
        CI32F64, // (Value value, Value value) cast 32 bit int to 64 bit float
        CF32I32, // (Value value, Value value) cast 32 bit float to 32 bit int
        CF64I32, // (Value value, Value value) cast 64 bit float to 32 bit int
    };
}
#endif //BRANESCRIPT_OPERANDS_H

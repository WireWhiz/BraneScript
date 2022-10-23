//
// Created by wirewhiz on 17/10/22.
//

#ifndef BRANESCRIPT_VALUEINDEX_H
#define BRANESCRIPT_VALUEINDEX_H

#include <cstdint>

enum ValueType : uint8_t
{
    Int32 = 0,
    Int64 = 1,
    Float32 = 2,
    Float64 = 3,
    Ptr = 4

};

const char* valueTypeName(ValueType type);

enum ValueIndexFlags : uint8_t
{
    ValueIndexFlags_Mem = 1,
    ValueIndexFlags_Reg = 1 << 1
};

struct alignas(2) ValueIndex
{
    uint16_t index;
    ValueType valueType;
    uint8_t flags;
};


#endif //BRANESCRIPT_VALUEINDEX_H

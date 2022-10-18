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

struct ValueIndex
{
    uint16_t registerIndex;
    ValueType valueType;
};


#endif //BRANESCRIPT_VALUEINDEX_H

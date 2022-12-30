//
// Created by wirewhiz on 17/10/22.
//

#ifndef BRANESCRIPT_VALUEINDEX_H
#define BRANESCRIPT_VALUEINDEX_H

#include <cstdint>
namespace BraneScript
{
    enum ValueType : uint8_t
    {
        Bool    = 1,
        UInt32  = 2,
        UInt64  = 3,
        Int32   = 4,
        Int64   = 5,
        Float32 = 6,
        Float64 = 7,
        Struct  = 8
    };

    enum ValueStorageType : uint8_t
    {
        ValueStorageType_Null = 0,
        ValueStorageType_Reg = 1,
        ValueStorageType_Const = 2,
        ValueStorageType_Ptr = 3,
        ValueStorageType_DerefPtr = 5

    };

    struct alignas(2) Value
    {
        uint16_t index;
        uint16_t offset;
        ValueType valueType;
        ValueStorageType storageType;
    };
}

#endif //BRANESCRIPT_VALUEINDEX_H

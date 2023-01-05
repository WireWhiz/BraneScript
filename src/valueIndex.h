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
        Char    = 2,
        UInt32  = 3,
        UInt64  = 4,
        Int32   = 5,
        Int64   = 6,
        Float32 = 7,
        Float64 = 8,
        Struct  = 9
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

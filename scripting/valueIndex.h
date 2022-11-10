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
        Bool = 1,
        Int32 = 2,
        Int64 = 3,
        Float32 = 4,
        Float64 = 5,
        Ptr = 6

    };

    const char* valueTypeName(ValueType type);

    enum ValueStorageType : uint8_t
    {
        ValueStorageType_Reg = 0,
        ValueStorageType_Mem = 1,
        ValueStorageType_EqualRes = 2,
        ValueStorageType_NotEqualRes = 3,
        ValueStorageType_AboveRes = 4,
        ValueStorageType_GreaterRes = 5,
        ValueStorageType_AboveEqualRes = 6,
        ValueStorageType_GreaterEqualRes = 7

    };

    struct alignas(2) ValueIndex
    {
        uint16_t index;
        ValueType valueType;
        ValueStorageType storageType;
    };
}

#endif //BRANESCRIPT_VALUEINDEX_H

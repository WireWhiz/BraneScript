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
        ObjectRef = 6
    };

    enum ValueStorageType : uint8_t
    {
        ValueStorageType_Null = 0,
        ValueStorageType_Reg = 1,
        ValueStorageType_Const = 2,
        ValueStorageType_Ptr = 3,
        ValueStorageType_DerefPtr = 4

    };

    struct alignas(2) ValueIndex
    {
        uint16_t index;
        uint16_t offset;
        ValueType valueType;
        ValueStorageType storageType;
    };
}

#endif //BRANESCRIPT_VALUEINDEX_H

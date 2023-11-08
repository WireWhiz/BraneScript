//
// Created by wirewhiz on 17/10/22.
//

#ifndef BRANESCRIPT_VALUETYPE_H
#define BRANESCRIPT_VALUETYPE_H

#include <cstdint>
namespace BraneScript
{
    enum class ValueType : uint8_t
    {
        None = 0,
        Bool    = 1,
        Char    = 2,
        Scalar_Begin   = 3,
        Int_Begin = 3,
        Unsigned_Begin = 3,
        UInt32  = 3,
        UInt64  = 4,
        Unsigned_End   = 4,
        Int32   = 5,
        Int64   = 6,
        Int_End = 6,
        Float_Begin    = 7,
        Float32 = 7,
        Float64 = 8,
        Float_End      = 8,
        Scalar_End     = 8,
        Ref = 9,
        Struct  = 10,
        Func = 11,
    };
    bool isValueTypeScalar(ValueType type);
    bool isValueTypeInt(ValueType type);
    bool isValueTypeUnsigned(ValueType type);
    bool isValueTypeFloat(ValueType type);
}

#endif // BRANESCRIPT_VALUETYPE_H

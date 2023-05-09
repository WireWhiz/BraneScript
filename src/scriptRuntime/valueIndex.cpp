//
// Created by wirewhiz on 17/10/22.
//

#include "valueIndex.h"

namespace BraneScript
{
    bool isValueTypeScalar(ValueType type) { return ValueType::Scalar_Begin <= type && type <= ValueType::Scalar_End; }

    bool isValueTypeSigned(ValueType type) { return ValueType::Signed_Begin <= type && type <= ValueType::Signed_End; }

    bool isValueTypeUnsigned(ValueType type)  { return ValueType::Unsigned_Begin <= type && type <= ValueType::Unsigned_End; }

    bool isValueTypeFloat(ValueType type) { return ValueType::Float_Begin <= type && type <= ValueType::Float_End; }
} // namespace BraneScript
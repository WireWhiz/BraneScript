//
// Created by wirewhiz on 17/10/22.
//

#include "valueIndex.h"
namespace BraneScript
{
    const char* valueTypeName(ValueType type)
    {
        switch (type)
        {

            case Int32:
                return "int";
            case Int64:
                return "long";
            case Float32:
                return "float";
            case Float64:
                return "double";
            default:
                return nullptr;
        }
    }
}
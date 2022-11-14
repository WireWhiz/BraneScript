//
// Created by wirewhiz on 15/10/22.
//

#include "nativeTypes.h"
namespace BraneScript
{
    std::vector<TypeDef*> nativeTypes({new BoolDef(), new IntDef(), new FloatDef()});

    std::vector<TypeDef*> getNativeTypes()
    {
        return nativeTypes;
    };


    TypeDef* getNativeTypeDef(ValueType type)
    {
        switch (type)
        {
            case Bool:
                return nativeTypes[0];
            case Int32:
                return nativeTypes[1];
            case Int64:
                break;
            case Float32:
                return nativeTypes[2];
            case Float64:
                break;
        }
        return nullptr;
    };


    const char* BoolDef::name() const
    {
        return "bool";
    }

    uint32_t BoolDef::size() const
    {
        return sizeof(bool);
    }

    ValueType BoolDef::type() const
    {
        return Bool;
    }

    const char* IntDef::name() const
    {
        return "int";
    }

    uint32_t IntDef::size() const
    {
        return sizeof(int32_t);
    }

    ValueType IntDef::type() const
    {
        return Int32;
    }

    const char* FloatDef::name() const
    {
        return "float";
    }

    uint32_t FloatDef::size() const
    {
        return sizeof(float);
    }

    ValueType FloatDef::type() const
    {
        return Float32;
    }
}
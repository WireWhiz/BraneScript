//
// Created by wirewhiz on 15/10/22.
//

#include "nativeTypes.h"

std::vector<TypeDef*> nativeTypes({new IntDef(), new FloatDef()});
std::vector<TypeDef*> getNativeTypes()
{
    return nativeTypes;
};


TypeDef* getTypeDef(ValueType type)
{
    switch(type)
    {
        case Int32:
            return nativeTypes[0];
        case Int64:
            break;
        case Float32:
            return nativeTypes[1];
        case Float64:
            break;
        case Ptr:
            break;
    }
    return nullptr;
};

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
    return ValueType::Int32;
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

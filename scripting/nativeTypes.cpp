//
// Created by wirewhiz on 15/10/22.
//

#include "nativeTypes.h"

std::vector<TypeDef*> nativeTypes({new IntDef()});
std::vector<TypeDef*> getNativeTypes()
{
    return nativeTypes;
};

const char* IntDef::name() const
{
    return "int";
}

uint32_t IntDef::size() const
{
    return sizeof(int32_t);
}

TypeDef::Type IntDef::type() const
{
    return TypeDef::Int;
}

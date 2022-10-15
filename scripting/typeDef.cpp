//
// Created by wirewhiz on 14/10/22.
//

#include "typeDef.h"

uint32_t IntDef::size() const
{
    return sizeof(int32_t);
}

TypeDef::Type IntDef::type() const
{
    return TypeDef::Int;
}

uint32_t FloatDef::size() const
{
    return sizeof(float);
}

TypeDef::Type FloatDef::type() const
{
    return Type::Float;
}


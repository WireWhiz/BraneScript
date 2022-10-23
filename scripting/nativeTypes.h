//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_NATIVETYPES_H
#define BRANESCRIPT_NATIVETYPES_H

#include "typeDef.h"
#include <vector>

std::vector<TypeDef*> getNativeTypes();
TypeDef* getTypeDef(ValueType type);

class IntDef : public TypeDef
{
public:
    const char* name() const override;
    uint32_t size() const override;
    ValueType type() const override;
};

class FloatDef : public TypeDef
{
public:
    const char* name() const override;
    uint32_t size() const override;
    ValueType type() const override;
};


#endif //BRANESCRIPT_NATIVETYPES_H

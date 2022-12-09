//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_NATIVETYPES_H
#define BRANESCRIPT_NATIVETYPES_H

#include "typeDef.h"
#include <vector>
namespace BraneScript
{
    std::vector<TypeDef*> getNativeTypes();

    TypeDef* getNativeTypeDef(ValueType type);

    class BoolDef : public TypeDef
    {
    public:
        const char* name() const override;

        uint16_t size() const override;

        ValueType type() const override;
    };

    class IntDef : public TypeDef
    {
    public:
        const char* name() const override;

        uint16_t size() const override;

        ValueType type() const override;
    };

    class FloatDef : public TypeDef
    {
    public:
        const char* name() const override;

        uint16_t size() const override;

        ValueType type() const override;
    };
}
#endif //BRANESCRIPT_NATIVETYPES_H
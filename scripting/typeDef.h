//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_TYPEDEF_H
#define BRANESCRIPT_TYPEDEF_H


#include <cstdint>

class TypeDef
{
public:
    enum Type
    {
        Void,
        Int,
        Float
    };

    virtual ~TypeDef() = default;
    virtual uint32_t size() const = 0;
    virtual Type type() const = 0;
};

class IntDef : public TypeDef
{
public:
    uint32_t size() const override;
    Type type() const override;
};

class FloatDef : public TypeDef
{
public:
    uint32_t size() const override;
    Type type() const override;
};




#endif //BRANESCRIPT_TYPEDEF_H

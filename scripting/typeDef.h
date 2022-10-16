//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_TYPEDEF_H
#define BRANESCRIPT_TYPEDEF_H

#include <cstdint>
#include <string>

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
    virtual const char* name() const = 0;
    virtual uint32_t size() const = 0;
    virtual Type type() const = 0;
};




#endif //BRANESCRIPT_TYPEDEF_H

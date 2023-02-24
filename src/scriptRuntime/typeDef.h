//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_TYPEDEF_H
#define BRANESCRIPT_TYPEDEF_H

#include <cstdint>
#include <string>
#include "valueIndex.h"
namespace BraneScript
{
    class TypeDef
    {
    public:
        virtual ~TypeDef() = default;
        virtual const char* name() const = 0;
        virtual uint16_t size() const = 0;
        virtual ValueType type() const = 0;
    };
}



#endif //BRANESCRIPT_TYPEDEF_H

//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_TYPEDEF_H
#define BRANESCRIPT_TYPEDEF_H

#include <cstdint>
#include <string>
#include <vector>
#include "valueIndex.h"

namespace BraneScript
{
    struct TypeDef
    {
        std::string name = "void";
        ValueType storageType = ValueType::Void;
        size_t size = 0;
        TypeDef() = default;
        TypeDef(std::string name, ValueType storageType, size_t size)
            : name(std::move(name)), storageType(storageType), size(size) {}
        virtual ~TypeDef() = default;
    };
}



#endif //BRANESCRIPT_TYPEDEF_H

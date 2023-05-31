//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_NATIVETYPES_H
#define BRANESCRIPT_NATIVETYPES_H

#include <cstdarg>
#include <vector>
#include "funcRef.h"
#include "typeDef.h"
#include <robin_hood.h>

namespace BraneScript
{
    const std::vector<TypeDef*>& getNativeTypes();

    TypeDef* getNativeTypeDef(ValueType type);

    class Operator;
    const robin_hood::unordered_map<std::string, Operator*>& nativeOperators();
}
#endif //BRANESCRIPT_NATIVETYPES_H

//
// Created by wirewhiz on 14/10/22.
//

#include "scriptFunction.h"

uint32_t ScriptFunction::registerConstant(int value)
{
    uint32_t index = constants.ints.size();
    constants.ints.push_back(value);
    return index;
}

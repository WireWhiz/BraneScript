//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_IRSCRIPT_H
#define BRANESCRIPT_IRSCRIPT_H

#include <vector>
#include <string>
#include "baseTypes.h"
#include "scriptFunction.h"

struct IRScript
{
    struct LinkedFunction
    {
        std::string name;
        std::vector<BaseType> arguments;
    };

    std::vector<ScriptFunction> localFunctions;
    std::vector<LinkedFunction> linkedFunctions;
};


#endif //BRANESCRIPT_IRSCRIPT_H

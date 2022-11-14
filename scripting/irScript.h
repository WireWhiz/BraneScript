//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_IRSCRIPT_H
#define BRANESCRIPT_IRSCRIPT_H

#include <vector>
#include <string>
#include "baseTypes.h"
#include "scriptFunction.h"
namespace BraneScript
{
    struct IRScript
    {
        struct LinkedFunction
        {
            std::string name;
            uint16_t library;
        };

        std::vector<std::string> linkedLibraries;
        std::vector<ScriptFunction> localFunctions;
        std::vector<LinkedFunction> linkedFunctions;
        std::vector<std::string> linkedTypes;
    };

}
#endif //BRANESCRIPT_IRSCRIPT_H

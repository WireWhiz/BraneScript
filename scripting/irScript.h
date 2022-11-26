//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_IRSCRIPT_H
#define BRANESCRIPT_IRSCRIPT_H

#include <vector>
#include <string>
#include "baseTypes.h"
#include "irFunction.h"
namespace BraneScript
{


    struct IRScript
    {
        std::string namespace_;
        std::vector<IRFunction> localFunctions;

        struct IRStructDef
        {
            struct Member
            {
                std::string name;
                uint16_t offset;
                std::string type;
            };
            std::string name;
            std::vector<Member> members;
            uint16_t functions;
            bool packed = false;
        };
        std::vector<IRStructDef> localStructs;
        std::vector<std::string> linkedStructs;

        struct LinkedFunction
        {
            std::string name;
            uint16_t library;
        };


        std::vector<std::string> linkedLibraries;
        std::vector<LinkedFunction> linkedFunctions;
        std::vector<std::string> linkedTypes;
    };

}
#endif //BRANESCRIPT_IRSCRIPT_H

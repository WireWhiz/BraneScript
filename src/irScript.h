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
            bool isPublic = false;
        };
        std::vector<IRStructDef> localStructs;

        std::vector<std::string> linkedLibraries;
        std::vector<std::string> linkedFunctions;
        std::vector<std::string> linkedStructs;

        int16_t findLocalFuncIndex(const std::string& name) const;

        int16_t linkLibrary(const std::string& name);
        int16_t linkFunction(const std::string& name);
        int16_t linkStruct(const std::string& name);
    };

}
#endif //BRANESCRIPT_IRSCRIPT_H

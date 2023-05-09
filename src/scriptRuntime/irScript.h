//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_IRSCRIPT_H
#define BRANESCRIPT_IRSCRIPT_H

#include <vector>
#include <string>

namespace llvm
{
    class Module;
}

namespace BraneScript
{
    struct IRStructDef
    {
        struct Member
        {
            std::string name;
            std::string type;
        };
        std::string name;
        std::vector<Member> members;
        bool packed;
    };

    struct IRScript
    {
        std::string id;
        std::string bitcode;

        std::vector<std::string> exportedFunctions;
        std::vector<std::string> exportedGlobals;
        std::vector<IRStructDef> exportedStructs;

        std::vector<std::string> importedLibs;
        std::vector<std::string> exportedLibs;
    };
}
#endif //BRANESCRIPT_IRSCRIPT_H

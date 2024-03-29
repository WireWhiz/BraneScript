//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_IRSCRIPT_H
#define BRANESCRIPT_IRSCRIPT_H

#include <vector>
#include <string>
#include <robin_hood.h>
#include "utility/serializedData.h"

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
            bool isRef;
        };
        std::string name;
        std::vector<Member> members;
        std::string constructorSig;
        std::string destructorSig;
        std::string copyConstructorSig;
        std::string moveConstructorSig;
        std::vector<std::string> tags;
        void serialize(OutputSerializer out);
        void deserialize(InputSerializer in);
    };

    struct IRFunction
    {
        std::string name;
        std::string returnType;
        std::vector<std::string> tags;
        void serialize(OutputSerializer out);
        void deserialize(InputSerializer in);
    };

    struct IRGlobal
    {
        std::string name;
        std::string type;
        void serialize(OutputSerializer out);
        void deserialize(InputSerializer in);
    };

    struct IRModule
    {
        std::string id;
        std::string bitcode;
        std::vector<std::string> tags;

        std::vector<IRFunction> functions;
        std::vector<IRGlobal> globals;
        std::vector<IRStructDef> structs;

        std::vector<std::string> links;
        void serialize(OutputSerializer out);
        void deserialize(InputSerializer in);
    };

    struct IRScript
    {
        std::string id;
        robin_hood::unordered_map<std::string, IRModule> modules;
    };
}
#endif //BRANESCRIPT_IRSCRIPT_H

//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_SCRIPT_H
#define BRANESCRIPT_SCRIPT_H

#include <vector>
#include <unordered_map>
#include <string>
#include <asmjit/core/codeholder.h>
#include "functionReference.h"

namespace BraneScript
{
    class Script
    {
    public:
        std::vector<FunctionReference> functions;
        std::unordered_map<std::string, size_t> functionNames;

        template<typename Ret, typename... Args>
        FunctionHandle<Ret, Args...> getFunction(const std::string& name)
        {
            auto f = functionNames.find(name);
            if (f == functionNames.end())
                return nullptr;
            return functions[f->second].getOverride<Ret, Args...>();
        }
    };
}

#endif //BRANESCRIPT_SCRIPT_H

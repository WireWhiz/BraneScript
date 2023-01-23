//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_SCRIPT_H
#define BRANESCRIPT_SCRIPT_H

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <asmjit/core/codeholder.h>
#include "functionHandle.h"

namespace BraneScript
{
    class Script
    {
    public:
        std::vector<void*> functions;

        std::vector<uint8_t> globalVars;
        std::vector<std::unique_ptr<std::string>> constStrings;

        std::unordered_map<std::string, size_t> functionNames;

        template<typename Ret, typename... Args>
        FunctionHandle<Ret, Args...> getFunction(const std::string& name) const
        {
            std::string arguments;
            //Check to see if arguments already have been filled in
            if(*--name.end() != ')')
            {
                if constexpr(sizeof...(Args) > 0)
                    arguments = "(" + argsToString<Args...>() + ")";
                else
                    arguments = "()";
            }

            auto f = functionNames.find(name + arguments);
            if (f == functionNames.end())
                return nullptr;
            return (FunctionHandle<Ret, Args...>)functions[f->second];
        }

        /** @brief DO NOT CALL! Called automatically by script runtime upon creation */
        void init();
        ~Script();
    };
}

#endif //BRANESCRIPT_SCRIPT_H

//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_SCRIPT_H
#define BRANESCRIPT_SCRIPT_H

#include <vector>
#include <unordered_map>
#include <string>
#include <asmjit/core/codeholder.h>

class Script
{
public:
    std::vector<void*> functions;
    std::unordered_map<std::string, size_t> functionNames;

    template<typename Ret, typename... Args>
    using FunctionHandle = Ret (__cdecl *)(Args...);

    template<typename Ret, typename... Args>
    FunctionHandle<Ret, Args...> getFunction(size_t index)
    {
        return (FunctionHandle<Ret, Args...>)functions[index];
    }

    template<typename Ret, typename... Args>
    FunctionHandle<Ret, Args...> getFunction(const std::string& name)
    {
        auto f = functionNames.find(name);
        if(f == functionNames.end())
            return nullptr;
        return (FunctionHandle<Ret, Args...>)functions[f->second];
    }
};


#endif //BRANESCRIPT_SCRIPT_H

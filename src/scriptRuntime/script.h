//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_SCRIPT_H
#define BRANESCRIPT_SCRIPT_H

#include <memory>
#include <string>
#include <vector>
#include "functionHandle.h"
#include "robin_hood.h"
#include <llvm/ADT/IntrusiveRefCntPtr.h>
#include <unordered_map>

namespace llvm::orc
{
    class JITDylib;
    class ResourceTracker;
}

namespace BraneScript
{
    class Script
    {
        friend class ScriptRuntime;
        FunctionHandle<void> destructor = nullptr;
    public:
        std::string source;
        robin_hood::unordered_set<std::string> exportsModules;

        llvm::orc::JITDylib& lib;
        llvm::IntrusiveRefCntPtr<llvm::orc::ResourceTracker> rt;

        std::vector<void*> functions;
        std::vector<void*> globalVars;

        robin_hood::unordered_map<std::string, size_t> functionNames;
        robin_hood::unordered_map<std::string, size_t> globalNames;

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

        template<typename T>
        T* getGlobal(const std::string& name)
        {
            auto g = globalNames.find(name);
            if(g == globalNames.end())
                return nullptr;
            return (T*)globalVars[g->second];
        }

        Script(llvm::orc::JITDylib& lib);
        ~Script();
    };
}

#endif //BRANESCRIPT_SCRIPT_H

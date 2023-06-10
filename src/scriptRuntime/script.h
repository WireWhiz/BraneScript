//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_SCRIPT_H
#define BRANESCRIPT_SCRIPT_H

#include <memory>
#include <string>
#include <vector>
#include "funcRef.h"
#include "robin_hood.h"
#include "scriptRuntime/structDef.h"
#include <llvm/ADT/IntrusiveRefCntPtr.h>
#include <unordered_map>

namespace llvm::orc
{
    class JITDylib;
    class ResourceTracker;
}

namespace BraneScript
{
    class Module
    {
        friend class ScriptRuntime;
    public:
        FuncRef<void> destructor = nullptr;
        std::string id;

        llvm::orc::JITDylib* lib = nullptr;
        llvm::IntrusiveRefCntPtr<llvm::orc::ResourceTracker> rt;

        std::vector<void*> functions;
        std::vector<void*> globalVars;
        robin_hood::unordered_map<std::string, std::unique_ptr<StructDef>> structDefinitions;

        robin_hood::unordered_map<std::string, size_t> functionNames;
        robin_hood::unordered_map<std::string, size_t> globalNames;

        template<typename Ret, typename... Args>
        FuncRef<Ret, Args...> getFunction(const std::string& name) const
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
            return (FuncRef<Ret, Args...>)functions[f->second];
        }

        template<typename T>
        T* getGlobal(const std::string& name)
        {
            auto g = globalNames.find(name);
            if(g == globalNames.end())
                return nullptr;
            return (T*)globalVars[g->second];
        }

        Module(llvm::orc::JITDylib& lib);
        ~Module();
    };
}

#endif //BRANESCRIPT_SCRIPT_H

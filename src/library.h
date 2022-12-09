#ifndef BRANESCRIPT_LIBRARY_H
#define BRANESCRIPT_LIBRARY_H

#include <unordered_map>
#include <string>
#include "functionHandle.h"

namespace BraneScript
{

    class Library
    {
        std::unordered_map<std::string, std::pair<std::string, void*>> _functions;
        std::string _name;
    public:
        Library(std::string name);

        //Library functions must use the cdecl calling convention
        template<typename Ret, typename... Args>
        void addFunction(std::string name, FunctionHandle<Ret, Args...> f)
        {
            std::string decl = std::move(name) + "(" + argsToString<Args...>() + ")";
            _functions.insert({decl, {typeName<Ret>(), (void*)f}});
        }

        void* getFunction(const std::string& name) const;
        std::string getFunctionReturnT(const std::string& name) const;

        const std::string& name() const;
    };
}

#endif //BRANESCRIPT_LIBRARY_H

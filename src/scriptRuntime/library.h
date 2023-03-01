#ifndef BRANESCRIPT_LIBRARY_H
#define BRANESCRIPT_LIBRARY_H

#include <unordered_map>
#include <string>
#include "functionHandle.h"
#include "structDefinition.h"
#include "robin_hood.h"

namespace BraneScript
{

    class Library
    {
        robin_hood::unordered_map<std::string, StructDef> _structs;
        robin_hood::unordered_map<std::string, FunctionData> _functions;
        std::string _name;
    public:
        Library(std::string name);

        //Library functions must use the cdecl calling convention
        template<typename Ret, typename... Args>
        void addFunction(std::string name, FunctionHandle<Ret, Args...> f)
        {
            std::string decl = std::move(name) + "(" + argsToString<Args...>() + ")";
            addFunction(decl, typeName<Ret>(), 0, (void*)f);
        }

        void addFunction(const std::string& sig, const std::string& ret, size_t argCount, void* f);
        void addStruct(StructDef def);

        const FunctionData* getFunction(const std::string& name) const;
        const StructDef* getStruct(const std::string& name) const;

        const std::string& name() const;
    };
}

#endif //BRANESCRIPT_LIBRARY_H

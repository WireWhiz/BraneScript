#ifndef BRANESCRIPT_LINKER_H
#define BRANESCRIPT_LINKER_H

#include <string>
#include "functionHandle.h"
#include <robin_hood.h>
#include <unordered_map>

#include "structDefinition.h"

namespace BraneScript
{
    class Operator;
    class TypeDef;

    class Linker
    {
        robin_hood::unordered_map<std::string, const TypeDef*> _globalTypes;

        robin_hood::unordered_node_map<std::string, FunctionData> _functions;
        robin_hood::unordered_node_map<std::string, StructDef> _structs;

      public:
        Linker();

        template<typename Ret, typename... Args>
        void addFunction(std::string name, FunctionHandle<Ret, Args...> f)
        {
            std::string decl = std::move(name) + "(";
            if constexpr(sizeof...(Args))
                decl += argsToString<Args...>();
            decl += ")";
            addFunction(decl, typeName<Ret>(), sizeof...(Args), (void*)f);
        }

        void addFunction(const std::string& sig, const std::string& ret, size_t argCount, void* f);
        void addStruct(StructDef def);

        void removeFunction(const std::string& sig);
        void removeStruct(const std::string& sig);

        const TypeDef* getType(const std::string& sig) const;
        const FunctionData* getFunction(const std::string& sig) const;
        const StructDef* getStruct(const std::string& sig) const;
    };
} // namespace BraneScript


#endif // BRANESCRIPT_LINKER_H

#ifndef BRANESCRIPT_LINKER_H
#define BRANESCRIPT_LINKER_H

#include <unordered_map>
#include <string>
#include "functionHandle.h"
#include "library.h"
#include <robin_hood.h>

namespace BraneScript
{
    class Operator;
    class TypeDef;
    class Linker
    {
        Library _global;
        robin_hood::unordered_map<std::string, const TypeDef*> _globalTypes;
        robin_hood::unordered_map<std::string, Library*> _libraries;
    public:
        Linker();
        Library* getLibrary(const std::string& name) const;

        void addLibrary(Library* lib);
        void removeLibrary(const std::string& name);

        Library& globalLib();

        void addGlobalType(const TypeDef* type);
        void addGlobalFunction(const std::string& sig, const std::string& ret, void* func);

        const TypeDef* getType(const std::string& name) const;
        const StructDef* getStruct(const std::string& name) const;
        const FunctionData* getFunction(const std::string& name) const;
    };
}


#endif //BRANESCRIPT_LINKER_H

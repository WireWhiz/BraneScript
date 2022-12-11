#ifndef BRANESCRIPT_LINKER_H
#define BRANESCRIPT_LINKER_H

#include <unordered_map>
#include <string>
#include "functionHandle.h"
#include "library.h"

namespace BraneScript
{
    class TypeDef;
    class Linker
    {
        Library _global;
        std::unordered_map<std::string, TypeDef*> _globalTypes;
    public:
        Linker();
        std::unordered_map<std::string, Library*> libraries;
        Library* getLibrary(const std::string& name) const;

        void addLibrary(Library* lib);
        void removeLibrary(const std::string& name);

        Library& globalLib();

        const TypeDef* getType(const std::string& name);
        const StructDef* getStruct(const std::string& name);
        const FunctionData* getFunction(const std::string& name);
    };
}


#endif //BRANESCRIPT_LINKER_H

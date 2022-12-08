#ifndef BRANESCRIPT_LINKER_H
#define BRANESCRIPT_LINKER_H

#include <unordered_map>
#include <string>

namespace BraneScript
{
    class Library;
    class TypeDef;
    class Linker
    {
    public:
        Linker();
        std::unordered_map<std::string, Library*> libraries;
        std::unordered_map<std::string, TypeDef*> globalTypes;
        Library* getLibrary(const std::string& name) const;

        void addLibrary(Library* lib);
        void removeLibrary(const std::string& name);
        TypeDef* getType(const std::string& name);
        void addType(TypeDef* type);
    };
}


#endif //BRANESCRIPT_LINKER_H

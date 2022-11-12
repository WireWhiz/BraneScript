#ifndef BRANESCRIPT_LINKER_H
#define BRANESCRIPT_LINKER_H

#include <unordered_map>
namespace BraneScript
{
    class Library;
    class Linker
    {
    public:
        std::unordered_map<std::string, Library*> libraries;
        Library* getLibrary(const std::string& name)const;

        void addLibrary(Library* lib);
        void removeLibrary(const std::string& name);
    };
}


#endif //BRANESCRIPT_LINKER_H

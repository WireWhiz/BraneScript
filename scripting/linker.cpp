//
// Created by eli on 11/11/2022.
//

#include "linker.h"
#include "library.h"
#include "typeDef.h"
#include "nativeTypes.h"

namespace BraneScript
{
    Library* Linker::getLibrary(const std::string& name) const
    {
        auto f = libraries.find(name);
        if (f == libraries.end())
            return nullptr;
        return f->second;
    }

    void Linker::addLibrary(Library* lib)
    {
        assert(lib);
        libraries.insert({lib->name(), lib});
    }

    void Linker::removeLibrary(const std::string& name)
    {
        assert(libraries.count(name));
        libraries.erase(name);
    }

    TypeDef* Linker::getType(const std::string& name)
    {
        if(globalTypes.count(name))
            return globalTypes.at(name);
        return nullptr;
    }

    Linker::Linker()
    {
        for(auto& t : getNativeTypes())
            globalTypes.emplace(t->name(), t);
    }

    void Linker::addType(TypeDef* type)
    {
        globalTypes.insert({type->name(), type});
    }
}
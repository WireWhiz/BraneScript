//
// Created by eli on 11/11/2022.
//

#include "linker.h"
#include "library.h"
#include "typeDef.h"
#include "nativeTypes.h"
#include "nativeLibrary.h"

namespace BraneScript
{

    Linker::Linker() : _global("global")
    {
        for(auto& t : getNativeTypes())
            _globalTypes.emplace(t->name(), t);
        _global.addStruct(*dynamic_cast<const StructDef*>(getNativeTypes()[8]));
        addLibrary(getNativeLibrary());
    }

    Library* Linker::getLibrary(const std::string& name) const
    {
        auto f = _libraries.find(name);
        if (f == _libraries.end())
            return nullptr;
        return f->second;
    }

    void Linker::addLibrary(Library* lib)
    {
        assert(lib);
        _libraries.insert({lib->name(), lib});
    }

    void Linker::removeLibrary(const std::string& name)
    {
        assert(_libraries.count(name));
        _libraries.erase(name);
    }

    Library& Linker::globalLib()
    {
        return _global;
    }

    void Linker::addGlobalType(const TypeDef *type) {
        auto structDef = dynamic_cast<const StructDef*>(type);
        if(structDef) {
            _global.addStruct(*structDef);
            return;
        }

        if(_globalTypes.contains(type->name()))
            return;
        _globalTypes.insert({type->name(), type});
    }

    void Linker::addGlobalFunction(const std::string& sig, const std::string& ret, void* func) {
        _global.addFunction(sig, ret, 0, func);
    }

    const TypeDef* Linker::getType(const std::string& name) const
    {
        auto gt = _globalTypes.find(name);
        if (gt != _globalTypes.end())
            return gt->second;
        return getStruct(name);
    }

    const StructDef* Linker::getStruct(const std::string& name) const
    {
        auto del = name.find("::");
        if(del == std::string::npos)
            return _global.getStruct(name);

        std::string prefix = {name.data(), del};
        auto lib = getLibrary(prefix);
        if(!lib)
            return _global.getStruct(name);
        return lib->getStruct(name);

    }

    const FunctionData* Linker::getFunction(const std::string& name) const
    {
        auto del = name.find("::");
        if(del == std::string::npos)
            return _global.getFunction(name);
        std::string prefix = {name.data(), del};
        auto lib = getLibrary(prefix);
        if(!lib)
            return _global.getFunction(name);
        return lib->getFunction(name);
    }
}
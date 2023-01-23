//
// Created by eli on 11/11/2022.
//

#include "linker.h"
#include "library.h"
#include "typeDef.h"
#include "nativeTypes.h"
#include "operator.h"

namespace BraneScript
{

    Linker::Linker() : _global("global")
    {
        for(auto& t : getNativeTypes())
            _globalTypes.emplace(t->name(), t);
        _global.addStruct(*dynamic_cast<const StructDef*>(getNativeTypes()[8]));
        for(auto& f : getNativeFunctions())
            _global.addFunction(f.name, f.ret, f.pointer);

        _operators = nativeOperators();
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

    void Linker::addGlobalOperator(const std::string& sig, Operator* opr) {
        if(_operators.contains(sig))
            return;
        _operators.insert({sig, opr});
    }

    void Linker::addGlobalFunction(const std::string& sig, const std::string& ret, void* func) {
        _global.addFunction(sig, ret, func);
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
        auto nameOffset = del + 2;
        assert(nameOffset < name.size());
        return lib->getStruct(std::string{name.data() + nameOffset, name.size() - nameOffset});

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
        auto nameOffset = del + 2;
        assert(nameOffset < name.size());
        return lib->getFunction(std::string{name.data() + nameOffset, name.size() - nameOffset});
    }

    const Operator* Linker::getOperator(const std::string& name) const
    {
        auto opr = _operators.find(name);
        if(opr != _operators.end())
            return opr->second;
        return nullptr;
    }


}
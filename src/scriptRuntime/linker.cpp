//
// Created by eli on 11/11/2022.
//

#include "linker.h"
#include "nativeLibrary.h"
#include "nativeTypes.h"
#include "typeDef.h"

namespace BraneScript
{

    Linker::Linker()
    {
        for(auto& t : getNativeTypes())
            _globalTypes.emplace(t->name(), t);
        addStruct(*dynamic_cast<const StructDef*>(getNativeTypes()[8]));
        addNativeFunctions(*this);
    }

    void Linker::addFunction(const std::string& sig, const std::string& ret, size_t argCount, void* f)
    {
        _functions.insert({sig, FunctionData(sig, ret, argCount, f)});
    }

    void Linker::addStruct(StructDef def)
    {
        if(_structs.count(def.name()))
            return;
        _structs.emplace(def.name(), std::move(def));
    }

    const TypeDef* Linker::getType(const std::string& sig) const
    {
        auto gt = _globalTypes.find(sig);
        if(gt != _globalTypes.end())
            return gt->second;
        return getStruct(sig);
    }

    const StructDef* Linker::getStruct(const std::string& sig) const
    {
        auto s = _structs.find(sig);
        if(s != _structs.end())
            return &s->second;
        return nullptr;
    }

    const FunctionData* Linker::getFunction(const std::string& sig) const
    {
        auto f = _functions.find(sig);
        if(f != _functions.end())
            return &f->second;
        return nullptr;
    }

    void Linker::removeFunction(const std::string& sig)
    {
        assert(_functions.contains(sig));
        _functions.erase(sig);
    }

    void Linker::removeStruct(const std::string& sig)
    {
        assert(_structs.contains(sig));
        _structs.erase(sig);
    }
} // namespace BraneScript
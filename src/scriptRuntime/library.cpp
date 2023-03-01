//
// Created by eli on 11/4/2022.
//

#include "library.h"

namespace BraneScript
{
    Library::Library(std::string name) : _name(std::move(name))
    {

    }

    const FunctionData* Library::getFunction(const std::string& name) const
    {
        auto f = _functions.find(name);
        if(f == _functions.end())
            return nullptr;
        return &f->second;
    }

    const std::string& Library::name() const
    {
        return _name;
    }

    void Library::addFunction(const std::string& sig, const std::string& ret, size_t argCount, void* f)
    {
        _functions.insert({sig, FunctionData(sig, ret, argCount, f)});
    }

    void Library::addStruct(StructDef def)
    {
        if(_structs.count(def.name()))
            return;
        std::string name = def.name();
        _structs.insert({name, std::move(def)});
    }

    const StructDef* Library::getStruct(const std::string& name) const
    {
        auto f = _structs.find(name);
        if(f == _structs.end())
            return nullptr;
        return &f->second;
    }
}



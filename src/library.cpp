//
// Created by eli on 11/4/2022.
//

#include "library.h"

BraneScript::Library::Library(std::string name) : _name(std::move(name))
{

}

void* BraneScript::Library::getFunction(const std::string& name) const
{
    auto f = _functions.find(name);
    if(f == _functions.end())
        return nullptr;
    return f->second.second;
}

const std::string& BraneScript::Library::name() const
{
    return _name;
}

std::string BraneScript::Library::getFunctionReturnT(const std::string& name) const
{
    auto f = _functions.find(name);
    if(f == _functions.end())
        return "void";
    return f->second.first;
}


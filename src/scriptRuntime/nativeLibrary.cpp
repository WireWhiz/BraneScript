//
// Created by wirewhiz on 2/24/23.
//

#include "nativeLibrary.h"

namespace BraneScript
{

    void NativeLibrary::addFunction(std::string signature, void* f) {
        functions.emplace_back(std::move(signature), f);
    }

    NativeLibrary::NativeLibrary(std::string identifier) : identifier(std::move(identifier)) {}

    void NativeLibrary::addStruct(std::unique_ptr<StructDef> s)
    {
        assert(s->name.find(identifier) != std::string::npos && "Struct name must be prefixed with the library identifier.");
        addFunction(s->name + "::_construct(ref " + s->name + ")", s->constructor);
        addFunction(s->name + "::_copy(ref " + s->name + ",const ref " + s->name + ")", s->copyConstructor);
        addFunction(s->name + "::_move(ref " + s->name + ",ref " + s->name + ")", s->moveConstructor);
        addFunction(s->name + "::_destruct(ref " + s->name + ")", s->destructor);
        structDefinitions.push_back(std::move(s));
    }
}
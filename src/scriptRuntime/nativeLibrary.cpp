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
}
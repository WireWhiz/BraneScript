//
// Created by wirewhiz on 2/24/23.
//

#ifndef BRANESCRIPT_NATIVELIBRARY_H
#define BRANESCRIPT_NATIVELIBRARY_H


#include <string>
#include <vector>
#include <memory>
#include "scriptRuntime/funcRef.h"
#include "scriptRuntime/structDef.h"

namespace BraneScript
{
    class StructDef;

    struct NativeLibrary
    {
        std::string identifier;
        std::vector<std::pair<std::string, void*>> functions;

        void addFunction(std::string signature, void* f);
        template<typename Ret, typename... Args>
        void addFunction(std::string signature, FuncRef<Ret, Args...> f)
        {
            addFunction(std::move(signature), (void*)f);
        }

        explicit NativeLibrary(std::string identifier);
        NativeLibrary(const NativeLibrary&) = delete;
        NativeLibrary(NativeLibrary&&) = default;
    };
}


#endif // BRANESCRIPT_NATIVELIBRARY_H

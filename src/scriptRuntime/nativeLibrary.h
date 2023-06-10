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
        std::vector<std::unique_ptr<StructDef>> structDefinitions;

        void addFunction(std::string signature, void* f);
        template<typename Ret, typename... Args>
        void addFunction(std::string signature, FuncRef<Ret, Args...> f)
        {
            addFunction(std::move(signature), (void*)f);
        }

        /***
         * Adds a struct definition to the library.
         * Constructor functions set in the struct definition will be added automatically, and should not added with addFunction method.
         * @param s The struct definition to add.
         */
        void addStruct(std::unique_ptr<StructDef> s);

        explicit NativeLibrary(std::string identifier);
        NativeLibrary(const NativeLibrary&) = delete;
        NativeLibrary(NativeLibrary&&) = default;
    };
}


#endif // BRANESCRIPT_NATIVELIBRARY_H

//
// Created by wirewhiz on 10/8/23.
//

#ifndef BRANESCRIPT_AST_H
#define BRANESCRIPT_AST_H

#include <optional>
#include <string>
#include <vector>
#include <memory>
#include <robin_hood.h>

#include "source.h"

namespace BraneScript::ast
{
    struct Module;

    struct Message
    {
        std::string message;
        std::optional<Source> source;
    };

    struct AstContext
    {
        virtual ~AstContext() = default;
    };

    struct AstWalkerBase;

    struct AstNode
    {
        std::optional<Source> source;
        std::vector<std::unique_ptr<AstContext>> contextItems;

        /**
         * Returns the first context item of type T.
         * @tparam T the type to find
         * @return pointer to a struct of type T or nullptr if not found.
         */
        template<typename T>
        T* context()
        {
            for(auto& item : contextItems)
            {
                if(auto ptr = dynamic_cast<T*>(&item))
                {
                    return ptr;
                }
            }

            return nullptr;
        }

        /**
         * Creates a new context item of type T and returns a pointer to it.
         * @tparam T the type to create, must be a subclass of AstContext
         */
        template<typename T>
        T* createContext()
        {
            static_assert(std::is_base_of_v<AstContext, T>, "T must be a subclass of AstContext");
            auto item = std::make_unique<T>();
            auto ptr = item.get();
            contextItems.push_back(std::move(item));
            return ptr;
        }

        virtual void accept(AstWalkerBase* walker) = 0;
    };

    /**
     * Stores an AST for brane script.
     */
    struct Ast
    {
        std::vector<Message> errors;
        std::vector<Message> warnings;
        robin_hood::unordered_map<std::string, std::unique_ptr<Module>> module;
        bool isValid = false;
    };
}



#endif // BRANESCRIPT_AST_H

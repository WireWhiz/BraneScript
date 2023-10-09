//
// Created by wirewhiz on 10/8/23.
//

#ifndef BRANESCRIPT_AST_H
#define BRANESCRIPT_AST_H

#include <optional>
#include "module.h"
#include "source.h"

namespace BraneScript::ast
{
    struct Message
    {
        std::string message;
        std::optional<Source> source;
    };

    struct Ast
    {
        std::vector<Message> errors;
        std::vector<Message> warnings;
        robin_hood::unordered_map<std::string, Module> module;
        bool isValid = false;
    };
}



#endif // BRANESCRIPT_AST_H

//
// Created by wirewhiz on 10/8/23.
//

#ifndef BRANESCRIPT_MODULE_H
#define BRANESCRIPT_MODULE_H

#include <vector>
#include <string>
#include <robin_hood.h>

#include "ast.h"
#include "expressions.h"
#include "scopedId.h"
#include "typeDef.h"

namespace BraneScript::ast
{
    struct Definition
    {
        bool isExported = false;
        virtual ~Definition() = default;
    };

    struct Import
    {
        virtual ~Import() = default;
    };

    struct Module : public AstNode
    {
        ScopedId name;
        std::vector<std::string> tags;

        std::vector<std::unique_ptr<Definition>> exports;
        std::vector<std::unique_ptr<Import>> imports;

        void accept(AstWalkerBase* walker) override;

        Module() = default;
    };

    struct ModuleImport : public Import
    {
        ScopedId id;
        std::optional<std::string> alias;
    };

    struct MemoryImport : public Import
    {
        ScopedId id;
        std::optional<std::string> alias;
    };

    struct MemoryDefinition : public Definition
    {
        ScopedId id;
    };

    struct GlobalDefinition : public Definition
    {
        ScopedId id;
        ScopedId type;
    };

    struct FunctionDefinition : public Definition
    {
        ScopedId id;
        std::vector<ScopedId> templateArgs;

        ScopedId returnType;
        std::vector<ScopedId> parameters;

        std::unique_ptr<Expression> body;
    };

    struct StructDefinition : public Definition
    {
        ScopedId id;

        std::vector<ScopedId> templateArgs;
        std::vector<ScopedId> members;
    };
}


#endif // BRANESCRIPT_MODULE_H

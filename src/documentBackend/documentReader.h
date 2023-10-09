//
// Created by wirewhiz on 10/8/23.
//

#ifndef BRANESCRIPT_DOCUMENTREADER_H
#define BRANESCRIPT_DOCUMENTREADER_H

#include <expected>
#include <string>

#include "compiler/ast/ast.h"

namespace BraneScript
{
    class DocumentReader
    {
      public:
        static std::expected<ast::Ast, std::string> readDocument(const std::string& text, std::optional<std::string> file = std::nullopt);
    };
}


#endif // BRANESCRIPT_DOCUMENTREADER_H

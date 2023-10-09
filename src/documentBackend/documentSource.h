//
// Created by wirewhiz on 10/8/23.
//

#ifndef BRANESCRIPT_DOCUMENTSOURCE_H
#define BRANESCRIPT_DOCUMENTSOURCE_H

#include <memory>
#include "compiler/ast/source.h"
#include "textPos.h"

namespace BraneScript::ast
{
    struct DocSource : public Source
    {
        TextRange range;
        std::shared_ptr<std::string> file;
    };
}

#endif // BRANESCRIPT_DOCUMENTSOURCE_H

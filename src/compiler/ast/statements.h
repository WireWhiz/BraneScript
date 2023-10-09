//
// Created by wirewhiz on 10/8/23.
//

#ifndef BRANESCRIPT_STATEMENTS_H
#define BRANESCRIPT_STATEMENTS_H

#include <string>
#include <optional>

#include "source.h"

namespace BraneScript::ast
{
    struct Statement
    {
        std::optional<Source> source;
        bool valid = false;
    };
}

#endif // BRANESCRIPT_STATEMENTS_H

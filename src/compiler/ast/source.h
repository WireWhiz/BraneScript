//
// Created by wirewhiz on 10/8/23.
//

#ifndef BRANESCRIPT_SOURCE_H
#define BRANESCRIPT_SOURCE_H

namespace BraneScript::ast
{
    /*
     * Source is the base class for implementation specific metadata about where an AST node came from.
     */
    struct Source
    {
        virtual ~Source() = default;
    };
}

#endif // BRANESCRIPT_SOURCE_H

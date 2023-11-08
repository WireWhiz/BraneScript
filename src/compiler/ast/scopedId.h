//
// Created by wirewhiz on 11/4/23.
//

#ifndef BRANESCRIPT_SCOPEDID_H
#define BRANESCRIPT_SCOPEDID_H

#include <optional>
#include <string>
#include <memory>

namespace BraneScript::ast
{
    struct ScopedId
    {
        std::optional<std::shared_ptr<ScopedId>> parent;
        std::string id;

        std::string toString() const;
        bool operator ==(const ScopedId& other) const;
    };


}

#endif // BRANESCRIPT_SCOPEDID_H

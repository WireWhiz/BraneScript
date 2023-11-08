#include "scopedId.h"

namespace BraneScript::ast
{
    std::string ScopedId::toString() const
    {
        if(!parent.has_value())
            return id;
        else
            return parent.value()->toString() + "::" + id;
    }

    bool ScopedId::operator==(const ScopedId& other) const
    {
        return id == other.id && parent == other.parent;
    }
}


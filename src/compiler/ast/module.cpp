#include "module.h"
#include "astWalker.h"

namespace BraneScript::ast
{
    void Module::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }
}
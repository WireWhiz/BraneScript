//
// Created by wirewhiz on 14/10/22.
//

#include "scriptFunction.h"

namespace BraneScript
{
    void ScriptFunction::appendCode(Operand op)
    {
        code.push_back(op);
    }
}
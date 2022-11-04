//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_SCRIPTRUNTIME_H
#define BRANESCRIPT_SCRIPTRUNTIME_H

#include <memory>
#include <vector>
#include "asmjit/core/jitruntime.h"
namespace BraneScript
{
    class Script;
    class IRScript;

    class ScriptRuntime
    {
        asmjit::JitRuntime _runtime;
        std::vector<std::unique_ptr<Script>> _scripts;
    public:
        Script* assembleScript(IRScript* irScript);
    };
}

#endif //BRANESCRIPT_SCRIPTRUNTIME_H

//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_SCRIPTRUNTIME_H
#define BRANESCRIPT_SCRIPTRUNTIME_H

#include <memory>
#include <vector>
#include "asmjit/core/jitruntime.h"
#include "functionHandle.h"
#include "robin_hood.h"

namespace BraneScript
{
    class Script;
    class IRScript;
    class IRFunction;
    class Linker;
    class StructDef;

#ifndef NDEBUG
    extern int scriptMallocDiff;
#endif

    struct ScriptAssembleContext
    {
        IRScript* irScript = nullptr;
        Script* script = nullptr;

        std::vector<const StructDef*> linkedStructs;
        std::vector<const FunctionData*> linkedFunctions;
    };

    class ScriptRuntime
    {
        asmjit::JitRuntime _runtime;
        std::vector<std::unique_ptr<Script>> _scripts;
        Linker* _linker = nullptr;
        size_t maxStackSize = 32768;

        robin_hood::unordered_map<void*, std::string> _exportedFunctions;

    public:
        Script* loadScript(IRScript* irScript);
        FunctionData loadFunction(IRFunction* function, ScriptAssembleContext* parentCtx = nullptr);
        void setLinker(Linker* linker);

        void unloadFunction(void* func);
    };
}

#endif //BRANESCRIPT_SCRIPTRUNTIME_H

//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_SCRIPTRUNTIME_H
#define BRANESCRIPT_SCRIPTRUNTIME_H

#include <memory>
#include <vector>
#include "functionHandle.h"
#include "nativeLibrary.h"
#include "robin_hood.h"

namespace llvm
{
    class DataLayout;

    namespace orc
    {
        class ExecutionSession;
        class IRCompileLayer;
        class MangleAndInterner;
        class RTDyldObjectLinkingLayer;
        class IRTransformLayer;
        class JITDylib;
    } // namespace orc
} // namespace llvm

namespace BraneScript
{
    class Script;
    class IRScript;
    class StructDef;

    class ScriptRuntime
    {
        robin_hood::unordered_map<std::string, std::unique_ptr<Script>> _scripts;
        robin_hood::unordered_map<std::string, robin_hood::unordered_set<llvm::orc::JITDylib*>> _modules;

        std::unique_ptr<llvm::orc::ExecutionSession> _session;
        std::unique_ptr<llvm::DataLayout> _layout;
        std::unique_ptr<llvm::orc::MangleAndInterner> _mangler;

        std::unique_ptr<llvm::orc::RTDyldObjectLinkingLayer> _linkingLayer;
        std::unique_ptr<llvm::orc::IRCompileLayer> _compileLayer;
        std::unique_ptr<llvm::orc::IRTransformLayer> _transformLayer;

        static int64_t _scriptMallocDiff;

      public:
        ScriptRuntime();
        ~ScriptRuntime();

        void loadLibrary(const NativeLibrary& lib);

        Script* loadScript(const IRScript& irScript);
        void unloadScript(const std::string& id);
        int64_t mallocDiff() const;
        void resetMallocDiff();
    };
} // namespace BraneScript

#endif // BRANESCRIPT_SCRIPTRUNTIME_H

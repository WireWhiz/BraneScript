//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_SCRIPTRUNTIME_H
#define BRANESCRIPT_SCRIPTRUNTIME_H

#include <memory>
#include <vector>
#include "funcRef.h"
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
    class Module;
    class IRModule;
    class StructDef;

    class ScriptRuntime
    {
        robin_hood::unordered_map<std::string, std::unique_ptr<Module>> _modules;
        robin_hood::unordered_map<std::string, llvm::orc::JITDylib*> _libraries;

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

        llvm::orc::JITDylib& loadLibrary(const NativeLibrary& lib);

        Module* loadModule(const IRModule& irModule);
        void unloadModule(const std::string& id);
        int64_t mallocDiff() const;
        void resetMallocDiff();
    };
} // namespace BraneScript

#endif // BRANESCRIPT_SCRIPTRUNTIME_H

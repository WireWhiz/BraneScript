//
// Created by wirewhiz on 15/10/22.
//

#ifndef BRANESCRIPT_SCRIPTRUNTIME_H
#define BRANESCRIPT_SCRIPTRUNTIME_H

#include "utility/DependencyGraph.h"
#include <vector>
#include "funcRef.h"
#include "nativeLibrary.h"
#include "robin_hood.h"
#include "varType.h"

namespace llvm
{
    class DataLayout;
    class Type;

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
    class TypeDef;

    enum ScriptRuntimeMode
    {
        // Debug mode will keep debug info and turn off optimization
        ScriptRuntimeMode_Debug,
        // Release mode will turn on optimization and remove debug info
        ScriptRuntimeMode_Release
    };

    class ScriptRuntime
    {
        ScriptRuntimeMode _mode;

        DependencyGraph<std::string, Module> _modules;
        robin_hood::unordered_map<std::string, TypeDef*> _types;

        std::unique_ptr<llvm::orc::ExecutionSession> _session;
        std::unique_ptr<llvm::DataLayout> _layout;
        std::unique_ptr<llvm::orc::MangleAndInterner> _mangler;

        std::unique_ptr<llvm::orc::RTDyldObjectLinkingLayer> _linkingLayer;
        std::unique_ptr<llvm::orc::IRCompileLayer> _compileLayer;
        std::unique_ptr<llvm::orc::IRTransformLayer> _transformLayer;

        static int64_t _scriptMallocDiff;

        VarType getVarType(llvm::Type* type) const;
      public:
        ScriptRuntime(ScriptRuntimeMode mode = ScriptRuntimeMode_Debug);
        ~ScriptRuntime();

        llvm::orc::JITDylib& loadLibrary(NativeLibrary&& lib);

        ResourceHandle<Module> loadModule(const IRModule& irModule);
        void unloadModule(const std::string& id);

        int64_t mallocDiff() const;
        void resetMallocDiff();
    };
} // namespace BraneScript

#endif // BRANESCRIPT_SCRIPTRUNTIME_H

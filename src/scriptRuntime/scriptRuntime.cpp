//
// Created by wirewhiz on 15/10/22.
//

#include "scriptRuntime.h"
#include "irScript.h"
#include "script.h"
#include "structDefinition.h"
#include "valueIndex.h"

#include "llvm/Analysis/CGSCCPassManager.h"
#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutorProcessControl.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/IRTransformLayer.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/Orc/Shared/ExecutorAddress.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"

#include <cstdio>
#include <stdexcept>
#include <llvm/Passes/PassBuilder.h>

namespace BraneScript
{

    int64_t ScriptRuntime::_scriptMallocDiff = 0;
    bool llvmInitialized = false;

    ScriptRuntime::ScriptRuntime(ScriptRuntimeMode mode) : _mode(mode)
    {
        if(!llvmInitialized)
        {
            llvm::InitializeNativeTarget();
            llvm::InitializeNativeTargetAsmPrinter();
            llvm::InitializeNativeTargetAsmParser();
            llvmInitialized = true;
        }

        auto EPC = llvm::orc::SelfExecutorProcessControl::Create();
        if(!EPC)
            throw std::runtime_error("Could not create llvm epc");
        _session = std::make_unique<llvm::orc::ExecutionSession>(std::move(*EPC));

        llvm::orc::JITTargetMachineBuilder jtmb(_session->getExecutorProcessControl().getTargetTriple());
        jtmb.setCodeGenOptLevel(llvm::CodeGenOpt::Level::Aggressive);

        auto dl = jtmb.getDefaultDataLayoutForTarget();
        if(!dl)
            throw std::runtime_error("Unable to get target data layout: " + toString(dl.takeError()));
        _layout = std::make_unique<llvm::DataLayout>(*dl);

        _mangler = std::make_unique<llvm::orc::MangleAndInterner>(*_session, *_layout);

        _linkingLayer = std::make_unique<llvm::orc::RTDyldObjectLinkingLayer>(
            *_session, []() { return std::make_unique<llvm::SectionMemoryManager>(); });

        if(_mode == ScriptRuntimeMode_Debug)
        {
            _linkingLayer->registerJITEventListener(*llvm::JITEventListener::createGDBRegistrationListener());
            _linkingLayer->setProcessAllSections(true);
        }

        _compileLayer = std::make_unique<llvm::orc::IRCompileLayer>(
            *_session, *_linkingLayer, std::make_unique<llvm::orc::ConcurrentIRCompiler>(jtmb));
        std::shared_ptr<llvm::TargetMachine> tm;
        if(auto etm = jtmb.createTargetMachine())
            tm = std::move(*etm);
        _transformLayer = std::make_unique<llvm::orc::IRTransformLayer>(*_session, *_compileLayer, [this, tm](llvm::orc::ThreadSafeModule m, const auto& r) {
                // Add some optimizations.
                std::string moduleErr;
                llvm::raw_string_ostream modErrStr(moduleErr);
                if(llvm::verifyModule(*m.getModuleUnlocked(), &modErrStr))
                {
                    std::string module;
                    llvm::raw_string_ostream modStr(module);
                    m.getModuleUnlocked()->print(modStr, nullptr);
                    fprintf(stderr, "%s", module.c_str());
                    throw std::runtime_error("Module verification failed: " + modErrStr.str());
                }

                if(_mode == ScriptRuntimeMode_Debug)
                    return std::move(m);

                llvm::LoopAnalysisManager lam;
                llvm::FunctionAnalysisManager fam;
                llvm::CGSCCAnalysisManager cgam;
                llvm::ModuleAnalysisManager mam;

                llvm::PassBuilder PB(tm.get());

                // Register all the basic analyses with the managers.

                PB.registerModuleAnalyses(mam);
                PB.registerCGSCCAnalyses(cgam);
                PB.registerFunctionAnalyses(fam);
                PB.registerLoopAnalyses(lam);
                PB.crossRegisterProxies(lam, fam, cgam, mam);

                // Create the pass manager.
                auto fpm = PB.buildFunctionSimplificationPipeline(llvm::PassBuilder::OptimizationLevel::O2,
                                                                  llvm::ThinOrFullLTOPhase::FullLTOPostLink);


                // Run the optimizations over all functions in the module being added to
                // the JIT.
                for(auto& f : *m.getModuleUnlocked())
                {
                    if(f.empty())
                        continue;
                    fpm.run(f, fam);
                }

                return std::move(m);
            });

        NativeLibrary unsafeLib("unsafe");
        unsafeLib.addFunction("unsafe::malloc(uint)", (FuncRef<void*, int>)[](int size){
            _scriptMallocDiff++;
            auto ptr = ::operator new(size);
            //printf("Allocating %d bytes at %p\n", size, ptr);
            return ptr;
        });
        unsafeLib.addFunction("unsafe::free(ref void)", (FuncRef<void, void*>)[](void* ptr){
            _scriptMallocDiff--;
            //printf("Freeing %p\n", ptr);
            ::operator delete(ptr);
        });
        loadLibrary(unsafeLib);
    }

    Module* ScriptRuntime::loadModule(const IRModule& irModule)
    {
        if(_modules.contains(irModule.id))
            throw std::runtime_error("Module with id \"" + irModule.id + "\" already loaded");
        auto ctx = std::make_unique<llvm::LLVMContext>();

        auto deserializedModule = llvm::parseBitcodeFile(llvm::MemoryBufferRef(irModule.bitcode, irModule.id), *ctx);
        if(!deserializedModule)
        {
            auto errorText = toString(deserializedModule.takeError());
            throw std::runtime_error("Could not deserialize module: " + errorText);
        }
        (*deserializedModule)->setDataLayout(*_layout);
        (*deserializedModule)->setTargetTriple(_session->getExecutorProcessControl().getTargetTriple().str());

        auto& lib = _session->createBareJITDylib(irModule.id);
        for(auto& importedModule : irModule.links)
        {
            auto providers = _libraries.find(importedModule);
            if(providers == _libraries.end())
                throw std::runtime_error(irModule.id + " Could not link to required module: " + importedModule);
            lib.addToLinkOrder(*providers->second);
        }

        auto* script = new Module(lib);
        script->rt = lib.getDefaultResourceTracker();

        if(llvm::Error res = _transformLayer->add(
               script->rt, llvm::orc::ThreadSafeModule(std::move(*deserializedModule), std::move(ctx))))
            throw std::runtime_error("Unable to add script: " + toString(std::move(res)));

        for(auto& glob : irModule.globals)
        {
            auto globSymbol = _session->lookup({&lib}, (*_mangler)(glob.name));
            if(!globSymbol)
                throw std::runtime_error("Unable to find exported global: " + toString(globSymbol.takeError()));
            script->globalNames.insert({glob.name, script->globalVars.size()});
            script->globalVars.push_back((void*)globSymbol->getAddress());
        }

        for(auto& func : irModule.functions)
        {
            auto functionSym = _session->lookup({&lib}, (*_mangler)(func.name));
            if(!functionSym)
                throw std::runtime_error("Unable to find exported function: " + toString(functionSym.takeError()));
            script->functionNames.insert({func.name, script->functions.size()});
            script->functions.push_back((void*)functionSym->getAddress());
        }

        auto constructor = _session->lookup({&lib}, (*_mangler)("_construct"));
        if(constructor)
            FuncRef<void>(constructor->getAddress())();

        auto destructor = _session->lookup({&lib}, (*_mangler)("_construct"));
        if(destructor)
            script->destructor = FuncRef<void>(destructor->getAddress());

        // TODO extract structs

        _modules.emplace(irModule.id, script);
        _libraries.emplace(irModule.id, &script->lib);

        return script;
    }

    void ScriptRuntime::unloadModule(const std::string& id)
    {
        // TODO assert that no scripts depend on this one
        assert(_modules.contains(id));

        _libraries.erase(id);
        _modules.erase(id);
    }

    ScriptRuntime::~ScriptRuntime() { _modules.clear(); }

    llvm::orc::JITDylib& ScriptRuntime::loadLibrary(const NativeLibrary& lib)
    {
        auto& newLib = _session->createBareJITDylib(lib.identifier);
        llvm::orc::SymbolMap symbols;
        for(auto& func : lib.functions)
        {
            symbols.insert(
                {(*_mangler)(func.first),
                 llvm::JITEvaluatedSymbol::fromPointer(func.second,
                                                       llvm::JITSymbolFlags::Exported | llvm::JITSymbolFlags::Weak |
                                                           llvm::JITSymbolFlags::Callable)});
        }
        if(auto err = newLib.define(llvm::orc::absoluteSymbols(symbols)))
            throw std::runtime_error("Unable to load native library: " + toString(std::move(err)));
        _libraries.emplace(lib.identifier, &newLib);
        return newLib;
    }

    int64_t ScriptRuntime::mallocDiff() const { return _scriptMallocDiff; }

    void ScriptRuntime::resetMallocDiff() { _scriptMallocDiff = 0; }

} // namespace BraneScript
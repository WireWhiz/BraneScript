//
// Created by wirewhiz on 15/10/22.
//

#include "scriptRuntime.h"
#include "irScript.h"
#include "script.h"
#include "structDef.h"
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

    std::vector<std::unique_ptr<TypeDef>> nativeTypes;

    ScriptRuntime::ScriptRuntime(ScriptRuntimeMode mode) : _mode(mode)
    {
        if(nativeTypes.empty())
        {
            nativeTypes.emplace_back(new TypeDef("void", ValueType::Void, 0));
            nativeTypes.emplace_back(new TypeDef("bool", ValueType::Bool, 1));
            nativeTypes.emplace_back(new TypeDef("uint", ValueType::UInt32, 4));
            nativeTypes.emplace_back(new TypeDef("int", ValueType::Int32, 4));
            nativeTypes.emplace_back(new TypeDef("uint64", ValueType::UInt64, 8));
            nativeTypes.emplace_back(new TypeDef("int64", ValueType::Int64, 8));
            nativeTypes.emplace_back(new TypeDef("float", ValueType::Float32, 4));
            nativeTypes.emplace_back(new TypeDef("double", ValueType::Float64, 8));
            nativeTypes.emplace_back(new TypeDef("FuncRef", ValueType::FuncRef, sizeof(void(*))));
        }
        for(auto& t : nativeTypes)
            _types.emplace(t->name, t.get());

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
        loadLibrary(std::move(unsafeLib));
    }

    ResourceHandle<Module> ScriptRuntime::loadModule(const IRModule& irModule)
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
            if(!_modules.contains(importedModule))
                throw std::runtime_error(irModule.id + " Could not link to required module: " + importedModule);
            lib.addToLinkOrder(*_modules.at(importedModule)->lib);
        }

        auto module = new Module(lib);
        module->rt = lib.getDefaultResourceTracker();

        printf("Loading module %s with structs:\n", irModule.id.c_str());
        for(auto& s : (*deserializedModule)->getIdentifiedStructTypes())
        {
            printf("  %s\n", s->getName().str().c_str());
        }

        std::vector<const llvm::StructLayout*> exportedStructLayouts;
        for(auto& s : irModule.structs)
        {
            auto structType = llvm::StructType::getTypeByName(*ctx, s.name);
            if(!structType)
                throw std::runtime_error("Module load failed, unable to find struct metadata: " + s.name);
            const llvm::StructLayout* structLayout = _layout->getStructLayout(structType);
            exportedStructLayouts.push_back(structLayout);
        }

        if(llvm::Error res = _transformLayer->add(
               module->rt, llvm::orc::ThreadSafeModule(std::move(*deserializedModule), std::move(ctx))))
            throw std::runtime_error("Unable to add script: " + toString(std::move(res)));

        for(auto& glob : irModule.globals)
        {
            auto globSymbol = _session->lookup({&lib}, (*_mangler)(glob.name));
            if(!globSymbol)
                throw std::runtime_error("Unable to find exported global: " + toString(globSymbol.takeError()));
            module->globalNames.insert({glob.name, module->globalVars.size()});
            module->globalVars.push_back((void*)globSymbol->getAddress());
        }

        for(auto& func : irModule.functions)
        {
            auto functionSym = _session->lookup({&lib}, (*_mangler)(func.name));
            if(!functionSym)
                throw std::runtime_error("Unable to find exported function: " + toString(functionSym.takeError()));
            module->functionNames.insert({func.name, module->functions.size()});
            module->functions.push_back((void*)functionSym->getAddress());
        }

        auto constructor = _session->lookup({&lib}, (*_mangler)("_construct"));
        if(constructor)
            FuncRef<void>(constructor->getAddress())();

        auto destructor = _session->lookup({&lib}, (*_mangler)("_construct"));
        if(destructor)
            module->destructor = FuncRef<void>(destructor->getAddress());


        std::unordered_map<std::string, std::unique_ptr<StructDef>> newStructs;
        //Extract all structs before populating members, so we can resolve out of order dependencies.

        for(auto& s : irModule.structs)
        {
            auto sConstructor = module->getFunction<void, void*>(s.constructorSig);
            auto sDestructor = module->getFunction<void, void*>(s.destructorSig);
            auto sCopyConstructor = module->getFunction<void, void*, const void*>(s.copyConstructorSig);
            auto sMoveConstructor = module->getFunction<void, void*, void*>(s.moveConstructorSig);
            if(!sConstructor || !sDestructor || !sCopyConstructor || !sMoveConstructor)
                throw std::runtime_error("Module load failed, missing constructors for: " + s.name);
            newStructs.emplace(s.name,
                               new StructDef(s.name, sConstructor, sCopyConstructor, sMoveConstructor, sDestructor));
        }

        for(auto& ns : newStructs)
        {
            if(_types.contains(ns.first))
                throw std::runtime_error("Module load failed, cannot load a type twice: " + ns.first);
            _types.insert({ns.first, ns.second.get()});
        }

        size_t structIndex = 0;
        for(auto& ns : newStructs)
        {
            auto structLayout = exportedStructLayouts[structIndex];
            auto& srcStruct = irModule.structs[structIndex];
            ns.second->size = structLayout->getSizeInBytes();
            for(size_t i = 0; i < srcStruct.members.size(); i++)
            {
                auto& src = srcStruct.members[i];
                auto memberOffset = structLayout->getElementOffset(i);
                auto memberType = _types.find(src.type);
                if(memberType == _types.end())
                    throw std::runtime_error("Module load failed, unable to find type metadata: " + src.type);
                ns.second->memberVars.push_back(StructVar{src.name, VarType{memberType->second, src.isRef}, memberOffset});
            }

            printf("Adding struct %s\n", ns.first.c_str());
            printf("Size: %zu\n", ns.second->size);
            printf("Members:\n");
            for(auto& m : ns.second->memberVars)
                printf("  %s %s, offset: %zu\n", m.type.def->name.c_str(), m.name.c_str(), m.offset);

            module->structDefinitions.insert({ns.first, std::move(ns.second)});
            ++structIndex;
        }

        _modules.insert(irModule.id, module);
        for(auto& dep : irModule.links)
            _modules.addDependency(irModule.id, dep);

        return _modules.at(irModule.id);
    }

    void ScriptRuntime::unloadModule(const std::string& id)
    {
        // TODO assert that no scripts depend on this one
        assert(_modules.contains(id));
        auto module = _modules.at(id);
        for(auto& s : module->structDefinitions)
            _types.erase(s.first);
        _modules.erase(id);
    }

    ScriptRuntime::~ScriptRuntime() { _modules.clear(); }

    llvm::orc::JITDylib& ScriptRuntime::loadLibrary(NativeLibrary&& lib)
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

        auto nativeModule = new Module(newLib);
        for(auto& structDef : lib.structDefinitions)
        {
            if(_types.contains(structDef->name))
                throw std::runtime_error("Cannot load a struct multiple times: " + structDef->name);
            _types.insert({structDef->name, structDef.get()});
            nativeModule->structDefinitions.insert({structDef->name, std::move(structDef)});
        }
        _modules.insert(lib.identifier, nativeModule);
        return newLib;
    }

    int64_t ScriptRuntime::mallocDiff() const { return _scriptMallocDiff; }

    void ScriptRuntime::resetMallocDiff() { _scriptMallocDiff = 0; }

    VarType ScriptRuntime::getVarType(llvm::Type* type) const
    {
        VarType output;
        if(type->isPointerTy())
        {
            output = getVarType(type->getPointerElementType());
            output.isRef = true;
            return output;
        }
        if(type->isStructTy())
        {
            auto structType = _types.find(type->getStructName().str());
            if(structType == _types.end())
                return output;
            output.def = structType->second;
            return output;
        }
        if(type->isIntegerTy())
        {
            switch(type->getScalarSizeInBits())
            {
                case 1:
                    output.def = _types.at("bool");
                    return output;
                case 8:
                    output.def = _types.at("char");
                    return output;
                case 32:
                    output.def = _types.at("int");
                    return output;
                case 64:
                    output.def = _types.at("int64");
                    return output;
            }
            assert(false);
            return output;
        }
        if(type->isFloatTy())
        {
            switch(type->getScalarSizeInBits())
            {
                case 32:
                output.def = _types.at("float");
                return output;
                case 64:
                output.def = _types.at("double");
                return output;
            }
            assert(false);
            return output;
        }
        assert(false);
        return output;
    }

} // namespace BraneScript
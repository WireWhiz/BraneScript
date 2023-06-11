//
// Created by wirewhiz on 1/23/23.
//

#include "documentContext.h"
#include <cassert>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/Host.h"
#include "llvm/Transforms/Scalar.h"

namespace BraneScript
{
    template<typename T, typename Arg>
    T* assertCast(Arg* arg)
    {
        T* result = dynamic_cast<T*>(arg);
        assert(result);
        return result;
    }

    Identifier::operator std::string&() { return text; }

    bool Identifier::operator==(const Identifier& o) const { return text == o.text; }

    bool Identifier::operator!=(const Identifier& o) const { return text == o.text; }

    bool TypeContext::operator==(const TypeContext& o) const
    {
        if(structCtx)
            return structCtx == o.structCtx;
        return identifier == o.identifier && storageType == o.storageType;
    }

    bool TypeContext::operator!=(const TypeContext& o) const
    {
        if(structCtx)
            return structCtx != o.structCtx;
        return identifier != o.identifier || storageType != o.storageType;
    }

    bool TypeContext::isScalar() const
    {
        return ValueType::Scalar_Begin <= storageType && storageType <= ValueType::Scalar_End;
    }

    bool TypeContext::isUnsigned() const
    {
        return ValueType::Unsigned_Begin <= storageType && storageType <= ValueType::Unsigned_End;
    }

    bool TypeContext::isInt() const { return ValueType::Int_Begin <= storageType && storageType <= ValueType::Int_End; }

    bool TypeContext::isFloat() const
    {
        return ValueType::Float_Begin <= storageType && storageType <= ValueType::Float_End;
    }

    uint8_t TypeContext::size() const
    {
        switch(storageType)
        {
            case ValueType::Void:
            case ValueType::Bool:
            case ValueType::Char:
                return 1;
            case ValueType::UInt32:
            case ValueType::Int32:
            case ValueType::Float32:
                return 4;
            case ValueType::UInt64:
            case ValueType::Int64:
            case ValueType::Float64:
                return 8;
            case ValueType::Struct:
            case ValueType::FuncRef:
                return sizeof(void*); // Not too important, these values are mostly used for casting cost calculations
        }
        return 1;
    }

    bool ValueContext::operator==(const ValueContext& o) const
    {
        if(type != o.type)
            return false;
        if(isConst != o.isConst)
            return false;
        if(isRef != o.isRef)
            return false;
        return true;
    }

    bool ValueContext::operator!=(const ValueContext& o) const
    {
        if(type != o.type)
            return true;
        if(isConst != o.isConst)
            return true;
        if(isRef != o.isRef)
            return true;
        return false;
    }

    ValueContext& ValueContext::operator=(const LabeledValueContext& o)
    {
        assert(o.type.storageType != ValueType::Struct || o.type.structCtx);
        type = o.type;
        isConst = o.isConst;
        isRef = o.isRef;
        isLValue = o.isLValue;
        return *this;
    }

    ASTContext::ASTContext(llvm::LLVMContext* llvmCtx, std::string moduleSource) : llvmCtx(llvmCtx), builder(*llvmCtx)
    {
        module = std::make_unique<llvm::Module>(std::move(moduleSource), *llvmCtx);
    }

    llvm::StructType* ASTContext::getStructDef(const StructContext* structCtx)
    {
        std::string id = structCtx->longId();
        auto definedStruct = definedStructs.find(id);
        if(definedStruct != definedStructs.end())
            return definedStruct->second.llvmType;

        StructEntry entry;
        std::vector<llvm::Type*> llvmTypes;
        llvmTypes.reserve(1);
        entry.def.name = id;
        entry.def.constructorSig = structCtx->constructor->signature();
        entry.def.destructorSig = structCtx->destructor->signature();
        entry.def.copyConstructorSig = structCtx->copyConstructor->signature();
        entry.def.moveConstructorSig = structCtx->moveConstructor->signature();
        for(auto& m : structCtx->variables)
        {
            IRStructDef::Member newM;
            if(m->type.storageType != ValueType::FuncRef)
                newM.name = m->identifier;
            else
                newM.name = "FuncRef";
            newM.type = m->type.identifier;
            newM.isRef = m->isRef;
            entry.def.members.push_back(std::move(newM));
            llvmTypes.push_back(getLLVMType(*m));
        }
        entry.def.tags = structCtx->tags;
        entry.exported = module->getName().equals(structCtx->getParent<ModuleContext>()->identifier.text);

        llvm::StructType* st;
        if(llvmTypes.empty())
            st = llvm::StructType::create(*llvmCtx, id);
        else
            st = llvm::StructType::create(llvmTypes, id, structCtx->packed);

        entry.llvmType = st;

        definedStructs.insert({std::move(id), std::move(entry)});
        if(dBuilder)
        {
            llvm::SmallVector<llvm::Metadata*, 8> members;
            auto& source = structCtx->getLast<const ScriptContext>()->source;
            auto* sourceFile = dBuilder->createFile(module->getSourceFileName(), module->getSourceFileName());
            size_t structSize = 0;
            size_t largestAlignment = 0;

            for(auto& m : structCtx->variables)
            {
                auto* type = getDebugType(*m);
                auto typeSize = type->getSizeInBits();
                auto padding = structSize % typeSize;
                if(padding)
                    structSize += typeSize - padding;
                members.push_back(dBuilder->createMemberType(diFile,
                                                             m->identifier.text,
                                                             diFile,
                                                             m->range.start.line,
                                                             typeSize,
                                                             type->getAlignInBits(),
                                                             structSize,
                                                             llvm::DINode::DIFlags::FlagZero,
                                                             type));
                if(type->getAlignInBits() > largestAlignment)
                    largestAlignment = type->getAlignInBits();
                structSize += typeSize;
            }
            if(largestAlignment)
            {
                auto padding = structSize % largestAlignment;
                if(padding)
                    structSize += largestAlignment - padding;
            }
            auto* dStruct = dBuilder->createStructType(diFile,
                                                       structCtx->identifier.text,
                                                       diFile,
                                                       structCtx->range.start.line,
                                                       structSize,
                                                       largestAlignment,
                                                       llvm::DINode::DIFlags::FlagZero,
                                                       nullptr,
                                                       dBuilder->getOrCreateArray(members));
            debugTypes.insert({structCtx->longId(), dStruct});
        }

        return st;
    }

    llvm::Type* ASTContext::getLLVMType(const ValueContext& valueCtx)
    {
        if(valueCtx.type.structCtx)
        {
            llvm::Type* type = getStructDef(valueCtx.type.structCtx);
            if(valueCtx.isRef)
                type = llvm::PointerType::get(type, 0);
            return type;
        }

        switch(valueCtx.type.storageType)
        {
            case ValueType::Void:
                if(valueCtx.isRef)
                    return llvm::PointerType::get(llvm::Type::getInt32Ty(*llvmCtx), 0);
                else
                    return llvm::Type::getVoidTy(*llvmCtx);
            case ValueType::Bool:
                if(valueCtx.isRef)
                    return llvm::Type::getInt1PtrTy(*llvmCtx);
                else
                    return llvm::Type::getInt1Ty(*llvmCtx);
            case ValueType::Char:
                if(valueCtx.isRef)
                    return llvm::Type::getInt8PtrTy(*llvmCtx);
                else
                    return llvm::Type::getInt8Ty(*llvmCtx);
            case ValueType::UInt32:
            case ValueType::Int32:
                if(valueCtx.isRef)
                    return llvm::Type::getInt32PtrTy(*llvmCtx);
                else
                    return llvm::Type::getInt32Ty(*llvmCtx);
            case ValueType::Int64:
            case ValueType::UInt64:
                if(valueCtx.isRef)
                    return llvm::Type::getInt64PtrTy(*llvmCtx);
                else
                    return llvm::Type::getInt64Ty(*llvmCtx);
            case ValueType::Float32:
                if(valueCtx.isRef)
                    return llvm::Type::getFloatPtrTy(*llvmCtx);
                else
                    return llvm::Type::getFloatTy(*llvmCtx);
            case ValueType::Float64:
                if(valueCtx.isRef)
                    return llvm::Type::getDoublePtrTy(*llvmCtx);
                else
                    return llvm::Type::getDoubleTy(*llvmCtx);
            case ValueType::FuncRef:
                return llvm::Type::getInt32PtrTy(*llvmCtx);
            default:
                throw std::runtime_error("Invalid type requested");
        }
    }

    std::function<llvm::GlobalVariable*()> ASTContext::makeGlobalVariable(LabeledValueContext& valueContext,
                                                                          bool shouldExport)
    {
        return [this, &valueContext, shouldExport]() -> llvm::GlobalVariable* {
            auto* type = getLLVMType(valueContext);
            std::string id = valueContext.longId();
            auto linkage = llvm::GlobalVariable::ExternalLinkage;
            if(shouldExport)
                exportedGlobals.push_back({id, valueContext.signature()});
            return new llvm::GlobalVariable(*module, type, false, linkage, llvm::UndefValue::get(type), id);
        };
    }

    std::function<llvm::GlobalVariable*()> ASTContext::makeExternGlobalVariable(LabeledValueContext& valueContext)
    {
        return [this, &valueContext]() -> llvm::GlobalVariable* {
            auto* type = getLLVMType(valueContext);
            return new llvm::GlobalVariable(*module,
                                            type,
                                            false,
                                            llvm::GlobalVariable::AvailableExternallyLinkage,
                                            llvm::UndefValue::get(type),
                                            valueContext.longId());
        };
    }

    void ASTContext::pushScope() { scopes.emplace_back(); }

    void ASTContext::popScope() { scopes.pop_back(); }

    llvm::Value* ASTContext::findValue(const std::string& id)
    {
        for(auto itr = scopes.rbegin(); itr != scopes.rend(); ++itr)
        {
            auto value = itr->values.find(id);
            if(value != itr->values.end())
                return value->second.value;
        }
        auto globVar = globals.find(id);
        if(globVar != globals.end())
            return globVar->second;
        assert(false);
        return nullptr;
    }

    bool ASTContext::setValue(llvm::Value* old, llvm::Value* newValue)
    {
        for(auto itr = scopes.rbegin(); itr != scopes.rend(); ++itr)
        {
            for(auto& value : itr->values)
            {
                if(value.second.value == old)
                {
                    value.second.value = newValue;
                    return true;
                }
            }
        }
        return false;
    }

    void ASTContext::addValue(std::string id, llvm::Value* value, ValueContext context)
    {
        scopes.back().values.insert({std::move(id), {value, std::move(context)}});
    }

    void ASTContext::addValue(llvm::Value* value, ValueContext context)
    {
        scopes.back().unnamedValues.push_back({value, std::move(context)});
    }

    void ASTContext::setInsertPoint(llvm::BasicBlock* block)
    {
        currentBlock = block;
        builder.SetInsertPoint(block);
    }

    void ASTContext::printModule() const
    {
        std::string moduleText;
        llvm::raw_string_ostream moduleTextStr(moduleText);
        module->print(moduleTextStr, nullptr, true, false);
        printf("%s", moduleTextStr.str().c_str());
    }

    llvm::Value* ASTContext::dereferenceToDepth(llvm::Value* value, size_t maxPointerDepth)
    {
        assert(value);
        if(value->getType()->isOpaquePointerTy())
            return value;
        size_t currentDepth = pointerDepth(value->getType());
        assert(currentDepth >= maxPointerDepth);
        while(currentDepth > maxPointerDepth)
        {
            value = builder.CreateLoad(value->getType()->getContainedType(0), value);
            currentDepth--;
        }
        return value;
    }

    void ASTContext::destructStack(bool onlyLocal)
    {
        auto argScope = --scopes.rend();
        for(auto itr = scopes.rbegin(); itr != argScope; ++itr)
        {
            for(auto& value : itr->values)
            {
                if(value.second.context.isRef)
                    continue;
                if(!value.second.context.type.structCtx)
                    continue;
                auto destructorFunc = functions.find(value.second.context.type.structCtx->destructor->signature());
                assert(destructorFunc != functions.end());
                builder.CreateCall(destructorFunc->second, {value.second.value});
            }
            for(auto& value : itr->unnamedValues)
            {
                if(value.context.isRef)
                    continue;
                if(!value.context.type.structCtx)
                    continue;
                auto destructorFunc = functions.find(value.context.type.structCtx->destructor->signature());
                assert(destructorFunc != functions.end());
                builder.CreateCall(destructorFunc->second, {value.value});
            }
            if(onlyLocal)
                break;
        }
    }

    size_t ASTContext::pointerDepth(llvm::Type* type)
    {
        if(!type->isPointerTy())
            return 0;
        if(type->isOpaquePointerTy())
            return 1;
        return 1 + pointerDepth(type->getContainedType(0));
    }

    // Passing value context as value is intentional here to make sure .signature() does not inclulde a variable name
    llvm::DIType* ASTContext::getDebugType(ValueContext valueCtx)
    {
        valueCtx.isConst = false;
        std::string sig = valueCtx.signature();
        auto itr = debugTypes.find(sig);
        if(itr != debugTypes.end())
            return itr->second;

        if(valueCtx.isRef)
        {
            auto baseType = valueCtx;
            baseType.isRef = false;
            auto* type = getDebugType(baseType);
            auto* debugType = dBuilder->createPointerType(type, sizeof(void*) * 8);
            debugTypes.insert({sig, debugType});
            return debugType;
        }

        if(valueCtx.type.storageType == ValueType::FuncRef)
        {
            auto* debugType = dBuilder->createPointerType(debugTypes.at("void"), sizeof(void*) * 8);
            debugTypes.insert({sig, debugType});
            return debugType;
        }
        assert(false);
        return nullptr;
    }

    void ASTContext::setDebugScope(llvm::DIScope* scope)
    {
        assert(!scopes.empty());
        assert(!scopes.back().debugScope);
        scopes.back().debugScope = scope;
    }

    llvm::DIScope* ASTContext::debugScope() const
    {
        for(auto itr = scopes.rbegin(); itr != scopes.rend(); ++itr)
        {
            auto scope = itr->debugScope;
            if(scope)
                return scope;
        }
        return diCompileUnit;
    }

    void ASTContext::setDebugLocation(const StatementContext* ctx)
    {
        if(!dBuilder)
            return;
        if(!ctx)
        {
            builder.SetCurrentDebugLocation(llvm::DebugLoc());
            return;
        }
        auto scope = debugScope();
        builder.SetCurrentDebugLocation(
            llvm::DILocation::get(scope->getContext(), ctx->range.start.line + 1, ctx->range.start.charPos, scope));
    }

    ASTContext::~ASTContext() = default;

    DocumentContext* DocumentContext::getNodeAtChar(TextPos pos)
    {
        if(range.posInRange(pos))
            return this;
        return nullptr;
    }

    DocumentContext* DocumentContext::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        if(!parent || searchOptions & IDSearchOptions_ChildrenOnly)
            return nullptr;
        return parent->findIdentifier(identifier, searchOptions);
    }

    void DocumentContext::getFunction(const std::string& identifier,
                                      FunctionOverridesContext* overrides,
                                      uint8_t searchOptions)
    {
        if(parent && !(searchOptions & IDSearchOptions_ChildrenOnly))
            parent->getFunction(identifier, overrides, searchOptions);
    }

    std::string DocumentContext::longId() const
    {
        if(!parent)
            return "";
        return parent->longId();
    }

    void DocumentContext::copyBase(const DocumentContext* src, DocumentContext* dest) const
    {
        dest->range = src->range;
        dest->version = src->version;
    }

    DocumentContext* DocumentContext::deepCopy() const
    {
        return deepCopy([](auto _) { return _; });
    }

    DocumentContext* DocumentContext::findIdentifier(const std::string& identifier)
    {
        return findIdentifier(identifier, 0);
    }

    void DocumentContext::getFunction(const std::string& identifier, FunctionOverridesContext* overrides)
    {
        getFunction(identifier, overrides, 0);
    }

    std::string ValueContext::signature() const
    {
        std::string sig;
        if(isConst)
            sig += "const ";
        if(isRef)
            sig += "ref ";
        sig += type.identifier;
        return sig;
    }

    ValueContext::ValueContext(const LabeledValueContext& o)
    {
        type = o.type;
        isConst = o.isConst;
        isRef = o.isRef;
    }

    bool ValueContext::sameBaseType(const ValueContext& o) const
    {
        if(type.identifier != o.type.identifier)
            return false;
        return isRef == o.isRef;
    }

    uint32_t ValueContext::castCost(const ValueContext& target) const
    {
        /* Costs subject to change, I just threw random values here. Generally I went with lower costs on things
         * that preserve data, and much higher costs on things that have a chance of loosing data.
         */

        uint32_t cost = 0;
        // Very minor cost to dereferencing, since we want to favor references
        if(isRef && !target.isRef)
            cost += 1;
        // Prefer to keep things mutable if possible
        if(!isConst && target.isConst)
            cost += 1;

        // Prefer up-casting to down-casting
        if(type.size() < target.type.size())
            cost += 2;
        else if(type.size() > target.type.size())
            cost += 20;

        // Prefer casting from unsigned integers to signed integers over casts to floats, but prefer casting signed
        // ints to floats
        if(type.isUnsigned() && !target.type.isUnsigned())
            cost += 7;
        else if(!type.isUnsigned() && target.type.isUnsigned())
            cost += 15;
        if(type.isInt() && target.type.isFloat())
            cost += 7;
        // Avoid casts from floats to ints like the plague (when implicit)
        if(type.isFloat() && target.type.isInt())
            cost += 30;
        return cost;
    }

    ValueContext::ValueContext(TypeContext type, bool isLValue, bool isConst, bool isRef)
    {
        this->type = std::move(type);
        this->isLValue = isLValue;
        this->isConst = isConst;
        this->isRef = isRef;
    }

    std::string LabeledValueContext::signature() const { return ValueContext::signature() + " " + identifier.text; }

    std::string LabeledValueContext::longId() const
    {
        if(parent && getParent<FunctionContext>())
            return identifier.text;
        auto prefix = DocumentContext::longId();
        if(prefix.empty())
            return identifier.text;
        return prefix + "::" + identifier.text;
    }

    DocumentContext*
    LabeledValueContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new LabeledValueContext(*this));
    }

    LabeledValueContext::LabeledValueContext(std::string identifier, ValueContext value) : ValueContext(value)
    {
        assert(value.type.storageType != ValueType::Struct || value.type.structCtx);
        this->identifier.text = std::move(identifier);
    }

    llvm::Value* LabeledValueContext::createAST(ASTContext& ctx) const
    {
        assert(false);
        return nullptr;
    }

    DocumentContext*
    StatementErrorContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new StatementErrorContext{*this});
    }

    bool StatementErrorContext::isConstexpr() const { return false; }

    llvm::Value* StatementErrorContext::createAST(ASTContext& ctx) const
    {
        assert(false);
        return nullptr;
    }

    DocumentContext*
    ExpressionErrorContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new ExpressionErrorContext{*this});
    }

    bool ExpressionErrorContext::isConstexpr() const { return false; }

    llvm::Value* ExpressionErrorContext::createAST(ASTContext& ctx) const { return nullptr; }

    void ExpressionContext::copyBase(const DocumentContext* src, DocumentContext* dest) const
    {
        DocumentContext::copyBase(src, dest);
        auto srcExpr = (ExpressionContext*)src;
        auto destExpr = (ExpressionContext*)dest;
        destExpr->returnType = srcExpr->returnType;
    }

    DocumentContext* ScopeContext::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        for(auto& lv : localVariables)
        {
            if(lv->identifier.text == identifier)
                return lv.get();
        }
        return DocumentContext::findIdentifier(identifier, searchOptions);
    }

    llvm::Value* ScopeContext::createAST(ASTContext& ctx) const
    {
        ctx.pushScope();
        if(!ctx.currentBlock)
            ctx.setInsertPoint(llvm::BasicBlock::Create(*ctx.llvmCtx, "", ctx.func));
        if(ctx.dBuilder)
        {
            auto newScope = ctx.dBuilder->createLexicalBlock(
                ctx.debugScope(), ctx.diFunction->getFile(), range.start.line, range.start.charPos);
            ctx.setDebugScope(newScope);
            ctx.setDebugLocation(this);
        }
        size_t varIndex = 0;
        for(auto& var : localVariables)
        {
            auto varValue = ctx.builder.CreateAlloca(ctx.getLLVMType(*var), nullptr, var->identifier.text);
            ctx.addValue(var->identifier.text, varValue, *var);
            if(ctx.dBuilder)
            {
                auto* dType = ctx.getDebugType(*var);
                auto line = var->range.start.line;
                auto charPos = var->range.start.charPos;
                llvm::DILocalVariable* dVar = ctx.dBuilder->createAutoVariable(
                    ctx.debugScope(), var->identifier.text, ctx.diFunction->getFile(), line, dType, true);

                // TODO move this to where the variable is declared in the grammar to make debug info cleaner
                ctx.dBuilder->insertDeclare(
                    varValue,
                    dVar,
                    ctx.dBuilder->createExpression(),
                    llvm::DILocation::get(ctx.debugScope()->getContext(), line, charPos, ctx.debugScope()),
                    ctx.currentBlock);
            }
        }
        for(auto& expression : expressions)
        {
            if(!ctx.currentBlock)
                ctx.setInsertPoint(llvm::BasicBlock::Create(*ctx.llvmCtx, "", ctx.func));
            expression->createAST(ctx);
        }
        if(ctx.currentBlock)
            ctx.destructStack(true);
        ctx.popScope();
        return nullptr;
    }

    DocumentContext* ScopeContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new ScopeContext{};
        copyBase(this, copy);
        for(auto& var : localVariables)
        {
            auto varCopy = assertCast<LabeledValueContext>(var->deepCopy(callback));
            varCopy->parent = copy;
            copy->localVariables.emplace_back(varCopy);
        }
        for(auto& stmt : expressions)
        {
            auto stmtCopy = assertCast<StatementContext>(stmt->deepCopy(callback));
            stmtCopy->parent = copy;
            copy->expressions.emplace_back(stmtCopy);
        }
        return callback(copy);
    }

    bool ScopeContext::isConstexpr() const
    {
        for(auto& stmt : expressions)
            if(!stmt->isConstexpr())
                return false;
        return true;
    }

    DocumentContext* ReturnContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new ReturnContext{};
        copyBase(this, copy);
        copy->value.reset(assertCast<ExpressionContext>(value->deepCopy(callback)));
        copy->value->parent = copy;
        return callback(copy);
    }

    bool ReturnContext::isConstexpr() const { return value->isConstexpr(); }

    llvm::Value* ReturnContext::createAST(ASTContext& ctx) const
    {
        if(!value)
        {
            assert(ctx.func->getReturnType()->isVoidTy());
            ctx.destructStack();
            ctx.currentBlock = nullptr;
            ctx.setDebugLocation(this);
            return ctx.builder.CreateRetVoid();
        }

        // TEMPORARY WORKAROUND until we have a proper metaprogramming system
        if(value->returnType.type.storageType == ValueType::Void)
        {
            assert(ctx.func->getReturnType()->isVoidTy());
            value->createAST(ctx);
            ctx.destructStack();
            ctx.currentBlock = nullptr;
            ctx.setDebugLocation(this);
            return ctx.builder.CreateRetVoid();
        }

        auto parentFunc = getParent<FunctionContext>();
        assert(parentFunc);
        auto retValue = value->createAST(ctx);
        ctx.setDebugLocation(this);
        assert(retValue);
        if(!parentFunc->returnType.isRef && parentFunc->returnType.type.structCtx)
        {
            assert(ctx.func->getReturnType()->isVoidTy());
            // If we are returning a value from a function, it will have detected this node as a parent and returned
            // the value directly.
            if(value->is<FunctionCallContext>())
            {
                ctx.destructStack();
                ctx.currentBlock = nullptr;
                ctx.setDebugLocation(this);
                return ctx.builder.CreateRetVoid();
            }
            auto retRef = ctx.findValue("-retRef");
            assert(retRef);

            auto copy = ctx.functions.find(parentFunc->returnType.type.structCtx->copyConstructor->signature());
            assert(copy != ctx.functions.end());

            std::vector<llvm::Value*> args = {retRef, ctx.dereferenceToDepth(retValue, 1)};
            ctx.builder.CreateCall(copy->second, args);
            ctx.destructStack();
            ctx.setDebugLocation(this);
            ctx.builder.CreateRetVoid();
            ctx.currentBlock = nullptr;
            return nullptr;
        }

        assert(!ctx.func->getReturnType()->isVoidTy());
        bool isRefType = parentFunc->returnType.isRef || parentFunc->returnType.type.storageType == ValueType::FuncRef;
        retValue = ctx.dereferenceToDepth(retValue, isRefType ? 1 : 0);
        assert(retValue->getType() == ctx.func->getReturnType());

        ctx.destructStack();
        ctx.setDebugLocation(this);
        ctx.builder.CreateRet(retValue);
        ctx.currentBlock = nullptr;
        return nullptr;
    }

    DocumentContext* IfContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new IfContext{};
        copyBase(this, copy);
        copy->condition.reset(assertCast<ExpressionContext>(condition->deepCopy(callback)));
        copy->condition->parent = copy;
        copy->body.reset(assertCast<StatementContext>(body->deepCopy(callback)));
        copy->condition->parent = copy;
        if(elseBody)
        {
            copy->elseBody.reset(assertCast<StatementContext>(elseBody->deepCopy(callback)));
            copy->elseBody->parent = copy;
        }
        return callback(copy);
    }

    bool IfContext::isConstexpr() const
    {
        if(elseBody && !elseBody->isConstexpr())
            return false;
        return condition->isConstexpr() && body->isConstexpr();
    }

    llvm::Value* IfContext::createAST(ASTContext& ctx) const
    {
        auto* cond = ctx.dereferenceToDepth(condition->createAST(ctx), 0);
        assert(cond->getType()->getIntegerBitWidth() == 1);

        llvm::BasicBlock* trueBranch = llvm::BasicBlock::Create(*ctx.llvmCtx, "", ctx.func);
        llvm::BasicBlock* mergeBlock = elseBody ? nullptr : llvm::BasicBlock::Create(*ctx.llvmCtx, "", ctx.func);
        llvm::BasicBlock* falseBranch = elseBody ? llvm::BasicBlock::Create(*ctx.llvmCtx, "", ctx.func) : mergeBlock;

        ctx.builder.CreateCondBr(cond, trueBranch, falseBranch);
        ctx.setInsertPoint(trueBranch);
        body->createAST(ctx);
        if(ctx.currentBlock)
        {
            if(!mergeBlock)
                mergeBlock = llvm::BasicBlock::Create(*ctx.llvmCtx, "", ctx.func);
            ctx.builder.CreateBr(mergeBlock);
        }

        if(elseBody)
        {
            ctx.setInsertPoint(falseBranch);
            elseBody->createAST(ctx);
            if(ctx.currentBlock)
            {
                if(!mergeBlock)
                    mergeBlock = llvm::BasicBlock::Create(*ctx.llvmCtx, "", ctx.func);
                ctx.builder.CreateBr(mergeBlock);
            }
        }

        if(mergeBlock)
            ctx.setInsertPoint(mergeBlock);

        return nullptr;
    }

    llvm::Value* WhileContext::createAST(ASTContext& ctx) const
    {

        auto* header = llvm::BasicBlock::Create(*ctx.llvmCtx, "whileHeader", ctx.func);
        auto* bodyBlock = llvm::BasicBlock::Create(*ctx.llvmCtx, "whileBody", ctx.func);
        auto* end = llvm::BasicBlock::Create(*ctx.llvmCtx, "whileEnd", ctx.func);

        ctx.builder.CreateBr(header);
        ctx.setInsertPoint(header);

        auto* cond = condition->createAST(ctx);
        ctx.builder.CreateCondBr(cond, bodyBlock, end);

        ctx.setInsertPoint(bodyBlock);
        body->createAST(ctx);
        ctx.builder.CreateBr(header);

        ctx.setInsertPoint(end);

        return nullptr;
    }

    DocumentContext* WhileContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new WhileContext{};
        copyBase(this, copy);
        copy->condition.reset(assertCast<ExpressionContext>(condition->deepCopy(callback)));
        copy->condition->parent = copy;
        copy->body.reset(assertCast<StatementContext>(body->deepCopy(callback)));
        copy->body->parent = copy;
        return callback(copy);
    }

    bool WhileContext::isConstexpr() const { return condition->isConstexpr() && body->isConstexpr(); }

    bool ForContext::isConstexpr() const
    {
        return init->isConstexpr() && condition->isConstexpr() && step->isConstexpr() && body->isConstexpr();
    }

    llvm::Value* ForContext::createAST(ASTContext& ctx) const
    {
        auto* header = llvm::BasicBlock::Create(*ctx.llvmCtx, "forHeader", ctx.func);
        auto* bodyBlock = llvm::BasicBlock::Create(*ctx.llvmCtx, "forBody", ctx.func);
        auto* end = llvm::BasicBlock::Create(*ctx.llvmCtx, "forEnd", ctx.func);

        init->createAST(ctx);
        ctx.builder.CreateBr(header);
        ctx.setInsertPoint(header);

        auto* cond = condition->createAST(ctx);
        ctx.builder.CreateCondBr(cond, bodyBlock, end);

        ctx.setInsertPoint(bodyBlock);
        body->createAST(ctx);
        step->createAST(ctx);
        ctx.builder.CreateBr(header);

        ctx.setInsertPoint(end);
        return nullptr;
    }

    DocumentContext* ForContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto copy = new ForContext{};
        copyBase(this, copy);
        copy->init.reset(assertCast<StatementContext>(init->deepCopy(callback)));
        copy->init->parent = copy;
        copy->condition.reset(assertCast<ExpressionContext>(condition->deepCopy(callback)));
        copy->condition->parent = copy;
        copy->step.reset(assertCast<StatementContext>(step->deepCopy(callback)));
        copy->step->parent = copy;
        copy->body.reset(assertCast<StatementContext>(body->deepCopy(callback)));
        copy->body->parent = copy;
        return callback(copy);
    }

    llvm::Value* AssignmentContext::createAST(ASTContext& ctx) const
    {
        llvm::Value* l = ctx.dereferenceToDepth(lValue->createAST(ctx),
                                                lValue->returnType.type.storageType == ValueType::FuncRef ? 2 : 1);
        llvm::Value* r = rValue->createAST(ctx);

        assert(l->getType()->isPointerTy());
        if(!lValue->returnType.type.structCtx)
        {
            r = ctx.dereferenceToDepth(r, lValue->returnType.type.storageType == ValueType::FuncRef ? 1 : 0);
            assert(l->getType()->getContainedType(0) == r->getType());
            ctx.setDebugLocation(this);
            ctx.builder.CreateStore(r, l);
            return l;
        }

        auto cc = ctx.functions.find(lValue->returnType.type.structCtx->copyConstructor->signature());
        assert(cc != ctx.functions.end());
        assert(cc->second->arg_size() == 2);
        auto structPointerType = lValue->returnType;
        structPointerType.isRef = true;

        std::vector<llvm::Value*> args = {l, ctx.dereferenceToDepth(r, 1)};
        ctx.setDebugLocation(this);
        ctx.builder.CreateCall(cc->second, args);
        return l;
    }

    DocumentContext*
    AssignmentContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new AssignmentContext{};
        copyBase(this, copy);
        copy->lValue.reset(assertCast<ExpressionContext>(lValue->deepCopy(callback)));
        copy->lValue->parent = copy;
        copy->rValue.reset(assertCast<ExpressionContext>(rValue->deepCopy(callback)));
        copy->rValue->parent = copy;
        return callback(copy);
    }

    bool AssignmentContext::isConstexpr() const { return lValue->isConstexpr() && rValue->isConstexpr(); }

    AssignmentContext::AssignmentContext(ExpressionContext* lValue, ExpressionContext* rValue)
        : lValue(lValue), rValue(rValue)
    {
        assert(lValue && rValue);
        returnType = lValue->returnType;
    }

    void AssignmentContext::setArgs(ExpressionContext* lValue, ExpressionContext* rValue)
    {
        this->lValue.reset(lValue);
        this->rValue.reset(rValue);
        returnType = lValue->returnType;
    }

    bool RefAssignmentContext::isConstexpr() const { return false; }

    RefAssignmentContext::RefAssignmentContext(ExpressionContext* lValue, ExpressionContext* rValue)
        : lValue(lValue), rValue(rValue)
    {
        assert(lValue->returnType.isRef && (rValue->returnType.isLValue || rValue->returnType.isRef));
        returnType = lValue->returnType;
    }

    void RefAssignmentContext::setArgs(ExpressionContext* lValue, ExpressionContext* rValue)
    {
        assert((lValue->returnType.isRef || lValue->returnType.type.storageType == ValueType::FuncRef) &&
               (rValue->returnType.isLValue || rValue->returnType.isRef));
        this->lValue.reset(lValue);
        this->rValue.reset(rValue);
    }

    llvm::Value* RefAssignmentContext::createAST(ASTContext& ctx) const
    {
        ctx.setDebugLocation(this);
        llvm::Value* l = ctx.dereferenceToDepth(lValue->createAST(ctx), 2);
        llvm::Value* r = ctx.dereferenceToDepth(rValue->createAST(ctx), 1);

        ctx.builder.CreateStore(r, l);
        return l;
    }

    DocumentContext*
    RefAssignmentContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new RefAssignmentContext{};
        copyBase(this, copy);
        copy->lValue.reset(assertCast<ExpressionContext>(lValue->deepCopy(callback)));
        copy->lValue->parent = copy;
        copy->rValue.reset(assertCast<ExpressionContext>(rValue->deepCopy(callback)));
        copy->rValue->parent = copy;
        return callback(copy);
    }

    TypeSizeContext::TypeSizeContext(ValueContext value) : value(std::move(value))
    {
        returnType.type = {"", ValueType::UInt64};
    }

    llvm::Value* TypeSizeContext::createAST(ASTContext& ctx) const
    {
        auto* type = ctx.getLLVMType(value);
        auto nullValue = llvm::ConstantPointerNull::get(llvm::PointerType::get(type, 0));
        auto* offset = ctx.builder.CreateGEP(type, nullValue, llvm::ConstantInt::get(*ctx.llvmCtx, llvm::APInt(16, 1)));
        return ctx.builder.CreatePtrToInt(offset, ctx.getLLVMType(returnType), "typeSize");
    }

    bool TypeSizeContext::isConstexpr() const { return !value.isRef; }

    DocumentContext* TypeSizeContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new TypeSizeContext{*this});
    }

    ConstBoolContext::ConstBoolContext()
    {
        returnType.type = {"bool", ValueType::Bool};
        returnType.isConst = true;
    }

    DocumentContext* ConstBoolContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new ConstBoolContext{*this});
    }

    ConstBoolContext::ConstBoolContext(bool value) : ConstBoolContext() { this->value = value; }

    std::string ConstBoolContext::toString() const { return value ? "true" : "false"; }

    llvm::Value* ConstBoolContext::createAST(ASTContext& ctx) const
    {
        return llvm::ConstantInt::get(*ctx.llvmCtx, llvm::APInt(1, value));
    }

    ConstCharContext::ConstCharContext()
    {
        returnType.type = {"char", ValueType::Char};
        returnType.isConst = true;
    }

    DocumentContext* ConstCharContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new ConstCharContext{*this});
    }

    ConstCharContext::ConstCharContext(char value) : ConstCharContext() { this->value = value; }

    std::string ConstCharContext::toString() const { return std::to_string(value); }

    llvm::Value* ConstCharContext::createAST(ASTContext& ctx) const
    {
        return llvm::ConstantInt::get(*ctx.llvmCtx, llvm::APInt(8, value));
    }

    ConstIntContext::ConstIntContext()
    {
        returnType.type = {"int", ValueType::Int32};
        returnType.isConst = true;
    }

    DocumentContext* ConstIntContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new ConstIntContext{*this});
    }

    ConstIntContext::ConstIntContext(int value) : ConstIntContext() { this->value = value; }

    std::string ConstIntContext::toString() const { return std::to_string(value); }

    llvm::Value* ConstIntContext::createAST(ASTContext& ctx) const
    {
        return llvm::ConstantInt::get(*ctx.llvmCtx, llvm::APInt(32, value));
    }

    ConstFloatContext::ConstFloatContext()
    {
        returnType.type = {"float", ValueType::Float32};
        returnType.isConst = true;
    }

    DocumentContext*
    ConstFloatContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new ConstFloatContext{*this});
    }

    ConstFloatContext::ConstFloatContext(float value) : ConstFloatContext() { this->value = value; }

    std::string ConstFloatContext::toString() const { return std::to_string(value); }

    llvm::Value* ConstFloatContext::createAST(ASTContext& ctx) const
    {
        return llvm::ConstantFP::get(*ctx.llvmCtx, llvm::APFloat(value));
    }

    ConstStringContext::ConstStringContext(std::string value) : ConstStringContext() { this->value = value; }

    ConstStringContext::ConstStringContext()
    {
        returnType.type = {"string::string", ValueType::Struct};
        returnType.isLValue = true;
    }

    DocumentContext*
    ConstStringContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new ConstStringContext{*this});
    }

    std::string ConstStringContext::toString() const { return value; }

    llvm::Value* ConstStringContext::createAST(ASTContext& ctx) const
    {
        auto* str = ctx.builder.CreateGlobalStringPtr(value);
        auto* stringType = ctx.getLLVMType(returnType);
        if(!stringType)
            throw std::runtime_error("String library must be linked to use strings!");
        auto* tempString = ctx.builder.CreateAlloca(stringType);
        auto hiddenConstructor =
            ctx.module->getOrInsertFunction("string::stringFromCharArr(ref string::string, const ref char)",
                                            llvm::Type::getVoidTy(*ctx.llvmCtx),
                                            llvm::PointerType::get(stringType, 0),
                                            llvm::Type::getInt8PtrTy(*ctx.llvmCtx));

        ctx.builder.CreateCall(hiddenConstructor, {tempString, str});
        return tempString;
    }

    LabeledValueConstructionContext::LabeledValueConstructionContext(const LabeledValueContext& value)
    {
        identifier = value.longId();
        returnType = value;
    }

    bool LabeledValueConstructionContext::isConstexpr() const { return false; }

    DocumentContext*
    LabeledValueConstructionContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new LabeledValueConstructionContext{*this});
    }

    llvm::Value* LabeledValueConstructionContext::createAST(ASTContext& ctx) const
    {
        auto value = ctx.findValue(identifier);
        assert(value);
        if(!returnType.type.structCtx || returnType.isRef)
            return value;

        auto func = ctx.functions.find(returnType.type.structCtx->constructor->signature());
        assert(func != ctx.functions.end());
        assert(func->second->arg_size() == 1);

        auto structPointerType = returnType;
        structPointerType.isRef = true;

        assert(value->getType()->isPointerTy());
        std::vector<llvm::Value*> arg = {ctx.dereferenceToDepth(value, 1)};
        ctx.builder.CreateCall(func->second, arg);
        return value;
    }

    LabeledValueDestructionContext::LabeledValueDestructionContext(const LabeledValueContext& value)
    {
        identifier = value.longId();
        returnType = value;
    }

    bool LabeledValueDestructionContext::isConstexpr() const { return false; }

    llvm::Value* LabeledValueDestructionContext::createAST(ASTContext& ctx) const
    {
        auto value = ctx.findValue(identifier);
        assert(value);
        if(!returnType.type.structCtx)
            return value;

        auto func = ctx.functions.find(returnType.type.structCtx->destructor->signature());
        assert(func != ctx.functions.end());


        auto* valueRef =
            ctx.builder.CreateStructGEP(llvm::PointerType::get(value->getType(), 0), value, 0, "structPtr");
        std::vector<llvm::Value*> arg = {valueRef};
        return ctx.builder.CreateCall(func->second, arg);
    }

    DocumentContext*
    LabeledValueDestructionContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new LabeledValueDestructionContext{*this});
    }

    LabeledValueReferenceContext::LabeledValueReferenceContext(const LabeledValueContext& value)
    {
        identifier = value.longId();
        returnType = value;
    }

    DocumentContext*
    LabeledValueReferenceContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new LabeledValueReferenceContext{*this});
    }

    bool LabeledValueReferenceContext::isConstexpr() const { return false; }

    llvm::Value* LabeledValueReferenceContext::createAST(ASTContext& ctx) const { return ctx.findValue(identifier); }

    bool FunctionOverridesContext::isConstexpr() const { return false; }

    DocumentContext*
    FunctionOverridesContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto copy = new FunctionOverridesContext{};
        copy->thisRef = std::unique_ptr<ExpressionContext>((ExpressionContext*)thisRef->deepCopy());
        copy->overrides = overrides;
        copy->templates = templates;
        return callback(copy);
    }

    llvm::Value* FunctionOverridesContext::createAST(ASTContext& ctx) const
    {
        assert(false);
        return nullptr;
    }

    std::string FunctionOverridesContext::longId() const
    {
        if(overrides.empty())
            return "";
        return overrides[0]->identifier.text;
    }

    FunctionReferenceContext::FunctionReferenceContext(FunctionContext* function) : function(function)
    {
        std::string tempArgs = "<";
        tempArgs += function->returnType.signature() + (function->arguments.empty() ? "" : ",");
        for(auto arg = function->arguments.begin(); arg != function->arguments.end(); ++arg)
        {
            tempArgs += ValueContext(**arg).signature();
            if(arg + 1 != function->arguments.end())
                tempArgs += ",";
        }
        tempArgs += ">";

        returnType.type = {"FuncRef" + tempArgs, ValueType::FuncRef, nullptr};
    }

    bool FunctionReferenceContext::isConstexpr() const { return false; }

    llvm::Value* FunctionReferenceContext::createAST(ASTContext& ctx) const
    {
        ctx.setDebugLocation(this);
        auto func = ctx.functions.at(function->signature());
        return llvm::ConstantExpr::getBitCast(func, ctx.getLLVMType(returnType));
    }

    DocumentContext*
    FunctionReferenceContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new FunctionReferenceContext{*this});
    }

    MemberAccessContext::MemberAccessContext(ExpressionContext* base, StructContext* baseType, size_t member)
    {
        baseExpression.reset(base);
        assert(base->returnType.type.identifier == baseType->longId());
        assert(member < baseType->variables.size());
        returnType = *baseType->variables[member];
        this->member = member;
    }

    DocumentContext*
    MemberAccessContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new MemberAccessContext{};
        copyBase(this, copy);
        copy->baseExpression.reset(assertCast<ExpressionContext>(baseExpression->deepCopy(callback)));
        copy->baseExpression->parent = copy;
        copy->member = member;
        return callback(copy);
    }

    bool MemberAccessContext::isConstexpr() const { return false; }

    llvm::Value* MemberAccessContext::createAST(ASTContext& ctx) const
    {
        auto baseValue = ctx.dereferenceToDepth(baseExpression->createAST(ctx), 1);

        assert(baseValue->getType()->getContainedType(0)->isStructTy());
        ctx.setDebugLocation(this);
        return ctx.builder.CreateStructGEP(baseValue->getType()->getContainedType(0), baseValue, member);
    }

    CreateReferenceContext::CreateReferenceContext(ExpressionContext* source) : _source(source)
    {
        returnType = source->returnType;
        returnType.isRef = true;
    }

    bool CreateReferenceContext::isConstexpr() const { return false; }

    llvm::Value* CreateReferenceContext::createAST(ASTContext& ctx) const
    {
        auto ref = _source->createAST(ctx);
        assert(ref->getType()->isPointerTy());
        return ref;
    }

    DocumentContext*
    CreateReferenceContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return new CreateReferenceContext((ExpressionContext*)_source->deepCopy());
    };

    DereferenceContext::DereferenceContext(ExpressionContext* source) : _source(source)
    {
        returnType = source->returnType;
        returnType.isRef = false;
    }

    bool DereferenceContext::isConstexpr() const { return false; }

    llvm::Value* DereferenceContext::createAST(ASTContext& ctx) const
    {
        auto deref = _source->createAST(ctx);
        // All lValues should be being passed around as pointers already, it's just a matter of how we use them
        assert(deref->getType()->isPointerTy());
        return deref;
    }

    DocumentContext*
    DereferenceContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return new DereferenceContext((ExpressionContext*)_source->deepCopy());
    }

    NativeCastContext::NativeCastContext(ValueContext targetType, ExpressionContext* source) : sourceExpr(source)
    {
        assert(targetType.type != source->returnType.type);
        returnType = std::move(targetType);
    }

    bool NativeCastContext::isConstexpr() const { return sourceExpr->isConstexpr(); }

    llvm::Value* NativeCastContext::createAST(ASTContext& ctx) const
    {
        using CastOps = llvm::Instruction::CastOps;
        if(sourceExpr->returnType.isRef && returnType.isRef)
        {
            auto* sourceValue = ctx.dereferenceToDepth(sourceExpr->createAST(ctx), 1);
            assert(sourceValue->getType()->isPointerTy());
            llvm::Type* endType = ctx.getLLVMType(returnType);
            return ctx.builder.CreateCast(CastOps::BitCast, sourceValue, endType);
        }

        auto& sourceType = sourceExpr->returnType;
        auto* sourceValue = ctx.dereferenceToDepth(sourceExpr->createAST(ctx), 0);
        CastOps castType;

        switch(returnType.type.storageType)
        {
            case ValueType::UInt32:
                switch(sourceType.type.storageType)
                {
                    case ValueType::Int32:
                        castType = CastOps::BitCast;
                        break;
                    case ValueType::Int64:
                    case ValueType::UInt64:
                        castType = CastOps::Trunc;
                        break;
                    case ValueType::Float32:
                    case ValueType::Float64:
                        castType = CastOps::FPToUI;
                        castType = CastOps::FPToUI;
                        break;
                    default:
                        assert(false);
                }
                break;
            case ValueType::UInt64:
                switch(sourceType.type.storageType)
                {
                    case ValueType::UInt32:
                    case ValueType::Int32:
                        castType = CastOps::ZExt;
                        break;
                    case ValueType::Int64:
                        castType = CastOps::BitCast;
                        break;
                    case ValueType::Float32:
                        castType = CastOps::FPToUI;
                        break;
                    case ValueType::Float64:
                        castType = CastOps::FPToUI;
                        break;
                    default:
                        assert(false);
                }
                break;
            case ValueType::Int32:
                switch(sourceType.type.storageType)
                {
                    case ValueType::UInt32:
                        castType = CastOps::BitCast;
                        break;
                    case ValueType::UInt64:
                    case ValueType::Int64:
                        castType = CastOps::Trunc;
                        break;
                    case ValueType::Float32:
                        castType = CastOps::FPToSI;
                        break;
                    case ValueType::Float64:
                        castType = CastOps::FPToSI;
                        break;
                    default:
                        assert(false);
                }
                break;
            case ValueType::Int64:
                switch(sourceType.type.storageType)
                {
                    case ValueType::UInt64:
                        castType = CastOps::BitCast;
                        break;
                    case ValueType::UInt32:
                    case ValueType::Int32:
                        castType = CastOps::SExt;
                        break;
                    case ValueType::Float32:
                        castType = CastOps::FPToSI;
                        break;
                    case ValueType::Float64:
                        castType = CastOps::FPToSI;
                        break;
                    default:
                        assert(false);
                }
                break;
            case ValueType::Float32:
                switch(sourceType.type.storageType)
                {
                    case ValueType::UInt32:
                    case ValueType::UInt64:
                        castType = CastOps::UIToFP;
                        break;
                    case ValueType::Int32:
                    case ValueType::Int64:
                        castType = CastOps::SIToFP;
                        break;
                    case ValueType::Float64:
                        castType = CastOps::FPTrunc;
                        break;
                    default:
                        assert(false);
                }
                break;
            case ValueType::Float64:
                switch(sourceType.type.storageType)
                {
                    case ValueType::UInt32:
                    case ValueType::UInt64:
                        castType = CastOps::UIToFP;
                        break;
                    case ValueType::Int32:
                    case ValueType::Int64:
                        castType = CastOps::SIToFP;
                        break;
                    case ValueType::Float32:
                        castType = CastOps::FPExt;
                        break;
                    default:
                        assert(false);
                }
                break;
            default:
                assert(false);
        }

        llvm::Type* endType = ctx.getLLVMType(returnType);
        return ctx.builder.CreateCast(castType, sourceValue, endType);
    }

    DocumentContext*
    NativeCastContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new NativeCastContext{returnType, (ExpressionContext*)sourceExpr->deepCopy(callback)});
    }

    bool NativeCastContext::validCast(const ValueContext& from, const ValueContext& to)
    {
        if(from.isRef || to.isRef)
        {
            if(from.isRef && to.isRef)
                return from.type.storageType == ValueType::Void || to.type.storageType == ValueType::Void;
            return false;
        }
        switch(from.type.storageType)
        {
            case ValueType::Bool:
                return false;
            case ValueType::Char:
                return false;
            case ValueType::UInt32:
            case ValueType::UInt64:
            case ValueType::Int32:
            case ValueType::Int64:
            case ValueType::Float32:
            case ValueType::Float64:
                switch(to.type.storageType)
                {
                    case ValueType::UInt32:
                    case ValueType::UInt64:
                    case ValueType::Int32:
                    case ValueType::Int64:
                    case ValueType::Float32:
                    case ValueType::Float64:
                        return true;
                    default:
                        return false;
                }
            default:
                return false;
        }
    }

    bool NativeArithmeticContext::validArithmetic(const ValueContext& left, const ValueContext& right)
    {
        if(!isValueTypeScalar(left.type.storageType) || !isValueTypeScalar(left.type.storageType))
            return false;
        if(left.type.storageType == ValueType::Struct || right.type.storageType == ValueType::Struct)
            return false;
        return true;
    }

    NativeArithmeticContext::NativeArithmeticContext(NativeArithmeticContext::Operation op,
                                                     ExpressionContext* lValue,
                                                     ExpressionContext* rValue)
        : op(op), lValue(lValue), rValue(rValue)
    {
        assert(lValue->returnType.sameBaseType(rValue->returnType));
        returnType = lValue->returnType;
    }

    bool NativeArithmeticContext::isConstexpr() const { return lValue->isConstexpr() && rValue->isConstexpr(); }

    llvm::Value* NativeArithmeticContext::createAST(ASTContext& ctx) const
    {
        auto l = ctx.dereferenceToDepth(lValue->createAST(ctx), 0);
        auto r = ctx.dereferenceToDepth(rValue->createAST(ctx), 0);
        ctx.setDebugLocation(this);
        auto type = returnType.type.storageType;
        switch(type)
        {
            case ValueType::Bool:
            case ValueType::Char:
            case ValueType::UInt32:
            case ValueType::UInt64:
            case ValueType::Int32:
            case ValueType::Int64:
                switch(op)
                {
                    case ADD:
                        return ctx.builder.CreateAdd(l, r);
                    case SUB:
                        return ctx.builder.CreateSub(l, r);
                    case MUL:
                        return ctx.builder.CreateMul(l, r);
                    case DIV:
                        if(isValueTypeUnsigned(type))
                            return ctx.builder.CreateUDiv(l, r);
                        else
                            return ctx.builder.CreateSDiv(l, r);
                }
            case ValueType::Float32:
            case ValueType::Float64:
                switch(op)
                {
                    case ADD:
                        return ctx.builder.CreateFAdd(l, r);
                    case SUB:
                        return ctx.builder.CreateFSub(l, r);
                    case MUL:
                        return ctx.builder.CreateFMul(l, r);
                    case DIV:
                        return ctx.builder.CreateFDiv(l, r);
                }
            default:
                assert(false);
        }
    }

    DocumentContext*
    NativeArithmeticContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return new NativeArithmeticContext(
            op, (ExpressionContext*)lValue->deepCopy(), (ExpressionContext*)rValue->deepCopy());
    }

    NativeNegateContext::NativeNegateContext(ExpressionContext* value) : value(value)
    {
        assert(isValueTypeScalar(value->returnType.type.storageType));
        returnType = value->returnType;
        returnType.isRef = false;
        returnType.isLValue = false;
    }

    bool NativeNegateContext::isConstexpr() const { return value->isConstexpr(); }

    llvm::Value* NativeNegateContext::createAST(ASTContext& ctx) const
    {
        auto num = ctx.dereferenceToDepth(value->createAST(ctx), 0);
        if(num->getType()->isFloatTy())
            return ctx.builder.CreateFNeg(num);
        else
            return ctx.builder.CreateNeg(num);
    }

    DocumentContext*
    NativeNegateContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto copy = new NativeNegateContext((ExpressionContext*)value->deepCopy(callback));
        value->parent = copy;
        return callback(copy);
    }

    NativeIncrementContext::NativeIncrementContext(ExpressionContext* value, bool isPrefix) : value(value)
    {
        assert(isValueTypeScalar(value->returnType.type.storageType));
        assert(value->returnType.isLValue || value->returnType.isRef);
        returnType = value->returnType;
        returnType.isRef = false;
        returnType.isLValue = false;
    }

    bool NativeIncrementContext::isConstexpr() const { return value->isConstexpr(); }

    llvm::Value* NativeIncrementContext::createAST(ASTContext& ctx) const
    {
        auto ref = ctx.dereferenceToDepth(value->createAST(ctx), 1);
        auto num = ctx.dereferenceToDepth(ref, 0);

        llvm::Value* incNum = nullptr;
        ctx.setDebugLocation(this);
        if(isValueTypeInt(value->returnType.type.storageType))
            incNum = ctx.builder.CreateAdd(num, llvm::ConstantInt::get(num->getType(), 1));
        else
            incNum = ctx.builder.CreateFAdd(num, llvm::ConstantFP::get(num->getType(), 1.0));
        ctx.builder.CreateStore(incNum, ref);
        if(isPrefix)
            return incNum;
        return num;
    }

    DocumentContext*
    NativeIncrementContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto copy = new NativeIncrementContext((ExpressionContext*)value->deepCopy(callback), isPrefix);
        value->parent = copy;
        return callback(copy);
    }

    NativeDecrementContext::NativeDecrementContext(ExpressionContext* value, bool isPrefix) : value(value)
    {
        assert(isValueTypeScalar(value->returnType.type.storageType));
        assert(value->returnType.isLValue || value->returnType.isRef);
        returnType = value->returnType;
        returnType.isRef = false;
        returnType.isLValue = false;
    }

    bool NativeDecrementContext::isConstexpr() const { return value->isConstexpr(); }

    llvm::Value* NativeDecrementContext::createAST(ASTContext& ctx) const
    {
        auto ref = ctx.dereferenceToDepth(value->createAST(ctx), 1);
        auto num = ctx.dereferenceToDepth(ref, 0);

        llvm::Value* decNum = nullptr;
        if(isValueTypeInt(value->returnType.type.storageType))
            decNum = ctx.builder.CreateSub(num, llvm::ConstantInt::get(num->getType(), 1));
        else
            decNum = ctx.builder.CreateFSub(num, llvm::ConstantFP::get(num->getType(), 1.0));
        ctx.builder.CreateStore(decNum, ref);
        if(isPrefix)
            return decNum;
        return num;
    }

    DocumentContext*
    NativeDecrementContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto copy = new NativeDecrementContext((ExpressionContext*)value->deepCopy(callback), isPrefix);
        value->parent = copy;
        return callback(copy);
    }

    NativeNotContext::NativeNotContext(ExpressionContext* value) : value(value)
    {
        assert(value->returnType.type.storageType == ValueType::Bool);
        returnType = ValueContext{{"bool", ValueType::Bool, nullptr}, false, false, false};
    }

    bool NativeNotContext::isConstexpr() const { return value->isConstexpr(); }

    llvm::Value* NativeNotContext::createAST(ASTContext& ctx) const
    {
        auto v = ctx.dereferenceToDepth(value->createAST(ctx), 0);
        ctx.setDebugLocation(this);
        assert(v->getType()->isIntegerTy());
        return ctx.builder.CreateNot(v);
    }

    DocumentContext* NativeNotContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto copy = new NativeNotContext((ExpressionContext*)value->deepCopy(callback));
        value->parent = copy;
        return callback(copy);
    }

    NativeLogicContext::NativeLogicContext(NativeLogicContext::Operation op,
                                           ExpressionContext* lValue,
                                           ExpressionContext* rValue)
        : op(op), lValue(lValue), rValue(rValue)
    {
        assert(lValue->returnType.type.storageType == ValueType::Bool);
        assert(rValue->returnType.type.storageType == ValueType::Bool);
        returnType.type = {"bool", ValueType::Bool, nullptr};
    }

    bool NativeLogicContext::isConstexpr() const { return lValue->isConstexpr() && rValue->isConstexpr(); }

    llvm::Value* NativeLogicContext::createAST(ASTContext& ctx) const
    {
        auto l = ctx.dereferenceToDepth(lValue->createAST(ctx), 0);
        assert(l->getType()->isIntegerTy());
        auto r = ctx.dereferenceToDepth(rValue->createAST(ctx), 0);

        ctx.setDebugLocation(this);
        assert(r->getType()->isIntegerTy());
        switch(op)
        {
            case AND:
                return ctx.builder.CreateAnd(l, r);
            case OR:
                return ctx.builder.CreateOr(l, r);
        }
        assert(false);
        return nullptr;
    }

    DocumentContext*
    NativeLogicContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto copy = new NativeLogicContext(
            op, (ExpressionContext*)lValue->deepCopy(callback), (ExpressionContext*)rValue->deepCopy(callback));
        lValue->parent = copy;
        rValue->parent = copy;
        return callback(copy);
    }

    bool NativeCompareContext::validCompare(const ValueContext& left, const ValueContext& right)
    {
        if(left.type.storageType == ValueType::Struct || right.type.storageType == ValueType::Struct)
            return false;
        return true;
    }

    NativeCompareContext::NativeCompareContext(Operation op, ExpressionContext* lValue, ExpressionContext* rValue)
        : op(op), lValue(lValue), rValue(rValue)
    {
        assert(lValue->returnType.sameBaseType(rValue->returnType));
        returnType.type = {"bool", ValueType::Bool, nullptr};
    }

    bool NativeCompareContext::isConstexpr() const { return lValue->isConstexpr() && rValue->isConstexpr(); }

    llvm::Value* NativeCompareContext::createAST(ASTContext& ctx) const
    {
        auto l = ctx.dereferenceToDepth(lValue->createAST(ctx), 0);
        auto r = ctx.dereferenceToDepth(rValue->createAST(ctx), 0);
        ctx.setDebugLocation(this);
        auto type = lValue->returnType.type.storageType;
        switch(type)
        {
            case ValueType::Bool:
            case ValueType::Char:
            case ValueType::UInt32:
            case ValueType::UInt64:
                switch(op)
                {
                    case EQ:
                        return ctx.builder.CreateICmpEQ(l, r);
                    case NEQ:
                        return ctx.builder.CreateICmpNE(l, r);
                    case GT:
                        return ctx.builder.CreateICmpUGT(l, r);
                    case GE:
                        return ctx.builder.CreateICmpUGE(l, r);
                    case LT:
                        return ctx.builder.CreateICmpULT(l, r);
                    case LE:
                        return ctx.builder.CreateICmpULE(l, r);
                }
                break;
            case ValueType::Int32:
            case ValueType::Int64:
                switch(op)
                {
                    case EQ:
                        return ctx.builder.CreateICmpEQ(l, r);
                    case NEQ:
                        return ctx.builder.CreateICmpNE(l, r);
                    case GT:
                        return ctx.builder.CreateICmpSGT(l, r);
                    case GE:
                        return ctx.builder.CreateICmpSGE(l, r);
                    case LT:
                        return ctx.builder.CreateICmpSLT(l, r);
                    case LE:
                        return ctx.builder.CreateICmpSLE(l, r);
                }
                break;
            case ValueType::Float32:
            case ValueType::Float64:
                switch(op)
                {
                    case EQ:
                        return ctx.builder.CreateFCmpOEQ(l, r);
                    case NEQ:
                        return ctx.builder.CreateFCmpONE(l, r);
                    case GT:
                        return ctx.builder.CreateFCmpOGE(l, r);
                    case GE:
                        return ctx.builder.CreateFCmpOGE(l, r);
                    case LT:
                        return ctx.builder.CreateFCmpOLT(l, r);
                    case LE:
                        return ctx.builder.CreateFCmpOLE(l, r);
                }
                break;
            default:
                assert(false);
                return nullptr;
        }
        return nullptr;
    }

    DocumentContext*
    NativeCompareContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return new NativeCompareContext(
            op, (ExpressionContext*)lValue->deepCopy(), (ExpressionContext*)rValue->deepCopy());
    }

    DocumentContext*
    FunctionCallContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new FunctionCallContext{};
        copyBase(this, copy);
        copy->function = function;
        for(auto& arg : arguments)
            copy->arguments.emplace_back(assertCast<ExpressionContext>(arg->deepCopy(callback)));
        return callback(copy);
    }

    bool FunctionCallContext::isConstexpr() const
    {
        if(!function || !function->isConstexpr)
            return false;
        for(auto& arg : arguments)
            if(!arg->isConstexpr())
                return false;
        return true;
    }

    llvm::Value* FunctionCallContext::createAST(ASTContext& ctx) const
    {
        ctx.setDebugLocation(this);
        bool argRet = !returnType.isRef && returnType.type.structCtx;
        std::vector<llvm::Value*> args;
        if(argRet)
        {
            // Avoid copy and construction operations by just returning the argument
            if(parent->is<ReturnContext>() && getParent<FunctionContext>()->returnType.sameBaseType(returnType))
                args.push_back(ctx.findValue("-retRef"));
            else
            {
                // Construct struct to be returned into
                args.push_back(ctx.builder.CreateAlloca(ctx.getLLVMType(returnType)));
                auto constructor = ctx.functions.find(returnType.type.structCtx->constructor->signature());
                assert(constructor != ctx.functions.end());

                ctx.setDebugLocation(this);
                ctx.builder.CreateCall(constructor->second, args[0]);
            }
        }


        llvm::Value* retVal = nullptr;
        if(function)
        {
            size_t argIndex = 0;
            for(auto& arg : arguments)
            {
                bool isRefType = function->arguments[argIndex]->isRef ||
                                 function->arguments[argIndex]->type.storageType == ValueType::FuncRef;
                args.push_back(ctx.dereferenceToDepth(arg->createAST(ctx), isRefType ? 1 : 0));
                argIndex++;
            }

            auto funcItr = ctx.functions.find(function->signature());
            assert(funcItr != ctx.functions.end());
            llvm::Function* func = funcItr->second;
            retVal = ctx.builder.CreateCall(func, args);
        }
        else
        {
            assert(functionRef);

            std::vector<llvm::Type*> argTypes;
            if(argRet)
                argTypes.push_back(args[0]->getType());
            for(auto& arg : arguments)
            {
                argTypes.push_back(ctx.getLLVMType(arg->returnType));
                bool isRefType = arg->returnType.isRef || arg->returnType.type.storageType == ValueType::FuncRef;
                args.push_back(ctx.dereferenceToDepth(arg->createAST(ctx), isRefType ? 1 : 0));
            }

            auto retType = argRet ? ctx.getLLVMType({}) : ctx.getLLVMType(returnType);
            llvm::FunctionType* funcType = llvm::FunctionType::get(retType, argTypes, false);

            auto funcRef = functionRef->createAST(ctx);
            if(funcRef->getType()->getContainedType(0)->isPointerTy())
            {
                funcRef = ctx.builder.CreateLoad(ctx.getLLVMType(functionRef->returnType), funcRef);
                funcRef = ctx.builder.CreatePointerCast(funcRef, llvm::PointerType::get(funcType, 0));
            }
            else if(funcRef->getType()->getContainedType(0)->isFunctionTy())
                funcRef = ctx.builder.CreateBitCast(funcRef, llvm::PointerType::get(funcType, 0));

            ctx.setDebugLocation(this);
            retVal = ctx.builder.CreateCall(funcType, funcRef, args);
        }


        if(!returnType.isRef && returnType.type.structCtx)
            return args[0];
        return retVal;
    }

    NativeIndexOperator::NativeIndexOperator(ExpressionContext* source, ExpressionContext* index)
        : source(source), index(index)
    {
        assert(source);
        assert(index);
        assert(source->returnType.isRef);
        assert(source->returnType.type.storageType == ValueType::UInt32 ||
               source->returnType.type.storageType == ValueType::Int32 ||
               source->returnType.type.storageType == ValueType::UInt64 ||
               source->returnType.type.storageType == ValueType::Int64);
        returnType = source->returnType;
    }

    bool NativeIndexOperator::isConstexpr() const { return false; }

    llvm::Value* NativeIndexOperator::createAST(ASTContext& ctx) const
    {
        auto srcArr = ctx.dereferenceToDepth(source->createAST(ctx), 1);
        auto idx = ctx.dereferenceToDepth(index->createAST(ctx), 0);
        assert(idx->getType()->isIntegerTy());
        auto elementType = returnType;
        elementType.isRef = false;

        return ctx.builder.CreateGEP(ctx.getLLVMType(elementType), srcArr, idx);
    }

    DocumentContext*
    NativeIndexOperator::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return new NativeIndexOperator((ExpressionContext*)source->deepCopy(callback),
                                       (ExpressionContext*)index->deepCopy(callback));
    }

    bool LambdaInstanceContext::isConstexpr() const { return false; }

    DocumentContext*
    LambdaInstanceContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new LambdaInstanceContext{};
        copyBase(this, copy);
        copy->lambdaType = lambdaType;
        copy->captureType = captureType;
        copy->func = func;
        for(auto& arg : captures)
            copy->captures.emplace_back(assertCast<ExpressionContext>(arg->deepCopy(callback)));
        return callback(copy);
    }

    llvm::Value* LambdaInstanceContext::createAST(ASTContext& ctx) const
    {
        auto lt = ctx.getLLVMType(returnType);
        auto lambdaInstance = ctx.builder.CreateAlloca(lt, nullptr, "lambda");
        ctx.addValue(lambdaInstance, returnType);

        auto lambdaConstructor = ctx.functions.at(lambdaType->constructor->signature());
        assert(lambdaConstructor);
        ctx.builder.CreateCall(lambdaConstructor, {lambdaInstance});

        if(allocFunc)
        {
            auto allocateCaptureMem = ctx.functions.at(allocFunc->signature());
            assert(allocateCaptureMem);
            ctx.builder.CreateCall(allocateCaptureMem, {lambdaInstance});

            auto dataType = ctx.getLLVMType({{"", ValueType::Struct, captureType}, true, false, false});
            auto _data = ctx.builder.CreateStructGEP(lt, lambdaInstance, 0);
            _data = ctx.builder.CreateLoad(_data->getType()->getContainedType(0), _data);
            _data = ctx.builder.CreatePointerCast(_data, llvm::PointerType::get(dataType, 0));

            size_t captureIndex = 0;
            for(auto& capture : captures)
            {
                auto l = ctx.builder.CreateStructGEP(dataType, _data, captureIndex);
                auto r = capture->createAST(ctx);

                if(!capture->returnType.type.structCtx || captureType->variables[captureIndex]->isRef)
                {
                    bool isRefType = captureType->variables[captureIndex]->isRef ||
                                     captureType->variables[captureIndex]->type.storageType == ValueType::FuncRef;
                    ctx.builder.CreateStore(ctx.dereferenceToDepth(r, isRefType ? 1 : 0), l);
                    continue;
                }

                auto cc = ctx.functions.find(capture->returnType.type.structCtx->copyConstructor->signature());
                assert(cc != ctx.functions.end());
                assert(cc->second->arg_size() == 2);
                auto structPointerType = *captureType->variables[captureIndex];
                structPointerType.isRef = true;

                std::vector<llvm::Value*> args = {ctx.dereferenceToDepth(l, 1), ctx.dereferenceToDepth(r, 1)};
                ctx.builder.CreateCall(cc->second, args);
                captureIndex++;
            }

            auto _dataDestructor = ctx.builder.CreateStructGEP(lt, lambdaInstance, 2);
            llvm::Value* dataDestructor = ctx.functions.at(captureType->destructor->signature());
            dataDestructor =
                ctx.builder.CreatePointerCast(dataDestructor, _dataDestructor->getType()->getContainedType(0));
            ctx.builder.CreateStore(dataDestructor, _dataDestructor);

            auto _dataCopyConstructor = ctx.builder.CreateStructGEP(lt, lambdaInstance, 3);
            llvm::Value* dataCopyConstructor = ctx.functions.at(copyFunc->signature());
            dataCopyConstructor = ctx.builder.CreatePointerCast(dataCopyConstructor,
                                                                _dataCopyConstructor->getType()->getContainedType(0));
            ctx.builder.CreateStore(dataCopyConstructor, _dataCopyConstructor);
        }


        auto _f = ctx.builder.CreateStructGEP(lt, lambdaInstance, 1);
        llvm::Value* f = ctx.functions.at(func->signature());
        f = ctx.builder.CreatePointerCast(f, _f->getType()->getContainedType(0));

        ctx.setDebugLocation(this);
        ctx.builder.CreateStore(f, _f);

        return lambdaInstance;
    }

    DocumentContext* LambdaInstanceContext::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        return captureType->findIdentifier(identifier, 0);
    }

    DocumentContext* FunctionContext::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        for(auto& arg : arguments)
        {
            if(arg->identifier.text == identifier)
                return arg.get();
        }
        auto argPack = argPackInstances.find(identifier);
        if(argPack != argPackInstances.end())
            return &argPack->second;
        return DocumentContext::findIdentifier(identifier, searchOptions);
    }

    std::string FunctionContext::longId() const
    {
        auto prefix = DocumentContext::longId();
        if(prefix.empty())
            return identifier.text;
        return prefix + "::" + identifier.text;
    }

    std::string FunctionContext::argSig() const
    {
        std::string sig = "(";
        if(returnType.type.structCtx && !returnType.isRef)
        {
            auto resType = returnType;
            resType.isRef = true;
            sig += resType.signature();
            if(!arguments.empty())
                sig += ",";
        }

        for(auto itr = arguments.begin(); itr != arguments.end();)
        {
            auto& arg = *itr;
            if(arg->isConst)
                sig += "const ";
            if(arg->isRef)
                sig += "ref ";
            sig += arg->type.identifier;
            if(++itr != arguments.end())
                sig += ",";
            else
                break;
        }
        sig += ")";
        return sig;
    }

    std::string FunctionContext::signature() const { return longId() + argSig(); }

    DocumentContext* FunctionContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new FunctionContext{};
        copyBase(this, copy);
        copy->identifier = identifier;
        copy->returnType = returnType;
        for(auto& arg : arguments)
        {
            auto* newArg = assertCast<LabeledValueContext>(arg->deepCopy(callback));
            copy->arguments.emplace_back(newArg);
            delete newArg;
        }

        copy->isConst = isConst;
        copy->isConstexpr = isConstexpr;
        if(body)
        {
            copy->body.reset(assertCast<ScopeContext>(body->deepCopy(callback)));
            copy->body->parent = copy;
        }

        return callback(copy);
    }

    llvm::Value* FunctionContext::createAST(ASTContext& ctx) const
    {
        assert(ctx.functions.contains(signature()));
        ctx.func = ctx.functions.at(signature());
        ctx.exportedFunctions.push_back({signature(), returnType.signature(), tags});

        ctx.pushScope();

        if(ctx.dBuilder)
        {
            ctx.diFunction = ctx.debugSubprograms.at(signature());
            ctx.setDebugScope(ctx.diFunction);
        }

        if(body)
        {
            ctx.currentBlock = llvm::BasicBlock::Create(*ctx.llvmCtx, "entry", ctx.func);
            ctx.builder.SetInsertPoint(ctx.currentBlock);
            ctx.setDebugLocation(body.get());
            bool argReturn = !returnType.isRef && returnType.type.structCtx;
            size_t index = argReturn ? -1 : 0;
            for(auto& arg : ctx.func->args())
            {
                if(index == -1)
                {
                    std::string id = "-retRef";
                    arg.setName(id);
                    ctx.addValue(id, &arg, returnType);
                    index++;
                    continue;
                }
                assert(index < arguments.size());
                // Using raw registers as values that might be set is more work than its worth when optimization can
                // just take care of it for us (I'm not dealing with phi nodes right now!)
                auto argValue = ctx.builder.CreateAlloca(arg.getType(), nullptr, arguments[index]->identifier.text);
                ctx.builder.CreateStore(&arg, argValue);
                std::string& id = arguments[index]->identifier.text;
                arg.setName(id);
                ctx.addValue(id, argValue, *arguments[index]);

                if(ctx.dBuilder)
                {
                    auto* dType = ctx.getDebugType(*arguments[index]);
                    auto line = arguments[index]->range.start.line;
                    auto charPos = arguments[index]->range.start.charPos;
                    llvm::DILocalVariable* dArg =
                        ctx.dBuilder->createParameterVariable(ctx.debugScope(),
                                                              arguments[index]->identifier.text,
                                                              index + 1,
                                                              ctx.diFunction->getFile(),
                                                              line,
                                                              dType,
                                                              true);

                    ctx.dBuilder->insertDeclare(
                        argValue,
                        dArg,
                        ctx.dBuilder->createExpression(),
                        llvm::DILocation::get(ctx.debugScope()->getContext(), line, charPos, ctx.debugScope()),
                        ctx.currentBlock);
                }
                index++;
            }

            if(ctx.dBuilder)
                ctx.builder.SetCurrentDebugLocation(llvm::DebugLoc());
            body->createAST(ctx);
            if(returnType.type.storageType == ValueType::Void)
            {
                if(!ctx.currentBlock)
                    ctx.setInsertPoint(llvm::BasicBlock::Create(*ctx.llvmCtx, "", ctx.func));
                ctx.builder.CreateRetVoid();
            }

            ctx.currentBlock = nullptr;
        }

        ctx.popScope();

        if(ctx.dBuilder)
            ctx.dBuilder->finalizeSubprogram(ctx.diFunction);

        std::string funcError;
        llvm::raw_string_ostream funcErrStr(funcError);
        if(llvm::verifyFunction(*ctx.func, &funcErrStr))
        {
            ctx.printModule();
            fprintf(stderr, "Invalid function IR generated:\n%s\n", funcErrStr.str().c_str());

            throw std::runtime_error("Invalid function IR generated");
        }
        // Only run optimization if verification succeeds
        else if(ctx.fpm)
            ctx.fpm->run(*ctx.func, *ctx.fam);

        return nullptr;
    }

    void FunctionContext::registerFunction(ASTContext& ctx, bool isLinked) const
    {
        std::vector<llvm::Type*> argTypes;
        bool argReturn = !returnType.isRef && returnType.type.structCtx;
        if(argReturn)
        {
            auto thisRefType = returnType;
            thisRefType.isRef = true;
            argTypes.push_back(ctx.getLLVMType(thisRefType));
        }

        bool exported = false;
        llvm::Function::LinkageTypes linkage;
        if(isLinked)
            linkage = llvm::Function::ExternalWeakLinkage;
        else if(isTemplateInstance)
            linkage = llvm::Function::WeakAnyLinkage;
        else
            linkage = llvm::Function::ExternalLinkage;

        for(auto& arg : arguments)
            argTypes.push_back(ctx.getLLVMType(*arg));
        auto retType = argReturn ? ctx.getLLVMType({}) : ctx.getLLVMType(returnType);
        llvm::FunctionType* funcType = llvm::FunctionType::get(retType, argTypes, false);

        std::string sig = signature();
        auto func = llvm::Function::Create(funcType, linkage, sig, ctx.module.get());
        ctx.functions.insert({sig, func});

        if(!isLinked && ctx.dBuilder)
        {
            std::vector<llvm::Metadata*> dArgs;
            size_t argIndex = 0;
            for(auto& arg : arguments)
            {
                auto* argType = ctx.getDebugType(ValueContext{*arg});
                dArgs.push_back(argType);
            }

            llvm::DIFile* file = ctx.diFile;
            if(isTemplateInstance)
            {
                auto source = std::filesystem::canonical(getParent<ScriptContext>()->source);
                file = ctx.dBuilder->createFile(source.filename().string(), source.parent_path().string());
            }

            auto subType = ctx.dBuilder->createSubroutineType(ctx.dBuilder->getOrCreateTypeArray(dArgs));
            llvm::DIScope* fCtx = file;
            llvm::DISubprogram* sp = ctx.dBuilder->createFunction(fCtx,
                                                                  identifier.text,
                                                                  signature(),
                                                                  file,
                                                                  range.start.line,
                                                                  subType,
                                                                  range.start.line,
                                                                  llvm::DINode::FlagPrototyped,
                                                                  llvm::DISubprogram::SPFlagDefinition);
            func->setSubprogram(sp);
            ctx.debugSubprograms.insert({sig, sp});
        }
    }

    DocumentContext* StructContext::getNodeAtChar(TextPos pos)
    {
        if(!DocumentContext::getNodeAtChar(pos))
            return nullptr;
        for(auto& f : functions)
        {
            auto node = f->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& v : variables)
        {
            auto node = v->getNodeAtChar(pos);
            if(node)
                return node;
        }

        return this;
    }

    DocumentContext* StructContext::findIdentifier(const std::string& id, uint8_t searchOptions)
    {
        for(auto& v : variables)
        {
            if(v->identifier.text == id)
                return v.get();
        }

        return DocumentContext::findIdentifier(id, searchOptions);
    }

    void StructContext::getFunction(const std::string& identifier,
                                    FunctionOverridesContext* overrides,
                                    uint8_t searchOptions)
    {
        for(auto& f : functions)
        {
            if(f->identifier.text == identifier)
                overrides->overrides.push_back(f.get());
        }
        auto temp = templates.find(identifier);
        if(temp != templates.end())
            overrides->templates.push_back(temp->second.get());
        DocumentContext::getFunction(identifier, overrides, searchOptions);
    }

    std::string StructContext::longId() const
    {
        auto prefix = DocumentContext::longId();
        if(prefix.empty())
            return identifier.text;
        return prefix + "::" + identifier.text;
    }

    DocumentContext* StructContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new StructContext{};
        copyBase(this, copy);
        copy->identifier = identifier;

        for(auto& var : variables)
            copy->variables.emplace_back(assertCast<LabeledValueContext>(var->deepCopy(callback)));
        for(auto& func : functions)
            copy->functions.emplace_back(assertCast<FunctionContext>(func->deepCopy(callback)));
        copy->packed = packed;

        return callback(copy);
    }

    llvm::Value* StructContext::createAST(ASTContext& ctx) const
    {
        assert(false);
        return nullptr;
    }

    TemplateHandle::TemplateHandle(TemplateHandle::Type type,
                                   antlr4::ParserRuleContext* root,
                                   DocumentContext* parent,
                                   const std::vector<TemplateDefArgumentContext*>& args)
    {
        this->type = type;
        this->root = root;
        this->parent = parent;
        for(auto& arg : args)
            this->args.emplace_back(arg);
    }

    llvm::Value* TemplateHandle::createAST(ASTContext& ctx) const
    {
        throw std::runtime_error("TemplateHandle can not create AST!");
    }

    std::string TemplateHandle::longId() const { return parent->longId() + "::" + identifier.text; }

    DocumentContext* TemplateHandle::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        std::vector<TemplateDefArgumentContext*> copyArgs;
        for(auto& arg : args)
            copyArgs.push_back(new TemplateDefArgumentContext{*arg});
        auto* copy = new TemplateHandle(type, root, parent, copyArgs);
        return callback(copy);
    }

    DocumentContext* ModuleContext::getNodeAtChar(TextPos pos)
    {
        for(auto& f : functions)
        {
            auto node = f->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& s : structs)
        {
            auto node = s->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& g : globals)
        {
            auto node = g->getNodeAtChar(pos);
            if(node)
                return node;
        }
        if(!range.posInRange(pos))
            return nullptr;
        return this;
    }

    DocumentContext* ModuleContext::findIdentifier(const std::string& id, uint8_t searchOptions)
    {
        auto t = templates.find(id);
        if(t != templates.end() && t->second->type == TemplateHandle::Struct)
            return t->second.get();

        for(auto& g : globals)
        {
            if(g->identifier.text == id)
                return g.get();
        }

        for(auto& s : structs)
        {
            if(s->identifier.text == id)
                return s.get();
        }

        if(searchOptions & IDSearchOptions_ChildrenOnly)
            return nullptr;
        return DocumentContext::findIdentifier(id, searchOptions);
    }

    void ModuleContext::getFunction(const std::string& id, FunctionOverridesContext* overrides, uint8_t searchOptions)
    {
        DocumentContext::getFunction(id, overrides, searchOptions);
        for(auto& f : functions)
        {
            if(f->identifier.text == id)
                overrides->overrides.push_back(f.get());
        }
        auto temp = templates.find(id);
        if(temp != templates.end() && temp->second->type == TemplateHandle::Function)
            overrides->templates.push_back(temp->second.get());
        if(searchOptions & IDSearchOptions_ParentsOnly)
            return;
        for(auto& s : structs)
            s->getFunction(id, overrides, searchOptions);
    }

    std::string ModuleContext::longId() const
    {
        auto prefix = DocumentContext::longId();
        if(prefix.empty())
            return identifier.text;
        return prefix + "::" + identifier.text;
    }

    DocumentContext* ModuleContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new ModuleContext{};
        copyBase(this, copy);
        copy->identifier = identifier;

        for(auto& var : globals)
            copy->globals.emplace_back(assertCast<LabeledValueContext>(var->deepCopy(callback)));
        for(auto& s : structs)
            copy->structs.emplace_back(assertCast<StructContext>(s->deepCopy(callback)));
        for(auto& func : functions)
            copy->functions.emplace_back(assertCast<FunctionContext>(func->deepCopy(callback)));

        return callback(copy);
    }

    llvm::Value* ModuleContext::createAST(ASTContext& ctx) const
    {
        for(auto& g : globals)
        {
            auto type = ctx.getLLVMType(*g);
            auto glob = ctx.module->getOrInsertGlobal(g->identifier.text, type, ctx.makeGlobalVariable(*g, true));
            ctx.globals.insert({g->longId(), glob});
        }
        for(auto& link : links)
            link.second->createAST(ctx);

        for(auto& f : functions)
            f->registerFunction(ctx, false);

        for(auto& s : structs)
        {
            for(auto& f : s->functions)
                f->registerFunction(ctx, false);
        }

        for(auto& f : functions)
            f->createAST(ctx);

        for(auto& s : structs)
        {
            for(auto& f : s->functions)
                f->createAST(ctx);
        }
        return nullptr;
    }

    IRModule ModuleContext::compile(llvm::LLVMContext* ctx, uint8_t flags) const
    {
        IRModule module;
        module.id = identifier.text;
        llvm::LoopAnalysisManager LAM;
        llvm::CGSCCAnalysisManager CGAM;

        ASTContext cc(ctx, identifier.text);
        cc.flags = flags;
        if(flags & CompileFlags_Optimize)
        {
            cc.fam = std::make_unique<llvm::FunctionAnalysisManager>();
            cc.mam = std::make_unique<llvm::ModuleAnalysisManager>();

            llvm::PassBuilder PB;

            // Register all the basic analyses with the managers.
            PB.registerModuleAnalyses(*cc.mam);
            PB.registerCGSCCAnalyses(CGAM);
            PB.registerFunctionAnalyses(*cc.fam);
            PB.registerLoopAnalyses(LAM);
            PB.crossRegisterProxies(LAM, *cc.fam, CGAM, *cc.mam);

            // Create the pass manager.
            // This one corresponds to a typical -O2 optimization pipeline.
            cc.mpm = std::make_unique<llvm::ModulePassManager>(
                PB.buildPerModuleDefaultPipeline(llvm::PassBuilder::OptimizationLevel::O2));
            cc.fpm = std::make_unique<llvm::FunctionPassManager>(PB.buildFunctionSimplificationPipeline(
                llvm::PassBuilder::OptimizationLevel::O2, llvm::ThinOrFullLTOPhase::None));
        }
        if(flags & CompileFlags_DebugInfo)
        {
            cc.module->addModuleFlag(llvm::Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);

            if(llvm::Triple(llvm::sys::getProcessTriple()).isOSDarwin())
                cc.module->addModuleFlag(llvm::Module::Warning, "Dwarf Version", 2);

            cc.dBuilder = std::make_unique<llvm::DIBuilder>(*cc.module);
            auto source = std::filesystem::canonical(getParent<ScriptContext>()->source);
            cc.diFile = cc.dBuilder->createFile(source.filename().string(), source.parent_path().string());
            cc.diCompileUnit = cc.dBuilder->createCompileUnit(
                llvm::dwarf::DW_LANG_C, cc.diFile, "Brane Script Runtime", flags & CompileFlags_Optimize, "", 0);

            cc.debugTypes.insert({"void", cc.dBuilder->createBasicType("void", 0, llvm::dwarf::DW_ATE_signed)});
            cc.debugTypes.insert({"bool", cc.dBuilder->createBasicType("bool", 1, llvm::dwarf::DW_ATE_boolean)});
            cc.debugTypes.insert({"char", cc.dBuilder->createBasicType("char", 8, llvm::dwarf::DW_ATE_unsigned_char)});
            cc.debugTypes.insert({"uint", cc.dBuilder->createBasicType("uint", 32, llvm::dwarf::DW_ATE_unsigned)});
            cc.debugTypes.insert({"int", cc.dBuilder->createBasicType("int", 32, llvm::dwarf::DW_ATE_signed)});
            cc.debugTypes.insert({"uint64", cc.dBuilder->createBasicType("uint64", 64, llvm::dwarf::DW_ATE_unsigned)});
            cc.debugTypes.insert({"int64", cc.dBuilder->createBasicType("int64", 64, llvm::dwarf::DW_ATE_signed)});
            cc.debugTypes.insert({"float", cc.dBuilder->createBasicType("float", 32, llvm::dwarf::DW_ATE_float)});
            cc.debugTypes.insert({"double", cc.dBuilder->createBasicType("double", 64, llvm::dwarf::DW_ATE_float)});
        }

        createAST(cc);

        std::string modErr;
        llvm::raw_string_ostream modErrStr(modErr);
        if(llvm::verifyModule(*cc.module, &modErrStr))
        {
            cc.printModule();
            std::fprintf(stderr, "Invalid IR result, verifyModule returned error: %s\n\n", modErr.c_str());
            throw std::runtime_error("Module IR invalid! [" + modErr + "]");
        }

        if(cc.mpm)
            cc.mpm->run(*cc.module, *cc.mam);

        if(cc.dBuilder)
            cc.dBuilder->finalize();

        if(flags & CompileFlags_PrintIR)
            cc.printModule();

        llvm::raw_string_ostream bitcodeStream(module.bitcode);
        llvm::WriteBitcodeToFile(*cc.module, bitcodeStream);
        bitcodeStream.str();

        for(auto& link : cc.linkedModules)
            module.links.push_back(link);

        module.functions = std::move(cc.exportedFunctions);
        module.globals = std::move(cc.exportedGlobals);
        for(auto& s : cc.definedStructs)
        {
            if(s.second.exported)
                module.structs.push_back(std::move(s.second.def));
        }

        return std::move(module);
    }

    IRScript ScriptContext::compile(llvm::LLVMContext* ctx, uint8_t flags)
    {
        IRScript script;
        script.id = source;

        for(auto& mod : modules)
        {
            auto module = mod.second->compile(ctx, flags);
            script.modules.insert({module.id, std::move(module)});
        }

        return script;
    }

    DocumentContext* ScriptContext::getNodeAtChar(TextPos pos)
    {
        for(auto& m : modules)
        {
            auto node = m.second->getNodeAtChar(pos);
            if(node)
                return node;
        }
        if(!range.posInRange(pos))
            return nullptr;
        return this;
    }

    DocumentContext* ScriptContext::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        auto m = modules.find(identifier);
        if(m != modules.end())
            return m->second.get();
        return nullptr;
    }

    void ScriptContext::getFunction(const std::string& identifier,
                                    FunctionOverridesContext* overrides,
                                    uint8_t searchOptions)
    {}

    llvm::Value* ScriptContext::createAST(ASTContext& ctx) const
    {
        assert(false);
        return nullptr;
    }

    DocumentContext* ScriptContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new ScriptContext{};
        copyBase(this, copy);

        for(auto& lib : modules)
            copy->modules.insert({lib.first, assertCast<ModuleContext>(lib.second->deepCopy(callback))});

        return callback(copy);
    }

    DocumentContext* LinkContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new LinkContext{*this});
    }

    llvm::Value* LinkContext::createAST(ASTContext& ctx) const
    {
        assert(module);
        if(ctx.linkedModules.contains(module->identifier.text))
            return nullptr;
        ctx.linkedModules.insert(module->identifier.text);

        for(auto& g : module->globals)
        {
            auto type = ctx.getLLVMType(*g);
            auto glob = ctx.module->getOrInsertGlobal(g->identifier.text, type, ctx.makeExternGlobalVariable(*g));
            ctx.globals.insert({g->longId(), glob});
        }

        for(auto& f : module->functions)
            f->registerFunction(ctx, true);

        for(auto& s : module->structs)
        {
            for(auto& f : s->functions)
                f->registerFunction(ctx, true);
        }

        for(auto& link : module->links)
            link.second->createAST(ctx);
        return nullptr;
    }

    TypedefArgContext::TypedefArgContext(std::string id, ValueContext value) : value(std::move(value))
    {
        identifier = std::move(id);
    }

    llvm::Value* ArgPackInstanceContext::createAST(ASTContext& ctx) const
    {
        assert(false);
        return nullptr;
    }

    DocumentContext*
    ArgPackInstanceContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return new ArgPackInstanceContext{*this};
    }

    bool ConstValueContext::isConstexpr() const { return true; }
} // namespace BraneScript
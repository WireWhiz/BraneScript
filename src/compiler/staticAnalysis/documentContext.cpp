//
// Created by wirewhiz on 1/23/23.
//

#include "documentContext.h"
#include <cassert>
#include <llvm/Analysis/LoopAnalysisManager.h>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/Analysis/CGSCCPassManager.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Scalar/Reassociate.h"
#include "llvm/Transforms/Scalar/SimplifyCFG.h"

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

    bool TypeContext::isInt() const
    {
        return ValueType::Signed_Begin <= storageType && storageType <= ValueType::Signed_End;
    }

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
                return sizeof(void*); // Not too important, these values are mostly used for casting cost calculations
        }
        return 1;
    }

    bool ValueContext::operator==(const ValueContext& o) const
    {
        if(type != o.type)
            return false;
        if(isRef != o.isRef)
            return false;
        return true;
    }

    bool ValueContext::operator!=(const ValueContext& o) const
    {
        if(type != o.type)
            return true;
        if(isRef != o.isRef)
            return true;
        return false;
    }

    void ValueContext::operator=(const LabeledValueContext& o)
    {
        assert(o.type.storageType != ValueType::Struct || o.type.structCtx);
        type = o.type;
        isConst = o.isConst;
        isRef = o.isRef;
        isLValue = o.isLValue;
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
        for(auto& m : structCtx->variables)
        {
            IRStructDef::Member newM;
            newM.type = m->type.identifier;
            newM.name = m->identifier;
            entry.def.members.push_back(std::move(newM));
            llvmTypes.push_back(getLLVMType(*m));
        }
        entry.def.packed = structCtx->packed;

        llvm::StructType* st;
        if(llvmTypes.empty())
            st = llvm::StructType::create(*llvmCtx, id);
        else
            st = llvm::StructType::create(llvmTypes, id, structCtx->packed);

        entry.llvmType = st;
        entry.isExported = structCtx->getParent<LibraryContext>();

        definedStructs.insert({std::move(id), std::move(entry)});

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
                    return llvm::PointerType::get(*llvmCtx, 0);
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
                exportedGlobals.push_back(id);
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

    void ASTContext::addValue(std::string id, llvm::Value* value, ValueContext context)
    {
        scopes.back().values.insert({std::move(id),  {value, std::move(context)}});
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

    llvm::Value* ASTContext::convertToType(llvm::Value* value, const ValueContext& valueCtx, bool forceToValue)
    {
        auto valueType = value->getType();
        if(valueType->isPointerTy() && (!valueCtx.isRef || forceToValue) && !valueCtx.type.structCtx)
        {
            auto targetType = getLLVMType(valueCtx);
            assert(valueType->getContainedType(0) == targetType);
            return builder.CreateLoad(targetType, value);
        }
        if(valueType->isPointerTy() && valueCtx.isRef && !valueType->isOpaquePointerTy() && valueType->getContainedType(0)->isPointerTy())
            return builder.CreateLoad(getLLVMType(valueCtx), value);
        if(!valueType->isPointerTy() && valueCtx.isRef)
            throw std::runtime_error("Unable to create ref from lValue");
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
                auto destructorFunc = functions.find(value.second.context.type.structCtx->destructorSig());
                assert(destructorFunc != functions.end());
                builder.CreateCall(destructorFunc->second, {value.second.value});
            }
            if(onlyLocal)
                break;
        }
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
                                      std::list<FunctionContext*>& overrides,
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
        for(auto& var : localVariables)
        {
            auto varValue = ctx.builder.CreateAlloca(ctx.getLLVMType(*var), nullptr, var->identifier.text);
            ctx.addValue(var->identifier.text, varValue, *var);
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
            ctx.destructStack();
            ctx.currentBlock = nullptr;
            return ctx.builder.CreateRetVoid();
        }

        auto parentFunc = getParent<FunctionContext>();
        assert(parentFunc);
        auto retValue = ctx.convertToType(value->createAST(ctx), parentFunc->returnType);

        if(!parentFunc->returnType.isRef && parentFunc->returnType.type.structCtx)
        {
            // If we are returning a value from a function, it will have detected this node as a parent and returned
            // the value directly.
            if(value->is<FunctionCallContext>())
            {
                ctx.destructStack();
                ctx.currentBlock = nullptr;
                return ctx.builder.CreateRetVoid();
            }
            auto retRef = ctx.findValue("-retRef");
            assert(retRef);

            auto copy = ctx.functions.find(parentFunc->returnType.type.structCtx->copyConstructorSig());
            assert(copy != ctx.functions.end());

            std::vector<llvm::Value*> args = {retRef,retValue};
            ctx.builder.CreateCall(copy->second, args);
            ctx.destructStack();
            ctx.builder.CreateRetVoid();
            ctx.currentBlock = nullptr;
            return nullptr;
        }


        if(retValue->getType()->getNumContainedTypes() && retValue->getType()->getContainedType(0)->isPointerTy())
            retValue = ctx.builder.CreateLoad(retValue->getType()->getContainedType(0), retValue);
        assert(retValue->getType() == ctx.func->getReturnType());

        ctx.destructStack();
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
        auto* cond = ctx.convertToType(condition->createAST(ctx), condition->returnType, true);
        assert(cond->getType()->getIntegerBitWidth() == 1);

        llvm::BasicBlock* trueBranch = llvm::BasicBlock::Create(*ctx.llvmCtx, "", ctx.func);
        llvm::BasicBlock* mergeBlock = llvm::BasicBlock::Create(*ctx.llvmCtx, "", ctx.func);
        llvm::BasicBlock* falseBranch = elseBody ? llvm::BasicBlock::Create(*ctx.llvmCtx, "", ctx.func) : mergeBlock;


        ctx.builder.CreateCondBr(cond, trueBranch, falseBranch);
        ctx.setInsertPoint(trueBranch);
        body->createAST(ctx);
        if(ctx.currentBlock)
            ctx.builder.CreateBr(mergeBlock);
        trueBranch = ctx.builder.GetInsertBlock();

        if(elseBody)
        {
            ctx.setInsertPoint(falseBranch);
            elseBody->createAST(ctx);
            if(ctx.currentBlock)
                ctx.builder.CreateBr(mergeBlock);
            falseBranch = ctx.builder.GetInsertBlock();
        }
        else
            falseBranch = mergeBlock;

        ctx.setInsertPoint(mergeBlock);

        return nullptr;
    }

    llvm::Value* WhileContext::createAST(ASTContext& ctx) const
    {
        ctx.builder.GetInsertBlock();

        auto* header = llvm::BasicBlock::Create(*ctx.llvmCtx, "while", ctx.func);
        auto* bodyBlock = llvm::BasicBlock::Create(*ctx.llvmCtx, "whileBdy", ctx.func);
        auto* end = llvm::BasicBlock::Create(*ctx.llvmCtx, "whileEnd", ctx.func);

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

    llvm::Value* AssignmentContext::createAST(ASTContext& ctx) const
    {
        llvm::Value* l = lValue->createAST(ctx);
        llvm::Value* r = rValue->createAST(ctx);

        assert(l->getType()->isPointerTy());
        if(!lValue->returnType.type.structCtx)
        {
            if(!l->getType()->getContainedType(0)->isPointerTy() && r->getType()->isPointerTy())
                r = ctx.builder.CreateLoad(r->getType()->getContainedType(0), r);
            ctx.builder.CreateStore(r, l);
            return nullptr;
        }

        auto cc = ctx.functions.find(lValue->returnType.type.structCtx->copyConstructorSig());
        assert(cc != ctx.functions.end());
        assert(cc->second->arg_size() == 2);
        auto structPointerType = lValue->returnType;
        structPointerType.isRef = true;

        std::vector<llvm::Value*> args = {ctx.convertToType(l, structPointerType), ctx.convertToType(r, structPointerType)};
        ctx.builder.CreateCall(cc->second, args);
        return nullptr;
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
    }

    void AssignmentContext::setArgs(ExpressionContext* lValue, ExpressionContext* rValue)
    {
        this->lValue.reset(lValue);
        this->rValue.reset(rValue);
    }

    bool RefAssignmentContext::isConstexpr() const
    {
        return false;
    }

    RefAssignmentContext::RefAssignmentContext(ExpressionContext* lValue, ExpressionContext* rValue) : lValue(lValue), rValue(rValue)
    {
        assert(lValue->returnType.isRef && (rValue->returnType.isLValue || rValue->returnType.isRef));
    }
    void RefAssignmentContext::setArgs(ExpressionContext* lValue, ExpressionContext* rValue)
    {
        assert(lValue->returnType.isRef && (rValue->returnType.isLValue || rValue->returnType.isRef));
        this->lValue.reset(lValue);
        this->rValue.reset(rValue);
    }

    llvm::Value* RefAssignmentContext::createAST(ASTContext& ctx) const
    {
        llvm::Value* l = lValue->createAST(ctx);
        llvm::Value* r = ctx.convertToType(rValue->createAST(ctx), lValue->returnType);

        assert(l->getType()->isPointerTy() && r->getType()->isPointerTy());
        assert(l->getType()->getContainedType(0)->isPointerTy());

        ctx.builder.CreateStore(r, l);
        return nullptr;
    }

    DocumentContext* RefAssignmentContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
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
        std::vector<llvm::Value*> indices = {llvm::ConstantInt::get(*ctx.llvmCtx, llvm::APInt(16, 1))};
        auto* offset = ctx.builder.CreateGEP(type, nullValue, indices);
        return ctx.builder.CreatePtrToInt(offset, ctx.getLLVMType(returnType), "typeSize");
    }

    bool TypeSizeContext::isConstexpr() const
    {
        return !value.isRef;
    }

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
        returnType.type = {"BraneScript::string", ValueType::Struct};
        returnType.isConst = true;
    }

    DocumentContext*
    ConstStringContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new ConstStringContext{*this});
    }

    std::string ConstStringContext::toString() const { return value; }

    llvm::Value* ConstStringContext::createAST(ASTContext& ctx) const
    {
        assert(false);
        return nullptr;
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

        auto func = ctx.functions.find(returnType.type.structCtx->constructorSig());
        assert(func != ctx.functions.end());
        assert(func->second->arg_size() == 1);

        auto structPointerType = returnType;
        structPointerType.isRef = true;

        assert(value->getType()->isPointerTy());
        std::vector<llvm::Value*> arg = {ctx.convertToType(value, structPointerType)};
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

        auto func = ctx.functions.find(returnType.type.structCtx->destructorSig());
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
        auto baseValue = baseExpression->createAST(ctx);
        if(baseValue->getType()->getContainedType(0)->isPointerTy())
            baseValue = ctx.builder.CreateLoad(baseValue->getType()->getContainedType(0), baseValue);

        assert(baseValue->getType()->getContainedType(0)->isStructTy());
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
            auto* sourceValue = sourceExpr->createAST(ctx);
            assert(sourceValue->getType()->isPointerTy());
            llvm::Type* endType = ctx.getLLVMType(returnType);
            return ctx.builder.CreateCast(CastOps::BitCast, sourceValue, endType);
        }

        auto& sourceType = sourceExpr->returnType;
        auto* sourceValue = ctx.convertToType(sourceExpr->createAST(ctx), sourceType, true);
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
        if(lValue->returnType != rValue->returnType)
            assert(lValue->returnType == rValue->returnType);
        returnType = lValue->returnType;
    }

    bool NativeArithmeticContext::isConstexpr() const { return lValue->isConstexpr() && rValue->isConstexpr(); }

    llvm::Value* NativeArithmeticContext::createAST(ASTContext& ctx) const
    {
        auto l = ctx.convertToType(lValue->createAST(ctx), lValue->returnType);
        auto r = ctx.convertToType(rValue->createAST(ctx), rValue->returnType);
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
                        if(isValueTypeSigned(type))
                            return ctx.builder.CreateSDiv(l, r);
                        else
                            return ctx.builder.CreateUDiv(l, r);
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

    bool NativeCompareContext::validCompare(const ValueContext& left, const ValueContext& right)
    {
        if(left.type.storageType == ValueType::Struct || right.type.storageType == ValueType::Struct)
            return false;
        return true;
    }

    NativeCompareContext::NativeCompareContext(Operation op, ExpressionContext* lValue, ExpressionContext* rValue)
        : op(op), lValue(lValue), rValue(rValue)
    {
        assert(lValue->returnType == rValue->returnType);
        returnType.type = {"bool", ValueType::Bool, nullptr};
    }

    bool NativeCompareContext::isConstexpr() const { return lValue->isConstexpr() && rValue->isConstexpr(); }

    llvm::Value* NativeCompareContext::createAST(ASTContext& ctx) const
    {
        auto l = lValue->createAST(ctx);
        auto r = rValue->createAST(ctx);
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
        auto funcItr = ctx.functions.find(function->signature());
        assert(funcItr != ctx.functions.end());
        llvm::Function* func = funcItr->second;

        bool argRet = !returnType.isRef && returnType.type.structCtx;
        std::vector<llvm::Value*> args;
        if(argRet)
        {
            // Avoid copy and construction operations by just returning the argument
            if(parent->is<ReturnContext>() && getParent<FunctionContext>()->returnType == returnType)
                args.push_back(ctx.findValue("-retRef"));
            else
            {
                // Construct struct to be returned into
                args.push_back(ctx.builder.CreateAlloca(ctx.getLLVMType(returnType)));
                auto constructor = ctx.functions.find(returnType.type.structCtx->constructor->signature());
                assert(constructor != ctx.functions.end());

                ctx.builder.CreateCall(constructor->second, args[0]);
            }
        }
        size_t argIndex = 0;
        for(auto& arg : arguments)
            args.push_back(ctx.convertToType(arg->createAST(ctx), *function->arguments[argIndex++]));

        auto retVal = ctx.builder.CreateCall(func, args);
        if(!returnType.isRef && returnType.type.structCtx)
            return args[0];
        return retVal;
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

    std::string FunctionContext::signature() const
    {
        std::string sig = longId();
        sig += "(";

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
        std::vector<llvm::Type*> argTypes;
        bool argReturn = false;
        if(!returnType.isRef && returnType.type.structCtx)
        {
            auto thisRefType = returnType;
            thisRefType.isRef = true;
            argTypes.push_back(ctx.getLLVMType(thisRefType));
            argReturn = true;
        }

        for(auto& arg : arguments)
            argTypes.push_back(ctx.getLLVMType(*arg));
        auto retType = argReturn ? ctx.getLLVMType({}) : ctx.getLLVMType(returnType);
        llvm::FunctionType* funcType = llvm::FunctionType::get(retType, argTypes, false);

        bool exported = false;
        auto linkage = llvm::Function::PrivateLinkage;
        if(!body)
            linkage = llvm::Function::AvailableExternallyLinkage;
        else if(getParent<LibraryContext>())
        {
            exported = true;
            linkage = llvm::Function::ExternalLinkage;
            ctx.exportedFunctions.push_back(signature());
        }

        ctx.func = llvm::Function::Create(funcType, linkage, signature(), *ctx.module);
        ctx.functions.insert({signature(), ctx.func});

        ctx.pushScope();

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
            std::string& id = arguments[index]->identifier.text;
            arg.setName(id);
            ctx.addValue(id, &arg, *arguments[index++]);
        }

        if(body)
        {
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

        for(auto& f : functions)
        {
            if(f->identifier.text == id)
                return f.get();
        }
        return DocumentContext::findIdentifier(id, searchOptions);
    }

    void StructContext::getFunction(const std::string& identifier,
                                    std::list<FunctionContext*>& overrides,
                                    uint8_t searchOptions)
    {
        for(auto& f : functions)
        {
            if(f->identifier.text == identifier)
                overrides.push_back(f.get());
        }
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

    std::string StructContext::constructorSig() const
    {
        std::string name = longId();
        return name + "::_construct(ref " + name + ")";
    }

    std::string StructContext::moveConstrutorSig() const
    {
        std::string name = longId();
        return name + "::_move(ref " + name + ",ref " + name + ")";
    }

    std::string StructContext::copyConstructorSig() const
    {
        std::string name = longId();
        return name + "::_copy(ref " + name + ",const ref " + name + ")";
    }

    std::string StructContext::destructorSig() const
    {
        std::string name = longId();
        return name + "::_destruct(ref " + name + ")";
    }

    llvm::Value* StructContext::createAST(ASTContext& ctx) const
    {
        assert(false);
        return nullptr;
    }

    DocumentContext* LibraryContext::getNodeAtChar(TextPos pos)
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

    DocumentContext* LibraryContext::findIdentifier(const std::string& id, uint8_t searchOptions)
    {
        for(auto& g : globals)
        {
            if(g->identifier.text == id)
                return g.get();
        }

        for(auto& f : functions)
        {
            if(f->identifier.text == id)
                return f.get();
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

    void LibraryContext::getFunction(const std::string& id, std::list<FunctionContext*>& overrides, uint8_t searchOptions)
    {
        DocumentContext::getFunction(id, overrides, searchOptions);
        for(auto& f : functions)
        {
            if(f->identifier.text == id)
                overrides.push_back(f.get());
        }
    }

    std::string LibraryContext::longId() const
    {
        auto prefix = DocumentContext::longId();
        if(prefix.empty())
            return identifier.text;
        return prefix + "::" + identifier.text;
    }

    DocumentContext* LibraryContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new LibraryContext{};
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

    llvm::Value* LibraryContext::createAST(ASTContext& ctx) const
    {
        if(!ctx.exports.contains(longId()))
            ctx.exports.insert(longId());
        for(auto& g : globals)
        {
            auto type = ctx.getLLVMType(*g);
            auto glob = ctx.module->getOrInsertGlobal(g->identifier.text, type, ctx.makeGlobalVariable(*g, true));
            ctx.globals.insert({g->longId(), glob});
        }
        return nullptr;
    }

    DocumentContext* ScriptContext::getNodeAtChar(TextPos pos)
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
        for(auto& lib : exports)
        {
            auto node = lib.second->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& i : imports)
        {
            auto node = i.second->getNodeAtChar(pos);
            if(node)
                return node;
        }
        if(!range.posInRange(pos))
            return nullptr;
        return this;
    }

    DocumentContext* ScriptContext::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        auto l = exports.find(identifier);
        if(l != exports.end())
            return l->second.get();

        for(auto& g : globals)
        {
            if(g->identifier.text == identifier)
                return g.get();
        }

        for(auto& f : functions)
        {
            if(f->identifier.text == identifier)
                return f.get();
        }

        for(auto& s : structs)
        {
            if(s->identifier.text == identifier)
                return s.get();
        }
        return nullptr;
    }

    void ScriptContext::getFunction(const std::string& identifier,
                                    std::list<FunctionContext*>& overrides,
                                    uint8_t searchOptions)
    {
        for(auto& f : functions)
        {
            if(f->identifier.text == identifier)
                overrides.push_back(f.get());
        }

        if(!(searchOptions & IDSearchOptions_ParentsOnly))
        {
            for(auto& lib : exports)
                lib.second->getFunction(identifier, overrides, searchOptions);
        }
    }

    llvm::Value* ScriptContext::createAST(ASTContext& ctx) const
    {
        for(auto& g : globals)
        {
            auto type = ctx.getLLVMType(*g);
            auto glob = ctx.module->getOrInsertGlobal(g->identifier.text, type, ctx.makeGlobalVariable(*g, false));
            ctx.globals.insert({g->longId(), glob});
        }
        for(auto& lib : imports)
            lib.second->createAST(ctx);
        for(auto& lib : exports)
            lib.second->createAST(ctx);

        for(auto func : callOrder)
            func->createAST(ctx);

        std::string modErr;
        llvm::raw_string_ostream modErrStr(modErr);
        if(llvm::verifyModule(*ctx.module, &modErrStr))
        {
            ctx.printModule();
            std::fprintf(stderr, "Invalid IR result, verifyModule returned error: %s\n\n", modErr.c_str());
            throw std::runtime_error("Module IR invalid! [" + modErr + "]");
        }

        if(ctx.mpm)
            ctx.mpm->run(*ctx.module, *ctx.mam);

        return nullptr;
    }

    DocumentContext* ScriptContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        auto* copy = new ScriptContext{};
        copyBase(this, copy);

        for(auto& var : globals)
            copy->globals.emplace_back(assertCast<LabeledValueContext>(var->deepCopy(callback)));
        for(auto& s : structs)
            copy->structs.emplace_back(assertCast<StructContext>(s->deepCopy(callback)));
        for(auto& func : functions)
            copy->functions.emplace_back(assertCast<FunctionContext>(func->deepCopy(callback)));
        for(auto& lib : exports)
            copy->exports.insert({lib.first, assertCast<LibraryContext>(lib.second->deepCopy(callback))});
        for(auto& lib : imports)
        {
            auto* imp = assertCast<ImportContext>(lib.second->deepCopy(callback));
            copy->imports.emplace(imp->library, imp);
            delete imp;
        }

        return callback(copy);
    }

    IRScript ScriptContext::compile(llvm::LLVMContext* ctx, bool optimize, bool print)
    {
        IRScript script;
        script.id = id;
        llvm::LoopAnalysisManager LAM;
        llvm::CGSCCAnalysisManager CGAM;

        ASTContext cc(ctx, id);
        if(optimize)
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
                llvm::PassBuilder::OptimizationLevel::O2, llvm::ThinOrFullLTOPhase::FullLTOPreLink));
        }

        createAST(cc);

        if(print)
            cc.printModule();

        llvm::raw_string_ostream bitcodeStream(script.bitcode);
        llvm::WriteBitcodeToFile(*cc.module, bitcodeStream);
        bitcodeStream.str();

        for(auto& lib : cc.exports)
            script.exportedLibs.push_back(lib);
        for(auto& lib : cc.imports)
            script.importedLibs.push_back(lib);
        script.exportedFunctions = std::move(cc.exportedFunctions);
        script.exportedGlobals = std::move(cc.exportedGlobals);
        for(auto& s : cc.definedStructs)
        {
            if(!s.second.isExported)
                continue;
            script.exportedStructs.push_back(std::move(s.second.def));
        }

        return std::move(script);
    }

    DocumentContext* LibrarySet::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        for(auto& lib : exports)
        {
            auto* ident = lib->findIdentifier(identifier, 0);
            if(ident)
                return ident;
        }
        return nullptr;
    }

    void LibrarySet::getFunction(const std::string& identifier,
                                 std::list<FunctionContext*>& overrides,
                                 uint8_t searchOptions)
    {
        for(auto& lib : exports)
            lib->getFunction(identifier, overrides, searchOptions);
    }

    DocumentContext* LibrarySet::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new LibrarySet{*this});
    }

    std::string LibrarySet::longId() const
    {
        if(exports.empty())
            return "";
        return (*exports.begin())->longId();
    }

    llvm::Value* LibrarySet::createAST(ASTContext& ctx) const
    {
        assert(false);
        return nullptr;
    }

    DocumentContext* ImportContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const
    {
        return callback(new ImportContext{*this});
    }

    llvm::Value* ImportContext::createAST(ASTContext& ctx) const
    {
        if(!ctx.imports.contains(library))
            ctx.imports.insert(library);
        for(auto lib : importedModules)
        {
            for(auto& g : lib->globals)
            {
                auto type = ctx.getLLVMType(*g);
                auto glob = ctx.module->getOrInsertGlobal(g->identifier.text, type, ctx.makeExternGlobalVariable(*g));
                ctx.globals.insert({g->longId(), glob});
            }

            for(auto& f : lib->functions)
            {
                std::vector<llvm::Type*> argTypes;
                argTypes.reserve(f->arguments.size());
                for(auto& arg : f->arguments)
                    argTypes.push_back(ctx.getLLVMType(*arg));
                bool argReturn = false;
                if(!f->returnType.isRef && f->returnType.type.structCtx)
                {
                    auto thisRefType = f->returnType;
                    thisRefType.isRef = true;
                    argTypes.push_back(ctx.getLLVMType(thisRefType));
                    argReturn = true;
                }
                llvm::Type* retType = ctx.getLLVMType(f->returnType);
                if(argReturn)
                    retType = ctx.getLLVMType({});
                llvm::FunctionType* funcType = llvm::FunctionType::get(retType, argTypes, false);

                auto linkage = llvm::Function::ExternalLinkage;
                std::string id = f->signature();
                assert(!id.empty());
                ctx.func = llvm::Function::Create(funcType, linkage, id, *ctx.module);
                ctx.functions.insert({id, ctx.func});
            }

            for(auto& s : lib->structs)
            {
                for(auto& f : s->functions)
                {
                    std::vector<llvm::Type*> argTypes;
                    argTypes.reserve(f->arguments.size());
                    for(auto& arg : f->arguments)
                        argTypes.push_back(ctx.getLLVMType(*arg));
                    bool argReturn = false;
                    if(!f->returnType.isRef && f->returnType.type.structCtx)
                    {
                        auto thisRefType = f->returnType;
                        thisRefType.isRef = true;
                        argTypes.push_back(ctx.getLLVMType(thisRefType));
                        argReturn = true;
                    }
                    llvm::Type* retType = ctx.getLLVMType(f->returnType);
                    if(argReturn)
                        retType = ctx.getLLVMType({});
                    llvm::FunctionType* funcType = llvm::FunctionType::get(retType, argTypes, false);

                    auto linkage = llvm::Function::ExternalLinkage;
                    std::string id = f->signature();
                    assert(!id.empty());
                    ctx.func = llvm::Function::Create(funcType, linkage, id, *ctx.module);
                    ctx.functions.insert({id, ctx.func});
                }
            }
        }

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
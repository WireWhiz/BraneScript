//
// Created by wirewhiz on 14/10/22.
//

#include "compiler.h"
#include <memory>
#include "antlr4/braneLexer.h"
#include "ANTLRInputStream.h"
#include "aotInlineFunctions/aotInlineFunction.h"
#include "aotInlineFunctions/aotNativeOperators.h"
#include "aotNodes/aotFlowNodes.h"
#include "aotNodes/aotLogicNodes.h"
#include "aotNodes/aotModifierNodes.h"
#include "aotNodes/aotValueNodes.h"
#include "library.h"
#include "linker.h"
#include "nativeTypes.h"
#include "structDefinition.h"

namespace BraneScript
{
    class ScriptCompiler
    {
        std::unique_ptr<ScriptCompilerCtx> _compileCtx;
        robin_hood::unordered_map<std::string, AotValue*> _globals;
        FunctionCompilerCtx* _currentFunc = nullptr;

        struct Scope
        {
            AotNodeList* node = nullptr;
            robin_hood::unordered_map<std::string, AotValue*> localValues;
        };

        std::list<Scope> _scopes;

        void pushScope() { _scopes.push_back({}); }

        void popScope() { _scopes.pop_back(); }

        Scope& currentScope() { return _scopes.back(); }

        const StructDef* visitStruct(StructContext* ctx)
        {
            std::string id = ctx->longId();
            auto def = new StructDef(id);
            for(auto& m : ctx->variables)
                def->addMemberVar(m->identifier, _compileCtx->getType(m->type.identifier));
            def->padMembers();

            return def;
        }

        AotValue* regFromValueCtx(LabeledValueContext* valueCtx)
        {
            auto* type = _compileCtx->getType(valueCtx->type.identifier);
            if(!type)
                throw CompilerError("Type " + valueCtx->type.identifier + " not found!");
            uint8_t flags = 0;
            if(valueCtx->isConst)
                flags |= AotValue::Const;
            if(valueCtx->isRef)
                flags |= AotValue::StackRef;
            return _currentFunc->newReg(type, flags);
        }

        AotValue* getVar(const std::string& identifier)
        {
            for(auto i = _scopes.rbegin(); i != _scopes.rend(); ++i)
            {
                auto v = i->localValues.find(identifier);
                if(v != i->localValues.end())
                    return v->second;
            }
            auto v = _globals.find(identifier);
            if(v != _globals.end())
                return v->second;
            return nullptr;
        }

        AotConstNode* visitConst(const ConstValueContext* ctx)
        {
            if(auto* node = dynamic_cast<const ConstBoolContext*>(ctx))
                return new AotConstNode(node->value);
            if(auto* node = dynamic_cast<const ConstCharContext*>(ctx))
                return new AotConstNode(node->value);
            if(auto* node = dynamic_cast<const ConstIntContext*>(ctx))
                return new AotConstNode(node->value);
            if(auto* node = dynamic_cast<const ConstFloatContext*>(ctx))
                return new AotConstNode(node->value);
            if(auto* node = dynamic_cast<const ConstStringContext*>(ctx))
                return new AotConstNode(node->value);
            assert(false);
            return nullptr;
        }

        AotNode* visitDeclaration(const LabeledValueConstructionContext* ctx)
        {
            AotValue* value = regFromValueCtx(ctx->value);
            currentScope().localValues.insert({ctx->value->identifier, value});
            if(value->type->type() != ValueType::Struct)
                return new AotValueConstruction(value);
            return new AotAllocNode(value);
        }

        AotNode* visitFunctionCall(const FunctionCallContext* ctx)
        {
            std::vector<AotNode*> args;
            for(auto& arg : ctx->arguments)
                args.push_back(visitExpression(arg.get()));

            // Replace a call with inline code if this is an inlined function
            std::string name = ctx->function->signature();
            if(const AotInlineFunction* func = _compileCtx->compiler->getInlineFunction(name, args))
                return func->generateAotTree(args);

            return new AotFunctionCall(name, _compileCtx->getType(ctx->returnType.type.identifier), args);
        }

        AotDerefNode* visitMemberAccess(const MemberAccessContext* ctx)
        {
            auto* arg = visitExpression(ctx->baseExpression.get());
            auto* baseType = dynamic_cast<const StructDef*>(arg->resType());
            assert(baseType);
            assert(ctx->member < baseType->memberVars().size());
            const auto& member = baseType->memberVars()[ctx->member];

            return new AotDerefNode(arg, member.type, member.offset);
        }

        AotValueReference* visitValueAccess(const LabeledValueReferenceContext* ctx)
        {
            return new AotValueReference(getVar(ctx->value->identifier));
        }

        AotNode* visitExpression(const ExpressionContext* ctx)
        {
            assert(ctx);
            if(auto* node = dynamic_cast<const ConstValueContext*>(ctx))
                return visitConst(node);
            if(auto* node = dynamic_cast<const LabeledValueConstructionContext*>(ctx))
                return visitDeclaration(node);
            if(auto* node = dynamic_cast<const FunctionCallContext*>(ctx))
                return visitFunctionCall(node);
            if(auto* node = dynamic_cast<const MemberAccessContext*>(ctx))
                return visitMemberAccess(node);
            if(auto* node = dynamic_cast<const LabeledValueReferenceContext*>(ctx))
                return visitValueAccess(node);
            if(auto error = dynamic_cast<const ExpressionErrorContext*>(ctx))
                throw std::runtime_error("Document with expression error node cannot be compiled (error: " +
                                         error->message + ". line: " + std::to_string(error->line) + ")");
            assert(false);
            return nullptr;
        }

        AotNode* visitAssignment(const AssignmentContext* ctx)
        {
            return new AotAssignNode(visitExpression(ctx->lValue.get()), visitExpression(ctx->rValue.get()));
        }

        AotNodeList* visitReturn(const ReturnContext* ctx)
        {
            auto nodes = new AotNodeList{};
            // Destruct local variables

            /* We store destruct operations in their own list so we can detect if we need to generate a holder variable
             * or not */
            AotNodeList* cleanup = nullptr;
            // Stop one before function scope, no Structs will ever be passed that we need to destruct
            auto functionScope = --_scopes.rend();
            for(auto i = _scopes.rbegin(); i != functionScope; ++i)
            {
                for(auto& v : i->localValues)
                {
                    if(v.second->type->type() != ValueType::Struct)
                        continue;
                    if(!cleanup)
                        cleanup = new AotNodeList{};
                    cleanup->appendStatement(new AotValueDestruction(v.second));
                }
            }

            // Store result to return (That way it isn't destroyed by a destructor before being read, asmjit will
            // optimize out unnecessary mov commands if this was not actually needed)
            AotValue* retValHolder = nullptr;
            if(ctx->value && cleanup)
            {
                auto result = visitExpression(ctx->value.get());
                retValHolder = _currentFunc->newReg(result->resType(), AotValue::Temp);
                if(result->resType()->type() == ValueType::Struct)
                    nodes->appendStatement(new AotMallocNode(retValHolder));
                nodes->appendStatement(new AotAssignNode(new AotValueReference(retValHolder), result));
            }

            if(cleanup)
                nodes->appendStatement(cleanup);

            // Return value
            if(!ctx->value)
            {
                nodes->appendStatement(new AotReturnNode());
                return nodes;
            }
            if(cleanup)
                nodes->appendStatement(new AotReturnValueNode(new AotValueReference(retValHolder)));
            else
                nodes->appendStatement(new AotReturnValueNode(visitExpression(ctx->value.get())));
            return nodes;
        }

        AotNodeList* visitIf(const IfContext* ctx)
        {
            auto operations = new AotNodeList{};
            uint32_t jumpID = _currentFunc->newJumpTargetID();
            uint32_t jumpID2 = -1;
            if(ctx->elseBody)
                jumpID2 = _currentFunc->newJumpTargetID();

            operations->appendStatement(new AotJumpFalse(visitExpression(ctx->condition.get()), jumpID));
            operations->appendStatement(visitStatement(ctx->body.get()));
            if(ctx->elseBody) // If the condition was true, and we have an else, skip the else.
                operations->appendStatement(new AotJump(jumpID2));
            operations->appendStatement(new AotJumpTarget(jumpID));
            if(ctx->elseBody)
            {
                operations->appendStatement(visitStatement(ctx->elseBody.get()));
                operations->appendStatement(new AotJumpTarget(jumpID2));
            }

            return operations;
        }

        AotNodeList* visitWhile(const WhileContext* ctx)
        {
            auto operations = new AotNodeList{};
            uint32_t restartTarget = _currentFunc->newJumpTargetID();
            uint32_t endTarget = _currentFunc->newJumpTargetID();

            operations->appendStatement(new AotJumpTarget(restartTarget));
            operations->appendStatement(new AotJumpFalse(visitExpression(ctx->condition.get()), endTarget));
            operations->appendStatement(visitStatement(ctx->body.get()));
            operations->appendStatement(new AotJump(restartTarget));
            operations->appendStatement(new AotJumpTarget(endTarget));

            return operations;
        }

        AotNode* visitStatement(const StatementContext* ctx)
        {
            assert(ctx);
            if(auto expr = dynamic_cast<const ExpressionContext*>(ctx))
                return visitExpression(expr);
            if(auto assignment = dynamic_cast<const AssignmentContext*>(ctx))
                return visitAssignment(assignment);
            if(auto ret = dynamic_cast<const ReturnContext*>(ctx))
                return visitReturn(ret);
            if(auto ifStmt = dynamic_cast<const IfContext*>(ctx))
                return visitIf(ifStmt);
            if(auto whileStmt = dynamic_cast<const WhileContext*>(ctx))
                return visitWhile(whileStmt);
            if(auto error = dynamic_cast<const StatementErrorContext*>(ctx))
                throw std::runtime_error("Document with statement error node cannot be compiled (error: " +
                                         error->message + ". line: " + std::to_string(error->line) + ")");

            assert(false);
            return nullptr;
        }

        AotNodeList* visitScope(const ScopeContext* ctx)
        {
            auto* scope = new AotNodeList{};
            pushScope();
            currentScope().node = scope;
            for(auto& statement : ctx->statements)
                scope->appendStatement(visitStatement(statement.get()));

            // Destruct all but function argument scope
            if(_scopes.size() > 1)
            {
                for(auto& v : currentScope().localValues)
                {
                    if(v.second->type->type() != ValueType::Struct)
                        continue;
                    scope->appendStatement(new AotValueDestruction(v.second));
                }
            }
            popScope();
            return scope;
        }

        void visitFunction(const FunctionContext* ctx)
        {
            FunctionCompilerCtx funcCtx(*_compileCtx, ctx->signature());
            _currentFunc = &funcCtx;

            IRFunction irFunc;
            irFunc.sig = funcCtx.signature;
            irFunc.returnType = {ctx->returnType.type.identifier, ctx->returnType.isConst, ctx->returnType.isRef};

            funcCtx.function = &irFunc;

            pushScope();
            for(auto& arg : ctx->arguments)
            {
                irFunc.arguments.push_back({arg.type.identifier, arg.isConst, arg.isRef});
                auto type = _compileCtx->getType(arg.type.identifier);
                if(!type)
                    throw std::runtime_error("Could not find type! " + arg.type.identifier);
                currentScope().localValues.insert({arg.identifier.text, funcCtx.newReg(type, AotValue::Initialized)});
            }

            auto operations = std::unique_ptr<AotNode>(visitScope(ctx->body.get()));
            // TODO in the future figure out a way to run constant expressions at compile time using this node tree

            popScope();
            assert(_scopes.empty());

            operations->optimize();
            operations->generateBytecode(funcCtx);

            _compileCtx->script->localFunctions.push_back(std::move(irFunc));
            _currentFunc = nullptr;
        }

        void visitScript(const ScriptContext* script)
        {

            for(auto& e : script->exports)
            {
                for(auto& s : e.second->structs)
                    _compileCtx->localStructDefs.emplace_back(visitStruct(s.get()));
            }
            for(auto& s : script->structs)
                _compileCtx->localStructDefs.emplace_back(visitStruct(s.get()));

            for(auto& g : script->globals)
                _globals.insert({g->longId(), _compileCtx->newGlobal(_compileCtx->getType(g->type.identifier), 0)});

            // Pre-register every function so that linking works correctly

            int16_t funcIndex = 0;
            for(auto& exp : script->exports)
            {
                for(auto& s : exp.second->structs)
                {
                    for(auto& f : s->functions)
                        _compileCtx->functionIndices.insert({f->signature(), funcIndex++});
                }
                for(auto& f : exp.second->functions)
                    _compileCtx->functionIndices.insert({f->signature(), funcIndex++});
            }
            for(auto& s : script->structs)
            {
                for(auto& f : s->functions)
                    _compileCtx->functionIndices.insert({f->signature(), funcIndex++});
            }
            for(auto& f : script->functions)
                _compileCtx->functionIndices.insert({f->signature(), funcIndex++});

            // Visit and compile functions
            for(auto& exp : script->exports)
            {
                for(auto& s : exp.second->structs)
                {
                    for(auto& f : s->functions)
                        visitFunction(f.get());
                }
                for(auto& f : exp.second->functions)
                    visitFunction(f.get());
            }
            for(auto& s : script->structs)
            {
                for(auto& f : s->functions)
                    visitFunction(f.get());
            }
            for(auto& f : script->functions)
                visitFunction(f.get());
        }

      public:
        IRScript* build(Compiler* compiler, const ScriptContext* document)
        {
            _compileCtx = std::make_unique<ScriptCompilerCtx>();
            _compileCtx->compiler = compiler;
            _compileCtx->script = std::make_unique<IRScript>();

            visitScript(document);

            return _compileCtx->script.release();
        }
    };

    Compiler::Compiler()
    {
        for(auto& type : getNativeTypes())
            registerType(type);

        // Define our native operators as inline functions, to be inserted directly into the Aot tree
        auto scalarTypes = {getNativeTypeDef(ValueType::UInt32),
                            getNativeTypeDef(ValueType::UInt64),
                            getNativeTypeDef(ValueType::Int32),
                            getNativeTypeDef(ValueType::Int64),
                            getNativeTypeDef(ValueType::Float32),
                            getNativeTypeDef(ValueType::Float64)};

        for(auto type : scalarTypes)
        {
            registerInlineFunction(new NativeBinaryOperator<AotAddNode>("+", type));
            registerInlineFunction(new NativeBinaryOperator<AotSubNode>("-", type));
            registerInlineFunction(new NativeBinaryOperator<AotMulNode>("*", type));
            registerInlineFunction(new NativeBinaryOperator<AotDivNode>("/", type));
            registerInlineFunction(
                new NativeBinaryOperator<AotCompareNode, AotCompareNode::Mode>("==", type, AotCompareNode::Equal));
            registerInlineFunction(
                new NativeBinaryOperator<AotCompareNode, AotCompareNode::Mode>("!=", type, AotCompareNode::NotEqual));
            registerInlineFunction(
                new NativeBinaryOperator<AotCompareNode, AotCompareNode::Mode>(">", type, AotCompareNode::Greater));
            registerInlineFunction(new NativeBinaryOperator<AotCompareNode, AotCompareNode::Mode>(
                ">=", type, AotCompareNode::GreaterEqual));
            registerInlineFunction(
                new NativeBinaryOperator<AotCompareNode, AotCompareNode::Mode>("<", type, AotCompareNode::Less));
            registerInlineFunction(
                new NativeBinaryOperator<AotCompareNode, AotCompareNode::Mode>("<=", type, AotCompareNode::LessEqual));

            for(auto targetType : scalarTypes)
            {
                if(targetType == type)
                    continue;
                registerInlineFunction(new NativeCastOperator(targetType, type));
            }
        }

        auto intTypes = {getNativeTypeDef(ValueType::UInt32),
                         getNativeTypeDef(ValueType::UInt64),
                         getNativeTypeDef(ValueType::Int32),
                         getNativeTypeDef(ValueType::Int64)};
        auto charType = getNativeTypeDef(ValueType::Char);
        for(auto type : intTypes)
        {
            registerInlineFunction(new NativeCastOperator(charType, type));
            registerInlineFunction(new NativeCastOperator(type, charType));
        }

        registerInlineFunction(new NativeBinaryOperator<AotCompareNode, AotCompareNode::Mode>(
            "==", getNativeTypeDef(ValueType::Bool), AotCompareNode::Equal));
        registerInlineFunction(new NativeBinaryOperator<AotCompareNode, AotCompareNode::Mode>(
            "==", getNativeTypeDef(ValueType::Char), AotCompareNode::Equal));

        registerInlineFunction(new NativeBinaryOperator<AotCompareNode, AotCompareNode::Mode>(
            "!=", getNativeTypeDef(ValueType::Bool), AotCompareNode::NotEqual));
        registerInlineFunction(new NativeBinaryOperator<AotCompareNode, AotCompareNode::Mode>(
            "!=", getNativeTypeDef(ValueType::Char), AotCompareNode::NotEqual));
    }

    void Compiler::registerType(const TypeDef* type) { _nativeTypes[type->name()] = type; }

    IRScript* Compiler::compile(const ScriptContext* script) { return ScriptCompiler().build(this, script); }

    StructDef Compiler::structFromDocumentContext(const StructContext* ctx)
    {
        auto def = StructDef(ctx->longId());
        for(auto& var : ctx->variables)
        {
            if(_nativeTypes.contains(var->type.identifier))
                def.addMemberVar(var->identifier, _nativeTypes.at(var->type.identifier));
            else
            {
                if(!_registeredStructs.contains(var->type.identifier))
                    _registeredStructs.insert(
                        {var->type.identifier, std::make_unique<StructDef>(var->type.identifier)});
                def.addMemberVar(var->identifier, _registeredStructs.at(var->type.identifier).get());
            }
        }
        if(ctx->packed)
            def.packMembers();
        else
            def.padMembers();
        return std::move(def);
    }

    void Compiler::updateDefinedStructs(const LibraryContext* lib)
    {
        for(auto& s : lib->structs)
        {
            auto newDef = structFromDocumentContext(s.get());
            std::string id = newDef.name();
            if(!_registeredStructs.contains(id))
                _registeredStructs.insert({id, std::make_unique<StructDef>(std::move(newDef))});
            else
                *_registeredStructs[id] = std::move(newDef);
        }
    }

    void Compiler::updateDefinedStructs(const ScriptContext* script)
    {
        for(auto& lib : script->exports)
            updateDefinedStructs(lib.second.get());
    }

    void Compiler::clearDefinedStructs() { _registeredStructs.clear(); }

    const TypeDef* Compiler::getType(const std::string& id) const
    {
        auto nt = _nativeTypes.find(id);
        if(nt != _nativeTypes.end())
            return nt->second;
        if(_linker)
        {
            if(auto lt = _linker->getType(id))
                return lt;
        }
        auto rt = _registeredStructs.find(id);
        if(rt != _registeredStructs.end())
            return rt->second.get();
        return nullptr;
    }

    void Compiler::registerInlineFunction(AotInlineFunction* function)
    {
        _inlineFunctions.insert({function->name(), std::unique_ptr<AotInlineFunction>(function)});
    }

    const AotInlineFunction* Compiler::getInlineFunction(const std::string& name, const std::vector<AotNode*>& args)
    {
        const auto list = _inlineFunctions.find(name);
        if(list == _inlineFunctions.end())
            return nullptr;
        return list->second.get();
    }

    void Compiler::setLinker(Linker* linker) { _linker = linker; }

    AotValue* ScriptCompilerCtx::newGlobal(const TypeDef* type, uint8_t flags)
    {
        assert(type);
        auto value = new AotValue();
        value->type = type;
        value->flags = flags | AotValue::Initialized;
        value->storageType = ValueStorageType_Global;
        value->ptrOffset = script->globalVarAllocSize;
        script->globalVarAllocSize += type->size();
        globalValues.push_back(std::unique_ptr<AotValue>(value));
        return value;
    }

    int16_t ScriptCompilerCtx::linkFunction(const std::string& sig)
    {
        assert(!sig.empty());
        if(functionIndices.contains(sig))
            return functionIndices.at(sig);
        int16_t index = -static_cast<int16_t>(script->linkedFunctions.size() + 1);
        functionIndices.insert({sig, index});
        script->linkedFunctions.push_back(sig);
        return index;
    }

    int16_t ScriptCompilerCtx::linkConstructor(const StructDef* type)
    {
        std::string name = type->name();
        return linkFunction(std::string(type->name()) + "::_construct(ref " + name + ")");
    }

    int16_t ScriptCompilerCtx::linkMoveConstructor(const StructDef* type)
    {
        std::string name = type->name();
        return linkFunction(std::string(type->name()) + "::_move(ref " + name + ",ref " + type->name() + ")");
    }

    int16_t ScriptCompilerCtx::linkCopyConstructor(const StructDef* type)
    {
        std::string name = type->name();
        return linkFunction(std::string(type->name()) + "::_copy(ref " + name + ",const ref " + type->name() + ")");
    }

    int16_t ScriptCompilerCtx::linkDestructor(const StructDef* type)
    {
        std::string name = type->name();
        return linkFunction(name + "::_destruct(ref " + name + ")");
    }

    const TypeDef* ScriptCompilerCtx::getType(const std::string& id) const
    {
        for(auto& ls : localStructDefs)
        {
            if(ls->name() == id)
                return ls.get();
        }
        return compiler->getType(id);
    }

    FunctionCompilerCtx::FunctionCompilerCtx(ScriptCompilerCtx& s, std::string sig)
        : script(s), signature(std::move(sig))
    {}

    AotValue* FunctionCompilerCtx::newReg(const TypeDef* type, uint8_t flags)
    {
        return newCustomReg(type, (type->type() != ValueType::Struct) ? ValueStorageType_Reg : ValueStorageType_Ptr, flags);
    }

    AotValue* FunctionCompilerCtx::newCustomReg(const TypeDef* type, ValueStorageType storageType, uint8_t flags)
    {
        assert(type);
        auto* value = new AotValue{};
        value->type = type;
        value->flags = flags;
        value->storageType = storageType;

        size_t newValIndex = registers.push({});
        Value& newVal = registers[newValIndex];
        newVal.index = newValIndex;
        newVal.valueType = type->type();
        newVal.storageType = value->storageType;

        if(!(value->flags & AotValue::Initialized))
        {
            assert(value->storageType != ValueStorageType_Null);
            appendCode(Operand::INITR, newVal);
            value->flags |= AotValue::Initialized;
        }

        if(function->maxRegs < registers.size())
            function->maxRegs = registers.size();

        auto id = values.push({std::unique_ptr<AotValue>(value), newValIndex, true});
        value->id = id;
        return value;
    }

    AotValue* FunctionCompilerCtx::castValue(AotValue* value)
    {
        if(value->isCompare())
            return castReg(value);
        if(value->isGlobal())
            return derefPtr(value, value->type, value->ptrOffset);
        assert(value->storageType != ValueStorageType_Null);
        return value;
    }

    AotValue* FunctionCompilerCtx::newConst(const TypeDef* type, uint8_t flags)
    {
        assert(type);
        auto* value = new AotValue();
        value->type = type;
        value->flags = flags;
        value->storageType = ValueStorageType_Const;

        auto newValIndex = memoryLocations.push({});
        Value& newVal = memoryLocations[newValIndex];
        newVal.index = newValIndex;
        newVal.valueType = type->type();
        newVal.storageType = value->storageType;

        if(function->maxMemLocations < memoryLocations.size())
            function->maxMemLocations = memoryLocations.size();

        auto id = values.push({std::unique_ptr<AotValue>(value), newValIndex, false});
        value->id = id;
        return value;
    }

    AotValue* FunctionCompilerCtx::newCompareResult()
    {
        auto* value = new AotValue();
        value->type = getNativeTypeDef(ValueType::Bool);
        value->flags = AotValue::Temp;
        value->storageType = ValueStorageType_Const;

        assert(!compareFlagsInUse);
        compareFlagsInUse = true;

        auto id = values.push({std::unique_ptr<AotValue>(value), 0, false});
        return value;
    }

    AotValue* FunctionCompilerCtx::castTemp(AotValue* value)
    {
        assert(function);
        if(value->isTemp())
            return value;
        AotValue* tempValue = newReg(value->type, AotValue::Temp | (AotValue::Constexpr & value->flags));
        appendCode(MOV, serialize(tempValue), serialize(value));
        return tempValue;
    }

    AotValue* FunctionCompilerCtx::castReg(AotValue* value)
    {
        if(value->storageType == ValueStorageType_Reg || value->storageType == ValueStorageType_Ptr)
            return value;
        if(value->isGlobal())
            return castReg(derefPtr(value, value->type, value->ptrOffset));
        auto* regValue = newReg(value->type, AotValue::Temp);
        if(!value->isCompare())
        {
            assert(regValue->flags & AotValue::Initialized);
            appendCode(MOV, serialize(regValue), serialize(value));
            return regValue;
        }
        assert(value->isCompare());
        auto ct = value->compareType;
        releaseValue(value);
        switch(ct)
        {
            case AotValue::EqualRes:
            {
                appendCode(SETE, serialize(regValue));
                return regValue;
            }
            case AotValue::NotEqualRes:
            {
                appendCode(SETNE, serialize(regValue));
                return regValue;
            }
            case AotValue::AboveRes:
            {
                appendCode(SETA, serialize(regValue));
                return regValue;
            }
            case AotValue::GreaterRes:
            {
                appendCode(SETG, serialize(regValue));
                return regValue;
            }
            case AotValue::AboveEqualRes:
            {
                appendCode(SETAE, serialize(regValue));
                return regValue;
            }
            case AotValue::GreaterEqualRes:
            {
                appendCode(SETGE, serialize(regValue));
                return regValue;
            }
            default:
                assert(false);
        }
    }

    AotValue* FunctionCompilerCtx::derefPtr(AotValue* value, const TypeDef* type, uint16_t offset)
    {
        assert(offset == 0 || value->type->type() == ValueType::Struct || value->isGlobal());
        if(value->isGlobal())
        {
            auto temp = newCustomReg(value->type, ValueStorageType_Ptr,  AotValue::Temp | value->flags & ~AotValue::Initialized);
            temp->ptrOffset = value->ptrOffset;
            appendCode(Operand::MOV, serialize(temp), serialize(value));
            value = temp;
        }
        assert(value->storageType == ValueStorageType_Ptr);
        assert(type);
        if(type->type() == ValueType::Struct)
        {
            auto* offsetPtr = newReg(type, AotValue::Temp | (value->flags & ~AotValue::Initialized));
            appendCode(Operand::MOV, serialize(offsetPtr), serialize(value));
            appendCode(Operand::ADDI, serialize(offsetPtr), (int32_t)offset);
            return offsetPtr;
        }

        auto* derefValue = new AotValue(*value);
        derefValue->storageType = ValueStorageType_DerefPtr;
        derefValue->type = type;
        derefValue->ptrOffset = offset;

        auto id = values.push({std::unique_ptr<AotValue>(derefValue), values[value->id].index, true});
        value->id = id;
        return derefValue;
    }

    Value FunctionCompilerCtx::serialize(AotValue* value) const
    {
        assert(value->flags & AotValue::Initialized);
        assert(value->storageType != ValueStorageType_Null);
        if(value->isGlobal())
        {
            return {0, value->ptrOffset, value->type->type(), ValueStorageType_Global};
        }
        auto& index = values[value->id];
        if(index.isReg)
        {
            Value output = registers[index.index];

            // We reuse register indexes for pointers, so we need to pull these from the value pointer
            output.storageType = value->storageType;
            output.offset = value->ptrOffset;
            return output;
        }
        return memoryLocations[index.index];
    }

    void FunctionCompilerCtx::releaseValue(AotValue* value)
    {
        assert(values.hasIndex(value->id));
        if(value->isCompare())
        {
            compareFlagsInUse = false;
            values.remove(value->id);
            return;
        }

        auto& index = values[value->id];
        if(index.isReg && registers[index.index].storageType != ValueStorageType_DerefPtr)
            registers.remove(index.index);
        else
            memoryLocations.remove(index.index);
        values.remove(value->id);
    }

    uint32_t FunctionCompilerCtx::newJumpTargetID() { return jumpTargetIDCounter++; }

    void FunctionCompilerCtx::appendCode(Operand op) { function->code.push_back(op); }

    void FunctionCompilerCtx::appendCode(const std::string& string)
    {
        assert(string.size() < 256);
        function->code.reserve(function->code.size() + string.size() + 1);
        function->code.push_back(string.size());
        for(char c : string)
            function->code.push_back(c);
    }

    void FunctionCompilerCtx::appendCode(Operand op, Value a)
    {
        size_t index = function->code.size();
        function->code.resize(function->code.size() + sizeof(op) + sizeof(a));
        function->code[index] = op;
        index += sizeof(Operand);
        *(Value*)(function->code.data() + index) = a;
    }

    void FunctionCompilerCtx::appendCode(Operand op, Value a, Value b)
    {
        size_t index = function->code.size();
        function->code.resize(function->code.size() + sizeof(op) + sizeof(a) + sizeof(b));
        function->code[index] = op;
        index += sizeof(Operand);
        *(Value*)(function->code.data() + index) = a;
        index += sizeof(Value);
        *(Value*)(function->code.data() + index) = b;
    }

    void FunctionCompilerCtx::appendCode(Operand op, int16_t index)
    {
        appendCode(op);
        appendCode(index);
    }

    void FunctionCompilerCtx::appendCode(Operand op, uint16_t index)
    {
        appendCode(op);
        appendCode(index);
    }

    void FunctionCompilerCtx::appendCode(Operand op, uint32_t index)
    {
        appendCode(op);
        appendCode(index);
    }

    CompilerError::CompilerError(const std::string& message) : runtime_error(message) {}
} // namespace BraneScript
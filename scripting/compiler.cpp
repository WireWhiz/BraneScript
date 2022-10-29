//
// Created by wirewhiz on 14/10/22.
//

#include "compiler.h"
#include "../antlr4/braneLexer.h"
#include "antlr4/ANTLRInputStream.h"
#include "nativeTypes.h"
#include "aotNode/aotOperationNodes.h"
#include "aotNode/aotValueNodes.h"
#include "aotNode/aotFlowNodes.h"

Compiler::Compiler()
{
    for(auto type : getNativeTypes())
        registerType(type);
}

std::any Compiler::visitProgram(braneParser::ProgramContext* context)
{
    return braneBaseVisitor::visitProgram(context);
}

IRScript* Compiler::compile(const std::string& script)
{
    antlr4::ANTLRInputStream input(script);
    braneLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    braneParser parser(&tokens);
    _ctx = std::make_unique<CompilerCtx>(*this, new IRScript());
    visit(parser.program());
    return _ctx->script;
}

std::any Compiler::visitInclude(braneParser::IncludeContext* context)
{
    return braneBaseVisitor::visitInclude(context);
}

std::any Compiler::visitConstString(braneParser::ConstStringContext* context)
{
    return braneBaseVisitor::visitConstString(context);
}

std::any Compiler::visitInlineScope(braneParser::InlineScopeContext* context)
{
    return visit(context->expression());
}

std::any Compiler::visitAssignment(braneParser::AssignmentContext* context)
{
    auto* rValue= std::any_cast<AotNode*>(visit(context->expr));
    auto* lValue = std::any_cast<AotNode*>(visit(context->dest));
    if(!lValue)
        throw std::runtime_error("Could not find identifier");

    return (AotNode*)new AotAssignNode(lValue, rValue);
}

std::any Compiler::visitScope(braneParser::ScopeContext* context)
{
    pushScope();
    std::vector<AotNode*> operations;
    for(auto stmt : context->statement())
        operations.push_back(std::any_cast<AotNode*>(visit(stmt)));
    popScope();
    return (AotNode*)new AotScope(std::move(operations));
}

std::any Compiler::visitConstFloat(braneParser::ConstFloatContext* context)
{
    return (AotNode*)new AotConst(std::stof(context->FLOAT()->getText()), _types.at("float"));
}

std::any Compiler::visitAddsub(braneParser::AddsubContext* context)
{
    auto left  = std::any_cast<AotNode*>(visit(context->left));
    auto right = std::any_cast<AotNode*>(visit(context->right));
    AotNode* node = nullptr;
    if(context->op->getText() == "+")
        node = new AotAddNode(left, right);
    else
        node = new AotSubNode(left, right);
    return node;
}

std::any Compiler::visitMuldiv(braneParser::MuldivContext* context)
{
    auto left  = std::any_cast<AotNode*>(visit(context->left));
    auto right = std::any_cast<AotNode*>(visit(context->right));
    AotNode* node = nullptr;
    if(context->op->getText() == "*")
        node = new AotMulNode(left, right);
    else
        node = new AotDivNode(left, right);
    return node;
}

std::any Compiler::visitConstInt(braneParser::ConstIntContext* context)
{
    return (AotNode*)new AotConst((int32_t)std::stoi(context->getText()), _types.at("int"));
}

std::any Compiler::visitId(braneParser::IdContext* context)
{
    AotNode* node = getValueNode(context->getText());
    if(!node)
        throw std::runtime_error("could not find identifier: " + std::string(context->getText()));
    return node;
}

std::any Compiler::visitDecl(braneParser::DeclContext* context)
{
    return visit(context->declaration());
}

std::any Compiler::visitDeclaration(braneParser::DeclarationContext* context)
{
    auto name = context->id->getText();
    registerLocalValue(name, context->type->getText(), false);
    return getValueNode(name);
}

const std::vector<Compiler::CompileError>& Compiler::errors() const
{
    return _errors;
}

std::any Compiler::visitArgumentList(braneParser::ArgumentListContext* ctx)
{
    return braneBaseVisitor::visitArgumentList(ctx);
}

std::any Compiler::visitFunction(braneParser::FunctionContext* ctx)
{
    ScriptFunction* previousFunction = _ctx->function;
    _ctx->setFunction(new ScriptFunction());

    //TODO: TypeAssert()
    _ctx->function->returnType = ctx->type->getText();
    _ctx->function->name = ctx->id->getText();
    pushScope();
    for(auto argument : ctx->arguments->declaration())
    {
        std::string type = argument->type->getText();
        _ctx->function->arguments.push_back(type);

        AotValue value = _ctx->newReg(type, false);
        _ctx->lValues.insert({_lValueIndex, value});
        registerLocalValue(argument->id->getText(), type, false);
    }

    for(auto* stmtCtx : ctx->statement())
    {
        auto stmt = std::any_cast<AotNode*>(visit(stmtCtx));
        //TODO optimize toggle
        auto expr = std::unique_ptr<AotNode>(stmt);

        AotNode* optimizedTree = expr->optimize();
        if(expr.get() != optimizedTree)
            expr = std::unique_ptr<AotNode>(optimizedTree);

        expr->generateBytecode(*_ctx);
    }
    popScope();

    uint32_t functionIndex = _ctx->script->localFunctions.size();
    _ctx->script->localFunctions.push_back(std::move(*_ctx->function));
    delete _ctx->function;
    _ctx->function = previousFunction;
    return functionIndex;
}

std::any Compiler::visitCast(braneParser::CastContext* ctx)
{
    return (AotNode*) new AotCastNode(std::any_cast<AotNode*>(visit(ctx->expression())), _types.at(ctx->ID()->getText()));
}

std::any Compiler::visitReturnVoid(braneParser::ReturnVoidContext* ctx)
{
    // _currentFunction->appendCode(ScriptFunction::RET);
    assert(false);
    return (AotNode*)nullptr;
}

std::any Compiler::visitReturnVal(braneParser::ReturnValContext* ctx)
{
    auto retVal = std::any_cast<AotNode*>(visit(ctx->expression()));
    if(retVal->resType()->name() != _ctx->function->returnType)
        retVal = new AotCastNode(retVal, _types.at(_ctx->function->returnType));
    return (AotNode*)new AotReturnValueNode(retVal);
}

void Compiler::registerType(TypeDef* type)
{
    _types.insert({type->name(), type});
}

const std::unordered_map<std::string, TypeDef*>& Compiler::types() const
{
    return _types;
}

void Compiler::registerLocalValue(std::string name, const std::string& type, bool constant)
{
    _scopes.back().localValues.emplace(std::move(name), AotValueNode(_lValueIndex++, _types.at(type), constant));
}

AotNode* Compiler::getValueNode(const std::string& name)
{
    for(auto i = _scopes.rbegin(); i != _scopes.rend(); ++i)
    {
        auto v = i->localValues.find(name);
        if(v != i->localValues.end())
            return new AotValueNode(v->second);
    }
    return nullptr;
}

void Compiler::pushScope()
{
    _scopes.push_back({});
}

void Compiler::popScope()
{
    _scopes.pop_back();
}

std::any Compiler::visitConstBool(braneParser::ConstBoolContext* ctx)
{
    if(ctx->getText() == "true")
        return (AotNode*)new AotConst(true, _types.at("bool"));
    else
        return (AotNode*)new AotConst(false, _types.at("bool"));
}

std::any Compiler::visitIf(braneParser::IfContext* ctx)
{
    auto condition = std::any_cast<AotNode*>(visit(ctx->cond));
    auto operation = std::any_cast<AotNode*>(visit(ctx->operation));
    return (AotNode*)new AotIf(condition, operation);
}

std::any Compiler::visitComparison(braneParser::ComparisonContext* context)
{
    auto* a = std::any_cast<AotNode*>(visit(context->left));
    auto* b = std::any_cast<AotNode*>(visit(context->right));

    AotCompareNode::Mode mode = AotCompareNode::Mode::Equal;
    std::string symbol = context->op->getText();
    if(symbol == "==")
        mode = AotCompareNode::Equal;
    else if(symbol == "!=")
        mode = AotCompareNode::NotEqual;
    else if(symbol == ">")
        mode = AotCompareNode::Greater;
    else if(symbol == ">=")
        mode = AotCompareNode::GreaterEqual;
    else if(symbol == "<")
    {
        std::swap(a, b);
        mode = AotCompareNode::Greater;
    }
    else if(symbol == "<=")
    {
        std::swap(a, b);
        mode = AotCompareNode::GreaterEqual;
    }


    return (AotNode*)new AotCompareNode(mode, a, b);
}

std::any Compiler::visitExprStatement(braneParser::ExprStatementContext* context)
{
    return visit(context->expression());
}

CompilerCtx::CompilerCtx(Compiler& c, IRScript* s) : compiler(c), script(s)
{

}

AotValue CompilerCtx::newReg(const std::string& type, uint8_t flags)
{
    TypeDef* t = nullptr;
    if(compiler.types().count(type))
        t = compiler.types().at(type);
    return newReg(t, flags);
}

AotValue CompilerCtx::newReg(TypeDef* type, uint8_t flags)
{
    AotValue value;
    value.def = type;
    value.flags = flags;
    if(!value.isVoid())
    {
        value.valueIndex.index = regIndex++;
        value.valueIndex.valueType = value.def->type();
        value.valueIndex.storageType = ValueStorageType_Reg;
    }
    return value;
}

AotValue CompilerCtx::newConst(ValueType type, uint8_t flags)
{
    AotValue value;
    value.def = getNativeTypeDef(type);
    assert(value.def);
    value.flags = flags;
    value.valueIndex.index = memIndex++;
    value.valueIndex.valueType = type;
    value.valueIndex.storageType = ValueStorageType_Mem;
    return std::move(value);
}

AotValue CompilerCtx::castTemp(const AotValue& value)
{
    assert(function);
    if(value.flags & AotValue::Temp)
        return value;
    AotValue tempValue = newReg(value.def, AotValue::Temp | (AotValue::Constexpr & value.flags));
    function->appendCode(ScriptFunction::MOV, tempValue.valueIndex, value.valueIndex);
    return tempValue;
}

AotValue CompilerCtx::castReg(const AotValue& value)
{
    if(value.valueIndex.storageType == ValueStorageType_Reg)
        return value;
    AotValue regValue = newReg(value.def, AotValue::Temp | (AotValue::Constexpr & value.flags));
    switch(value.valueIndex.storageType)
    {
        case ValueStorageType_Mem:
        {
            function->appendCode(ScriptFunction::MOV, regValue.valueIndex, value.valueIndex);
            return regValue;
        }
        case ValueStorageType_EqualRes:
        {
            function->appendCode(ScriptFunction::SETE, regValue.valueIndex);
            return regValue;
        }
        case ValueStorageType_NotEqualRes:
        {
            function->appendCode(ScriptFunction::SETNE, regValue.valueIndex);
            return regValue;
        }
        case ValueStorageType_AboveRes:
        {
            function->appendCode(ScriptFunction::SETA, regValue.valueIndex);
            return regValue;
        }
        case ValueStorageType_GreaterRes:
        {
            function->appendCode(ScriptFunction::SETG, regValue.valueIndex);
            return regValue;
        }
        case ValueStorageType_AboveEqualRes:
        {
            function->appendCode(ScriptFunction::SETAE, regValue.valueIndex);
            return regValue;
        }
        case ValueStorageType_GreaterEqualRes:
        {
            function->appendCode(ScriptFunction::SETGE, regValue.valueIndex);
            return regValue;
        }
        default:
            assert(false);
    }

}

uint32_t CompilerCtx::newMark()
{
    return markIndex++;
}

void CompilerCtx::setFunction(ScriptFunction* f)
{
    function = f;
    regIndex = 0;
    memIndex = 0;
    markIndex = 0;
    lValues.clear();
}

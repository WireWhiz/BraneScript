//
// Created by wirewhiz on 14/10/22.
//

#include "compiler.h"
#include "../antlr4/braneLexer.h"
#include "antlr4/ANTLRInputStream.h"
#include "nativeTypes.h"
#include "aotNode/aotOperationNodes.h"
#include "aotNode/aotValueNodes.h"

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

std::any Compiler::visitStatement(braneParser::StatementContext* context)
{
    return braneBaseVisitor::visitStatement(context);
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
    /*Value lValue;
    if(!getValueNode(context->dest->getText(), lValue))
        throw std::runtime_error("Could not find identifier");
    if(lValue.flags & Value::Temp)
        throw std::runtime_error("Can not assign to temporary value");
    auto rValue= std::any_cast<Value>(visit(context->expr));

    _currentFunction->appendCode(ScriptFunction::MOV, lValue, rValue);

    if(!(rValue.flags & Value::Constexpr))
        lValue.flags &= ~Value::Constexpr;*/

    return {};
}

std::any Compiler::visitScope(braneParser::ScopeContext* context)
{
    return braneBaseVisitor::visitScope(context);
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
    return braneBaseVisitor::visitDeclaration(context);
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
    _ctx->function = new ScriptFunction();

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
        registerLocalValue(argument->id->getText(), type, false);\
    }

    for(auto* expression : std::any_cast<std::vector<AotNode*>>(visit(ctx->expressions)))
    {
        //TODO optimize toggle
        auto expr = std::unique_ptr<AotNode>(expression);

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

std::any Compiler::visitExprList(braneParser::ExprListContext* ctx)
{
    std::vector<AotNode*> nodes;
    for(auto expr : ctx->expression())
        nodes.push_back(std::any_cast<AotNode*>(visit(expr)));
    return nodes;
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
        value.valueIndex.flags |= ValueIndexFlags_Reg;
    }
    return value;
}

AotValue CompilerCtx::newConst(ValueType type, uint8_t flags)
{
    AotValue value;
    value.def = getTypeDef(type);
    assert(value.def);
    value.flags = flags;
    value.valueIndex.index = memIndex++;
    value.valueIndex.valueType = type;
    value.valueIndex.flags |= ValueIndexFlags_Mem;
    return std::move(value);
}

AotValue CompilerCtx::castTemp(const AotValue& value)
{
    assert(function);
    if(value.flags & AotValue::Temp)
        return value;
    AotValue tempValue = newReg(value.def->name(), AotValue::Temp | (AotValue::Constexpr & value.flags));
    function->appendCode(ScriptFunction::MOV, tempValue.valueIndex, value.valueIndex);
    return tempValue;
}

AotValue CompilerCtx::castReg(const AotValue& value)
{
    if(value.valueIndex.flags & ValueIndexFlags_Reg)
        return value;
    AotValue regValue = newReg(value.def->name(), AotValue::Temp | (AotValue::Constexpr & value.flags));
    function->appendCode(ScriptFunction::MOV, regValue.valueIndex, value.valueIndex);
    return regValue;
}

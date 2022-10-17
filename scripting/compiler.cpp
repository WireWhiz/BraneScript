//
// Created by wirewhiz on 14/10/22.
//

#include "compiler.h"
#include "../antlr4/braneLexer.h"
#include "antlr4/ANTLRInputStream.h"
#include "nativeTypes.h"

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
    _currentScript = new IRScript();
    visit(parser.program());
    return _currentScript;
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
    Value lValue;
    if(!tryGetValue(context->dest->getText(), lValue))
        throw std::runtime_error("Could not find identifier");
    if(lValue.flags & Value::Temp)
        throw std::runtime_error("Can not assign to temporary value");
    auto rValue= std::any_cast<Value>(visit(context->expr));

    _currentFunction->appendCode(ScriptFunction::MOV, lValue, rValue);

    if(!(rValue.flags & Value::Constexpr))
        lValue.flags &= ~Value::Constexpr;

    return lValue;
}

std::any Compiler::visitScope(braneParser::ScopeContext* context)
{
    return braneBaseVisitor::visitScope(context);
}

std::any Compiler::visitConstFloat(braneParser::ConstFloatContext* context)
{
    return std::stof(context->FLOAT()->getText());
}

std::any Compiler::visitAddsub(braneParser::AddsubContext* context)
{
    auto left  = std::any_cast<Value>(visit(context->left));
    auto right = std::any_cast<Value>(visit(context->right));
    left = castTemp(left);
    _currentFunction->appendCode((context->op->getText() == "+") ? ScriptFunction::ADD : ScriptFunction::SUB, left.valueIndex, right.valueIndex);
    return left;
}

std::any Compiler::visitConstInt(braneParser::ConstIntContext* context)
{

    auto value = newValue("int", Value::Const | Value::Constexpr);

    auto constIndex = _currentFunction->registerConstant(std::stoi(context->getText()));
    _currentFunction->appendCode(ScriptFunction::MOVC, value.valueIndex, constIndex);

    return value;
}

std::any Compiler::visitId(braneParser::IdContext* context)
{
    Value value;
    if(!tryGetValue(context->getText(), value))
        throw std::runtime_error("could not find identifier");
    return value;
}

std::any Compiler::visitDecl(braneParser::DeclContext* context)
{
    return visit(context->declaration());
}

std::any Compiler::visitMuldiv(braneParser::MuldivContext* context)
{
    auto left  = std::any_cast<Value>(visit(context->left));
    auto right = std::any_cast<Value>(visit(context->right));
    left = castTemp(left);
    _currentFunction->appendCode((context->op->getText() == "*") ? ScriptFunction::MUL : ScriptFunction::DIV, left.valueIndex, right.valueIndex);

    return left;
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
    ScriptFunction function;
    ScriptFunction* previousFunction = _currentFunction;
    _currentFunction = &function;

    //TODO: TypeAssert()
    function.returnType = ctx->type->getText();
    function.name = ctx->id->getText();
    pushScope();
    size_t argumentIndex =  0;
    _valueIndex = 0;
    for(auto argument : ctx->arguments->declaration())
    {
        std::string type = argument->type->getText();
        function.arguments.push_back(type);
        auto argValue = newValue(type, 0);
        registerValue(argument->id->getText(), argValue);
        ++argumentIndex;
    }

    visit(ctx->expressions);
    popScope();

    uint32_t functionIndex = _currentScript->localFunctions.size();
    _currentScript->localFunctions.push_back(std::move(function));
    _currentFunction = previousFunction;
    return functionIndex;
}

std::any Compiler::visitReturnVoid(braneParser::ReturnVoidContext* ctx)
{
    _currentFunction->appendCode(ScriptFunction::RET);
    return {};
}

std::any Compiler::visitReturnVal(braneParser::ReturnValContext* ctx)
{
    auto retVal = std::any_cast<Value>(visit(ctx->expression()));
    switch(retVal.def->type())
    {
        case TypeDef::Int:
            _currentFunction->appendCode(ScriptFunction::RETV, retVal.valueIndex);
            break;
        default:
            throw std::runtime_error(std::string("Unknown return type ") + retVal.def->name());
    }
    return {};
}

std::any Compiler::visitExprList(braneParser::ExprListContext* ctx)
{
    for(auto expr : ctx->expression())
        visit(expr);
    return {};
}

void Compiler::registerType(TypeDef* type)
{
    _types.insert({type->name(), type});
}

Compiler::Value Compiler::newValue(const std::string& type, uint8_t flags)
{
    Value value;
    if(type == "void")
        value.def = nullptr;
    else if(_types.count(type))
        value.def = _types.at(type);
    value.flags = flags;
    value.valueIndex  = _valueIndex++;
    return std::move(value);
}

Compiler::Value Compiler::castTemp(const Value& value)
{
    if(value.flags & Value::Temp)
        return value;
    Value tempValue = newValue(value.def->name(), Value::Temp | (Value::Constexpr & value.flags));
    _currentFunction->appendCode(ScriptFunction::MOV, tempValue.valueIndex, value.valueIndex);
    return tempValue;
}

void Compiler::registerValue(std::string name, Compiler::Value value)
{
    _scopes.back().localValues.emplace(std::move(name), std::move(value));
}

bool Compiler::tryGetValue(const std::string& name, Compiler::Value& value)
{
    for(auto i = _scopes.rbegin(); i != _scopes.rend(); ++i)
    {
        auto v = i->localValues.find(name);
        if(v != i->localValues.end())
        {
            value = v->second;
            return true;
        }
    }
    return false;
}

void Compiler::pushScope()
{
    _scopes.push_back({});
}

void Compiler::popScope()
{
    _scopes.pop_back();
}

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

#define PROPAGATE_NULL(node) \
    if(!node) return (AotNode*)nullptr;

class LexerErrorListener : public antlr4::BaseErrorListener {

    Compiler& _compiler;
public:
    LexerErrorListener(Compiler& compiler) : _compiler(compiler){};
    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, size_t line, size_t charPositionInLine,
                             const std::string &msg, std::exception_ptr e) override
    {
        if(offendingSymbol)
            _compiler.throwError(offendingSymbol, msg);
        else
        {
            size_t charIndex = 0;
            size_t lineIndex = 0;
            while(lineIndex < line - 1)
            {
                if((*_compiler._currentFile)[charIndex] == '\n')
                    ++lineIndex;
                charIndex++;
            }
            _compiler.throwError((std::string)"Unknown Token \"" + (*_compiler._currentFile)[charIndex + charPositionInLine] + "\" on line " + std::to_string(line) + ":" + std::to_string(charPositionInLine));
        }
    }
};

class ParserErrorListener : public antlr4::BaseErrorListener
{
    Compiler& _compiler;
public:
    ParserErrorListener(Compiler& compiler) : _compiler(compiler)
    {

    }
    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, size_t line, size_t charPositionInLine,
                     const std::string &msg, std::exception_ptr e) override
    {
        if(offendingSymbol)
            _compiler.throwError(offendingSymbol, msg);
    }
};

Compiler::Compiler()
{
    for(auto type : getNativeTypes())
        registerType(type);
}

IRScript* Compiler::compile(const std::string& script)
{
    _currentFile = &script;
    antlr4::ANTLRInputStream input(script);

    LexerErrorListener lexErrListener(*this);
    braneLexer lexer(&input);
    lexer.removeErrorListeners();
    lexer.addErrorListener(&lexErrListener);
    antlr4::CommonTokenStream tokens(&lexer);

    ParserErrorListener parserErrListener(*this);
    braneParser parser(&tokens);
    parser.removeErrorListeners();
    parser.addErrorListener(&parserErrListener);

    _ctx = std::make_unique<CompilerCtx>(*this, new IRScript());
    visit(parser.program());

    if(contextValid())
        return _ctx->script;
    return nullptr;
}

std::any Compiler::visitProgram(braneParser::ProgramContext* context)
{
    return braneBaseVisitor::visitProgram(context);
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
    PROPAGATE_NULL(rValue);
    auto* lValue = std::any_cast<AotNode*>(visit(context->dest));
    PROPAGATE_NULL(rValue);
    if(!lValue)
        throw std::runtime_error("Could not find identifier");

    return (AotNode*)new AotAssignNode(lValue, rValue);
}

std::any Compiler::visitScope(braneParser::ScopeContext* context)
{
    pushScope();
    std::vector<AotNode*> operations;
    for(auto stmt : context->statement())
    {
        auto* operation = std::any_cast<AotNode*>(visit(stmt));
        PROPAGATE_NULL(operation);
        operations.push_back(operation);
    }
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
    PROPAGATE_NULL(left);
    auto right = std::any_cast<AotNode*>(visit(context->right));
    PROPAGATE_NULL(right);
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
    PROPAGATE_NULL(left);
    auto right = std::any_cast<AotNode*>(visit(context->right));
    PROPAGATE_NULL(right);
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
    {
        throwError(context->start, "Undefined identifier");
        return (AotNode*)nullptr;
    }
    return node;
}

std::any Compiler::visitDecl(braneParser::DeclContext* context)
{
    return visit(context->declaration());
}

std::any Compiler::visitDeclaration(braneParser::DeclarationContext* context)
{
    auto name = context->id->getText();
    if(!getType(context->type->getText()))
    {
        throwError(context->type, "Undefined type");
        return (AotNode*)nullptr;
    }
    if(localValueExists(name))
    {
        throwError(context->id, "Identifier is already in use");
        return (AotNode*)nullptr;
    }
    registerLocalValue(name, context->type->getText(), false);
    return getValueNode(name);
}

const std::vector<std::string>& Compiler::errors() const
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
    if(!getType(_ctx->function->returnType))
    {
        throwError(ctx->type, "Unknown return type");
        delete _ctx->function;
        return {};
    }

    _ctx->function->name = ctx->id->getText();
    pushScope();
    for(auto argument : ctx->arguments->declaration())
    {
        std::string type = argument->type->getText();
        if(!getType(type))
        {
            throwError(argument->type, "Unknown argument type");
            delete _ctx->function;
            return {};
        }
        _ctx->function->arguments.push_back(type);

        AotValue value = _ctx->newReg(type, false);
        _ctx->lValues.insert({_lValueIndex, value});
        registerLocalValue(argument->id->getText(), type, false);
    }

    bool previousReturnVal = _ctx->returnCalled;
    _ctx->returnCalled = false;
    for(auto* stmtCtx : ctx->statement())
    {
        auto stmt = std::any_cast<AotNode*>(visit(stmtCtx));
        if(!stmt)
            continue;

        //TODO optimize toggle
        auto expr = std::unique_ptr<AotNode>(stmt);

        AotNode* optimizedTree = expr->optimize();
        if(expr.get() != optimizedTree)
            expr = std::unique_ptr<AotNode>(optimizedTree);

        expr->generateBytecode(*_ctx);
    }
    if(!_ctx->returnCalled && _ctx->function->returnType != "void")
    {
        size_t begin = ctx->start->getStartIndex();
        size_t end = ctx->stop->getStopIndex() + 1;
        throwError(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(), "\n" + _currentFile->substr(begin, end - begin), "Function missing call to return");
        return {};
    }
    _ctx->returnCalled = previousReturnVal;
    popScope();

    _ctx->script->localFunctions.push_back(std::move(*_ctx->function));
    delete _ctx->function;
    _ctx->function = previousFunction;
    return {};
}

std::any Compiler::visitCast(braneParser::CastContext* ctx)
{
    return (AotNode*) new AotCastNode(std::any_cast<AotNode*>(visit(ctx->expression())), _types.at(ctx->ID()->getText()));
}

std::any Compiler::visitReturnVoid(braneParser::ReturnVoidContext* ctx)
{
    assert(false);
    throwError("Void return statements not implemented");
    _ctx->returnCalled = true;
    return (AotNode*)nullptr;
}

std::any Compiler::visitReturnVal(braneParser::ReturnValContext* ctx)
{
    auto retVal = std::any_cast<AotNode*>(visit(ctx->expression()));
    if(retVal->resType()->name() != _ctx->function->returnType)
        retVal = new AotCastNode(retVal, _types.at(_ctx->function->returnType));
    _ctx->returnCalled = true;
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

std::any Compiler::visitWhile(braneParser::WhileContext* ctx)
{
    auto condition = std::any_cast<AotNode*>(visit(ctx->cond));
    auto operation = std::any_cast<AotNode*>(visit(ctx->operation));
    return (AotNode*)new AotWhile(condition, operation);
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

void Compiler::throwError(const std::string& message)
{
    _errors.push_back(message);
}

void Compiler::throwError(antlr4::Token* token, const std::string& message)
{
    assert(token);
    throwError(token->getLine(), token->getCharPositionInLine(), token->getText(), message);
}

void Compiler::throwError(size_t line, size_t position,  const std::string& context,  const std::string& message)
{
    std::string error = "Compile Error at [" + std::to_string(line) + ":" + std::to_string(position) + "] "+ message;
    if(!context.empty())
        error += ": " + context;
    _errors.push_back(std::move(error));
}

bool Compiler::contextValid()
{
    return _errors.empty();
}

TypeDef* Compiler::getType(const std::string& typeName)
{
    if(!_types.count(typeName))
        return nullptr;
    return _types.at(typeName);
}

bool Compiler::localValueExists(const std::string& name)
{
    for(auto& s : _scopes)
    {
        if(s.localValues.count(name))
            return true;
    }
    return false;
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

AotValue CompilerCtx::castValue(const AotValue& value)
{
    if(value.valueIndex.storageType == ValueStorageType_Mem)
        return value;
    return castReg(value);
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


//
// Created by wirewhiz on 14/10/22.
//

#include "compiler.h"
#include "../antlr4/braneLexer.h"
#include "../antlr4/braneParser.h"
#include "../antlr4/braneVisitor.h"
#include "../antlr4/braneBaseVisitor.h"
#include "antlr4/ANTLRInputStream.h"

Compiler::Compiler()
{

}

std::any Compiler::visitProgram(braneParser::ProgramContext* context)
{
    return braneBaseVisitor::visitProgram(context);
}

bool Compiler::compile(const std::string& script)
{
    antlr4::ANTLRInputStream input(script);
    braneLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    braneParser parser(&tokens);

    visit(parser.program());
    return true;
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
    auto expr = visit(context->expr);
    if(expr.has_value())
    {
        std::cout << (expr.type() == typeid(int) ? std::any_cast<int>(expr) : std::any_cast<float>(expr));
    }
    return braneBaseVisitor::visitAssignment(context);
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
    auto left  = visit(context->left);
    auto right = visit(context->right);
    if(left.type() == typeid(int) && right.type() == typeid(int))
    {
        int a = std::any_cast<int>(left);
        int b = std::any_cast<int>(right);
        return (context->op->getText() == "+") ? a + b : a - b;
    }
    float a = left.type() == typeid(int) ? std::any_cast<int>(left) : std::any_cast<float>(left);
    float b = right.type() == typeid(int) ? std::any_cast<int>(right) : std::any_cast<float>(right);

    return (context->op->getText() == "+") ? a + b : a - b;
}

std::any Compiler::visitConstInt(braneParser::ConstIntContext* context)
{
    return std::stof(context->INT()->getText());
}

std::any Compiler::visitId(braneParser::IdContext* context)
{
    return braneBaseVisitor::visitId(context);
}

std::any Compiler::visitDecl(braneParser::DeclContext* context)
{
    return visit(context->declaration());
}

std::any Compiler::visitMuldiv(braneParser::MuldivContext* context)
{
    auto left  = visit(context->left);
    auto right = visit(context->right);
    if(left.type() == typeid(int) && right.type() == typeid(int))
    {
        int a = std::any_cast<int>(left);
        int b = std::any_cast<int>(right);
        return (context->op->getText() == "*") ? a * b : a / b;
    }
    float a = left.type() == typeid(int) ? std::any_cast<int>(left) : std::any_cast<float>(left);
    float b = right.type() == typeid(int) ? std::any_cast<int>(right) : std::any_cast<float>(right);

    return (context->op->getText() == "*") ? a * b : a / b;
}

std::any Compiler::visitDeclaration(braneParser::DeclarationContext* context)
{
    return braneBaseVisitor::visitDeclaration(context);
}

const std::vector<Compiler::CompileError>& Compiler::errors() const
{
    return _errors;
}

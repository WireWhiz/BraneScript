//
// Created by wirewhiz on 11/5/23.
//

#include <typeindex>
#include "astWalker.h"

namespace BraneScript::ast
{
    void AstWalker::visit(AstNode* expression) {
        if (expression) {
            expression->accept(this);
        }
    }

    void AstWalker::visit(Ast* ast)
    {

    }

    void AstWalker::visit(Module* module)
    {

    }

    void AstWalker::visit(BooleanLiteral* booleanLiteral)
    {

    }

    void AstWalker::visit(IntegerLiteral* integerLiteral)
    {

    }

    void AstWalker::visit(FloatLiteral* floatLiteral)
    {

    }

    void AstWalker::visit(CharLiteral* charLiteral)
    {

    }

    void AstWalker::visit(StringLiteral* stringLiteral)
    {

    }

    void AstWalker::visit(Scope* scope)
    {
        for (const auto& statement : scope->statements) {
            visit(statement.get());
        }
    }

    void AstWalker::visit(Parenthesis* parenthesis)
    {
        if (parenthesis->expression) {
            visit(parenthesis->expression.get());
        }
    }

    void AstWalker::visit(ReturnStatement* returnStatement)
    {
        if (returnStatement->expression) {
            visit(returnStatement->expression.get());
        }
    }

    void AstWalker::visit(IfStatement* ifStatement)
    {
        visit(ifStatement->condition.get());
        visit(ifStatement->body.get());

        if (ifStatement->elseBody) {
            visit(ifStatement->elseBody.value().get());
        }
    }

    void AstWalker::visit(WhileStatement* whileStatement)
    {
        visit(whileStatement->condition.get());
        visit(whileStatement->body.get());
    }

    void AstWalker::visit(ForStatement* forStatement)
    {
        visit(forStatement->init.get());
        visit(forStatement->condition.get());
        visit(forStatement->increment.get());
        visit(forStatement->body.get());
    }

    void AstWalker::visit(SwitchCase* switchCase)
    {
        visit(switchCase->condition.get());
        visit(switchCase->body.get());
    }

    void AstWalker::visit(SwitchStatement* switchStatement)
    {
        visit(switchStatement->expression.get());

        for (const auto& switchCase : switchStatement->cases) {
            visit(switchCase.get());
        }
    }

    void AstWalker::visit(BreakStatement* breakStatement)
    {

    }

    void AstWalker::visit(ContinueStatement* continueStatement)
    {

    }

    void AstWalker::visit(Declaration* declaration)
    {
        if (declaration->initializer) {
            visit(declaration->initializer.get());
        }
    }

    void AstWalker::visit(VariableAccess* variableAccess)
    {

    }

    void AstWalker::visit(LambdaCapture* lambdaCapture)
    {

    }

    void AstWalker::visit(LambdaStatement* lambdaStatement)
    { visit(lambdaStatement->body.get());
    }

    void AstWalker::visit(FunctionCall* functionCall)
    {
        for (const auto& argument : functionCall->arguments) {
            visit(argument.get());
        }
    }
}
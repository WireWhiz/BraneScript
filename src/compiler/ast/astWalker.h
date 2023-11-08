//
// Created by wirewhiz on 11/5/23.
//

#ifndef BRANESCRIPT_ASTWALKER_H
#define BRANESCRIPT_ASTWALKER_H

#include "ast.h"
#include "expressions.h"

namespace BraneScript::ast
{
    /**
     * A message recorded during the AST visit, usually an error or warning.
     * Has a reference to the context of the message so that the ast source (such as a text file or node editor)
     * can be referenced if needed.
     */
    class ContextMessage
    {
        std::optional<std::unique_ptr<Source>> source;
        std::string message;
    };

    /**
     * A base class for walking and modifying an AST
     */
    class AstWalkerBase
    {
        std::vector<ContextMessage> logs;
        std::vector<ContextMessage> errors;
        std::vector<ContextMessage> warnings;

      public:
        virtual ~AstWalkerBase() = default;

        virtual void visit(AstNode* expression) = 0;
        virtual void visit(Ast* ast) = 0;
        virtual void visit(Module* module) = 0;
        virtual void visit(BooleanLiteral* booleanLiteral) = 0;
        virtual void visit(IntegerLiteral* integerLiteral) = 0;
        virtual void visit(FloatLiteral* floatLiteral) = 0;
        virtual void visit(CharLiteral* charLiteral) = 0;
        virtual void visit(StringLiteral* stringLiteral) = 0;
        virtual void visit(Scope* scope) = 0;
        virtual void visit(Parenthesis* parenthesis) = 0;
        virtual void visit(ReturnStatement* returnStatement) = 0;
        virtual void visit(IfStatement* ifStatement) = 0;
        virtual void visit(WhileStatement* whileStatement) = 0;
        virtual void visit(ForStatement* forStatement) = 0;
        virtual void visit(SwitchCase* switchCase) = 0;
        virtual void visit(SwitchStatement* switchStatement) = 0;
        virtual void visit(BreakStatement* breakStatement) = 0;
        virtual void visit(ContinueStatement* continueStatement) = 0;
        virtual void visit(Declaration* declaration) = 0;
        virtual void visit(VariableAccess* variableAccess) = 0;
        virtual void visit(LambdaCapture* lambdaCapture) = 0;
        virtual void visit(LambdaStatement* lambdaStatement) = 0;
        virtual void visit(FunctionCall* functionCall) = 0;
    };

    /**
     * Extension of the AstWalkerBase class that provides default implementations for all methods.
     */
    class AstWalker : public AstWalkerBase
    {
        std::vector<ContextMessage> logs;
        std::vector<ContextMessage> errors;
        std::vector<ContextMessage> warnings;

      public:
        void visit(AstNode* expression) override;
        void visit(Ast* ast) override;
        void visit(Module* module) override;
        void visit(BooleanLiteral* booleanLiteral) override;
        void visit(IntegerLiteral* integerLiteral) override;
        void visit(FloatLiteral* floatLiteral) override;
        void visit(CharLiteral* charLiteral) override;
        void visit(StringLiteral* stringLiteral) override;
        void visit(Scope* scope) override;
        void visit(Parenthesis* parenthesis) override;
        void visit(ReturnStatement* returnStatement) override;
        void visit(IfStatement* ifStatement) override;
        void visit(WhileStatement* whileStatement) override;
        void visit(ForStatement* forStatement) override;
        void visit(SwitchCase* switchCase) override;
        void visit(SwitchStatement* switchStatement) override;
        void visit(BreakStatement* breakStatement) override;
        void visit(ContinueStatement* continueStatement) override;
        void visit(Declaration* declaration) override;
        void visit(VariableAccess* variableAccess) override;
        void visit(LambdaCapture* lambdaCapture) override;
        void visit(LambdaStatement* lambdaStatement) override;
        void visit(FunctionCall* functionCall) override;
    };
} // namespace BraneScript::ast


#endif // BRANESCRIPT_ASTWALKER_H

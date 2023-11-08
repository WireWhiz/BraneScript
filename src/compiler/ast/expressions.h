//
// Created by wirewhiz on 10/8/23.
//

#ifndef BRANESCRIPT_EXPRESSIONS_H
#define BRANESCRIPT_EXPRESSIONS_H

#include <memory>
#include <optional>
#include <string>
#include <vector>
#include "ast.h"
#include "scopedId.h"
#include "source.h"
#include "typeDef.h"

namespace BraneScript::ast
{
    struct Expression : public AstNode
    {
    };

    //Constants

    struct BooleanLiteral : public Expression
    {
        bool value;
        void accept(AstWalkerBase* walker) override;
    };

    struct IntegerLiteral : public Expression
    {
        int value;
        void accept(AstWalkerBase* walker) override;
    };

    struct FloatLiteral : public Expression
    {
        float value;
        void accept(AstWalkerBase* walker) override;
    };

    struct CharLiteral : public Expression
    {
        char value;
        void accept(AstWalkerBase* walker) override;
    };

    struct StringLiteral : public Expression
    {
        std::string value;
        void accept(AstWalkerBase* walker) override;
    };

    //Structure

    struct Scope : public Expression
    {
        std::vector<std::unique_ptr<Expression>> statements;
        void accept(AstWalkerBase* walker) override;
    };

    struct Parenthesis : public Expression
    {
        std::unique_ptr<Expression> expression;
        void accept(AstWalkerBase* walker) override;
    };

    struct ReturnStatement : public Expression
    {
        std::unique_ptr<Expression> expression;
        void accept(AstWalkerBase* walker) override;
    };

    struct IfStatement : public Expression
    {
        std::unique_ptr<Expression> condition;
        std::unique_ptr<Expression> body;
        std::optional<std::unique_ptr<Expression>> elseBody;
        void accept(AstWalkerBase* walker) override;
    };

    struct WhileStatement : public Expression
    {
        std::unique_ptr<Expression> condition;
        std::unique_ptr<Expression> body;
        void accept(AstWalkerBase* walker) override;
    };

    struct ForStatement : public Expression
    {
        std::unique_ptr<Expression> init;
        std::unique_ptr<Expression> condition;
        std::unique_ptr<Expression> increment;
        std::unique_ptr<Expression> body;
        void accept(AstWalkerBase* walker) override;
    };

    struct SwitchCase : public Expression
    {
        std::unique_ptr<Expression> condition;
        std::unique_ptr<Expression> body;
        void accept(AstWalkerBase* walker) override;
    };

    struct SwitchStatement : public Expression
    {
        std::unique_ptr<Expression> expression;
        std::vector<std::unique_ptr<SwitchCase>> cases;
        void accept(AstWalkerBase* walker) override;
    };

    struct BreakStatement : public Expression
    {
        void accept(AstWalkerBase* walker) override;
    };

    struct ContinueStatement : public Expression
    {
        void accept(AstWalkerBase* walker) override;
    };

    //Variables
    struct Declaration : public Expression
    {
        std::string name;
        ScopedId type;
        std::unique_ptr<Expression> initializer;

        void accept(AstWalkerBase* walker) override;
    };

    struct VariableAccess : public Expression
    {
        ScopedId name;

        void accept(AstWalkerBase* walker) override;
    };

    struct LambdaCapture : public Expression
    {
        ScopedId name;
        bool byRef = false;

        void accept(AstWalkerBase* walker) override;
    };

    struct LambdaStatement : public Expression
    {
        std::vector<LambdaCapture> captures;

        std::vector<std::string> paramNames;
        std::vector<ScopedId> paramTypes;
        ScopedId returnType;
        std::unique_ptr<Expression> body;

        void accept(AstWalkerBase* walker) override;
    };

    struct FunctionCall : public Expression
    {
        ScopedId function;
        std::vector<std::unique_ptr<Expression>> arguments;

        void accept(AstWalkerBase* walker) override;
    };
}


#endif // BRANESCRIPT_EXPRESSIONS_H

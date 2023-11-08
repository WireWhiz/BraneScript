#include "expressions.h"
#include "astWalker.h"

namespace BraneScript::ast
{
    void BooleanLiteral::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void IntegerLiteral::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void FloatLiteral::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void CharLiteral::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void StringLiteral::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void Scope::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void Parenthesis::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void ReturnStatement::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void IfStatement::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void WhileStatement::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void ForStatement::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void SwitchCase::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void SwitchStatement::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void BreakStatement::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void ContinueStatement::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void Declaration::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void VariableAccess::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void LambdaCapture::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void LambdaStatement::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }

    void FunctionCall::accept(AstWalkerBase* walker)
    {
        walker->visit(this);
    }
}

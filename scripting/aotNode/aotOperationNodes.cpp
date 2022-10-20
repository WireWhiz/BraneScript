//
// Created by wirewhiz on 17/10/22.
//

#include "aotOperationNodes.h"
#include "../compiler.h"

AotSingleArgNode::AotSingleArgNode(AotNode*arg, NodeType type) : AotNode(type), _arg(arg)
{

}

AotNode* AotSingleArgNode::optimize()
{
    auto optArg = _arg->optimize();
    if(optArg != _arg.get())
        _arg = std::unique_ptr<AotNode>(optArg);
    return this;
}


AotDualArgNode::AotDualArgNode(AotNode* argA, AotNode* argB, NodeType type) : AotNode(type), _argA(argA), _argB(argB)
{

}

AotNode* AotDualArgNode::optimize()
{
    auto optArgA = _argA->optimize();
    if(optArgA != _argA.get())
        _argA = std::unique_ptr<AotNode>(optArgA);
    auto optArgB = _argB->optimize();
    if(optArgB != _argB.get())
        _argB = std::unique_ptr<AotNode>(optArgB);
    return this;
}

AotAddNode::AotAddNode(AotNode* argA, AotNode* argB) : AotDualArgNode(argA, argB, Add)
{

}

AotValue AotAddNode::generateBytecode(CompilerCtx& ctx) const
{
    AotValue left  = _argA->generateBytecode(ctx);
    AotValue right = _argB->generateBytecode(ctx);
    left = ctx.castTemp(left);
    ctx.function->appendCode(ScriptFunction::ADD, left.valueIndex, right.valueIndex);
    return left;
}

AotSubNode::AotSubNode(AotNode* argA, AotNode* argB) : AotDualArgNode(argA, argB, Sub)
{

}

AotNode* AotSubNode::optimize()
{
    AotDualArgNode::optimize();

    if(_argA->type() == Const && _argB->type() == Const)
    {
        auto& a = dynamic_cast<AotConst*>(_argA.get())->value();
        auto& b = dynamic_cast<AotConst*>(_argB.get())->value();
        if(a.type() == b.type())
        {
            if(a.type() == typeid(int32_t))
                return new AotConst(std::any_cast<int32_t>(a) - std::any_cast<int32_t>(b));
            if(a.type() == typeid(float))
                return new AotConst(std::any_cast<float>(a) - std::any_cast<float>(b));
            if(a.type() == typeid(double))
                return new AotConst(std::any_cast<double>(a) - std::any_cast<double>(b));
        }
    }

    return this;
}

AotValue AotSubNode::generateBytecode(CompilerCtx& ctx) const
{
    AotValue left  = _argA->generateBytecode(ctx);
    AotValue right = _argB->generateBytecode(ctx);
    left = ctx.castTemp(left);
    ctx.function->appendCode(ScriptFunction::SUB, left.valueIndex, right.valueIndex);
    return left;
}

AotMulNode::AotMulNode(AotNode* argA, AotNode* argB) : AotDualArgNode(argA, argB, Mul)
{

}

AotValue AotMulNode::generateBytecode(CompilerCtx& ctx) const
{
    AotValue left  = _argA->generateBytecode(ctx);
    AotValue right = _argB->generateBytecode(ctx);
    left = ctx.castTemp(left);
    ctx.function->appendCode(ScriptFunction::MUL, left.valueIndex, right.valueIndex);
    return left;
}

AotDivNode::AotDivNode(AotNode* argA, AotNode* argB) : AotDualArgNode(argA, argB, Div)
{

}

AotValue AotDivNode::generateBytecode(CompilerCtx& ctx) const
{
    AotValue left  = _argA->generateBytecode(ctx);
    AotValue right = _argB->generateBytecode(ctx);
    left = ctx.castTemp(left);
    right = ctx.castReg(right);
    ctx.function->appendCode(ScriptFunction::DIV, left.valueIndex, right.valueIndex);
    return left;
}

AotReturnValueNode::AotReturnValueNode(AotNode* arg) : AotSingleArgNode(arg, ReturnValue)
{

}

AotValue AotReturnValueNode::generateBytecode(CompilerCtx& ctx) const
{
    auto value = _arg->generateBytecode(ctx);
    value = ctx.castReg(value);
    ctx.function->appendCode(ScriptFunction::RETV, value.valueIndex);

    AotValue voidValue;
    return voidValue;
}

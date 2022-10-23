//
// Created by wirewhiz on 17/10/22.
//

#include "aotOperationNodes.h"
#include "../compiler.h"
#include "../typeDef.h"

AotSingleArgNode::AotSingleArgNode(AotNode*arg, TypeDef* resType, NodeType type) : AotNode(resType, type), arg(arg)
{

}

AotNode* AotSingleArgNode::optimize()
{
    auto optArg = arg->optimize();
    if(optArg != arg.get())
        arg = std::unique_ptr<AotNode>(optArg);
    return this;
}


AotDualArgNode::AotDualArgNode(AotNode* argA, AotNode* argB, TypeDef* resType, NodeType type) : AotNode(resType, type), argA(argA), argB(argB)
{

}

AotNode* AotDualArgNode::optimize()
{
    auto optArgA = argA->optimize();
    if(optArgA != argA.get())
        argA = std::unique_ptr<AotNode>(optArgA);
    auto optArgB = argB->optimize();
    if(optArgB != argB.get())
        argB = std::unique_ptr<AotNode>(optArgB);
    return this;
}

AotNode* AotDualArgNode::constArg() const
{
    if(argA->type() == Const)
        return argA.get();
    if(argB->type() == Const)
        return argB.get();
    return nullptr;
}

AotNode* AotDualArgNode::nonConstArg() const
{
    if(argA->type() != Const)
        return argA.get();
    if(argB->type() != Const)
        return argB.get();
    return nullptr;
}

AotNode* AotDualArgNode::releaseNonConstArg()
{
    if(argA->type() != Const)
        return argA.release();
    if(argB->type() != Const)
        return argB.release();
    assert(false);
    return nullptr;
}

AotCastNode::AotCastNode(AotNode* arg, TypeDef* castType) : AotSingleArgNode(arg, castType, Cast)
{
}

AotNode* AotCastNode::optimize()
{
    AotSingleArgNode::optimize();

    if(arg->type() == Const)
        return arg->as<AotConst>()->cast(_resType);
    return this;
}

AotValue AotCastNode::generateBytecode(CompilerCtx& ctx) const
{
    AotValue source = arg->generateBytecode(ctx);
    if(source.valueIndex.valueType == _resType->type())
        return source;

    AotValue castValue = ctx.newReg(_resType->name(), AotValue::Temp);
    ctx.function->appendCode(ScriptFunction::MOV, castValue.valueIndex, source.valueIndex);
    return castValue;
}

AotAddNode::AotAddNode(AotNode* a, AotNode* b) : AotDualArgNode(a, b, dominantArgType(a->resType(), b->resType()), Add)
{
    if(argA->resType() != _resType)
        argA = std::unique_ptr<AotNode>(new AotCastNode(argA.release(), _resType));
    if(argB->resType() != _resType)
        argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), _resType));
}

AotNode* AotAddNode::optimize()
{
    AotDualArgNode::optimize();
    auto* ca = constArg()->as<AotConst>();
    auto* nca = nonConstArg();
    if(!ca)
        return this;

    if(argA->type() == Const && argB->type() == Const)
    {
        auto* aNode = argA->as<AotConst>();
        auto* bNode = argB->as<AotConst>();
        if (aNode->isNumber() && bNode->isNumber())
            return *aNode + *bNode;
    }
    auto* nonConstA = nca->as<AotDualArgNode>();
    if(nonConstA)
    {
        auto* distantConstNode = nonConstA->constArg()->as<AotConst>();
        if(distantConstNode)
        {
            if(nca->type() == Add)
                return new AotAddNode(nonConstA->releaseNonConstArg(), *distantConstNode + *ca);
            if(nonConstA->type() == Sub)
            {
                if(nonConstA->argA.get() == distantConstNode)
                    return new AotSubNode(nonConstA->releaseNonConstArg(), *ca + *distantConstNode);
                else
                    return new AotAddNode(nonConstA->releaseNonConstArg(), *ca - *distantConstNode);
            }
        }
    }

    return this;
}

AotValue AotAddNode::generateBytecode(CompilerCtx& ctx) const
{
    AotValue left  = argA->generateBytecode(ctx);
    AotValue right = argB->generateBytecode(ctx);
    if(right.flags & AotValue::Temp && !(left.flags & AotValue::Temp))
        std::swap(left, right);
    else
        left = ctx.castTemp(left);
    ctx.function->appendCode(ScriptFunction::ADD, left.valueIndex, right.valueIndex);
    return left;
}

AotSubNode::AotSubNode(AotNode* a, AotNode* b) : AotDualArgNode(a, b, dominantArgType(a->resType(), b->resType()), Sub)
{
    if(argA->resType() != _resType)
        argA = std::unique_ptr<AotNode>(new AotCastNode(argA.release(), _resType));
    if(argB->resType() != _resType)
        argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), _resType));
}

AotNode* AotSubNode::optimize()
{
    AotDualArgNode::optimize();

    auto* ca = constArg()->as<AotConst>();
    auto* nca = nonConstArg();
    if(!ca)
        return this;

    if(argA->type() == Const && argB->type() == Const)
    {
        auto* aNode = argA->as<AotConst>();
        auto* bNode = argB->as<AotConst>();
        if(aNode->isNumber() && bNode->isNumber())
            return *aNode - *bNode;
    }

    auto* nonConstA = nca->as<AotDualArgNode>();
    if(nonConstA)
    {
        auto* distantConstNode = nonConstA->constArg()->as<AotConst>();
        if(distantConstNode)
        {
            if(nca->type() == Add)
                return new AotAddNode(*distantConstNode - *ca, nonConstA->releaseNonConstArg());
            if(nonConstA->type() == Sub)
            {
                if(nonConstA->argA.get() == distantConstNode)
                    return new AotSubNode(*distantConstNode - *ca, nonConstA->releaseNonConstArg());
                else
                    return new AotSubNode(nonConstA->releaseNonConstArg(), *ca + *distantConstNode);
            }
        }
    }

    return this;
}

AotValue AotSubNode::generateBytecode(CompilerCtx& ctx) const
{
    AotValue left  = argA->generateBytecode(ctx);
    AotValue right = argB->generateBytecode(ctx);
    left = ctx.castTemp(left);
    ctx.function->appendCode(ScriptFunction::SUB, left.valueIndex, right.valueIndex);
    return left;
}

AotMulNode::AotMulNode(AotNode* a, AotNode* v) : AotDualArgNode(a, v, dominantArgType(a->resType(), v->resType()), Mul)
{
    if(argA->resType() != _resType)
        argA = std::unique_ptr<AotNode>(new AotCastNode(argA.release(), _resType));
    if(argB->resType() != _resType)
        argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), _resType));
}

AotValue AotMulNode::generateBytecode(CompilerCtx& ctx) const
{
    AotValue left  = argA->generateBytecode(ctx);
    AotValue right = argB->generateBytecode(ctx);
    if(right.flags & AotValue::Temp && !(left.flags & AotValue::Temp))
        std::swap(left, right);
    else
        left = ctx.castTemp(left);
    ctx.function->appendCode(ScriptFunction::MUL, left.valueIndex, right.valueIndex);
    return left;
}

AotDivNode::AotDivNode(AotNode* a, AotNode* b) : AotDualArgNode(a, b, dominantArgType(a->resType(), b->resType()), Div)
{
    if(argA->resType() != _resType)
        argA = std::unique_ptr<AotNode>(new AotCastNode(argA.release(), _resType));
    if(argB->resType() != _resType)
        argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), _resType));
}

AotValue AotDivNode::generateBytecode(CompilerCtx& ctx) const
{
    AotValue left  = argA->generateBytecode(ctx);
    AotValue right = argB->generateBytecode(ctx);
    left = ctx.castTemp(left);
    right = ctx.castReg(right);
    ctx.function->appendCode(ScriptFunction::DIV, left.valueIndex, right.valueIndex);
    return left;
}

AotReturnValueNode::AotReturnValueNode(AotNode* arg) : AotSingleArgNode(arg, arg->resType(), ReturnValue)
{

}

AotValue AotReturnValueNode::generateBytecode(CompilerCtx& ctx) const
{
    auto value = arg->generateBytecode(ctx);
    value = ctx.castReg(value);
    ctx.function->appendCode(ScriptFunction::RETV, value.valueIndex);

    AotValue voidValue;
    return voidValue;
}
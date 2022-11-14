//
// Created by wirewhiz on 17/10/22.
//

#include "aotOperationNodes.h"
#include "../compiler.h"
#include "../typeDef.h"
#include "../nativeTypes.h"
namespace BraneScript
{
    AotSingleArgNode::AotSingleArgNode(AotNode* arg, TypeDef* resType, NodeType type) : AotNode(resType, type), arg(arg)
    {

    }

    AotNode* AotSingleArgNode::optimize()
    {
        auto optArg = arg->optimize();
        if (optArg != arg.get())
            arg = std::unique_ptr<AotNode>(optArg);
        return this;
    }


    AotDualArgNode::AotDualArgNode(AotNode* argA, AotNode* argB, TypeDef* resType, NodeType type) : AotNode(resType,
                                                                                                            type),
                                                                                                    argA(argA),
                                                                                                    argB(argB)
    {

    }

    AotNode* AotDualArgNode::optimize()
    {
        auto optArgA = argA->optimize();
        if (optArgA != argA.get())
            argA = std::unique_ptr<AotNode>(optArgA);
        auto optArgB = argB->optimize();
        if (optArgB != argB.get())
            argB = std::unique_ptr<AotNode>(optArgB);
        return this;
    }

    AotNode* AotDualArgNode::constArg() const
    {
        if (argA->type() == Const)
            return argA.get();
        if (argB->type() == Const)
            return argB.get();
        return nullptr;
    }

    AotNode* AotDualArgNode::nonConstArg() const
    {
        if (argA->type() != Const)
            return argA.get();
        if (argB->type() != Const)
            return argB.get();
        return nullptr;
    }

    AotNode* AotDualArgNode::releaseNonConstArg()
    {
        if (argA->type() != Const)
            return argA.release();
        if (argB->type() != Const)
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

        if (arg->type() == Const)
            return arg->as<AotConst>()->cast(_resType);
        return this;
    }

    AotValue AotCastNode::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue source = arg->generateBytecode(ctx);
        if (source.valueIndex.valueType == _resType->type())
            return source;

        AotValue castValue = ctx.newReg(_resType->name(), AotValue::Temp);
        ctx.function->appendCode(MOV, castValue.valueIndex, source.valueIndex);
        return castValue;
    }

    AotAddNode::AotAddNode(AotNode* a, AotNode* b) : AotDualArgNode(a, b, dominantArgType(a->resType(), b->resType()),
                                                                    Add)
    {
        if (argA->resType() != _resType)
            argA = std::unique_ptr<AotNode>(new AotCastNode(argA.release(), _resType));
        if (argB->resType() != _resType)
            argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), _resType));
    }

    AotNode* AotAddNode::optimize()
    {
        AotDualArgNode::optimize();
        auto* ca = constArg()->as<AotConst>();
        auto* nca = nonConstArg();
        if (!ca)
            return this;

        if (argA->type() == Const && argB->type() == Const)
        {
            auto* aNode = argA->as<AotConst>();
            auto* bNode = argB->as<AotConst>();
            if (aNode->isNumber() && bNode->isNumber())
                return *aNode + *bNode;
        }
        auto* nonConstA = nca->as<AotDualArgNode>();
        if (nonConstA)
        {
            auto* distantConstNode = nonConstA->constArg()->as<AotConst>();
            if (distantConstNode)
            {
                if (nca->type() == Add)
                    return new AotAddNode(nonConstA->releaseNonConstArg(), *distantConstNode + *ca);
                if (nonConstA->type() == Sub)
                {
                    if (nonConstA->argA.get() == distantConstNode)
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
        AotValue left = argA->generateBytecode(ctx);
        AotValue right = argB->generateBytecode(ctx);
        if (right.flags & AotValue::Temp && !(left.flags & AotValue::Temp))
            std::swap(left, right);
        else
            left = ctx.castTemp(left);
        ctx.function->appendCode(ADD, left.valueIndex, right.valueIndex);
        return left;
    }

    AotSubNode::AotSubNode(AotNode* a, AotNode* b) : AotDualArgNode(a, b, dominantArgType(a->resType(), b->resType()), Sub)
    {
        if (argA->resType() != _resType)
            argA = std::unique_ptr<AotNode>(new AotCastNode(argA.release(), _resType));
        if (argB->resType() != _resType)
            argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), _resType));
    }

    AotNode* AotSubNode::optimize()
    {
        AotDualArgNode::optimize();

        auto* ca = constArg()->as<AotConst>();
        auto* nca = nonConstArg();
        if (!ca)
            return this;

        if (argA->type() == Const && argB->type() == Const)
        {
            auto* aNode = argA->as<AotConst>();
            auto* bNode = argB->as<AotConst>();
            if (aNode->isNumber() && bNode->isNumber())
                return *aNode - *bNode;
        }

        auto* nonConstA = nca->as<AotDualArgNode>();
        if (nonConstA)
        {
            auto* distantConstNode = nonConstA->constArg()->as<AotConst>();
            if (distantConstNode)
            {
                if (nca->type() == Add)
                    return new AotAddNode(*distantConstNode - *ca, nonConstA->releaseNonConstArg());
                if (nonConstA->type() == Sub)
                {
                    if (nonConstA->argA.get() == distantConstNode)
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
        AotValue left = ctx.castTemp(argA->generateBytecode(ctx));
        AotValue right = argB->generateBytecode(ctx);
        ctx.function->appendCode(SUB, left.valueIndex, right.valueIndex);
        return left;
    }

    AotMulNode::AotMulNode(AotNode* a, AotNode* v) : AotDualArgNode(a, v, dominantArgType(a->resType(), v->resType()),
                                                                    Mul)
    {
        if (argA->resType() != _resType)
            argA = std::unique_ptr<AotNode>(new AotCastNode(argA.release(), _resType));
        if (argB->resType() != _resType)
            argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), _resType));
    }

    AotValue AotMulNode::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue left = argA->generateBytecode(ctx);
        AotValue right = argB->generateBytecode(ctx);
        if (right.flags & AotValue::Temp && !(left.flags & AotValue::Temp))
            std::swap(left, right);
        else
            left = ctx.castTemp(left);
        ctx.function->appendCode(MUL, left.valueIndex, right.valueIndex);
        return left;
    }

    AotDivNode::AotDivNode(AotNode* a, AotNode* b) : AotDualArgNode(a, b, dominantArgType(a->resType(), b->resType()),
                                                                    Div)
    {
        if (argA->resType() != _resType)
            argA = std::unique_ptr<AotNode>(new AotCastNode(argA.release(), _resType));
        if (argB->resType() != _resType)
            argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), _resType));
    }

    AotValue AotDivNode::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue left = ctx.castTemp(argA->generateBytecode(ctx));
        AotValue right = ctx.castReg(argB->generateBytecode(ctx));
        ctx.function->appendCode(DIV, left.valueIndex, right.valueIndex);
        return left;
    }

    AotReturnNode::AotReturnNode() : AotNode(nullptr, Return)
    {

    }

    AotNode* AotReturnNode::optimize()
    {
        return this;
    }

    AotValue AotReturnNode::generateBytecode(CompilerCtx& ctx) const
    {
        ctx.function->appendCode(Operand::RET);
        return {};
    }

    AotReturnValueNode::AotReturnValueNode(AotNode* arg) : AotSingleArgNode(arg, arg->resType(), ReturnValue)
    {

    }

    AotValue AotReturnValueNode::generateBytecode(CompilerCtx& ctx) const
    {
        auto value = ctx.castReg(arg->generateBytecode(ctx));
        ctx.function->appendCode(RETV, value.valueIndex);

        AotValue voidValue;
        return voidValue;
    }

    AotCompareNode::AotCompareNode(Mode mode, AotNode* a, AotNode* b) : _mode(mode), AotDualArgNode(a, b,
                                                                                                    getNativeTypeDef(
                                                                                                            ValueType::Bool),
                                                                                                    Compare)
    {
        auto castType = dominantArgType(a->resType(), b->resType());
        if (argA->resType() != castType)
            argA = std::unique_ptr<AotNode>(new AotCastNode(argA.release(), castType));
        if (argB->resType() != castType)
            argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), castType));
    }

    AotValue AotCompareNode::generateBytecode(CompilerCtx& ctx) const
    {
        auto a = ctx.castReg(argA->generateBytecode(ctx));
        auto b = argB->generateBytecode(ctx);

        AotValue result;
        bool sign = a.def->type() == Int32 || a.def->type() == Int64;
        switch (_mode)
        {
            case Equal:
            case NotEqual:
                result.compareType = (AotValue::CompareType)_mode;
                break;
            case Greater:
                result.compareType = sign ? AotValue::GreaterRes : AotValue::AboveRes;
                break;
            case GreaterEqual:
                result.compareType = sign ? AotValue::GreaterEqualRes : AotValue::AboveEqualRes;
                break;
        }

        result.def = resType();

        ctx.function->appendCode(CMP, a.valueIndex, b.valueIndex);

        return result;
    }

    AotAssignNode::AotAssignNode(AotNode* lvalue, AotNode* rvalue) : AotDualArgNode(lvalue, rvalue, lvalue->resType(),
                                                                                    Assign)
    {
        if (argB->resType() != _resType)
            argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), _resType));
    }

    AotValue AotAssignNode::generateBytecode(CompilerCtx& ctx) const
    {
        auto rValue = ctx.castValue(argB->generateBytecode(ctx));
        auto lValue = argA->generateBytecode(ctx);

        ctx.function->appendCode(MOV, lValue.valueIndex, rValue.valueIndex);

        return lValue;
    };
}
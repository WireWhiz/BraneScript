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
        if (argA->type() == NodeType::Const)
            return argA.get();
        if (argB->type() == NodeType::Const)
            return argB.get();
        return nullptr;
    }

    AotNode* AotDualArgNode::nonConstArg() const
    {
        if (argA->type() != NodeType::Const)
            return argA.get();
        if (argB->type() != NodeType::Const)
            return argB.get();
        return nullptr;
    }

    AotNode* AotDualArgNode::releaseNonConstArg()
    {
        if (argA->type() != NodeType::Const)
            return argA.release();
        if (argB->type() != NodeType::Const)
            return argB.release();
        assert(false);
        return nullptr;
    }

    AotCastNode::AotCastNode(AotNode* arg, TypeDef* castType) : AotSingleArgNode(arg, castType, NodeType::Cast)
    {
    }

    AotNode* AotCastNode::optimize()
    {
        AotSingleArgNode::optimize();

        if (arg->type() == NodeType::Const)
            return arg->as<AotConst>()->cast(_resType);
        return this;
    }

    AotValue* AotCastNode::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue* source = arg->generateBytecode(ctx);
        if (source->value(ctx).valueType == _resType->type())
            return source;

        AotValue* castValue = ctx.newReg(_resType->name(), AotValue::Temp);
        ctx.function->appendCode(MOV, castValue->value(ctx), source->value(ctx));
        return castValue;
    }

    AotAddNode::AotAddNode(AotNode* a, AotNode* b) : AotDualArgNode(a, b, dominantArgType(a->resType(), b->resType()),
                                                                    NodeType::Add)
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

        if (argA->type() == NodeType::Const && argB->type() == NodeType::Const)
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
                if (nca->type() == NodeType::Add)
                    return new AotAddNode(nonConstA->releaseNonConstArg(), *distantConstNode + *ca);
                if (nonConstA->type() == NodeType::Sub)
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

    AotValue* AotAddNode::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue* left = argA->generateBytecode(ctx);
        AotValue* right = argB->generateBytecode(ctx);
        if (right->flags & AotValue::Temp && !(left->flags & AotValue::Temp))
            std::swap(left, right);
        else
            left = ctx.castTemp(left);
        ctx.function->appendCode(ADD, left->value(ctx), right->value(ctx));
        return left;
    }

    AotSubNode::AotSubNode(AotNode* a, AotNode* b) : AotDualArgNode(a, b, dominantArgType(a->resType(), b->resType()), NodeType::Sub)
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

        if (argA->type() == NodeType::Const && argB->type() == NodeType::Const)
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
                if (nca->type() == NodeType::Add)
                    return new AotAddNode(*distantConstNode - *ca, nonConstA->releaseNonConstArg());
                if (nonConstA->type() == NodeType::Sub)
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

    AotValue* AotSubNode::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue* left = ctx.castTemp(argA->generateBytecode(ctx));
        AotValue* right = argB->generateBytecode(ctx);
        ctx.function->appendCode(SUB, left->value(ctx), right->value(ctx));
        return left;
    }

    AotMulNode::AotMulNode(AotNode* a, AotNode* v) : AotDualArgNode(a, v, dominantArgType(a->resType(), v->resType()),
                                                                    NodeType::Mul)
    {
        if (argA->resType() != _resType)
            argA = std::unique_ptr<AotNode>(new AotCastNode(argA.release(), _resType));
        if (argB->resType() != _resType)
            argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), _resType));
    }

    AotValue* AotMulNode::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue* left = argA->generateBytecode(ctx);
        AotValue* right = argB->generateBytecode(ctx);
        if (right->flags & AotValue::Temp && !(left->flags & AotValue::Temp))
            std::swap(left, right);
        else
            left = ctx.castTemp(left);
        ctx.function->appendCode(MUL, left->value(ctx), right->value(ctx));
        return left;
    }

    AotDivNode::AotDivNode(AotNode* a, AotNode* b) : AotDualArgNode(a, b, dominantArgType(a->resType(), b->resType()),
                                                                    NodeType::Div)
    {
        if (argA->resType() != _resType)
            argA = std::unique_ptr<AotNode>(new AotCastNode(argA.release(), _resType));
        if (argB->resType() != _resType)
            argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), _resType));
    }

    AotValue* AotDivNode::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue* left = ctx.castTemp(argA->generateBytecode(ctx));
        AotValue* right = ctx.castReg(argB->generateBytecode(ctx));
        ctx.function->appendCode(DIV, left->value(ctx), right->value(ctx));
        return left;
    }

    AotReturnNode::AotReturnNode() : AotNode(nullptr, NodeType::Return)
    {

    }

    AotNode* AotReturnNode::optimize()
    {
        return this;
    }

    AotValue* AotReturnNode::generateBytecode(CompilerCtx& ctx) const
    {
        ctx.function->appendCode(Operand::RET);
        return {};
    }

    AotReturnValueNode::AotReturnValueNode(AotNode* arg) : AotSingleArgNode(arg, arg->resType(), NodeType::ReturnValue)
    {

    }

    AotValue* AotReturnValueNode::generateBytecode(CompilerCtx& ctx) const
    {
        auto value = ctx.castReg(arg->generateBytecode(ctx));

        if(value->isStackRef())
        {
            //This is where a move/copy constructor would go
            auto* sDef = static_cast<StructDef*>(value->def);
            auto ptr = ctx.newReg(value->def, 0);
            if(ctx.localStructIndices.count(sDef))
                ctx.function->appendCode(Operand::MALLOC, ptr->value(ctx), ctx.localStructIndices.at(sDef));
            else
            {
                uint16_t sIndex = 0;
                for(auto& sName : ctx.script->linkedStructs)
                {
                    if(sName == sDef->name())
                        break;
                    ++sIndex;
                }
                if(sIndex == ctx.script->linkedStructs.size())
                    ctx.script->linkedStructs.push_back(sDef->name());
                ctx.function->appendCode(Operand::EXMALLOC, ptr->value(ctx), sIndex);
            }
            for(auto& m : sDef->members())
            {
                Value valA = value->value(ctx);
                valA.offset = m.offset;
                valA.storageType = ValueStorageType_DerefPtr;
                valA.valueType = m.type->type();
                Value valB = ptr->value(ctx);
                valB.offset = m.offset;
                valB.storageType = ValueStorageType_DerefPtr;
                ctx.function->appendCode(MOV, valB, valA);
            }
            value = ptr;
        }

        ctx.function->appendCode(RETV, value->value(ctx));

        return nullptr;
    }

    AotCompareNode::AotCompareNode(Mode mode, AotNode* a, AotNode* b) : _mode(mode), AotDualArgNode(a, b, getNativeTypeDef(ValueType::Bool), NodeType::Compare)
    {
        auto castType = dominantArgType(a->resType(), b->resType());
        if (argA->resType() != castType)
            argA = std::unique_ptr<AotNode>(new AotCastNode(argA.release(), castType));
        if (argB->resType() != castType)
            argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), castType));
    }

    AotValue* AotCompareNode::generateBytecode(CompilerCtx& ctx) const
    {
        auto a = ctx.castReg(argA->generateBytecode(ctx));
        auto b = argB->generateBytecode(ctx);

        AotValue* result = ctx.blankValue();
        bool sign = a->def->type() == Int32 || a->def->type() == Int64;
        switch (_mode)
        {
            case Equal:
            case NotEqual:
                result->compareType = (AotValue::CompareType)_mode;
                break;
            case Greater:
                result->compareType = sign ? AotValue::GreaterRes : AotValue::AboveRes;
                break;
            case GreaterEqual:
                result->compareType = sign ? AotValue::GreaterEqualRes : AotValue::AboveEqualRes;
                break;
        }

        result->def = resType();

        ctx.function->appendCode(CMP, a->value(ctx), b->value(ctx));

        return result;
    }

    AotAssignNode::AotAssignNode(AotNode* lvalue, AotNode* rvalue) : AotDualArgNode(lvalue, rvalue, lvalue->resType(), NodeType::Assign)
    {
        if (argB->resType() != _resType)
            argB = std::unique_ptr<AotNode>(new AotCastNode(argB.release(), _resType));
    }

    AotValue* AotAssignNode::generateBytecode(CompilerCtx& ctx) const
    {
        auto rValue = ctx.castValue(argB->generateBytecode(ctx));
        auto lValue = argA->generateBytecode(ctx);

        if(lValue->isRef() && lValue->flags & AotValue::Initialized && rValue->isRef())
        {
            //This is where a move/copy constructor would go
            auto* sDef = static_cast<StructDef*>(rValue->def);
            for(auto& m : sDef->members())
            {
                Value valA = lValue->value(ctx);
                valA.offset = m.offset;
                valA.storageType = ValueStorageType_DerefPtr;
                Value valB = rValue->value(ctx);
                valB.offset = m.offset;
                valB.storageType = ValueStorageType_DerefPtr;
                valB.valueType = m.type->type();
                ctx.function->appendCode(MOV, valA, valB);
            }
            if(rValue->isExternalRef() && rValue->isTemp())
                ctx.function->appendCode(FREE, rValue->value(ctx));
        }
        else
            ctx.function->appendCode(MOV, lValue->value(ctx), rValue->value(ctx));

        lValue->flags |= AotValue::Initialized;

        return lValue;
    };
}
//
// Created by wirewhiz on 17/10/22.
//

#include "aotOperationNodes.h"
#include "../compiler.h"
#include "../typeDef.h"
#include "../nativeTypes.h"
namespace BraneScript
{
    AotSingleArgNode::AotSingleArgNode(AotNode* arg, const TypeDef* resType, NodeType type) : AotNode(resType, type), arg(arg)
    {

    }

    AotNode* AotSingleArgNode::optimize()
    {
        auto optArg = arg->optimize();
        if (optArg != arg.get())
            arg = std::unique_ptr<AotNode>(optArg);
        return this;
    }


    AotDualArgNode::AotDualArgNode(AotNode* argA, AotNode* argB, const TypeDef* resType, NodeType type) : AotNode(resType,
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

    AotCastNode::AotCastNode(AotNode* arg, const TypeDef* castType) : AotSingleArgNode(arg, castType, NodeType::Cast)
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
        if (source->def == _resType)
            return source;

        source = ctx.castReg(source);
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
        assert(left->def == right->def);
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
        //Call destructors for local values
        for(auto& v : ctx.values)
        {
            if(!v->isStackRef())
                continue;

            auto sDef = static_cast<const StructDef*>(v->def);
            int16_t dIndex;
            if(ctx.localStructIndices.count(sDef))
            {
                dIndex = ctx.script->findLocalFuncIndex(std::string(sDef->name()) + "::_destruct()");
                assert(dIndex >= 0);
            }
            else
                dIndex = int16_t{-1} -  ctx.script->linkFunction(std::string(sDef->name()) + "::_destruct()");
            ctx.function->appendCode(Operand::CALL, dIndex);
            ctx.function->appendCode(v->value(ctx));
        }

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
            auto* sDef = static_cast<const StructDef*>(value->def);
            auto ptr = ctx.newReg(value->def, 0);
            int16_t sIndex;
            int16_t cIndex;
            int16_t mcIndex;
            if(ctx.localStructIndices.count(sDef))
            {
                sIndex = ctx.localStructIndices.at(sDef);
                cIndex = ctx.script->findLocalFuncIndex(std::string(sDef->name()) + "::_construct()");
                mcIndex = ctx.script->findLocalFuncIndex(std::string(sDef->name()) + "::_move(ref " + sDef->name() + ")");
                assert(mcIndex >= 0);
            }
            else
            {
                sIndex = int16_t{-1} - ctx.script->linkStruct(sDef->name());
                cIndex = int16_t{-1} -  ctx.script->linkFunction(std::string(sDef->name()) + "::_construct()");
                mcIndex = int16_t{-1} -  ctx.script->linkFunction(std::string(sDef->name()) + "::_move(ref " + sDef->name() + ")");
            }
            //Allocate memory to return
            ctx.function->appendCode(Operand::MALLOC, ptr->value(ctx), sIndex);

            //Call constructor
            ctx.function->appendCode(Operand::CALL, cIndex);
            ctx.function->appendCode(ptr->value(ctx));

            //Call move constructor
            ctx.function->appendCode(Operand::CALL, mcIndex);
            ctx.function->appendCode(ptr->value(ctx));
            ctx.function->appendCode(value->value(ctx));

            value = ptr;
        }

        //Call destructors for local values
        for(auto& v : ctx.values)
        {
            if(!v->isStackRef())
                continue;

            auto sDef = static_cast<const StructDef*>(v->def);
            int16_t dIndex;
            if(ctx.localStructIndices.count(sDef))
            {
                dIndex = ctx.script->findLocalFuncIndex(std::string(sDef->name()) + "::_destruct()");
                assert(dIndex >= 0);
            }
            else
                dIndex = int16_t{-1} -  ctx.script->linkFunction(std::string(sDef->name()) + "::_destruct()");
            ctx.function->appendCode(Operand::CALL, dIndex);
            ctx.function->appendCode(v->value(ctx));
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
            auto s = static_cast<const StructDef*>(lValue->def);
            bool shouldMove = rValue->isExternalRef() && rValue->isTemp();
            std::string cName;
            if(shouldMove)
                cName = std::string(s->name()) + "::_move(ref " + s->name() + ")";
            else
                cName = std::string(s->name()) + "::_copy(const ref " + s->name() + ")";

            int16_t cIndex;
            if(ctx.localStructIndices.count(s))
                cIndex = ctx.script->findLocalFuncIndex(cName);
            else
                cIndex = int16_t{-1} - ctx.script->linkFunction(cName);
            //Call constructor
            ctx.function->appendCode(Operand::CALL, cIndex);
            ctx.function->appendCode(lValue->value(ctx));
            ctx.function->appendCode(rValue->value(ctx));

            if(shouldMove)
            {
                //Destruct the temp struct before deleting
                int16_t dIndex;
                if(ctx.localStructIndices.count(s))
                    dIndex = ctx.script->findLocalFuncIndex(std::string(s->name()) + "::_destruct()");
                else
                    dIndex = int16_t{-1} - ctx.script->linkFunction(std::string(s->name()) + "::_destruct()");
                ctx.function->appendCode(Operand::CALL, dIndex);
                ctx.function->appendCode(rValue->value(ctx));
                ctx.function->appendCode(FREE, rValue->value(ctx));
            }
        }
        else
            ctx.function->appendCode(MOV, lValue->value(ctx), rValue->value(ctx));

        lValue->flags |= AotValue::Initialized;

        return lValue;
    };
}
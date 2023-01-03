//
// Created by wirewhiz on 17/10/22.
//

#include "aotOperationNodes.h"
#include "../compiler.h"
#include "../typeDef.h"
#include "../nativeTypes.h"
#include "../operator.h"

namespace BraneScript
{


    AotUnaryArgNode::AotUnaryArgNode(AotNode* arg, const TypeDef* resType, NodeType type) : AotNode(resType, type), arg(arg)
    {

    }

    AotNode* AotUnaryArgNode::optimize()
    {
        auto optArg = arg->optimize();
        if (optArg != arg.get())
            arg = std::unique_ptr<AotNode>(optArg);
        return this;
    }


    AotBinaryArgNode::AotBinaryArgNode(AotNode* argA, AotNode* argB, const TypeDef* resType, NodeType type) : AotNode(resType,
                                                                                                                      type),
                                                                                                              argA(argA),
                                                                                                              argB(argB)
    {

    }

    AotNode* AotBinaryArgNode::optimize()
    {
        auto optArgA = argA->optimize();
        if (optArgA != argA.get())
            argA = std::unique_ptr<AotNode>(optArgA);
        auto optArgB = argB->optimize();
        if (optArgB != argB.get())
            argB = std::unique_ptr<AotNode>(optArgB);
        return this;
    }

    AotNode* AotBinaryArgNode::constArg() const
    {
        if (argA->type() == NodeType::Const)
            return argA.get();
        if (argB->type() == NodeType::Const)
            return argB.get();
        return nullptr;
    }

    AotNode* AotBinaryArgNode::nonConstArg() const
    {
        if (argA->type() != NodeType::Const)
            return argA.get();
        if (argB->type() != NodeType::Const)
            return argB.get();
        return nullptr;
    }

    AotNode* AotBinaryArgNode::releaseNonConstArg()
    {
        if (argA->type() != NodeType::Const)
            return argA.release();
        if (argB->type() != NodeType::Const)
            return argB.release();
        assert(false);
        return nullptr;
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

    AotReturnValueNode::AotReturnValueNode(AotNode* arg) : AotUnaryArgNode(arg, arg->resType(), NodeType::ReturnValue)
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

    AotUnaryOperatorNode::AotUnaryOperatorNode(const Operator* opr, AotNode* arg) : _opr(opr), AotUnaryArgNode(arg, opr->resType(), NodeType::Operator)
    {

    }

    AotNode* AotUnaryOperatorNode::optimize()
    {
        if(arg->type() != NodeType::Const)
            return this;
        auto* constexprOpr = dynamic_cast<const ConstexprOperator*>(_opr);
        if(!constexprOpr)
            return this;
        return constexprOpr->precalculate(static_cast<AotConstNode*>(arg.get()), nullptr);
    }

    AotValue* AotUnaryOperatorNode::generateBytecode(CompilerCtx& ctx) const
    {
        return _opr->generateBytecode(ctx, arg->generateBytecode(ctx), nullptr);
    }

    AotBinaryOperatorNode::AotBinaryOperatorNode(const Operator* opr, AotNode* arg1, AotNode* arg2) : _opr(opr), AotBinaryArgNode(arg1, arg2, opr->resType(), NodeType::Operator)
    {

    }

    AotNode* AotBinaryOperatorNode::optimize()
    {
        if(argA->type() != NodeType::Const || argB->type() != NodeType::Const)
            return this;
        auto* constexprOpr = dynamic_cast<const ConstexprOperator*>(_opr);
        if(!constexprOpr)
            return this;
        return constexprOpr->precalculate(static_cast<AotConstNode*>(argA.get()), static_cast<AotConstNode*>(argB.get()));
    }

    AotValue* AotBinaryOperatorNode::generateBytecode(CompilerCtx& ctx) const
    {
        auto a = argA->generateBytecode(ctx);
        if(a->isCompare())
            a = ctx.castReg(a);
        return _opr->generateBytecode(ctx, a, argB->generateBytecode(ctx));
    }

    AotAssignNode::AotAssignNode(AotNode* lvalue, AotNode* rvalue) : AotBinaryArgNode(lvalue, rvalue, lvalue->resType(), NodeType::Assign)
    {

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
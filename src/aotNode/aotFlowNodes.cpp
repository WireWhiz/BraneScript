//
// Created by eli on 10/24/2022.
//

#include "aotFlowNodes.h"

#include "../compiler.h"

#include "../functionHandle.h"

namespace BraneScript
{
    AotScope::AotScope(std::vector<AotNode*> operations) : AotNode(nullptr, NodeType::Scope)
    {
        _operations.reserve(operations.size());
        for (AotNode* node: operations)
            _operations.push_back(std::unique_ptr<AotNode>(node));
    }

    AotNode* AotScope::optimize()
    {
        for (auto& op: _operations)
        {
            AotNode* result = op->optimize();
            if (result != op.get())
                op = std::unique_ptr<AotNode>(result);
        }
        return this;
    }

    AotValue* AotScope::generateBytecode(CompilerCtx& ctx) const
    {
        for (auto& op: _operations)
            op->generateBytecode(ctx);
        return {};
    }

    AotConditionBase::AotConditionBase(TypeDef* resType, AotNode::NodeType type) : AotNode(resType, type)
    {

    }

    void AotConditionBase::jumpOnConditionFalse(AotValue* condition, uint32_t markIndex, CompilerCtx& ctx)
    {
        if(!condition->isCompare())
        {
            if(condition->storageType == ValueStorageType_Const)
                condition = ctx.castReg(condition);
            ctx.function->appendCode(TEST, condition->value(ctx));
            ctx.function->appendCode(JE, markIndex);
            return;
        }
        switch (condition->compareType)
        {
            case AotValue::EqualRes:
                ctx.function->appendCode(JNE, markIndex);
                break;
            case AotValue::NotEqualRes:
                ctx.function->appendCode(JE, markIndex);
                break;
            case AotValue::AboveRes:
                ctx.function->appendCode(JBE, markIndex);
                break;
            case AotValue::GreaterRes:
                ctx.function->appendCode(JLE, markIndex);
                break;
            case AotValue::AboveEqualRes:
                ctx.function->appendCode(JB, markIndex);
                break;
            case AotValue::GreaterEqualRes:
                ctx.function->appendCode(JL, markIndex);
                break;
            default:
                assert(false);
        }
    }

    AotIf::AotIf(AotNode* condition, AotNode* operation) : _condition(condition), _operation(operation),
                                                           AotConditionBase(nullptr, NodeType::If)
    {

    }

    AotNode* AotIf::optimize()
    {
        auto cond = _condition->optimize();
        if (cond != _condition.get())
            _condition = std::unique_ptr<AotNode>(cond);
        auto op = _operation->optimize();
        if (op != _operation.get())
            _operation = std::unique_ptr<AotNode>(op);
        return this;
    }

    AotValue* AotIf::generateBytecode(CompilerCtx& ctx) const
    {
        uint32_t markIndex = ctx.newMark();
        AotValue* condition = _condition->generateBytecode(ctx);
        jumpOnConditionFalse(condition, markIndex, ctx);

        _operation->generateBytecode(ctx);

        ctx.function->appendCode(MARK, markIndex);
        return {};
    }

    AotWhile::AotWhile(AotNode* condition, AotNode* operation) : _condition(condition), _operation(operation),
                                                                 AotConditionBase(nullptr, NodeType::If)
    {
    }

    AotNode* AotWhile::optimize()
    {
        auto cond = _condition->optimize();
        if (cond != _condition.get())
            _condition = std::unique_ptr<AotNode>(cond);
        auto op = _operation->optimize();
        if (op != _operation.get())
            _operation = std::unique_ptr<AotNode>(op);
        return this;
    }

    AotValue* AotWhile::generateBytecode(CompilerCtx& ctx) const
    {
        uint32_t beginMark = ctx.newMark();
        uint32_t exitMark = ctx.newMark();
        ctx.function->appendCode(MARK, beginMark);

        AotValue* condition = _condition->generateBytecode(ctx);
        jumpOnConditionFalse(condition, exitMark, ctx);

        _operation->generateBytecode(ctx);

        ctx.function->appendCode(JMP, beginMark);
        ctx.function->appendCode(MARK, exitMark);
        return {};
    }

    AotFunctionCall::AotFunctionCall(int16_t functionIndex, const TypeDef* returnType, const std::vector<AotNode*>& arguments) : AotNode(returnType, NodeType::Call)
    {
        _functionIndex = functionIndex;
        _arguments.reserve(arguments.size());
        for (AotNode* node: arguments)
            _arguments.push_back(std::unique_ptr<AotNode>(node));
    }

    AotNode* AotFunctionCall::optimize()
    {
        for (auto& arg : _arguments)
        {
            auto* result = arg->optimize();
            if(arg.get() != result)
                arg = std::unique_ptr<AotNode>(result);
        }
        return this;
    }

    AotValue* AotFunctionCall::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue* returnValue = nullptr;

        std::vector<AotValue*> args;
        for(auto& arg : _arguments)
            args.push_back(ctx.castReg(arg->generateBytecode(ctx)));
        if(_resType)
        {
            returnValue = ctx.newReg(_resType, AotValue::Temp | AotValue::Initialized);
            if(returnValue->def->type() == Struct)
                returnValue->flags |= AotValue::ExternalRef;
        }

        ctx.function->appendCode(Operand::CALL, _functionIndex);
        if(_resType)
            ctx.function->appendCode(returnValue->value(ctx));
        for(auto& a : args)
            ctx.function->appendCode(a->value(ctx));

        return returnValue;
    }
}
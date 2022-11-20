//
// Created by eli on 10/24/2022.
//

#include "aotFlowNodes.h"

#include "../compiler.h"

#include "../functionHandle.h"

namespace BraneScript
{
    AotScope::AotScope(std::vector<AotNode*> operations) : AotNode(nullptr, Scope)
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

    AotValue AotScope::generateBytecode(CompilerCtx& ctx) const
    {
        for (auto& op: _operations)
            op->generateBytecode(ctx);
        return {};
    }

    AotConditionBase::AotConditionBase(TypeDef* resType, AotNode::NodeType type) : AotNode(resType, type)
    {

    }

    void AotConditionBase::jumpOnConditionFalse(AotValue& condition, uint32_t markIndex, CompilerCtx& ctx)
    {
        if(!condition.isCompare())
        {
            if(condition.valueIndex.storageType == ValueStorageType_Const)
                condition = ctx.castReg(condition);
            ctx.function->appendCode(TEST, condition.valueIndex);
            ctx.function->appendCode(JE, markIndex);
            return;
        }
        switch (condition.compareType)
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
                                                           AotConditionBase(nullptr, If)
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

    AotValue AotIf::generateBytecode(CompilerCtx& ctx) const
    {
        uint32_t markIndex = ctx.newMark();
        AotValue condition = _condition->generateBytecode(ctx);
        jumpOnConditionFalse(condition, markIndex, ctx);

        _operation->generateBytecode(ctx);

        ctx.function->appendCode(MARK, markIndex);
        return {};
    }

    AotWhile::AotWhile(AotNode* condition, AotNode* operation) : _condition(condition), _operation(operation),
                                                                 AotConditionBase(nullptr, If)
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

    AotValue AotWhile::generateBytecode(CompilerCtx& ctx) const
    {
        uint32_t beginMark = ctx.newMark();
        uint32_t exitMark = ctx.newMark();
        ctx.function->appendCode(MARK, beginMark);

        AotValue condition = _condition->generateBytecode(ctx);
        jumpOnConditionFalse(condition, exitMark, ctx);

        _operation->generateBytecode(ctx);

        ctx.function->appendCode(JMP, beginMark);
        ctx.function->appendCode(MARK, exitMark);
        return {};
    }

    AotFunctionCall::AotFunctionCall(uint32_t functionIndex, TypeDef* returnType, const std::vector<AotNode*>& arguments) : AotNode(returnType, Call)
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

    AotValue AotFunctionCall::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue returnValue;

        std::vector<AotValue> args;
        for(auto& arg : _arguments)
            args.push_back(ctx.castReg(arg->generateBytecode(ctx)));
        if(_resType)
            returnValue = ctx.newReg(_resType, AotValue::Temp);

        ctx.function->appendCode(Operand::CALL, _functionIndex);
        if(_resType)
            ctx.function->appendCode(returnValue.valueIndex);
        for(auto& a : args)
            ctx.function->appendCode(a.valueIndex);

        return returnValue;
    }

    AotExternalFunctionCall::AotExternalFunctionCall(uint32_t library, std::string name, TypeDef* returnType, const std::vector<AotNode*>& arguments) : _library(library), _name(std::move(name)), AotNode(returnType, Call)
    {
        _arguments.reserve(arguments.size());
        for (AotNode* node: arguments)
            _arguments.push_back(std::unique_ptr<AotNode>(node));
    }

    AotNode* AotExternalFunctionCall::optimize()
    {
        for (auto& arg : _arguments)
        {
            auto* result = arg->optimize();
            if(arg.get() != result)
                arg = std::unique_ptr<AotNode>(result);
        }
        return this;
    }

    AotValue AotExternalFunctionCall::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue returnValue;

        std::vector<AotValue> args;
        for(auto& arg : _arguments)
            args.push_back(ctx.castReg(arg->generateBytecode(ctx)));
        if(_resType)
            returnValue = ctx.newReg(_resType, AotValue::Temp);

        ctx.function->appendCode(Operand::EXCALL, _library);
        ctx.function->appendCode(_name);
        assert(args.size() < 128);
        uint8_t argFlags = args.size();
        if(_resType)
            argFlags |= (1 << 7);
        else
            argFlags &= ~(1 << 7);
        ctx.function->appendCode(argFlags);

        if(_resType)
            ctx.function->appendCode(returnValue.valueIndex);
        for(auto& a : args)
            ctx.function->appendCode(a.valueIndex);

        return returnValue;
    }
}
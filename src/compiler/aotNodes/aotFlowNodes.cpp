//
// Created by eli on 10/24/2022.
//

#include "aotFlowNodes.h"

#include <utility>

#include "../compiler.h"

#include "functionHandle.h"

namespace BraneScript
{
    AotNodeList::AotNodeList() : AotNode(nullptr) {}

    void AotNodeList::appendStatement(AotNode* stmt)
    {
        if(auto* resType = stmt->resType())
            _resType = resType;
        operations.push_back(std::unique_ptr<AotNode>(stmt));
    }

    AotNode* AotNodeList::optimize(FunctionCompilerCtx& ctx)
    {
        for(auto itr = operations.begin(); itr != operations.end();)
        {
            auto& op = *itr;
            AotNode* result = op->optimize(ctx);
            if(result == nullptr)
            {
                itr = operations.erase(itr);
                continue;
            }
            if(result != op.get())
                op.reset(result);
            ++itr;
        }
        return this;
    }

    AotValue* AotNodeList::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        AotValue* resValue = nullptr;
        for(auto& op : operations)
        {
            if(auto* hasRet = op->generateBytecode(ctx))
                resValue = hasRet;
        }
        return resValue;
    }

    AotReturnNode::AotReturnNode() : AotNode(nullptr) {}

    AotNode* AotReturnNode::optimize(FunctionCompilerCtx& ctx) { return this; }

    AotValue* AotReturnNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        ctx.appendCode(Operand::RET);
        return {};
    }

    AotReturnValueNode::AotReturnValueNode(AotNode* arg) : AotUnaryArgNode(arg, arg->resType()) {
        assert(arg);
        assert(arg->resType()->type() != ValueType::Struct);
    }

    AotValue* AotReturnValueNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        auto value = ctx.castReg(arg->generateBytecode(ctx));

        assert(!value->isStruct());

        ctx.appendCode(RETV, ctx.serialize(value));
        if(value->isTemp())
            ctx.releaseValue(value);
        return nullptr;
    }

    AotJump::AotJump(uint16_t target) : AotNode(nullptr) { _target = target; }

    AotNode* AotJump::optimize(FunctionCompilerCtx& ctx) { return this; }

    AotValue* AotJump::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        ctx.appendCode(Operand::JMP, _target);
        return nullptr;
    }

    AotJumpFalse::AotJumpFalse(AotNode* condition, uint16_t target) : AotUnaryArgNode(condition, nullptr)
    {
        _target = target;
    }

    AotNode* AotJumpFalse::optimize(FunctionCompilerCtx& ctx) { return this; }

    AotValue* AotJumpFalse::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        auto condition = arg->generateBytecode(ctx);
        if(!condition->isCompare())
        {
            if(condition->storageType == ValueStorageType_Const)
                condition = ctx.castReg(condition);
            ctx.appendCode(TEST, ctx.serialize(condition));
            ctx.appendCode(JE, _target);
            return nullptr;
        }
        switch(condition->compareType)
        {
            case AotValue::EqualRes:
                ctx.appendCode(JNE, _target);
                break;
            case AotValue::NotEqualRes:
                ctx.appendCode(JE, _target);
                break;
            case AotValue::AboveRes:
                ctx.appendCode(JBE, _target);
                break;
            case AotValue::GreaterRes:
                ctx.appendCode(JLE, _target);
                break;
            case AotValue::AboveEqualRes:
                ctx.appendCode(JB, _target);
                break;
            case AotValue::GreaterEqualRes:
                ctx.appendCode(JL, _target);
                break;
            default:
                assert(false);
        }
        return nullptr;
    }

    AotFunctionCall::AotFunctionCall(std::string signature,
                                     const TypeDef* returnType,
                                     const std::vector<AotNode*>& arguments)
        : AotNode(returnType)
    {
        _signature = std::move(signature);
        _arguments.reserve(arguments.size());
        for(AotNode* node : arguments)
            _arguments.push_back(std::unique_ptr<AotNode>(node));
    }

    AotNode* AotFunctionCall::optimize(FunctionCompilerCtx& ctx)
    {
        for(auto& arg : _arguments)
        {
            auto* result = arg->optimize(ctx);
            if(arg.get() != result)
                arg = std::unique_ptr<AotNode>(result);
        }

        return this;
    }

    AotValue* AotFunctionCall::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        AotValue* returnValue = nullptr;

        std::vector<AotValue*> args;
        for(auto& arg : _arguments)
            args.push_back(ctx.castReg(arg->generateBytecode(ctx)));
        if(_resType)
        {
            if(_resType->type() != ValueType::Struct)
                returnValue = ctx.newReg(_resType, AotValue::Temp);
            else
            {
                //Return reference to ref arg, instead of an actual return register
                assert(!args.empty());
                returnValue = args[0];
            }
        }

        ctx.appendCode(Operand::CALL, ctx.script.linkFunction(_signature));
        if(_resType && _resType->type() != ValueType::Struct)
            ctx.appendCode(ctx.serialize(returnValue));
        for(auto& a : args)
            ctx.appendCode(ctx.serialize(a));

        return returnValue;
    }

    AotJumpTarget::AotJumpTarget(uint32_t id) : AotNode(nullptr) { _id = id; }

    AotNode* AotJumpTarget::optimize(FunctionCompilerCtx& ctx) { return this; }

    AotValue* AotJumpTarget::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        ctx.appendCode(MARK, _id);
        return nullptr;
    }

    uint32_t AotJumpTarget::id() const { return _id; }

} // namespace BraneScript
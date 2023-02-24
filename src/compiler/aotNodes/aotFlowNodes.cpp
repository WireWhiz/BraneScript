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

    void AotNodeList::appendStatement(AotNode* stmt) { operations.push_back(std::unique_ptr<AotNode>(stmt)); }

    AotNode* AotNodeList::optimize()
    {
        for(auto itr = operations.begin(); itr != operations.end();)
        {
            auto& op = *itr;
            AotNode* result = op->optimize();
            if(result == nullptr)
            {
                itr = operations.erase(itr);
                continue;
            }
            if(result != op.get())
                op = std::unique_ptr<AotNode>(result);
            ++itr;
        }
        return this;
    }

    AotValue* AotNodeList::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        for(auto& op : operations)
            op->generateBytecode(ctx);
        return nullptr;
    }

    AotReturnNode::AotReturnNode() : AotNode(nullptr) {}

    AotNode* AotReturnNode::optimize() { return this; }

    AotValue* AotReturnNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        // Call destructors for local values
        for(auto& v : ctx.values)
        {
            if(!v.aotValue->isStackRef())
                continue;

            auto sDef = static_cast<const StructDef*>(v.aotValue->type);
            int16_t dIndex = ctx.script.linkFunction(std::string(sDef->name()) + "::_destruct()");
            ctx.appendCode(Operand::CALL, dIndex);
            ctx.appendCode(ctx.serialize(v.aotValue.get()));
        }

        ctx.appendCode(Operand::RET);
        return {};
    }

    AotReturnValueNode::AotReturnValueNode(AotNode* arg) : AotUnaryArgNode(arg, arg->resType()) {}

    AotValue* AotReturnValueNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        auto value = ctx.castReg(arg->generateBytecode(ctx));

        if(value->isStackRef())
        {
            auto* sDef = static_cast<const StructDef*>(value->type);
            auto ptr = ctx.newReg(value->type, AotValue::Temp);
            int16_t cIndex = ctx.script.linkFunction(std::string(sDef->name()) + "::_construct()");
            int16_t mcIndex = ctx.script.linkFunction(std::string(sDef->name()) + "::_move(ref " + sDef->name() + ")");
            // Allocate memory to return
            ctx.appendCode(Operand::MALLOC, ctx.serialize(ptr), sDef->size());

            // Call constructor
            ctx.appendCode(Operand::CALL, cIndex);
            ctx.appendCode(ctx.serialize(ptr));

            // Call move constructor
            ctx.appendCode(Operand::CALL, mcIndex);
            ctx.appendCode(ctx.serialize(ptr));
            ctx.appendCode(ctx.serialize(value));

            if(value->isTemp())
                ctx.releaseValue(value);
            value = ptr;
        }

        // Call destructors for local values
        for(auto& v : ctx.values)
        {
            if(!v.aotValue->isStackRef())
                continue;

            auto sDef = static_cast<const StructDef*>(v.aotValue->type);
            int16_t dIndex = ctx.script.linkFunction(std::string(sDef->name()) + "::_destruct()");
            ctx.appendCode(Operand::CALL, dIndex);
            ctx.appendCode(ctx.serialize(v.aotValue.get()));
        }

        ctx.appendCode(RETV, ctx.serialize(value));
        if(value->isTemp())
            ctx.releaseValue(value);

        return nullptr;
    }

    AotJump::AotJump(uint16_t target) : AotNode(nullptr) { _target = target; }

    AotNode* AotJump::optimize() { return this; }

    AotValue* AotJump::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        ctx.appendCode(Operand::JMP, _target);
        return nullptr;
    }

    AotJumpFalse::AotJumpFalse(AotNode* condition, uint16_t target) : AotUnaryArgNode(condition, nullptr)
    {
        _target = target;
    }

    AotNode* AotJumpFalse::optimize() { return this; }

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

    AotNode* AotFunctionCall::optimize()
    {
        for(auto& arg : _arguments)
        {
            auto* result = arg->optimize();
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
            returnValue = ctx.newReg(_resType, AotValue::Temp);
            if(returnValue->type->type() == ValueType::Struct)
                returnValue->flags |= AotValue::HeapRef;
        }

        ctx.appendCode(Operand::CALL, ctx.script.linkFunction(_signature));
        if(_resType)
            ctx.appendCode(ctx.serialize(returnValue));
        for(auto& a : args)
            ctx.appendCode(ctx.serialize(a));

        return returnValue;
    }

    AotJumpTarget::AotJumpTarget(uint32_t id) : AotNode(nullptr) { _id = id; }

    AotNode* AotJumpTarget::optimize() { return this; }

    AotValue* AotJumpTarget::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        ctx.appendCode(MARK, _id);
        return nullptr;
    }

    uint32_t AotJumpTarget::id() const { return _id; }

} // namespace BraneScript
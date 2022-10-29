//
// Created by eli on 10/24/2022.
//

#include "aotFlowNodes.h"

#include "../compiler.h"

AotScope::AotScope(std::vector<AotNode*> operations) : AotNode(nullptr, Scope)
{
    _operations.reserve(operations.size());
    for(AotNode* node : operations)
        _operations.push_back(std::unique_ptr<AotNode>(node));
}

AotNode* AotScope::optimize()
{
    for(auto& op : _operations)
    {
        AotNode* result = op->optimize();
        if(result != op.get())
            op = std::unique_ptr<AotNode>(result);
    }
    return this;
}

AotValue AotScope::generateBytecode(CompilerCtx& ctx) const
{
    for(auto& op : _operations)
        op->generateBytecode(ctx);
    return {};
}

AotIf::AotIf(AotNode* condition, AotNode* operation) : _condition(condition), _operation(operation), AotNode(nullptr, If)
{

}

AotNode* AotIf::optimize()
{
    auto cond = _condition->optimize();
    if(cond != _condition.get())
        _condition = std::unique_ptr<AotNode>(cond);
    auto op = _operation->optimize();
    if(op != _operation.get())
        _operation = std::unique_ptr<AotNode>(op);
    return this;
}

AotValue AotIf::generateBytecode(CompilerCtx& ctx) const
{
    uint32_t markIndex = ctx.newMark();
    AotValue condition = _condition->generateBytecode(ctx);
    switch(condition.valueIndex.storageType)
    {

        case ValueStorageType_Mem:
            condition = ctx.castReg(condition);
        case ValueStorageType_Reg:
        {
            ctx.function->appendCode(ScriptFunction::TEST0, condition.valueIndex);
            ctx.function->appendCode(ScriptFunction::JE, markIndex);
        }
            break;
        case ValueStorageType_EqualRes:
            ctx.function->appendCode(ScriptFunction::JNE, markIndex);
            break;
        case ValueStorageType_NotEqualRes:
            ctx.function->appendCode(ScriptFunction::JE, markIndex);
            break;
        case ValueStorageType_AboveRes:
            ctx.function->appendCode(ScriptFunction::JA, markIndex);
            break;
        case ValueStorageType_GreaterRes:
            ctx.function->appendCode(ScriptFunction::JG, markIndex);
            break;
        case ValueStorageType_AboveEqualRes:
            ctx.function->appendCode(ScriptFunction::JAE, markIndex);
            break;
        case ValueStorageType_GreaterEqualRes:
            ctx.function->appendCode(ScriptFunction::JGE, markIndex);
            break;
    }

    _operation->generateBytecode(ctx);

    ctx.function->appendCode(ScriptFunction::MARK, markIndex);
    return {};
}

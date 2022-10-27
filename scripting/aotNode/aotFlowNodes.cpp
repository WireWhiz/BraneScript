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
    condition = ctx.castReg(condition);
    ctx.function->appendCode(ScriptFunction::TEST0, condition.valueIndex);
    ctx.function->appendCode(ScriptFunction::JE, markIndex);

    _operation->generateBytecode(ctx);

    ctx.function->appendCode(ScriptFunction::MARK, markIndex);
    return {};
}

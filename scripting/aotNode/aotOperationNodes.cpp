//
// Created by wirewhiz on 17/10/22.
//

#include "aotOperationNodes.h"

AotSingleArgNode::AotSingleArgNode(AotNode*arg) : _arg(arg)
{

}

AotNode* AotSingleArgNode::optimize()
{
    auto optArg = _arg->optimize();
    if(optArg != _arg.get())
        _arg = std::unique_ptr<AotNode>(optArg);
    return this;
}


AotDualArgNode::AotDualArgNode(AotNode* argA, AotNode* argB) : _argA(argA), _argB(argB)
{

}

AotNode* AotDualArgNode::optimize()
{
    auto optArgA = _argA->optimize();
    if(optArgA != _argA.get())
        _argA = std::unique_ptr<AotNode>(optArgA);
    auto optArgB = _argB->optimize();
    if(optArgB != _argB.get())
        _argB = std::unique_ptr<AotNode>(optArgB);
    return this;
}

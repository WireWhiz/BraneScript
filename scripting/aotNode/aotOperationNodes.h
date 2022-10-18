//
// Created by wirewhiz on 17/10/22.
//

#ifndef BRANESCRIPT_AOTOPERATIONNODES_H
#define BRANESCRIPT_AOTOPERATIONNODES_H

#include "aotNode.h"
#include <memory>

class AotSingleArgNode : public AotNode
{
    std::unique_ptr<AotNode> _arg;
public:
    explicit AotSingleArgNode(AotNode* arg);
    AotNode* optimize() override;
};

class AotDualArgNode : public AotNode
{
    std::unique_ptr<AotNode> _argA;
    std::unique_ptr<AotNode> _argB;
public:
    explicit AotDualArgNode(AotNode* argA, AotNode* argB);
    AotNode* optimize() override;
};

class AddNode : public AotDualArgNode
{
public:
    AddNode(std::shared_ptr<AotNode> argA, std::shared_ptr<AotNode> argB);
};


#endif //BRANESCRIPT_AOTOPERATIONNODES_H

//
// Created by eli on 10/24/2022.
//

#ifndef BRANESCRIPT_AOTFLOWNODES_H
#define BRANESCRIPT_AOTFLOWNODES_H

#include "aotNode.h"

#include <vector>
#include <memory>

class AotScope : public AotNode
{
    std::vector<std::unique_ptr<AotNode>> _operations;
public:
    explicit AotScope(std::vector<AotNode*> operations);
    AotNode* optimize() override;
    AotValue generateBytecode(CompilerCtx& ctx) const override;
};

class AotIf : public AotNode
{
    std::unique_ptr<AotNode> _condition;
    std::unique_ptr<AotNode> _operation;
public:
    AotIf(AotNode* condition, AotNode* operation);
    AotNode* optimize() override;
    AotValue generateBytecode(CompilerCtx& ctx) const override;
};

#endif //BRANESCRIPT_AOTFLOWNODES_H

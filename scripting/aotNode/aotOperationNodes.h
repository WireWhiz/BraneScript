//
// Created by wirewhiz on 17/10/22.
//

#ifndef BRANESCRIPT_AOTOPERATIONNODES_H
#define BRANESCRIPT_AOTOPERATIONNODES_H

#include "aotNode.h"
#include <memory>

class AotSingleArgNode : public AotNode
{
protected:
    std::unique_ptr<AotNode> _arg;
public:
    explicit AotSingleArgNode(AotNode* arg, NodeType type);
    AotNode* optimize() override;
};

class AotDualArgNode : public AotNode
{
protected:
    std::unique_ptr<AotNode> _argA;
    std::unique_ptr<AotNode> _argB;
public:
    explicit AotDualArgNode(AotNode* argA, AotNode* argB, NodeType type);
    AotNode* optimize() override;
};

class AotReturnValueNode : public AotSingleArgNode
{
public:
    explicit AotReturnValueNode(AotNode* arg);
    AotValue generateBytecode(CompilerCtx& ctx) const override;
};

class AotAddNode : public AotDualArgNode
{
public:
    AotAddNode(AotNode* argA, AotNode* argB);
    AotValue generateBytecode(CompilerCtx& ctx) const override;
};

class AotSubNode : public AotDualArgNode
{
public:
    AotSubNode(AotNode* argA, AotNode* argB);
    AotNode* optimize() override;
    AotValue generateBytecode(CompilerCtx& ctx) const override;
};

class AotMulNode : public AotDualArgNode
{
public:
    AotMulNode(AotNode* argA, AotNode* argB);
    AotValue generateBytecode(CompilerCtx& ctx) const override;
};

class AotDivNode : public AotDualArgNode
{
public:
    AotDivNode(AotNode* argA, AotNode* argB);
    AotValue generateBytecode(CompilerCtx& ctx) const override;
};

#endif //BRANESCRIPT_AOTOPERATIONNODES_H

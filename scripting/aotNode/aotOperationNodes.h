//
// Created by wirewhiz on 17/10/22.
//

#ifndef BRANESCRIPT_AOTOPERATIONNODES_H
#define BRANESCRIPT_AOTOPERATIONNODES_H

#include "aotNode.h"
#include <memory>

class AotSingleArgNode : public AotNode
{
public:
    std::unique_ptr<AotNode> arg;
    explicit AotSingleArgNode(AotNode* arg,TypeDef* resType, NodeType type);
    AotNode* optimize() override;
};

class AotDualArgNode : public AotNode
{
public:
    std::unique_ptr<AotNode> argA;
    std::unique_ptr<AotNode> argB;
    explicit AotDualArgNode(AotNode* argA, AotNode* argB, TypeDef* resType, NodeType type);
    AotNode* optimize() override;

    AotNode* constArg() const;
    AotNode* nonConstArg() const;
    AotNode* releaseNonConstArg();
};

class AotReturnValueNode : public AotSingleArgNode
{
public:
    explicit AotReturnValueNode(AotNode* arg);
    AotValue generateBytecode(CompilerCtx& ctx) const override;
};

class AotCastNode : public AotSingleArgNode
{
public:
    explicit AotCastNode(AotNode* arg, TypeDef* castType);
    AotNode* optimize() override;
    AotValue generateBytecode(CompilerCtx& ctx) const override;
};

class AotAssignNode : public AotDualArgNode
{
public:
    AotAssignNode(AotNode* lvalue, AotNode* rvalue);
    AotValue generateBytecode(CompilerCtx& ctx) const override;
};

class AotAddNode : public AotDualArgNode
{
public:
    AotAddNode(AotNode* argA, AotNode* argB);
    AotNode* optimize() override;
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

class AotCompareNode : public AotDualArgNode
{
public:
    enum Mode
    {
        Equal = ValueStorageType_EqualRes,
        NotEqual = ValueStorageType_NotEqualRes,
        Greater  = ValueStorageType_GreaterRes,
        GreaterEqual = ValueStorageType_GreaterEqualRes
    };
private:
    Mode _mode;
public:

    AotCompareNode(Mode mode, AotNode* a, AotNode* b);
    AotValue generateBytecode(CompilerCtx& ctx) const override;
};

#endif //BRANESCRIPT_AOTOPERATIONNODES_H

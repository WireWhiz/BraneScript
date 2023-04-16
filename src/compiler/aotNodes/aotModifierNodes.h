//
// Created by wirewhiz on 2/18/23.
//

#ifndef BRANESCRIPT_AOTMODIFIERNODES_H
#define BRANESCRIPT_AOTMODIFIERNODES_H

#include "aotNode.h"
#include <memory>

namespace BraneScript
{
    class AotCastNode : public AotUnaryArgNode
    {
      public:
        explicit AotCastNode(AotNode* arg, const TypeDef* castType);

        AotNode* optimize(FunctionCompilerCtx& ctx) override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotAssignNode : public AotBinaryArgNode
    {
        bool _forceMove;
      public:
        AotAssignNode(AotNode* lvalue, AotNode* rvalue, bool forceMove = false);

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotAddNode : public AotBinaryArgNode
    {
      public:
        AotAddNode(AotNode* argA, AotNode* argB);

        AotNode* optimize(FunctionCompilerCtx& ctx) override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotSubNode : public AotBinaryArgNode
    {
      public:
        AotSubNode(AotNode* argA, AotNode* argB);

        AotNode* optimize(FunctionCompilerCtx& ctx) override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotMulNode : public AotBinaryArgNode
    {
      public:
        AotMulNode(AotNode* a, AotNode* b);

        AotNode* optimize(FunctionCompilerCtx& ctx) override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotDivNode : public AotBinaryArgNode
    {
      public:
        AotDivNode(AotNode* argA, AotNode* argB);

        AotNode* optimize(FunctionCompilerCtx& ctx) override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

} // namespace BraneScript

#endif // BRANESCRIPT_AOTMODIFIERNODES_H

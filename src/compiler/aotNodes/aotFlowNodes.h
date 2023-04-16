//
// Created by eli on 10/24/2022.
//

#ifndef BRANESCRIPT_AOTFLOWNODES_H
#define BRANESCRIPT_AOTFLOWNODES_H

#include "aotNode.h"

#include <vector>
#include <memory>
#include <string>

namespace BraneScript
{
    class AotNodeList : public AotNode
    {
      public:
        AotNodeList();
        std::vector<std::unique_ptr<AotNode>> operations;

        void appendStatement(AotNode* stmt);

        AotNode* optimize(FunctionCompilerCtx& ctx) override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;

    };

    class AotReturnNode : public AotNode
    {
      public:
        AotReturnNode();
        AotNode* optimize(FunctionCompilerCtx& ctx) override;
        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotReturnValueNode : public AotUnaryArgNode
    {
      public:
        AotReturnValueNode(AotNode* arg);

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotJumpTarget : public AotNode
    {
        uint32_t _id = -1;
      public:
        AotJumpTarget(uint32_t id);

        AotNode* optimize(FunctionCompilerCtx& ctx) override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;

        uint32_t id() const;
    };

    class AotJump : public AotNode
    {
        uint32_t _target;
      public:
        AotJump(uint16_t target);

        AotNode* optimize(FunctionCompilerCtx& ctx) override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotJumpFalse : public AotUnaryArgNode
    {
        uint32_t _target;
      public:
        AotJumpFalse(AotNode* condition, uint16_t target);
        AotNode* optimize(FunctionCompilerCtx& ctx) override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotFunctionCall : public AotNode
    {
        std::string _signature;
        std::vector<std::unique_ptr<AotNode>> _arguments;
    public:
        AotFunctionCall(std::string signature, const TypeDef* returnType, const std::vector<AotNode*>& arguments);
        AotNode* optimize(FunctionCompilerCtx& ctx) override;
        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };
}
#endif //BRANESCRIPT_AOTFLOWNODES_H

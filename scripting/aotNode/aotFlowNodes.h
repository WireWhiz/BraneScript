//
// Created by eli on 10/24/2022.
//

#ifndef BRANESCRIPT_AOTFLOWNODES_H
#define BRANESCRIPT_AOTFLOWNODES_H

#include "aotNode.h"

#include <vector>
#include <memory>

namespace BraneScript
{

    class AotScope : public AotNode
    {
        std::vector<std::unique_ptr<AotNode>> _operations;
    public:
        explicit AotScope(std::vector<AotNode*> operations);

        AotNode* optimize() override;

        AotValue generateBytecode(CompilerCtx& ctx) const override;
    };

    class AotConditionBase : public AotNode
    {
    protected:
        static void jumpOnConditionFalse(AotValue& condition, uint32_t markIndex, CompilerCtx& ctx);

    public:
        AotConditionBase(TypeDef* resType, NodeType type);
    };

    class AotIf : public AotConditionBase
    {
        std::unique_ptr<AotNode> _condition;
        std::unique_ptr<AotNode> _operation;
    public:
        AotIf(AotNode* condition, AotNode* operation);

        AotNode* optimize() override;

        AotValue generateBytecode(CompilerCtx& ctx) const override;
    };

    class AotWhile : public AotConditionBase
    {
        std::unique_ptr<AotNode> _condition;
        std::unique_ptr<AotNode> _operation;
    public:
        AotWhile(AotNode* condition, AotNode* operation);

        AotNode* optimize() override;

        AotValue generateBytecode(CompilerCtx& ctx) const override;
    };

    class FunctionCall : public AotNode
    {
        uint32_t _functionIndex;
        std::vector<std::unique_ptr<AotNode>> _arguments;
    public:
        FunctionCall(uint32_t functionIndex, TypeDef* returnType, const std::vector<AotNode*>& arguments);
        AotNode* optimize() override;
        AotValue generateBytecode(CompilerCtx& ctx) const override;
    };
}
#endif //BRANESCRIPT_AOTFLOWNODES_H

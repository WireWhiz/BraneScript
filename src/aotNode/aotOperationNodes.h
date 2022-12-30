//
// Created by wirewhiz on 17/10/22.
//

#ifndef BRANESCRIPT_AOTOPERATIONNODES_H
#define BRANESCRIPT_AOTOPERATIONNODES_H

#include "aotNode.h"
#include <memory>
#include <vector>
#include <string>

namespace BraneScript
{
    class Linker;

    class AotUnaryArgNode : public AotNode
    {
    public:
        std::unique_ptr<AotNode> arg;

        explicit AotUnaryArgNode(AotNode* arg, const TypeDef* resType, NodeType type);

        AotNode* optimize() override;
    };

    class AotBinaryArgNode : public AotNode
    {
    public:
        std::unique_ptr<AotNode> argA;
        std::unique_ptr<AotNode> argB;

        explicit AotBinaryArgNode(AotNode* argA, AotNode* argB, const TypeDef* resType, NodeType type);

        AotNode* optimize() override;

        AotNode* constArg() const;

        AotNode* nonConstArg() const;

        AotNode* releaseNonConstArg();
    };

    class AotReturnNode : public AotNode
    {
    public:
        AotReturnNode();
        AotNode* optimize() override;
        AotValue* generateBytecode(CompilerCtx& ctx) const override;
    };

    class AotReturnValueNode : public AotUnaryArgNode
    {
    public:
        AotReturnValueNode(AotNode* arg);

        AotValue* generateBytecode(CompilerCtx& ctx) const override;
    };


    class Operator;
    class AotUnaryOperatorNode : public AotUnaryArgNode
    {
        const Operator* _opr;
    public:
        AotUnaryOperatorNode(const Operator* opr, AotNode* arg);
        AotNode* optimize() override;
        AotValue* generateBytecode(CompilerCtx& ctx) const override;
    };

    class AotBinaryOperatorNode : public AotBinaryArgNode
    {
        const Operator* _opr;
    public:
        AotBinaryOperatorNode(const Operator* opr, AotNode* arg1, AotNode* arg2);
        AotNode* optimize() override;
        AotValue* generateBytecode(CompilerCtx& ctx) const override;
    };

    class AotAssignNode : public AotBinaryArgNode
    {
    public:
        AotAssignNode(AotNode* lvalue, AotNode* rvalue);

        AotValue* generateBytecode(CompilerCtx& ctx) const override;
    };

    class AotCompareNode : public AotBinaryArgNode
    {
    public:
        enum Mode
        {
            Equal = AotValue::EqualRes,
            NotEqual = AotValue::NotEqualRes,
            Greater = AotValue::GreaterRes,
            GreaterEqual = AotValue::GreaterEqualRes
        };
    private:
        Mode _mode;
    public:

        AotCompareNode(Mode mode, AotNode* a, AotNode* b);

        AotValue* generateBytecode(CompilerCtx& ctx) const override;
    };
}
#endif //BRANESCRIPT_AOTOPERATIONNODES_H

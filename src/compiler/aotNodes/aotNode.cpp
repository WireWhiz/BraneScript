//
// Created by wirewhiz on 17/10/22.
//

#include "aotNode.h"
#include <cassert>
#include "../compiler.h"
#include "irFunction.h"
#include "typeDef.h"

namespace BraneScript
{
    AotNode::AotNode(const TypeDef* resType) : _resType(resType) {}

    const TypeDef* AotNode::resType() const { return _resType; }

    AotUnaryArgNode::AotUnaryArgNode(AotNode* arg, const TypeDef* resType) : AotNode(resType), arg(arg) {}

    AotNode* AotUnaryArgNode::optimize()
    {
        auto optArg = arg->optimize();
        if(optArg != arg.get())
            arg = std::unique_ptr<AotNode>(optArg);
        return this;
    }

    AotBinaryArgNode::AotBinaryArgNode(AotNode* argA, AotNode* argB, const TypeDef* resType)
        : AotNode(resType), argA(argA), argB(argB)
    {}

    AotNode* AotBinaryArgNode::optimize()
    {
        auto optArgA = argA->optimize();
        if(optArgA != argA.get())
            argA = std::unique_ptr<AotNode>(optArgA);
        auto optArgB = argB->optimize();
        if(optArgB != argB.get())
            argB = std::unique_ptr<AotNode>(optArgB);
        return this;
    }

    bool AotValue::isScalar() const
    {
        return ValueType::Scalar_Begin <= type->type() && type->type() <= ValueType::Scalar_End;
    }

    bool AotValue::isUnsigned() const
    {
        return ValueType::Unsigned_Begin <= type->type() && type->type() <= ValueType::Unsigned_End;
    }

    bool AotValue::isInt() const { return ValueType::Int_Begin <= type->type() && type->type() <= ValueType::Int_End; }

    bool AotValue::isFloat() const
    {
        return ValueType::Float_Begin <= type->type() && type->type() <= ValueType::Float_End;
    }
} // namespace BraneScript
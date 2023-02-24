//
// Created by wirewhiz on 2/20/23.
//

#include "aotLogicNodes.h"
#include "../compiler.h"
#include "aotModifierNodes.h"
#include "nativeTypes.h"
#include "operands.h"

namespace BraneScript
{
    AotCompareNode::AotCompareNode(Mode mode, AotNode* a, AotNode* b)
        : _mode(mode), AotBinaryArgNode(a, b, getNativeTypeDef(ValueType::Bool))
    {
        assert(argA->resType() == argB->resType());
    }

    AotValue* AotCompareNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        auto a = ctx.castValue(argA->generateBytecode(ctx));
        auto b = argB->generateBytecode(ctx);

        auto mode = _mode;
        if(mode == Less)
        {
            std::swap(a, b);
            mode = Greater;
        }
        else if(mode == LessEqual)
        {
            std::swap(a, b);
            mode = GreaterEqual;
        }

        a = ctx.castReg(a);

        AotValue* result = ctx.newCompareResult();
        bool sign = !a->isUnsigned();
        switch(mode)
        {
            case Equal:
            case NotEqual:
                result->compareType = (AotValue::CompareType)mode;
                break;
            case Greater:
                result->compareType = sign ? AotValue::GreaterRes : AotValue::AboveRes;
                break;
            case GreaterEqual:
                result->compareType = sign ? AotValue::GreaterEqualRes : AotValue::AboveEqualRes;
                break;
        }

        result->type = resType();

        ctx.appendCode(CMP, ctx.serialize(a), ctx.serialize(b));

        if(a->isTemp())
            ctx.releaseValue(a);
        if(b->isTemp())
            ctx.releaseValue(b);

        return result;
    }
} // namespace BraneScript
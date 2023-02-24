//
// Created by wirewhiz on 2/20/23.
//

#ifndef BRANESCRIPT_AOTLOGICNODES_H
#define BRANESCRIPT_AOTLOGICNODES_H

#include "aotNode.h"
namespace BraneScript
{
    class FunctionCompilerCtx;

    class AotCompareNode : public AotBinaryArgNode
    {
      public:
        enum Mode
        {
            Equal = AotValue::EqualRes,
            NotEqual = AotValue::NotEqualRes,
            Greater = AotValue::GreaterRes,
            GreaterEqual = AotValue::GreaterEqualRes,
            Less,
            LessEqual
        };
      private:
        Mode _mode;
      public:

        AotCompareNode(Mode mode, AotNode* a, AotNode* b);

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };
}

#endif // BRANESCRIPT_AOTLOGICNODES_H

//
// Created by wirewhiz on 2/23/23.
//

#include "aotNativeOperators.h"
#include "aotNodes/aotModifierNodes.h"

namespace BraneScript
{
    NativeCastOperator::NativeCastOperator(const BraneScript::TypeDef* currentType,
                                           const BraneScript::TypeDef* targetType)
        : AotInlineFunction("BraneScript::opr " + std::string(targetType->name()), targetType)
    {
        _currentType = currentType;
    }

    bool NativeCastOperator::argsMatch(const std::vector<AotNode*>& args) const
    {
        if(args.size() != 1)
            return false;
        return args[0]->resType() == _currentType;
    }

    AotNode* NativeCastOperator::generateAotTree(const std::vector<AotNode*>& args) const
    {
        return new AotCastNode(args[0], _resType);
    }
} // namespace BraneScript

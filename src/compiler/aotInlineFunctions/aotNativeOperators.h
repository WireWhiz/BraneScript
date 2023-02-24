//
// Created by wirewhiz on 2/23/23.
//

#ifndef BRANESCRIPT_AOTNATIVEOPERATORS_H
#define BRANESCRIPT_AOTNATIVEOPERATORS_H

#include "aotInlineFunction.h"
#include "nativeTypes.h"
#include <functional>
#include <tuple>

namespace BraneScript
{
    template<typename Node, typename... Args>
    class NativeBinaryOperator : public AotInlineFunction
    {
        std::tuple<Args...> _args;
        static constexpr size_t argIndex(size_t i)
        {
            return sizeof...(Args) - 2 + i;
        }
    public:
      NativeBinaryOperator(const char* symbol, const TypeDef* type, Args... args) : AotInlineFunction("BraneScript::opr " + std::string(symbol), type)
        {
            _args = std::make_tuple(args...);
        }

        bool argsMatch(const std::vector<AotNode*>& args) const override
        {
            if(args.size() != 2)
                return false;
            return args[0]->resType() == _resType && args[1]->resType() == _resType;
        }
        Node* generateAotTree(const std::vector<AotNode*>& args) const override
        {
            if constexpr(sizeof...(Args))
                return new Node(std::get<Args>(_args)..., args[0], args[1]);
            else
                return new Node(args[0], args[1]);
        }
    };

    class NativeCastOperator : public AotInlineFunction
    {
        const TypeDef* _currentType;
      public:
        NativeCastOperator(const TypeDef* currentType, const TypeDef* targetType);

        bool argsMatch(const std::vector<AotNode*>& args) const override;

        AotNode* generateAotTree(const std::vector<AotNode*>& args) const override;
    };
}


#endif // BRANESCRIPT_AOTNATIVEOPERATORS_H

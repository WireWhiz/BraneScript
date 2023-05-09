//
// Created by wirewhiz on 4/19/23.
//

#ifndef BRANESCRIPT_CONSTEXPREVALUATOR_H
#define BRANESCRIPT_CONSTEXPREVALUATOR_H

#include "documentContext.h"
#include "functionHandle.h"

namespace BraneScript
{
    class ConstexprFunction;

    class ConstexprEvaluator
    {
        Linker* _linker;

        static robin_hood::unordered_map<std::string, std::unique_ptr<ConstexprFunction>> _inlineFunctions;

      public:

        void addInlineFunction(ConstexprFunction* func);
        ConstexprFunction* getInlineFunction(const std::string& sig);

        ConstexprEvaluator();
        ConstValueContext* evaluateConstexpr(const ExpressionContext* expr);
    };

}


#endif // BRANESCRIPT_CONSTEXPREVALUATOR_H

//
// Created by wirewhiz on 4/19/23.
//

#ifndef BRANESCRIPT_CONSTEXPREVALUATOR_H
#define BRANESCRIPT_CONSTEXPREVALUATOR_H

#include "aotNodes/aotNode.h"
#include "aotNodes/aotValueNodes.h"
#include "compiler.h"
#include "documentContext.h"
#include "functionHandle.h"
#include "irFunction.h"

namespace BraneScript
{
    class ConstexprFunction;

    class ConstexprEvaluator
    {
        Linker* _linker;
        ScriptRuntime* _runtime;

        static robin_hood::unordered_map<std::string, std::unique_ptr<ConstexprFunction>> _inlineFunctions;

        bool isNativeFunction(const std::string& sig);
        AotConstNode* evaluateNativeFunction(const std::string& sig,
                                             const TypeDef* resType,
                                             std::vector<AotConstNode*>& args,
                                             ScriptCompilerCtx& scriptCtx);
      public:

        void addInlineFunction(ConstexprFunction* func);
        ConstexprFunction* getInlineFunction(const std::string& sig);

        ConstexprEvaluator();
        ConstValueContext* evaluateConstexpr(const ExpressionContext* expr);
    };

}


#endif // BRANESCRIPT_CONSTEXPREVALUATOR_H

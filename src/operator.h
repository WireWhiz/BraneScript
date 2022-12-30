//
// Created by eli on 12/29/2022.
//

#ifndef BRANESCRIPT_OPERATOR_H
#define BRANESCRIPT_OPERATOR_H

#include <string>
#include "aotNode/aotNode.h"

namespace BraneScript
{
    class CompilerCtx;
    class AotValue;
    class TypeDef;
    class AotConstNode;

    class Operator
    {
        std::string _symbol;
    public:
        explicit Operator(std::string symbol);
        /***
         * Generate operator bytecode
         * @param ctx compiler context
         * @param res value to store result in
         * @param arg1 first arg
         * @param arg2 second arg (leave as nullptr for unary operators)
         */
        virtual AotValue* generateBytecode(CompilerCtx& ctx, AotValue* arg1, AotValue* arg2) const = 0;
        const std::string& symbol();
        virtual const TypeDef* resType() const = 0;
    };

    class ConstexprOperator : public Operator
    {
    public:
        explicit ConstexprOperator(std::string symbol);
        virtual AotNode* precalculate(AotConstNode* arg1, AotConstNode* arg2) const = 0;
    };


    std::string oprSig(const std::string& opr, const TypeDef* arg);
    std::string oprSig(const std::string& opr, const TypeDef* arg1, const TypeDef* arg2);
}

#endif //BRANESCRIPT_OPERATOR_H

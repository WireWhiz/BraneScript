//
// Created by eli on 12/29/2022.
//

#include "operator.h"
#include "typeDef.h"
#include <cassert>

namespace BraneScript
{
    Operator::Operator(std::string symbol) : _symbol(std::move(symbol))
    {

    }

    const std::string& Operator::symbol()
    {
        return _symbol;
    }

    std::string oprSig(const std::string& opr, const TypeDef* arg)
    {
        return "opr " + opr + "(" + arg->name() + ")";
    }

    std::string oprSig(const std::string& opr, const TypeDef* arg1, const TypeDef* arg2)
    {
        return "opr " + opr + "(" + arg1->name() + ", " + arg2->name() + ")";
    }

    ConstexprOperator::ConstexprOperator(std::string symbol) : Operator(std::move(symbol))
    {

    }
}
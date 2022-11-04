//
// Created by eli on 10/19/2022.
//

#ifndef BRANESCRIPT_AOTVALUENODES_H
#define BRANESCRIPT_AOTVALUENODES_H

#include <any>
#include <string>
#include "aotNode.h"
namespace BraneScript
{
    class AotConst : public AotNode
    {
        std::any _value;
    public:
        AotConst(std::any value, TypeDef* resType);

        AotNode* optimize() override;

        AotValue generateBytecode(CompilerCtx& ctx) const override;

        const std::any& value() const;

        bool isNumber() const;

        bool isBool() const;

        AotConst* operator+(const AotConst&);

        AotConst* operator-(const AotConst&);

        AotConst* operator*(const AotConst&);

        AotConst* operator/(const AotConst&);

        AotNode* cast(TypeDef* type) const;
    };

    class AotValueNode : public AotNode
    {
        uint16_t _lValueIndex;
        bool _constant;
    public:
        AotValueNode(uint16_t lValueIndex, TypeDef* type, bool constant);

        AotNode* optimize() override;

        AotValue generateBytecode(CompilerCtx& ctx) const override;
    };

}


#endif //BRANESCRIPT_AOTVALUENODES_H

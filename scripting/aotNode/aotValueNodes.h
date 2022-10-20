//
// Created by eli on 10/19/2022.
//

#ifndef BRANESCRIPT_AOTVALUENODES_H
#define BRANESCRIPT_AOTVALUENODES_H

#include <any>
#include <string>
#include "aotNode.h"

class AotConst : public AotNode
{
    std::any _value;
public:
    AotConst(std::any value);
    AotNode* optimize() override;
    AotValue generateBytecode(CompilerCtx& ctx) const override;
    const std::any& value() const;
};

class AotValueNode : public AotNode
{
    uint16_t _lValueIndex;
    std::string _type;
    bool _constant;
public:
    AotValueNode(uint16_t lValueIndex, std::string type, bool constant);
    AotNode* optimize() override;
    AotValue generateBytecode(CompilerCtx& ctx) const override;
};



#endif //BRANESCRIPT_AOTVALUENODES_H

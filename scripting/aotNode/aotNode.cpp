//
// Created by wirewhiz on 17/10/22.
//

#include "aotNode.h"
#include "../scriptFunction.h"
#include "../typeDef.h"

AotNode::NodeType AotNode::type() const
{
    return _type;
}

AotNode::AotNode(TypeDef* resType, NodeType type) : _type(type), _resType(resType)
{

}

TypeDef* AotNode::resType() const
{
    return _resType;
}

TypeDef* AotNode::dominantArgType(TypeDef* a, TypeDef* b)
{
    if(a->type() == Float64)
        return a;
    if(b->type() == Float64)
        return b;
    if(a->type() == Float32)
        return a;
    if(b->type() == Float32)
        return b;
    if(a->type() == Int32)
        return a;
    if(b->type() == Int32)
        return b;
    return nullptr;
}
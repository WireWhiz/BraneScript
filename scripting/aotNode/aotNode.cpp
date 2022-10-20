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

AotNode::AotNode(AotNode::NodeType type) : _type(type)
{

}

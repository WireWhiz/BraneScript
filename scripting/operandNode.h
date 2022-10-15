//
// Created by wirewhiz on 13/10/22.
//

#ifndef BRANESCRIPT_OPERANDNODE_H
#define BRANESCRIPT_OPERANDNODE_H

#include "bytecode.h"
#include "typeDef.h"
#include <list>

class ScriptRuntime;
class OperationNode
{
public:
    virtual ~OperationNode() = default;
    virtual std::list<Codebyte> generateBytecode(ScriptRuntime& rt) = 0;
};




#endif //BRANESCRIPT_OPERANDNODE_H

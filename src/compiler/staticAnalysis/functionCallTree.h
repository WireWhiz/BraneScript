//
// Created by wirewhiz on 3/22/23.
//

#ifndef BRANESCRIPT_FUNCTIONCALLTREE_H
#define BRANESCRIPT_FUNCTIONCALLTREE_H

#include "robin_hood.h"

namespace BraneScript
{
    class FunctionContext;

    class FunctionCallTree
    {
        struct FunctionNode
        {
            FunctionContext* ctx;
            robin_hood::unordered_set<FunctionNode*> dependencies;
            bool visited = false;
            bool placed = false;
        };
        robin_hood::unordered_node_map<FunctionContext*, FunctionNode> nodes;

        bool visitNode(FunctionNode* node, std::vector<FunctionContext*>& result);
      public:
        void addFunction(FunctionContext* func);
        void addDependency(FunctionContext* func, FunctionContext* dep);
        bool resolveCallOrder(std::vector<FunctionContext*>& result);
    };
}



#endif // BRANESCRIPT_FUNCTIONCALLTREE_H

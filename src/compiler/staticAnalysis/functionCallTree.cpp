//
// Created by wirewhiz on 3/22/23.
//

#include <cassert>
#include "functionCallTree.h"

namespace BraneScript
{

    bool FunctionCallTree::visitNode(FunctionNode* node, std::vector<FunctionContext*>& result)
    {
        if(node->placed)
            return true;
        if(node->visited)
            return false;
        node->visited = true;
        for(FunctionNode* dep : node->dependencies)
            visitNode(dep, result);
        result.push_back(node->ctx);
        node->placed = true;
        node->visited = false;
        return true;
    }

    void FunctionCallTree::addFunction(FunctionContext* func)
    {
        nodes.insert({func, FunctionNode{func}});
    }

    void FunctionCallTree::addDependency(FunctionContext* func, FunctionContext* dep)
    {
        assert(func && dep);
        if(!nodes.contains(func))
            addFunction(func);
        if(!nodes.contains(dep))
            addFunction(dep);
        auto& node = nodes.at(func);
        auto& depNode = nodes.at(dep);
        if(!node.dependencies.contains(&depNode))
            node.dependencies.insert(&depNode);
    }

    bool FunctionCallTree::resolveCallOrder(std::vector<FunctionContext*>& result)
    {
        for(auto& node : nodes)
        {
            node.second.placed = false;
            node.second.visited = false;
        }
        if(nodes.empty())
            return true;
        for(auto& node : nodes)
        {
            if(node.second.placed)
                continue;
            if(!visitNode(&node.second, result))
                return false;
        }
        return true;
    }
}


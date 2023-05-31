//
// Created by wirewhiz on 3/22/23.
//

#include <cassert>
#include "functionCallTree.h"
#include "documentContext.h"

namespace BraneScript
{
    uint32_t indentDepth = 0;
    bool FunctionCallTree::visitNode(FunctionNode* node, std::vector<FunctionContext*>& result)
    {
        printf("%*sVisiting %s\n", indentDepth, "", node->ctx->identifier.text.c_str());
        if(node->placed)
            return true;
        if(node->visited)
            return false;
        node->visited = true;
        indentDepth += 2;
        for(FunctionNode* dep : node->dependencies)
            visitNode(dep, result);
        indentDepth -= 2;
        result.push_back(node->ctx);
        printf("%*s%s placed\n", indentDepth, "", node->ctx->identifier.text.c_str());
        node->placed = true;
        node->visited = false;
        return true;
    }

    void FunctionCallTree::addFunction(FunctionContext* func)
    {
        if(!nodes.contains(func))
            nodes.insert({func, FunctionNode{func}});
    }

    void FunctionCallTree::addDependency(FunctionContext* func, FunctionContext* dep)
    {
        assert(func && dep);
        if(func == dep)
            return;
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
        printf("Resolving call order\n");
        result.clear();
        result.reserve(nodes.size());
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
        printf("Call order resolved\n\n");
        return true;
    }

    void FunctionCallTree::clear()
    {
        nodes.clear();
    }
}


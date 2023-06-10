#ifndef BRANESCRIPT_DEPENDANCYGRAPH_H
#define BRANESCRIPT_DEPENDANCYGRAPH_H

#include <list>
#include "Resource.h"
#include <robin_hood.h>

template<typename Key, typename T>
class DependencyGraph
{
    struct Node
    {
        Key key;
        Resource<T> value;
        bool visited = false;
        bool placed = false;
        robin_hood::unordered_set<Node*> dependencies;
        robin_hood::unordered_set<Node*> dependants;
        Node(Key key, std::unique_ptr<T> value) : key(std::move(key)), value(std::move(value)) {}
    };

    robin_hood::unordered_node_map<Key, Node> nodes;

    void sortNodes(Node* node, std::list<Node*>& result)
    {
        if(node->placed)
            return;
        if(node->visited)
            throw std::runtime_error("Can't sort graph with circular dependencies!");
        node->visited = true;
        for(auto& dep : node->dependencies)
            sortNodes(dep, result);
        node->visited = false;
        result.push_back(node);
        node->placed = true;
    }

  public:
    ~DependencyGraph() { clear(); }

    void insert(Key k, T value)
    {
        assert(!nodes.contains(k));
        nodes.insert({k, Node(k, std::make_unique<T>(std::move(value)))});
    }
    void insert(Key k, T* value)
    {
        assert(!nodes.contains(k));
        nodes.insert({k, Node(k, std::unique_ptr<T>(value))});
    }

    void addDependency(Key k, Key dep)
    {
        assert(nodes.contains(k));
        assert(nodes.contains(dep));
        auto it = nodes.find(k);
        auto it2 = nodes.find(dep);
        it->second.dependencies.insert(&it2->second);
        it2->second.dependants.insert(&it->second);
    }

    void removeDependency(Key k, Key dep)
    {
        assert(nodes.contains(k));
        assert(nodes.contains(dep));
        auto it = nodes.find(k);
        auto it2 = nodes.find(dep);
        it->second.dependencies.erase(&it2->second);
        it2->second.dependants.erase(&it->second);
    }

    void erase(Key k, bool eraseUnusedDependencies = false)
    {
        if(!nodes.contains(k))
            return;
        auto it = nodes.find(k);
        if(it->second.visited)
            throw std::runtime_error("Attempted to erase resource with circular dependency!");
        if(it->second.dependants.size() > 0)
            throw std::runtime_error("Attempted to erase resource with dependents!");
        it->second.visited = true;
        if(eraseUnusedDependencies)
        {
            std::vector<Node*> dependencies;
            dependencies.reserve(it->second.dependencies.size());
            for(auto& dep : it->second.dependencies)
                dependencies.push_back(dep);
            for(auto& dep : dependencies)
            {
                if(!dep->value.isUsed() && dep->dependants.size() == 1)
                    erase(dep->key);
            }
        }
        // Remove this node from all remaining dependencies
        for(auto& dep : it->second.dependencies)
            dep->dependants.erase(&it->second);
        nodes.erase(it);
    }

    bool contains(Key k) const { return nodes.contains(k); }

    ResourceHandle<T> at(Key k)
    {
        assert(nodes.contains(k));
        return {nodes.at(k).value};
    }

    std::list<Node*> asSortedList()
    {
        std::list<Node*> result;
        for(auto& node : nodes)
        {
            node.second.placed = false;
            node.second.visited = false;
        }
        for(auto& node : nodes)
            sortNodes(&node.second, result);
        return result;
    }

    void clear()
    {
        std::list<Node*> deleteOrder = asSortedList();
        for(auto& node : deleteOrder)
            nodes.erase(node->key);
    }
};

#endif // BRANESCRIPT_DEPENDANCYGRAPH_H

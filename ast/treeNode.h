//
// Created by wirewhiz on 13/10/22.
//

#ifndef BRANESCRIPT_TREENODE_H
#define BRANESCRIPT_TREENODE_H

class NodeValue
{
    virtual void toString() = 0;
};

class TreeNode
{
public:
    virtual ~TreeNode() = default;
};


#endif //BRANESCRIPT_TREENODE_H

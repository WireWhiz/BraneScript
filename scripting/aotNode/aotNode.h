//
// Created by wirewhiz on 17/10/22.
//

#ifndef BRANESCRIPT_AOTNODE_H
#define BRANESCRIPT_AOTNODE_H

#include <cstdint>
#include <type_traits>

class IRScript;
class AotNode
{
protected:
    enum NodeType
    {
        Const,
        Return,
        ReturnValue,
        Move,
        Add,
        Sub,
        Mul,
        Div
    };
public:
    virtual ~AotNode() =default;
    virtual AotNode* optimize() = 0;
    virtual void generateBytecode(IRScript* script) const = 0;
    template<class T>
    T* as()
    {
        static_assert(std::is_base_of<AotNode, T>());
        return dynamic_cast<T*>(this);
    }
};


#endif //BRANESCRIPT_AOTNODE_H

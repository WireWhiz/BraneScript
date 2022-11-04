//
// Created by wirewhiz on 17/10/22.
//

#ifndef BRANESCRIPT_AOTNODE_H
#define BRANESCRIPT_AOTNODE_H

#include <cstdint>
#include <type_traits>
#include "../valueIndex.h"
namespace BraneScript
{
    class TypeDef;

    struct AotValue
    {
        enum : uint8_t
        {
            Const = 1,
            Constexpr = 1 << 1,
            Temp = 1 << 2
        };
        uint8_t flags = 0;
        ValueIndex valueIndex = {};
        TypeDef* def = nullptr;

        inline bool isVoid() const
        { return def == nullptr; };
    };

    class CompilerCtx;

    class AotNode
    {
    protected:
        enum NodeType
        {
            Const,
            Value,
            Cast,
            Compare,
            Return,
            ReturnValue,
            Scope,
            If,
            While,
            Assign,
            Add,
            Sub,
            Mul,
            Div
        };
        NodeType _type;
        TypeDef* _resType = nullptr;

        static TypeDef* dominantArgType(TypeDef* a, TypeDef* b);

    public:
        explicit AotNode(TypeDef* resType, NodeType type);

        virtual ~AotNode() = default;

        virtual AotNode* optimize() = 0;

        virtual AotValue generateBytecode(CompilerCtx& ctx) const = 0;

        template<class T>
        T* as()
        {
            static_assert(std::is_base_of<AotNode, T>());
            return dynamic_cast<T*>(this);
        }

        NodeType type() const;

        TypeDef* resType() const;
    };

}
#endif //BRANESCRIPT_AOTNODE_H

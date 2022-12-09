//
// Created by eli on 10/19/2022.
//

#ifndef BRANESCRIPT_AOTVALUENODES_H
#define BRANESCRIPT_AOTVALUENODES_H

#include <any>
#include <string>
#include <memory>

#include "aotNode.h"
#include "../typeInfo.h"
namespace BraneScript
{
    class AotConst : public AotNode
    {
        std::any _value;
    public:
        AotConst(std::any value, TypeDef* resType);

        AotNode* optimize() override;

        AotValue* generateBytecode(CompilerCtx& ctx) const override;

        const std::any& value() const;

        bool isNumber() const;

        bool isBool() const;

        AotConst* operator+(const AotConst&);

        AotConst* operator-(const AotConst&);

        AotConst* operator*(const AotConst&);

        AotConst* operator/(const AotConst&);

        AotNode* cast(TypeDef* type) const;
    };

    class AotValueNode : public AotNode
    {
        struct ValueContext {
            TypeInfo info;
            AotValue* value = nullptr;
        };
        std::shared_ptr<ValueContext> _ctx;
    public:
        AotValueNode(TypeDef* type, TypeInfo info);
        AotValueNode(TypeDef* type, AotValue* value, TypeInfo info);
        AotValueNode(const AotValueNode&);

        AotNode* optimize() override;

        AotValue* generateBytecode(CompilerCtx& ctx) const override;
    };

    class AotDerefNode : public AotNode
    {
        std::unique_ptr<AotNode> _value;
        uint32_t _offset;

    public:
        AotDerefNode(AotNode* value, TypeDef* type, uint32_t offset);

        AotNode* optimize() override;

        AotValue* generateBytecode(CompilerCtx& ctx) const override;
    };

    class StructDef;
    class AotNewNode : public AotNode
    {
    public:
        AotNewNode(StructDef* structType);

        AotNode* optimize() override;

        AotValue* generateBytecode(CompilerCtx& ctx) const override;
    };

    class AotDeleteNode : public AotNode
    {
        std::unique_ptr<AotNode> _ptr;
    public:
        AotDeleteNode(AotNode* ptr);

        AotNode* optimize() override;

        AotValue* generateBytecode(CompilerCtx& ctx) const override;
    };

}


#endif //BRANESCRIPT_AOTVALUENODES_H
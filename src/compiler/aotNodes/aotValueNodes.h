//
// Created by eli on 10/19/2022.
//

#ifndef BRANESCRIPT_AOTVALUENODES_H
#define BRANESCRIPT_AOTVALUENODES_H

#include <any>
#include <memory>
#include <string>

#include "aotNode.h"
#include "typeInfo.h"
#include "typeDef.h"

namespace BraneScript
{
    class AotConstNode : public AotNode
    {
      public:
        union
        {
            bool asBool;
            char asChar;
            uint32_t asUInt;
            int32_t asInt;
            uint64_t asUInt64;
            int64_t asInt64;
            float asFloat32;
            double asFloat64;
        };

        std::string asString;
        AotConstNode(bool value);
        AotConstNode(char value);
        AotConstNode(uint32_t value);
        AotConstNode(int32_t value);
        AotConstNode(uint64_t value);
        AotConstNode(int64_t value);
        AotConstNode(float value);
        AotConstNode(double value);
        AotConstNode(std::string value);

        AotNode* optimize() override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
        ValueType type() const;

        template<typename T>
        AotConstNode* cast()
        {
            switch(_resType->type())
            {
                case ValueType::Void:
                case ValueType::Struct:
                    throw std::runtime_error("Invalid compile time cast attempted!");
                case ValueType::Bool:
                    return new AotConstNode(static_cast<T>(asBool));
                case ValueType::Char:
                    return new AotConstNode(static_cast<T>(asChar));
                case ValueType::UInt32:
                    return new AotConstNode(static_cast<T>(asUInt));
                case ValueType::UInt64:
                    return new AotConstNode(static_cast<T>(asUInt64));
                case ValueType::Int32:
                    return new AotConstNode(static_cast<T>(asInt));
                case ValueType::Int64:
                    return new AotConstNode(static_cast<T>(asInt64));
                case ValueType::Float32:
                    return new AotConstNode(static_cast<T>(asFloat32));
                case ValueType::Float64:
                    return new AotConstNode(static_cast<T>(asFloat64));
            }
        }
    };

    class AotAllocNode : public AotNode
    {
        AotValue* _value;
      public:
        AotAllocNode(AotValue* value);

        AotNode* optimize() override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotMallocNode : public AotNode
    {
        AotValue* _value;
      public:
        AotMallocNode(AotValue* value);

        AotNode* optimize() override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotValueConstruction : public AotNode
    {
        AotValue* _value = nullptr;
      public:
        AotValueConstruction(AotValue* value);

        AotNode* optimize() override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotValueDestruction : public AotNode
    {
        AotValue* _value;
      public:
        AotValueDestruction(AotValue* value);

        AotNode* optimize() override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotValueReference : public AotNode
    {
        AotValue* _value = nullptr;
      public:
        AotValueReference(AotValue* value);

        AotNode* optimize() override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotDerefNode : public AotNode
    {
        std::unique_ptr<AotNode> _value;
        uint32_t _offset;

      public:
        AotDerefNode(AotNode* value, const TypeDef* type, uint32_t offset);

        AotNode* optimize() override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class StructDef;

    class AotNewNode : public AotNode
    {
      public:
        AotNewNode(StructDef* structType);

        AotNode* optimize() override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };

    class AotDeleteNode : public AotNode
    {
        std::unique_ptr<AotNode> _ptr;

      public:
        AotDeleteNode(AotNode* ptr);

        AotNode* optimize() override;

        AotValue* generateBytecode(FunctionCompilerCtx& ctx) const override;
    };
} // namespace BraneScript

#endif // BRANESCRIPT_AOTVALUENODES_H

//
// Created by eli on 10/19/2022.
//

#include "aotValueNodes.h"
#include "../compiler.h"
#include "nativeTypes.h"
#include "typeDef.h"

namespace BraneScript
{
    AotNode* AotConstNode::optimize(FunctionCompilerCtx& ctx) { return this; }

    AotValue* AotConstNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        auto value = ctx.newConst(_resType, AotValue::Const | AotValue::ExternalRef | AotValue::Constexpr);

        value->flags |= AotValue::Initialized;
        switch(_resType->type())
        {
            case ValueType::Bool:
                ctx.appendCode(LOADC, ctx.serialize(value), asBool);
                break;
            case ValueType::Char:
                ctx.appendCode(LOADC, ctx.serialize(value), asChar);
                break;
            case ValueType::UInt32:
                ctx.appendCode(LOADC, ctx.serialize(value), asUInt);
                break;
            case ValueType::UInt64:
                ctx.appendCode(LOADC, ctx.serialize(value), asUInt64);
                break;
            case ValueType::Int32:
                ctx.appendCode(LOADC, ctx.serialize(value), asInt);
                break;
            case ValueType::Int64:
                ctx.appendCode(LOADC, ctx.serialize(value), asInt64);
                break;
            case ValueType::Float32:
                ctx.appendCode(LOADC, ctx.serialize(value), asFloat32);
                break;
            case ValueType::Float64:
                ctx.appendCode(LOADC, ctx.serialize(value), asFloat64);
                break;
            case ValueType::Struct:
                if(std::string_view(_resType->name()) != "BraneScript::string")
                    throw std::runtime_error("Unknown type");
                ctx.appendCode(LOADS, ctx.serialize(value),(uint32_t)asString.size());
                for(char c : asString)
                    ctx.appendCode(c);
                break;
        }
        return value;
    }

    ValueType AotConstNode::type() const { return _resType->type(); }

    AotConstNode::AotConstNode(bool value) : AotNode(getNativeTypeDef(ValueType::Bool)) { asBool = value; }

    AotConstNode::AotConstNode(char value) : AotNode(getNativeTypeDef(ValueType::Char)) { asChar = value; }

    AotConstNode::AotConstNode(uint32_t value) : AotNode(getNativeTypeDef(ValueType::UInt32)) { asInt = value; }

    AotConstNode::AotConstNode(int32_t value) : AotNode(getNativeTypeDef(ValueType::Int32)) { asInt = value; }

    AotConstNode::AotConstNode(uint64_t value) : AotNode(getNativeTypeDef(ValueType::UInt64)) { asUInt64 = value; }

    AotConstNode::AotConstNode(int64_t value) : AotNode(getNativeTypeDef(ValueType::Int64)) { asInt64 = value; }

    AotConstNode::AotConstNode(float value) : AotNode(getNativeTypeDef(ValueType::Float32)) { asFloat32 = value; }

    AotConstNode::AotConstNode(double value) : AotNode(getNativeTypeDef(ValueType::Float64)) { asFloat64 = value; }

    AotConstNode::AotConstNode(std::string value) : AotNode(getNativeTypes()[8]) { asString = std::move(value); }

    AotValueReference::AotValueReference(AotValue* value) : AotNode(value->type) { _value = value; }

    AotNode* AotValueReference::optimize(FunctionCompilerCtx& ctx)
    {
        // TODO if is const expression just return const node
        return this;
    }

    AotValue* AotValueReference::generateBytecode(FunctionCompilerCtx& ctx) const { return _value; }

    AotDerefNode::AotDerefNode(AotNode* value, const TypeDef* type, uint32_t offset) : AotNode(type), _value(value)
    {
        _offset = offset;
    }

    AotNode* AotDerefNode::optimize(FunctionCompilerCtx& ctx)
    {
        auto optArg = _value->optimize(ctx);
        if(optArg != _value.get())
            _value = std::unique_ptr<AotNode>(optArg);
        return this;
    }

    AotValue* AotDerefNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        AotValue* ptr = ctx.castReg(_value->generateBytecode(ctx));
        return ctx.derefPtr(ptr, _resType, _offset);
    }

    AotNewNode::AotNewNode(StructDef* structType) : AotNode((TypeDef*)structType) {}

    AotNode* AotNewNode::optimize(FunctionCompilerCtx& ctx) { return this; }

    AotValue* AotNewNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        auto ptr = ctx.newReg(_resType, 0);
        ctx.appendCode(Operand::ALLOC, ctx.serialize(ptr), _resType->size());
        return ptr;
    }

    AotDeleteNode::AotDeleteNode(AotNode* ptr) : AotNode(nullptr), _ptr(ptr) {}

    AotNode* AotDeleteNode::optimize(FunctionCompilerCtx& ctx) { return this; }

    AotValue* AotDeleteNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        auto ptr = _ptr->generateBytecode(ctx);
        assert(ptr->storageType == ValueStorageType_Ptr);
        ctx.appendCode(Operand::FREE, ctx.serialize(ptr));
        ctx.appendCode(Operand::MOVI, ctx.serialize(ptr), (int32_t)0);
        return {};
    }

    AotValueConstruction::AotValueConstruction(AotValue* value) : AotNode(value->type), _value(value) { assert(value); }

    AotNode* AotValueConstruction::optimize(FunctionCompilerCtx& ctx) { return this; }

    AotValue* AotValueConstruction::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        switch(_value->type->type())
        {
            case ValueType::Void:
                throw std::runtime_error("can not construct void type!");
            case ValueType::Bool:
            case ValueType::Char:
                ctx.appendCode(Operand::MOVI, ctx.serialize(_value), (int8_t)0);
                break;
            case ValueType::UInt32:
            case ValueType::Int32:
                ctx.appendCode(Operand::MOVI, ctx.serialize(_value), (int32_t)0);
                break;
            case ValueType::UInt64:
            case ValueType::Int64:
                ctx.appendCode(Operand::MOVI, ctx.serialize(_value), (int64_t)0);
                break;
            case ValueType::Float32:
                ctx.appendCode(Operand::MOVI, ctx.serialize(_value), (float)0);
                break;
            case ValueType::Float64:
                ctx.appendCode(Operand::MOVI, ctx.serialize(_value), (double)0);
                break;
            case ValueType::Struct:
            {
                auto* s = dynamic_cast<const StructDef*>(_value->type);
                auto* v = ctx.castReg(_value);
                ctx.appendCode(Operand::CALL, ctx.script.linkConstructor(s));
                ctx.appendCode(ctx.serialize(v));
                if(v->isTemp() && v != _value)
                    ctx.releaseValue(v);
            }
            break;
        }
        return _value;
    }

    AotValueDestruction::AotValueDestruction(AotValue* value) : AotNode(nullptr) { _value = value; }

    AotNode* AotValueDestruction::optimize(FunctionCompilerCtx& ctx)
    {
        if(_value && _value->type->type() != ValueType::Struct)
            return nullptr;
        return this;
    }

    AotValue* AotValueDestruction::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        if(auto s = dynamic_cast<const StructDef*>(_value->type))
        {
            auto* v = ctx.castReg(_value);
            ctx.appendCode(Operand::CALL, ctx.script.linkDestructor(s));
            ctx.appendCode(ctx.serialize(v ));
            if(v ->isHeapRef())
                ctx.appendCode(Operand::FREE, ctx.serialize(v ));
            if(v->isTemp())
                ctx.releaseValue(v);
        }
        if(_value->isTemp())
            ctx.releaseValue(_value);
        return nullptr;
    }

    AotAllocNode::AotAllocNode(AotValue* value) : AotNode(value->type), _value(value) {}

    AotNode* AotAllocNode::optimize(FunctionCompilerCtx& ctx) { return this; }

    AotValue* AotAllocNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        ctx.appendCode(Operand::ALLOC, ctx.serialize(_value), (uint16_t)_resType->size());
        if(auto s = dynamic_cast<const StructDef*>(_value->type))
        {
            ctx.appendCode(Operand::CALL, ctx.script.linkConstructor(s));
            ctx.appendCode(ctx.serialize(_value));
            _value->flags |= AotValue::StackRef;
        }
        return _value;
    }

    AotMallocNode::AotMallocNode(AotValue* value) : AotNode(value->type), _value(value) {}

    AotNode* AotMallocNode::optimize(FunctionCompilerCtx& ctx) { return this; }

    AotValue* AotMallocNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        ctx.appendCode(Operand::MALLOC, ctx.serialize(_value), (uint16_t)_resType->size());
        if(auto s = dynamic_cast<const StructDef*>(_value->type))
        {
            ctx.appendCode(Operand::CALL, ctx.script.linkConstructor(s));
            ctx.appendCode(ctx.serialize(_value));
            _value->flags |= AotValue::HeapRef;
        }
        return _value;
    }
} // namespace BraneScript
//
// Created by eli on 10/19/2022.
//

#include "aotValueNodes.h"
#include "../compiler.h"
#include "../typeDef.h"

namespace BraneScript
{
    AotConstNode::AotConstNode(std::any value, const TypeDef* resType) : AotNode(resType, NodeType::Const), _value(std::move(value))
    {
    }

    AotNode* AotConstNode::optimize()
    {
        return this;
    }

    AotValue* AotConstNode::generateBytecode(CompilerCtx& ctx) const
    {
        auto value = (_resType->name() == std::string_view("string")) ? ctx.newReg(_resType, AotValue::ExternalRef | AotValue::Initialized | AotValue::Temp) : ctx.newConst(_resType->type());
        switch (_resType->type())
        {
            case Bool:
                ctx.function->appendCode(LOADC, value->value(ctx), (uint8_t)std::any_cast<bool>(_value));
                break;
            case Char:
                ctx.function->appendCode(LOADC, value->value(ctx), (uint8_t)std::any_cast<char>(_value));
                break;
            case UInt32:
                ctx.function->appendCode(LOADC, value->value(ctx), std::any_cast<uint32_t>(_value));
                break;
            case UInt64:
                ctx.function->appendCode(LOADC, value->value(ctx), std::any_cast<uint64_t>(_value));
                break;
            case Int32:
                ctx.function->appendCode(LOADC, value->value(ctx), std::any_cast<int32_t>(_value));
                break;
            case Int64:
                ctx.function->appendCode(LOADC, value->value(ctx), std::any_cast<int64_t>(_value));
                break;
            case Float32:
                ctx.function->appendCode(LOADC, value->value(ctx), std::any_cast<float>(_value));
                break;
            case Float64:
                ctx.function->appendCode(LOADC, value->value(ctx), std::any_cast<double>(_value));
                break;
            case Struct:
                if(std::string_view(_resType->name()) != "string")
                    throw std::runtime_error("Unknown type");
                auto str = std::any_cast<std::string>(_value);
                ctx.function->appendCode(LOADS, value->value(ctx), (uint32_t)str.size());
                for(char c : str)
                    ctx.function->appendCode(c);
                break;
        }
        value->flags |= AotValue::Initialized;
        return value;
    }

    const std::any& AotConstNode::value() const
    {
        return _value;
    }

    bool AotConstNode::isNumber() const
    {
        if (_value.type() == typeid(int32_t))
            return true;
        if (_value.type() == typeid(int64_t))
            return true;
        if (_value.type() == typeid(float))
            return true;
        if (_value.type() == typeid(double))
            return true;
        return false;
    }

    bool AotConstNode::isBool() const
    {
        return _value.type() == typeid(bool);
    }

#define CONST_OP(operator, t1, t2, rt, other) \
    if(_value.type() == typeid(t1) && other._value.type() == typeid(t2)) \
        return new AotConstNode((rt)(std::any_cast<t1>(_value) operator std::any_cast<t2>(other._value)), dominantArgType(_resType, other._resType)); \
    if(_value.type() == typeid(t2) && other._value.type() == typeid(t1)) \
        return new AotConstNode((rt)(std::any_cast<t2>(_value) operator std::any_cast<t1>(other._value)), dominantArgType(_resType, other._resType));

    AotConstNode* AotConstNode::operator+(const AotConstNode& o)
    {
        CONST_OP(+, int32_t, int32_t, int32_t, o);
        CONST_OP(+, int32_t, float, float, o);
        CONST_OP(+, float, float, float, o);
        CONST_OP(+, double, double, double, o);
        assert(false);
        return nullptr;
    }

    AotConstNode* AotConstNode::operator-(const AotConstNode& o)
    {
        CONST_OP(-, int32_t, int32_t, int32_t, o);
        CONST_OP(-, int32_t, float, float, o);
        CONST_OP(-, float, float, float, o);
        CONST_OP(-, double, double, double, o);
        assert(false);
        return nullptr;
    }

    AotConstNode* AotConstNode::operator*(const AotConstNode& o)
    {
        CONST_OP(*, int32_t, int32_t, int32_t, o);
        CONST_OP(*, int32_t, float, float, o);
        CONST_OP(*, float, float, float, o);
        CONST_OP(*, double, double, double, o);
        assert(false);
        return nullptr;
    }

    AotConstNode* AotConstNode::operator/(const AotConstNode& o)
    {
        CONST_OP(/, int32_t, int32_t, int32_t, o);
        CONST_OP(/, int32_t, float, float, o);
        CONST_OP(/, float, float, float, o);
        CONST_OP(/, double, double, double, o);
        assert(false);
        return nullptr;
    }

    AotNode* AotConstNode::cast(const TypeDef* type) const
    {
        if (type == _resType)
            return new AotConstNode(_value, _resType);
        switch (_resType->type())
        {
            case Int32:
            {
                auto value = std::any_cast<int32_t>(_value);
                switch (type->type())
                {
                    case Float32:
                        return new AotConstNode((float)(value), type);
                }
                break;
            }
            case Float32:
            {
                auto value = std::any_cast<float>(_value);
                switch (type->type())
                {
                    case Int32:
                        return new AotConstNode((int32_t)value, type);
                }
            }
        }

        assert(false);
        return nullptr;
    }

    AotValueNode::AotValueNode(const TypeDef* type, TypeInfo info) : AotNode(type, NodeType::Value)
    {
        _ctx = std::shared_ptr<ValueContext>(new ValueContext{std::move(info)});
    }

    AotValueNode::AotValueNode(const TypeDef* type, AotValue* value, TypeInfo info) : AotNode(type, NodeType::Value)
    {
        _ctx = std::shared_ptr<ValueContext>(new ValueContext{std::move(info), value});
    }

    AotValueNode::AotValueNode(const AotValueNode& o) : _ctx(o._ctx), AotNode(*this)
    {
        _type = o._type;
        _resType = o._resType;
    }

    AotNode* AotValueNode::optimize()
    {
        //TODO if is const expression just return const node
        return this;
    }

    AotValue* AotValueNode::generateBytecode(CompilerCtx& ctx) const
    {
        if (_ctx->value)
            return _ctx->value;

        uint8_t flags = 0;
        if(_ctx->info.isConst)
            flags |= AotValue::Const;
        if(_ctx->info.isRef|| _resType->type() == ValueType::Struct)
        {
            if(_ctx->info.stackRef)
                flags |= AotValue::StackRef;
            else
                flags |= AotValue::HeapRef;
        }
        _ctx->value = ctx.newReg(_resType, flags);
        if(!_ctx->info.isRef && _resType->type() != ValueType::Struct)
            return _ctx->value;

        if(!_ctx->info.stackRef)
        {
            ctx.function->appendCode(Operand::MOVI, _ctx->value->value(ctx), (uint32_t)0);
        }
        else
        {
            auto s = dynamic_cast<const StructDef*>(_resType);

            int16_t sIndex = 0;
            int16_t cIndex;
            if(ctx.localStructIndices.count(s))
            {
                sIndex = ctx.localStructIndices.at(s);
                cIndex = ctx.script->findLocalFuncIndex(std::string(s->name()) + "::_construct()");
            }
            else
            {
                sIndex = int16_t{-1} -ctx.script->linkStruct(s->name());
                cIndex = int16_t{-1} -  ctx.script->linkFunction(std::string(s->name()) + "::_construct()");
            }
            ctx.function->appendCode(Operand::ALLOC, _ctx->value->value(ctx), sIndex);
            _ctx->value->flags |= AotValue::Initialized;

            //Call constructor
            ctx.function->appendCode(Operand::CALL, cIndex);
            ctx.function->appendCode(_ctx->value->value(ctx));
        }


        return _ctx->value;
    }

    AotDerefNode::AotDerefNode(AotNode* value, const TypeDef* type, uint32_t offset) : AotNode(type, NodeType::Deref), _value(value)
    {
        _offset = offset;
    }

    AotNode* AotDerefNode::optimize()
    {
        auto optArg = _value->optimize();
        if (optArg != _value.get())
            _value = std::unique_ptr<AotNode>(optArg);
        return this;
    }

    AotValue* AotDerefNode::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue* ptr = _value->generateBytecode(ctx);
        return ctx.derefPtr(ptr, _resType, _offset);
    }

    AotNewNode::AotNewNode(StructDef* structType) : AotNode((TypeDef*)structType, NodeType::New)
    {

    }

    AotNode* AotNewNode::optimize()
    {
        return this;
    }

    AotValue* AotNewNode::generateBytecode(CompilerCtx& ctx) const
    {
        auto ptr = ctx.newReg(_resType, 0);
        ctx.function->appendCode(Operand::ALLOC, ptr->value(ctx), _resType->size());
        return ptr;
    }

    AotDeleteNode::AotDeleteNode(AotNode* ptr) : AotNode(nullptr, NodeType::Free), _ptr(ptr)
    {
    }

    AotNode* AotDeleteNode::optimize()
    {
        return this;
    }

    AotValue* AotDeleteNode::generateBytecode(CompilerCtx& ctx) const
    {
        auto ptr = _ptr->generateBytecode(ctx);
        assert(ptr->storageType == ValueStorageType_Ptr);
        ctx.function->appendCode(Operand::FREE, ptr->value(ctx));
        ctx.function->appendCode(Operand::MOVI, ptr->value(ctx), (int32_t)0);
        return {};
    }

    AotLibraryNode::AotLibraryNode(Library* lib) : AotNode(nullptr, NodeType::Lib)
    {
        _lib = lib;
    }

    Library* AotLibraryNode::lib() const
    {
        return _lib;
    }

    AotNode* AotLibraryNode::optimize()
    {
        assert(false);
        return this;
    }

    AotValue* AotLibraryNode::generateBytecode(CompilerCtx& ctx) const
    {
        assert(false);
        return nullptr;
    }

    AotFunctionNode::AotFunctionNode(int16_t index) : AotNode(nullptr, NodeType::Func)
    {
        _index = index;
    }

    AotNode* AotFunctionNode::optimize()
    {
        assert(false);
        return this;
    }

    AotValue* AotFunctionNode::generateBytecode(CompilerCtx& ctx) const
    {
        assert(false);
        return nullptr;
    }
}
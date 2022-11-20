//
// Created by eli on 10/19/2022.
//

#include "aotValueNodes.h"
#include "../compiler.h"
#include "../typeDef.h"

namespace BraneScript
{
    AotConst::AotConst(std::any value, TypeDef* resType) : AotNode(resType, Const), _value(std::move(value))
    {
    }

    AotNode* AotConst::optimize()
    {
        return this;
    }

    AotValue AotConst::generateBytecode(CompilerCtx& ctx) const
    {
        auto value = ctx.newConst(_resType->type());
        switch (_resType->type())
        {
            case Bool:
                ctx.function->appendCode(LOADC, value.valueIndex, (uint8_t)std::any_cast<bool>(_value));
                break;
            case Int32:
                ctx.function->appendCode(LOADC, value.valueIndex, std::any_cast<int32_t>(_value));
                break;
            case Int64:
                ctx.function->appendCode(LOADC, value.valueIndex, std::any_cast<int64_t>(_value));
                break;
            case Float32:
                ctx.function->appendCode(LOADC, value.valueIndex, std::any_cast<float>(_value));
                break;
            case Float64:
                ctx.function->appendCode(LOADC, value.valueIndex, std::any_cast<double>(_value));
                break;
            case ObjectRef:
                assert(false);
                break;
        }
        return value;
    }

    const std::any& AotConst::value() const
    {
        return _value;
    }

    bool AotConst::isNumber() const
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

    bool AotConst::isBool() const
    {
        return _value.type() == typeid(bool);
    }

#define CONST_OP(operator, t1, t2, rt, other) \
    if(_value.type() == typeid(t1) && other._value.type() == typeid(t2)) \
        return new AotConst((rt)(std::any_cast<t1>(_value) operator std::any_cast<t2>(other._value)), dominantArgType(_resType, other._resType)); \
    if(_value.type() == typeid(t2) && other._value.type() == typeid(t1)) \
        return new AotConst((rt)(std::any_cast<t2>(_value) operator std::any_cast<t1>(other._value)), dominantArgType(_resType, other._resType));

    AotConst* AotConst::operator+(const AotConst& o)
    {
        CONST_OP(+, int32_t, int32_t, int32_t, o);
        CONST_OP(+, int32_t, float, float, o);
        CONST_OP(+, float, float, float, o);
        CONST_OP(+, double, double, double, o);
        assert(false);
        return nullptr;
    }

    AotConst* AotConst::operator-(const AotConst& o)
    {
        CONST_OP(-, int32_t, int32_t, int32_t, o);
        CONST_OP(-, int32_t, float, float, o);
        CONST_OP(-, float, float, float, o);
        CONST_OP(-, double, double, double, o);
        assert(false);
        return nullptr;
    }

    AotConst* AotConst::operator*(const AotConst& o)
    {
        CONST_OP(*, int32_t, int32_t, int32_t, o);
        CONST_OP(*, int32_t, float, float, o);
        CONST_OP(*, float, float, float, o);
        CONST_OP(*, double, double, double, o);
        assert(false);
        return nullptr;
    }

    AotConst* AotConst::operator/(const AotConst& o)
    {
        CONST_OP(/, int32_t, int32_t, int32_t, o);
        CONST_OP(/, int32_t, float, float, o);
        CONST_OP(/, float, float, float, o);
        CONST_OP(/, double, double, double, o);
        assert(false);
        return nullptr;
    }

    AotNode* AotConst::cast(TypeDef* type) const
    {
        if (type == _resType)
            return new AotConst(_value, _resType);
        switch (_resType->type())
        {
            case Int32:
            {
                auto value = std::any_cast<int32_t>(_value);
                switch (type->type())
                {
                    case Float32:
                        return new AotConst((float)(value), type);
                }
                break;
            }
            case Float32:
            {
                auto value = std::any_cast<float>(_value);
                switch (type->type())
                {
                    case Int32:
                        return new AotConst((int32_t)value, type);
                }
            }
        }

        assert(false);
        return nullptr;
    }

    AotValueNode::AotValueNode(uint16_t lValueIndex, TypeDef* type, bool constant, bool ref) : AotNode(type, Value)
    {
        assert(type);
        _lValueID = lValueIndex;
        _constant = constant;
        _ref = ref;
    }

    AotNode* AotValueNode::optimize()
    {
        //TODO if is const just return const node
        return this;
    }

    AotValue AotValueNode::generateBytecode(CompilerCtx& ctx) const
    {
        if (ctx.lValues.count(_lValueID))
            return ctx.lValues.at(_lValueID);
        AotValue value = ctx.newReg(_resType, _constant & AotValue::Const);

        if(_resType->type() != ObjectRef)
        {
            ctx.lValues.insert({_lValueID, value});
            return value;
        }
        if(_ref)
        {
            ctx.lValues.insert({_lValueID, value});
            ctx.function->appendCode(Operand::MOVI, value.valueIndex, (uint32_t)0);
            return value;
        }

        value.valueIndex.storageType = ValueStorageType_StackPtr;
        ctx.lValues.insert({_lValueID, value});

        auto s = dynamic_cast<StructDef*>(_resType);

        if(ctx.localStructIndices.count(s))
            ctx.function->appendCode(Operand::ALLOC, value.valueIndex, ctx.localStructIndices.at(s));
        else
        {
            uint16_t sIndex = 0;
            for(auto& sName : ctx.script->linkedStructs)
            {
                if(sName == s->name())
                    break;
                ++sIndex;
            }
            if(sIndex == ctx.script->linkedStructs.size())
                ctx.script->linkedStructs.push_back(s->name());
            ctx.function->appendCode(Operand::EXALLOC, value.valueIndex, sIndex);
        }
        return value;
    }

    AotDerefNode::AotDerefNode(AotNode* value, TypeDef* type, uint32_t offset) : AotNode(type, Deref), _value(value)
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

    AotValue AotDerefNode::generateBytecode(CompilerCtx& ctx) const
    {
        AotValue ptr = _value->generateBytecode(ctx);
        assert(ptr.valueIndex.storageType == ValueStorageType_Ptr || ptr.valueIndex.storageType == ValueStorageType_StackPtr);
        ptr.valueIndex.offset = _offset;
        ptr.valueIndex.storageType = ValueStorageType_DerefPtr;
        ptr.def = _resType;
        return ptr;
    }

    AotNewNode::AotNewNode(StructDef* structType) : AotNode((TypeDef*)structType, New)
    {

    }

    AotNode* AotNewNode::optimize()
    {
        return this;
    }

    AotValue AotNewNode::generateBytecode(CompilerCtx& ctx) const
    {
        auto ptr = ctx.newReg(_resType, 0);
        ctx.function->appendCode(Operand::ALLOC, ptr.valueIndex, _resType->size());
        return ptr;
    }

    AotDeleteNode::AotDeleteNode(AotNode* ptr) : AotNode(nullptr, Free), _ptr(ptr)
    {
    }

    AotNode* AotDeleteNode::optimize()
    {
        return this;
    }

    AotValue AotDeleteNode::generateBytecode(CompilerCtx& ctx) const
    {
        auto ptr = _ptr->generateBytecode(ctx);
        assert(ptr.valueIndex.storageType == ValueStorageType_Ptr);
        ctx.function->appendCode(Operand::FREE, ptr.valueIndex);
        ctx.function->appendCode(Operand::MOVI, ptr.valueIndex, (int32_t)0);
        return {};
    }
}
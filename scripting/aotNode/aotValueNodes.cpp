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
            case Ptr:
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

    AotValueNode::AotValueNode(uint16_t lValueIndex, TypeDef* type, bool constant) : AotNode(type, Value)
    {
        _lValueIndex = lValueIndex;
        _constant = constant;
    }

    AotNode* AotValueNode::optimize()
    {
        //TODO if is const just return const node
        return this;
    }

    AotValue AotValueNode::generateBytecode(CompilerCtx& ctx) const
    {
        if (ctx.lValues.count(_lValueIndex))
            return ctx.lValues.at(_lValueIndex);
        AotValue value = ctx.newReg(_resType, _constant & AotValue::Const);
        ctx.lValues.insert({_lValueIndex, value});
        return value;
    }
}
//
// Created by eli on 10/19/2022.
//

#include "aotValueNodes.h"
#include "../compiler.h"

AotConst::AotConst(std::any value) : AotNode(Const), _value(std::move(value))
{

}

AotNode* AotConst::optimize()
{
    return this;
}

AotValue AotConst::generateBytecode(CompilerCtx& ctx) const
{
    ValueType type;
    if(_value.type() == typeid(int32_t))
        type = ValueType::Int32;
    else if(_value.type() == typeid(int64_t))
        type = ValueType::Int64;
    else if(_value.type() == typeid(float))
        type = ValueType::Float32;
    else if(_value.type() == typeid(double))
        type = ValueType::Float64;
    else
        assert(false);
    auto value = ctx.newConst(type);
    switch(type)
    {
        case Int32:
            ctx.function->appendCode(ScriptFunction::LOADC, value.valueIndex, std::any_cast<int32_t>(_value));
            break;
        case Int64:
            ctx.function->appendCode(ScriptFunction::LOADC, value.valueIndex, std::any_cast<int64_t>(_value));
            break;
        case Float32:
            ctx.function->appendCode(ScriptFunction::LOADC, value.valueIndex, std::any_cast<float>(_value));
            break;
        case Float64:
            ctx.function->appendCode(ScriptFunction::LOADC, value.valueIndex, std::any_cast<double>(_value));
            break;
    }
    return value;
}

const std::any& AotConst::value() const
{
    return _value;
}

AotValueNode::AotValueNode(uint16_t lValueIndex, std::string type, bool constant) : AotNode(Value)
{
    _lValueIndex = lValueIndex;
    _type = std::move(type);
    _constant = constant;
}

AotNode* AotValueNode::optimize()
{
    //TODO if is const just return const node
    return this;
}

AotValue AotValueNode::generateBytecode(CompilerCtx& ctx) const
{
    if(ctx.lValues.count(_lValueIndex))
        return ctx.lValues.at(_lValueIndex);
    AotValue value = ctx.newReg(_type, _constant & AotValue::Const);
    ctx.lValues.insert({_lValueIndex, value});
    return value;
}

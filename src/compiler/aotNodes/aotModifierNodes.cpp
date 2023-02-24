//
// Created by wirewhiz on 2/18/23.
//

#include "aotModifierNodes.h"
#include "../compiler.h"
#include "aotValueNodes.h"
#include "nativeTypes.h"
#include "typeDef.h"

namespace BraneScript
{
    AotCastNode::AotCastNode(AotNode* arg, const TypeDef* castType) : AotUnaryArgNode(arg, castType) {}

    AotNode* AotCastNode::optimize()
    {
        AotUnaryArgNode::optimize();

        if(arg->is<AotConstNode>())
        {
            if(arg->resType() == _resType)
                return arg.release();
            switch(arg->resType()->type())
            {
                case ValueType::Void:
                case ValueType::Struct:
                    throw std::runtime_error("Invalid compile time cast");
                case ValueType::Bool:
                    return arg->as<AotConstNode>()->cast<bool>();
                case ValueType::Char:
                    return arg->as<AotConstNode>()->cast<char>();
                case ValueType::UInt32:
                    return arg->as<AotConstNode>()->cast<uint32_t>();
                case ValueType::UInt64:
                    return arg->as<AotConstNode>()->cast<uint64_t>();
                case ValueType::Int32:
                    return arg->as<AotConstNode>()->cast<int32_t>();
                case ValueType::Int64:
                    return arg->as<AotConstNode>()->cast<int64_t>();
                case ValueType::Float32:
                    return arg->as<AotConstNode>()->cast<float>();
                case ValueType::Float64:
                    return arg->as<AotConstNode>()->cast<double>();
            }
        }
        return this;
    }

    AotValue* AotCastNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        AotValue* source = arg->generateBytecode(ctx);
        if (source->type == _resType)
            return source;

        source = ctx.castReg(source);
        AotValue* castValue = ctx.newReg(_resType, AotValue::Temp);

        switch(_resType->type())
        {
            case ValueType::UInt32:
                switch(source->type->type())
                {
                    case ValueType::Int32:
                        ctx.appendCode(Operand::MOV, ctx.serialize(castValue), ctx.serialize(source));
                    case ValueType::UInt64:
                    case ValueType::Int64:
                        ctx.appendCode(Operand::CI64I32, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::Float32:
                        ctx.appendCode(Operand::CF32I32, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::Float64:
                        ctx.appendCode(Operand::CF64I32, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    default:
                        assert(false);
                }
                break;
            case ValueType::UInt64:
                switch(source->type->type())
                {
                    case ValueType::UInt32:
                    case ValueType::Int32:
                        ctx.appendCode(Operand::CU32U64, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::Int64:
                        ctx.appendCode(Operand::MOV, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::Float32:
                        ctx.appendCode(Operand::CF32I32, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::Float64:
                        ctx.appendCode(Operand::CF64I32, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    default:
                        assert(false);
                }
                break;
            case ValueType::Int32:
                switch(source->type->type())
                {
                    case ValueType::UInt32:
                        ctx.appendCode(Operand::MOV, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::UInt64:
                    case ValueType::Int64:
                        ctx.appendCode(Operand::CI64I32, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::Float32:
                        ctx.appendCode(Operand::CF32I32, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::Float64:
                        ctx.appendCode(Operand::CF64I32, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    default:
                        assert(false);
                }
                break;
            case ValueType::Int64:
                switch(source->type->type())
                {
                    case ValueType::UInt32:
                        ctx.appendCode(Operand::CU32U64, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::UInt64:
                        ctx.appendCode(Operand::CU64I64, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::Int32:
                        ctx.appendCode(Operand::CI32I64, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::Float32:
                    {
                        auto temp = ctx.newReg(getNativeTypeDef(ValueType::Int32), AotValue::Temp);
                        ctx.appendCode(Operand::CF32I32, ctx.serialize(temp), ctx.serialize(source));
                        ctx.appendCode(Operand::CI32I64, ctx.serialize(castValue), ctx.serialize(temp));
                    }
                    break;
                    case ValueType::Float64:
                    {
                        auto temp = ctx.newReg(getNativeTypeDef(ValueType::Int32), AotValue::Temp);
                        ctx.appendCode(Operand::CF64I32, ctx.serialize(temp), ctx.serialize(source));
                        ctx.appendCode(Operand::CI32I64, ctx.serialize(castValue), ctx.serialize(temp));
                    }
                    break;
                    default:
                        assert(false);
                }
                break;
            case ValueType::Float32:
                switch(source->type->type())
                {
                    case ValueType::UInt32:
                    {
                        auto temp = ctx.newReg(getNativeTypeDef(ValueType::Int32), AotValue::Temp);
                        ctx.appendCode(Operand::CU32I32, ctx.serialize(temp), ctx.serialize(source));
                        ctx.appendCode(Operand::CI32F32, ctx.serialize(castValue), ctx.serialize(temp));
                    }
                    break;
                    case ValueType::UInt64:
                    {
                        auto temp = ctx.newReg(getNativeTypeDef(ValueType::Int32), AotValue::Temp);
                        ctx.appendCode(Operand::CU32I32, ctx.serialize(temp), ctx.serialize(source));
                        ctx.appendCode(Operand::CI32F32, ctx.serialize(castValue), ctx.serialize(temp));
                    }
                    break;
                    case ValueType::Int32:
                        ctx.appendCode(Operand::CI32F32, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::Int64:
                    {
                        auto temp = ctx.newReg(getNativeTypeDef(ValueType::Int32), AotValue::Temp);
                        ctx.appendCode(Operand::CI64I32, ctx.serialize(temp), ctx.serialize(source));
                        ctx.appendCode(Operand::CI32F32, ctx.serialize(castValue), ctx.serialize(temp));
                    }
                    break;
                    case ValueType::Float64:
                        ctx.appendCode(Operand::CF64F32, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    default:
                        assert(false);
                }
                break;
            case ValueType::Float64:
                switch(source->type->type())
                {
                    case ValueType::UInt32:
                    {
                        auto temp = ctx.newReg(getNativeTypeDef(ValueType::Int32), AotValue::Temp);
                        ctx.appendCode(Operand::CU32I32, ctx.serialize(temp), ctx.serialize(source));
                        ctx.appendCode(Operand::CI32F64, ctx.serialize(castValue), ctx.serialize(temp));
                    }
                    break;
                    case ValueType::UInt64:
                    {
                        auto temp = ctx.newReg(getNativeTypeDef(ValueType::Int32), AotValue::Temp);
                        ctx.appendCode(Operand::CU32I32, ctx.serialize(temp), ctx.serialize(source));
                        ctx.appendCode(Operand::CI32F64, ctx.serialize(castValue), ctx.serialize(temp));
                    }
                    break;
                    case ValueType::Int32:
                        ctx.appendCode(Operand::CI32F64, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    case ValueType::Int64:
                    {
                        auto temp = ctx.newReg(getNativeTypeDef(ValueType::Int32), AotValue::Temp);
                        ctx.appendCode(Operand::CI64I32, ctx.serialize(temp), ctx.serialize(source));
                        ctx.appendCode(Operand::CI32F64, ctx.serialize(castValue), ctx.serialize(temp));
                    }
                    break;
                    case ValueType::Float32:
                        ctx.appendCode(Operand::CF32F64, ctx.serialize(castValue), ctx.serialize(source));
                        break;
                    default:
                        assert(false);
                }
                break;
            default:
                assert(false);
        }
        assert(castValue);
        return castValue;
    }

    AotAssignNode::AotAssignNode(AotNode* lvalue, AotNode* rvalue) : AotBinaryArgNode(lvalue, rvalue, lvalue->resType())
    {
        assert(argB->resType() == _resType);
    }

    AotValue* AotAssignNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        auto rValue = ctx.castValue(argB->generateBytecode(ctx));
        auto lValue = argA->generateBytecode(ctx);

        if(lValue->isRef() && rValue->isRef())
        {
            auto s = static_cast<const StructDef*>(lValue->type);
            bool shouldMove = rValue->isExternalRef() && rValue->isTemp();
            int16_t cIndex;
            if(shouldMove)
                cIndex = ctx.script.linkMoveConstructor(s);
            else
                cIndex = ctx.script.linkCopyConstructor(s);

            // Call constructor
            ctx.appendCode(Operand::CALL, cIndex);
            ctx.appendCode(ctx.serialize(lValue));
            ctx.appendCode(ctx.serialize(rValue));

            if(shouldMove)
            {
                // Destruct the temp struct before deleting
                ctx.appendCode(Operand::CALL, ctx.script.linkDestructor(s));
                ctx.appendCode(ctx.serialize(rValue));
                ctx.appendCode(FREE, ctx.serialize(rValue));
            }
        }
        else
            ctx.appendCode(MOV, ctx.serialize(lValue), ctx.serialize(rValue));

        if(rValue->isTemp())
            ctx.releaseValue(rValue);

        return lValue;
    };

    AotAddNode::AotAddNode(AotNode* a, AotNode* b) : AotBinaryArgNode(a, b, a->resType())
    {
        assert(a->resType() == b->resType());
    }

    AotNode* AotAddNode::optimize()
    {
        AotBinaryArgNode::optimize();
        if(argA->is<AotConstNode>() && argB->is<AotConstNode>())
        {
            auto* aNode = argA->as<AotConstNode>();
            auto* bNode = argB->as<AotConstNode>();
            switch(resType()->type())
            {
                case ValueType::Void:
                case ValueType::Bool:
                case ValueType::Struct:
                    throw std::runtime_error("Invalid arguments for compile time operation");
                case ValueType::Char:
                    return new AotConstNode(aNode->asChar + bNode->asChar);
                case ValueType::UInt32:
                    return new AotConstNode(aNode->asUInt + bNode->asUInt);
                case ValueType::UInt64:
                    return new AotConstNode(aNode->asUInt64 + bNode->asUInt64);
                case ValueType::Int32:
                    return new AotConstNode(aNode->asInt + bNode->asInt);
                case ValueType::Int64:
                    return new AotConstNode(aNode->asInt64 + bNode->asInt64);
                case ValueType::Float32:
                    return new AotConstNode(aNode->asFloat32 + bNode->asFloat32);
                case ValueType::Float64:
                    return new AotConstNode(aNode->asFloat64 + bNode->asFloat64);
            }
        }
        return this;
    }

    AotValue* AotAddNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        AotValue* left = argA->generateBytecode(ctx);
        AotValue* right = argB->generateBytecode(ctx);
        assert(left->type == right->type);
        if(right->flags & AotValue::Temp && !(left->flags & AotValue::Temp))
            std::swap(left, right);
        else
            left = ctx.castTemp(left);
        ctx.appendCode(ADD, ctx.serialize(left), ctx.serialize(right));
        if(right->isTemp())
            ctx.releaseValue(right);
        return left;
    }

    AotSubNode::AotSubNode(AotNode* a, AotNode* b) : AotBinaryArgNode(a, b, a->resType())
    {
        assert(a->resType() == b->resType());
    }

    AotNode* AotSubNode::optimize()
    {
        AotBinaryArgNode::optimize();
        if(argA->is<AotConstNode>() && argB->is<AotConstNode>())
        {
            auto* aNode = argA->as<AotConstNode>();
            auto* bNode = argB->as<AotConstNode>();
            switch(resType()->type())
            {
                case ValueType::Void:
                case ValueType::Bool:
                case ValueType::Struct:
                    throw std::runtime_error("Invalid arguments for compile time operation");
                case ValueType::Char:
                    return new AotConstNode(aNode->asChar - bNode->asChar);
                case ValueType::UInt32:
                    return new AotConstNode(aNode->asUInt - bNode->asUInt);
                case ValueType::UInt64:
                    return new AotConstNode(aNode->asUInt64 - bNode->asUInt64);
                case ValueType::Int32:
                    return new AotConstNode(aNode->asInt - bNode->asInt);
                case ValueType::Int64:
                    return new AotConstNode(aNode->asInt64 - bNode->asInt64);
                case ValueType::Float32:
                    return new AotConstNode(aNode->asFloat32 - bNode->asFloat32);
                case ValueType::Float64:
                    return new AotConstNode(aNode->asFloat64 - bNode->asFloat64);
            }
        }
        return this;
    }

    AotValue* AotSubNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        AotValue* left = ctx.castTemp(argA->generateBytecode(ctx));
        AotValue* right = argB->generateBytecode(ctx);
        ctx.appendCode(SUB, ctx.serialize(left), ctx.serialize(right));
        if(right->isTemp())
            ctx.releaseValue(right);
        return left;
    }

    AotMulNode::AotMulNode(AotNode* a, AotNode* b) : AotBinaryArgNode(a, b, a->resType())
    {
        assert(a->resType() == b->resType());
    }

    AotNode* AotMulNode::optimize()
    {
        AotBinaryArgNode::optimize();
        if(argA->is<AotConstNode>() && argB->is<AotConstNode>())
        {
            auto* aNode = argA->as<AotConstNode>();
            auto* bNode = argB->as<AotConstNode>();
            switch(resType()->type())
            {
                case ValueType::Void:
                case ValueType::Bool:
                case ValueType::Struct:
                    throw std::runtime_error("Invalid arguments for compile time operation");
                case ValueType::Char:
                    return new AotConstNode(aNode->asChar * bNode->asChar);
                case ValueType::UInt32:
                    return new AotConstNode(aNode->asUInt * bNode->asUInt);
                case ValueType::UInt64:
                    return new AotConstNode(aNode->asUInt64 * bNode->asUInt64);
                case ValueType::Int32:
                    return new AotConstNode(aNode->asInt * bNode->asInt);
                case ValueType::Int64:
                    return new AotConstNode(aNode->asInt64 * bNode->asInt64);
                case ValueType::Float32:
                    return new AotConstNode(aNode->asFloat32 * bNode->asFloat32);
                case ValueType::Float64:
                    return new AotConstNode(aNode->asFloat64 * bNode->asFloat64);
            }
        }
        return this;
    }

    AotValue* AotMulNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        AotValue* left = argA->generateBytecode(ctx);
        AotValue* right = argB->generateBytecode(ctx);
        if(right->flags & AotValue::Temp && !(left->flags & AotValue::Temp))
            std::swap(left, right);
        else
            left = ctx.castTemp(left);
        ctx.appendCode(MUL, ctx.serialize(left), ctx.serialize(right));
        if(right->isTemp())
            ctx.releaseValue(right);
        return left;
    }

    AotDivNode::AotDivNode(AotNode* a, AotNode* b) : AotBinaryArgNode(a, b, a->resType())
    {
        assert(a->resType() == b->resType());
    }

    AotNode* AotDivNode::optimize()
    {
        AotBinaryArgNode::optimize();
        if(argA->is<AotConstNode>() && argB->is<AotConstNode>())
        {
            auto* aNode = argA->as<AotConstNode>();
            auto* bNode = argB->as<AotConstNode>();
            switch(resType()->type())
            {
                case ValueType::Void:
                case ValueType::Bool:
                case ValueType::Struct:
                    throw std::runtime_error("Invalid arguments for compile time operation");
                case ValueType::Char:
                    return new AotConstNode(aNode->asChar / bNode->asChar);
                case ValueType::UInt32:
                    return new AotConstNode(aNode->asUInt / bNode->asUInt);
                case ValueType::UInt64:
                    return new AotConstNode(aNode->asUInt64 / bNode->asUInt64);
                case ValueType::Int32:
                    return new AotConstNode(aNode->asInt / bNode->asInt);
                case ValueType::Int64:
                    return new AotConstNode(aNode->asInt64 / bNode->asInt64);
                case ValueType::Float32:
                    return new AotConstNode(aNode->asFloat32 / bNode->asFloat32);
                case ValueType::Float64:
                    return new AotConstNode(aNode->asFloat64 / bNode->asFloat64);
            }
        }
        return this;
    }

    AotValue* AotDivNode::generateBytecode(FunctionCompilerCtx& ctx) const
    {
        AotValue* left = ctx.castTemp(argA->generateBytecode(ctx));
        AotValue* right = ctx.castReg(argB->generateBytecode(ctx));
        ctx.appendCode(DIV, ctx.serialize(left), ctx.serialize(right));
        if(right->isTemp())
            ctx.releaseValue(right);
        return left;
    }

} // namespace BraneScript
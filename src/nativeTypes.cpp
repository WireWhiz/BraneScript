//
// Created by wirewhiz on 15/10/22.
//

#include "nativeTypes.h"
#include "operator.h"
#include "aotNode/aotNode.h"
#include "compiler.h"

#include <cassert>

namespace BraneScript
{
    class BoolDef : public TypeDef
    {
    public:
        const char* name() const override
        {
            return "bool";
        }

        uint16_t size() const override
        {
            return sizeof(bool);
        }

        ValueType type() const override
        {
            return Bool;
        }
    };

    class UIntDef : public TypeDef
    {
    public:
        const char* name() const override
        {
            return "uint";
        }

        uint16_t size() const override
        {
            return sizeof(uint32_t);
        }

        ValueType type() const override
        {
            return UInt32;
        }
    };

    class IntDef : public TypeDef
    {
    public:
        const char* name() const override
        {
            return "int";
        }

        uint16_t size() const override
        {
            return sizeof(int32_t);
        }

        ValueType type() const override
        {
            return Int32;
        }
    };

    class FloatDef : public TypeDef
    {
    public:
        const char* name() const override
        {
            return "float";
        }

        uint16_t size() const override
        {
            return sizeof(float);
        }

        ValueType type() const override
        {
            return Float32;
        }
    };

    std::vector<TypeDef*> nativeTypes({new BoolDef(), new UIntDef(), new IntDef(), new FloatDef()});

    std::vector<TypeDef*> getNativeTypes()
    {
        return nativeTypes;
    };


    TypeDef* getNativeTypeDef(ValueType type)
    {
        switch (type)
        {
            case Bool:
                return nativeTypes[0];
            case UInt32:
                return nativeTypes[1];
            case Int32:
                return nativeTypes[2];
            case UInt64:
                break;
            case Int64:
                break;
            case Float32:
                return nativeTypes[3];
            case Float64:
                break;
        }
        return nullptr;
    };

    class NativeCastOpr : public ConstexprOperator
    {
        const TypeDef* _resType;
        template<typename T>
        AotNode* castConst(AotConstNode* arg1) const
        {
            if(arg1->resType() == _resType)
                return new AotConstNode(arg1->value(), _resType);
            switch(arg1->resType()->type())
            {
                case UInt32:
                    return new AotConstNode((T)std::any_cast<uint32_t>(arg1->value()), _resType);
                case UInt64:
                    return new AotConstNode((T)std::any_cast<uint64_t>(arg1->value()), _resType);
                case Int32:
                    return new AotConstNode((T)std::any_cast<int32_t>(arg1->value()), _resType);
                case Int64:
                    return new AotConstNode((T)std::any_cast<int64_t>(arg1->value()), _resType);
                case Float32:
                    return new AotConstNode((T)std::any_cast<float>(arg1->value()), _resType);
                case Float64:
                    return new AotConstNode((T)std::any_cast<double>(arg1->value()), _resType);
            }
            return nullptr;
        }
    public:
        explicit NativeCastOpr(const TypeDef* type) : _resType(type), ConstexprOperator(type->name())
        {
        }
        AotValue* generateBytecode(CompilerCtx& ctx, AotValue* source, AotValue* nullArg) const override
        {
            assert(nullArg == nullptr);
            if (source->def == _resType)
                return source;

            source = ctx.castReg(source);
            AotValue* castValue = ctx.newReg(_resType->name(), AotValue::Temp);
            ctx.function->appendCode(MOV, castValue->value(ctx), source->value(ctx));
            return castValue;
        }
        const TypeDef* resType() const override
        {
            return _resType;
        }
        AotNode* precalculate(AotConstNode* arg1, AotConstNode* arg2) const override
        {
            assert(arg2 == nullptr);
            switch(_resType->type())
            {
                case UInt32:
                    return castConst<uint32_t>(arg1);
                case UInt64:
                    return castConst<uint64_t>(arg1);
                case Int32:
                    return castConst<int32_t>(arg1);
                case Int64:
                    return castConst<int64_t>(arg1);
                case Float32:
                    return castConst<float>(arg1);
                case Float64:
                    return castConst<double>(arg1);
                default:
                    break;
            }
            throw std::runtime_error("tried to precalculate native cast with unknown type");
        }
    };

    class AdditionOpr : public ConstexprOperator
    {
        const TypeDef* _resType;
    public:
        AdditionOpr(const TypeDef* type) : _resType(type), ConstexprOperator("+")
        {
        }
        AotValue* generateBytecode(CompilerCtx& ctx, AotValue* left, AotValue* right) const override
        {
            assert(left->def == _resType && right->def == _resType);
            if (right->flags & AotValue::Temp && !(left->flags & AotValue::Temp))
                std::swap(left, right);
            else
                left = ctx.castTemp(left);
            ctx.function->appendCode(ADD, left->value(ctx), right->value(ctx));
            return left;
        }
        const TypeDef* resType() const override
        {
            return _resType;
        }
        AotNode* precalculate(AotConstNode* arg1, AotConstNode* arg2) const override
        {
            switch(_resType->type())
            {
                case UInt32:
                    return new AotConstNode(std::any_cast<uint32_t>(arg1->value()) + std::any_cast<uint32_t>(arg2->value()), _resType);
                case UInt64:
                    return new AotConstNode(std::any_cast<uint64_t>(arg1->value()) + std::any_cast<uint64_t>(arg2->value()), _resType);
                case Int32:
                    return new AotConstNode(std::any_cast<int32_t>(arg1->value()) + std::any_cast<int32_t>(arg2->value()), _resType);
                case Int64:
                    return new AotConstNode(std::any_cast<int64_t>(arg1->value()) + std::any_cast<int64_t>(arg2->value()), _resType);
                case Float32:
                    return new AotConstNode(std::any_cast<float>(arg1->value()) + std::any_cast<float>(arg2->value()), _resType);
                case Float64:
                    return new AotConstNode(std::any_cast<double>(arg1->value()) + std::any_cast<double>(arg2->value()), _resType);
                default:
                    throw std::runtime_error("tried to precalculate addition with unknown type");
            }
        }
    };

    class SubtractionOpr : public ConstexprOperator
    {
        const TypeDef* _resType;
    public:
        SubtractionOpr(const TypeDef* type) : _resType(type), ConstexprOperator("-")
        {
        }
        AotValue* generateBytecode(CompilerCtx& ctx, AotValue* left, AotValue* right) const override
        {
            assert(left->def == _resType && right->def == _resType);
            left = ctx.castTemp(left);
            ctx.function->appendCode(SUB, left->value(ctx), right->value(ctx));
            return left;
        }
        const TypeDef* resType() const override
        {
            return _resType;
        }
        AotNode* precalculate(AotConstNode* arg1, AotConstNode* arg2) const override
        {
            switch(_resType->type())
            {
                case UInt32:
                    return new AotConstNode(std::any_cast<uint32_t>(arg1->value()) - std::any_cast<uint32_t>(arg2->value()), _resType);
                case UInt64:
                    return new AotConstNode(std::any_cast<uint64_t>(arg1->value()) - std::any_cast<uint64_t>(arg2->value()), _resType);
                case Int32:
                    return new AotConstNode(std::any_cast<int32_t>(arg1->value()) - std::any_cast<int32_t>(arg2->value()), _resType);
                case Int64:
                    return new AotConstNode(std::any_cast<int64_t>(arg1->value()) - std::any_cast<int64_t>(arg2->value()), _resType);
                case Float32:
                    return new AotConstNode(std::any_cast<float>(arg1->value()) - std::any_cast<float>(arg2->value()), _resType);
                case Float64:
                    return new AotConstNode(std::any_cast<double>(arg1->value()) - std::any_cast<double>(arg2->value()), _resType);
                default:
                    throw std::runtime_error("tried to precalculate addition with unknown type");
            }
        }
    };

    class MultiplicationOpr : public ConstexprOperator
    {
        const TypeDef* _resType;
    public:
        MultiplicationOpr(const TypeDef* type) : _resType(type), ConstexprOperator("*")
        {
        }
        AotValue* generateBytecode(CompilerCtx& ctx, AotValue* left, AotValue* right) const override
        {
            assert(left->def == _resType && right->def == _resType);
            if (right->flags & AotValue::Temp && !(left->flags & AotValue::Temp))
                std::swap(left, right);
            else
                left = ctx.castTemp(left);
            ctx.function->appendCode(MUL, left->value(ctx), right->value(ctx));
            return left;
        }
        const TypeDef* resType() const override
        {
            return _resType;
        }
        AotNode* precalculate(AotConstNode* arg1, AotConstNode* arg2) const override
        {
            switch(_resType->type())
            {
                case UInt32:
                    return new AotConstNode(std::any_cast<uint32_t>(arg1->value()) * std::any_cast<uint32_t>(arg2->value()), _resType);
                case UInt64:
                    return new AotConstNode(std::any_cast<uint64_t>(arg1->value()) * std::any_cast<uint64_t>(arg2->value()), _resType);
                case Int32:
                    return new AotConstNode(std::any_cast<int32_t>(arg1->value()) * std::any_cast<int32_t>(arg2->value()), _resType);
                case Int64:
                    return new AotConstNode(std::any_cast<int64_t>(arg1->value()) * std::any_cast<int64_t>(arg2->value()), _resType);
                case Float32:
                    return new AotConstNode(std::any_cast<float>(arg1->value()) * std::any_cast<float>(arg2->value()), _resType);
                case Float64:
                    return new AotConstNode(std::any_cast<double>(arg1->value()) * std::any_cast<double>(arg2->value()), _resType);
                default:
                    throw std::runtime_error("tried to precalculate addition with unknown type");
            }
        }
    };

    class DivisionOpr : public ConstexprOperator
    {
        const TypeDef* _resType;
    public:
        DivisionOpr(const TypeDef* type) : _resType(type), ConstexprOperator("*")
        {
        }
        AotValue* generateBytecode(CompilerCtx& ctx, AotValue* left, AotValue* right) const override
        {
            assert(left->def == _resType && right->def == _resType);
            left = ctx.castTemp(left);
            right = ctx.castReg(right);
            ctx.function->appendCode(DIV, left->value(ctx), right->value(ctx));
            return left;
        }
        const TypeDef* resType() const override
        {
            return _resType;
        }
        AotNode* precalculate(AotConstNode* arg1, AotConstNode* arg2) const override
        {
            switch(_resType->type())
            {
                case UInt32:
                    return new AotConstNode(std::any_cast<uint32_t>(arg1->value()) / std::any_cast<uint32_t>(arg2->value()), _resType);
                case UInt64:
                    return new AotConstNode(std::any_cast<uint64_t>(arg1->value()) / std::any_cast<uint64_t>(arg2->value()), _resType);
                case Int32:
                    return new AotConstNode(std::any_cast<int32_t>(arg1->value()) / std::any_cast<int32_t>(arg2->value()), _resType);
                case Int64:
                    return new AotConstNode(std::any_cast<int64_t>(arg1->value()) / std::any_cast<int64_t>(arg2->value()), _resType);
                case Float32:
                    return new AotConstNode(std::any_cast<float>(arg1->value()) / std::any_cast<float>(arg2->value()), _resType);
                case Float64:
                    return new AotConstNode(std::any_cast<double>(arg1->value()) / std::any_cast<double>(arg2->value()), _resType);
                default:
                    throw std::runtime_error("tried to precalculate addition with unknown type");
            }
        }
    };

    class CompareOpr : public ConstexprOperator
    {
        enum Mode
        {
            Equal = AotValue::EqualRes,
            NotEqual = AotValue::NotEqualRes,
            Greater = AotValue::GreaterRes,
            GreaterEqual = AotValue::GreaterEqualRes
        } _mode;
        bool _swapOperands;

#define PRECALCULATE_COMPARE(operator) \
        switch(arg1->resType()->type())\
        {\
            case UInt32:\
                return new AotConstNode(std::any_cast<uint32_t>(arg1->value()) operator std::any_cast<uint32_t>(arg2->value()), getNativeTypeDef(Bool));\
            case UInt64:\
                return new AotConstNode(std::any_cast<uint64_t>(arg1->value()) operator std::any_cast<uint64_t>(arg2->value()), getNativeTypeDef(Bool));\
            case Int32:\
                return new AotConstNode(std::any_cast<int32_t>(arg1->value()) operator std::any_cast<int32_t>(arg2->value()), getNativeTypeDef(Bool));\
            case Int64:\
                return new AotConstNode(std::any_cast<int64_t>(arg1->value()) operator std::any_cast<int64_t>(arg2->value()), getNativeTypeDef(Bool));\
            case Float32:\
                return new AotConstNode(std::any_cast<float>(arg1->value()) operator std::any_cast<float>(arg2->value()), getNativeTypeDef(Bool));\
            case Float64:\
                return new AotConstNode(std::any_cast<double>(arg1->value()) operator std::any_cast<double>(arg2->value()), getNativeTypeDef(Bool));\
            default:\
                throw std::runtime_error("tried to precalculate compare with unknown type");\
        }

    public:
        CompareOpr(const std::string& symbol) : ConstexprOperator(symbol)
        {
            _swapOperands = false;
            if(symbol == "==")
                _mode = Equal;
            else if(symbol == "!=")
                _mode = NotEqual;
            else if(symbol == ">")
                _mode = Greater;
            else if(symbol == ">=")
                _mode = GreaterEqual;
            else if(symbol == "<")
            {
                _mode = Greater;
                _swapOperands = true;
            }
            else if(symbol == "<=")
            {
                _mode = GreaterEqual;
                _swapOperands = true;
            }
            else
                assert(false);
        }

        AotValue* generateBytecode(CompilerCtx& ctx, AotValue* left, AotValue* right) const override
        {
            if(_swapOperands)
                std::swap(left, right);
            left = ctx.castReg(left);

            AotValue* result = ctx.blankValue();
            bool sign = left->def->type() == Int32 || right->def->type() == Int64;
            switch (_mode)
            {
                case Equal:
                case NotEqual:
                    result->compareType = (AotValue::CompareType)_mode;
                    break;
                case Greater:
                    result->compareType = sign ? AotValue::GreaterRes : AotValue::AboveRes;
                    break;
                case GreaterEqual:
                    result->compareType = sign ? AotValue::GreaterEqualRes : AotValue::AboveEqualRes;
                    break;
            }

            result->def = resType();

            ctx.function->appendCode(CMP, left->value(ctx), right->value(ctx));
            return result;
        }

        AotNode* precalculate(AotConstNode* arg1, AotConstNode* arg2) const override
        {
            if(_swapOperands)
                std::swap(arg1, arg2);
            switch (_mode)
            {
                case Equal:
                    PRECALCULATE_COMPARE(==)
                    break;
                case NotEqual:
                    PRECALCULATE_COMPARE(!=)
                    break;
                case Greater:
                    PRECALCULATE_COMPARE(>)
                    break;
                case GreaterEqual:
                    PRECALCULATE_COMPARE(>=)
                    break;
            }
            return nullptr;
        }
        const TypeDef* resType() const override
        {
            return getNativeTypeDef(Bool);
        }
    };

    robin_hood::unordered_map<std::string, Operator*> setupNativeOperators()
    {
        robin_hood::unordered_map<std::string, Operator*> oprs;
        auto scalarTypes = {
                getNativeTypeDef(UInt32),
                getNativeTypeDef(Int32),
                getNativeTypeDef(Float32)
        };
        for(auto type : scalarTypes)
        {
            oprs.insert({oprSig("+", type, type), new AdditionOpr(type)});
            oprs.insert({oprSig("-", type, type), new SubtractionOpr(type)});
            oprs.insert({oprSig("*", type, type), new MultiplicationOpr(type)});
            oprs.insert({oprSig("/", type, type), new DivisionOpr(type)});
            for(const char* cmpOp : {"==", "!=", "<", ">", "<=", ">="})
                oprs.insert({oprSig(cmpOp, type, type), new CompareOpr(cmpOp)});
            for(auto type2 : scalarTypes)
            {
                if(type == type2)
                    continue;
                oprs.insert({oprSig(type2->name(), type), new NativeCastOpr(type2)});
            }
        }
        return std::move(oprs);
    };

    robin_hood::unordered_map<std::string, Operator*> _nativeOperators = setupNativeOperators();


    const robin_hood::unordered_map<std::string, Operator*>& nativeOperators()
    {
        return _nativeOperators;
    }
}
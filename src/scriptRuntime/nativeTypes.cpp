//
// Created by wirewhiz on 15/10/22.
//

#include "nativeTypes.h"
#include "structDefinition.h"

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
            return ValueType::Bool;
        }
    };

    class CharDef : public TypeDef
    {
    public:
        const char* name() const override
        {
            return "char";
        }

        uint16_t size() const override
        {
            return sizeof(char);
        }

        ValueType type() const override
        {
            return ValueType::Char;
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
            return ValueType::UInt32;
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
            return ValueType::Int32;
        }
    };

    class UInt64Def : public TypeDef
    {
    public:
        const char* name() const override
        {
            return "uint64";
        }

        uint16_t size() const override
        {
            return sizeof(uint64_t);
        }

        ValueType type() const override
        {
            return ValueType::UInt64;
        }
    };

    class Int64Def : public TypeDef
    {
    public:
        const char* name() const override
        {
            return "int64";
        }

        uint16_t size() const override
        {
            return sizeof(int64_t);
        }

        ValueType type() const override
        {
            return ValueType::Int64;
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
            return ValueType::Float32;
        }
    };

    class Float64Def : public TypeDef
    {
    public:
        const char* name() const override
        {
            return "double";
        }

        uint16_t size() const override
        {
            return sizeof(double);
        }

        ValueType type() const override
        {
            return ValueType::Float64;
        }
    };

    class StringDef : public StructDef
    {
    public:
        StringDef() : StructDef("string"){
            /*setConstructor([](void* data){
                new (data)std::string;
            });
            setCopyConstructor([](void* dest, void* source){
                *(std::string*)dest = *(std::string*)source;
            });
            setMoveConstructor([](void* dest, void* source){
                *(std::string*)dest = std::move(*(std::string*)source);
            });
            setDestructor([](void* data)
            {
                delete (std::string*)data;
            });*/
        };

        uint16_t size() const override
        {
            return sizeof(std::string);
        }
    };

    std::vector<TypeDef*> nativeTypes({new BoolDef(), new CharDef(), new UIntDef(), new IntDef(), new UInt64Def(), new Int64Def(), new FloatDef(), new Float64Def(), new StringDef()});

    const std::vector<TypeDef*>& getNativeTypes()
    {
        return nativeTypes;
    };


    TypeDef* getNativeTypeDef(ValueType type)
    {
        switch (type)
        {
            case ValueType::Bool:
                return nativeTypes[0];
            case ValueType::Char:
                return nativeTypes[1];
            case ValueType::UInt32:
                return nativeTypes[2];
            case ValueType::Int32:
                return nativeTypes[3];
            case ValueType::UInt64:
                return nativeTypes[4];
            case ValueType::Int64:
                return nativeTypes[5];
            case ValueType::Float32:
                return nativeTypes[6];
            case ValueType::Float64:
                return nativeTypes[7];
            case ValueType::Struct:
                throw std::runtime_error("No native definition for struct type");
        }
        return nullptr;
    };

    /*class NativeCastOpr : public ConstexprOperator
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

            switch(_resType->type())
            {
                case UInt32:
                    switch(source->def->type())
                    {
                        case UInt64:
                        case Int32:
                        case Int64:
                            ctx.function->appendCode(Operand::MOV, castValue->value(ctx), source->value(ctx));
                            break;
                        case Float32:
                            ctx.function->appendCode(Operand::CF32I32, castValue->value(ctx), source->value(ctx));
                            break;
                        case Float64:
                            ctx.function->appendCode(Operand::CF64I32, castValue->value(ctx), source->value(ctx));
                            break;
                        default:
                            assert(false);
                    }
                    break;
                case UInt64:
                    switch(source->def->type())
                    {
                        case UInt32:
                        case Int32:
                        case Int64:
                            ctx.function->appendCode(Operand::MOV, castValue->value(ctx), source->value(ctx));
                            ctx.function->appendCode(Operand::MOV, castValue->value(ctx), source->value(ctx));
                            break;
                        case Float32:
                            ctx.function->appendCode(Operand::CF32I32, castValue->value(ctx), source->value(ctx));
                            break;
                        case Float64:
                            ctx.function->appendCode(Operand::CF64I32, castValue->value(ctx), source->value(ctx));
                            break;
                        default:
                            assert(false);
                    }
                    break;
                case Int32:
                    switch(source->def->type())
                    {
                        case UInt32:
                        case UInt64:
                            ctx.function->appendCode(Operand::CU32I32, castValue->value(ctx), source->value(ctx));
                            break;
                        case Int64:
                            ctx.function->appendCode(Operand::MOV, castValue->value(ctx), source->value(ctx));
                            break;
                        case Float32:
                            ctx.function->appendCode(Operand::CF32I32, castValue->value(ctx), source->value(ctx));
                            break;
                        case Float64:
                            ctx.function->appendCode(Operand::CF64I32, castValue->value(ctx), source->value(ctx));
                            break;
                        default:
                            assert(false);
                    }
                    break;
                case Int64:
                    switch(source->def->type())
                    {
                        case UInt32:
                            ctx.function->appendCode(Operand::MOV, castValue->value(ctx), source->value(ctx));
                            break;
                        case UInt64:
                            ctx.function->appendCode(Operand::CU64I64, castValue->value(ctx), source->value(ctx));
                            break;
                        case Int32:
                            ctx.function->appendCode(Operand::CI32I64, castValue->value(ctx), source->value(ctx));
                            break;
                        case Float32:
                        {
                            auto temp = ctx.newReg(getNativeTypeDef(Int32), 0);
                            ctx.function->appendCode(Operand::CF32I32, temp->value(ctx), source->value(ctx));
                            ctx.function->appendCode(Operand::CI32I64, castValue->value(ctx), temp->value(ctx));
                        }
                            break;
                        case Float64:
                        {
                            auto temp = ctx.newReg(getNativeTypeDef(Int32), 0);
                            ctx.function->appendCode(Operand::CF64I32, temp->value(ctx), source->value(ctx));
                            ctx.function->appendCode(Operand::CI32I64, castValue->value(ctx), temp->value(ctx));
                        }
                            break;
                        default:
                            assert(false);
                    }
                    break;
                case Float32:
                    switch(source->def->type())
                    {
                        case UInt32:
                        {
                            auto temp = ctx.newReg(getNativeTypeDef(Int32), 0);
                            ctx.function->appendCode(Operand::CU32I32, temp->value(ctx), source->value(ctx));
                            ctx.function->appendCode(Operand::CI32F32, castValue->value(ctx), temp->value(ctx));
                        }
                            break;
                        case UInt64:
                        {
                            auto temp = ctx.newReg(getNativeTypeDef(Int32), 0);
                            ctx.function->appendCode(Operand::CU32I32, temp->value(ctx), source->value(ctx));
                            ctx.function->appendCode(Operand::CI32F32, castValue->value(ctx), temp->value(ctx));
                        }
                            break;
                        case Int32:
                            ctx.function->appendCode(Operand::CI32F32, castValue->value(ctx), source->value(ctx));
                            break;
                        case Int64:
                        {
                            auto temp = ctx.newReg(getNativeTypeDef(Int32), 0);
                            ctx.function->appendCode(Operand::MOV, temp->value(ctx), source->value(ctx));
                            ctx.function->appendCode(Operand::CI32F32, castValue->value(ctx), temp->value(ctx));
                        }
                            break;
                        case Float64:
                            ctx.function->appendCode(Operand::CF64F32, castValue->value(ctx), source->value(ctx));
                            break;
                        default:
                            assert(false);
                    }
                    break;
                case Float64:
                    switch(source->def->type())
                    {
                        case UInt32:
                        {
                            auto temp = ctx.newReg(getNativeTypeDef(Int32), 0);
                            ctx.function->appendCode(Operand::CU32I32, temp->value(ctx), source->value(ctx));
                            ctx.function->appendCode(Operand::CI32F64, castValue->value(ctx), temp->value(ctx));
                        }
                            break;
                        case UInt64:
                        {
                            auto temp = ctx.newReg(getNativeTypeDef(Int32), 0);
                            ctx.function->appendCode(Operand::CU32I32, temp->value(ctx), source->value(ctx));
                            ctx.function->appendCode(Operand::CI32F64, castValue->value(ctx), temp->value(ctx));
                        }
                            break;
                        case Int32:
                            ctx.function->appendCode(Operand::CI32F64, castValue->value(ctx), source->value(ctx));
                            break;
                        case Int64:
                        {
                            auto temp = ctx.newReg(getNativeTypeDef(Int32), 0);
                            ctx.function->appendCode(Operand::MOV, temp->value(ctx), source->value(ctx));
                            ctx.function->appendCode(Operand::CI32F64, castValue->value(ctx), temp->value(ctx));
                        }
                            break;
                        case Float64:
                            ctx.function->appendCode(Operand::CF32F64, castValue->value(ctx), source->value(ctx));
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
        {                              \
            case Char:                 \
                return new AotConstNode(std::any_cast<char>(arg1->value()) operator std::any_cast<char>(arg2->value()), getNativeTypeDef(Bool));\
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

    class StringCmp : public ConstexprOperator
    {
        bool _equals;
    public:
        StringCmp(bool equals) : ConstexprOperator(equals ? "==" : "!=")
        {
            _equals = equals;
        }

        AotValue* generateBytecode(CompilerCtx& ctx, AotValue* left, AotValue* right) const override
        {
            AotValue* result = ctx.newReg(getNativeTypeDef(Bool), AotValue::Temp);
            result->def = resType();
            left = ctx.castReg(left);
            right = ctx.castReg(right);

            int16_t fIndex;
            if(_equals)
                fIndex = ctx.script->linkFunction("opr ==(string,string)");
            else
                fIndex = ctx.script->linkFunction("opr !=(string,string)");
            fIndex = -1 - fIndex;
            ctx.function->appendCode(CALL, fIndex);
            ctx.function->appendCode(result->value(ctx));
            ctx.function->appendCode(left->value(ctx));
            ctx.function->appendCode(right->value(ctx));
            return result;
        }

        AotNode* precalculate(AotConstNode* arg1, AotConstNode* arg2) const override
        {
            if(_equals)
                return new AotConstNode(std::any_cast<std::string>(arg1->value()) == std::any_cast<std::string>(arg2->value()), getNativeTypeDef(Bool));
            return new AotConstNode(std::any_cast<std::string>(arg1->value()) != std::any_cast<std::string>(arg2->value()),  getNativeTypeDef(Bool));

            return nullptr;
        }

        const TypeDef* resType() const override
        {
            return getNativeTypeDef(Bool);
        }
    };

    class StringConcat : public ConstexprOperator
    {
    public:
        StringConcat() : ConstexprOperator("+")
        {
        }

        AotValue* generateBytecode(CompilerCtx& ctx, AotValue* left, AotValue* right) const override
        {
            AotValue* result = ctx.newReg(nativeTypes[8], AotValue::Temp | AotValue::HeapRef);
            result->def = resType();
            left = ctx.castReg(left);
            right = ctx.castReg(right);

            int16_t fIndex = -ctx.script->linkFunction("opr +(string,string)") -1;
            ctx.function->appendCode(CALL, fIndex);
            ctx.function->appendCode(result->value(ctx));
            ctx.function->appendCode(left->value(ctx));
            ctx.function->appendCode(right->value(ctx));
            return result;
        }

        AotNode* precalculate(AotConstNode* arg1, AotConstNode* arg2) const override
        {
            return new AotConstNode(std::any_cast<std::string>(arg1->value()) + std::any_cast<std::string>(arg2->value()), nativeTypes[8]);
        }

        const TypeDef* resType() const override
        {
            return getNativeTypes()[8];
        }
    };

    class StringIndex : public ConstexprOperator
    {
    public:
        StringIndex() : ConstexprOperator("[]")
        {
        }

        AotValue* generateBytecode(CompilerCtx& ctx, AotValue* left, AotValue* right) const override
        {
            AotValue* result = ctx.newReg(getNativeTypeDef(Char), AotValue::Temp | AotValue::HeapRef);
            result->def = resType();
            left = ctx.castReg(left);
            right = ctx.castReg(right);

            int16_t fIndex = -ctx.script->linkFunction("opr [](string,uint)") -1;
            ctx.function->appendCode(CALL, fIndex);
            ctx.function->appendCode(result->value(ctx));
            ctx.function->appendCode(left->value(ctx));
            ctx.function->appendCode(right->value(ctx));
            return result;
        }

        AotNode* precalculate(AotConstNode* arg1, AotConstNode* arg2) const override
        {
            return new AotConstNode(std::any_cast<std::string>(arg1->value())[std::any_cast<uint32_t>(arg2->value())], getNativeTypeDef(Char));
        }

        const TypeDef* resType() const override
        {
            return getNativeTypeDef(Char);
        }
    };

    robin_hood::unordered_map<std::string, Operator*> setupNativeOperators()
    {
        robin_hood::unordered_map<std::string, Operator*> oprs;

        auto scalarTypes = {
                getNativeTypeDef(UInt32),
                getNativeTypeDef(Int32),
                getNativeTypeDef(UInt64),
                getNativeTypeDef(Int64),
                getNativeTypeDef(Float32),
                getNativeTypeDef(Float64)
        };
        auto charDef = getNativeTypeDef(Char);
        for(const char* cmpOp : {"==", "!=", "<", ">", "<=", ">="})
            oprs.insert({oprSig(cmpOp, charDef, charDef), new CompareOpr(cmpOp)});
        oprs.insert({"opr ==(string,string)", new StringCmp(true)});
        oprs.insert({"opr !=(string,string)", new StringCmp(false)});
        oprs.insert({"opr +(string,string)", new StringConcat()});
        oprs.insert({"opr [](string,uint)", new StringIndex()});
        for(auto type : scalarTypes)
        {
            oprs.insert({oprSig("+", type, type), new AdditionOpr(type)});
            oprs.insert({oprSig("-", type, type), new SubtractionOpr(type)});
            oprs.insert({oprSig("*", type, type), new MultiplicationOpr(type)});
            oprs.insert({oprSig("/", type, type), new DivisionOpr(type)});
            for(const char* cmpOp : {"==", "!=", "<", ">", "<=", ">="})
                oprs.insert({oprSig(cmpOp, type, type), new CompareOpr(cmpOp)});
            //Add cast operators
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
    }*/

    std::vector<FunctionData> getNativeFunctions()
    {
        std::vector<FunctionData> output;
        output.emplace_back("opr ==(string,string)", "string", (void*)(FunctionHandle<bool, const std::string*, const std::string*>)[](const std::string* a, const std::string* b){
            return *a == *b;
        });
        output.emplace_back("opr !=(string,string)", "string", (void*)(FunctionHandle<bool, const std::string*, const std::string*>)[](const std::string* a, const std::string* b){
            return *a != *b;
        });
        output.emplace_back("opr +(string,string)", "string", (void*)(FunctionHandle<std::string*, const std::string*, const std::string*>)[](const std::string* a, const std::string* b){
            return new std::string(*a + *b);
        });
        output.emplace_back("opr [](string,uint)", "char", (void*)(FunctionHandle<char, const std::string*, uint32_t>)[](const std::string* str, uint32_t index){
            return (*str)[index];
        });
        return output;
    }
}
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
        StringDef() : StructDef("BraneScript::string"){
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
}
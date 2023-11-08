//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_TYPEDEF_H
#define BRANESCRIPT_TYPEDEF_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include "valueType.h"
#include <robin_hood.h>

namespace BraneScript
{
    struct TypeTrait
    {
        std::string signature;
        virtual ~TypeTrait() = default;
    };

    struct TypeDef
    {
        robin_hood::unordered_set<std::string> traits;

        virtual ~TypeDef() = default;

        virtual std::string signature() const = 0;
        virtual bool isRef() const = 0;
        virtual bool isStruct() const = 0;
        virtual bool isFunc() const = 0;

        template<typename T>
        T* as()
        {
            return dynamic_cast<T*>(this);
        }
    };

    struct NativeType : public TypeDef
    {
        std::string name = "void";
        ValueType valueType = ValueType::None;
        bool isRef() const override;
        bool isStruct() const override;
        bool isFunc() const override;
        std::string signature() const override;
    };

    struct ReferenceType : public TypeDef
    {
        std::shared_ptr<const TypeDef> containedType = nullptr;
        bool isRef() const override;
        bool isStruct() const override;
        bool isFunc() const override;
        std::string signature() const override;
    };

    struct StructType : public TypeDef
    {
        std::string name;
        std::vector<std::string> memberNames;
        std::vector<std::shared_ptr<const TypeDef>> memberTypes;
        bool packed = false;

        bool isRef() const override;
        bool isStruct() const override;
        bool isFunc() const override;
        std::string signature() const override;
    };

    struct FunctionType : public TypeDef
    {
        std::shared_ptr<const TypeDef> returnType = nullptr;
        std::vector<std::shared_ptr<const TypeDef>> paramTypes;
        bool isRef() const override;
        bool isStruct() const override;
        bool isFunc() const override;
        std::string signature() const override;
    };
}



#endif //BRANESCRIPT_TYPEDEF_H

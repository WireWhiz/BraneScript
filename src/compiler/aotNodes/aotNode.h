//
// Created by wirewhiz on 17/10/22.
//

#ifndef BRANESCRIPT_AOTNODE_H
#define BRANESCRIPT_AOTNODE_H

#include "valueIndex.h"
#include <cstdint>
#include <type_traits>
#include <vector>
#include <ostream>
#include <memory>

namespace BraneScript
{
    class TypeDef;
    struct FunctionCompilerCtx;

    struct AotValue
    {
        enum : uint8_t
        {
            Const      = 1,
            Constexpr  = 1 << 1,
            Temp       = 1 << 2,
            StackRef   = 1 << 3,
            HeapRef    = 1 << 4,
            ExternalRef = 1 << 5,
            Initialized    = 1 << 6,

        };

        enum CompareType : uint8_t
        {
            NoRes = 0,
            EqualRes,
            NotEqualRes,
            AboveRes,
            GreaterRes,
            AboveEqualRes,
            GreaterEqualRes
        };

        uint8_t flags = 0;
        CompareType compareType = NoRes;
        ValueStorageType storageType = ValueStorageType_Null;
        const TypeDef* type = nullptr;
        uint16_t id = 0;
        uint16_t ptrOffset = 0;
        inline bool isCompare() const { return compareType != NoRes; }
        inline bool isVoid() const { return type == nullptr; }
        inline bool isTemp() const { return flags & Temp; }
        inline bool isGlobal() const { return storageType == ValueStorageType_Global; }
        inline bool isRef() const { return storageType == ValueStorageType_Ptr || storageType == ValueStorageType_DerefPtr; }
        inline bool isStackRef() const { return isRef() && flags & StackRef; }
        inline bool isHeapRef() const { return isRef() && flags & HeapRef; }
        inline bool isExternalRef() const { return isRef() && flags & ExternalRef; }
        bool isScalar() const;
        bool isUnsigned() const;
        bool isInt() const;
        bool isFloat() const;
        bool isStruct() const;
    };

    class AotNode
    {
    protected:
        const TypeDef* _resType = nullptr;
        bool isConstexpr = false;

    public:
        explicit AotNode(const TypeDef* resType);

        virtual ~AotNode() = default;
        AotNode(const AotNode&) = default;

        virtual AotNode* optimize() = 0;

        virtual AotValue* generateBytecode(FunctionCompilerCtx& ctx) const = 0;

        const TypeDef* resType() const;

        template<class T>
        T* as()
        {
            static_assert(std::is_base_of<AotNode, T>());
            return dynamic_cast<T*>(this);
        }

        template<class T>
        bool is()
        {
            static_assert(std::is_base_of<AotNode, T>());
            return dynamic_cast<T*>(this);
        }
    };

    class AotUnaryArgNode : public AotNode
    {
      public:
        std::unique_ptr<AotNode> arg;

        AotUnaryArgNode(AotNode* arg, const TypeDef* resType);

        AotNode* optimize() override;
    };

    class AotBinaryArgNode : public AotNode
    {
      public:
        std::unique_ptr<AotNode> argA;
        std::unique_ptr<AotNode> argB;

        AotBinaryArgNode(AotNode* argA, AotNode* argB, const TypeDef* resType);

        AotNode* optimize() override;
    };

}
#endif //BRANESCRIPT_AOTNODE_H

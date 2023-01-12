//
// Created by wirewhiz on 17/10/22.
//

#include "aotNode.h"
#include "../irFunction.h"
#include "../typeDef.h"
#include <cassert>
#include "../compiler.h"

namespace BraneScript
{
    AotNode::NodeType AotNode::type() const
    {
        return _type;
    }

    AotNode::AotNode(const TypeDef* resType, NodeType type) : _type(type), _resType(resType)
    {

    }

    const TypeDef* AotNode::resType() const
    {
        return _resType;
    }

    const TypeDef* AotNode::dominantArgType(const TypeDef* a, const TypeDef* b)
    {
        assert(a && b);
        if (a->type() == Float64)
            return a;
        if (b->type() == Float64)
            return b;
        if (a->type() == Float32)
            return a;
        if (b->type() == Float32)
            return b;
        if (a->type() == Int32)
            return a;
        if (b->type() == Int32)
            return b;
        return nullptr;
    }

    Value AotValue::value(CompilerCtx& ctx)
    {
        assert(storageType != ValueStorageType_Null);
        assert(compareType == CompareType::NoRes);
        Value value{};
        value.valueType = def->type();
        value.storageType = storageType;
        switch(storageType)
        {
            case ValueStorageType_Ptr:
            case ValueStorageType_Reg:
                if(valueIndex == (uint16_t)-1)
                    valueIndex = ctx.regIndex++;
                    break;
            case ValueStorageType_Const:
                if(valueIndex == (uint16_t)-1)
                    valueIndex = ctx.memIndex++;
                break;
            case ValueStorageType_DerefPtr:
                assert(valueIndex != (uint16_t)-1);
                value.offset = ptrOffset;
                break;
            case ValueStorageType_Global:
                break;
            default:
                assert(false);
        }
        value.index = valueIndex;
        return value;
    }
}
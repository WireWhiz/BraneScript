//
// Created by eli on 11/13/2022.
//

#include "structDefinition.h"
namespace BraneScript
{
    StructDef::StructDef(std::string name)
    {
        _name = std::move(name);
        _size = 0;
    }

    void StructDef::addMemberVar(std::string name, const TypeDef* type)
    {
        _variables.push_back({std::move(name), (uint16_t)_size, type});
        _size += type->size();
    }

    void StructDef::addMemberVar(std::string name, const TypeDef* type, uint16_t offset)
    {
        _variables.push_back({std::move(name), offset, type});
        _size = offset + type->size();
    }

    void StructDef::padMembers()
    {
        _size = 0;
        uint16_t largestItem = 0;
        for (auto& m: _variables)
        {
            const auto* t = m.type;
            auto mSize = t->size();
            if(m.type->type() == Struct)
            {
                auto sDef = dynamic_cast<const StructDef*>(m.type);
                mSize = sDef->alignment();
            }
            auto padding = _size % mSize;
            if(padding)
                _size += mSize - padding;
            largestItem = std::max(largestItem, mSize);

            m.offset = _size;
            _size += t->size();
        }
        _size += largestItem - (_size % largestItem);
    }

    void StructDef::packMembers()
    {
        _size = 0;
        for (auto& m: _variables)
        {
            const auto* t = m.type;
            m.offset = _size;
            _size += t->size();
        }
    }

    const StructVar* StructDef::getMemberVar(const std::string& name) const
    {
        for (const auto& m: _variables)
            if (name == m.name)
                return &m;
        return nullptr;
    }

    const std::vector<StructVar>& StructDef::memberVars() const
    {
        return _variables;
    }

    const char* StructDef::name() const
    {
        return _name.c_str();
    }

    uint16_t StructDef::size() const
    {
        return _size;
    }

    ValueType StructDef::type() const
    {
        return Struct;
    }

    void StructDef::setConstructor(FunctionHandle<void, void*> f)
    {
        _constructor = f;
    }

    void StructDef::setCopyConstructor(FunctionHandle<void, void*, void*> f)
    {
        _copyConstructor = f;
    }

    void StructDef::setMoveConstructor(FunctionHandle<void, void*, void*> f)
    {
        _moveConstructor = f;
    }

    void StructDef::setDestructor(FunctionHandle<void, void*> f)
    {
        _destructor = f;
    }

    FunctionHandle<void, void*> StructDef::constructor() const
    {
        return _constructor;
    }

    FunctionHandle<void, void*, void*> StructDef::copyConstructor() const
    {
        return _copyConstructor;
    }

    FunctionHandle<void, void*, void*> StructDef::moveConstructor() const
    {
        return _moveConstructor;
    }

    FunctionHandle<void, void*> StructDef::destructor() const
    {
        return _destructor;
    }

    uint16_t StructDef::alignment() const
    {
        uint16_t largest = 0;
        for(auto& m : _variables)
        {
            if(m.type->type() != Struct)
                largest = std::max(largest, m.type->size());
            else
                largest = std::max(largest, dynamic_cast<const StructDef*>(m.type)->alignment());
        }
        if(largest == 0)
            return 1;
        return largest;
    }
}

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

    void StructDef::addMemberVar(std::string name, TypeDef* type)
    {
        _variables.push_back({std::move(name), (uint16_t)_size, type});
        _size += type->size();
    }

    void StructDef::addMemberVar(std::string name, TypeDef* type, uint16_t offset)
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
            auto mSize = std::min<uint16_t>(t->size(), 8);
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
}

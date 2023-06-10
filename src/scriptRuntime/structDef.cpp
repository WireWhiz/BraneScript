//
// Created by eli on 11/13/2022.
//

#include "structDef.h"

namespace BraneScript
{
    StructDef::StructDef(std::string name,
                         FuncRef<void, void*> constructor,
                         FuncRef<void, void*, const void*> copyConstructor,
                         FuncRef<void, void*, void*> moveConstructor,
                         FuncRef<void, void*> destructor)
        : constructor(constructor), destructor(destructor), copyConstructor(copyConstructor),
          moveConstructor(moveConstructor)
    {
        this->name = std::move(name);
        storageType = ValueType::Struct;
    }

    size_t StructDef::getMemberIndex(const std::string& name) const
    {
        size_t index = 0;
        for(const auto& m : memberVars)
        {
            if(name == m.name)
                return index;
            ++index;
        }
        return -1;
    }
} // namespace BraneScript

//
// Created by eli on 11/13/2022.
//

#ifndef BRANESCRIPT_STRUCTDEF_H
#define BRANESCRIPT_STRUCTDEF_H

#include <vector>
#include "funcRef.h"
#include "typeDef.h"
#include "varType.h"
#include "robin_hood.h"

namespace BraneScript
{
    struct StructVar
    {
        std::string name;
        VarType type;
        size_t offset = 0;
    };

    struct StructDef : public TypeDef
    {
        std::vector<StructVar> memberVars;
        FuncRef<void, void*> constructor;
        FuncRef<void, void*, const void*> copyConstructor;
        FuncRef<void, void*, void*> moveConstructor;
        FuncRef<void, void*> destructor;
        robin_hood::unordered_set<std::string> tags;

        StructDef(std::string name,
                  FuncRef<void, void*> constructor,
                  FuncRef<void, void*, const void*> copyConstructor,
                  FuncRef<void, void*, void*> moveConstructor,
                  FuncRef<void, void*> destructor);

        size_t getMemberIndex(const std::string& name) const;
    };
} // namespace BraneScript


#endif // BRANESCRIPT_STRUCTDEF_H

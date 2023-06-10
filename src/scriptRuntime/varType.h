//
// Created by wirewhiz on 6/8/23.
//

#ifndef BRANESCRIPT_VARMETADATA_H
#define BRANESCRIPT_VARMETADATA_H

#include "typeDef.h"

namespace BraneScript
{
    struct VarType
    {
        TypeDef* def = nullptr;
        bool isRef = false;
    };
}


#endif // BRANESCRIPT_VARMETADATA_H

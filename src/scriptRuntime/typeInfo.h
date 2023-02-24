//
// Created by eli on 11/23/2022.
//

#ifndef BRANESCRIPT_TYPEINFO_H
#define BRANESCRIPT_TYPEINFO_H

#include <string>

namespace BraneScript
{
    struct TypeInfo
    {
        std::string type;
        bool isConst = false;
        bool isRef = false;
    };
}

#endif //BRANESCRIPT_TYPEINFO_H

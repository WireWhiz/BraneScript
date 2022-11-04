//
// Created by eli on 11/4/2022.
//

#ifndef BRANESCRIPT_LIBRARY_H
#define BRANESCRIPT_LIBRARY_H

#include <unordered_map>

namespace BraneScript
{
    class Library
    {
        std::unordered_map<std::string, void*> _functions;
    public:

    };
}

#endif //BRANESCRIPT_LIBRARY_H

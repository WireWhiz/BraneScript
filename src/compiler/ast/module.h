//
// Created by wirewhiz on 10/8/23.
//

#ifndef BRANESCRIPT_MODULE_H
#define BRANESCRIPT_MODULE_H

#include <vector>
#include <string>
#include <robin_hood.h>

struct Definition
{
    virtual ~Definition() = default;
};

struct Module
{
    std::string name;
    std::vector<std::string> importedModules;
    robin_hood::unordered_map<std::string, Definition> defines;
};


#endif // BRANESCRIPT_MODULE_H

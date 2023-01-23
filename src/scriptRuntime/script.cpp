//
// Created by wirewhiz on 14/10/22.
//

#include "script.h"

void BraneScript::Script::init()
{
    if(globalVars.empty())
        return;
    auto constructor = getFunction<void>("_construct()");
    if(!constructor)
        throw std::runtime_error("Script has global vars but no constructor!");
    constructor();
}

BraneScript::Script::~Script()
{
    if(globalVars.empty())
        return;
    auto destructor = getFunction<void>("_destruct()");
    if(!destructor)
        throw std::runtime_error("Script has global vars but no destructor! This may result in memory leaks!");
    destructor();
}

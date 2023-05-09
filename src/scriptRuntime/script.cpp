//
// Created by wirewhiz on 14/10/22.
//

#include "script.h"
#include "llvm/ExecutionEngine/Orc/Core.h"

BraneScript::Script::Script(llvm::orc::JITDylib& lib) : lib(lib){}

BraneScript::Script::~Script()
{
    if(globalVars.empty())
        return;
    if(destructor)
        destructor();
    if(auto err = rt->remove())
        throw std::runtime_error("Error deallocating script resources: " + toString(std::move(err)));
}

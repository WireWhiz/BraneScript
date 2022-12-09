//
// Created by eli on 10/27/2022.
//

#include "testing.h"
#include "../src/compiler.h"

namespace BraneScript
{
    void checkCompileErrors(Compiler& c)
    {
        EXPECT_TRUE(c.errors().empty()) << "Compiler errors were detected";
        if(c.errors().empty())
            return;
        for(auto& compileError: c.errors())
            std::cerr << compileError << std::endl;
    }

}


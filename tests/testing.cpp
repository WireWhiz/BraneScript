//
// Created by eli on 10/27/2022.
//

#include "testing.h"
#include "compiler.h"

namespace BraneScript
{
    void checkCompileErrors(StaticAnalyzer& analyzer, const std::string& testString)
    {
        if(!analyzer.getCtx("test")->errors.empty())
        {
            for(auto& error : analyzer.getCtx("test")->errors)
            {
                auto bounds = error.range.getBoundsForText(testString);
                std::cerr << "(" << bounds.first << ", " << bounds.second << ") " << error.message << std::endl;
            }
            ASSERT_TRUE(false);
        }
    }
}


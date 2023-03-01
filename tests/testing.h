//
// Created by eli on 10/27/2022.
//

#ifndef BRANESCRIPT_TESTING_H
#define BRANESCRIPT_TESTING_H

#include <gtest/gtest.h>
#include "staticAnalysis/staticAnalyzer.h"

namespace BraneScript
{
    class Compiler;
    void checkCompileErrors(StaticAnalyzer& analyzer, const std::string& testString);
}

#endif //BRANESCRIPT_TESTING_H

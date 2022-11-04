//
// Created by eli on 10/27/2022.
//

#ifndef BRANESCRIPT_TESTING_H
#define BRANESCRIPT_TESTING_H

#include <gtest/gtest.h>

namespace BraneScript
{
    class Compiler;
    void checkCompileErrors(Compiler& c);
}

#endif //BRANESCRIPT_TESTING_H

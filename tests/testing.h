//
// Created by eli on 10/27/2022.
//

#ifndef BRANESCRIPT_TESTING_H
#define BRANESCRIPT_TESTING_H

#include <gtest/gtest.h>
#include "staticAnalysis/staticAnalyzer.h"

#define checkCompileErrors(analyzer, testString) \
    {\
        if(!analyzer.getCtx("test")->errors.empty())\
        {\
            for(auto& error : analyzer.getCtx("test")->errors)\
            {\
                auto bounds = error.range.getBoundsForText(testString);\
                std::cerr << "(" << bounds.first << ", " << bounds.second << ") " << error.message << std::endl;\
            }\
            ASSERT_TRUE(false);\
        }\
    }\

#endif //BRANESCRIPT_TESTING_H

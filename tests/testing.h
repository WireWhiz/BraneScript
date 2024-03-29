//
// Created by eli on 10/27/2022.
//

#ifndef BRANESCRIPT_TESTING_H
#define BRANESCRIPT_TESTING_H

#include <gtest/gtest.h>
#include "analyzer.h"

#define checkCompileErrors(analyzer, path) \
    {\
        if(!analyzer.getCtx(path)->errors.empty())\
        {\
            for(auto& error : analyzer.getCtx(path)->errors)\
            {\
                auto bounds = error.range;\
                std::cerr << "(" << bounds.start.line << ", " << bounds.start.charPos << ") " << error.message << std::endl;\
            }\
            ASSERT_TRUE(false);\
        }\
    }\

#endif //BRANESCRIPT_TESTING_H

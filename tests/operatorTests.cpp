
#include "testing.h"

#include "../scripting/compiler.h"
#include "../scripting/scriptRuntime.h"
#include "../scripting/script.h"

#define TEST_DUAL_ARG_OPERATOR(operator, function, argList)     \
    for(auto& argPair : argList)                                \
        EXPECT_EQ(function(argPair.first, argPair.second), argPair.first operator argPair.second);

TEST(OperatorTests, AddSub)
{
    std::string testString = R"(
    int testIntAdd(int a, int b)
    {
        return a + b;
    }
    float testFloatAdd(float a, float b)
    {
        return a + b;
    }
    float testIntFloatAdd(int a, float b)
    {
        return a + b;
    }
    int testIntSub(int a, int b)
    {
        return a - b;
    }
    float testFloatSub(float a, float b)
    {
        return a - b;
    }
    float testIntFloatSub(int a, float b)
    {
        return a - b;
    }
)";

    Compiler compiler;
    auto* ir = compiler.compile(testString);

    ScriptRuntime rt;
    Script* testScript = rt.assembleScript(ir);

    std::vector<std::pair<int32_t, int32_t>>     intTestArgs =   {{0, 1},{1, 1},{2, 3}, {3, 3}, {123451, 12332169}, {0, -1}, {-1234123, 12341612}};
    std::vector<std::pair<float, float>>         floatTestArgs = {{0.0f, 1.0f},{1.0f, 1.0f},{2.4f, 3.2f}, {3.0f, 3.0f}, {123451.0f, 12332169.0f}, {0.0f, -1.0f}, {-1234123.126414f, 12341612.4123f}};
    std::vector<std::pair<int32_t, float>>       intFloatTestArgs = {{0.0f, 1.0f},{1.0f, 1.0f},{2.0f, 3.0f}, {3.0f, 3.0f}, {123451.0f, 12332169.0f}, {0.0f, -1.0f}, {-1234123.0f, 12341612.0f}};

    auto testIntAdd = testScript->getFunction<int, int, int>("testIntAdd");
    TEST_DUAL_ARG_OPERATOR(+, testIntAdd, intTestArgs);
    auto testIntSub = testScript->getFunction<int, int, int>("testIntSub");
    TEST_DUAL_ARG_OPERATOR(-, testIntSub, intTestArgs);

    auto testFloatAdd = testScript->getFunction<float, float, float>("testFloatAdd");
    TEST_DUAL_ARG_OPERATOR(+, testFloatAdd, floatTestArgs);
    auto testFloatSub = testScript->getFunction<float, float, float>("testFloatSub");
    TEST_DUAL_ARG_OPERATOR(-, testFloatSub, floatTestArgs);

    auto testIntFloatAdd = testScript->getFunction<float, int, float>("testIntFloatAdd");
    TEST_DUAL_ARG_OPERATOR(+, testIntFloatAdd, intFloatTestArgs);
    auto testIntFloatSub = testScript->getFunction<float, int, float>("testIntFloatSub");
    TEST_DUAL_ARG_OPERATOR(-, testIntFloatSub, intFloatTestArgs);

}
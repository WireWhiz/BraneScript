
#include "testing.h"

#include "../src/compiler.h"
#include "../src/scriptRuntime.h"
#include "../src/script.h"
#include "../src/linker.h"

using namespace BraneScript;

#define TEST_DUAL_ARG_OPERATOR(operator, function, argList)     \
    for(auto& argPair : argList)                                \
        EXPECT_EQ(function(argPair.first, argPair.second), argPair.first operator argPair.second) << "Operation args: " << argPair.first << ", " << argPair.second << std::endl;

TEST(BraneScript, Operators)
{
    std::string testString = R"(

    //Addition/Subtraction
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

    //Multiplication/division
    int testIntMul(int a, int b)
    {
        return a * b;
    }
    float testFloatMul(float a, float b)
    {
        return a * b;
    }
    int testIntDiv(int a, int b)
    {
        return a / b;
    }
    float testFloatDiv(float a, float b)
    {
        return a / b;
    }

    //Casting
    bool testBoolCast(int a, int b)
    {
        return a > b;
    }
    float testFloatCast(int a)
    {
        return a;
    }
    int testIntCast(float a)
    {
        return a;
    }
)";

    Linker l;
    Compiler compiler(&l);
    auto* ir = compiler.compile(testString);
    checkCompileErrors(compiler);
    ASSERT_TRUE(ir);

    ScriptRuntime rt;
    Script* testScript = rt.assembleScript(ir);
    ASSERT_TRUE(testScript);

    std::vector<std::pair<int32_t, int32_t>>     intTestArgs =   {{0, 1},{1, 1},{2, 3}, {3, 3}, {123451, 12332169}, {0, -1}, {-1234123, 12341612}};
    std::vector<std::pair<float, float>>         floatTestArgs = {{0.0f, 1.0f},{1.0f, 1.0f},{2.4f, 3.2f}, {3.0f, 3.0f}, {123451.0f, 12332169.0f}, {0.0f, -1.0f}, {-1234123.126414f, 12341612.4123f}};
    std::vector<std::pair<int32_t, float>>       intFloatTestArgs = {{0, 1.0f},{1, 1.0f},{2, 3.0f}, {3, 3.0f}, {123451, 12332169.0f}, {0, -1.0f}, {-1234123, 12341612.0f}};

    //Addition/subtraction
    auto testIntAdd = testScript->getFunction<int, int, int>("testIntAdd");
    ASSERT_TRUE(testIntAdd);
    TEST_DUAL_ARG_OPERATOR(+, testIntAdd, intTestArgs);
    auto testIntSub = testScript->getFunction<int, int, int>("testIntSub");
    ASSERT_TRUE(testIntSub);
    TEST_DUAL_ARG_OPERATOR(-, testIntSub, intTestArgs);

    auto testFloatAdd = testScript->getFunction<float, float, float>("testFloatAdd");
    ASSERT_TRUE(testFloatAdd);
    TEST_DUAL_ARG_OPERATOR(+, testFloatAdd, floatTestArgs);
    auto testFloatSub = testScript->getFunction<float, float, float>("testFloatSub");
    ASSERT_TRUE(testFloatSub);
    TEST_DUAL_ARG_OPERATOR(-, testFloatSub, floatTestArgs);

    auto testIntFloatAdd = testScript->getFunction<float, int, float>("testIntFloatAdd");
    ASSERT_TRUE(testIntFloatAdd);
    TEST_DUAL_ARG_OPERATOR(+, testIntFloatAdd, intFloatTestArgs);
    auto testIntFloatSub = testScript->getFunction<float, int, float>("testIntFloatSub");
    ASSERT_TRUE(testIntFloatSub);
    TEST_DUAL_ARG_OPERATOR(-, testIntFloatSub, intFloatTestArgs);

    //Multiplication/division
    auto testIntMul = testScript->getFunction<int, int, int>("testIntMul");
    EXPECT_TRUE(testIntMul);
    TEST_DUAL_ARG_OPERATOR(*, testIntMul, intTestArgs);
    auto testIntDiv = testScript->getFunction<int, int, int>("testIntDiv");
    EXPECT_TRUE(testIntDiv);
    for(auto& argPair : intTestArgs)
        testIntDiv(argPair.first, argPair.second);
    TEST_DUAL_ARG_OPERATOR(/, testIntDiv, intTestArgs);

    auto testFloatMul = testScript->getFunction<float, float, float>("testFloatMul");
    EXPECT_TRUE(testFloatMul);
    TEST_DUAL_ARG_OPERATOR(*, testFloatMul, floatTestArgs);
    auto testFloatDiv = testScript->getFunction<float, float, float>("testFloatDiv");
    EXPECT_TRUE(testFloatDiv);
    TEST_DUAL_ARG_OPERATOR(/, testFloatDiv, floatTestArgs);

    //Casting
    auto testBoolCast = testScript->getFunction<bool, int, int>("testBoolCast");
    EXPECT_TRUE(testBoolCast);
    EXPECT_TRUE(testBoolCast(5, 3));
    EXPECT_FALSE(testBoolCast(2,4));

    auto testFloatCast = testScript->getFunction<float, int>("testFloatCast");
    EXPECT_TRUE(testFloatCast);
    EXPECT_EQ(testFloatCast(23), 23);
    auto testIntCast = testScript->getFunction<int, float>("testIntCast");
    EXPECT_TRUE(testIntCast);
    EXPECT_EQ(testIntCast(23.23f), 23);

}
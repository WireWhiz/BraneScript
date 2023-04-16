#include "testing.h"

#include "compiler.h"
#include "linker.h"
#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

TEST(BraneScript, Templates)
{
    std::string testString = R"(
    link "BraneScript";

    template<type Arg1, type Arg2>
    Arg1 add(Arg1 a, Arg2 b)
    {
        return a + b;
    }

    int addIntExplicit(int a, int b)
    {
        return add<int, int>(a, b);
    }

    int addIntExplicit2(int a, int b)
    {
        return add<int, int>(a, b) + add<int, int>(a, b);
    }

    float addFloatExplicit(float a, float b)
    {
        return add<float, float>(a, b);
    }

    template<type T1, type T2>
    struct TestPair
    {
        T1 first;
        T2 second;
    }

    TestPair<int, float> generatePair(int a, float b)
    {
        TestPair<int, float> output;
        output.first = a;
        output.second = b;
        return output;
    }

    template<type T>
    T sumRecursive(T value)
    {
        return value;
    }

    template<type T, type... Args>
    T sumRecursive(T value, Args... args)
    {
        return value + sumRecursive<Args...>(args...);
    }

    int sum4(int v1, int v2, int v3, int v4)
    {
        return sumRecursive<int, int, int, int>(v1, v2, v3, v4);
    }
)";
    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    Compiler compiler;
    auto* ir = compiler.compile(analyzer.getCtx("test")->scriptContext.get());
    ASSERT_TRUE(ir);

    /* Make sure that the amount of functions generated is what we expect (make sure there are no duplicate template instances)
     * getter functions = 4
     * global function template instances = 2
     * template struct constructors = 4
     */
    EXPECT_EQ(ir->localFunctions.size(), 15);

    ScriptRuntime rt;
    Script* testScript = rt.loadScript(ir);
    delete ir;
    ASSERT_TRUE(testScript);

    auto addIntExplicit = testScript->getFunction<int, int, int>("addIntExplicit");
    ASSERT_TRUE(addIntExplicit);
    EXPECT_EQ(addIntExplicit(2, 4), 6);

    //Make sure templates are only instantiated once
    auto addIntExplicit2 = testScript->getFunction<int, int, int>("addIntExplicit2");
    ASSERT_TRUE(addIntExplicit2);
    EXPECT_EQ(addIntExplicit2(4, 5), 18);

    auto addFloatExplicit = testScript->getFunction<float, float, float>("addFloatExplicit");
    ASSERT_TRUE(addFloatExplicit);
    EXPECT_EQ(addFloatExplicit(2.0f, 4.0f), 6.0f);

    using TestPair = std::pair<int, float>;
    TestPair testPair{};
    auto generatePair = testScript->getFunction<void, TestPair*, int, float>("generatePair(ref TestPair<int,float>,int,float)");
    ASSERT_TRUE(generatePair);
    generatePair(&testPair, 32, 42.0f);
    EXPECT_EQ(testPair.first, 32);
    EXPECT_EQ(testPair.second, 42.0f);

    auto sum4 = testScript->getFunction<int, int, int, int, int>("sum4");
    ASSERT_TRUE(sum4);
    EXPECT_EQ(sum4(1, 2, 3, 4), 10);
}

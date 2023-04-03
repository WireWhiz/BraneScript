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

/*  Add this back in when we add in template arg inference
    int addInt(int a, int b)
    {
        return add(a, b);
    }
*/

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

    /*template<T...>
    int sumFlat(T... args)
    {

    }*/
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
    EXPECT_EQ(ir->localFunctions.size(), 10);

    ScriptRuntime rt;
    Script* testScript = rt.assembleScript(ir);
    delete ir;
    ASSERT_TRUE(testScript);

    /*auto addInt = testScript->getFunction<int, int, int>("addInt");
    ASSERT_TRUE(addInt);
    EXPECT_EQ(addInt(5, 5), 10);*/

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
    auto generatePair = testScript->getFunction<TestPair*, int, float>("generatePair");
    ASSERT_TRUE(generatePair);
    TestPair*  testPair = generatePair(32, 42.0f);
    ASSERT_TRUE(testPair);
    EXPECT_EQ(testPair->first, 32);
    EXPECT_EQ(testPair->second, 42.0f);
    delete testPair;
}

#include "testing.h"

#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/constexprEvaluator.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

TEST(BraneScript, Templates)
{
    std::string testString = R"(
    module "tests"
    {
        template<typedef Arg1, typedef Arg2>
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

        template<typedef T1, typedef T2>
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

        template<typedef T, typedef... Args>
        T sumRecursive(T value, Args... args)
        {
            if(sizeof...(Args) != 0)
                return value + sumRecursive<Args...>(args...);
            return value;
        }

        int sum4(int v1, int v2, int v3, int v4)
        {
            return sumRecursive<int, int, int, int>(v1, v2, v3, v4);
        }

        template<int i>
        int sumTemplate()
        {
            if(i > 1)
                return i + sumTemplate<i - 1>();
            return 1;
        }

        int testTemplateExprArg()
        {
            return sumTemplate<6>();
        }
    }
)";
    ConstexprEvaluator evaluator;
    StaticAnalyzer analyzer;
    analyzer.setConstexprEvaluator(&evaluator);
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    auto ir = analyzer.compile("test");
    ASSERT_TRUE(ir.modules.contains("tests"));

    /* Make sure that the amount of functions generated is what we expect (make sure there are no duplicate template instances)
     * getter functions = 4
     * global function template instances = 2
     * template struct constructors = 4
     */
    EXPECT_EQ(ir.modules.at("tests").functions.size(), 24);

    ScriptRuntime rt;
    rt.resetMallocDiff();
    Module* testScript = rt.loadModule(ir.modules.at("tests"));
    ASSERT_TRUE(testScript);


    auto addIntExplicit = testScript->getFunction<int, int, int>("tests::addIntExplicit");
    ASSERT_TRUE(addIntExplicit);
    EXPECT_EQ(addIntExplicit(2, 4), 6);

    //Make sure templates are only instantiated once
    auto addIntExplicit2 = testScript->getFunction<int, int, int>("tests::addIntExplicit2");
    ASSERT_TRUE(addIntExplicit2);
    EXPECT_EQ(addIntExplicit2(4, 5), 18);

    auto addFloatExplicit = testScript->getFunction<float, float, float>("tests::addFloatExplicit");
    ASSERT_TRUE(addFloatExplicit);
    EXPECT_EQ(addFloatExplicit(2.0f, 4.0f), 6.0f);

    using TestPair = std::pair<int, float>;
    TestPair testPair{};
    auto generatePair = testScript->getFunction<void, TestPair*, int, float>("tests::generatePair(ref tests::TestPair<int,float>,int,float)");
    ASSERT_TRUE(generatePair);
    generatePair(&testPair, 32, 42.0f);
    EXPECT_EQ(testPair.first, 32);
    EXPECT_EQ(testPair.second, 42.0f);

    auto sum4 = testScript->getFunction<int, int, int, int, int>("tests::sum4");
    ASSERT_TRUE(sum4);
    EXPECT_EQ(sum4(1, 2, 3, 4), 10);

    auto testTemplateExprArg = testScript->getFunction<int>("tests::testTemplateExprArg");
    ASSERT_TRUE(testTemplateExprArg);
    EXPECT_EQ(testTemplateExprArg(), 6 + 5 + 4 + 3 + 2 + 1);
}

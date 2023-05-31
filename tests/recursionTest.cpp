#include "testing.h"

#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

TEST(BraneScript, Recursion)
{
    std::string testString = R"(
    module "tests"
    {
        int called1(int in)
        {
            return in;
        }
        int caller1(int in)
        {
            return called1(in);
        }

        //recursively calculate x to the nth power
        int pow(int x, int n)
        {
            if(n == 1)
                return x;
            return x * pow(x, n - 1);
        }
    }
)";
    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    auto ir = analyzer.compile("test");
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    Module* testScript = rt.loadModule(ir.modules.at("tests"));
    ASSERT_TRUE(testScript);

    auto f0 = testScript->getFunction<int, int>("tests::caller1");
    ASSERT_TRUE(f0);
    EXPECT_EQ(f0(5), 5);

    auto pow = testScript->getFunction<int, int, int>("tests::pow");
    ASSERT_TRUE(pow);
    EXPECT_EQ(pow(2, 4), 16);
}


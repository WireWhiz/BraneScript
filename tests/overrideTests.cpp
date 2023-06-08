

#include "testing.h"

#include "script.h"
#include "scriptRuntime.h"
#include "analyzer.h"

using namespace BraneScript;

TEST(BraneScript, Overrides)
{
    Analyzer analyzer;
    std::string path = "testScripts/overrideTests.bs";
    analyzer.load(path);
    analyzer.validate(path);
    checkCompileErrors(analyzer, path);

    auto ir = analyzer.compile(path, CompileFlags_DebugInfo);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    Module* testScript = rt.loadModule(ir.modules.at("tests"));
    ASSERT_TRUE(testScript);

    auto f0 = testScript->getFunction<int>("tests::func");
    ASSERT_TRUE(f0);
    EXPECT_EQ(f0(), 0);

    auto f1 = testScript->getFunction<int, int>("tests::func");
    ASSERT_TRUE(f1);
    EXPECT_EQ(f1(0), 1);

    auto f2 = testScript->getFunction<int, int, float>("tests::func");
    ASSERT_TRUE(f2);
    EXPECT_EQ(f2(0, 0.0f), 2);

    auto f3 = testScript->getFunction<bool, int, float, bool>("tests::func");
    ASSERT_TRUE(f3);
    EXPECT_TRUE(f3(0, 0.0f, true));

    auto f4 = testScript->getFunction<int, float>("tests::func");
    EXPECT_FALSE(f4);
}

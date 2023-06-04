#include "testing.h"

#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

TEST(BraneScript, Recursion)
{
    StaticAnalyzer analyzer;
    std::string path = "testScripts/recursionTest.bs";
    analyzer.load(path);
    analyzer.validate(path);
    checkCompileErrors(analyzer, path);

    auto ir = analyzer.compile(path, CompileFlags_DebugInfo);
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


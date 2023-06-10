

#include "testing.h"

#include "script.h"
#include "scriptRuntime.h"
#include "analyzer.h"

using namespace BraneScript;

TEST(BraneScript, GlobalVariables)
{
    Analyzer analyzer;
    std::string path = "testScripts/globalVariableTests.bs";
    analyzer.load(path);
    analyzer.validate(path);
    checkCompileErrors(analyzer, path);

    auto ir = analyzer.compile(path, CompileFlags_DebugInfo);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    auto testScript = rt.loadModule(ir.modules.at("tests"));

    auto setInt = testScript->getFunction<void, int>("tests::setInt");
    ASSERT_TRUE(setInt);
    setInt(42);

    auto setFloat = testScript->getFunction<void, float>("tests::setFloat");
    ASSERT_TRUE(setFloat);
    setFloat(42.0f);

    auto setStructVar = testScript->getFunction<void, int>("tests::setStructVar");
    ASSERT_TRUE(setStructVar);
    setStructVar(32);

    auto getInt = testScript->getFunction<int>("tests::getInt");
    ASSERT_TRUE(getInt);
    EXPECT_EQ(getInt(), 42);

    auto getFloat = testScript->getFunction<float>("tests::getFloat");
    ASSERT_TRUE(getFloat);
    EXPECT_EQ(getFloat(), 42.0f);

    auto getStructVar = testScript->getFunction<int>("tests::getStructVar");
    ASSERT_TRUE(getStructVar);
    EXPECT_EQ(getStructVar(), 32);
}

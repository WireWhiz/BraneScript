#include "testing.h"

#include <iostream>
#include "script.h"
#include "scriptRuntime.h"
#include "analyzer.h"

using namespace BraneScript;

struct TestStruct
{
    int x;
    float y;
};

TEST(BraneScript, UnsafeTests)
{

    Analyzer analyzer;
    std::string path = "testScripts/unsafeTests.bs";
    analyzer.load(path);
    analyzer.validate(path, false);
    EXPECT_GT(analyzer.getCtx(path)->errors.size(), 0);
    analyzer.validate(path, true);
    checkCompileErrors(analyzer, path)

    auto ir = analyzer.compile(path, CompileFlags_DebugInfo);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    auto testScript = rt.loadModule(ir.modules.at("tests"));

    auto allocStruct = testScript->getFunction<TestStruct*>("tests::allocStruct()");
    ASSERT_TRUE(allocStruct);
    TestStruct* testStruct = allocStruct();
    ASSERT_TRUE(testStruct);
    ASSERT_EQ(testStruct->x, 2);
    ASSERT_EQ(testStruct->y, 2.0f);

    auto deleteStruct = testScript->getFunction<void, TestStruct*>("tests::deleteStruct(ref tests::TestStruct)");
    ASSERT_TRUE(deleteStruct);
    deleteStruct(testStruct);
    ASSERT_EQ(rt.mallocDiff(), 0);
}
#include "testing.h"

#include <iostream>
#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

struct TestStruct
{
    int x;
    float y;
};

TEST(BraneScript, UnsafeTests)
{

    std::string testString = R"(
    link "unsafe";
    export as "tests"
    {
        struct TestStruct
        {
            int x;
            float y;
        }

        ref TestStruct allocStruct()
        {
            ref TestStruct ts <- malloc<TestStruct>();
            TestStruct::_construct(ts);
            ts.x = 2;
            ts.y = 2.0f;
            return ts;
        }

        void deleteStruct(ref TestStruct ts)
        {
            free(ts);
        }
    }
)";
    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.validate("test", false);
    EXPECT_GT(analyzer.getCtx("test")->errors.size(), 0);

    analyzer.validate("test", true);
    checkCompileErrors(analyzer, testString)

    llvm::LLVMContext ctx;
    auto ir = analyzer.getCtx("test")->scriptContext->compile(&ctx, false);

    ScriptRuntime rt;
    rt.resetMallocDiff();
    Script* testScript = rt.loadScript(ir);
    ASSERT_TRUE(testScript);

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
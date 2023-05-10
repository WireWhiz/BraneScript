#include "testing.h"

#include <iostream>
#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

TEST(BraneScript, Refs)
{

    std::string testString = R"(

    export as "tests"
    {
        int testValue;

        ref int getInt()
        {
            return testValue;
        }

        void addOne(ref int value)
        {
            value = value + 1;
        }

        int addOneCall()
        {
            int testValue = 0;
            addOne(testValue);
            return testValue;
        }

        void addOneToRef(ref int value)
        {
            addOne(value);
        }
    }
)";
    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    llvm::LLVMContext ctx;
    auto ir = analyzer.getCtx("test")->scriptContext->compile(&ctx, false, true);

    ScriptRuntime rt;
    Script* testScript = rt.loadScript(ir);
    ASSERT_TRUE(testScript);

    auto getInt = testScript->getFunction<int*>("tests::getInt()");
    ASSERT_TRUE(getInt);

    int* testValue = getInt();
    ASSERT_EQ(testScript->getGlobal<int>("tests::testValue"), testValue);
    *testValue = 1;

    auto addOne = testScript->getFunction<void, int*>("tests::addOne");
    ASSERT_TRUE(addOne);
    addOne(testValue);
    ASSERT_EQ(*testValue, 2);

    auto addOneCall = testScript->getFunction<int>("tests::addOneCall");
    ASSERT_TRUE(addOneCall);
    ASSERT_EQ(addOneCall(), 1);

    auto addOneToRef = testScript->getFunction<void, int*>("tests::addOneToRef");
    ASSERT_TRUE(addOneToRef);
    *testValue = 0;
    addOneToRef(testValue);
    ASSERT_EQ(*testValue, 1);
}
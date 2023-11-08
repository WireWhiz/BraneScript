#include "testing.h"

#include <iostream>
#include "script.h"
#include "scriptRuntime.h"
#include "analyzer.h"

using namespace BraneScript;

TEST(BraneScript, Refs)
{
    Parser analyzer;
    std::string path = "testScripts/refTests.bs";
    analyzer.load(path);
    analyzer.validate(path);
    checkCompileErrors(analyzer, path);

    auto ir = analyzer.compile(path, CompileFlags_DebugInfo);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    auto testScript = rt.loadModule(ir.modules.at("tests"));

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
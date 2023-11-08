//
// Created by wirewhiz on 5/14/23.
//

#include "testing.h"

#include <iostream>
#include "script.h"
#include "scriptRuntime.h"
#include "analyzer.h"

using namespace BraneScript;

int addTwo(int a)
{
    return a + 2;
}

TEST(BraneScript, FunctionRefs)
{
    Parser analyzer;
    std::string path = "testScripts/functionRefTests.bs";
    analyzer.load(path);
    analyzer.validate(path);
    checkCompileErrors(analyzer, path);

    auto ir = analyzer.compile(path, CompileFlags_DebugInfo);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    ResourceHandle<Module> testScript = rt.loadModule(ir.modules.at("tests"));

    auto setGlobalFunctionExt = testScript->getFunction<void, int(*)(int)>("tests::setGlobalFuncExt(FuncRef<int,int>)");
    ASSERT_TRUE(setGlobalFunctionExt);
    setGlobalFunctionExt(addTwo);

    EXPECT_EQ(*testScript->getGlobal<int(*)(int)>("tests::globalFunc"), addTwo);

    auto getGlobalFunction = testScript->getFunction<int(*)(int)>("tests::getGlobalFunc()");
    ASSERT_TRUE(getGlobalFunction);

    EXPECT_EQ(*testScript->getGlobal<int(*)(int)>("tests::globalFunc"), getGlobalFunction());

    auto callGlobalFunction = testScript->getFunction<int, int>("tests::callGlobalFunc");
    ASSERT_TRUE(callGlobalFunction);

    EXPECT_EQ(callGlobalFunction(2), 4);

    auto setGlobalFunctionLoc = testScript->getFunction<void>("tests::setGlobalFuncLoc()");
    ASSERT_TRUE(setGlobalFunctionLoc);
    setGlobalFunctionLoc();

    EXPECT_EQ(callGlobalFunction(2), 3);

    auto testStructRet = testScript->getFunction<int>("tests::testStructRet()");
    ASSERT_TRUE(testStructRet);
    ASSERT_EQ(testStructRet(), 5);
}

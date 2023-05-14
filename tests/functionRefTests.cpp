//
// Created by wirewhiz on 5/14/23.
//

#include "testing.h"

#include <iostream>
#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

int addTwo(int a)
{
    return a + 2;
}

TEST(BraneScript, FunctionRefs)
{

    std::string testString = R"(

    export as "tests"
    {
        FuncRef<int, int> globalFunc;

        void setGlobalFuncExt(FuncRef<int, int> func)
        {
            globalFunc <- func;
        }

        FuncRef<int, int> getGlobalFunc()
        {
            return globalFunc;
        }

        int callGlobalFunc(int value)
        {
            return globalFunc(value);
        }

        // Add multiple functions with the same name, to test function pointer selection
        float addOne(float value)
        {
            return value + 1.0f;
        }

        int addOne(int value)
        {
            return value + 1;
        }

        void setGlobalFuncLoc()
        {
            globalFunc <- addOne;
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
}

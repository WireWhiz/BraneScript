
#include "testing.h"

#include "nativeTypes/bsLambda.h"
#include "nativeTypes/bsString.h"
#include "script.h"
#include "scriptRuntime.h"

using namespace BraneScript;

TEST(BraneScript, ArrayTests)
{
    Analyzer analyzer;
    std::string path = "testScripts/arrayTests.bs";
    analyzer.load(path);
    analyzer.validate(path);
    checkCompileErrors(analyzer, path);

    auto ir = analyzer.compile(path, CompileFlags_DebugInfo | CompileFlags_PrintIR);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    rt.loadDefaultModules();
    auto testScript = rt.loadModule(ir.modules.at("tests"));

    auto setSimpleArray = testScript->getFunction<void, int[], int>("tests::setSimpleArray(ref int[],int)");
    ASSERT_TRUE(setSimpleArray);
    int simpleArray[4] = { 0, 0, 0, 0 };
    setSimpleArray(simpleArray, 4);
    EXPECT_EQ(simpleArray[0], 0);
    EXPECT_EQ(simpleArray[1], 1);
    EXPECT_EQ(simpleArray[2], 2);
    EXPECT_EQ(simpleArray[3], 3);

    auto returnSimpleArray = testScript->getFunction<void, int[]>("tests::returnSimpleArray(ref int[4])");
    ASSERT_TRUE(returnSimpleArray);
    int simpleArray2[4] = { -1, -1, -1, -1 };
    returnSimpleArray(simpleArray2);
    EXPECT_EQ(simpleArray2[0], 0);
    EXPECT_EQ(simpleArray2[1], 1);
    EXPECT_EQ(simpleArray2[2], 2);
    EXPECT_EQ(simpleArray2[3], 3);

    auto returnStringArray = testScript->getFunction<void, BSString[]>("tests::returnStringArray(ref string::string[4])");
    ASSERT_TRUE(returnStringArray);
    BSString stringArray[4];
    returnStringArray(stringArray);
    EXPECT_EQ(stringArray[0], "a");
    EXPECT_EQ(stringArray[1], "b");
    EXPECT_EQ(stringArray[2], "c");
    EXPECT_EQ(stringArray[3], "d");



}
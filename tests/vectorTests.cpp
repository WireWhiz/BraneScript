
#include "testing.h"

#include "src/scriptRuntime/script.h"
#include "src/scriptRuntime/scriptRuntime.h"
#include "analyzer.h"
#include "nativeTypes/bsVector.h"

using namespace BraneScript;

TEST(BraneScript, VectorTests)
{
    Analyzer analyzer;
    std::string path = "testScripts/vectorTests.bs";
    analyzer.load(path);
    analyzer.validate(path);
    checkCompileErrors(analyzer, path);

    auto ir = analyzer.compile(path, CompileFlags_DebugInfo | CompileFlags_PrintIR);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    rt.loadDefaultModules();
    auto testScript = rt.loadModule(ir.modules.at("tests"));

    auto returnSimpleVector = testScript->getFunction<void, BSVector<int>&>("tests::returnSimpleVector(ref vector::Vector<int>)");
    ASSERT_TRUE(returnSimpleVector);
    BSVector<int> simpleVector;
    returnSimpleVector(simpleVector);
    EXPECT_EQ(simpleVector.size(), 3);
    EXPECT_GE(simpleVector.capacity(), 3);
    EXPECT_EQ(simpleVector[0], 1);
    EXPECT_EQ(simpleVector[1], 2);
    EXPECT_EQ(simpleVector[2], 3);
}


#include "testing.h"

#include "analyzer.h"
#include "nativeTypes/bsString.h"
#include "nativeTypes/bsVector.h"
#include "src/scriptRuntime/script.h"
#include "src/scriptRuntime/scriptRuntime.h"

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

    auto returnComplexVector = testScript->getFunction<void, BSVector<BSString>&>("tests::returnComplexVector(ref vector::Vector<string::string>)");
    ASSERT_TRUE(returnComplexVector);
    BSVector<BSString> complexVector;
    returnComplexVector(complexVector);
    EXPECT_EQ(complexVector.size(), 4);
    EXPECT_GE(complexVector.capacity(), 4);
    EXPECT_EQ(complexVector[0], "a");
    EXPECT_EQ(complexVector[1], "b");
    EXPECT_EQ(complexVector[2], "c");
    EXPECT_EQ(complexVector[3], "d");

    auto setIndex = testScript->getFunction<void, BSVector<BSString>&, int, BSString&>("tests::setIndex(ref vector::Vector<string::string>,int,ref string::string)");
    ASSERT_TRUE(setIndex);
    BSString newValue = "Hello there!";
    setIndex(complexVector, 0, newValue);
    EXPECT_EQ(complexVector[0], newValue);
    newValue = "General Kenobi!";
    setIndex(complexVector, 2, newValue);
    EXPECT_EQ(complexVector[2], newValue);

    auto getIndex = testScript->getFunction<void, BSString&, BSVector<BSString>&, int>("tests::getIndex(ref string::string,ref vector::Vector<string::string>,int)");
    ASSERT_TRUE(getIndex);
    BSString result;
    getIndex(result, complexVector, 0);
    EXPECT_STREQ(result.data(), "Hello there!");
    getIndex(result, complexVector, 2);
    EXPECT_STREQ(result.data(), "General Kenobi!");

    auto clearVector = testScript->getFunction<void, BSVector<BSString>&>("tests::clearVector(ref vector::Vector<string::string>)");
    ASSERT_TRUE(clearVector);
    clearVector(complexVector);
    EXPECT_EQ(complexVector.size(), 0);
    EXPECT_GE(complexVector.capacity(), 4);
}

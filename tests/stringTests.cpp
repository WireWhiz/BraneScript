
#include "testing.h"

#include "analyzer.h"
#include "nativeTypes/bsString.h"
#include "script.h"
#include "scriptRuntime.h"

using namespace BraneScript;

TEST(BraneScript, Strings)
{
    Parser analyzer;
    std::string path = "testScripts/stringTests.bs";
    analyzer.load(path);
    analyzer.validate(path);
    checkCompileErrors(analyzer, path);

    auto ir = analyzer.compile(path, CompileFlags_DebugInfo);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    rt.loadDefaultModules();
    auto testScript = rt.loadModule(ir.modules.at("tests"));

    BSString argA = "a";
    BSString argB = "b";

    BSString str;
    auto constStr = testScript->getFunction<void, BSString&>("tests::testConst(ref string::string)");
    ASSERT_TRUE(constStr);
    constStr(str);
    EXPECT_STREQ(str.data(), "Hello World!");

    auto returnE = testScript->getFunction<char>("tests::returnE()");
    ASSERT_TRUE(returnE);
    EXPECT_EQ('E', returnE());

    auto concat = testScript->getFunction<void, BSString&, BSString&, BSString&>("tests::concat(ref string::string,ref string::string,ref string::string)");
    ASSERT_TRUE(concat);
    concat(str, argA, argB);
    EXPECT_STREQ(str.data(), "ab");

    auto strEQ = testScript->getFunction<bool, BSString&, BSString&>("tests::strEQ(ref string::string,ref string::string)");
    ASSERT_TRUE(strEQ);
    EXPECT_TRUE(strEQ(argA, argA));
    EXPECT_FALSE(strEQ(argA, argB));

    auto strNEQ = testScript->getFunction<bool, BSString&, BSString&>("tests::strNEQ(ref string::string,ref string::string)");
    ASSERT_TRUE(strNEQ);
    EXPECT_FALSE(strNEQ(argA, argA));
    EXPECT_TRUE(strNEQ(argA, argB));
}
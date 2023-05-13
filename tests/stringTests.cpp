
#include "testing.h"

#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"
#include "nativeTypes/BSString.h"

using namespace BraneScript;

TEST(BraneScript, Strings)
{
    std::string testString = R"(
    link "string";
    export as "tests"
    {
        string testConst()
        {
            return "Hello World!";
        }
        char returnE()
        {
            return "ABCDE"[4];
        }
        string concat(ref string a, ref string b)
        {
            return a + b;
        }
        bool strEQ(ref string a, ref string b)
        {
            return a == b;
        }
        bool strNEQ(ref string a, ref string b)
        {
            return a != b;
        }
    }
    )";

    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    llvm::LLVMContext ctx;
    auto ir = analyzer.getCtx("test")->scriptContext->compile(&ctx, false);

    ScriptRuntime rt;
    rt.loadLibrary(BSString::library());
    Script* testScript = rt.loadScript(ir);
    ASSERT_TRUE(testScript);

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
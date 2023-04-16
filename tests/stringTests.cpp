
#include "testing.h"

#include "compiler.h"
#include "linker.h"
#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

TEST(BraneScript, Strings)
{
#ifndef NDEBUG
    scriptMallocDiff = 0;
#endif
    std::string testString = R"(
    link "BraneScript";
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

    Linker l;

    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    Compiler compiler;
    compiler.setLinker(&l);
    auto* ir = compiler.compile(analyzer.getCtx("test")->scriptContext.get());
    ASSERT_TRUE(ir);

    ScriptRuntime rt;
    rt.setLinker(&l);
    Script* testScript = rt.loadScript(ir);
    delete ir;
    ASSERT_TRUE(testScript);

    std::string argA = "a";
    std::string argB = "b";

    std::string str;
    auto constStr = testScript->getFunction<void, std::string*>("tests::testConst(ref BraneScript::string)");
    ASSERT_TRUE(constStr);
    constStr(&str);
    EXPECT_STREQ(str.c_str(), "Hello World!");

    auto returnE = testScript->getFunction<char>("tests::returnE()");
    ASSERT_TRUE(returnE);
    EXPECT_EQ('E', returnE());

    auto concat = testScript->getFunction<void, std::string*, std::string*, std::string*>("tests::concat(ref BraneScript::string,ref BraneScript::string,ref BraneScript::string)");
    ASSERT_TRUE(concat);
    concat(&str, &argA, &argB);
    EXPECT_STREQ(str.c_str(), "ab");

    auto strEQ = testScript->getFunction<bool, std::string*, std::string*>("tests::strEQ(ref BraneScript::string,ref BraneScript::string)");
    ASSERT_TRUE(strEQ);
    EXPECT_TRUE(strEQ(&argA, &argA));
    EXPECT_FALSE(strEQ(&argA, &argB));

    auto strNEQ = testScript->getFunction<bool, std::string*, std::string*>("tests::strNEQ(ref BraneScript::string,ref BraneScript::string)");
    ASSERT_TRUE(strNEQ);
    EXPECT_FALSE(strNEQ(&argA, &argA));
    EXPECT_TRUE(strNEQ(&argA, &argB));

#ifndef NDEBUG
    EXPECT_EQ(scriptMallocDiff, 0);
#endif
}
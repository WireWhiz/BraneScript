
#include "testing.h"

#include "../src/compiler.h"
#include "../src/scriptRuntime.h"
#include "../src/script.h"
#include "../src/linker.h"

using namespace BraneScript;

TEST(BraneScript, Strings)
{
    scriptMallocDiff = 0;
    std::string testString = R"(
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
    )";

    Linker l;

    Compiler compiler(&l);
    IRScript* ir = compiler.compile(testString);
    checkCompileErrors(compiler);
    ASSERT_TRUE(ir);

    ScriptRuntime rt;
    rt.setLinker(&l);
    Script* testScript = rt.assembleScript(ir);
    ASSERT_TRUE(testScript);

    std::string argA = "a";
    std::string argB = "b";

    auto constStr = testScript->getFunction<std::string*>("testConst()");
    ASSERT_TRUE(constStr);
    std::string* str = constStr();
    EXPECT_STREQ(str->c_str(), "Hello World!");
    delete str;

    auto returnE = testScript->getFunction<char>("returnE()");
    ASSERT_TRUE(returnE);
    EXPECT_EQ('E', returnE());

    auto concat = testScript->getFunction<std::string*, std::string*, std::string*>("concat(ref string,ref string)");
    ASSERT_TRUE(concat);
    str = concat(&argA, &argB);
    EXPECT_STREQ(str->c_str(), "ab");
    delete str;

    auto strEQ = testScript->getFunction<bool, std::string*, std::string*>("strEQ(ref string,ref string)");
    ASSERT_TRUE(strEQ);
    EXPECT_TRUE(strEQ(&argA, &argA));
    EXPECT_FALSE(strEQ(&argA, &argB));

    auto strNEQ = testScript->getFunction<bool, std::string*, std::string*>("strNEQ(ref string,ref string)");
    ASSERT_TRUE(strNEQ);
    EXPECT_FALSE(strNEQ(&argA, &argA));
    EXPECT_TRUE(strNEQ(&argA, &argB));

    #ifndef NDEBUG
    EXPECT_EQ(scriptMallocDiff, 1);
    #endif
}
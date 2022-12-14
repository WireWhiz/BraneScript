#include "testing.h"

#include "../src/compiler.h"
#include "../src/scriptRuntime.h"
#include "../src/script.h"
#include "../src/linker.h"

using namespace BraneScript;

TEST(BraneScript, Recursion)
{
    std::string testString = R"(
    int called1(int in)
    {
        return in;
    }
    int caller1(int in)
    {
        return called1(in);
    }

    //recursively calculate x to the nth power
    int pow(int x, int n)
    {
        if(n == 1)
            return x;
        return x * pow(x, n - 1);
    }
)";
    Linker l;
    Compiler compiler(&l);
    auto* ir = compiler.compile(testString);
    checkCompileErrors(compiler);
    ASSERT_TRUE(ir);

    ScriptRuntime rt;
    Script* testScript = rt.assembleScript(ir);
    ASSERT_TRUE(testScript);

    auto f0 = testScript->getFunction<int, int>("caller1");
    ASSERT_TRUE(f0);
    EXPECT_EQ(f0(5), 5);

    auto pow = testScript->getFunction<int, int, int>("pow");
    ASSERT_TRUE(pow);
    EXPECT_EQ(pow(2, 4), 16);
}


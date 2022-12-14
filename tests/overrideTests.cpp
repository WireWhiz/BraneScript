

#include "testing.h"

#include "../src/compiler.h"
#include "../src/scriptRuntime.h"
#include "../src/script.h"
#include "../src/linker.h"

using namespace BraneScript;

TEST(BraneScript, Overrides)
{
    std::string testString = R"(
    bool func(int a, float b, bool c)
    {
        return true;
    }
    int func(int a)
    {
        return 1;
    }
    int func()
    {
        return 0;
    }
    int func(int a, float b)
    {
        return 2;
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

    auto f0 = testScript->getFunction<int>("func");
    ASSERT_TRUE(f0);
    EXPECT_EQ(f0(), 0);

    auto f1 = testScript->getFunction<int, int>("func");
    ASSERT_TRUE(f1);
    EXPECT_EQ(f1(0), 1);

    auto f2 = testScript->getFunction<int, int, float>("func");
    ASSERT_TRUE(f2);
    EXPECT_EQ(f2(0, 0.0f), 2);

    auto f3 = testScript->getFunction<bool, int, float, bool>("func");
    ASSERT_TRUE(f3);
    EXPECT_TRUE(f3(0, 0.0f, true));

    auto f4 = testScript->getFunction<int, float>("func");
    EXPECT_FALSE(f4);
}

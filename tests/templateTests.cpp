#include "testing.h"

#include "compiler.h"
#include "linker.h"
#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

TEST(BraneScript, Templates)
{
    std::string testString = R"(
    link "BraneScript";

    template<Arg1, Arg2>
    Arg1 add(Arg1 a, Arg2 b)
    {
        return a + b;
    }

/*  Add this back in when we add in template arg inference
    int addInt(int a, int b)
    {
        return add(a, b);
    }
*/

    int addIntExplicit(int a, int b)
    {
        return add<int, int>(a, b);
    }

    float addFloatExplicit(float a, float b)
    {
        return add<float, float>(a, b);
    }
)";
    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    Compiler compiler;
    auto* ir = compiler.compile(analyzer.getCtx("test")->scriptContext.get());
    ASSERT_TRUE(ir);

    ScriptRuntime rt;
    Script* testScript = rt.assembleScript(ir);
    ASSERT_TRUE(testScript);

    /*auto addInt = testScript->getFunction<int, int, int>("addInt");
    ASSERT_TRUE(addInt);
    EXPECT_EQ(addInt(5, 5), 10);*/

    auto addIntExplicit = testScript->getFunction<int, int, int>("addIntExplicit");
    ASSERT_TRUE(addIntExplicit);
    EXPECT_EQ(addIntExplicit(2, 4), 6);

    auto addFloatExplicit = testScript->getFunction<float, float, float>("addFloatExplicit");
    ASSERT_TRUE(addFloatExplicit);
    EXPECT_EQ(addFloatExplicit(2.0f, 4.0f), 6.0f);
}

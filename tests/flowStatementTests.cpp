
#include "testing.h"

#include "../scripting/compiler.h"
#include "../scripting/scriptRuntime.h"
#include "../scripting/script.h"

using namespace BraneScript;

void testFunction(const std::string& name, Script* script)
{
    auto f = script->getFunction<bool>(name);
    ASSERT_TRUE(f) << "Function does not exist: " << name;
    EXPECT_TRUE(f()) << "Testing function: " << name;
}

TEST(FlowStatementTests, FlowStatements)
{
    std::string testString = R"(
    bool testConstTrueIf()
    {
        if(true)
            return true;
        return false;
    }
    bool testConstFalseIf()
    {
        if(false)
            return false;
        return true;
    }
    bool testTrueVarIf()
    {
        bool condition = true;
        if(condition)
            return true;
        return false;
    }
    bool testFalseVarIf()
    {
        bool condition = false;
        if(condition)
            return false;
        return true;
    }
    bool testIfInlineCompareInt1()
    {
        if(5 < 10)
            return true;
        return false;
    }
    bool testIfInlineCompareInt2()
    {
        if(10 < 10)
            return false;
        return true;
    }
)";

    Compiler compiler;
    auto* ir = compiler.compile(testString);

    ScriptRuntime rt;
    Script* testScript = rt.assembleScript(ir);

    testFunction("testConstTrueIf", testScript);
    testFunction("testConstFalseIf", testScript);
    testFunction("testTrueVarIf", testScript);
    testFunction("testFalseVarIf", testScript);
    testFunction("testIfInlineCompareInt1", testScript);
    testFunction("testIfInlineCompareInt2", testScript);

}
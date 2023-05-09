
#include "testing.h"

#include "src/scriptRuntime/script.h"
#include "src/scriptRuntime/scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

void testFunction(const std::string& name, Script* script)
{
    auto f = script->getFunction<bool>(name);
    ASSERT_TRUE(f) << "Function does not exist: " << name;
    EXPECT_TRUE(f()) << "Testing function: " << name;
}

TEST(BraneScript, FlowStatements)
{
    std::string testString = R"(
    export as "tests"
    {
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
    }
)";
    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    llvm::LLVMContext ctx;
    auto ir = analyzer.getCtx("test")->scriptContext->compile(&ctx);

    ScriptRuntime rt;
    Script* testScript = rt.loadScript(ir);
    ASSERT_TRUE(testScript);

    testFunction("tests::testConstTrueIf", testScript);
    testFunction("tests::testConstFalseIf", testScript);
    testFunction("tests::testTrueVarIf", testScript);
    testFunction("tests::testFalseVarIf", testScript);
    testFunction("tests::testIfInlineCompareInt1", testScript);
    testFunction("tests::testIfInlineCompareInt2", testScript);

}
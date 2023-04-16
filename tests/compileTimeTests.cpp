#include "testing.h"

#include <iostream>
#include "compiler.h"
#include "linker.h"
#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

TEST(BraneScript, CompileTimeTests)
{

    std::string testString = R"(
    link "BraneScript";
    export as "tests"
    {
        constexpr int add(int a, int b)
        {
            return a + b;
        }

        int testOp()
        {
            return add(2, 2);
        }
    }
)";
    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    Linker linker;
    ScriptRuntime rt;
    Compiler compiler;
    compiler.setLinker(&linker);
    compiler.setRuntime(&rt);
    auto* ir = compiler.compile(analyzer.getCtx("test")->scriptContext.get());
    ASSERT_TRUE(ir);

    Script* testScript = rt.loadScript(ir);
    delete ir;
    ASSERT_TRUE(testScript);

    auto testOp = testScript->getFunction<int>("tests::testOp");
    ASSERT_TRUE(testOp);
    EXPECT_EQ(testOp(), 4);
}

/*
#include "testing.h"

#include "compiler.h"
#include "scriptRuntime.h"
#include "script.h"
#include "linker.h"

using namespace BraneScript;

TEST(BraneScript, Lambdas)
{
#ifndef NDEBUG
    scriptMallocDiff = 0;
#endif
    std::string testString = R"(
    link "testLib" as "lib";

    void setRef(int v)
    {
        lib::setRef(v);
    }
)";

    std::string header = R"(
    export as "testLib"
    {
        void setRef(int v) ext;
    }
)";
    Linker linker;

    StaticAnalyzer analyzer;
    analyzer.load("header", header);
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    Compiler compiler;
    compiler.setLinker(&linker);
    auto* ir = compiler.compile(analyzer.getCtx("test")->scriptContext.get());
    ASSERT_TRUE(ir);

    ScriptRuntime rt;
    rt.setLinker(&linker);
    Script* testScript = rt.assembleScript(ir);
    ASSERT_TRUE(testScript);

    auto scriptSetRef = testScript->getFunction<void, int>("setRef");
    ASSERT_TRUE(scriptSetRef);
    scriptSetRef(5);

#ifndef NDEBUG
    EXPECT_EQ(scriptMallocDiff, 0);
#endif
}*/

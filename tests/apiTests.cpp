
#include "testing.h"

#include "compiler.h"
#include "scriptRuntime.h"
#include "script.h"
#include "linker.h"

using namespace BraneScript;

int refValue = 0;

void BS_API_CALL setRef(int newVal)
{
    refValue = newVal;
}

TEST(BraneScript, API)
{
#ifndef NDEBUG
    scriptMallocDiff = 0;
#endif
    std::string testString = R"(
    link "testLib" as "lib";

    export as "tests"
    {
        void setRef(int v)
        {
            lib::setRef(v);
        }
    }
)";

    std::string testLibString = R"(
    export as "testLib"
    {
        void setRef(int v) ext;
    }
)";

    Linker linker;
    linker.addFunction("testLib::setRef", setRef);

    StaticAnalyzer analyzer;
    analyzer.load("testLibHeader", testLibString);
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
    delete ir;
    ASSERT_TRUE(testScript);

    auto scriptSetRef = testScript->getFunction<void, int>("tests::setRef");
    ASSERT_TRUE(scriptSetRef);
    scriptSetRef(5);

    EXPECT_EQ(refValue, 5);

#ifndef NDEBUG
    EXPECT_EQ(scriptMallocDiff, 0);
#endif
}

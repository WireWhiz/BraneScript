
#include "testing.h"
/*

#include "../src/compiler.h"
#include "../src/scriptRuntime.h"
#include "../src/script.h"
#include "../src/library.h"
#include "../src/linker.h"

using namespace BraneScript;

int refValue = 0;

void BS_API_CALL setRef(int newVal)
{
    refValue = newVal;
}

TEST(BraneScript, Libraries)
{
#ifndef NDEBUG
    scriptMallocDiff = 0;
#endif
    std::string testString = R"(
    link "testLib" as "lib";

    void setRef(int v)
    {
        lib.setRef(v);
    }
)";
    Library testLib("testLib");
    testLib.addFunction("setRef", setRef);

    Linker linker;
    linker.addLibrary(&testLib);

    Compiler compiler(&linker);
    auto* ir = compiler.compile(testString);
    checkCompileErrors(compiler);
    ASSERT_TRUE(ir);

    ScriptRuntime rt;
    rt.setLinker(&linker);
    Script* testScript = rt.assembleScript(ir);
    checkCompileErrors(compiler);
    ASSERT_TRUE(testScript);

    auto scriptSetRef = testScript->getFunction<void, int>("setRef");
    ASSERT_TRUE(scriptSetRef);
    scriptSetRef(5);

    EXPECT_EQ(refValue, 5);

#ifndef NDEBUG
    EXPECT_EQ(scriptMallocDiff, 0);
#endif
}*/

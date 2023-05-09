
#include "testing.h"

#include "scriptRuntime.h"
#include "script.h"

using namespace BraneScript;

int refValue = 0;

void BS_API_CALL setRef(int newVal)
{
    refValue = newVal;
}

TEST(BraneScript, API)
{
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

    NativeLibrary testLib;
    testLib.identifier = "testLib";
    testLib.addFunction("testLib::setRef(int)", setRef);

    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.load("testLib", testLibString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString)

    llvm::LLVMContext ctx;
    auto ir = analyzer.getCtx("test")->scriptContext->compile(&ctx);

    ScriptRuntime rt;
    rt.loadLibrary(testLib);
    Script* testScript = rt.loadScript(ir);
    ASSERT_TRUE(testScript);

    auto scriptSetRef = testScript->getFunction<void, int>("tests::setRef");
    ASSERT_TRUE(scriptSetRef);
    scriptSetRef(5);

    EXPECT_EQ(refValue, 5);
}

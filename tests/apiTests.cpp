
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

    std::string header = R"(
    module "testLib"
    {
        void setRef(int v) ext;
    }
)";

    NativeLibrary testLib("testLib");
    testLib.addFunction("testLib::setRef(int)", setRef);

    Analyzer analyzer;
    std::string path = "testScripts/apiTests.bs";
    analyzer.load(path);
    analyzer.load("header", header);
    analyzer.validate(path);
    checkCompileErrors(analyzer, path);

    llvm::LLVMContext ctx;
    auto ir = analyzer.getCtx(path)->scriptContext->compile(&ctx, CompileFlags_DebugInfo);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    rt.loadLibrary(testLib);
    Module* testScript = rt.loadModule(ir.modules.at("tests"));
    ASSERT_TRUE(testScript);

    auto scriptSetRef = testScript->getFunction<void, int>("tests::setRef");
    ASSERT_TRUE(scriptSetRef);
    scriptSetRef(5);

    EXPECT_EQ(refValue, 5);
}

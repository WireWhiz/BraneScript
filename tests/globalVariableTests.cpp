

#include "testing.h"

#include "linker.h"
#include "script.h"
#include "scriptRuntime.h"
#include "compiler.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

TEST(BraneScript, GlobalVariables)
{
    std::string testString = R"(
    link "BraneScript";

    int globalInt;
    float globalFloat;
    export as "tests"
    {
        struct GlobalStruct
        {
            int var;
        }
        GlobalStruct globalStruct;
        string globalString;

        void setInt(int v)
        {
            globalInt = v;
        }
        void setFloat(float v)
        {
            globalFloat = v;
        }
        void setStructVar(int v)
        {
            globalStruct.var = v;
        }
        void setStringVar(ref string v)
        {
            globalString = v;
        }
        int getInt()
        {
            return globalInt;
        }
        float getFloat()
        {
            return globalFloat;
        }
        int getStructVar()
        {
            return globalStruct.var;
        }
        string getStringVar()
        {
            return globalString;
        }
    }
)";
    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    Compiler compiler;
    auto* ir = compiler.compile(analyzer.getCtx("test")->scriptContext.get());
    ASSERT_TRUE(ir);

    Linker linker;
    ScriptRuntime rt;
    rt.setLinker(&linker);
    Script* testScript = rt.loadScript(ir);
    delete ir;
    ASSERT_TRUE(testScript);

    auto setInt = testScript->getFunction<void, int>("tests::setInt");
    ASSERT_TRUE(setInt);
    setInt(42);

    auto setFloat = testScript->getFunction<void, float>("tests::setFloat");
    ASSERT_TRUE(setFloat);
    setFloat(42.0f);

    auto setStructVar = testScript->getFunction<void, int>("tests::setStructVar");
    ASSERT_TRUE(setStructVar);
    setStructVar(32);

    auto setStringVar = testScript->getFunction<void, std::string*>("tests::setStringVar(ref BraneScript::string)");
    ASSERT_TRUE(setStringVar);
    std::string str = "Hello world!";
    setStringVar(&str);

    auto getInt = testScript->getFunction<int>("tests::getInt");
    ASSERT_TRUE(getInt);
    EXPECT_EQ(getInt(), 42);

    auto getFloat = testScript->getFunction<float>("tests::getFloat");
    ASSERT_TRUE(getFloat);
    EXPECT_EQ(getFloat(), 42.0f);

    auto getStructVar = testScript->getFunction<int>("tests::getStructVar");
    ASSERT_TRUE(getStructVar);
    EXPECT_EQ(getStructVar(), 32);

    std::string strRet;
    auto getStringVar = testScript->getFunction<void, std::string*>("tests::getStringVar(ref BraneScript::string)");
    ASSERT_TRUE(getStringVar);
    getStringVar(&strRet);
    EXPECT_EQ(strRet, str);
}

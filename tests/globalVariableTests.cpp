

#include "testing.h"

#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

TEST(BraneScript, GlobalVariables)
{
    std::string testString = R"(
    module "tests"
    {
        int globalInt;
        float globalFloat;
        struct GlobalStruct
        {
            int var;
        }
        GlobalStruct globalStruct;

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
    }
)";
    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    auto ir = analyzer.compile("test");
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    Module* testScript = rt.loadModule(ir.modules.at("tests"));
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

    auto getInt = testScript->getFunction<int>("tests::getInt");
    ASSERT_TRUE(getInt);
    EXPECT_EQ(getInt(), 42);

    auto getFloat = testScript->getFunction<float>("tests::getFloat");
    ASSERT_TRUE(getFloat);
    EXPECT_EQ(getFloat(), 42.0f);

    auto getStructVar = testScript->getFunction<int>("tests::getStructVar");
    ASSERT_TRUE(getStructVar);
    EXPECT_EQ(getStructVar(), 32);
}

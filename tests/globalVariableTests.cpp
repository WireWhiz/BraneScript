

#include "testing.h"

#include "../src/compiler.h"
#include "../src/scriptRuntime.h"
#include "../src/script.h"
#include "../src/library.h"
#include "../src/linker.h"

using namespace BraneScript;

TEST(BraneScript, GlobalVariables)
{
    std::string testString = R"(
    int globalInt;
    float globalFloat;
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
)";

    Linker linker;

    Compiler compiler(&linker);
    auto* ir = compiler.compile(testString);
    checkCompileErrors(compiler);
    ASSERT_TRUE(ir);

    ScriptRuntime rt;
    rt.setLinker(&linker);
    Script* testScript = rt.assembleScript(ir);
    checkCompileErrors(compiler);
    ASSERT_TRUE(testScript);

    auto setInt = testScript->getFunction<void, int>("setInt");
    ASSERT_TRUE(setInt);
    setInt(42);

    auto setFloat = testScript->getFunction<void, float>("setFloat");
    ASSERT_TRUE(setFloat);
    setFloat(42.0f);

    auto setStructVar = testScript->getFunction<void, int>("setStructVar");
    ASSERT_TRUE(setStructVar);
    setStructVar(32);

    auto setStringVar = testScript->getFunction<void, std::string*>("setStringVar(ref string)");
    ASSERT_TRUE(setStringVar);
    std::string str = "Hello world!";
    setStringVar(&str);

    auto getInt = testScript->getFunction<int>("getInt");
    ASSERT_TRUE(getInt);
    EXPECT_EQ(getInt(), 42);

    auto getFloat = testScript->getFunction<float>("getFloat");
    ASSERT_TRUE(getFloat);
    EXPECT_EQ(getFloat(), 42.0f);

    auto getStructVar = testScript->getFunction<int>("getStructVar");
    ASSERT_TRUE(getStructVar);
    EXPECT_EQ(getStructVar(), 32);

    auto getStringVar = testScript->getFunction<std::string*>("getStringVar()");
    ASSERT_TRUE(getStringVar);
    auto strRet = getStringVar();
    EXPECT_EQ(*strRet, str);
    delete strRet;
}

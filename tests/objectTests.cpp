#include "testing.h"

#include "../scripting/compiler.h"
#include "../scripting/scriptRuntime.h"
#include "../scripting/script.h"
#include "../scripting/structDefinition.h"
#include "../scripting/nativeTypes.h"
#include "../scripting/linker.h"

using namespace BraneScript;

struct TestStruct1
{
    bool c;
    float a;
    int b;
};

struct TestStruct2
{
    int a;
    bool b;
    float c;
};

TEST(BraneScript, Objects)
{
    std::string testString = R"(
    float getMember1(ref TestStruct1 s)
    {
        return s.a;
    }
    int getMember2(ref TestStruct1 s)
    {
        return s.b;
    }
    bool getMember3(ref TestStruct1 s)
    {
        return s.c;
    }

    TestStruct1 createStruct()
    {
        TestStruct1 output;
        ref TestStruct1 o = output;
        o.a = 6.9f;
        o.b = 420;
        o.c = false;
        TestStruct1 notOut = output;
        notOut.a = 43;
        return output;
    }

    struct TestStruct2
    {
        int a;
        bool b;
        float c;
    }

    TestStruct2 testScriptStruct()
    {
        TestStruct2 output;
        output.a = 5;
        output.b = true;
        output.c = 3.2f;
        return output;
    }

    /*void modStruct(ref TestStruct2 r)
    {
          r.c = 4.2f;
    }*/
)";
    StructDef testStruct1Def("TestStruct1");
    testStruct1Def.addMember("c", getNativeTypeDef(ValueType::Bool));
    testStruct1Def.addMember("a", getNativeTypeDef(ValueType::Float32));
    testStruct1Def.addMember("b", getNativeTypeDef(ValueType::Int32));
    testStruct1Def.padMembers();

    EXPECT_EQ(testStruct1Def.members()[0].offset, offsetof(TestStruct1, c));
    EXPECT_EQ(testStruct1Def.members()[1].offset, offsetof(TestStruct1, a));
    EXPECT_EQ(testStruct1Def.members()[2].offset, offsetof(TestStruct1, b));

    Linker l;
    l.addType(&testStruct1Def);

    Compiler compiler(&l);
    auto* ir = compiler.compile(testString);
    checkCompileErrors(compiler);
    ASSERT_TRUE(ir);

    ScriptRuntime rt;
    rt.setLinker(&l);
    Script* testScript = rt.assembleScript(ir);
    ASSERT_TRUE(testScript);

    TestStruct1 testStruct1{true, 23.3, 45};

    auto getMember1 = (FunctionHandle<float, TestStruct1*>)testScript->functions[0];
    ASSERT_TRUE(getMember1);
    EXPECT_EQ(getMember1(&testStruct1), 23.3f);

    auto getMember2 = (FunctionHandle<int, TestStruct1*>)testScript->functions[1];
    ASSERT_TRUE(getMember2);
    EXPECT_EQ(getMember2(&testStruct1), 45);

    auto getMember3 = (FunctionHandle<bool, TestStruct1*>)testScript->functions[2];
    ASSERT_TRUE(getMember3);
    EXPECT_EQ(getMember3(&testStruct1), true);

    auto createStruct = (FunctionHandle<TestStruct1*>)testScript->functions[3];
    ASSERT_TRUE(createStruct);
    TestStruct1* createdStruct = createStruct();
    ASSERT_TRUE(createdStruct);
    EXPECT_EQ(createdStruct->a, 6.9f);
    EXPECT_EQ(createdStruct->b, 420);
    EXPECT_EQ(createdStruct->c, false);
    delete createdStruct;

    auto testScriptStruct = (FunctionHandle<TestStruct2*>)testScript->functions[4];
    ASSERT_TRUE(testScriptStruct);
    TestStruct2* ts2 = testScriptStruct();
    ASSERT_TRUE(ts2);
    EXPECT_EQ(ts2->a, 5);
    EXPECT_EQ(ts2->b, true);
    EXPECT_EQ(ts2->c, 3.2f);
    delete ts2;



}
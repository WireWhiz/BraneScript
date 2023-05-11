#include "testing.h"

#include "nativeTypes.h"
#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

int constructorCalled = 0;
int copyConstructorCalled = 0;
int moveConstructorCalled = 0;
int destructorCalled = 0;

void resetTestCounters()
{
    constructorCalled = 0;
    copyConstructorCalled = 0;
    moveConstructorCalled = 0;
    destructorCalled = 0;
}

struct TestStruct1
{
    bool c = false;
    float a = 0;
    int b = 0;
};

struct TestStruct2
{
    int a;
    bool b;
    float c;
};

struct NestedStructChild
{
    float x;
    float y;
    float z;
};

struct NestedStructBase
{
    float a;
    NestedStructChild b;
    float c;
};

TEST(BraneScript, Objects)
{
    std::string testString = R"(
    link "BraneScript";
    export as "tests"
    {
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
            output.a = 6.9f;
            output.b = 420;
            output.c = false;
            TestStruct1 notOut = output;
            notOut.a = 43;
            return output;
        }

        TestStruct1 createStructClean()
        {
            TestStruct1 output;
            output.a = 6.9f;
            output.b = 420;
            output.c = false;
            return output;
        }

        TestStruct1 testReturnThroughArg()
        {
            return createStructClean();
        }

        void testDestruct()
        {
            TestStruct1 temp = createStruct();
        }

        struct TestStruct2
        {
            int a;
            bool b;
            float c;
            void _construct()
            {
                a = 5;
                b = true;
                c = 3.2f;
            }
            float sum()
            {
                return a + c;
            }
        }

        TestStruct2 testScriptStruct()
        {
            TestStruct2 output;
            return output;
        }

        void modStruct(ref TestStruct2 s)
        {
              s.c = 4.2f;
        }

        float testMemberFunc(ref TestStruct2 s)
        {
            return s.sum();
        }

        struct NestedStructChild
        {
            float x;
            float y;
            float z;
            void _construct()
            {
                x = 1;
                y = 2;
                z = 3;
            }
        }
        struct NestedStructBase
        {
            float a;
            NestedStructChild b;
            float c;
        }

        NestedStructBase nestedTest()
        {
            NestedStructBase base;
            base.c = 42;
            base.b.y = 4;
            NestedStructBase copied = base;
            return copied;
        }
    }
)";

    std::string header = R"(
    export as "BraneScript"
    {
        struct TestStruct1
        {
            bool c;
            float a;
            int b;
            void _construct() ext;
            void _copy(const ref TestStruct1 o) ext;
            void _move(ref TestStruct1 o) ext;
            void _destruct() ext;
        }
    }
)";

    StructDef testStruct1Def("BraneScript::TestStruct1");

    testStruct1Def.addMemberVar("c", getNativeTypeDef(ValueType::Bool));
    testStruct1Def.addMemberVar("a", getNativeTypeDef(ValueType::Float32));
    testStruct1Def.addMemberVar("b", getNativeTypeDef(ValueType::Int32));
    testStruct1Def.padMembers();

    EXPECT_EQ(testStruct1Def.memberVars()[0].offset, offsetof(TestStruct1, c));
    EXPECT_EQ(testStruct1Def.memberVars()[1].offset, offsetof(TestStruct1, a));
    EXPECT_EQ(testStruct1Def.memberVars()[2].offset, offsetof(TestStruct1, b));

    NativeLibrary constructors;
    constructors.identifier = "BraneScript";
    constructors.addFunction("BraneScript::TestStruct1::_construct(ref BraneScript::TestStruct1)",  (void*)(FunctionHandle<void, void*>)[](void* data) {
        new(data) TestStruct1();
        constructorCalled++;
    });
    constructors.addFunction("BraneScript::TestStruct1::_copy(ref BraneScript::TestStruct1,const ref BraneScript::TestStruct1)", (void*)(FunctionHandle<void, void*, const void*>)[](void* dest, const void* src) {
        *((TestStruct1*)dest) = *((TestStruct1*)src);
        copyConstructorCalled++;
    });
    constructors.addFunction("BraneScript::TestStruct1::_move(ref BraneScript::TestStruct1,ref BraneScript::TestStruct1)", (void*)(FunctionHandle<void, void*, void*>)[](void* dest, void* src) {
        *((TestStruct1*)dest) = std::move(*((TestStruct1*)src));
        moveConstructorCalled++;
    });
    constructors.addFunction("BraneScript::TestStruct1::_destruct(ref BraneScript::TestStruct1)", (void*)(FunctionHandle<void, void*>)[](void* data) {
        ((TestStruct1*)data)->~TestStruct1();
        destructorCalled++;
    });

    StaticAnalyzer analyzer;
    analyzer.load("header", header);
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    llvm::LLVMContext llvmContext;
    auto ir = analyzer.getCtx("test")->scriptContext->compile(&llvmContext, false, true);

    ScriptRuntime rt;
    rt.loadLibrary(constructors);
    Script* testScript = rt.loadScript(ir);
    ASSERT_TRUE(testScript);

    TestStruct1 testStruct1{true, 23.3, 45};

    auto getMember1 = testScript->getFunction<float, TestStruct1*>("tests::getMember1(ref BraneScript::TestStruct1)");
    ASSERT_TRUE(getMember1);
    EXPECT_EQ(getMember1(&testStruct1), 23.3f);

    auto getMember2 =  testScript->getFunction<int, TestStruct1*>("tests::getMember2(ref BraneScript::TestStruct1)");
    ASSERT_TRUE(getMember2);
    EXPECT_EQ(getMember2(&testStruct1), 45);

    auto getMember3 = testScript->getFunction<bool, TestStruct1*>("tests::getMember3(ref BraneScript::TestStruct1)");
    ASSERT_TRUE(getMember3);
    EXPECT_EQ(getMember3(&testStruct1), true);

    EXPECT_EQ(constructorCalled, 0);
    EXPECT_EQ(moveConstructorCalled, 0);
    EXPECT_EQ(copyConstructorCalled, 0);
    EXPECT_EQ(destructorCalled, 0);
    resetTestCounters();

    TestStruct1 createdStruct{};
    auto createStruct = testScript->getFunction<void, TestStruct1*>("tests::createStruct(ref BraneScript::TestStruct1)");
    ASSERT_TRUE(createStruct);
    createStruct(&createdStruct);
    EXPECT_EQ(createdStruct.a, 6.9f);
    EXPECT_EQ(createdStruct.b, 420);
    EXPECT_EQ(createdStruct.c, false);

    EXPECT_EQ(constructorCalled, 2);
    EXPECT_EQ(moveConstructorCalled, 0);
    EXPECT_EQ(copyConstructorCalled, 2);
    EXPECT_EQ(destructorCalled, 2);
    resetTestCounters();

    createdStruct = {};
    auto testReturnThroughArg = testScript->getFunction<void, TestStruct1*>("tests::testReturnThroughArg(ref BraneScript::TestStruct1)");
    ASSERT_TRUE(testReturnThroughArg);
    testReturnThroughArg(&createdStruct);
    EXPECT_EQ(createdStruct.a, 6.9f);
    EXPECT_EQ(createdStruct.b, 420);
    EXPECT_EQ(createdStruct.c, false);

    EXPECT_EQ(constructorCalled, 1);
    EXPECT_EQ(moveConstructorCalled, 0);
    EXPECT_EQ(copyConstructorCalled, 1);
    EXPECT_EQ(destructorCalled, 1);
    resetTestCounters();

    auto testDestruct = testScript->getFunction<void>("tests::testDestruct()");
    ASSERT_TRUE(testDestruct);
    testDestruct();

    EXPECT_TRUE(destructorCalled);


    TestStruct2 ts2{};
    auto testScriptStruct = testScript->getFunction<void, TestStruct2*>("tests::testScriptStruct(ref tests::TestStruct2)");
    ASSERT_TRUE(testScriptStruct);
    testScriptStruct(&ts2);
    EXPECT_EQ(ts2.a, 5);
    EXPECT_EQ(ts2.b, true);
    EXPECT_EQ(ts2.c, 3.2f);

    auto modStruct = testScript->getFunction<void, TestStruct2*>("tests::modStruct(ref tests::TestStruct2)");
    ASSERT_TRUE(modStruct);
    modStruct(&ts2);
    EXPECT_EQ(ts2.a, 5);
    EXPECT_EQ(ts2.b, true);
    EXPECT_EQ(ts2.c, 4.2f);

    auto testMemberFunc = testScript->getFunction<float, TestStruct2*>("tests::testMemberFunc(ref tests::TestStruct2)");
    ASSERT_TRUE(testMemberFunc);
    EXPECT_EQ(testMemberFunc(&ts2), 5 + 4.2f);
    EXPECT_EQ(ts2.a, 5);
    EXPECT_EQ(ts2.b, true);
    EXPECT_EQ(ts2.c, 4.2f);

    NestedStructBase nestedStruct{};
    auto nestedTest = testScript->getFunction<void, NestedStructBase*>("tests::nestedTest(ref tests::NestedStructBase)");
    ASSERT_TRUE(nestedTest);
    nestedTest(&nestedStruct);
    // We don't test a and c as they are not initialized
    EXPECT_EQ(nestedStruct.b.x, 1.0f);
    EXPECT_EQ(nestedStruct.b.y, 4.0f);
    EXPECT_EQ(nestedStruct.b.z, 3.0f);
}
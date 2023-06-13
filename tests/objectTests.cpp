#include "testing.h"

#include "script.h"
#include "scriptRuntime.h"
#include "analyzer.h"

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

struct NestedStructBase
{
    float a;
    TestStruct1 b;
    float c;
};

TEST(BraneScript, Objects)
{
    std::string testString = R"(

)";

    std::string header = R"(
    module "BraneScript"
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

    NativeLibrary constructors("BraneScript");
    constructors.addFunction("BraneScript::TestStruct1::_construct(ref BraneScript::TestStruct1)",  (void*)(FuncRef<void, void*>)[](void* data) {
        new(data) TestStruct1();
        constructorCalled++;
    });
    constructors.addFunction("BraneScript::TestStruct1::_copy(ref BraneScript::TestStruct1,const ref BraneScript::TestStruct1)", (void*)(FuncRef<void, void*, const void*>)[](void* dest, const void* src) {
        *((TestStruct1*)dest) = *((TestStruct1*)src);
        copyConstructorCalled++;
    });
    constructors.addFunction("BraneScript::TestStruct1::_move(ref BraneScript::TestStruct1,ref BraneScript::TestStruct1)", (void*)(FuncRef<void, void*, void*>)[](void* dest, void* src) {
        *((TestStruct1*)dest) = std::move(*((TestStruct1*)src));
        moveConstructorCalled++;
    });
    constructors.addFunction("BraneScript::TestStruct1::_destruct(ref BraneScript::TestStruct1)", (void*)(FuncRef<void, void*>)[](void* data) {
        ((TestStruct1*)data)->~TestStruct1();
        destructorCalled++;
    });

    Analyzer analyzer;
    analyzer.load("header", header);
    std::string path = "testScripts/objectTests.bs";
    analyzer.load(path);
    analyzer.validate("header");
    analyzer.validate(path);
    checkCompileErrors(analyzer, "header");
    checkCompileErrors(analyzer, path);

    auto ir = analyzer.compile(path, CompileFlags_DebugInfo);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    rt.loadLibrary(std::move(constructors));
    rt.loadModule(analyzer.compile("header", CompileFlags_None).modules.at("BraneScript"));
    auto testScript = rt.loadModule(ir.modules.at("tests"));

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

    resetTestCounters();

    NestedStructBase nestedStruct{};
    auto nestedTest = testScript->getFunction<void, NestedStructBase*>("tests::nestedTest(ref tests::NestedStructBase)");
    ASSERT_TRUE(nestedTest);
    nestedTest(&nestedStruct);
    // We don't test a and c as they are not initialized
    EXPECT_EQ(nestedStruct.b.a, 0);
    EXPECT_EQ(nestedStruct.b.b, 4);
    EXPECT_EQ(nestedStruct.b.c, false);
    EXPECT_EQ(nestedStruct.a, 5);
    EXPECT_EQ(nestedStruct.c, 42.0f);

    EXPECT_EQ(constructorCalled, 2);
    EXPECT_EQ(moveConstructorCalled, 0);
    EXPECT_EQ(copyConstructorCalled, 2);
    EXPECT_EQ(destructorCalled, 2);
}
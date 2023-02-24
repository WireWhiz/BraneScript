#include "testing.h"

#include "compiler.h"
#include "linker.h"
#include "nativeTypes.h"
#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

bool constructorCalled = false;
bool copyConstructorCalled = false;
bool moveConstructorCalled = false;
bool destructorCalled = false;

struct TestStruct1
{
    bool c;
    float a;
    int b;
public:
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
#ifndef NDEBUG
    scriptMallocDiff = 0;
#endif
    std::string testString = R"(
    link "BraneScript";
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

)";

    StructDef testStruct1Def("TestStruct1");

    testStruct1Def.addMemberVar("c", getNativeTypeDef(ValueType::Bool));
    testStruct1Def.addMemberVar("a", getNativeTypeDef(ValueType::Float32));
    testStruct1Def.addMemberVar("b", getNativeTypeDef(ValueType::Int32));
    testStruct1Def.padMembers();

    auto libraryContext = new LibraryContext{};
    libraryContext->identifier.text = "BraneScript";
    auto structCtx = new StructContext{};
    structCtx->identifier.text = "TestStruct1";
    structCtx->variables.emplace_back(new LabeledValueContext{});
    structCtx->variables.emplace_back(new LabeledValueContext{});
    structCtx->variables.emplace_back(new LabeledValueContext{});
    structCtx->variables[0]->identifier.text = "c";
    structCtx->variables[0]->type = {
        "bool",
        ValueType::Bool
    };
    structCtx->variables[1]->identifier.text = "a";
    structCtx->variables[1]->type = {
        "float",
        ValueType::Float32
    };
    structCtx->variables[2]->identifier.text = "b";
    structCtx->variables[2]->type = {
        "int",
        ValueType::Int32
    };
    libraryContext->structs.insert({"TestStruct1", std::unique_ptr<StructContext>(structCtx)});

    EXPECT_EQ(testStruct1Def.memberVars()[0].offset, offsetof(TestStruct1, c));
    EXPECT_EQ(testStruct1Def.memberVars()[1].offset, offsetof(TestStruct1, a));
    EXPECT_EQ(testStruct1Def.memberVars()[2].offset, offsetof(TestStruct1, b));

    Linker l;
    l.globalLib().addStruct(testStruct1Def);
    l.globalLib().addFunction(std::string(testStruct1Def.name()) + "::_construct()", "void", (void*)(FunctionHandle<void, void*>)[](void* data) {
            new(data) TestStruct1();
            constructorCalled = true;
        });
    l.globalLib().addFunction(std::string(testStruct1Def.name()) + "::_copy(const ref " + std::string(testStruct1Def.name())  + ")", "void", (void*)(FunctionHandle<void, void*, const void*>)[](void* dest, const void* src){
            *((TestStruct1*)dest) = *((TestStruct1*)src);
            copyConstructorCalled = true;
        });
    l.globalLib().addFunction(std::string(testStruct1Def.name()) + "::_move(ref " + std::string(testStruct1Def.name())  + ")", "void", (void*)(FunctionHandle<void, void*, void*>)[](void* dest, void* src){
            *((TestStruct1*)dest) = std::move(*((TestStruct1*)src));
            moveConstructorCalled = true;
        });
    l.globalLib().addFunction(std::string(testStruct1Def.name())  + "::_destruct()", "void", (void*)(FunctionHandle<void, void*>)[](void* data) {
            ((TestStruct1*)data)->~TestStruct1();
            destructorCalled = true;
        });

    StaticAnalyzer analyzer;
    analyzer.registerLibrary(libraryContext);
    analyzer.load("test", testString);
    if(!analyzer.validate("test"))
    {
        for(auto& error : analyzer.getCtx("test")->errors)
            std::cerr << error.message << std::endl;
        ASSERT_TRUE(false);
    }

    Compiler compiler;
    auto* ir = compiler.compile(analyzer.getCtx("test")->scriptContext.get());
    ASSERT_TRUE(ir);

    /*IRScript::IRStructDef& scriptStructDef = ir->localStructs[0];
    EXPECT_TRUE(scriptStructDef.isPublic);
    EXPECT_EQ(scriptStructDef.members[0].offset, offsetof(TestStruct2, a));
    EXPECT_EQ(scriptStructDef.members[1].offset, offsetof(TestStruct2, b));
    EXPECT_EQ(scriptStructDef.members[2].offset, offsetof(TestStruct2, c));*/

    ScriptRuntime rt;
    rt.setLinker(&l);
    Script* testScript = rt.assembleScript(ir);
    ASSERT_TRUE(testScript);

    TestStruct1 testStruct1{true, 23.3, 45};

    auto getMember1 = testScript->getFunction<float, TestStruct1*>("getMember1(ref TestStruct1)");
    ASSERT_TRUE(getMember1);
    EXPECT_EQ(getMember1(&testStruct1), 23.3f);

    auto getMember2 =  testScript->getFunction<int, TestStruct1*>("getMember2(ref TestStruct1)");
    ASSERT_TRUE(getMember2);
    EXPECT_EQ(getMember2(&testStruct1), 45);

    auto getMember3 = testScript->getFunction<bool, TestStruct1*>("getMember3(ref TestStruct1)");
    ASSERT_TRUE(getMember3);
    EXPECT_EQ(getMember3(&testStruct1), true);

    EXPECT_FALSE(constructorCalled);
    EXPECT_FALSE(moveConstructorCalled);
    EXPECT_FALSE(copyConstructorCalled);
    EXPECT_FALSE(destructorCalled);

    auto createStruct = testScript->getFunction<TestStruct1*>("createStruct()");
    ASSERT_TRUE(createStruct);
    TestStruct1* createdStruct = createStruct();
    ASSERT_TRUE(createdStruct);
    EXPECT_EQ(createdStruct->a, 6.9f);
    EXPECT_EQ(createdStruct->b, 420);
    EXPECT_EQ(createdStruct->c, false);
    delete createdStruct;

    EXPECT_TRUE(constructorCalled);
    EXPECT_TRUE(moveConstructorCalled);
    EXPECT_TRUE(copyConstructorCalled);
    EXPECT_TRUE(destructorCalled);
    destructorCalled = false;

    auto testDestruct = testScript->getFunction<void>("testDestruct()");
    ASSERT_TRUE(testDestruct);
    testDestruct();

    EXPECT_TRUE(destructorCalled);

    auto testScriptStruct = testScript->getFunction<TestStruct2*>("testScriptStruct()");
    ASSERT_TRUE(testScriptStruct);
    TestStruct2* ts2 = testScriptStruct();
    ASSERT_TRUE(ts2);
    EXPECT_EQ(ts2->a, 5);
    EXPECT_EQ(ts2->b, true);
    EXPECT_EQ(ts2->c, 3.2f);

    auto modStruct = testScript->getFunction<void, TestStruct2*>("modStruct(ref TestStruct2)");
    ASSERT_TRUE(testScriptStruct);
    modStruct(ts2);
    EXPECT_EQ(ts2->a, 5);
    EXPECT_EQ(ts2->b, true);
    EXPECT_EQ(ts2->c, 4.2f);

    auto testMemberFunc = testScript->getFunction<float, TestStruct2*>("testMemberFunc(ref TestStruct2)");
    ASSERT_TRUE(testMemberFunc);
    EXPECT_EQ(testMemberFunc(ts2), 5 + 4.2f);
    EXPECT_EQ(ts2->a, 5);
    EXPECT_EQ(ts2->b, true);
    EXPECT_EQ(ts2->c, 4.2f);
    delete ts2;

    auto nestedTest = testScript->getFunction<NestedStructBase*>("nestedTest()");
    ASSERT_TRUE(nestedTest);
    auto nestedStruct = nestedTest();
    // We don't test a and c as they are not initialized
    EXPECT_EQ(nestedStruct->b.x, 1.0f);
    EXPECT_EQ(nestedStruct->b.y, 4.0f);
    EXPECT_EQ(nestedStruct->b.z, 3.0f);
    delete nestedStruct;

#ifndef NDEBUG
    EXPECT_EQ(scriptMallocDiff, 3);
#endif
}
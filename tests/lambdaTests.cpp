
#include "testing.h"

#include "nativeTypes/BSLambda.h"
#include "script.h"
#include "scriptRuntime.h"

using namespace BraneScript;

TEST(BraneScript, Lambdas)
{
    BSLambda<int> testLambda;
    ASSERT_FALSE(testLambda);

    BSLambda<int> testLambda2((FuncRef<int, void*>)[](void* data)->int{
        return std::get<0>(*(std::tuple<int, float>*)data);
    }, 5, 2.f);
    ASSERT_EQ(testLambda2(), 5);
    ASSERT_TRUE(testLambda2);

    testLambda = testLambda2;
    ASSERT_TRUE(testLambda);

    ASSERT_NE(testLambda.data(), testLambda2.data());
    ASSERT_EQ(testLambda(), 5);
    ASSERT_EQ(testLambda2(), 5);

    std::string testString = R"(
    module "tests"
    link "lambda"
    {
        Lambda<int> returnInt(int value)
        {
            float capturedValue = value;
            return int Lambda[capturedValue]()
            {
                return capturedValue;
            };
        }

        int callLambda(ref Lambda<int> lambda)
        {
            return lambda();
        }
    }
)";

    StaticAnalyzer analyzer;
    analyzer.load("test", testString);
    analyzer.validate("test");
    checkCompileErrors(analyzer, testString);

    llvm::LLVMContext ctx;
    auto ir = analyzer.getCtx("test")->scriptContext->compile(&ctx, true, true);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    rt.loadLibrary(getLambdaLibrary());
    Module* testScript = rt.loadModule(ir.modules.at("tests"));
    ASSERT_TRUE(testScript);

    auto returnInt = testScript->getFunction<void, BSLambda<int>&, int>("tests::returnInt(ref lambda::Lambda<int>,int)");
    ASSERT_TRUE(returnInt);
    BSLambda<int> lambda;
    returnInt(lambda, 5);
    ASSERT_TRUE(lambda);
    EXPECT_EQ(lambda.captureSize(), sizeof(std::tuple<int>));
    EXPECT_EQ(lambda(), 5);

    auto callLambda = testScript->getFunction<int, BSLambda<int>&>("tests::callLambda(ref lambda::Lambda<int>)");
    ASSERT_TRUE(callLambda);
    EXPECT_EQ(callLambda(lambda), 5);
    
}

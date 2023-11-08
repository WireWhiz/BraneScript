
#include "testing.h"

#include <limits>
#include "script.h"
#include "scriptRuntime.h"
#include "analyzer.h"

using namespace BraneScript;

template<typename... Args>
std::string sformat(const char* format, Args... args)
{
    int size = std::snprintf(nullptr, 0, format, args...);
    if(size <= 0)
        throw std::runtime_error("String format error!");
    std::string output;
    output.resize(size);
    std::snprintf(output.data(), size + 1, format, args...);
    return std::move(output);
}

#define TEST_DUAL_ARG_OPERATOR(operator, function, argList)                                                            \
    for(auto& argPair : argList)                                                                                       \
        EXPECT_EQ(function(argPair.first, argPair.second), argPair.first operator argPair.second)                      \
            << "Operation args: " << argPair.first << ", " << argPair.second << std::endl;

void addScalarTestFunctions(const std::string& typeName, std::string& script)
{
    script += "\n" + sformat("%s add(%s a, %s b){return a + b;}%s sub(%s a, %s b){return a - b;}%s mul(%s a, %s "
                             "b){return a * b;}%s div(%s a, %s b){return a / b;}",
                             typeName.c_str(),
                             typeName.c_str(),
                             typeName.c_str(),
                             typeName.c_str(),
                             typeName.c_str(),
                             typeName.c_str(),
                             typeName.c_str(),
                             typeName.c_str(),
                             typeName.c_str(),
                             typeName.c_str(),
                             typeName.c_str(),
                             typeName.c_str());
}

template<typename T>
void runScalarTestFunctions(const std::string& typeName,
                            const Module* testScript,
                            const std::vector<std::pair<T, T>>& testArgs)
{
    auto add = testScript->getFunction<T, T, T>("tests::add");
    ASSERT_TRUE(add);
    TEST_DUAL_ARG_OPERATOR(+, add, testArgs);
    auto sub = testScript->getFunction<T, T, T>("tests::sub");
    ASSERT_TRUE(sub);
    TEST_DUAL_ARG_OPERATOR(-, sub, testArgs);
    auto mul = testScript->getFunction<T, T, T>("tests::mul");
    ASSERT_TRUE(mul);
    TEST_DUAL_ARG_OPERATOR(*, mul, testArgs);
    auto div = testScript->getFunction<T, T, T>("tests::div");
    ASSERT_TRUE(div);
    TEST_DUAL_ARG_OPERATOR(/, div, testArgs);
}

void testCasts(std::vector<std::string> typenames) {}

TEST(BraneScript, Operators)
{
    std::string testString = R"(
    module "tests"
    {
        bool testBoolCast(int a, int b)
        {
            return a > b;
        }

        bool testAnd(bool a, bool b)
        {
            return a && b;
        }

        bool testOr(bool a, bool b)
        {
            return a || b;
        }

        bool testNot(bool a)
        {
            return !a;
        }
)";

    auto scalarCasts = {"uint", "uint64", "int", "int64", "float", "double"};
    for(auto& targetType : scalarCasts)
    {
        for(auto& sourceType : scalarCasts)
        {
            if(targetType == sourceType)
                continue;
            testString += sformat("%s %sCast(%s v){return (%s)v;}", targetType, targetType, sourceType, targetType);
        }
    }

    addScalarTestFunctions("int", testString);
    addScalarTestFunctions("int64", testString);
    addScalarTestFunctions("uint", testString);
    addScalarTestFunctions("uint64", testString);
    addScalarTestFunctions("float", testString);
    addScalarTestFunctions("double", testString);

    testString += "}";

    Parser analyzer;
    std::string path = "testScripts/operatorTests.bs";
    analyzer.load(path, testString);
    analyzer.validate(path);
    checkCompileErrors(analyzer, path);

    llvm::LLVMContext ctx;
    auto ir = analyzer.getCtx(path)->scriptContext->compile(&ctx, CompileFlags_DebugInfo);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    auto testScript = rt.loadModule(ir.modules.at("tests"));

    // Casting
    auto testBoolCast = testScript->getFunction<bool, int, int>("tests::testBoolCast");
    ASSERT_TRUE(testBoolCast) << "Function was not found in script";
    EXPECT_TRUE(testBoolCast(5, 3));
    EXPECT_FALSE(testBoolCast(2, 4));

    //Logical
    auto testAnd = testScript->getFunction<bool, bool, bool>("tests::testAnd");
    ASSERT_TRUE(testAnd) << "Function was not found in script";
    EXPECT_TRUE(testAnd(true, true));
    EXPECT_FALSE(testAnd(true, false));
    EXPECT_FALSE(testAnd(false, true));
    EXPECT_FALSE(testAnd(false, false));

    auto testOr = testScript->getFunction<bool, bool, bool>("tests::testOr");
    ASSERT_TRUE(testOr) << "Function was not found in script";
    EXPECT_TRUE(testOr(true, true));
    EXPECT_TRUE(testOr(true, false));
    EXPECT_TRUE(testOr(false, true));
    EXPECT_FALSE(testOr(false, false));

    auto testNot = testScript->getFunction<bool, bool>("tests::testNot");
    ASSERT_TRUE(testNot) << "Function was not found in script";
    EXPECT_FALSE(testNot(true));
    EXPECT_TRUE(testNot(false));

    // Arithmetic
    runScalarTestFunctions<int32_t>("int",
                                    testScript.get(),
                                    {{0, 1},
                                     {1, 1},
                                     {2, 3},
                                     {3, 3},
                                     {123451, 12332169},
                                     {0, -1},
                                     {std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max()}});
    runScalarTestFunctions<int64_t>("int64",
                                    testScript.get(),
                                    {{0, 1},
                                     {1, 1},
                                     {2, 3},
                                     {3, 3},
                                     {123451, 12332169},
                                     {0, -1},
                                     {std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max()},
                                     {std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max()}});
    runScalarTestFunctions<uint32_t>(
        "uint", testScript.get(), {{0u, 1u}, {1u, 1u}, {2u, 3u}, {3u, 3u}, {123451u, 12332169u}});
    runScalarTestFunctions<uint64_t>(
        "uint64", testScript.get(), {{0lu, 1lu}, {1lu, 1lu}, {2lu, 3lu}, {3lu, 3lu}, {123451lu, 12332169lu}});
    runScalarTestFunctions<float>("float",
                                  testScript.get(),
                                  {{0.0f, 1.0f},
                                   {1.0f, 1.0f},
                                   {2.4f, 3.2f},
                                   {3.0f, 3.0f},
                                   {123451.0f, 12332169.0f},
                                   {0.0f, -1.0f},
                                   {-1234123.126414f, 12341612.4123f}});
    runScalarTestFunctions<double>("double",
                                   testScript.get(),
                                   {{0.0, 1.0},
                                    {1.0, 1.0},
                                    {2.4, 3.2},
                                    {3.0, 3.0},
                                    {123451.0, 12332169.0},
                                    {0.0, -1.0},
                                    {-1234123.126414, 12341612.4123}});
}
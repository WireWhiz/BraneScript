#include "testing.h"

#include <iostream>
#include "script.h"
#include "scriptRuntime.h"
#include "staticAnalysis/staticAnalyzer.h"

using namespace BraneScript;

// Returns time in milliseconds it takes for function f to run n times
template<typename F, typename T>
size_t speedTestFib(F f, T n, size_t count)
{
    auto start = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < count; ++i)
        f(n);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int iFib(int n)
{
    if(n < 2)
        return n;
    return iFib(n-1) + iFib(n-2);
}

float fFib(float n)
{
    if(n < 2)
        return n;
    return fFib(n-1) + fFib(n-2);
}

TEST(BraneScript, Speed)
{

    std::string testString = R"(

)";
    StaticAnalyzer analyzer;
    std::string path = "testScripts/speedTests.bs";
    analyzer.load(path);
    analyzer.validate(path);
    checkCompileErrors(analyzer, path);

    auto ir = analyzer.compile(path, CompileFlags_DebugInfo);
    ASSERT_TRUE(ir.modules.contains("tests"));

    ScriptRuntime rt;
    rt.resetMallocDiff();
    Module* testScript = rt.loadModule(ir.modules.at("tests"));
    ASSERT_TRUE(testScript);

    auto scIFib = testScript->getFunction<int, int>("tests::iFib");
    ASSERT_TRUE(scIFib);

    auto scFFib = testScript->getFunction<float, float>("tests::fFib");
    ASSERT_TRUE(scFFib);

    EXPECT_EQ(iFib(6), 8);
    EXPECT_EQ(fFib(6), 8.0f);
    EXPECT_EQ(scIFib(6), 8);
    EXPECT_EQ(scFFib(6), 8.0f);

    size_t c = 2000;
    int n = 30;
    std::cout << "Testing with n = " << n << ", " << c << " times" << std::endl;
    std::cout << "native int fib: " << speedTestFib(iFib, n, c) << " milliseconds" << std::endl;
    std::cout << "native float fib: " << speedTestFib(fFib, n, c) << " milliseconds" << std::endl;
    std::cout << "script int fib: " << speedTestFib(scIFib, n, c) << " milliseconds" << std::endl;
    std::cout << "script float fib: " << speedTestFib(scFFib, n, c) << " milliseconds" << std::endl;


}
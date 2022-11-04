#include <iostream>

#include "scripting/compiler.h"
#include "scripting/scriptRuntime.h"
#include "scripting/script.h"

 int countLoop(int target)
 {
     int counter = 0;
     while(counter < target)
         ++counter;
     return counter;
 }

 using CounterFunction = int (*)(int);
 void testLoop(CounterFunction func, int target)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    auto result = func(target);
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << "Counter with target " << target << " returned " << result << std::endl;
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    std::cout << "Function took " << nanoseconds << " nanoseconds or " << (double)nanoseconds / 1000000.0 << " milliseconds" << std::endl;
}

int main(const int argc, const char** argv)
{
    std::string testString = R"(
int main(int target) {
    int counter = 0;
    while(counter < target)
        counter = counter + 1;
    return counter;
}
)";

    Compiler compiler;
    auto* ir = compiler.compile(testString);
    if(!ir)
    {
        std::cout << "Failed to compile script!\n";
        for(auto& compileError: compiler.errors())
            std::cerr << compileError << std::endl;
        return 1;
    }

    ScriptRuntime rt;
    Script* testScript = rt.assembleScript(ir);

    std::cout << "native c++" << std::endl;
    testLoop(&countLoop, 1000000);
    std::cout << "Brane Script" << std::endl;
    auto testFunction = testScript->getFunction<int, int>("main");
    testLoop(testFunction, 1000000);

    return 0;
}

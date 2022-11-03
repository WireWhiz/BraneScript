#include <iostream>

#include "scripting/compiler.h"
#include "scripting/scriptRuntime.h"
#include "scripting/script.h"


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

    auto testFunction = testScript->getFunction<int, int>("main");
    std::cout << "Counter with target 3000 returned " << testFunction(3000) << std::endl;
    return 0;
}

#include <iostream>

#include "scripting/compiler.h"
#include "scripting/scriptRuntime.h"
#include "scripting/script.h"


int main(const int argc, const char** argv)
{
    std::string testString = "int main(int a, int b) { return a+ b +3 + 1;}";

    Compiler compiler;
    auto* ir = compiler.compile(testString);

    ScriptRuntime rt;
    auto* testScript = rt.assembleScript(ir);

    auto testFunction  = testScript->getFunction<int, int, int>("main");
    int result = testFunction(5, 2);
    std::cout << "Test result: " << result;
    return 0;
}

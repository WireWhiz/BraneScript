#include <iostream>

#include "scripting/compiler.h"
#include "scripting/scriptRuntime.h"
#include "scripting/script.h"


int main(const int argc, const char** argv)
{
    std::string testString = "float main(float a, int c, int b) { return a + c + 2; }";

    Compiler compiler;
    auto* ir = compiler.compile(testString);

    ScriptRuntime rt;
    Script* testScript = nullptr;

    testScript =  rt.assembleScript(ir);

    auto testFunction  = testScript->getFunction<float, float, int, int>("main");
    float result = testFunction(3.0f, 2.0f, 1);
    std::cout << "Test result: " << result;
    return 0;
}

#include <iostream>

#include "scripting/compiler.h"
#include "scripting/scriptRuntime.h"
#include "scripting/script.h"


int main(const int argc, const char** argv)
{
    std::string testString = "float main(float a, int b) { return a + b + 2; }";

    Compiler compiler;
    auto* ir = compiler.compile(testString);

    ScriptRuntime rt;
    Script* testScript = rt.assembleScript(ir);

    auto testFunction = testScript->getFunction<float, float, int>("main");
    float result = testFunction(3.0f, 2.0f);
    std::cout << "Test result: " << result;
    return 0;
}

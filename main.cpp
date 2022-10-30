#include <iostream>

#include "scripting/compiler.h"
#include "scripting/scriptRuntime.h"
#include "scripting/script.h"


int main(const int argc, const char** argv)
{
    std::string testString = R"(
bool main(float a, int b) {
    bool condition;
    if(a > b)
    {
        condition = true;
    }
    //return condition;
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

    auto testFunction = testScript->getFunction<bool, float, int>("main");
    std::cout << "Test result 3 < 5: " << (testFunction(3.0f, 5.0f) ? "true" : "false") << std::endl;
    std::cout << "Test result 5 < 3: " << (testFunction(5.0f, 3.0f) ? "true" : "false") << std::endl;
    return 0;
}

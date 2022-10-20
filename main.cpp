#include <iostream>

#include "scripting/compiler.h"
#include "scripting/scriptRuntime.h"
#include "scripting/script.h"


int main(const int argc, const char** argv)
{
    std::string testString = "int main(int a, int b) { return 2 - 4 + 6 * (a - b);}";

    Compiler compiler;
    auto* ir = compiler.compile(testString);

    ScriptRuntime rt;
    Script* testScript = nullptr;
    try{
        testScript =  rt.assembleScript(ir);
    }
    catch(const std::runtime_error& e)
    {
        std::cout << "assemble error: " << e.what() << std::endl;
        return 1;
    }

    auto testFunction  = testScript->getFunction<int, int, int>("main");
    int result = testFunction(5, 2);
    std::cout << "Test result: " << result;
    return 0;
}

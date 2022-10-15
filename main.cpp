#include <iostream>
#define ANTLR4CPP_STATIC

#include "scripting/compiler.h"

int main(const int argc, const char** argv)
{
    std::cout << "Hello Brane!" << std::endl;

    std::string args = "int res = ( 10 + 2 *2) * 3 / 4;";

    Compiler compiler;
    compiler.compile(args);
    return 0;
}

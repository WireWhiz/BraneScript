#include <iostream>
#define ANTLR4CPP_STATIC
#include "antlr4/braneLexer.h"
#include "antlr4/braneParser.h"
#include "antlr4/braneVisitor.h"

int main(const int argc, const char** argv)
{
    std::cout << "Hello Brane!" << std::endl;

    std::string args = "10*2+5f/3";

    antlr4::ANTLRInputStream input(args);
    braneLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    braneParser parser(&tokens);

    antlr4::tree::ParseTree *tree = parser.expr();
    std::cout << tree->toStringTree(true) << std::endl;

    return 0;
}

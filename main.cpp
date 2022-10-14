#include <iostream>
#define ANTLR4CPP_STATIC
#include "antlr4/braneLexer.h"
#include "antlr4/braneParser.h"
#include "antlr4/braneVisitor.h"
#include "antlr4/braneBaseVisitor.h"

class Visitor : public braneBaseVisitor
{
    std::any visitStatement(braneParser::StatementContext *ctx) override {
        std::cout << "Found statement: " << ctx->getText() << std::endl;
        auto res = braneBaseVisitor::visitStatement(ctx);
        return res;
    }

    std::any visitMuldiv(braneParser::MuldivContext *ctx) override {
        auto res = braneBaseVisitor::visitMuldiv(ctx);
        if(ctx->DIV())
            std::cout << "\tFound division: " << ctx->getText() << std::endl;
        else if(ctx->MUL())
            std::cout << "\tFound multiplication: " << ctx->getText() << std::endl;
        return res;
    }

    std::any visitAddsub(braneParser::AddsubContext *ctx) override {
        auto res = braneBaseVisitor::visitAddsub(ctx);
        if(ctx->ADD())
            std::cout << "\tFound addition: " << ctx->getText() << std::endl;
        else if(ctx->SUB())
            std::cout << "\tFound subtraction: " << ctx->getText() << std::endl;
        return res;
    }

    std::any visitNumber(braneParser::NumberContext *ctx) override {
        auto res = braneBaseVisitor::visitNumber(ctx);
        std::cout << "\tFound number: " << ctx->getText() << std::endl;
        return res;
    }
};

int main(const int argc, const char** argv)
{
    std::cout << "Hello Brane!" << std::endl;

    std::string args = "( 10 + 2 *5) * 3;";

    antlr4::ANTLRInputStream input(args);
    braneLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    braneParser parser(&tokens);

    Visitor visitor;
    visitor.visit(parser.program());
    return 0;
}

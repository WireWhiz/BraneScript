//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_COMPILER_H
#define BRANESCRIPT_COMPILER_H

#include <unordered_map>
#include <string>
#include <list>
#include <any>
#include <exception>

#include "../antlr4/braneBaseVisitor.h"

class TypeDef;
class Compiler : public braneBaseVisitor
{
    struct Variable
    {
        uint32_t memIndex = 0;
        TypeDef* def = nullptr;
    };
    struct Scope
    {
        std::unordered_map<std::string, Variable> _localVariables;
    };
    std::unordered_map<std::string, Variable> _globalVariables;
    std::list<Scope> _scopes;

public:
    struct CompileError
    {
        size_t start;
        size_t end;
        std::string message;
    };
private:
    std::vector<CompileError> _errors;

    std::any visitProgram(braneParser::ProgramContext *context);

    std::any visitStatement(braneParser::StatementContext *context);

    std::any visitInclude(braneParser::IncludeContext *context);

    std::any visitConstString(braneParser::ConstStringContext *context);

    std::any visitInlineScope(braneParser::InlineScopeContext *context) override;

    std::any visitAssignment(braneParser::AssignmentContext *context) override;

    std::any visitScope(braneParser::ScopeContext *context) override;

    std::any visitConstFloat(braneParser::ConstFloatContext *context) override;

    std::any visitAddsub(braneParser::AddsubContext *context) override;

    std::any visitConstInt(braneParser::ConstIntContext *context) override;

    std::any visitId(braneParser::IdContext *context) override;

    std::any visitDecl(braneParser::DeclContext *context) override;

    std::any visitMuldiv(braneParser::MuldivContext *context) override;

    std::any visitDeclaration(braneParser::DeclarationContext *context) override;

public:
    Compiler();
    bool compile(const std::string& script);
    const std::vector<CompileError>& errors() const;
};


#endif //BRANESCRIPT_COMPILER_H

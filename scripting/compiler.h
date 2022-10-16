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
#include "scriptFunction.h"
#include "irScript.h"

class TypeDef;
class Compiler : public braneBaseVisitor
{
    uint32_t _valueIndex = 0;
    struct Value
    {
        enum : uint8_t{
            Const = 1,
            Constexpr = 1 << 1,
            Temp = 1 << 2
        };
        uint8_t flags = 0;
        uint32_t valueIndex = 0;
        TypeDef* def = nullptr;
        inline bool isVoid() const{return def == nullptr;};
    };
    struct Scope
    {
        std::unordered_map<std::string, Value> localValues;
    };
    std::list<Scope> _scopes;

    IRScript* _currentScript = nullptr;
    ScriptFunction* _currentFunction = nullptr;
    std::unordered_map<std::string, TypeDef*> _types;
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

    std::any visitArgumentList(braneParser::ArgumentListContext *ctx) override;

    std::any visitFunction(braneParser::FunctionContext *ctx) override;

    std::any visitExprList(braneParser::ExprListContext *ctx) override;

    void registerType(TypeDef* type);
    Value newValue(const std::string& type, uint8_t flags);
    Value castTemp(const Value& value);

    void registerValue(std::string name, Value value);
    bool tryGetValue(const std::string&  name, Value& value);
    void pushScope();
    void popScope();

public:
    Compiler();
    IRScript* compile(const std::string& script);
    const std::vector<CompileError>& errors() const;
};


#endif //BRANESCRIPT_COMPILER_H

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
#include "aotNode/aotNode.h"
#include "aotNode/aotValueNodes.h"

class TypeDef;
class CompilerCtx;
class Compiler : public braneBaseVisitor
{

public:
    struct CompileError
    {
        size_t start;
        size_t end;
        std::string message;
    };
private:
    std::vector<CompileError> _errors;

    std::unique_ptr<CompilerCtx> _ctx;
    std::unordered_map<std::string, TypeDef*> _types;

    uint16_t _lValueIndex = 0;

    struct Scope
    {
        std::unordered_map<std::string, AotValueNode> localValues;
    };
    std::list<Scope> _scopes;

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

    std::any visitReturnVoid(braneParser::ReturnVoidContext *ctx) override;

    std::any visitReturnVal(braneParser::ReturnValContext *ctx) override;

    void registerLocalValue(std::string name, const std::string type, bool constant);
    AotNode* getValueNode(const std::string& name);
    void pushScope();
    void popScope();

public:
    Compiler();
    IRScript* compile(const std::string& script);
    const std::vector<CompileError>& errors() const;

    void registerType(TypeDef* type);
    const std::unordered_map<std::string, TypeDef*>& types() const;
};

struct CompilerCtx
{
    Compiler& compiler;
    uint32_t regIndex = 0;
    uint32_t memIndex = 0;

    IRScript* script = nullptr;
    ScriptFunction* function = nullptr;
    std::map<uint16_t, AotValue> lValues;

    CompilerCtx(Compiler& c, IRScript* s);

    AotValue newReg(const std::string& type, uint8_t flags);
    AotValue newConst(ValueType type, uint8_t flags = AotValue::Const | AotValue::Constexpr);
    AotValue castTemp(const AotValue& value);
    AotValue castReg(const AotValue& value);
};


#endif //BRANESCRIPT_COMPILER_H

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

namespace BraneScript
{
    class TypeDef;

    class CompilerCtx;

    class Compiler : public braneBaseVisitor
    {
    private:
        const std::string* _currentFile = nullptr;
        std::unique_ptr<CompilerCtx> _ctx;
        std::vector<std::string> _errors;

        std::unordered_map<std::string, TypeDef*> _types;

        uint16_t _lValueIndex = 0;

        struct Scope
        {
            std::unordered_map<std::string, AotValueNode> localValues;
        };
        std::list<Scope> _scopes;

        std::any visitProgram(braneParser::ProgramContext* context) override;

        std::any visitInclude(braneParser::IncludeContext* context) override;

        std::any visitConstString(braneParser::ConstStringContext* context) override;

        std::any visitInlineScope(braneParser::InlineScopeContext* context) override;

        std::any visitAssignment(braneParser::AssignmentContext* context) override;

        std::any visitScope(braneParser::ScopeContext* context) override;

        std::any visitConstFloat(braneParser::ConstFloatContext* context) override;

        std::any visitAddsub(braneParser::AddsubContext* context) override;

        std::any visitConstInt(braneParser::ConstIntContext* context) override;

        std::any visitId(braneParser::IdContext* context) override;

        std::any visitDecl(braneParser::DeclContext* context) override;

        std::any visitMuldiv(braneParser::MuldivContext* context) override;

        std::any visitDeclaration(braneParser::DeclarationContext* context) override;

        std::any visitArgumentList(braneParser::ArgumentListContext* ctx) override;

        std::any visitFunction(braneParser::FunctionContext* ctx) override;

        std::any visitExprStatement(braneParser::ExprStatementContext* context) override;

        std::any visitReturnVoid(braneParser::ReturnVoidContext* ctx) override;

        std::any visitReturnVal(braneParser::ReturnValContext* ctx) override;

        std::any visitCast(braneParser::CastContext* context) override;

        std::any visitConstBool(braneParser::ConstBoolContext* ctx) override;

        std::any visitIf(braneParser::IfContext* ctx) override;

        std::any visitWhile(braneParser::WhileContext* context) override;

        std::any visitComparison(braneParser::ComparisonContext* context) override;

        std::any visitArgumentPack(braneParser::ArgumentPackContext *context) override;

        std::any visitFunctionCall(braneParser::FunctionCallContext *context) override;

        bool localValueExists(const std::string& name);

        void registerLocalValue(std::string name, const std::string& type, bool constant);

        AotNode* getValueNode(const std::string& name);

        void pushScope();

        void popScope();

        friend class LexerErrorListener;

        friend class ParserErrorListener;

        void throwError(const std::string& message);

        void throwError(antlr4::Token* token, const std::string& message);

        void throwError(size_t line, size_t position, const std::string& context, const std::string& message);

        bool contextValid();

    public:

        Compiler();

        IRScript* compile(const std::string& script);

        const std::vector<std::string>& errors() const;

        void registerType(TypeDef* type);

        TypeDef* getType(const std::string& typeName);

        const std::unordered_map<std::string, TypeDef*>& types() const;
    };

    struct CompilerCtx
    {
        Compiler& compiler;
        uint32_t regIndex = 0;
        uint32_t memIndex = 0;
        uint32_t markIndex = 0;

        IRScript* script = nullptr;
        ScriptFunction* function = nullptr;
        bool returnCalled = false;
        std::map<uint16_t, AotValue> lValues;

        CompilerCtx(Compiler& c, IRScript* s);

        void setFunction(ScriptFunction* function);

        uint32_t newMark();

        AotValue newReg(const std::string& type, uint8_t flags);

        AotValue newReg(TypeDef* type, uint8_t flags);

        AotValue newConst(ValueType type, uint8_t flags = AotValue::Const | AotValue::Constexpr);

        AotValue castValue(const AotValue& value);

        AotValue castTemp(const AotValue& value);

        AotValue castReg(const AotValue& value);

    };

}
#endif //BRANESCRIPT_COMPILER_H

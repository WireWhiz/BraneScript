
// Generated from /home/wirewhiz/Documents/git/BraneEngine/libraries/internal/BraneScript/antlr4/brane.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "braneParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by braneParser.
 */
class  braneVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by braneParser.
   */
    virtual std::any visitProgram(braneParser::ProgramContext *context) = 0;

    virtual std::any visitProgSegment(braneParser::ProgSegmentContext *context) = 0;

    virtual std::any visitGlobal(braneParser::GlobalContext *context) = 0;

    virtual std::any visitTemplateDefArgument(braneParser::TemplateDefArgumentContext *context) = 0;

    virtual std::any visitTemplateDef(braneParser::TemplateDefContext *context) = 0;

    virtual std::any visitTemplateTypeArg(braneParser::TemplateTypeArgContext *context) = 0;

    virtual std::any visitTemplateExprArg(braneParser::TemplateExprArgContext *context) = 0;

    virtual std::any visitPackExpansionArg(braneParser::PackExpansionArgContext *context) = 0;

    virtual std::any visitTemplateArgs(braneParser::TemplateArgsContext *context) = 0;

    virtual std::any visitScopedID(braneParser::ScopedIDContext *context) = 0;

    virtual std::any visitType(braneParser::TypeContext *context) = 0;

    virtual std::any visitDeclaration(braneParser::DeclarationContext *context) = 0;

    virtual std::any visitArgumentListItem(braneParser::ArgumentListItemContext *context) = 0;

    virtual std::any visitArgumentList(braneParser::ArgumentListContext *context) = 0;

    virtual std::any visitArgumentPackItem(braneParser::ArgumentPackItemContext *context) = 0;

    virtual std::any visitArgumentPack(braneParser::ArgumentPackContext *context) = 0;

    virtual std::any visitFunctionSig(braneParser::FunctionSigContext *context) = 0;

    virtual std::any visitFunctionStub(braneParser::FunctionStubContext *context) = 0;

    virtual std::any visitFunction(braneParser::FunctionContext *context) = 0;

    virtual std::any visitLink(braneParser::LinkContext *context) = 0;

    virtual std::any visitExport(braneParser::ExportContext *context) = 0;

    virtual std::any visitExportSegment(braneParser::ExportSegmentContext *context) = 0;

    virtual std::any visitStructDef(braneParser::StructDefContext *context) = 0;

    virtual std::any visitMemberVariable(braneParser::MemberVariableContext *context) = 0;

    virtual std::any visitMemberFunction(braneParser::MemberFunctionContext *context) = 0;

    virtual std::any visitMemberFunctionStub(braneParser::MemberFunctionStubContext *context) = 0;

    virtual std::any visitExprStatement(braneParser::ExprStatementContext *context) = 0;

    virtual std::any visitAssignment(braneParser::AssignmentContext *context) = 0;

    virtual std::any visitScope(braneParser::ScopeContext *context) = 0;

    virtual std::any visitReturn(braneParser::ReturnContext *context) = 0;

    virtual std::any visitIf(braneParser::IfContext *context) = 0;

    virtual std::any visitWhile(braneParser::WhileContext *context) = 0;

    virtual std::any visitUnroll(braneParser::UnrollContext *context) = 0;

    virtual std::any visitMemberAccess(braneParser::MemberAccessContext *context) = 0;

    virtual std::any visitComparison(braneParser::ComparisonContext *context) = 0;

    virtual std::any visitDecl(braneParser::DeclContext *context) = 0;

    virtual std::any visitMakeRef(braneParser::MakeRefContext *context) = 0;

    virtual std::any visitAddsub(braneParser::AddsubContext *context) = 0;

    virtual std::any visitConstInt(braneParser::ConstIntContext *context) = 0;

    virtual std::any visitConstBool(braneParser::ConstBoolContext *context) = 0;

    virtual std::any visitSizeOfExpr(braneParser::SizeOfExprContext *context) = 0;

    virtual std::any visitMuldiv(braneParser::MuldivContext *context) = 0;

    virtual std::any visitIndexAccess(braneParser::IndexAccessContext *context) = 0;

    virtual std::any visitConstString(braneParser::ConstStringContext *context) = 0;

    virtual std::any visitCast(braneParser::CastContext *context) = 0;

    virtual std::any visitParen(braneParser::ParenContext *context) = 0;

    virtual std::any visitMemberFunctionCall(braneParser::MemberFunctionCallContext *context) = 0;

    virtual std::any visitSizeOfPack(braneParser::SizeOfPackContext *context) = 0;

    virtual std::any visitFunctionCall(braneParser::FunctionCallContext *context) = 0;

    virtual std::any visitConstFloat(braneParser::ConstFloatContext *context) = 0;

    virtual std::any visitSizeOfType(braneParser::SizeOfTypeContext *context) = 0;

    virtual std::any visitId(braneParser::IdContext *context) = 0;

    virtual std::any visitLogic(braneParser::LogicContext *context) = 0;

    virtual std::any visitConstChar(braneParser::ConstCharContext *context) = 0;


};


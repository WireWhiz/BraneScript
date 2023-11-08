
// Generated from /home/wirewhiz/CLionProjects/BraneScript/antlr4/brane.g4 by ANTLR 4.13.1

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
    virtual std::any visitModules(braneParser::ModulesContext *context) = 0;

    virtual std::any visitTags(braneParser::TagsContext *context) = 0;

    virtual std::any visitModule(braneParser::ModuleContext *context) = 0;

    virtual std::any visitModule_item(braneParser::Module_itemContext *context) = 0;

    virtual std::any visitImports(braneParser::ImportsContext *context) = 0;

    virtual std::any visitExports(braneParser::ExportsContext *context) = 0;

    virtual std::any visitImportModule(braneParser::ImportModuleContext *context) = 0;

    virtual std::any visitImportMemory(braneParser::ImportMemoryContext *context) = 0;

    virtual std::any visitMod_export(braneParser::Mod_exportContext *context) = 0;

    virtual std::any visitGlobal(braneParser::GlobalContext *context) = 0;

    virtual std::any visitTemplateDefArg(braneParser::TemplateDefArgContext *context) = 0;

    virtual std::any visitTemplateDef(braneParser::TemplateDefContext *context) = 0;

    virtual std::any visitTemplateTypeArg(braneParser::TemplateTypeArgContext *context) = 0;

    virtual std::any visitTemplateExprArg(braneParser::TemplateExprArgContext *context) = 0;

    virtual std::any visitPackExpansionArg(braneParser::PackExpansionArgContext *context) = 0;

    virtual std::any visitTemplateArgs(braneParser::TemplateArgsContext *context) = 0;

    virtual std::any visitScopedID(braneParser::ScopedIDContext *context) = 0;

    virtual std::any visitType(braneParser::TypeContext *context) = 0;

    virtual std::any visitValueType(braneParser::ValueTypeContext *context) = 0;

    virtual std::any visitRefType(braneParser::RefTypeContext *context) = 0;

    virtual std::any visitSliceType(braneParser::SliceTypeContext *context) = 0;

    virtual std::any visitDeclaration(braneParser::DeclarationContext *context) = 0;

    virtual std::any visitArgumentListItem(braneParser::ArgumentListItemContext *context) = 0;

    virtual std::any visitArgumentList(braneParser::ArgumentListContext *context) = 0;

    virtual std::any visitArgumentPackItem(braneParser::ArgumentPackItemContext *context) = 0;

    virtual std::any visitArgumentPack(braneParser::ArgumentPackContext *context) = 0;

    virtual std::any visitBracketOpr(braneParser::BracketOprContext *context) = 0;

    virtual std::any visitFunctionSig(braneParser::FunctionSigContext *context) = 0;

    virtual std::any visitFunctionStub(braneParser::FunctionStubContext *context) = 0;

    virtual std::any visitFunction(braneParser::FunctionContext *context) = 0;

    virtual std::any visitCapturedVar(braneParser::CapturedVarContext *context) = 0;

    virtual std::any visitVarCapture(braneParser::VarCaptureContext *context) = 0;

    virtual std::any visitStructDef(braneParser::StructDefContext *context) = 0;

    virtual std::any visitMemberFunctionStub(braneParser::MemberFunctionStubContext *context) = 0;

    virtual std::any visitMemberFunction(braneParser::MemberFunctionContext *context) = 0;

    virtual std::any visitMemberVariable(braneParser::MemberVariableContext *context) = 0;

    virtual std::any visitExpressions(braneParser::ExpressionsContext *context) = 0;

    virtual std::any visitDeref(braneParser::DerefContext *context) = 0;

    virtual std::any visitDecl(braneParser::DeclContext *context) = 0;

    virtual std::any visitFor(braneParser::ForContext *context) = 0;

    virtual std::any visitAddsub(braneParser::AddsubContext *context) = 0;

    virtual std::any visitPreDec(braneParser::PreDecContext *context) = 0;

    virtual std::any visitWhile(braneParser::WhileContext *context) = 0;

    virtual std::any visitSwitch(braneParser::SwitchContext *context) = 0;

    virtual std::any visitCast(braneParser::CastContext *context) = 0;

    virtual std::any visitParen(braneParser::ParenContext *context) = 0;

    virtual std::any visitLambda(braneParser::LambdaContext *context) = 0;

    virtual std::any visitNot(braneParser::NotContext *context) = 0;

    virtual std::any visitRef(braneParser::RefContext *context) = 0;

    virtual std::any visitMagicFunctionCall(braneParser::MagicFunctionCallContext *context) = 0;

    virtual std::any visitScope(braneParser::ScopeContext *context) = 0;

    virtual std::any visitId(braneParser::IdContext *context) = 0;

    virtual std::any visitIf(braneParser::IfContext *context) = 0;

    virtual std::any visitConstChar(braneParser::ConstCharContext *context) = 0;

    virtual std::any visitMemberAccess(braneParser::MemberAccessContext *context) = 0;

    virtual std::any visitComparison(braneParser::ComparisonContext *context) = 0;

    virtual std::any visitAssignment(braneParser::AssignmentContext *context) = 0;

    virtual std::any visitMatch(braneParser::MatchContext *context) = 0;

    virtual std::any visitConstBool(braneParser::ConstBoolContext *context) = 0;

    virtual std::any visitConstInt(braneParser::ConstIntContext *context) = 0;

    virtual std::any visitPostDec(braneParser::PostDecContext *context) = 0;

    virtual std::any visitMuldiv(braneParser::MuldivContext *context) = 0;

    virtual std::any visitPreInc(braneParser::PreIncContext *context) = 0;

    virtual std::any visitPostInc(braneParser::PostIncContext *context) = 0;

    virtual std::any visitIndexAccess(braneParser::IndexAccessContext *context) = 0;

    virtual std::any visitConstString(braneParser::ConstStringContext *context) = 0;

    virtual std::any visitFunctionCall(braneParser::FunctionCallContext *context) = 0;

    virtual std::any visitConstFloat(braneParser::ConstFloatContext *context) = 0;

    virtual std::any visitLogic(braneParser::LogicContext *context) = 0;

    virtual std::any visitReturn(braneParser::ReturnContext *context) = 0;

    virtual std::any visitSwitchCase(braneParser::SwitchCaseContext *context) = 0;

    virtual std::any visitMatchCase(braneParser::MatchCaseContext *context) = 0;

    virtual std::any visitSizeOfType(braneParser::SizeOfTypeContext *context) = 0;

    virtual std::any visitSizeOfPack(braneParser::SizeOfPackContext *context) = 0;

    virtual std::any visitFail(braneParser::FailContext *context) = 0;


};


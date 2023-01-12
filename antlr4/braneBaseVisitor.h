
// Generated from /home/wirewhiz/CLionProjects/BraneEngine/libraries/internal/BraneScript/antlr4/brane.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "braneVisitor.h"


/**
 * This class provides an empty implementation of braneVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  braneBaseVisitor : public braneVisitor {
public:

  virtual std::any visitProgram(braneParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgSegment(braneParser::ProgSegmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobal(braneParser::GlobalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(braneParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(braneParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(braneParser::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentPack(braneParser::ArgumentPackContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction(braneParser::FunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInclude(braneParser::IncludeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLink(braneParser::LinkContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructMember(braneParser::StructMemberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructMembers(braneParser::StructMembersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructDef(braneParser::StructDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprStatement(braneParser::ExprStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScope(braneParser::ScopeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnVal(braneParser::ReturnValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnVoid(braneParser::ReturnVoidContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf(braneParser::IfContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhile(braneParser::WhileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberAccess(braneParser::MemberAccessContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComparison(braneParser::ComparisonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecl(braneParser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInlineScope(braneParser::InlineScopeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(braneParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddsub(braneParser::AddsubContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstInt(braneParser::ConstIntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstBool(braneParser::ConstBoolContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDelete(braneParser::DeleteContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMuldiv(braneParser::MuldivContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndexAccess(braneParser::IndexAccessContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstString(braneParser::ConstStringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCast(braneParser::CastContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberFunctionCall(braneParser::MemberFunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(braneParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstFloat(braneParser::ConstFloatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitId(braneParser::IdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstChar(braneParser::ConstCharContext *ctx) override {
    return visitChildren(ctx);
  }


};


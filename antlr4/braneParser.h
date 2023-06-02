
// Generated from /home/wirewhiz/Documents/git/BraneEngine/libraries/internal/BraneScript/antlr4/brane.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  braneParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, COMMENT = 41, NEWLINE = 42, BLOCK_COMMENT = 43, 
    SPACE = 44, BOOL = 45, INT = 46, FLOAT = 47, CHAR = 48, STRING = 49, 
    ID = 50, MUL = 51, DIV = 52, ADD = 53, SUB = 54, LOGIC = 55
  };

  enum {
    RuleProgram = 0, RuleLink = 1, RuleLinkList = 2, RuleTags = 3, RuleModule = 4, 
    RuleModuleComponent = 5, RuleGlobal = 6, RuleTemplateDefArgument = 7, 
    RuleTemplateDef = 8, RuleTemplateArg = 9, RuleTemplateArgs = 10, RuleScopedID = 11, 
    RuleType = 12, RuleDeclaration = 13, RuleArgumentListItem = 14, RuleArgumentList = 15, 
    RuleArgumentPackItem = 16, RuleArgumentPack = 17, RuleBracketOpr = 18, 
    RuleFunctionSig = 19, RuleFunctionStub = 20, RuleFunction = 21, RuleCapturedVar = 22, 
    RuleVarCapture = 23, RuleStructDef = 24, RuleStructMember = 25, RuleStatement = 26, 
    RuleExpression = 27
  };

  explicit braneParser(antlr4::TokenStream *input);

  braneParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~braneParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class LinkContext;
  class LinkListContext;
  class TagsContext;
  class ModuleContext;
  class ModuleComponentContext;
  class GlobalContext;
  class TemplateDefArgumentContext;
  class TemplateDefContext;
  class TemplateArgContext;
  class TemplateArgsContext;
  class ScopedIDContext;
  class TypeContext;
  class DeclarationContext;
  class ArgumentListItemContext;
  class ArgumentListContext;
  class ArgumentPackItemContext;
  class ArgumentPackContext;
  class BracketOprContext;
  class FunctionSigContext;
  class FunctionStubContext;
  class FunctionContext;
  class CapturedVarContext;
  class VarCaptureContext;
  class StructDefContext;
  class StructMemberContext;
  class StatementContext;
  class ExpressionContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ModuleContext *> module();
    ModuleContext* module(size_t i);
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  LinkContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *isPublic = nullptr;
    antlr4::Token *library = nullptr;
    antlr4::Token *alias = nullptr;
    LinkContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LinkContext* link();

  class  LinkListContext : public antlr4::ParserRuleContext {
  public:
    LinkListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LinkContext *> link();
    LinkContext* link(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LinkListContext* linkList();

  class  TagsContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *tag = nullptr;
    TagsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TagsContext* tags();

  class  ModuleContext : public antlr4::ParserRuleContext {
  public:
    braneParser::TagsContext *modTags = nullptr;
    antlr4::Token *id = nullptr;
    ModuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LinkListContext *linkList();
    antlr4::tree::TerminalNode *STRING();
    std::vector<ModuleComponentContext *> moduleComponent();
    ModuleComponentContext* moduleComponent(size_t i);
    TagsContext *tags();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ModuleContext* module();

  class  ModuleComponentContext : public antlr4::ParserRuleContext {
  public:
    ModuleComponentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionContext *function();
    FunctionStubContext *functionStub();
    StructDefContext *structDef();
    GlobalContext *global();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ModuleComponentContext* moduleComponent();

  class  GlobalContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *id = nullptr;
    GlobalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *ID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GlobalContext* global();

  class  TemplateDefArgumentContext : public antlr4::ParserRuleContext {
  public:
    braneParser::TypeContext *exprType = nullptr;
    antlr4::Token *isTypedef = nullptr;
    antlr4::Token *isPack = nullptr;
    antlr4::Token *id = nullptr;
    TemplateDefArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    TypeContext *type();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TemplateDefArgumentContext* templateDefArgument();

  class  TemplateDefContext : public antlr4::ParserRuleContext {
  public:
    TemplateDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TemplateDefArgumentContext *> templateDefArgument();
    TemplateDefArgumentContext* templateDefArgument(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TemplateDefContext* templateDef();

  class  TemplateArgContext : public antlr4::ParserRuleContext {
  public:
    TemplateArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TemplateArgContext() = default;
    void copyFrom(TemplateArgContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TemplateTypeArgContext : public TemplateArgContext {
  public:
    TemplateTypeArgContext(TemplateArgContext *ctx);

    braneParser::TypeContext *t = nullptr;
    TypeContext *type();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PackExpansionArgContext : public TemplateArgContext {
  public:
    PackExpansionArgContext(TemplateArgContext *ctx);

    antlr4::Token *packID = nullptr;
    antlr4::tree::TerminalNode *ID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TemplateExprArgContext : public TemplateArgContext {
  public:
    TemplateExprArgContext(TemplateArgContext *ctx);

    braneParser::ExpressionContext *expr = nullptr;
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TemplateArgContext* templateArg();

  class  TemplateArgsContext : public antlr4::ParserRuleContext {
  public:
    TemplateArgsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TemplateArgContext *> templateArg();
    TemplateArgContext* templateArg(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TemplateArgsContext* templateArgs();

  class  ScopedIDContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *id = nullptr;
    braneParser::TemplateArgsContext *template_ = nullptr;
    braneParser::ScopedIDContext *child = nullptr;
    ScopedIDContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    TemplateArgsContext *templateArgs();
    ScopedIDContext *scopedID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScopedIDContext* scopedID();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *isConst = nullptr;
    antlr4::Token *isRef = nullptr;
    braneParser::ScopedIDContext *name = nullptr;
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ScopedIDContext *scopedID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *id = nullptr;
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *ID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationContext* declaration();

  class  ArgumentListItemContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *pack = nullptr;
    antlr4::Token *id = nullptr;
    ArgumentListItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclarationContext *declaration();
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentListItemContext* argumentListItem();

  class  ArgumentListContext : public antlr4::ParserRuleContext {
  public:
    ArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgumentListItemContext *> argumentListItem();
    ArgumentListItemContext* argumentListItem(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentListContext* argumentList();

  class  ArgumentPackItemContext : public antlr4::ParserRuleContext {
  public:
    braneParser::ExpressionContext *expr = nullptr;
    antlr4::Token *packID = nullptr;
    ArgumentPackItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentPackItemContext* argumentPackItem();

  class  ArgumentPackContext : public antlr4::ParserRuleContext {
  public:
    ArgumentPackContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgumentPackItemContext *> argumentPackItem();
    ArgumentPackItemContext* argumentPackItem(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentPackContext* argumentPack();

  class  BracketOprContext : public antlr4::ParserRuleContext {
  public:
    BracketOprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BracketOprContext* bracketOpr();

  class  FunctionSigContext : public antlr4::ParserRuleContext {
  public:
    braneParser::TagsContext *funcTags = nullptr;
    braneParser::TemplateDefContext *template_ = nullptr;
    antlr4::Token *isConstexpr = nullptr;
    antlr4::Token *id = nullptr;
    antlr4::Token *oprID = nullptr;
    braneParser::BracketOprContext *bracketOprID = nullptr;
    braneParser::TypeContext *castType = nullptr;
    FunctionSigContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TagsContext *tags();
    TemplateDefContext *templateDef();
    TypeContext *type();
    antlr4::tree::TerminalNode *ID();
    BracketOprContext *bracketOpr();
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *SUB();
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *LOGIC();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionSigContext* functionSig();

  class  FunctionStubContext : public antlr4::ParserRuleContext {
  public:
    braneParser::FunctionSigContext *sig = nullptr;
    braneParser::ArgumentListContext *arguments = nullptr;
    antlr4::Token *isConst = nullptr;
    FunctionStubContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionSigContext *functionSig();
    ArgumentListContext *argumentList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionStubContext* functionStub();

  class  FunctionContext : public antlr4::ParserRuleContext {
  public:
    braneParser::FunctionSigContext *sig = nullptr;
    braneParser::ArgumentListContext *arguments = nullptr;
    antlr4::Token *isConst = nullptr;
    braneParser::StatementContext *statements = nullptr;
    FunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionSigContext *functionSig();
    ArgumentListContext *argumentList();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionContext* function();

  class  CapturedVarContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *isRef = nullptr;
    braneParser::ScopedIDContext *id = nullptr;
    CapturedVarContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ScopedIDContext *scopedID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CapturedVarContext* capturedVar();

  class  VarCaptureContext : public antlr4::ParserRuleContext {
  public:
    VarCaptureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CapturedVarContext *> capturedVar();
    CapturedVarContext* capturedVar(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarCaptureContext* varCapture();

  class  StructDefContext : public antlr4::ParserRuleContext {
  public:
    braneParser::TagsContext *structTags = nullptr;
    braneParser::TemplateDefContext *template_ = nullptr;
    antlr4::Token *packed = nullptr;
    antlr4::Token *id = nullptr;
    braneParser::StructMemberContext *memberVars = nullptr;
    StructDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    TagsContext *tags();
    TemplateDefContext *templateDef();
    std::vector<StructMemberContext *> structMember();
    StructMemberContext* structMember(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDefContext* structDef();

  class  StructMemberContext : public antlr4::ParserRuleContext {
  public:
    StructMemberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StructMemberContext() = default;
    void copyFrom(StructMemberContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MemberVariableContext : public StructMemberContext {
  public:
    MemberVariableContext(StructMemberContext *ctx);

    braneParser::DeclarationContext *var = nullptr;
    DeclarationContext *declaration();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MemberFunctionStubContext : public StructMemberContext {
  public:
    MemberFunctionStubContext(StructMemberContext *ctx);

    FunctionStubContext *functionStub();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MemberFunctionContext : public StructMemberContext {
  public:
    MemberFunctionContext(StructMemberContext *ctx);

    braneParser::FunctionContext *func = nullptr;
    FunctionContext *function();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StructMemberContext* structMember();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StatementContext() = default;
    void copyFrom(StatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AssignmentContext : public StatementContext {
  public:
    AssignmentContext(StatementContext *ctx);

    braneParser::ExpressionContext *lValue = nullptr;
    braneParser::ExpressionContext *rValue = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ScopeContext : public StatementContext {
  public:
    ScopeContext(StatementContext *ctx);

    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprStatementContext : public StatementContext {
  public:
    ExprStatementContext(StatementContext *ctx);

    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RefAssignmentContext : public StatementContext {
  public:
    RefAssignmentContext(StatementContext *ctx);

    braneParser::ExpressionContext *lValue = nullptr;
    braneParser::ExpressionContext *rValue = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WhileContext : public StatementContext {
  public:
    WhileContext(StatementContext *ctx);

    braneParser::ExpressionContext *cond = nullptr;
    braneParser::StatementContext *operation = nullptr;
    ExpressionContext *expression();
    StatementContext *statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnrollContext : public StatementContext {
  public:
    UnrollContext(StatementContext *ctx);

    antlr4::Token *id = nullptr;
    braneParser::StatementContext *body = nullptr;
    antlr4::tree::TerminalNode *ID();
    StatementContext *statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfContext : public StatementContext {
  public:
    IfContext(StatementContext *ctx);

    braneParser::ExpressionContext *cond = nullptr;
    braneParser::StatementContext *operation = nullptr;
    braneParser::StatementContext *elseOp = nullptr;
    ExpressionContext *expression();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ReturnContext : public StatementContext {
  public:
    ReturnContext(StatementContext *ctx);

    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StatementContext* statement();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MemberAccessContext : public ExpressionContext {
  public:
    MemberAccessContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *base = nullptr;
    antlr4::Token *member = nullptr;
    braneParser::TemplateArgsContext *template_ = nullptr;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ID();
    TemplateArgsContext *templateArgs();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ComparisonContext : public ExpressionContext {
  public:
    ComparisonContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *left = nullptr;
    antlr4::Token *opr = nullptr;
    braneParser::ExpressionContext *right = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DeclContext : public ExpressionContext {
  public:
    DeclContext(ExpressionContext *ctx);

    DeclarationContext *declaration();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddsubContext : public ExpressionContext {
  public:
    AddsubContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *left = nullptr;
    antlr4::Token *opr = nullptr;
    braneParser::ExpressionContext *right = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *SUB();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstIntContext : public ExpressionContext {
  public:
    ConstIntContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *INT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstBoolContext : public ExpressionContext {
  public:
    ConstBoolContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *BOOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MuldivContext : public ExpressionContext {
  public:
    MuldivContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *left = nullptr;
    antlr4::Token *opr = nullptr;
    braneParser::ExpressionContext *right = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IndexAccessContext : public ExpressionContext {
  public:
    IndexAccessContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *base = nullptr;
    braneParser::ExpressionContext *arg = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstStringContext : public ExpressionContext {
  public:
    ConstStringContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *STRING();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CastContext : public ExpressionContext {
  public:
    CastContext(ExpressionContext *ctx);

    TypeContext *type();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NotContext : public ExpressionContext {
  public:
    NotContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *value = nullptr;
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenContext : public ExpressionContext {
  public:
    ParenContext(ExpressionContext *ctx);

    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LambdaContext : public ExpressionContext {
  public:
    LambdaContext(ExpressionContext *ctx);

    braneParser::TypeContext *returnType = nullptr;
    antlr4::Token *label = nullptr;
    braneParser::VarCaptureContext *capture = nullptr;
    braneParser::ArgumentListContext *arguments = nullptr;
    TypeContext *type();
    ArgumentListContext *argumentList();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    VarCaptureContext *varCapture();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SizeOfPackContext : public ExpressionContext {
  public:
    SizeOfPackContext(ExpressionContext *ctx);

    antlr4::Token *id = nullptr;
    antlr4::tree::TerminalNode *ID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionCallContext : public ExpressionContext {
  public:
    FunctionCallContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *overrides = nullptr;
    ArgumentPackContext *argumentPack();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstFloatContext : public ExpressionContext {
  public:
    ConstFloatContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *FLOAT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SizeOfTypeContext : public ExpressionContext {
  public:
    SizeOfTypeContext(ExpressionContext *ctx);

    braneParser::TypeContext *t = nullptr;
    TypeContext *type();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdContext : public ExpressionContext {
  public:
    IdContext(ExpressionContext *ctx);

    ScopedIDContext *scopedID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LogicContext : public ExpressionContext {
  public:
    LogicContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *left = nullptr;
    antlr4::Token *opr = nullptr;
    braneParser::ExpressionContext *right = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LOGIC();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstCharContext : public ExpressionContext {
  public:
    ConstCharContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *CHAR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);

  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};


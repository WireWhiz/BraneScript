
// Generated from /home/wirewhiz/Documents/git/BraneEngine/libraries/internal/BraneScript/antlr4/brane.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"




class  braneParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, NEWLINE = 25, COMMENT = 26, 
    BLOCK_COMMENT = 27, SPACE = 28, BOOL = 29, INT = 30, FLOAT = 31, CHAR = 32, 
    STRING = 33, ID = 34, MUL = 35, DIV = 36, ADD = 37, SUB = 38, COMPARE = 39, 
    LOGIC = 40
  };

  enum {
    RuleProgram = 0, RuleProgSegment = 1, RuleGlobal = 2, RuleType = 3, 
    RuleDeclaration = 4, RuleArgumentList = 5, RuleArgumentPack = 6, RuleFunctionStub = 7, 
    RuleFunction = 8, RuleLink = 9, RuleExport = 10, RuleExportSegment = 11, 
    RuleStructMember = 12, RuleStructMembers = 13, RuleStructDef = 14, RuleStatement = 15, 
    RuleExpression = 16
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
  class ProgSegmentContext;
  class GlobalContext;
  class TypeContext;
  class DeclarationContext;
  class ArgumentListContext;
  class ArgumentPackContext;
  class FunctionStubContext;
  class FunctionContext;
  class LinkContext;
  class ExportContext;
  class ExportSegmentContext;
  class StructMemberContext;
  class StructMembersContext;
  class StructDefContext;
  class StatementContext;
  class ExpressionContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<ProgSegmentContext *> progSegment();
    ProgSegmentContext* progSegment(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  ProgSegmentContext : public antlr4::ParserRuleContext {
  public:
    ProgSegmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionContext *function();
    FunctionStubContext *functionStub();
    StructDefContext *structDef();
    GlobalContext *global();
    LinkContext *link();
    ExportContext *export_();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgSegmentContext* progSegment();

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

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *isConst = nullptr;
    antlr4::Token *isRef = nullptr;
    antlr4::Token *id = nullptr;
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();


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

  class  ArgumentListContext : public antlr4::ParserRuleContext {
  public:
    ArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentListContext* argumentList();

  class  ArgumentPackContext : public antlr4::ParserRuleContext {
  public:
    ArgumentPackContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentPackContext* argumentPack();

  class  FunctionStubContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *id = nullptr;
    antlr4::Token *oprID = nullptr;
    braneParser::TypeContext *castType = nullptr;
    braneParser::ArgumentListContext *arguments = nullptr;
    antlr4::Token *isConst = nullptr;
    FunctionStubContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArgumentListContext *argumentList();
    TypeContext *type();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *SUB();
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *COMPARE();
    antlr4::tree::TerminalNode *LOGIC();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionStubContext* functionStub();

  class  FunctionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *id = nullptr;
    antlr4::Token *oprID = nullptr;
    braneParser::TypeContext *castType = nullptr;
    braneParser::ArgumentListContext *arguments = nullptr;
    antlr4::Token *isConst = nullptr;
    braneParser::StatementContext *statements = nullptr;
    FunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArgumentListContext *argumentList();
    TypeContext *type();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *SUB();
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *COMPARE();
    antlr4::tree::TerminalNode *LOGIC();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionContext* function();

  class  LinkContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *library = nullptr;
    antlr4::Token *alias = nullptr;
    LinkContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LinkContext* link();

  class  ExportContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *libID = nullptr;
    ExportContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();
    std::vector<ExportSegmentContext *> exportSegment();
    ExportSegmentContext* exportSegment(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExportContext* export_();

  class  ExportSegmentContext : public antlr4::ParserRuleContext {
  public:
    ExportSegmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionContext *function();
    FunctionStubContext *functionStub();
    StructDefContext *structDef();
    GlobalContext *global();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExportSegmentContext* exportSegment();

  class  StructMemberContext : public antlr4::ParserRuleContext {
  public:
    braneParser::DeclarationContext *var = nullptr;
    braneParser::FunctionContext *func = nullptr;
    StructMemberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclarationContext *declaration();
    FunctionContext *function();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructMemberContext* structMember();

  class  StructMembersContext : public antlr4::ParserRuleContext {
  public:
    StructMembersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StructMemberContext *> structMember();
    StructMemberContext* structMember(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructMembersContext* structMembers();

  class  StructDefContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *packed = nullptr;
    antlr4::Token *id = nullptr;
    braneParser::StructMembersContext *memberVars = nullptr;
    StructDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    StructMembersContext *structMembers();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDefContext* structDef();

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

  class  WhileContext : public StatementContext {
  public:
    WhileContext(StatementContext *ctx);

    braneParser::ExpressionContext *cond = nullptr;
    braneParser::StatementContext *operation = nullptr;
    ExpressionContext *expression();
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
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ID();

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
    antlr4::tree::TerminalNode *COMPARE();

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

  class  ParenContext : public ExpressionContext {
  public:
    ParenContext(ExpressionContext *ctx);

    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MemberFunctionCallContext : public ExpressionContext {
  public:
    MemberFunctionCallContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *base = nullptr;
    antlr4::Token *name = nullptr;
    ArgumentPackContext *argumentPack();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionCallContext : public ExpressionContext {
  public:
    FunctionCallContext(ExpressionContext *ctx);

    antlr4::Token *name = nullptr;
    ArgumentPackContext *argumentPack();
    antlr4::tree::TerminalNode *ID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstFloatContext : public ExpressionContext {
  public:
    ConstFloatContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *FLOAT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdContext : public ExpressionContext {
  public:
    IdContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *ID();

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


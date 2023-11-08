
// Generated from /home/wirewhiz/CLionProjects/BraneScript/antlr4/brane.g4 by ANTLR 4.13.1

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
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, COMMENT = 49, NEWLINE = 50, 
    BLOCK_COMMENT = 51, SPACE = 52, BOOL = 53, INT = 54, FLOAT = 55, CHAR = 56, 
    STRING = 57, ID = 58, MUL = 59, DIV = 60, ADD = 61, SUB = 62, LOGIC = 63
  };

  enum {
    RuleModules = 0, RuleTags = 1, RuleModule = 2, RuleModule_item = 3, 
    RuleImports = 4, RuleExports = 5, RuleMod_import = 6, RuleMod_export = 7, 
    RuleGlobal = 8, RuleTemplateDefArg = 9, RuleTemplateDef = 10, RuleTemplateArg = 11, 
    RuleTemplateArgs = 12, RuleScopedID = 13, RuleType = 14, RuleValueType = 15, 
    RuleRefType = 16, RuleSliceType = 17, RuleDeclaration = 18, RuleArgumentListItem = 19, 
    RuleArgumentList = 20, RuleArgumentPackItem = 21, RuleArgumentPack = 22, 
    RuleBracketOpr = 23, RuleFunctionSig = 24, RuleFunctionStub = 25, RuleFunction = 26, 
    RuleCapturedVar = 27, RuleVarCapture = 28, RuleStructDef = 29, RuleStructMember = 30, 
    RuleExpressions = 31, RuleExpression = 32, RuleSwitchCase = 33, RuleMatchCase = 34, 
    RuleMagicFunction = 35
  };

  explicit braneParser(antlr4::TokenStream *input);

  braneParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~braneParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ModulesContext;
  class TagsContext;
  class ModuleContext;
  class Module_itemContext;
  class ImportsContext;
  class ExportsContext;
  class Mod_importContext;
  class Mod_exportContext;
  class GlobalContext;
  class TemplateDefArgContext;
  class TemplateDefContext;
  class TemplateArgContext;
  class TemplateArgsContext;
  class ScopedIDContext;
  class TypeContext;
  class ValueTypeContext;
  class RefTypeContext;
  class SliceTypeContext;
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
  class ExpressionsContext;
  class ExpressionContext;
  class SwitchCaseContext;
  class MatchCaseContext;
  class MagicFunctionContext; 

  class  ModulesContext : public antlr4::ParserRuleContext {
  public:
    ModulesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ModuleContext *> module();
    ModuleContext* module(size_t i);
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ModulesContext* modules();

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
    antlr4::tree::TerminalNode *STRING();
    std::vector<Module_itemContext *> module_item();
    Module_itemContext* module_item(size_t i);
    TagsContext *tags();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ModuleContext* module();

  class  Module_itemContext : public antlr4::ParserRuleContext {
  public:
    Module_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImportsContext *imports();
    ExportsContext *exports();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Module_itemContext* module_item();

  class  ImportsContext : public antlr4::ParserRuleContext {
  public:
    ImportsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Mod_importContext *> mod_import();
    Mod_importContext* mod_import(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportsContext* imports();

  class  ExportsContext : public antlr4::ParserRuleContext {
  public:
    ExportsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Mod_exportContext *> mod_export();
    Mod_exportContext* mod_export(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExportsContext* exports();

  class  Mod_importContext : public antlr4::ParserRuleContext {
  public:
    Mod_importContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Mod_importContext() = default;
    void copyFrom(Mod_importContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ImportModuleContext : public Mod_importContext {
  public:
    ImportModuleContext(Mod_importContext *ctx);

    antlr4::Token *id = nullptr;
    antlr4::tree::TerminalNode *STRING();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ImportMemoryContext : public Mod_importContext {
  public:
    ImportMemoryContext(Mod_importContext *ctx);

    antlr4::Token *id = nullptr;
    antlr4::tree::TerminalNode *STRING();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Mod_importContext* mod_import();

  class  Mod_exportContext : public antlr4::ParserRuleContext {
  public:
    Mod_exportContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionContext *function();
    StructDefContext *structDef();
    GlobalContext *global();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mod_exportContext* mod_export();

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

  class  TemplateDefArgContext : public antlr4::ParserRuleContext {
  public:
    braneParser::TypeContext *exprType = nullptr;
    antlr4::Token *isTypedef = nullptr;
    antlr4::Token *isPack = nullptr;
    antlr4::Token *id = nullptr;
    TemplateDefArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    TypeContext *type();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TemplateDefArgContext* templateDefArg();

  class  TemplateDefContext : public antlr4::ParserRuleContext {
  public:
    TemplateDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TemplateDefArgContext *> templateDefArg();
    TemplateDefArgContext* templateDefArg(size_t i);


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
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ValueTypeContext *valueType();
    RefTypeContext *refType();
    SliceTypeContext *sliceType();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  ValueTypeContext : public antlr4::ParserRuleContext {
  public:
    braneParser::ScopedIDContext *name = nullptr;
    ValueTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ScopedIDContext *scopedID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueTypeContext* valueType();

  class  RefTypeContext : public antlr4::ParserRuleContext {
  public:
    braneParser::ScopedIDContext *refSource = nullptr;
    RefTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    ScopedIDContext *scopedID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RefTypeContext* refType();

  class  SliceTypeContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *size = nullptr;
    SliceTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *INT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SliceTypeContext* sliceType();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *mut = nullptr;
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
    braneParser::ExpressionsContext *content = nullptr;
    FunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionSigContext *functionSig();
    ArgumentListContext *argumentList();
    ExpressionsContext *expressions();


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

  class  ExpressionsContext : public antlr4::ParserRuleContext {
  public:
    braneParser::ExpressionContext *returnValue = nullptr;
    ExpressionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionsContext* expressions();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DerefContext : public ExpressionContext {
  public:
    DerefContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *value = nullptr;
    antlr4::tree::TerminalNode *MUL();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DeclContext : public ExpressionContext {
  public:
    DeclContext(ExpressionContext *ctx);

    DeclarationContext *declaration();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ForContext : public ExpressionContext {
  public:
    ForContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *init = nullptr;
    braneParser::ExpressionContext *cond = nullptr;
    braneParser::ExpressionContext *step = nullptr;
    braneParser::ExpressionContext *operation = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

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

  class  PreDecContext : public ExpressionContext {
  public:
    PreDecContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *value = nullptr;
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WhileContext : public ExpressionContext {
  public:
    WhileContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *cond = nullptr;
    braneParser::ExpressionContext *operation = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SwitchContext : public ExpressionContext {
  public:
    SwitchContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *value = nullptr;
    ExpressionContext *expression();
    std::vector<SwitchCaseContext *> switchCase();
    SwitchCaseContext* switchCase(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CastContext : public ExpressionContext {
  public:
    CastContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *expr = nullptr;
    braneParser::TypeContext *targetType = nullptr;
    ExpressionContext *expression();
    TypeContext *type();

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
    braneParser::ExpressionsContext *content = nullptr;
    TypeContext *type();
    ArgumentListContext *argumentList();
    ExpressionsContext *expressions();
    VarCaptureContext *varCapture();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NotContext : public ExpressionContext {
  public:
    NotContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *value = nullptr;
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RefContext : public ExpressionContext {
  public:
    RefContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *value = nullptr;
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MagicFunctionCallContext : public ExpressionContext {
  public:
    MagicFunctionCallContext(ExpressionContext *ctx);

    MagicFunctionContext *magicFunction();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ScopeContext : public ExpressionContext {
  public:
    ScopeContext(ExpressionContext *ctx);

    braneParser::ExpressionsContext *content = nullptr;
    ExpressionsContext *expressions();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdContext : public ExpressionContext {
  public:
    IdContext(ExpressionContext *ctx);

    ScopedIDContext *scopedID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfContext : public ExpressionContext {
  public:
    IfContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *cond = nullptr;
    braneParser::ExpressionContext *operation = nullptr;
    braneParser::ExpressionContext *elseOp = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstCharContext : public ExpressionContext {
  public:
    ConstCharContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *CHAR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
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

  class  AssignmentContext : public ExpressionContext {
  public:
    AssignmentContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *left = nullptr;
    braneParser::ExpressionContext *right = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MatchContext : public ExpressionContext {
  public:
    MatchContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *value = nullptr;
    ExpressionContext *expression();
    std::vector<MatchCaseContext *> matchCase();
    MatchCaseContext* matchCase(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstBoolContext : public ExpressionContext {
  public:
    ConstBoolContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *BOOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstIntContext : public ExpressionContext {
  public:
    ConstIntContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *INT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PostDecContext : public ExpressionContext {
  public:
    PostDecContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *value = nullptr;
    ExpressionContext *expression();

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

  class  PreIncContext : public ExpressionContext {
  public:
    PreIncContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *value = nullptr;
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PostIncContext : public ExpressionContext {
  public:
    PostIncContext(ExpressionContext *ctx);

    braneParser::ExpressionContext *value = nullptr;
    ExpressionContext *expression();

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

  class  ReturnContext : public ExpressionContext {
  public:
    ReturnContext(ExpressionContext *ctx);

    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  SwitchCaseContext : public antlr4::ParserRuleContext {
  public:
    braneParser::ExpressionContext *value = nullptr;
    braneParser::ExpressionsContext *content = nullptr;
    SwitchCaseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    ExpressionsContext *expressions();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SwitchCaseContext* switchCase();

  class  MatchCaseContext : public antlr4::ParserRuleContext {
  public:
    braneParser::ExpressionContext *pattern = nullptr;
    braneParser::ExpressionsContext *content = nullptr;
    MatchCaseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    ExpressionsContext *expressions();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchCaseContext* matchCase();

  class  MagicFunctionContext : public antlr4::ParserRuleContext {
  public:
    MagicFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    MagicFunctionContext() = default;
    void copyFrom(MagicFunctionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FailContext : public MagicFunctionContext {
  public:
    FailContext(MagicFunctionContext *ctx);

    antlr4::Token *message = nullptr;
    antlr4::tree::TerminalNode *STRING();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SizeOfPackContext : public MagicFunctionContext {
  public:
    SizeOfPackContext(MagicFunctionContext *ctx);

    antlr4::Token *id = nullptr;
    antlr4::tree::TerminalNode *ID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SizeOfTypeContext : public MagicFunctionContext {
  public:
    SizeOfTypeContext(MagicFunctionContext *ctx);

    braneParser::TypeContext *t = nullptr;
    TypeContext *type();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  MagicFunctionContext* magicFunction();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};


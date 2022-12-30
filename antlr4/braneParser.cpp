
// Generated from C:/Users/eli/Documents/GitHub/BraneScript/antlr4\brane.g4 by ANTLR 4.10.1


#include "braneVisitor.h"

#include "braneParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct BraneParserStaticData final {
  BraneParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  BraneParserStaticData(const BraneParserStaticData&) = delete;
  BraneParserStaticData(BraneParserStaticData&&) = delete;
  BraneParserStaticData& operator=(const BraneParserStaticData&) = delete;
  BraneParserStaticData& operator=(BraneParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag braneParserOnceFlag;
BraneParserStaticData *braneParserStaticData = nullptr;

void braneParserInitialize() {
  assert(braneParserStaticData == nullptr);
  auto staticData = std::make_unique<BraneParserStaticData>(
    std::vector<std::string>{
      "program", "progSegment", "type", "declaration", "argumentList", "argumentPack", 
      "function", "preprocessor", "link", "structMember", "structMembers", 
      "structDef", "statement", "expression"
    },
    std::vector<std::string>{
      "", "'const'", "'ref'", "','", "'('", "')'", "'{'", "'}'", "'#include'", 
      "'link'", "'as'", "';'", "'public'", "'packed'", "'struct'", "'return'", 
      "'if'", "'while'", "'delete'", "'.'", "'=='", "'!='", "'<'", "'>'", 
      "'<='", "'>='", "'='", "", "", "", "", "", "", "", "", "", "'*'", 
      "'/'", "'+'", "'-'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "NEWLINE", "COMMENT", "BLOCK_COMMENT", 
      "SPACE", "BOOL", "INT", "FLOAT", "STRING", "ID", "MUL", "DIV", "ADD", 
      "SUB"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,39,215,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,1,0,4,0,
  	30,8,0,11,0,12,0,31,1,0,1,0,1,0,3,0,37,8,0,1,1,1,1,1,1,1,1,1,1,1,1,3,
  	1,45,8,1,1,2,3,2,48,8,2,1,2,3,2,51,8,2,1,2,1,2,1,3,1,3,1,3,1,4,1,4,1,
  	4,5,4,61,8,4,10,4,12,4,64,9,4,3,4,66,8,4,1,5,1,5,1,5,5,5,71,8,5,10,5,
  	12,5,74,9,5,3,5,76,8,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,5,6,85,8,6,10,6,12,
  	6,88,9,6,1,6,1,6,1,7,1,7,5,7,94,8,7,10,7,12,7,97,9,7,1,7,1,7,1,8,1,8,
  	1,8,1,8,3,8,105,8,8,1,8,1,8,1,9,1,9,1,9,1,9,3,9,113,8,9,1,10,5,10,116,
  	8,10,10,10,12,10,119,9,10,1,11,3,11,122,8,11,1,11,3,11,125,8,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,5,12,138,8,12,10,12,
  	12,12,141,9,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,3,12,162,8,12,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,3,13,186,8,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,5,13,210,8,13,10,13,12,13,213,9,13,1,13,1,95,1,26,14,0,2,4,
  	6,8,10,12,14,16,18,20,22,24,26,0,3,1,0,36,37,1,0,38,39,1,0,20,25,239,
  	0,36,1,0,0,0,2,44,1,0,0,0,4,47,1,0,0,0,6,54,1,0,0,0,8,65,1,0,0,0,10,75,
  	1,0,0,0,12,77,1,0,0,0,14,91,1,0,0,0,16,100,1,0,0,0,18,112,1,0,0,0,20,
  	117,1,0,0,0,22,121,1,0,0,0,24,161,1,0,0,0,26,185,1,0,0,0,28,30,3,2,1,
  	0,29,28,1,0,0,0,30,31,1,0,0,0,31,29,1,0,0,0,31,32,1,0,0,0,32,33,1,0,0,
  	0,33,34,5,0,0,1,34,37,1,0,0,0,35,37,5,0,0,1,36,29,1,0,0,0,36,35,1,0,0,
  	0,37,1,1,0,0,0,38,45,3,12,6,0,39,40,3,14,7,0,40,41,5,27,0,0,41,45,1,0,
  	0,0,42,45,3,16,8,0,43,45,3,22,11,0,44,38,1,0,0,0,44,39,1,0,0,0,44,42,
  	1,0,0,0,44,43,1,0,0,0,45,3,1,0,0,0,46,48,5,1,0,0,47,46,1,0,0,0,47,48,
  	1,0,0,0,48,50,1,0,0,0,49,51,5,2,0,0,50,49,1,0,0,0,50,51,1,0,0,0,51,52,
  	1,0,0,0,52,53,5,35,0,0,53,5,1,0,0,0,54,55,3,4,2,0,55,56,5,35,0,0,56,7,
  	1,0,0,0,57,62,3,6,3,0,58,59,5,3,0,0,59,61,3,6,3,0,60,58,1,0,0,0,61,64,
  	1,0,0,0,62,60,1,0,0,0,62,63,1,0,0,0,63,66,1,0,0,0,64,62,1,0,0,0,65,57,
  	1,0,0,0,65,66,1,0,0,0,66,9,1,0,0,0,67,72,3,26,13,0,68,69,5,3,0,0,69,71,
  	3,26,13,0,70,68,1,0,0,0,71,74,1,0,0,0,72,70,1,0,0,0,72,73,1,0,0,0,73,
  	76,1,0,0,0,74,72,1,0,0,0,75,67,1,0,0,0,75,76,1,0,0,0,76,11,1,0,0,0,77,
  	78,3,4,2,0,78,79,5,35,0,0,79,80,5,4,0,0,80,81,3,8,4,0,81,82,5,5,0,0,82,
  	86,5,6,0,0,83,85,3,24,12,0,84,83,1,0,0,0,85,88,1,0,0,0,86,84,1,0,0,0,
  	86,87,1,0,0,0,87,89,1,0,0,0,88,86,1,0,0,0,89,90,5,7,0,0,90,13,1,0,0,0,
  	91,95,5,8,0,0,92,94,9,0,0,0,93,92,1,0,0,0,94,97,1,0,0,0,95,96,1,0,0,0,
  	95,93,1,0,0,0,96,98,1,0,0,0,97,95,1,0,0,0,98,99,5,27,0,0,99,15,1,0,0,
  	0,100,101,5,9,0,0,101,104,5,34,0,0,102,103,5,10,0,0,103,105,5,34,0,0,
  	104,102,1,0,0,0,104,105,1,0,0,0,105,106,1,0,0,0,106,107,5,11,0,0,107,
  	17,1,0,0,0,108,109,3,6,3,0,109,110,5,11,0,0,110,113,1,0,0,0,111,113,3,
  	12,6,0,112,108,1,0,0,0,112,111,1,0,0,0,113,19,1,0,0,0,114,116,3,18,9,
  	0,115,114,1,0,0,0,116,119,1,0,0,0,117,115,1,0,0,0,117,118,1,0,0,0,118,
  	21,1,0,0,0,119,117,1,0,0,0,120,122,5,12,0,0,121,120,1,0,0,0,121,122,1,
  	0,0,0,122,124,1,0,0,0,123,125,5,13,0,0,124,123,1,0,0,0,124,125,1,0,0,
  	0,125,126,1,0,0,0,126,127,5,14,0,0,127,128,5,35,0,0,128,129,5,6,0,0,129,
  	130,3,20,10,0,130,131,5,7,0,0,131,23,1,0,0,0,132,133,3,26,13,0,133,134,
  	5,11,0,0,134,162,1,0,0,0,135,139,5,6,0,0,136,138,3,24,12,0,137,136,1,
  	0,0,0,138,141,1,0,0,0,139,137,1,0,0,0,139,140,1,0,0,0,140,142,1,0,0,0,
  	141,139,1,0,0,0,142,162,5,7,0,0,143,144,5,15,0,0,144,145,3,26,13,0,145,
  	146,5,11,0,0,146,162,1,0,0,0,147,148,5,15,0,0,148,162,5,11,0,0,149,150,
  	5,16,0,0,150,151,5,4,0,0,151,152,3,26,13,0,152,153,5,5,0,0,153,154,3,
  	24,12,0,154,162,1,0,0,0,155,156,5,17,0,0,156,157,5,4,0,0,157,158,3,26,
  	13,0,158,159,5,5,0,0,159,160,3,24,12,0,160,162,1,0,0,0,161,132,1,0,0,
  	0,161,135,1,0,0,0,161,143,1,0,0,0,161,147,1,0,0,0,161,149,1,0,0,0,161,
  	155,1,0,0,0,162,25,1,0,0,0,163,164,6,13,-1,0,164,186,5,32,0,0,165,186,
  	5,33,0,0,166,186,5,34,0,0,167,186,5,31,0,0,168,186,3,6,3,0,169,170,5,
  	18,0,0,170,186,3,26,13,11,171,172,5,35,0,0,172,173,5,4,0,0,173,174,3,
  	10,5,0,174,175,5,5,0,0,175,186,1,0,0,0,176,186,5,35,0,0,177,178,5,4,0,
  	0,178,179,5,35,0,0,179,180,5,5,0,0,180,186,3,26,13,6,181,182,5,4,0,0,
  	182,183,3,26,13,0,183,184,5,5,0,0,184,186,1,0,0,0,185,163,1,0,0,0,185,
  	165,1,0,0,0,185,166,1,0,0,0,185,167,1,0,0,0,185,168,1,0,0,0,185,169,1,
  	0,0,0,185,171,1,0,0,0,185,176,1,0,0,0,185,177,1,0,0,0,185,181,1,0,0,0,
  	186,211,1,0,0,0,187,188,10,5,0,0,188,189,7,0,0,0,189,210,3,26,13,6,190,
  	191,10,4,0,0,191,192,7,1,0,0,192,210,3,26,13,5,193,194,10,3,0,0,194,195,
  	7,2,0,0,195,210,3,26,13,4,196,197,10,1,0,0,197,198,5,26,0,0,198,210,3,
  	26,13,2,199,200,10,9,0,0,200,201,5,19,0,0,201,202,5,35,0,0,202,203,5,
  	4,0,0,203,204,3,10,5,0,204,205,5,5,0,0,205,210,1,0,0,0,206,207,10,7,0,
  	0,207,208,5,19,0,0,208,210,5,35,0,0,209,187,1,0,0,0,209,190,1,0,0,0,209,
  	193,1,0,0,0,209,196,1,0,0,0,209,199,1,0,0,0,209,206,1,0,0,0,210,213,1,
  	0,0,0,211,209,1,0,0,0,211,212,1,0,0,0,212,27,1,0,0,0,213,211,1,0,0,0,
  	21,31,36,44,47,50,62,65,72,75,86,95,104,112,117,121,124,139,161,185,209,
  	211
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  braneParserStaticData = staticData.release();
}

}

braneParser::braneParser(TokenStream *input) : braneParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

braneParser::braneParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  braneParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *braneParserStaticData->atn, braneParserStaticData->decisionToDFA, braneParserStaticData->sharedContextCache, options);
}

braneParser::~braneParser() {
  delete _interpreter;
}

const atn::ATN& braneParser::getATN() const {
  return *braneParserStaticData->atn;
}

std::string braneParser::getGrammarFileName() const {
  return "brane.g4";
}

const std::vector<std::string>& braneParser::getRuleNames() const {
  return braneParserStaticData->ruleNames;
}

const dfa::Vocabulary& braneParser::getVocabulary() const {
  return braneParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView braneParser::getSerializedATN() const {
  return braneParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

braneParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* braneParser::ProgramContext::EOF() {
  return getToken(braneParser::EOF, 0);
}

std::vector<braneParser::ProgSegmentContext *> braneParser::ProgramContext::progSegment() {
  return getRuleContexts<braneParser::ProgSegmentContext>();
}

braneParser::ProgSegmentContext* braneParser::ProgramContext::progSegment(size_t i) {
  return getRuleContext<braneParser::ProgSegmentContext>(i);
}


size_t braneParser::ProgramContext::getRuleIndex() const {
  return braneParser::RuleProgram;
}


std::any braneParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ProgramContext* braneParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, braneParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(36);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__0:
      case braneParser::T__1:
      case braneParser::T__7:
      case braneParser::T__8:
      case braneParser::T__11:
      case braneParser::T__12:
      case braneParser::T__13:
      case braneParser::ID: {
        setState(29); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(28);
          progSegment();
          setState(31); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << braneParser::T__0)
          | (1ULL << braneParser::T__1)
          | (1ULL << braneParser::T__7)
          | (1ULL << braneParser::T__8)
          | (1ULL << braneParser::T__11)
          | (1ULL << braneParser::T__12)
          | (1ULL << braneParser::T__13)
          | (1ULL << braneParser::ID))) != 0));
        setState(33);
        match(braneParser::EOF);
        break;
      }

      case braneParser::EOF: {
        setState(35);
        match(braneParser::EOF);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgSegmentContext ------------------------------------------------------------------

braneParser::ProgSegmentContext::ProgSegmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::FunctionContext* braneParser::ProgSegmentContext::function() {
  return getRuleContext<braneParser::FunctionContext>(0);
}

braneParser::PreprocessorContext* braneParser::ProgSegmentContext::preprocessor() {
  return getRuleContext<braneParser::PreprocessorContext>(0);
}

tree::TerminalNode* braneParser::ProgSegmentContext::NEWLINE() {
  return getToken(braneParser::NEWLINE, 0);
}

braneParser::LinkContext* braneParser::ProgSegmentContext::link() {
  return getRuleContext<braneParser::LinkContext>(0);
}

braneParser::StructDefContext* braneParser::ProgSegmentContext::structDef() {
  return getRuleContext<braneParser::StructDefContext>(0);
}


size_t braneParser::ProgSegmentContext::getRuleIndex() const {
  return braneParser::RuleProgSegment;
}


std::any braneParser::ProgSegmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitProgSegment(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ProgSegmentContext* braneParser::progSegment() {
  ProgSegmentContext *_localctx = _tracker.createInstance<ProgSegmentContext>(_ctx, getState());
  enterRule(_localctx, 2, braneParser::RuleProgSegment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(44);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__0:
      case braneParser::T__1:
      case braneParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(38);
        function();
        break;
      }

      case braneParser::T__7: {
        enterOuterAlt(_localctx, 2);
        setState(39);
        preprocessor();
        setState(40);
        match(braneParser::NEWLINE);
        break;
      }

      case braneParser::T__8: {
        enterOuterAlt(_localctx, 3);
        setState(42);
        link();
        break;
      }

      case braneParser::T__11:
      case braneParser::T__12:
      case braneParser::T__13: {
        enterOuterAlt(_localctx, 4);
        setState(43);
        structDef();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

braneParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* braneParser::TypeContext::ID() {
  return getToken(braneParser::ID, 0);
}


size_t braneParser::TypeContext::getRuleIndex() const {
  return braneParser::RuleType;
}


std::any braneParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

braneParser::TypeContext* braneParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 4, braneParser::RuleType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(47);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__0) {
      setState(46);
      antlrcpp::downCast<TypeContext *>(_localctx)->isConst = match(braneParser::T__0);
    }
    setState(50);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__1) {
      setState(49);
      antlrcpp::downCast<TypeContext *>(_localctx)->isRef = match(braneParser::T__1);
    }
    setState(52);
    antlrcpp::downCast<TypeContext *>(_localctx)->id = match(braneParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

braneParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::TypeContext* braneParser::DeclarationContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}

tree::TerminalNode* braneParser::DeclarationContext::ID() {
  return getToken(braneParser::ID, 0);
}


size_t braneParser::DeclarationContext::getRuleIndex() const {
  return braneParser::RuleDeclaration;
}


std::any braneParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

braneParser::DeclarationContext* braneParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 6, braneParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(54);
    type();
    setState(55);
    antlrcpp::downCast<DeclarationContext *>(_localctx)->id = match(braneParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListContext ------------------------------------------------------------------

braneParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::DeclarationContext *> braneParser::ArgumentListContext::declaration() {
  return getRuleContexts<braneParser::DeclarationContext>();
}

braneParser::DeclarationContext* braneParser::ArgumentListContext::declaration(size_t i) {
  return getRuleContext<braneParser::DeclarationContext>(i);
}


size_t braneParser::ArgumentListContext::getRuleIndex() const {
  return braneParser::RuleArgumentList;
}


std::any braneParser::ArgumentListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitArgumentList(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ArgumentListContext* braneParser::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 8, braneParser::RuleArgumentList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << braneParser::T__0)
      | (1ULL << braneParser::T__1)
      | (1ULL << braneParser::ID))) != 0)) {
      setState(57);
      declaration();
      setState(62);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__2) {
        setState(58);
        match(braneParser::T__2);
        setState(59);
        declaration();
        setState(64);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentPackContext ------------------------------------------------------------------

braneParser::ArgumentPackContext::ArgumentPackContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::ExpressionContext *> braneParser::ArgumentPackContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::ArgumentPackContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}


size_t braneParser::ArgumentPackContext::getRuleIndex() const {
  return braneParser::RuleArgumentPack;
}


std::any braneParser::ArgumentPackContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitArgumentPack(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ArgumentPackContext* braneParser::argumentPack() {
  ArgumentPackContext *_localctx = _tracker.createInstance<ArgumentPackContext>(_ctx, getState());
  enterRule(_localctx, 10, braneParser::RuleArgumentPack);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(75);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << braneParser::T__0)
      | (1ULL << braneParser::T__1)
      | (1ULL << braneParser::T__3)
      | (1ULL << braneParser::T__17)
      | (1ULL << braneParser::BOOL)
      | (1ULL << braneParser::INT)
      | (1ULL << braneParser::FLOAT)
      | (1ULL << braneParser::STRING)
      | (1ULL << braneParser::ID))) != 0)) {
      setState(67);
      expression(0);
      setState(72);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__2) {
        setState(68);
        match(braneParser::T__2);
        setState(69);
        expression(0);
        setState(74);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

braneParser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::TypeContext* braneParser::FunctionContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}

tree::TerminalNode* braneParser::FunctionContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::ArgumentListContext* braneParser::FunctionContext::argumentList() {
  return getRuleContext<braneParser::ArgumentListContext>(0);
}

std::vector<braneParser::StatementContext *> braneParser::FunctionContext::statement() {
  return getRuleContexts<braneParser::StatementContext>();
}

braneParser::StatementContext* braneParser::FunctionContext::statement(size_t i) {
  return getRuleContext<braneParser::StatementContext>(i);
}


size_t braneParser::FunctionContext::getRuleIndex() const {
  return braneParser::RuleFunction;
}


std::any braneParser::FunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitFunction(this);
  else
    return visitor->visitChildren(this);
}

braneParser::FunctionContext* braneParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 12, braneParser::RuleFunction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    type();
    setState(78);
    antlrcpp::downCast<FunctionContext *>(_localctx)->id = match(braneParser::ID);
    setState(79);
    match(braneParser::T__3);
    setState(80);
    antlrcpp::downCast<FunctionContext *>(_localctx)->arguments = argumentList();
    setState(81);
    match(braneParser::T__4);
    setState(82);
    match(braneParser::T__5);
    setState(86);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << braneParser::T__0)
      | (1ULL << braneParser::T__1)
      | (1ULL << braneParser::T__3)
      | (1ULL << braneParser::T__5)
      | (1ULL << braneParser::T__14)
      | (1ULL << braneParser::T__15)
      | (1ULL << braneParser::T__16)
      | (1ULL << braneParser::T__17)
      | (1ULL << braneParser::BOOL)
      | (1ULL << braneParser::INT)
      | (1ULL << braneParser::FLOAT)
      | (1ULL << braneParser::STRING)
      | (1ULL << braneParser::ID))) != 0)) {
      setState(83);
      antlrcpp::downCast<FunctionContext *>(_localctx)->statements = statement();
      setState(88);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(89);
    match(braneParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PreprocessorContext ------------------------------------------------------------------

braneParser::PreprocessorContext::PreprocessorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t braneParser::PreprocessorContext::getRuleIndex() const {
  return braneParser::RulePreprocessor;
}

void braneParser::PreprocessorContext::copyFrom(PreprocessorContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IncludeContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::IncludeContext::NEWLINE() {
  return getToken(braneParser::NEWLINE, 0);
}

braneParser::IncludeContext::IncludeContext(PreprocessorContext *ctx) { copyFrom(ctx); }


std::any braneParser::IncludeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitInclude(this);
  else
    return visitor->visitChildren(this);
}
braneParser::PreprocessorContext* braneParser::preprocessor() {
  PreprocessorContext *_localctx = _tracker.createInstance<PreprocessorContext>(_ctx, getState());
  enterRule(_localctx, 14, braneParser::RulePreprocessor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    _localctx = _tracker.createInstance<braneParser::IncludeContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(91);
    match(braneParser::T__7);
    setState(95);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(92);
        antlrcpp::downCast<IncludeContext *>(_localctx)->content = matchWildcard(); 
      }
      setState(97);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    }
    setState(98);
    match(braneParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LinkContext ------------------------------------------------------------------

braneParser::LinkContext::LinkContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> braneParser::LinkContext::STRING() {
  return getTokens(braneParser::STRING);
}

tree::TerminalNode* braneParser::LinkContext::STRING(size_t i) {
  return getToken(braneParser::STRING, i);
}


size_t braneParser::LinkContext::getRuleIndex() const {
  return braneParser::RuleLink;
}


std::any braneParser::LinkContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitLink(this);
  else
    return visitor->visitChildren(this);
}

braneParser::LinkContext* braneParser::link() {
  LinkContext *_localctx = _tracker.createInstance<LinkContext>(_ctx, getState());
  enterRule(_localctx, 16, braneParser::RuleLink);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(100);
    match(braneParser::T__8);
    setState(101);
    antlrcpp::downCast<LinkContext *>(_localctx)->library = match(braneParser::STRING);
    setState(104);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__9) {
      setState(102);
      match(braneParser::T__9);
      setState(103);
      antlrcpp::downCast<LinkContext *>(_localctx)->alias = match(braneParser::STRING);
    }
    setState(106);
    match(braneParser::T__10);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructMemberContext ------------------------------------------------------------------

braneParser::StructMemberContext::StructMemberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::DeclarationContext* braneParser::StructMemberContext::declaration() {
  return getRuleContext<braneParser::DeclarationContext>(0);
}

braneParser::FunctionContext* braneParser::StructMemberContext::function() {
  return getRuleContext<braneParser::FunctionContext>(0);
}


size_t braneParser::StructMemberContext::getRuleIndex() const {
  return braneParser::RuleStructMember;
}


std::any braneParser::StructMemberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitStructMember(this);
  else
    return visitor->visitChildren(this);
}

braneParser::StructMemberContext* braneParser::structMember() {
  StructMemberContext *_localctx = _tracker.createInstance<StructMemberContext>(_ctx, getState());
  enterRule(_localctx, 18, braneParser::RuleStructMember);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(112);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(108);
      antlrcpp::downCast<StructMemberContext *>(_localctx)->var = declaration();
      setState(109);
      match(braneParser::T__10);
      break;
    }

    case 2: {
      setState(111);
      antlrcpp::downCast<StructMemberContext *>(_localctx)->func = function();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructMembersContext ------------------------------------------------------------------

braneParser::StructMembersContext::StructMembersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::StructMemberContext *> braneParser::StructMembersContext::structMember() {
  return getRuleContexts<braneParser::StructMemberContext>();
}

braneParser::StructMemberContext* braneParser::StructMembersContext::structMember(size_t i) {
  return getRuleContext<braneParser::StructMemberContext>(i);
}


size_t braneParser::StructMembersContext::getRuleIndex() const {
  return braneParser::RuleStructMembers;
}


std::any braneParser::StructMembersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitStructMembers(this);
  else
    return visitor->visitChildren(this);
}

braneParser::StructMembersContext* braneParser::structMembers() {
  StructMembersContext *_localctx = _tracker.createInstance<StructMembersContext>(_ctx, getState());
  enterRule(_localctx, 20, braneParser::RuleStructMembers);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << braneParser::T__0)
      | (1ULL << braneParser::T__1)
      | (1ULL << braneParser::ID))) != 0)) {
      setState(114);
      structMember();
      setState(119);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDefContext ------------------------------------------------------------------

braneParser::StructDefContext::StructDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* braneParser::StructDefContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::StructMembersContext* braneParser::StructDefContext::structMembers() {
  return getRuleContext<braneParser::StructMembersContext>(0);
}


size_t braneParser::StructDefContext::getRuleIndex() const {
  return braneParser::RuleStructDef;
}


std::any braneParser::StructDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitStructDef(this);
  else
    return visitor->visitChildren(this);
}

braneParser::StructDefContext* braneParser::structDef() {
  StructDefContext *_localctx = _tracker.createInstance<StructDefContext>(_ctx, getState());
  enterRule(_localctx, 22, braneParser::RuleStructDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__11) {
      setState(120);
      antlrcpp::downCast<StructDefContext *>(_localctx)->isPublic = match(braneParser::T__11);
    }
    setState(124);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__12) {
      setState(123);
      antlrcpp::downCast<StructDefContext *>(_localctx)->packed = match(braneParser::T__12);
    }
    setState(126);
    match(braneParser::T__13);
    setState(127);
    antlrcpp::downCast<StructDefContext *>(_localctx)->id = match(braneParser::ID);
    setState(128);
    match(braneParser::T__5);
    setState(129);
    antlrcpp::downCast<StructDefContext *>(_localctx)->memberVars = structMembers();
    setState(130);
    match(braneParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

braneParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t braneParser::StatementContext::getRuleIndex() const {
  return braneParser::RuleStatement;
}

void braneParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ReturnVoidContext ------------------------------------------------------------------

braneParser::ReturnVoidContext::ReturnVoidContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::ReturnVoidContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitReturnVoid(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnValContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::ReturnValContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::ReturnValContext::ReturnValContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::ReturnValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitReturnVal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ScopeContext ------------------------------------------------------------------

std::vector<braneParser::StatementContext *> braneParser::ScopeContext::statement() {
  return getRuleContexts<braneParser::StatementContext>();
}

braneParser::StatementContext* braneParser::ScopeContext::statement(size_t i) {
  return getRuleContext<braneParser::StatementContext>(i);
}

braneParser::ScopeContext::ScopeContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::ScopeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitScope(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprStatementContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::ExprStatementContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::ExprStatementContext::ExprStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::ExprStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitExprStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::WhileContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::StatementContext* braneParser::WhileContext::statement() {
  return getRuleContext<braneParser::StatementContext>(0);
}

braneParser::WhileContext::WhileContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::WhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitWhile(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::IfContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::StatementContext* braneParser::IfContext::statement() {
  return getRuleContext<braneParser::StatementContext>(0);
}

braneParser::IfContext::IfContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::IfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitIf(this);
  else
    return visitor->visitChildren(this);
}
braneParser::StatementContext* braneParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 24, braneParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(161);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::ExprStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(132);
      expression(0);
      setState(133);
      match(braneParser::T__10);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::ScopeContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(135);
      match(braneParser::T__5);
      setState(139);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << braneParser::T__0)
        | (1ULL << braneParser::T__1)
        | (1ULL << braneParser::T__3)
        | (1ULL << braneParser::T__5)
        | (1ULL << braneParser::T__14)
        | (1ULL << braneParser::T__15)
        | (1ULL << braneParser::T__16)
        | (1ULL << braneParser::T__17)
        | (1ULL << braneParser::BOOL)
        | (1ULL << braneParser::INT)
        | (1ULL << braneParser::FLOAT)
        | (1ULL << braneParser::STRING)
        | (1ULL << braneParser::ID))) != 0)) {
        setState(136);
        statement();
        setState(141);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(142);
      match(braneParser::T__6);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::ReturnValContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(143);
      match(braneParser::T__14);
      setState(144);
      expression(0);
      setState(145);
      match(braneParser::T__10);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<braneParser::ReturnVoidContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(147);
      match(braneParser::T__14);
      setState(148);
      match(braneParser::T__10);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<braneParser::IfContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(149);
      match(braneParser::T__15);
      setState(150);
      match(braneParser::T__3);
      setState(151);
      antlrcpp::downCast<IfContext *>(_localctx)->cond = expression(0);
      setState(152);
      match(braneParser::T__4);
      setState(153);
      antlrcpp::downCast<IfContext *>(_localctx)->operation = statement();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<braneParser::WhileContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(155);
      match(braneParser::T__16);
      setState(156);
      match(braneParser::T__3);
      setState(157);
      antlrcpp::downCast<WhileContext *>(_localctx)->cond = expression(0);
      setState(158);
      match(braneParser::T__4);
      setState(159);
      antlrcpp::downCast<WhileContext *>(_localctx)->operation = statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

braneParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t braneParser::ExpressionContext::getRuleIndex() const {
  return braneParser::RuleExpression;
}

void braneParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MemberAccessContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::MemberAccessContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

tree::TerminalNode* braneParser::MemberAccessContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::MemberAccessContext::MemberAccessContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::MemberAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitMemberAccess(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ComparisonContext ------------------------------------------------------------------

std::vector<braneParser::ExpressionContext *> braneParser::ComparisonContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::ComparisonContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}

braneParser::ComparisonContext::ComparisonContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::ComparisonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitComparison(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DeclContext ------------------------------------------------------------------

braneParser::DeclarationContext* braneParser::DeclContext::declaration() {
  return getRuleContext<braneParser::DeclarationContext>(0);
}

braneParser::DeclContext::DeclContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InlineScopeContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::InlineScopeContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::InlineScopeContext::InlineScopeContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::InlineScopeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitInlineScope(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignmentContext ------------------------------------------------------------------

std::vector<braneParser::ExpressionContext *> braneParser::AssignmentContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::AssignmentContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}

braneParser::AssignmentContext::AssignmentContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddsubContext ------------------------------------------------------------------

std::vector<braneParser::ExpressionContext *> braneParser::AddsubContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::AddsubContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}

tree::TerminalNode* braneParser::AddsubContext::ADD() {
  return getToken(braneParser::ADD, 0);
}

tree::TerminalNode* braneParser::AddsubContext::SUB() {
  return getToken(braneParser::SUB, 0);
}

braneParser::AddsubContext::AddsubContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::AddsubContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitAddsub(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstIntContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::ConstIntContext::INT() {
  return getToken(braneParser::INT, 0);
}

braneParser::ConstIntContext::ConstIntContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::ConstIntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitConstInt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstBoolContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::ConstBoolContext::BOOL() {
  return getToken(braneParser::BOOL, 0);
}

braneParser::ConstBoolContext::ConstBoolContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::ConstBoolContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitConstBool(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DeleteContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::DeleteContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::DeleteContext::DeleteContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::DeleteContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitDelete(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MuldivContext ------------------------------------------------------------------

std::vector<braneParser::ExpressionContext *> braneParser::MuldivContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::MuldivContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}

tree::TerminalNode* braneParser::MuldivContext::MUL() {
  return getToken(braneParser::MUL, 0);
}

tree::TerminalNode* braneParser::MuldivContext::DIV() {
  return getToken(braneParser::DIV, 0);
}

braneParser::MuldivContext::MuldivContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::MuldivContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitMuldiv(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstStringContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::ConstStringContext::STRING() {
  return getToken(braneParser::STRING, 0);
}

braneParser::ConstStringContext::ConstStringContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::ConstStringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitConstString(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CastContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::CastContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::ExpressionContext* braneParser::CastContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::CastContext::CastContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::CastContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitCast(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemberFunctionCallContext ------------------------------------------------------------------

braneParser::ArgumentPackContext* braneParser::MemberFunctionCallContext::argumentPack() {
  return getRuleContext<braneParser::ArgumentPackContext>(0);
}

braneParser::ExpressionContext* braneParser::MemberFunctionCallContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

tree::TerminalNode* braneParser::MemberFunctionCallContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::MemberFunctionCallContext::MemberFunctionCallContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::MemberFunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitMemberFunctionCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionCallContext ------------------------------------------------------------------

braneParser::ArgumentPackContext* braneParser::FunctionCallContext::argumentPack() {
  return getRuleContext<braneParser::ArgumentPackContext>(0);
}

tree::TerminalNode* braneParser::FunctionCallContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::FunctionCallContext::FunctionCallContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstFloatContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::ConstFloatContext::FLOAT() {
  return getToken(braneParser::FLOAT, 0);
}

braneParser::ConstFloatContext::ConstFloatContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::ConstFloatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitConstFloat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::IdContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::IdContext::IdContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::IdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitId(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ExpressionContext* braneParser::expression() {
   return expression(0);
}

braneParser::ExpressionContext* braneParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  braneParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  braneParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 26;
  enterRecursionRule(_localctx, 26, braneParser::RuleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(185);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ConstIntContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(164);
      match(braneParser::INT);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ConstFloatContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(165);
      match(braneParser::FLOAT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ConstStringContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(166);
      match(braneParser::STRING);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ConstBoolContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(167);
      match(braneParser::BOOL);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<DeclContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(168);
      declaration();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<DeleteContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(169);
      match(braneParser::T__17);
      setState(170);
      antlrcpp::downCast<DeleteContext *>(_localctx)->ptr = expression(11);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<FunctionCallContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(171);
      antlrcpp::downCast<FunctionCallContext *>(_localctx)->name = match(braneParser::ID);
      setState(172);
      match(braneParser::T__3);
      setState(173);
      argumentPack();
      setState(174);
      match(braneParser::T__4);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<IdContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(176);
      match(braneParser::ID);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<CastContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(177);
      match(braneParser::T__3);
      setState(178);
      match(braneParser::ID);
      setState(179);
      match(braneParser::T__4);
      setState(180);
      expression(6);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<InlineScopeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(181);
      match(braneParser::T__3);
      setState(182);
      expression(0);
      setState(183);
      match(braneParser::T__4);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(211);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(209);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MuldivContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(187);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(188);
          antlrcpp::downCast<MuldivContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == braneParser::MUL

          || _la == braneParser::DIV)) {
            antlrcpp::downCast<MuldivContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(189);
          antlrcpp::downCast<MuldivContext *>(_localctx)->right = expression(6);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddsubContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(190);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(191);
          antlrcpp::downCast<AddsubContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == braneParser::ADD

          || _la == braneParser::SUB)) {
            antlrcpp::downCast<AddsubContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(192);
          antlrcpp::downCast<AddsubContext *>(_localctx)->right = expression(5);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ComparisonContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(193);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(194);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << braneParser::T__19)
            | (1ULL << braneParser::T__20)
            | (1ULL << braneParser::T__21)
            | (1ULL << braneParser::T__22)
            | (1ULL << braneParser::T__23)
            | (1ULL << braneParser::T__24))) != 0))) {
            antlrcpp::downCast<ComparisonContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(195);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->right = expression(4);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<AssignmentContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->dest = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(196);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(197);
          match(braneParser::T__25);
          setState(198);
          antlrcpp::downCast<AssignmentContext *>(_localctx)->expr = expression(2);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<MemberFunctionCallContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(199);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(200);
          match(braneParser::T__18);
          setState(201);
          antlrcpp::downCast<MemberFunctionCallContext *>(_localctx)->name = match(braneParser::ID);
          setState(202);
          match(braneParser::T__3);
          setState(203);
          argumentPack();
          setState(204);
          match(braneParser::T__4);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(206);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(207);
          match(braneParser::T__18);
          setState(208);
          antlrcpp::downCast<MemberAccessContext *>(_localctx)->member = match(braneParser::ID);
          break;
        }

        default:
          break;
        } 
      }
      setState(213);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool braneParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 13: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool braneParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 5);
    case 1: return precpred(_ctx, 4);
    case 2: return precpred(_ctx, 3);
    case 3: return precpred(_ctx, 1);
    case 4: return precpred(_ctx, 9);
    case 5: return precpred(_ctx, 7);

  default:
    break;
  }
  return true;
}

void braneParser::initialize() {
  std::call_once(braneParserOnceFlag, braneParserInitialize);
}

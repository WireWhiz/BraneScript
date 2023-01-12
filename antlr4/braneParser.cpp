
// Generated from /home/wirewhiz/CLionProjects/BraneEngine/libraries/internal/BraneScript/antlr4/brane.g4 by ANTLR 4.11.1


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

::antlr4::internal::OnceFlag braneParserOnceFlag;
BraneParserStaticData *braneParserStaticData = nullptr;

void braneParserInitialize() {
  assert(braneParserStaticData == nullptr);
  auto staticData = std::make_unique<BraneParserStaticData>(
    std::vector<std::string>{
      "program", "progSegment", "global", "type", "declaration", "argumentList", 
      "argumentPack", "function", "preprocessor", "link", "structMember", 
      "structMembers", "structDef", "statement", "expression"
    },
    std::vector<std::string>{
      "", "';'", "'const'", "'ref'", "','", "'('", "')'", "'{'", "'}'", 
      "'#include'", "'link'", "'as'", "'public'", "'packed'", "'struct'", 
      "'return'", "'if'", "'while'", "'delete'", "'.'", "'['", "']'", "'=='", 
      "'!='", "'<'", "'>'", "'<='", "'>='", "'='", "", "", "", "", "", "", 
      "", "", "", "", "'*'", "'/'", "'+'", "'-'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "NEWLINE", "COMMENT", 
      "BLOCK_COMMENT", "SPACE", "BOOL", "INT", "FLOAT", "CHAR", "STRING", 
      "ID", "MUL", "DIV", "ADD", "SUB"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,42,227,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,1,0,4,0,32,8,0,11,0,12,0,33,1,0,1,0,1,0,3,0,39,8,0,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,3,1,48,8,1,1,2,1,2,1,2,1,3,3,3,54,8,3,1,3,3,3,57,8,3,1,3,
  	1,3,1,4,1,4,1,4,1,5,1,5,1,5,5,5,67,8,5,10,5,12,5,70,9,5,3,5,72,8,5,1,
  	6,1,6,1,6,5,6,77,8,6,10,6,12,6,80,9,6,3,6,82,8,6,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,5,7,91,8,7,10,7,12,7,94,9,7,1,7,1,7,1,8,1,8,5,8,100,8,8,10,8,
  	12,8,103,9,8,1,8,1,8,1,9,1,9,1,9,1,9,3,9,111,8,9,1,9,1,9,1,10,1,10,1,
  	10,1,10,3,10,119,8,10,1,11,5,11,122,8,11,10,11,12,11,125,9,11,1,12,3,
  	12,128,8,12,1,12,3,12,131,8,12,1,12,1,12,1,12,1,12,1,12,1,12,1,13,1,13,
  	1,13,1,13,1,13,5,13,144,8,13,10,13,12,13,147,9,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,3,13,168,8,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,3,14,
  	193,8,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,5,14,222,8,14,10,14,12,14,225,9,14,1,14,1,101,1,28,15,0,2,4,6,8,
  	10,12,14,16,18,20,22,24,26,28,0,3,1,0,39,40,1,0,41,42,1,0,22,27,253,0,
  	38,1,0,0,0,2,47,1,0,0,0,4,49,1,0,0,0,6,53,1,0,0,0,8,60,1,0,0,0,10,71,
  	1,0,0,0,12,81,1,0,0,0,14,83,1,0,0,0,16,97,1,0,0,0,18,106,1,0,0,0,20,118,
  	1,0,0,0,22,123,1,0,0,0,24,127,1,0,0,0,26,167,1,0,0,0,28,192,1,0,0,0,30,
  	32,3,2,1,0,31,30,1,0,0,0,32,33,1,0,0,0,33,31,1,0,0,0,33,34,1,0,0,0,34,
  	35,1,0,0,0,35,36,5,0,0,1,36,39,1,0,0,0,37,39,5,0,0,1,38,31,1,0,0,0,38,
  	37,1,0,0,0,39,1,1,0,0,0,40,48,3,14,7,0,41,42,3,16,8,0,42,43,5,29,0,0,
  	43,48,1,0,0,0,44,48,3,18,9,0,45,48,3,24,12,0,46,48,3,4,2,0,47,40,1,0,
  	0,0,47,41,1,0,0,0,47,44,1,0,0,0,47,45,1,0,0,0,47,46,1,0,0,0,48,3,1,0,
  	0,0,49,50,3,8,4,0,50,51,5,1,0,0,51,5,1,0,0,0,52,54,5,2,0,0,53,52,1,0,
  	0,0,53,54,1,0,0,0,54,56,1,0,0,0,55,57,5,3,0,0,56,55,1,0,0,0,56,57,1,0,
  	0,0,57,58,1,0,0,0,58,59,5,38,0,0,59,7,1,0,0,0,60,61,3,6,3,0,61,62,5,38,
  	0,0,62,9,1,0,0,0,63,68,3,8,4,0,64,65,5,4,0,0,65,67,3,8,4,0,66,64,1,0,
  	0,0,67,70,1,0,0,0,68,66,1,0,0,0,68,69,1,0,0,0,69,72,1,0,0,0,70,68,1,0,
  	0,0,71,63,1,0,0,0,71,72,1,0,0,0,72,11,1,0,0,0,73,78,3,28,14,0,74,75,5,
  	4,0,0,75,77,3,28,14,0,76,74,1,0,0,0,77,80,1,0,0,0,78,76,1,0,0,0,78,79,
  	1,0,0,0,79,82,1,0,0,0,80,78,1,0,0,0,81,73,1,0,0,0,81,82,1,0,0,0,82,13,
  	1,0,0,0,83,84,3,6,3,0,84,85,5,38,0,0,85,86,5,5,0,0,86,87,3,10,5,0,87,
  	88,5,6,0,0,88,92,5,7,0,0,89,91,3,26,13,0,90,89,1,0,0,0,91,94,1,0,0,0,
  	92,90,1,0,0,0,92,93,1,0,0,0,93,95,1,0,0,0,94,92,1,0,0,0,95,96,5,8,0,0,
  	96,15,1,0,0,0,97,101,5,9,0,0,98,100,9,0,0,0,99,98,1,0,0,0,100,103,1,0,
  	0,0,101,102,1,0,0,0,101,99,1,0,0,0,102,104,1,0,0,0,103,101,1,0,0,0,104,
  	105,5,29,0,0,105,17,1,0,0,0,106,107,5,10,0,0,107,110,5,37,0,0,108,109,
  	5,11,0,0,109,111,5,37,0,0,110,108,1,0,0,0,110,111,1,0,0,0,111,112,1,0,
  	0,0,112,113,5,1,0,0,113,19,1,0,0,0,114,115,3,8,4,0,115,116,5,1,0,0,116,
  	119,1,0,0,0,117,119,3,14,7,0,118,114,1,0,0,0,118,117,1,0,0,0,119,21,1,
  	0,0,0,120,122,3,20,10,0,121,120,1,0,0,0,122,125,1,0,0,0,123,121,1,0,0,
  	0,123,124,1,0,0,0,124,23,1,0,0,0,125,123,1,0,0,0,126,128,5,12,0,0,127,
  	126,1,0,0,0,127,128,1,0,0,0,128,130,1,0,0,0,129,131,5,13,0,0,130,129,
  	1,0,0,0,130,131,1,0,0,0,131,132,1,0,0,0,132,133,5,14,0,0,133,134,5,38,
  	0,0,134,135,5,7,0,0,135,136,3,22,11,0,136,137,5,8,0,0,137,25,1,0,0,0,
  	138,139,3,28,14,0,139,140,5,1,0,0,140,168,1,0,0,0,141,145,5,7,0,0,142,
  	144,3,26,13,0,143,142,1,0,0,0,144,147,1,0,0,0,145,143,1,0,0,0,145,146,
  	1,0,0,0,146,148,1,0,0,0,147,145,1,0,0,0,148,168,5,8,0,0,149,150,5,15,
  	0,0,150,151,3,28,14,0,151,152,5,1,0,0,152,168,1,0,0,0,153,154,5,15,0,
  	0,154,168,5,1,0,0,155,156,5,16,0,0,156,157,5,5,0,0,157,158,3,28,14,0,
  	158,159,5,6,0,0,159,160,3,26,13,0,160,168,1,0,0,0,161,162,5,17,0,0,162,
  	163,5,5,0,0,163,164,3,28,14,0,164,165,5,6,0,0,165,166,3,26,13,0,166,168,
  	1,0,0,0,167,138,1,0,0,0,167,141,1,0,0,0,167,149,1,0,0,0,167,153,1,0,0,
  	0,167,155,1,0,0,0,167,161,1,0,0,0,168,27,1,0,0,0,169,170,6,14,-1,0,170,
  	193,5,34,0,0,171,193,5,35,0,0,172,193,5,36,0,0,173,193,5,37,0,0,174,193,
  	5,33,0,0,175,193,3,8,4,0,176,177,5,18,0,0,177,193,3,28,14,12,178,179,
  	5,38,0,0,179,180,5,5,0,0,180,181,3,12,6,0,181,182,5,6,0,0,182,193,1,0,
  	0,0,183,193,5,38,0,0,184,185,5,5,0,0,185,186,5,38,0,0,186,187,5,6,0,0,
  	187,193,3,28,14,6,188,189,5,5,0,0,189,190,3,28,14,0,190,191,5,6,0,0,191,
  	193,1,0,0,0,192,169,1,0,0,0,192,171,1,0,0,0,192,172,1,0,0,0,192,173,1,
  	0,0,0,192,174,1,0,0,0,192,175,1,0,0,0,192,176,1,0,0,0,192,178,1,0,0,0,
  	192,183,1,0,0,0,192,184,1,0,0,0,192,188,1,0,0,0,193,223,1,0,0,0,194,195,
  	10,5,0,0,195,196,7,0,0,0,196,222,3,28,14,6,197,198,10,4,0,0,198,199,7,
  	1,0,0,199,222,3,28,14,5,200,201,10,3,0,0,201,202,7,2,0,0,202,222,3,28,
  	14,4,203,204,10,1,0,0,204,205,5,28,0,0,205,222,3,28,14,2,206,207,10,10,
  	0,0,207,208,5,19,0,0,208,209,5,38,0,0,209,210,5,5,0,0,210,211,3,12,6,
  	0,211,212,5,6,0,0,212,222,1,0,0,0,213,214,10,8,0,0,214,215,5,20,0,0,215,
  	216,3,28,14,0,216,217,5,21,0,0,217,222,1,0,0,0,218,219,10,7,0,0,219,220,
  	5,19,0,0,220,222,5,38,0,0,221,194,1,0,0,0,221,197,1,0,0,0,221,200,1,0,
  	0,0,221,203,1,0,0,0,221,206,1,0,0,0,221,213,1,0,0,0,221,218,1,0,0,0,222,
  	225,1,0,0,0,223,221,1,0,0,0,223,224,1,0,0,0,224,29,1,0,0,0,225,223,1,
  	0,0,0,21,33,38,47,53,56,68,71,78,81,92,101,110,118,123,127,130,145,167,
  	192,221,223
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
    setState(38);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__1:
      case braneParser::T__2:
      case braneParser::T__8:
      case braneParser::T__9:
      case braneParser::T__11:
      case braneParser::T__12:
      case braneParser::T__13:
      case braneParser::ID: {
        setState(31); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(30);
          progSegment();
          setState(33); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 274877937164) != 0);
        setState(35);
        match(braneParser::EOF);
        break;
      }

      case braneParser::EOF: {
        setState(37);
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

braneParser::GlobalContext* braneParser::ProgSegmentContext::global() {
  return getRuleContext<braneParser::GlobalContext>(0);
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
    setState(47);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(40);
      function();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(41);
      preprocessor();
      setState(42);
      match(braneParser::NEWLINE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(44);
      link();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(45);
      structDef();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(46);
      global();
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

//----------------- GlobalContext ------------------------------------------------------------------

braneParser::GlobalContext::GlobalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::DeclarationContext* braneParser::GlobalContext::declaration() {
  return getRuleContext<braneParser::DeclarationContext>(0);
}


size_t braneParser::GlobalContext::getRuleIndex() const {
  return braneParser::RuleGlobal;
}


std::any braneParser::GlobalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitGlobal(this);
  else
    return visitor->visitChildren(this);
}

braneParser::GlobalContext* braneParser::global() {
  GlobalContext *_localctx = _tracker.createInstance<GlobalContext>(_ctx, getState());
  enterRule(_localctx, 4, braneParser::RuleGlobal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(49);
    declaration();
    setState(50);
    match(braneParser::T__0);
   
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
  enterRule(_localctx, 6, braneParser::RuleType);
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
    setState(53);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__1) {
      setState(52);
      antlrcpp::downCast<TypeContext *>(_localctx)->isConst = match(braneParser::T__1);
    }
    setState(56);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__2) {
      setState(55);
      antlrcpp::downCast<TypeContext *>(_localctx)->isRef = match(braneParser::T__2);
    }
    setState(58);
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
  enterRule(_localctx, 8, braneParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(60);
    type();
    setState(61);
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
  enterRule(_localctx, 10, braneParser::RuleArgumentList);
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
    setState(71);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 274877906956) != 0) {
      setState(63);
      declaration();
      setState(68);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__3) {
        setState(64);
        match(braneParser::T__3);
        setState(65);
        declaration();
        setState(70);
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
  enterRule(_localctx, 12, braneParser::RuleArgumentPack);
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
    setState(81);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 541166141484) != 0) {
      setState(73);
      expression(0);
      setState(78);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__3) {
        setState(74);
        match(braneParser::T__3);
        setState(75);
        expression(0);
        setState(80);
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
  enterRule(_localctx, 14, braneParser::RuleFunction);
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
    setState(83);
    type();
    setState(84);
    antlrcpp::downCast<FunctionContext *>(_localctx)->id = match(braneParser::ID);
    setState(85);
    match(braneParser::T__4);
    setState(86);
    antlrcpp::downCast<FunctionContext *>(_localctx)->arguments = argumentList();
    setState(87);
    match(braneParser::T__5);
    setState(88);
    match(braneParser::T__6);
    setState(92);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 541166370988) != 0) {
      setState(89);
      antlrcpp::downCast<FunctionContext *>(_localctx)->statements = statement();
      setState(94);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(95);
    match(braneParser::T__7);
   
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
  enterRule(_localctx, 16, braneParser::RulePreprocessor);

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
    setState(97);
    match(braneParser::T__8);
    setState(101);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(98);
        antlrcpp::downCast<IncludeContext *>(_localctx)->content = matchWildcard(); 
      }
      setState(103);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    }
    setState(104);
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
  enterRule(_localctx, 18, braneParser::RuleLink);
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
    setState(106);
    match(braneParser::T__9);
    setState(107);
    antlrcpp::downCast<LinkContext *>(_localctx)->library = match(braneParser::STRING);
    setState(110);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__10) {
      setState(108);
      match(braneParser::T__10);
      setState(109);
      antlrcpp::downCast<LinkContext *>(_localctx)->alias = match(braneParser::STRING);
    }
    setState(112);
    match(braneParser::T__0);
   
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
  enterRule(_localctx, 20, braneParser::RuleStructMember);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(114);
      antlrcpp::downCast<StructMemberContext *>(_localctx)->var = declaration();
      setState(115);
      match(braneParser::T__0);
      break;
    }

    case 2: {
      setState(117);
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
  enterRule(_localctx, 22, braneParser::RuleStructMembers);
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
    setState(123);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 274877906956) != 0) {
      setState(120);
      structMember();
      setState(125);
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
  enterRule(_localctx, 24, braneParser::RuleStructDef);
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
    setState(127);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__11) {
      setState(126);
      antlrcpp::downCast<StructDefContext *>(_localctx)->isPublic = match(braneParser::T__11);
    }
    setState(130);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__12) {
      setState(129);
      antlrcpp::downCast<StructDefContext *>(_localctx)->packed = match(braneParser::T__12);
    }
    setState(132);
    match(braneParser::T__13);
    setState(133);
    antlrcpp::downCast<StructDefContext *>(_localctx)->id = match(braneParser::ID);
    setState(134);
    match(braneParser::T__6);
    setState(135);
    antlrcpp::downCast<StructDefContext *>(_localctx)->memberVars = structMembers();
    setState(136);
    match(braneParser::T__7);
   
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
  enterRule(_localctx, 26, braneParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(167);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::ExprStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(138);
      expression(0);
      setState(139);
      match(braneParser::T__0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::ScopeContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(141);
      match(braneParser::T__6);
      setState(145);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 541166370988) != 0) {
        setState(142);
        statement();
        setState(147);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(148);
      match(braneParser::T__7);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::ReturnValContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(149);
      match(braneParser::T__14);
      setState(150);
      expression(0);
      setState(151);
      match(braneParser::T__0);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<braneParser::ReturnVoidContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(153);
      match(braneParser::T__14);
      setState(154);
      match(braneParser::T__0);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<braneParser::IfContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(155);
      match(braneParser::T__15);
      setState(156);
      match(braneParser::T__4);
      setState(157);
      antlrcpp::downCast<IfContext *>(_localctx)->cond = expression(0);
      setState(158);
      match(braneParser::T__5);
      setState(159);
      antlrcpp::downCast<IfContext *>(_localctx)->operation = statement();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<braneParser::WhileContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(161);
      match(braneParser::T__16);
      setState(162);
      match(braneParser::T__4);
      setState(163);
      antlrcpp::downCast<WhileContext *>(_localctx)->cond = expression(0);
      setState(164);
      match(braneParser::T__5);
      setState(165);
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
//----------------- IndexAccessContext ------------------------------------------------------------------

std::vector<braneParser::ExpressionContext *> braneParser::IndexAccessContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::IndexAccessContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}

braneParser::IndexAccessContext::IndexAccessContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::IndexAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitIndexAccess(this);
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
//----------------- ConstCharContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::ConstCharContext::CHAR() {
  return getToken(braneParser::CHAR, 0);
}

braneParser::ConstCharContext::ConstCharContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::ConstCharContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitConstChar(this);
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
  size_t startState = 28;
  enterRecursionRule(_localctx, 28, braneParser::RuleExpression, precedence);

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
    setState(192);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ConstIntContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(170);
      match(braneParser::INT);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ConstFloatContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(171);
      match(braneParser::FLOAT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ConstCharContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(172);
      match(braneParser::CHAR);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ConstStringContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(173);
      match(braneParser::STRING);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ConstBoolContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(174);
      match(braneParser::BOOL);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<DeclContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(175);
      declaration();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<DeleteContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(176);
      match(braneParser::T__17);
      setState(177);
      antlrcpp::downCast<DeleteContext *>(_localctx)->ptr = expression(12);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<FunctionCallContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(178);
      antlrcpp::downCast<FunctionCallContext *>(_localctx)->name = match(braneParser::ID);
      setState(179);
      match(braneParser::T__4);
      setState(180);
      argumentPack();
      setState(181);
      match(braneParser::T__5);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<IdContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(183);
      match(braneParser::ID);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<CastContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(184);
      match(braneParser::T__4);
      setState(185);
      match(braneParser::ID);
      setState(186);
      match(braneParser::T__5);
      setState(187);
      expression(6);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<InlineScopeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(188);
      match(braneParser::T__4);
      setState(189);
      expression(0);
      setState(190);
      match(braneParser::T__5);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(223);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(221);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MuldivContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(194);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(195);
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
          setState(196);
          antlrcpp::downCast<MuldivContext *>(_localctx)->right = expression(6);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddsubContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(197);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(198);
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
          setState(199);
          antlrcpp::downCast<AddsubContext *>(_localctx)->right = expression(5);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ComparisonContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(200);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(201);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 264241152) != 0)) {
            antlrcpp::downCast<ComparisonContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(202);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->right = expression(4);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<AssignmentContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->dest = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(203);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(204);
          match(braneParser::T__27);
          setState(205);
          antlrcpp::downCast<AssignmentContext *>(_localctx)->expr = expression(2);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<MemberFunctionCallContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(206);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(207);
          match(braneParser::T__18);
          setState(208);
          antlrcpp::downCast<MemberFunctionCallContext *>(_localctx)->name = match(braneParser::ID);
          setState(209);
          match(braneParser::T__4);
          setState(210);
          argumentPack();
          setState(211);
          match(braneParser::T__5);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<IndexAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(213);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(214);
          match(braneParser::T__19);
          setState(215);
          antlrcpp::downCast<IndexAccessContext *>(_localctx)->arg = expression(0);
          setState(216);
          match(braneParser::T__20);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(218);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(219);
          match(braneParser::T__18);
          setState(220);
          antlrcpp::downCast<MemberAccessContext *>(_localctx)->member = match(braneParser::ID);
          break;
        }

        default:
          break;
        } 
      }
      setState(225);
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
    case 14: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

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
    case 4: return precpred(_ctx, 10);
    case 5: return precpred(_ctx, 8);
    case 6: return precpred(_ctx, 7);

  default:
    break;
  }
  return true;
}

void braneParser::initialize() {
  ::antlr4::internal::call_once(braneParserOnceFlag, braneParserInitialize);
}

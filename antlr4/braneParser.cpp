
// Generated from /home/wirewhiz/Documents/git/BraneEngine/libraries/internal/BraneScript/antlr4/brane.g4 by ANTLR 4.11.1


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
      "argumentPack", "functionStub", "function", "link", "export", "exportSegment", 
      "structMember", "structMembers", "structDef", "statement", "expression"
    },
    std::vector<std::string>{
      "", "';'", "'const'", "'ref'", "','", "'opr'", "'[]'", "'('", "')'", 
      "'ext'", "'{'", "'}'", "'link'", "'as'", "'export as'", "'packed'", 
      "'struct'", "'='", "'return'", "'if'", "'else'", "'while'", "'.'", 
      "'['", "']'", "", "", "", "", "", "", "", "", "", "", "'*'", "'/'", 
      "'+'", "'-'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "NEWLINE", "COMMENT", "BLOCK_COMMENT", 
      "SPACE", "BOOL", "INT", "FLOAT", "CHAR", "STRING", "ID", "MUL", "DIV", 
      "ADD", "SUB", "COMPARE", "LOGIC"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,40,263,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,1,0,4,0,36,8,0,11,0,12,0,37,1,0,1,0,1,0,3,0,43,
  	8,0,1,1,1,1,1,1,1,1,1,1,1,1,3,1,51,8,1,1,2,1,2,1,2,1,2,1,3,3,3,58,8,3,
  	1,3,3,3,61,8,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,5,5,71,8,5,10,5,12,5,74,
  	9,5,3,5,76,8,5,1,6,1,6,1,6,5,6,81,8,6,10,6,12,6,84,9,6,3,6,86,8,6,1,7,
  	1,7,1,7,1,7,3,7,92,8,7,1,7,1,7,1,7,1,7,3,7,98,8,7,1,7,1,7,1,7,1,8,1,8,
  	1,8,1,8,3,8,107,8,8,1,8,1,8,1,8,1,8,3,8,113,8,8,1,8,1,8,5,8,117,8,8,10,
  	8,12,8,120,9,8,1,8,1,8,1,9,1,9,1,9,1,9,3,9,128,8,9,1,9,1,9,1,10,1,10,
  	1,10,1,10,5,10,136,8,10,10,10,12,10,139,9,10,1,10,1,10,1,11,1,11,1,11,
  	1,11,3,11,147,8,11,1,12,1,12,1,12,1,12,3,12,153,8,12,1,13,5,13,156,8,
  	13,10,13,12,13,159,9,13,1,14,3,14,162,8,14,1,14,1,14,1,14,1,14,1,14,1,
  	14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,5,15,180,8,15,10,
  	15,12,15,183,9,15,1,15,1,15,1,15,3,15,188,8,15,1,15,1,15,1,15,1,15,1,
  	15,1,15,1,15,1,15,3,15,198,8,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,206,
  	8,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,229,8,16,1,16,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,5,16,258,8,16,10,16,
  	12,16,261,9,16,1,16,0,1,32,17,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
  	30,32,0,3,2,0,6,6,35,40,1,0,35,36,1,0,37,38,295,0,42,1,0,0,0,2,50,1,0,
  	0,0,4,52,1,0,0,0,6,57,1,0,0,0,8,64,1,0,0,0,10,75,1,0,0,0,12,85,1,0,0,
  	0,14,87,1,0,0,0,16,102,1,0,0,0,18,123,1,0,0,0,20,131,1,0,0,0,22,146,1,
  	0,0,0,24,152,1,0,0,0,26,157,1,0,0,0,28,161,1,0,0,0,30,205,1,0,0,0,32,
  	228,1,0,0,0,34,36,3,2,1,0,35,34,1,0,0,0,36,37,1,0,0,0,37,35,1,0,0,0,37,
  	38,1,0,0,0,38,39,1,0,0,0,39,40,5,0,0,1,40,43,1,0,0,0,41,43,5,0,0,1,42,
  	35,1,0,0,0,42,41,1,0,0,0,43,1,1,0,0,0,44,51,3,16,8,0,45,51,3,14,7,0,46,
  	51,3,28,14,0,47,51,3,4,2,0,48,51,3,18,9,0,49,51,3,20,10,0,50,44,1,0,0,
  	0,50,45,1,0,0,0,50,46,1,0,0,0,50,47,1,0,0,0,50,48,1,0,0,0,50,49,1,0,0,
  	0,51,3,1,0,0,0,52,53,3,6,3,0,53,54,5,34,0,0,54,55,5,1,0,0,55,5,1,0,0,
  	0,56,58,5,2,0,0,57,56,1,0,0,0,57,58,1,0,0,0,58,60,1,0,0,0,59,61,5,3,0,
  	0,60,59,1,0,0,0,60,61,1,0,0,0,61,62,1,0,0,0,62,63,5,34,0,0,63,7,1,0,0,
  	0,64,65,3,6,3,0,65,66,5,34,0,0,66,9,1,0,0,0,67,72,3,8,4,0,68,69,5,4,0,
  	0,69,71,3,8,4,0,70,68,1,0,0,0,71,74,1,0,0,0,72,70,1,0,0,0,72,73,1,0,0,
  	0,73,76,1,0,0,0,74,72,1,0,0,0,75,67,1,0,0,0,75,76,1,0,0,0,76,11,1,0,0,
  	0,77,82,3,32,16,0,78,79,5,4,0,0,79,81,3,32,16,0,80,78,1,0,0,0,81,84,1,
  	0,0,0,82,80,1,0,0,0,82,83,1,0,0,0,83,86,1,0,0,0,84,82,1,0,0,0,85,77,1,
  	0,0,0,85,86,1,0,0,0,86,13,1,0,0,0,87,91,3,6,3,0,88,92,5,34,0,0,89,90,
  	5,5,0,0,90,92,7,0,0,0,91,88,1,0,0,0,91,89,1,0,0,0,92,93,1,0,0,0,93,94,
  	5,7,0,0,94,95,3,10,5,0,95,97,5,8,0,0,96,98,5,2,0,0,97,96,1,0,0,0,97,98,
  	1,0,0,0,98,99,1,0,0,0,99,100,5,9,0,0,100,101,5,1,0,0,101,15,1,0,0,0,102,
  	106,3,6,3,0,103,107,5,34,0,0,104,105,5,5,0,0,105,107,7,0,0,0,106,103,
  	1,0,0,0,106,104,1,0,0,0,107,108,1,0,0,0,108,109,5,7,0,0,109,110,3,10,
  	5,0,110,112,5,8,0,0,111,113,5,2,0,0,112,111,1,0,0,0,112,113,1,0,0,0,113,
  	114,1,0,0,0,114,118,5,10,0,0,115,117,3,30,15,0,116,115,1,0,0,0,117,120,
  	1,0,0,0,118,116,1,0,0,0,118,119,1,0,0,0,119,121,1,0,0,0,120,118,1,0,0,
  	0,121,122,5,11,0,0,122,17,1,0,0,0,123,124,5,12,0,0,124,127,5,33,0,0,125,
  	126,5,13,0,0,126,128,5,33,0,0,127,125,1,0,0,0,127,128,1,0,0,0,128,129,
  	1,0,0,0,129,130,5,1,0,0,130,19,1,0,0,0,131,132,5,14,0,0,132,133,5,33,
  	0,0,133,137,5,10,0,0,134,136,3,22,11,0,135,134,1,0,0,0,136,139,1,0,0,
  	0,137,135,1,0,0,0,137,138,1,0,0,0,138,140,1,0,0,0,139,137,1,0,0,0,140,
  	141,5,11,0,0,141,21,1,0,0,0,142,147,3,16,8,0,143,147,3,14,7,0,144,147,
  	3,28,14,0,145,147,3,4,2,0,146,142,1,0,0,0,146,143,1,0,0,0,146,144,1,0,
  	0,0,146,145,1,0,0,0,147,23,1,0,0,0,148,149,3,8,4,0,149,150,5,1,0,0,150,
  	153,1,0,0,0,151,153,3,16,8,0,152,148,1,0,0,0,152,151,1,0,0,0,153,25,1,
  	0,0,0,154,156,3,24,12,0,155,154,1,0,0,0,156,159,1,0,0,0,157,155,1,0,0,
  	0,157,158,1,0,0,0,158,27,1,0,0,0,159,157,1,0,0,0,160,162,5,15,0,0,161,
  	160,1,0,0,0,161,162,1,0,0,0,162,163,1,0,0,0,163,164,5,16,0,0,164,165,
  	5,34,0,0,165,166,5,10,0,0,166,167,3,26,13,0,167,168,5,11,0,0,168,29,1,
  	0,0,0,169,170,3,32,16,0,170,171,5,1,0,0,171,206,1,0,0,0,172,173,3,32,
  	16,0,173,174,5,17,0,0,174,175,3,32,16,0,175,176,5,1,0,0,176,206,1,0,0,
  	0,177,181,5,10,0,0,178,180,3,30,15,0,179,178,1,0,0,0,180,183,1,0,0,0,
  	181,179,1,0,0,0,181,182,1,0,0,0,182,184,1,0,0,0,183,181,1,0,0,0,184,206,
  	5,11,0,0,185,187,5,18,0,0,186,188,3,32,16,0,187,186,1,0,0,0,187,188,1,
  	0,0,0,188,189,1,0,0,0,189,206,5,1,0,0,190,191,5,19,0,0,191,192,5,7,0,
  	0,192,193,3,32,16,0,193,194,5,8,0,0,194,197,3,30,15,0,195,196,5,20,0,
  	0,196,198,3,30,15,0,197,195,1,0,0,0,197,198,1,0,0,0,198,206,1,0,0,0,199,
  	200,5,21,0,0,200,201,5,7,0,0,201,202,3,32,16,0,202,203,5,8,0,0,203,204,
  	3,30,15,0,204,206,1,0,0,0,205,169,1,0,0,0,205,172,1,0,0,0,205,177,1,0,
  	0,0,205,185,1,0,0,0,205,190,1,0,0,0,205,199,1,0,0,0,206,31,1,0,0,0,207,
  	208,6,16,-1,0,208,229,5,30,0,0,209,229,5,31,0,0,210,229,5,32,0,0,211,
  	229,5,33,0,0,212,229,5,29,0,0,213,229,3,8,4,0,214,215,5,34,0,0,215,216,
  	5,7,0,0,216,217,3,12,6,0,217,218,5,8,0,0,218,229,1,0,0,0,219,229,5,34,
  	0,0,220,221,5,7,0,0,221,222,5,34,0,0,222,223,5,8,0,0,223,229,3,32,16,
  	6,224,225,5,7,0,0,225,226,3,32,16,0,226,227,5,8,0,0,227,229,1,0,0,0,228,
  	207,1,0,0,0,228,209,1,0,0,0,228,210,1,0,0,0,228,211,1,0,0,0,228,212,1,
  	0,0,0,228,213,1,0,0,0,228,214,1,0,0,0,228,219,1,0,0,0,228,220,1,0,0,0,
  	228,224,1,0,0,0,229,259,1,0,0,0,230,231,10,5,0,0,231,232,7,1,0,0,232,
  	258,3,32,16,6,233,234,10,4,0,0,234,235,7,2,0,0,235,258,3,32,16,5,236,
  	237,10,3,0,0,237,238,5,40,0,0,238,258,3,32,16,4,239,240,10,2,0,0,240,
  	241,5,39,0,0,241,258,3,32,16,3,242,243,10,10,0,0,243,244,5,22,0,0,244,
  	245,5,34,0,0,245,246,5,7,0,0,246,247,3,12,6,0,247,248,5,8,0,0,248,258,
  	1,0,0,0,249,250,10,8,0,0,250,251,5,23,0,0,251,252,3,32,16,0,252,253,5,
  	24,0,0,253,258,1,0,0,0,254,255,10,7,0,0,255,256,5,22,0,0,256,258,5,34,
  	0,0,257,230,1,0,0,0,257,233,1,0,0,0,257,236,1,0,0,0,257,239,1,0,0,0,257,
  	242,1,0,0,0,257,249,1,0,0,0,257,254,1,0,0,0,258,261,1,0,0,0,259,257,1,
  	0,0,0,259,260,1,0,0,0,260,33,1,0,0,0,261,259,1,0,0,0,27,37,42,50,57,60,
  	72,75,82,85,91,97,106,112,118,127,137,146,152,157,161,181,187,197,205,
  	228,257,259
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
    setState(42);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__1:
      case braneParser::T__2:
      case braneParser::T__11:
      case braneParser::T__13:
      case braneParser::T__14:
      case braneParser::T__15:
      case braneParser::ID: {
        setState(35); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(34);
          progSegment();
          setState(37); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 17179987980) != 0);
        setState(39);
        match(braneParser::EOF);
        break;
      }

      case braneParser::EOF: {
        setState(41);
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

braneParser::FunctionStubContext* braneParser::ProgSegmentContext::functionStub() {
  return getRuleContext<braneParser::FunctionStubContext>(0);
}

braneParser::StructDefContext* braneParser::ProgSegmentContext::structDef() {
  return getRuleContext<braneParser::StructDefContext>(0);
}

braneParser::GlobalContext* braneParser::ProgSegmentContext::global() {
  return getRuleContext<braneParser::GlobalContext>(0);
}

braneParser::LinkContext* braneParser::ProgSegmentContext::link() {
  return getRuleContext<braneParser::LinkContext>(0);
}

braneParser::ExportContext* braneParser::ProgSegmentContext::export_() {
  return getRuleContext<braneParser::ExportContext>(0);
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
    setState(50);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(44);
      function();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(45);
      functionStub();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(46);
      structDef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(47);
      global();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(48);
      link();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(49);
      export_();
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

braneParser::TypeContext* braneParser::GlobalContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}

tree::TerminalNode* braneParser::GlobalContext::ID() {
  return getToken(braneParser::ID, 0);
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
    setState(52);
    type();
    setState(53);
    antlrcpp::downCast<GlobalContext *>(_localctx)->id = match(braneParser::ID);
    setState(54);
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
    setState(57);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__1) {
      setState(56);
      antlrcpp::downCast<TypeContext *>(_localctx)->isConst = match(braneParser::T__1);
    }
    setState(60);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__2) {
      setState(59);
      antlrcpp::downCast<TypeContext *>(_localctx)->isRef = match(braneParser::T__2);
    }
    setState(62);
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
    setState(64);
    type();
    setState(65);
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
    setState(75);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17179869196) != 0) {
      setState(67);
      declaration();
      setState(72);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__3) {
        setState(68);
        match(braneParser::T__3);
        setState(69);
        declaration();
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
    setState(85);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 33822867596) != 0) {
      setState(77);
      expression(0);
      setState(82);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__3) {
        setState(78);
        match(braneParser::T__3);
        setState(79);
        expression(0);
        setState(84);
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

//----------------- FunctionStubContext ------------------------------------------------------------------

braneParser::FunctionStubContext::FunctionStubContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::TypeContext* braneParser::FunctionStubContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}

braneParser::ArgumentListContext* braneParser::FunctionStubContext::argumentList() {
  return getRuleContext<braneParser::ArgumentListContext>(0);
}

tree::TerminalNode* braneParser::FunctionStubContext::ID() {
  return getToken(braneParser::ID, 0);
}

tree::TerminalNode* braneParser::FunctionStubContext::ADD() {
  return getToken(braneParser::ADD, 0);
}

tree::TerminalNode* braneParser::FunctionStubContext::SUB() {
  return getToken(braneParser::SUB, 0);
}

tree::TerminalNode* braneParser::FunctionStubContext::MUL() {
  return getToken(braneParser::MUL, 0);
}

tree::TerminalNode* braneParser::FunctionStubContext::DIV() {
  return getToken(braneParser::DIV, 0);
}

tree::TerminalNode* braneParser::FunctionStubContext::COMPARE() {
  return getToken(braneParser::COMPARE, 0);
}

tree::TerminalNode* braneParser::FunctionStubContext::LOGIC() {
  return getToken(braneParser::LOGIC, 0);
}


size_t braneParser::FunctionStubContext::getRuleIndex() const {
  return braneParser::RuleFunctionStub;
}


std::any braneParser::FunctionStubContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitFunctionStub(this);
  else
    return visitor->visitChildren(this);
}

braneParser::FunctionStubContext* braneParser::functionStub() {
  FunctionStubContext *_localctx = _tracker.createInstance<FunctionStubContext>(_ctx, getState());
  enterRule(_localctx, 14, braneParser::RuleFunctionStub);
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
    setState(87);
    type();
    setState(91);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::ID: {
        setState(88);
        antlrcpp::downCast<FunctionStubContext *>(_localctx)->id = match(braneParser::ID);
        break;
      }

      case braneParser::T__4: {
        setState(89);
        match(braneParser::T__4);
        setState(90);
        antlrcpp::downCast<FunctionStubContext *>(_localctx)->oprID = _input->LT(1);
        _la = _input->LA(1);
        if (!(((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 2164663517248) != 0)) {
          antlrcpp::downCast<FunctionStubContext *>(_localctx)->oprID = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(93);
    match(braneParser::T__6);
    setState(94);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->arguments = argumentList();
    setState(95);
    match(braneParser::T__7);
    setState(97);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__1) {
      setState(96);
      antlrcpp::downCast<FunctionStubContext *>(_localctx)->isConst = match(braneParser::T__1);
    }
    setState(99);
    match(braneParser::T__8);
    setState(100);
    match(braneParser::T__0);
   
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

braneParser::ArgumentListContext* braneParser::FunctionContext::argumentList() {
  return getRuleContext<braneParser::ArgumentListContext>(0);
}

tree::TerminalNode* braneParser::FunctionContext::ID() {
  return getToken(braneParser::ID, 0);
}

std::vector<braneParser::StatementContext *> braneParser::FunctionContext::statement() {
  return getRuleContexts<braneParser::StatementContext>();
}

braneParser::StatementContext* braneParser::FunctionContext::statement(size_t i) {
  return getRuleContext<braneParser::StatementContext>(i);
}

tree::TerminalNode* braneParser::FunctionContext::ADD() {
  return getToken(braneParser::ADD, 0);
}

tree::TerminalNode* braneParser::FunctionContext::SUB() {
  return getToken(braneParser::SUB, 0);
}

tree::TerminalNode* braneParser::FunctionContext::MUL() {
  return getToken(braneParser::MUL, 0);
}

tree::TerminalNode* braneParser::FunctionContext::DIV() {
  return getToken(braneParser::DIV, 0);
}

tree::TerminalNode* braneParser::FunctionContext::COMPARE() {
  return getToken(braneParser::COMPARE, 0);
}

tree::TerminalNode* braneParser::FunctionContext::LOGIC() {
  return getToken(braneParser::LOGIC, 0);
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
  enterRule(_localctx, 16, braneParser::RuleFunction);
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
    setState(102);
    type();
    setState(106);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::ID: {
        setState(103);
        antlrcpp::downCast<FunctionContext *>(_localctx)->id = match(braneParser::ID);
        break;
      }

      case braneParser::T__4: {
        setState(104);
        match(braneParser::T__4);
        setState(105);
        antlrcpp::downCast<FunctionContext *>(_localctx)->oprID = _input->LT(1);
        _la = _input->LA(1);
        if (!(((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 2164663517248) != 0)) {
          antlrcpp::downCast<FunctionContext *>(_localctx)->oprID = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(108);
    match(braneParser::T__6);
    setState(109);
    antlrcpp::downCast<FunctionContext *>(_localctx)->arguments = argumentList();
    setState(110);
    match(braneParser::T__7);
    setState(112);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__1) {
      setState(111);
      antlrcpp::downCast<FunctionContext *>(_localctx)->isConst = match(braneParser::T__1);
    }
    setState(114);
    match(braneParser::T__9);
    setState(118);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 33825752204) != 0) {
      setState(115);
      antlrcpp::downCast<FunctionContext *>(_localctx)->statements = statement();
      setState(120);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(121);
    match(braneParser::T__10);
   
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
    setState(123);
    match(braneParser::T__11);
    setState(124);
    antlrcpp::downCast<LinkContext *>(_localctx)->library = match(braneParser::STRING);
    setState(127);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__12) {
      setState(125);
      match(braneParser::T__12);
      setState(126);
      antlrcpp::downCast<LinkContext *>(_localctx)->alias = match(braneParser::STRING);
    }
    setState(129);
    match(braneParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExportContext ------------------------------------------------------------------

braneParser::ExportContext::ExportContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* braneParser::ExportContext::STRING() {
  return getToken(braneParser::STRING, 0);
}

std::vector<braneParser::ExportSegmentContext *> braneParser::ExportContext::exportSegment() {
  return getRuleContexts<braneParser::ExportSegmentContext>();
}

braneParser::ExportSegmentContext* braneParser::ExportContext::exportSegment(size_t i) {
  return getRuleContext<braneParser::ExportSegmentContext>(i);
}


size_t braneParser::ExportContext::getRuleIndex() const {
  return braneParser::RuleExport;
}


std::any braneParser::ExportContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitExport(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ExportContext* braneParser::export_() {
  ExportContext *_localctx = _tracker.createInstance<ExportContext>(_ctx, getState());
  enterRule(_localctx, 20, braneParser::RuleExport);
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
    setState(131);
    match(braneParser::T__13);
    setState(132);
    antlrcpp::downCast<ExportContext *>(_localctx)->libID = match(braneParser::STRING);
    setState(133);
    match(braneParser::T__9);
    setState(137);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17179967500) != 0) {
      setState(134);
      exportSegment();
      setState(139);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(140);
    match(braneParser::T__10);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExportSegmentContext ------------------------------------------------------------------

braneParser::ExportSegmentContext::ExportSegmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::FunctionContext* braneParser::ExportSegmentContext::function() {
  return getRuleContext<braneParser::FunctionContext>(0);
}

braneParser::FunctionStubContext* braneParser::ExportSegmentContext::functionStub() {
  return getRuleContext<braneParser::FunctionStubContext>(0);
}

braneParser::StructDefContext* braneParser::ExportSegmentContext::structDef() {
  return getRuleContext<braneParser::StructDefContext>(0);
}

braneParser::GlobalContext* braneParser::ExportSegmentContext::global() {
  return getRuleContext<braneParser::GlobalContext>(0);
}


size_t braneParser::ExportSegmentContext::getRuleIndex() const {
  return braneParser::RuleExportSegment;
}


std::any braneParser::ExportSegmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitExportSegment(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ExportSegmentContext* braneParser::exportSegment() {
  ExportSegmentContext *_localctx = _tracker.createInstance<ExportSegmentContext>(_ctx, getState());
  enterRule(_localctx, 22, braneParser::RuleExportSegment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(146);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(142);
      function();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(143);
      functionStub();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(144);
      structDef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(145);
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
  enterRule(_localctx, 24, braneParser::RuleStructMember);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      setState(148);
      antlrcpp::downCast<StructMemberContext *>(_localctx)->var = declaration();
      setState(149);
      match(braneParser::T__0);
      break;
    }

    case 2: {
      setState(151);
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
  enterRule(_localctx, 26, braneParser::RuleStructMembers);
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
    setState(157);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17179869196) != 0) {
      setState(154);
      structMember();
      setState(159);
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
  enterRule(_localctx, 28, braneParser::RuleStructDef);
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
    setState(161);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__14) {
      setState(160);
      antlrcpp::downCast<StructDefContext *>(_localctx)->packed = match(braneParser::T__14);
    }
    setState(163);
    match(braneParser::T__15);
    setState(164);
    antlrcpp::downCast<StructDefContext *>(_localctx)->id = match(braneParser::ID);
    setState(165);
    match(braneParser::T__9);
    setState(166);
    antlrcpp::downCast<StructDefContext *>(_localctx)->memberVars = structMembers();
    setState(167);
    match(braneParser::T__10);
   
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

//----------------- AssignmentContext ------------------------------------------------------------------

std::vector<braneParser::ExpressionContext *> braneParser::AssignmentContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::AssignmentContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}

braneParser::AssignmentContext::AssignmentContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
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

std::vector<braneParser::StatementContext *> braneParser::IfContext::statement() {
  return getRuleContexts<braneParser::StatementContext>();
}

braneParser::StatementContext* braneParser::IfContext::statement(size_t i) {
  return getRuleContext<braneParser::StatementContext>(i);
}

braneParser::IfContext::IfContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::IfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitIf(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::ReturnContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::ReturnContext::ReturnContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::ReturnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitReturn(this);
  else
    return visitor->visitChildren(this);
}
braneParser::StatementContext* braneParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 30, braneParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(205);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::ExprStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(169);
      expression(0);
      setState(170);
      match(braneParser::T__0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::AssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(172);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->lValue = expression(0);
      setState(173);
      match(braneParser::T__16);
      setState(174);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->rValue = expression(0);
      setState(175);
      match(braneParser::T__0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::ScopeContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(177);
      match(braneParser::T__9);
      setState(181);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 33825752204) != 0) {
        setState(178);
        statement();
        setState(183);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(184);
      match(braneParser::T__10);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<braneParser::ReturnContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(185);
      match(braneParser::T__17);
      setState(187);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 33822867596) != 0) {
        setState(186);
        expression(0);
      }
      setState(189);
      match(braneParser::T__0);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<braneParser::IfContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(190);
      match(braneParser::T__18);
      setState(191);
      match(braneParser::T__6);
      setState(192);
      antlrcpp::downCast<IfContext *>(_localctx)->cond = expression(0);
      setState(193);
      match(braneParser::T__7);
      setState(194);
      antlrcpp::downCast<IfContext *>(_localctx)->operation = statement();
      setState(197);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
      case 1: {
        setState(195);
        match(braneParser::T__19);
        setState(196);
        antlrcpp::downCast<IfContext *>(_localctx)->elseOp = statement();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<braneParser::WhileContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(199);
      match(braneParser::T__20);
      setState(200);
      match(braneParser::T__6);
      setState(201);
      antlrcpp::downCast<WhileContext *>(_localctx)->cond = expression(0);
      setState(202);
      match(braneParser::T__7);
      setState(203);
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

tree::TerminalNode* braneParser::ComparisonContext::COMPARE() {
  return getToken(braneParser::COMPARE, 0);
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
//----------------- ParenContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::ParenContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::ParenContext::ParenContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::ParenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitParen(this);
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
//----------------- LogicContext ------------------------------------------------------------------

std::vector<braneParser::ExpressionContext *> braneParser::LogicContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::LogicContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}

tree::TerminalNode* braneParser::LogicContext::LOGIC() {
  return getToken(braneParser::LOGIC, 0);
}

braneParser::LogicContext::LogicContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::LogicContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitLogic(this);
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
  size_t startState = 32;
  enterRecursionRule(_localctx, 32, braneParser::RuleExpression, precedence);

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
    setState(228);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ConstIntContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(208);
      match(braneParser::INT);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ConstFloatContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(209);
      match(braneParser::FLOAT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ConstCharContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(210);
      match(braneParser::CHAR);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ConstStringContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(211);
      match(braneParser::STRING);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ConstBoolContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(212);
      match(braneParser::BOOL);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<DeclContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(213);
      declaration();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<FunctionCallContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(214);
      antlrcpp::downCast<FunctionCallContext *>(_localctx)->name = match(braneParser::ID);
      setState(215);
      match(braneParser::T__6);
      setState(216);
      argumentPack();
      setState(217);
      match(braneParser::T__7);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<IdContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(219);
      match(braneParser::ID);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<CastContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(220);
      match(braneParser::T__6);
      setState(221);
      match(braneParser::ID);
      setState(222);
      match(braneParser::T__7);
      setState(223);
      expression(6);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<ParenContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(224);
      match(braneParser::T__6);
      setState(225);
      expression(0);
      setState(226);
      match(braneParser::T__7);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(259);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(257);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MuldivContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(230);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(231);
          antlrcpp::downCast<MuldivContext *>(_localctx)->opr = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == braneParser::MUL

          || _la == braneParser::DIV)) {
            antlrcpp::downCast<MuldivContext *>(_localctx)->opr = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(232);
          antlrcpp::downCast<MuldivContext *>(_localctx)->right = expression(6);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddsubContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(233);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(234);
          antlrcpp::downCast<AddsubContext *>(_localctx)->opr = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == braneParser::ADD

          || _la == braneParser::SUB)) {
            antlrcpp::downCast<AddsubContext *>(_localctx)->opr = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(235);
          antlrcpp::downCast<AddsubContext *>(_localctx)->right = expression(5);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<LogicContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(236);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(237);
          antlrcpp::downCast<LogicContext *>(_localctx)->opr = match(braneParser::LOGIC);
          setState(238);
          antlrcpp::downCast<LogicContext *>(_localctx)->right = expression(4);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<ComparisonContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(239);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(240);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->opr = match(braneParser::COMPARE);
          setState(241);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->right = expression(3);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<MemberFunctionCallContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(242);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(243);
          match(braneParser::T__21);
          setState(244);
          antlrcpp::downCast<MemberFunctionCallContext *>(_localctx)->name = match(braneParser::ID);
          setState(245);
          match(braneParser::T__6);
          setState(246);
          argumentPack();
          setState(247);
          match(braneParser::T__7);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<IndexAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(249);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(250);
          match(braneParser::T__22);
          setState(251);
          antlrcpp::downCast<IndexAccessContext *>(_localctx)->arg = expression(0);
          setState(252);
          match(braneParser::T__23);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(254);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(255);
          match(braneParser::T__21);
          setState(256);
          antlrcpp::downCast<MemberAccessContext *>(_localctx)->member = match(braneParser::ID);
          break;
        }

        default:
          break;
        } 
      }
      setState(261);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
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
    case 16: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

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
    case 3: return precpred(_ctx, 2);
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

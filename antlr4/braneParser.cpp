
// Generated from /home/wirewhiz/Documents/git/BraneEngine/libraries/internal/BraneScript/antlr4/brane.g4 by ANTLR 4.12.0


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
      "program", "progSegment", "global", "templateDefArgument", "templateDef", 
      "templateArg", "templateArgs", "scopedID", "type", "declaration", 
      "argumentListItem", "argumentList", "argumentPackItem", "argumentPack", 
      "functionSig", "functionStub", "function", "link", "export", "exportSegment", 
      "structDef", "structMember", "statement", "expression"
    },
    std::vector<std::string>{
      "", "';'", "'type'", "'...'", "'template'", "'<'", "','", "'>'", "'::'", 
      "'const'", "'ref'", "'constexpr'", "'opr'", "'=='", "'!='", "'<='", 
      "'>='", "'[]'", "'('", "')'", "'ext'", "'{'", "'}'", "'link'", "'as'", 
      "'export as'", "'packed'", "'struct'", "'='", "'return'", "'if'", 
      "'else'", "'while'", "'unroll'", "'sizeof'", "'.'", "'['", "']'", 
      "", "", "", "", "", "", "", "", "", "", "'*'", "'/'", "'+'", "'-'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "NEWLINE", "COMMENT", "BLOCK_COMMENT", "SPACE", "BOOL", 
      "INT", "FLOAT", "CHAR", "STRING", "ID", "MUL", "DIV", "ADD", "SUB", 
      "LOGIC"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,52,362,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,1,0,4,0,50,8,0,11,0,12,0,51,1,0,1,0,1,0,3,0,57,
  	8,0,1,1,1,1,1,1,1,1,1,1,1,1,3,1,65,8,1,1,2,1,2,1,2,1,2,1,3,1,3,3,3,73,
  	8,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,5,4,82,8,4,10,4,12,4,85,9,4,1,4,1,4,1,
  	5,1,5,1,5,3,5,92,8,5,1,6,1,6,1,6,1,6,5,6,98,8,6,10,6,12,6,101,9,6,1,6,
  	1,6,1,7,1,7,3,7,107,8,7,1,7,1,7,3,7,111,8,7,1,8,3,8,114,8,8,1,8,3,8,117,
  	8,8,1,8,1,8,1,9,1,9,1,9,1,10,1,10,1,10,1,10,3,10,128,8,10,1,11,1,11,1,
  	11,5,11,133,8,11,10,11,12,11,136,9,11,3,11,138,8,11,1,12,1,12,1,12,3,
  	12,143,8,12,1,13,1,13,1,13,5,13,148,8,13,10,13,12,13,151,9,13,3,13,153,
  	8,13,1,14,3,14,156,8,14,1,14,3,14,159,8,14,1,14,1,14,1,14,1,14,3,14,165,
  	8,14,1,14,1,14,3,14,169,8,14,1,15,1,15,1,15,1,15,1,15,3,15,176,8,15,1,
  	15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,3,16,186,8,16,1,16,1,16,5,16,190,
  	8,16,10,16,12,16,193,9,16,1,16,1,16,1,17,1,17,1,17,1,17,3,17,201,8,17,
  	1,17,1,17,1,18,1,18,1,18,1,18,5,18,209,8,18,10,18,12,18,212,9,18,1,18,
  	1,18,1,19,1,19,1,19,1,19,3,19,220,8,19,1,20,3,20,223,8,20,1,20,3,20,226,
  	8,20,1,20,1,20,1,20,1,20,5,20,232,8,20,10,20,12,20,235,9,20,1,20,1,20,
  	1,21,1,21,1,21,1,21,3,21,243,8,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,
  	1,22,1,22,1,22,5,22,255,8,22,10,22,12,22,258,9,22,1,22,1,22,1,22,3,22,
  	263,8,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,273,8,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,286,8,22,1,23,1,
  	23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,
  	23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,
  	23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,3,23,325,8,23,1,23,1,23,1,23,1,
  	23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,3,23,343,
  	8,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,5,23,
  	357,8,23,10,23,12,23,360,9,23,1,23,0,1,46,24,0,2,4,6,8,10,12,14,16,18,
  	20,22,24,26,28,30,32,34,36,38,40,42,44,46,0,4,4,0,5,5,7,7,13,17,48,52,
  	1,0,48,49,1,0,50,51,3,0,5,5,7,7,13,16,403,0,56,1,0,0,0,2,64,1,0,0,0,4,
  	66,1,0,0,0,6,70,1,0,0,0,8,76,1,0,0,0,10,91,1,0,0,0,12,93,1,0,0,0,14,104,
  	1,0,0,0,16,113,1,0,0,0,18,120,1,0,0,0,20,127,1,0,0,0,22,137,1,0,0,0,24,
  	142,1,0,0,0,26,152,1,0,0,0,28,155,1,0,0,0,30,170,1,0,0,0,32,180,1,0,0,
  	0,34,196,1,0,0,0,36,204,1,0,0,0,38,219,1,0,0,0,40,222,1,0,0,0,42,242,
  	1,0,0,0,44,285,1,0,0,0,46,324,1,0,0,0,48,50,3,2,1,0,49,48,1,0,0,0,50,
  	51,1,0,0,0,51,49,1,0,0,0,51,52,1,0,0,0,52,53,1,0,0,0,53,54,5,0,0,1,54,
  	57,1,0,0,0,55,57,5,0,0,1,56,49,1,0,0,0,56,55,1,0,0,0,57,1,1,0,0,0,58,
  	65,3,32,16,0,59,65,3,30,15,0,60,65,3,40,20,0,61,65,3,4,2,0,62,65,3,34,
  	17,0,63,65,3,36,18,0,64,58,1,0,0,0,64,59,1,0,0,0,64,60,1,0,0,0,64,61,
  	1,0,0,0,64,62,1,0,0,0,64,63,1,0,0,0,65,3,1,0,0,0,66,67,3,16,8,0,67,68,
  	5,47,0,0,68,69,5,1,0,0,69,5,1,0,0,0,70,72,5,2,0,0,71,73,5,3,0,0,72,71,
  	1,0,0,0,72,73,1,0,0,0,73,74,1,0,0,0,74,75,5,47,0,0,75,7,1,0,0,0,76,77,
  	5,4,0,0,77,78,5,5,0,0,78,83,3,6,3,0,79,80,5,6,0,0,80,82,3,6,3,0,81,79,
  	1,0,0,0,82,85,1,0,0,0,83,81,1,0,0,0,83,84,1,0,0,0,84,86,1,0,0,0,85,83,
  	1,0,0,0,86,87,5,7,0,0,87,9,1,0,0,0,88,92,3,16,8,0,89,90,5,47,0,0,90,92,
  	5,3,0,0,91,88,1,0,0,0,91,89,1,0,0,0,92,11,1,0,0,0,93,94,5,5,0,0,94,99,
  	3,10,5,0,95,96,5,6,0,0,96,98,3,10,5,0,97,95,1,0,0,0,98,101,1,0,0,0,99,
  	97,1,0,0,0,99,100,1,0,0,0,100,102,1,0,0,0,101,99,1,0,0,0,102,103,5,7,
  	0,0,103,13,1,0,0,0,104,106,5,47,0,0,105,107,3,12,6,0,106,105,1,0,0,0,
  	106,107,1,0,0,0,107,110,1,0,0,0,108,109,5,8,0,0,109,111,3,14,7,0,110,
  	108,1,0,0,0,110,111,1,0,0,0,111,15,1,0,0,0,112,114,5,9,0,0,113,112,1,
  	0,0,0,113,114,1,0,0,0,114,116,1,0,0,0,115,117,5,10,0,0,116,115,1,0,0,
  	0,116,117,1,0,0,0,117,118,1,0,0,0,118,119,3,14,7,0,119,17,1,0,0,0,120,
  	121,3,16,8,0,121,122,5,47,0,0,122,19,1,0,0,0,123,128,3,18,9,0,124,125,
  	5,47,0,0,125,126,5,3,0,0,126,128,5,47,0,0,127,123,1,0,0,0,127,124,1,0,
  	0,0,128,21,1,0,0,0,129,134,3,20,10,0,130,131,5,6,0,0,131,133,3,20,10,
  	0,132,130,1,0,0,0,133,136,1,0,0,0,134,132,1,0,0,0,134,135,1,0,0,0,135,
  	138,1,0,0,0,136,134,1,0,0,0,137,129,1,0,0,0,137,138,1,0,0,0,138,23,1,
  	0,0,0,139,143,3,46,23,0,140,141,5,47,0,0,141,143,5,3,0,0,142,139,1,0,
  	0,0,142,140,1,0,0,0,143,25,1,0,0,0,144,149,3,24,12,0,145,146,5,6,0,0,
  	146,148,3,24,12,0,147,145,1,0,0,0,148,151,1,0,0,0,149,147,1,0,0,0,149,
  	150,1,0,0,0,150,153,1,0,0,0,151,149,1,0,0,0,152,144,1,0,0,0,152,153,1,
  	0,0,0,153,27,1,0,0,0,154,156,3,8,4,0,155,154,1,0,0,0,155,156,1,0,0,0,
  	156,158,1,0,0,0,157,159,5,11,0,0,158,157,1,0,0,0,158,159,1,0,0,0,159,
  	168,1,0,0,0,160,164,3,16,8,0,161,165,5,47,0,0,162,163,5,12,0,0,163,165,
  	7,0,0,0,164,161,1,0,0,0,164,162,1,0,0,0,165,169,1,0,0,0,166,167,5,12,
  	0,0,167,169,3,16,8,0,168,160,1,0,0,0,168,166,1,0,0,0,169,29,1,0,0,0,170,
  	171,3,28,14,0,171,172,5,18,0,0,172,173,3,22,11,0,173,175,5,19,0,0,174,
  	176,5,9,0,0,175,174,1,0,0,0,175,176,1,0,0,0,176,177,1,0,0,0,177,178,5,
  	20,0,0,178,179,5,1,0,0,179,31,1,0,0,0,180,181,3,28,14,0,181,182,5,18,
  	0,0,182,183,3,22,11,0,183,185,5,19,0,0,184,186,5,9,0,0,185,184,1,0,0,
  	0,185,186,1,0,0,0,186,187,1,0,0,0,187,191,5,21,0,0,188,190,3,44,22,0,
  	189,188,1,0,0,0,190,193,1,0,0,0,191,189,1,0,0,0,191,192,1,0,0,0,192,194,
  	1,0,0,0,193,191,1,0,0,0,194,195,5,22,0,0,195,33,1,0,0,0,196,197,5,23,
  	0,0,197,200,5,46,0,0,198,199,5,24,0,0,199,201,5,46,0,0,200,198,1,0,0,
  	0,200,201,1,0,0,0,201,202,1,0,0,0,202,203,5,1,0,0,203,35,1,0,0,0,204,
  	205,5,25,0,0,205,206,5,46,0,0,206,210,5,21,0,0,207,209,3,38,19,0,208,
  	207,1,0,0,0,209,212,1,0,0,0,210,208,1,0,0,0,210,211,1,0,0,0,211,213,1,
  	0,0,0,212,210,1,0,0,0,213,214,5,22,0,0,214,37,1,0,0,0,215,220,3,32,16,
  	0,216,220,3,30,15,0,217,220,3,40,20,0,218,220,3,4,2,0,219,215,1,0,0,0,
  	219,216,1,0,0,0,219,217,1,0,0,0,219,218,1,0,0,0,220,39,1,0,0,0,221,223,
  	3,8,4,0,222,221,1,0,0,0,222,223,1,0,0,0,223,225,1,0,0,0,224,226,5,26,
  	0,0,225,224,1,0,0,0,225,226,1,0,0,0,226,227,1,0,0,0,227,228,5,27,0,0,
  	228,229,5,47,0,0,229,233,5,21,0,0,230,232,3,42,21,0,231,230,1,0,0,0,232,
  	235,1,0,0,0,233,231,1,0,0,0,233,234,1,0,0,0,234,236,1,0,0,0,235,233,1,
  	0,0,0,236,237,5,22,0,0,237,41,1,0,0,0,238,239,3,18,9,0,239,240,5,1,0,
  	0,240,243,1,0,0,0,241,243,3,32,16,0,242,238,1,0,0,0,242,241,1,0,0,0,243,
  	43,1,0,0,0,244,245,3,46,23,0,245,246,5,1,0,0,246,286,1,0,0,0,247,248,
  	3,46,23,0,248,249,5,28,0,0,249,250,3,46,23,0,250,251,5,1,0,0,251,286,
  	1,0,0,0,252,256,5,21,0,0,253,255,3,44,22,0,254,253,1,0,0,0,255,258,1,
  	0,0,0,256,254,1,0,0,0,256,257,1,0,0,0,257,259,1,0,0,0,258,256,1,0,0,0,
  	259,286,5,22,0,0,260,262,5,29,0,0,261,263,3,46,23,0,262,261,1,0,0,0,262,
  	263,1,0,0,0,263,264,1,0,0,0,264,286,5,1,0,0,265,266,5,30,0,0,266,267,
  	5,18,0,0,267,268,3,46,23,0,268,269,5,19,0,0,269,272,3,44,22,0,270,271,
  	5,31,0,0,271,273,3,44,22,0,272,270,1,0,0,0,272,273,1,0,0,0,273,286,1,
  	0,0,0,274,275,5,32,0,0,275,276,5,18,0,0,276,277,3,46,23,0,277,278,5,19,
  	0,0,278,279,3,44,22,0,279,286,1,0,0,0,280,281,5,33,0,0,281,282,5,18,0,
  	0,282,283,5,47,0,0,283,284,5,19,0,0,284,286,3,44,22,0,285,244,1,0,0,0,
  	285,247,1,0,0,0,285,252,1,0,0,0,285,260,1,0,0,0,285,265,1,0,0,0,285,274,
  	1,0,0,0,285,280,1,0,0,0,286,45,1,0,0,0,287,288,6,23,-1,0,288,325,5,43,
  	0,0,289,325,5,44,0,0,290,325,5,45,0,0,291,325,5,46,0,0,292,325,5,42,0,
  	0,293,294,5,34,0,0,294,295,5,18,0,0,295,296,3,46,23,0,296,297,5,19,0,
  	0,297,325,1,0,0,0,298,299,5,34,0,0,299,300,5,18,0,0,300,301,3,16,8,0,
  	301,302,5,19,0,0,302,325,1,0,0,0,303,304,5,34,0,0,304,305,5,3,0,0,305,
  	306,5,18,0,0,306,307,5,47,0,0,307,325,5,19,0,0,308,325,3,18,9,0,309,310,
  	3,14,7,0,310,311,5,18,0,0,311,312,3,26,13,0,312,313,5,19,0,0,313,325,
  	1,0,0,0,314,325,5,47,0,0,315,316,5,18,0,0,316,317,3,16,8,0,317,318,5,
  	19,0,0,318,319,3,46,23,6,319,325,1,0,0,0,320,321,5,18,0,0,321,322,3,46,
  	23,0,322,323,5,19,0,0,323,325,1,0,0,0,324,287,1,0,0,0,324,289,1,0,0,0,
  	324,290,1,0,0,0,324,291,1,0,0,0,324,292,1,0,0,0,324,293,1,0,0,0,324,298,
  	1,0,0,0,324,303,1,0,0,0,324,308,1,0,0,0,324,309,1,0,0,0,324,314,1,0,0,
  	0,324,315,1,0,0,0,324,320,1,0,0,0,325,358,1,0,0,0,326,327,10,5,0,0,327,
  	328,7,1,0,0,328,357,3,46,23,6,329,330,10,4,0,0,330,331,7,2,0,0,331,357,
  	3,46,23,5,332,333,10,3,0,0,333,334,5,52,0,0,334,357,3,46,23,4,335,336,
  	10,2,0,0,336,337,7,3,0,0,337,357,3,46,23,3,338,339,10,10,0,0,339,340,
  	5,35,0,0,340,342,5,47,0,0,341,343,3,12,6,0,342,341,1,0,0,0,342,343,1,
  	0,0,0,343,344,1,0,0,0,344,345,5,18,0,0,345,346,3,26,13,0,346,347,5,19,
  	0,0,347,357,1,0,0,0,348,349,10,8,0,0,349,350,5,36,0,0,350,351,3,46,23,
  	0,351,352,5,37,0,0,352,357,1,0,0,0,353,354,10,7,0,0,354,355,5,35,0,0,
  	355,357,5,47,0,0,356,326,1,0,0,0,356,329,1,0,0,0,356,332,1,0,0,0,356,
  	335,1,0,0,0,356,338,1,0,0,0,356,348,1,0,0,0,356,353,1,0,0,0,357,360,1,
  	0,0,0,358,356,1,0,0,0,358,359,1,0,0,0,359,47,1,0,0,0,360,358,1,0,0,0,
  	39,51,56,64,72,83,91,99,106,110,113,116,127,134,137,142,149,152,155,158,
  	164,168,175,185,191,200,210,219,222,225,233,242,256,262,272,285,324,342,
  	356,358
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
    setState(56);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__3:
      case braneParser::T__8:
      case braneParser::T__9:
      case braneParser::T__10:
      case braneParser::T__11:
      case braneParser::T__22:
      case braneParser::T__24:
      case braneParser::T__25:
      case braneParser::T__26:
      case braneParser::ID: {
        setState(49); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(48);
          progSegment();
          setState(51); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 140737731632656) != 0));
        setState(53);
        match(braneParser::EOF);
        break;
      }

      case braneParser::EOF: {
        setState(55);
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
    setState(64);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(58);
      function();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(59);
      functionStub();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(60);
      structDef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(61);
      global();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(62);
      link();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(63);
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
    setState(66);
    type();
    setState(67);
    antlrcpp::downCast<GlobalContext *>(_localctx)->id = match(braneParser::ID);
    setState(68);
    match(braneParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateDefArgumentContext ------------------------------------------------------------------

braneParser::TemplateDefArgumentContext::TemplateDefArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* braneParser::TemplateDefArgumentContext::ID() {
  return getToken(braneParser::ID, 0);
}


size_t braneParser::TemplateDefArgumentContext::getRuleIndex() const {
  return braneParser::RuleTemplateDefArgument;
}


std::any braneParser::TemplateDefArgumentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitTemplateDefArgument(this);
  else
    return visitor->visitChildren(this);
}

braneParser::TemplateDefArgumentContext* braneParser::templateDefArgument() {
  TemplateDefArgumentContext *_localctx = _tracker.createInstance<TemplateDefArgumentContext>(_ctx, getState());
  enterRule(_localctx, 6, braneParser::RuleTemplateDefArgument);
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
    setState(70);
    match(braneParser::T__1);
    setState(72);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__2) {
      setState(71);
      antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->isPack = match(braneParser::T__2);
    }
    setState(74);
    antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->id = match(braneParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateDefContext ------------------------------------------------------------------

braneParser::TemplateDefContext::TemplateDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::TemplateDefArgumentContext *> braneParser::TemplateDefContext::templateDefArgument() {
  return getRuleContexts<braneParser::TemplateDefArgumentContext>();
}

braneParser::TemplateDefArgumentContext* braneParser::TemplateDefContext::templateDefArgument(size_t i) {
  return getRuleContext<braneParser::TemplateDefArgumentContext>(i);
}


size_t braneParser::TemplateDefContext::getRuleIndex() const {
  return braneParser::RuleTemplateDef;
}


std::any braneParser::TemplateDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitTemplateDef(this);
  else
    return visitor->visitChildren(this);
}

braneParser::TemplateDefContext* braneParser::templateDef() {
  TemplateDefContext *_localctx = _tracker.createInstance<TemplateDefContext>(_ctx, getState());
  enterRule(_localctx, 8, braneParser::RuleTemplateDef);
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
    setState(76);
    match(braneParser::T__3);
    setState(77);
    match(braneParser::T__4);
    setState(78);
    templateDefArgument();
    setState(83);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__5) {
      setState(79);
      match(braneParser::T__5);
      setState(80);
      templateDefArgument();
      setState(85);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(86);
    match(braneParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateArgContext ------------------------------------------------------------------

braneParser::TemplateArgContext::TemplateArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t braneParser::TemplateArgContext::getRuleIndex() const {
  return braneParser::RuleTemplateArg;
}

void braneParser::TemplateArgContext::copyFrom(TemplateArgContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TemplateTypeArgContext ------------------------------------------------------------------

braneParser::TypeContext* braneParser::TemplateTypeArgContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}

braneParser::TemplateTypeArgContext::TemplateTypeArgContext(TemplateArgContext *ctx) { copyFrom(ctx); }


std::any braneParser::TemplateTypeArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitTemplateTypeArg(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PackExpansionArgContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::PackExpansionArgContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::PackExpansionArgContext::PackExpansionArgContext(TemplateArgContext *ctx) { copyFrom(ctx); }


std::any braneParser::PackExpansionArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitPackExpansionArg(this);
  else
    return visitor->visitChildren(this);
}
braneParser::TemplateArgContext* braneParser::templateArg() {
  TemplateArgContext *_localctx = _tracker.createInstance<TemplateArgContext>(_ctx, getState());
  enterRule(_localctx, 10, braneParser::RuleTemplateArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(91);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::TemplateTypeArgContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(88);
      antlrcpp::downCast<TemplateTypeArgContext *>(_localctx)->t = type();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::PackExpansionArgContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(89);
      antlrcpp::downCast<PackExpansionArgContext *>(_localctx)->packID = match(braneParser::ID);
      setState(90);
      match(braneParser::T__2);
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

//----------------- TemplateArgsContext ------------------------------------------------------------------

braneParser::TemplateArgsContext::TemplateArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::TemplateArgContext *> braneParser::TemplateArgsContext::templateArg() {
  return getRuleContexts<braneParser::TemplateArgContext>();
}

braneParser::TemplateArgContext* braneParser::TemplateArgsContext::templateArg(size_t i) {
  return getRuleContext<braneParser::TemplateArgContext>(i);
}


size_t braneParser::TemplateArgsContext::getRuleIndex() const {
  return braneParser::RuleTemplateArgs;
}


std::any braneParser::TemplateArgsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitTemplateArgs(this);
  else
    return visitor->visitChildren(this);
}

braneParser::TemplateArgsContext* braneParser::templateArgs() {
  TemplateArgsContext *_localctx = _tracker.createInstance<TemplateArgsContext>(_ctx, getState());
  enterRule(_localctx, 12, braneParser::RuleTemplateArgs);
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
    setState(93);
    match(braneParser::T__4);
    setState(94);
    templateArg();
    setState(99);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__5) {
      setState(95);
      match(braneParser::T__5);
      setState(96);
      templateArg();
      setState(101);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(102);
    match(braneParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScopedIDContext ------------------------------------------------------------------

braneParser::ScopedIDContext::ScopedIDContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* braneParser::ScopedIDContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::TemplateArgsContext* braneParser::ScopedIDContext::templateArgs() {
  return getRuleContext<braneParser::TemplateArgsContext>(0);
}

braneParser::ScopedIDContext* braneParser::ScopedIDContext::scopedID() {
  return getRuleContext<braneParser::ScopedIDContext>(0);
}


size_t braneParser::ScopedIDContext::getRuleIndex() const {
  return braneParser::RuleScopedID;
}


std::any braneParser::ScopedIDContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitScopedID(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ScopedIDContext* braneParser::scopedID() {
  ScopedIDContext *_localctx = _tracker.createInstance<ScopedIDContext>(_ctx, getState());
  enterRule(_localctx, 14, braneParser::RuleScopedID);
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
    setState(104);
    antlrcpp::downCast<ScopedIDContext *>(_localctx)->id = match(braneParser::ID);
    setState(106);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__4) {
      setState(105);
      antlrcpp::downCast<ScopedIDContext *>(_localctx)->template_ = templateArgs();
    }
    setState(110);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__7) {
      setState(108);
      match(braneParser::T__7);
      setState(109);
      antlrcpp::downCast<ScopedIDContext *>(_localctx)->child = scopedID();
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

braneParser::ScopedIDContext* braneParser::TypeContext::scopedID() {
  return getRuleContext<braneParser::ScopedIDContext>(0);
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
  enterRule(_localctx, 16, braneParser::RuleType);
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
    setState(113);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__8) {
      setState(112);
      antlrcpp::downCast<TypeContext *>(_localctx)->isConst = match(braneParser::T__8);
    }
    setState(116);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__9) {
      setState(115);
      antlrcpp::downCast<TypeContext *>(_localctx)->isRef = match(braneParser::T__9);
    }
    setState(118);
    antlrcpp::downCast<TypeContext *>(_localctx)->name = scopedID();
   
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
  enterRule(_localctx, 18, braneParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(120);
    type();
    setState(121);
    antlrcpp::downCast<DeclarationContext *>(_localctx)->id = match(braneParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListItemContext ------------------------------------------------------------------

braneParser::ArgumentListItemContext::ArgumentListItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::DeclarationContext* braneParser::ArgumentListItemContext::declaration() {
  return getRuleContext<braneParser::DeclarationContext>(0);
}

std::vector<tree::TerminalNode *> braneParser::ArgumentListItemContext::ID() {
  return getTokens(braneParser::ID);
}

tree::TerminalNode* braneParser::ArgumentListItemContext::ID(size_t i) {
  return getToken(braneParser::ID, i);
}


size_t braneParser::ArgumentListItemContext::getRuleIndex() const {
  return braneParser::RuleArgumentListItem;
}


std::any braneParser::ArgumentListItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitArgumentListItem(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ArgumentListItemContext* braneParser::argumentListItem() {
  ArgumentListItemContext *_localctx = _tracker.createInstance<ArgumentListItemContext>(_ctx, getState());
  enterRule(_localctx, 20, braneParser::RuleArgumentListItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(127);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(123);
      declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(124);
      antlrcpp::downCast<ArgumentListItemContext *>(_localctx)->pack = match(braneParser::ID);
      setState(125);
      match(braneParser::T__2);
      setState(126);
      antlrcpp::downCast<ArgumentListItemContext *>(_localctx)->id = match(braneParser::ID);
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

//----------------- ArgumentListContext ------------------------------------------------------------------

braneParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::ArgumentListItemContext *> braneParser::ArgumentListContext::argumentListItem() {
  return getRuleContexts<braneParser::ArgumentListItemContext>();
}

braneParser::ArgumentListItemContext* braneParser::ArgumentListContext::argumentListItem(size_t i) {
  return getRuleContext<braneParser::ArgumentListItemContext>(i);
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
  enterRule(_localctx, 22, braneParser::RuleArgumentList);
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
    setState(137);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 140737488356864) != 0)) {
      setState(129);
      argumentListItem();
      setState(134);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__5) {
        setState(130);
        match(braneParser::T__5);
        setState(131);
        argumentListItem();
        setState(136);
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

//----------------- ArgumentPackItemContext ------------------------------------------------------------------

braneParser::ArgumentPackItemContext::ArgumentPackItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::ExpressionContext* braneParser::ArgumentPackItemContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

tree::TerminalNode* braneParser::ArgumentPackItemContext::ID() {
  return getToken(braneParser::ID, 0);
}


size_t braneParser::ArgumentPackItemContext::getRuleIndex() const {
  return braneParser::RuleArgumentPackItem;
}


std::any braneParser::ArgumentPackItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitArgumentPackItem(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ArgumentPackItemContext* braneParser::argumentPackItem() {
  ArgumentPackItemContext *_localctx = _tracker.createInstance<ArgumentPackItemContext>(_ctx, getState());
  enterRule(_localctx, 24, braneParser::RuleArgumentPackItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(142);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(139);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(140);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->packID = match(braneParser::ID);
      setState(141);
      match(braneParser::T__2);
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

//----------------- ArgumentPackContext ------------------------------------------------------------------

braneParser::ArgumentPackContext::ArgumentPackContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::ArgumentPackItemContext *> braneParser::ArgumentPackContext::argumentPackItem() {
  return getRuleContexts<braneParser::ArgumentPackItemContext>();
}

braneParser::ArgumentPackItemContext* braneParser::ArgumentPackContext::argumentPackItem(size_t i) {
  return getRuleContext<braneParser::ArgumentPackItemContext>(i);
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
  enterRule(_localctx, 26, braneParser::RuleArgumentPack);
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
    setState(152);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 277094110332416) != 0)) {
      setState(144);
      argumentPackItem();
      setState(149);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__5) {
        setState(145);
        match(braneParser::T__5);
        setState(146);
        argumentPackItem();
        setState(151);
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

//----------------- FunctionSigContext ------------------------------------------------------------------

braneParser::FunctionSigContext::FunctionSigContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::TemplateDefContext* braneParser::FunctionSigContext::templateDef() {
  return getRuleContext<braneParser::TemplateDefContext>(0);
}

braneParser::TypeContext* braneParser::FunctionSigContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}

tree::TerminalNode* braneParser::FunctionSigContext::ID() {
  return getToken(braneParser::ID, 0);
}

tree::TerminalNode* braneParser::FunctionSigContext::ADD() {
  return getToken(braneParser::ADD, 0);
}

tree::TerminalNode* braneParser::FunctionSigContext::SUB() {
  return getToken(braneParser::SUB, 0);
}

tree::TerminalNode* braneParser::FunctionSigContext::MUL() {
  return getToken(braneParser::MUL, 0);
}

tree::TerminalNode* braneParser::FunctionSigContext::DIV() {
  return getToken(braneParser::DIV, 0);
}

tree::TerminalNode* braneParser::FunctionSigContext::LOGIC() {
  return getToken(braneParser::LOGIC, 0);
}


size_t braneParser::FunctionSigContext::getRuleIndex() const {
  return braneParser::RuleFunctionSig;
}


std::any braneParser::FunctionSigContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitFunctionSig(this);
  else
    return visitor->visitChildren(this);
}

braneParser::FunctionSigContext* braneParser::functionSig() {
  FunctionSigContext *_localctx = _tracker.createInstance<FunctionSigContext>(_ctx, getState());
  enterRule(_localctx, 28, braneParser::RuleFunctionSig);
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
    setState(155);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(154);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->template_ = templateDef();
    }
    setState(158);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__10) {
      setState(157);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->isConstexpr = match(braneParser::T__10);
    }
    setState(168);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__8:
      case braneParser::T__9:
      case braneParser::ID: {
        setState(160);
        type();
        setState(164);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case braneParser::ID: {
            setState(161);
            antlrcpp::downCast<FunctionSigContext *>(_localctx)->id = match(braneParser::ID);
            break;
          }

          case braneParser::T__11: {
            setState(162);
            match(braneParser::T__11);
            setState(163);
            antlrcpp::downCast<FunctionSigContext *>(_localctx)->oprID = _input->LT(1);
            _la = _input->LA(1);
            if (!((((_la & ~ 0x3fULL) == 0) &&
              ((1ULL << _la) & 8725724278284448) != 0))) {
              antlrcpp::downCast<FunctionSigContext *>(_localctx)->oprID = _errHandler->recoverInline(this);
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
        break;
      }

      case braneParser::T__11: {
        setState(166);
        match(braneParser::T__11);
        setState(167);
        antlrcpp::downCast<FunctionSigContext *>(_localctx)->castType = type();
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

//----------------- FunctionStubContext ------------------------------------------------------------------

braneParser::FunctionStubContext::FunctionStubContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::FunctionSigContext* braneParser::FunctionStubContext::functionSig() {
  return getRuleContext<braneParser::FunctionSigContext>(0);
}

braneParser::ArgumentListContext* braneParser::FunctionStubContext::argumentList() {
  return getRuleContext<braneParser::ArgumentListContext>(0);
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
  enterRule(_localctx, 30, braneParser::RuleFunctionStub);
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
    setState(170);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->sig = functionSig();
    setState(171);
    match(braneParser::T__17);
    setState(172);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->arguments = argumentList();
    setState(173);
    match(braneParser::T__18);
    setState(175);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__8) {
      setState(174);
      antlrcpp::downCast<FunctionStubContext *>(_localctx)->isConst = match(braneParser::T__8);
    }
    setState(177);
    match(braneParser::T__19);
    setState(178);
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

braneParser::FunctionSigContext* braneParser::FunctionContext::functionSig() {
  return getRuleContext<braneParser::FunctionSigContext>(0);
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
  enterRule(_localctx, 32, braneParser::RuleFunction);
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
    setState(180);
    antlrcpp::downCast<FunctionContext *>(_localctx)->sig = functionSig();
    setState(181);
    match(braneParser::T__17);
    setState(182);
    antlrcpp::downCast<FunctionContext *>(_localctx)->arguments = argumentList();
    setState(183);
    match(braneParser::T__18);
    setState(185);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__8) {
      setState(184);
      antlrcpp::downCast<FunctionContext *>(_localctx)->isConst = match(braneParser::T__8);
    }
    setState(187);
    match(braneParser::T__20);
    setState(191);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 277108607944192) != 0)) {
      setState(188);
      antlrcpp::downCast<FunctionContext *>(_localctx)->statements = statement();
      setState(193);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(194);
    match(braneParser::T__21);
   
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
  enterRule(_localctx, 34, braneParser::RuleLink);
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
    setState(196);
    match(braneParser::T__22);
    setState(197);
    antlrcpp::downCast<LinkContext *>(_localctx)->library = match(braneParser::STRING);
    setState(200);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__23) {
      setState(198);
      match(braneParser::T__23);
      setState(199);
      antlrcpp::downCast<LinkContext *>(_localctx)->alias = match(braneParser::STRING);
    }
    setState(202);
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
  enterRule(_localctx, 36, braneParser::RuleExport);
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
    setState(204);
    match(braneParser::T__24);
    setState(205);
    antlrcpp::downCast<ExportContext *>(_localctx)->libID = match(braneParser::STRING);
    setState(206);
    match(braneParser::T__20);
    setState(210);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 140737689689616) != 0)) {
      setState(207);
      exportSegment();
      setState(212);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(213);
    match(braneParser::T__21);
   
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
  enterRule(_localctx, 38, braneParser::RuleExportSegment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(219);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(215);
      function();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(216);
      functionStub();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(217);
      structDef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(218);
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

//----------------- StructDefContext ------------------------------------------------------------------

braneParser::StructDefContext::StructDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* braneParser::StructDefContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::TemplateDefContext* braneParser::StructDefContext::templateDef() {
  return getRuleContext<braneParser::TemplateDefContext>(0);
}

std::vector<braneParser::StructMemberContext *> braneParser::StructDefContext::structMember() {
  return getRuleContexts<braneParser::StructMemberContext>();
}

braneParser::StructMemberContext* braneParser::StructDefContext::structMember(size_t i) {
  return getRuleContext<braneParser::StructMemberContext>(i);
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
  enterRule(_localctx, 40, braneParser::RuleStructDef);
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
    setState(222);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(221);
      antlrcpp::downCast<StructDefContext *>(_localctx)->template_ = templateDef();
    }
    setState(225);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__25) {
      setState(224);
      antlrcpp::downCast<StructDefContext *>(_localctx)->packed = match(braneParser::T__25);
    }
    setState(227);
    match(braneParser::T__26);
    setState(228);
    antlrcpp::downCast<StructDefContext *>(_localctx)->id = match(braneParser::ID);
    setState(229);
    match(braneParser::T__20);
    setState(233);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 140737488363024) != 0)) {
      setState(230);
      antlrcpp::downCast<StructDefContext *>(_localctx)->memberVars = structMember();
      setState(235);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(236);
    match(braneParser::T__21);
   
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


size_t braneParser::StructMemberContext::getRuleIndex() const {
  return braneParser::RuleStructMember;
}

void braneParser::StructMemberContext::copyFrom(StructMemberContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MemberVariableContext ------------------------------------------------------------------

braneParser::DeclarationContext* braneParser::MemberVariableContext::declaration() {
  return getRuleContext<braneParser::DeclarationContext>(0);
}

braneParser::MemberVariableContext::MemberVariableContext(StructMemberContext *ctx) { copyFrom(ctx); }


std::any braneParser::MemberVariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitMemberVariable(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemberFunctionContext ------------------------------------------------------------------

braneParser::FunctionContext* braneParser::MemberFunctionContext::function() {
  return getRuleContext<braneParser::FunctionContext>(0);
}

braneParser::MemberFunctionContext::MemberFunctionContext(StructMemberContext *ctx) { copyFrom(ctx); }


std::any braneParser::MemberFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitMemberFunction(this);
  else
    return visitor->visitChildren(this);
}
braneParser::StructMemberContext* braneParser::structMember() {
  StructMemberContext *_localctx = _tracker.createInstance<StructMemberContext>(_ctx, getState());
  enterRule(_localctx, 42, braneParser::RuleStructMember);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(242);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::MemberVariableContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(238);
      antlrcpp::downCast<MemberVariableContext *>(_localctx)->var = declaration();
      setState(239);
      match(braneParser::T__0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::MemberFunctionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(241);
      antlrcpp::downCast<MemberFunctionContext *>(_localctx)->func = function();
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
//----------------- UnrollContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::UnrollContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::StatementContext* braneParser::UnrollContext::statement() {
  return getRuleContext<braneParser::StatementContext>(0);
}

braneParser::UnrollContext::UnrollContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::UnrollContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitUnroll(this);
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
  enterRule(_localctx, 44, braneParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(285);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::ExprStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(244);
      expression(0);
      setState(245);
      match(braneParser::T__0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::AssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(247);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->lValue = expression(0);
      setState(248);
      match(braneParser::T__27);
      setState(249);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->rValue = expression(0);
      setState(250);
      match(braneParser::T__0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::ScopeContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(252);
      match(braneParser::T__20);
      setState(256);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 277108607944192) != 0)) {
        setState(253);
        statement();
        setState(258);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(259);
      match(braneParser::T__21);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<braneParser::ReturnContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(260);
      match(braneParser::T__28);
      setState(262);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 277094110332416) != 0)) {
        setState(261);
        expression(0);
      }
      setState(264);
      match(braneParser::T__0);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<braneParser::IfContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(265);
      match(braneParser::T__29);
      setState(266);
      match(braneParser::T__17);
      setState(267);
      antlrcpp::downCast<IfContext *>(_localctx)->cond = expression(0);
      setState(268);
      match(braneParser::T__18);
      setState(269);
      antlrcpp::downCast<IfContext *>(_localctx)->operation = statement();
      setState(272);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
      case 1: {
        setState(270);
        match(braneParser::T__30);
        setState(271);
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
      setState(274);
      match(braneParser::T__31);
      setState(275);
      match(braneParser::T__17);
      setState(276);
      antlrcpp::downCast<WhileContext *>(_localctx)->cond = expression(0);
      setState(277);
      match(braneParser::T__18);
      setState(278);
      antlrcpp::downCast<WhileContext *>(_localctx)->operation = statement();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<braneParser::UnrollContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(280);
      match(braneParser::T__32);
      setState(281);
      match(braneParser::T__17);
      setState(282);
      antlrcpp::downCast<UnrollContext *>(_localctx)->id = match(braneParser::ID);
      setState(283);
      match(braneParser::T__18);
      setState(284);
      antlrcpp::downCast<UnrollContext *>(_localctx)->body = statement();
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
//----------------- SizeOfExprContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::SizeOfExprContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::SizeOfExprContext::SizeOfExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::SizeOfExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitSizeOfExpr(this);
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

braneParser::TypeContext* braneParser::CastContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
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

braneParser::TemplateArgsContext* braneParser::MemberFunctionCallContext::templateArgs() {
  return getRuleContext<braneParser::TemplateArgsContext>(0);
}

braneParser::MemberFunctionCallContext::MemberFunctionCallContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::MemberFunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitMemberFunctionCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SizeOfPackContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::SizeOfPackContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::SizeOfPackContext::SizeOfPackContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::SizeOfPackContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitSizeOfPack(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionCallContext ------------------------------------------------------------------

braneParser::ArgumentPackContext* braneParser::FunctionCallContext::argumentPack() {
  return getRuleContext<braneParser::ArgumentPackContext>(0);
}

braneParser::ScopedIDContext* braneParser::FunctionCallContext::scopedID() {
  return getRuleContext<braneParser::ScopedIDContext>(0);
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
//----------------- SizeOfTypeContext ------------------------------------------------------------------

braneParser::TypeContext* braneParser::SizeOfTypeContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}

braneParser::SizeOfTypeContext::SizeOfTypeContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::SizeOfTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitSizeOfType(this);
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
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, braneParser::RuleExpression, precedence);

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
    setState(324);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ConstIntContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(288);
      match(braneParser::INT);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ConstFloatContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(289);
      match(braneParser::FLOAT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ConstCharContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(290);
      match(braneParser::CHAR);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ConstStringContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(291);
      match(braneParser::STRING);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ConstBoolContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(292);
      match(braneParser::BOOL);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SizeOfExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(293);
      match(braneParser::T__33);
      setState(294);
      match(braneParser::T__17);
      setState(295);
      antlrcpp::downCast<SizeOfExprContext *>(_localctx)->expr = expression(0);
      setState(296);
      match(braneParser::T__18);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SizeOfTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(298);
      match(braneParser::T__33);
      setState(299);
      match(braneParser::T__17);
      setState(300);
      antlrcpp::downCast<SizeOfTypeContext *>(_localctx)->t = type();
      setState(301);
      match(braneParser::T__18);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<SizeOfPackContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(303);
      match(braneParser::T__33);
      setState(304);
      match(braneParser::T__2);
      setState(305);
      match(braneParser::T__17);
      setState(306);
      antlrcpp::downCast<SizeOfPackContext *>(_localctx)->id = match(braneParser::ID);
      setState(307);
      match(braneParser::T__18);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<DeclContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(308);
      declaration();
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<FunctionCallContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(309);
      antlrcpp::downCast<FunctionCallContext *>(_localctx)->id = scopedID();
      setState(310);
      match(braneParser::T__17);
      setState(311);
      argumentPack();
      setState(312);
      match(braneParser::T__18);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<IdContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(314);
      match(braneParser::ID);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<CastContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(315);
      match(braneParser::T__17);
      setState(316);
      type();
      setState(317);
      match(braneParser::T__18);
      setState(318);
      expression(6);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<ParenContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(320);
      match(braneParser::T__17);
      setState(321);
      expression(0);
      setState(322);
      match(braneParser::T__18);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(358);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(356);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MuldivContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(326);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(327);
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
          setState(328);
          antlrcpp::downCast<MuldivContext *>(_localctx)->right = expression(6);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddsubContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(329);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(330);
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
          setState(331);
          antlrcpp::downCast<AddsubContext *>(_localctx)->right = expression(5);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<LogicContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(332);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(333);
          antlrcpp::downCast<LogicContext *>(_localctx)->opr = match(braneParser::LOGIC);
          setState(334);
          antlrcpp::downCast<LogicContext *>(_localctx)->right = expression(4);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<ComparisonContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(335);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(336);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->opr = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 123040) != 0))) {
            antlrcpp::downCast<ComparisonContext *>(_localctx)->opr = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(337);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->right = expression(3);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<MemberFunctionCallContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(338);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(339);
          match(braneParser::T__34);
          setState(340);
          antlrcpp::downCast<MemberFunctionCallContext *>(_localctx)->name = match(braneParser::ID);
          setState(342);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == braneParser::T__4) {
            setState(341);
            antlrcpp::downCast<MemberFunctionCallContext *>(_localctx)->template_ = templateArgs();
          }
          setState(344);
          match(braneParser::T__17);
          setState(345);
          argumentPack();
          setState(346);
          match(braneParser::T__18);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<IndexAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(348);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(349);
          match(braneParser::T__35);
          setState(350);
          antlrcpp::downCast<IndexAccessContext *>(_localctx)->arg = expression(0);
          setState(351);
          match(braneParser::T__36);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(353);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(354);
          match(braneParser::T__34);
          setState(355);
          antlrcpp::downCast<MemberAccessContext *>(_localctx)->member = match(braneParser::ID);
          break;
        }

        default:
          break;
        } 
      }
      setState(360);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
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
    case 23: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

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

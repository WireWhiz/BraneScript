
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
      "", "';'", "'type'", "'expr'", "'...'", "'template'", "'<'", "','", 
      "'>'", "'::'", "'const'", "'ref'", "'constexpr'", "'opr'", "'=='", 
      "'!='", "'<='", "'>='", "'[]'", "'('", "')'", "'ext'", "'{'", "'}'", 
      "'link'", "'as'", "'export as'", "'packed'", "'struct'", "'='", "'return'", 
      "'if'", "'else'", "'while'", "'unroll'", "'sizeof'", "'.'", "'['", 
      "']'", "", "", "", "", "", "", "", "", "", "", "'*'", "'/'", "'+'", 
      "'-'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "NEWLINE", "COMMENT", "BLOCK_COMMENT", "SPACE", 
      "BOOL", "INT", "FLOAT", "CHAR", "STRING", "ID", "MUL", "DIV", "ADD", 
      "SUB", "LOGIC"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,53,363,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,1,0,4,0,50,8,0,11,0,12,0,51,1,0,1,0,1,0,3,0,57,
  	8,0,1,1,1,1,1,1,1,1,1,1,1,1,3,1,65,8,1,1,2,1,2,1,2,1,2,1,3,1,3,3,3,73,
  	8,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,5,4,82,8,4,10,4,12,4,85,9,4,1,4,1,4,1,
  	5,1,5,1,5,1,5,3,5,93,8,5,1,6,1,6,1,6,1,6,5,6,99,8,6,10,6,12,6,102,9,6,
  	1,6,1,6,1,7,1,7,3,7,108,8,7,1,7,1,7,3,7,112,8,7,1,8,3,8,115,8,8,1,8,3,
  	8,118,8,8,1,8,1,8,1,9,1,9,1,9,1,10,1,10,1,10,1,10,3,10,129,8,10,1,11,
  	1,11,1,11,5,11,134,8,11,10,11,12,11,137,9,11,3,11,139,8,11,1,12,1,12,
  	1,12,3,12,144,8,12,1,13,1,13,1,13,5,13,149,8,13,10,13,12,13,152,9,13,
  	3,13,154,8,13,1,14,3,14,157,8,14,1,14,3,14,160,8,14,1,14,1,14,1,14,1,
  	14,3,14,166,8,14,1,14,1,14,3,14,170,8,14,1,15,1,15,1,15,1,15,1,15,3,15,
  	177,8,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,3,16,187,8,16,1,16,1,
  	16,5,16,191,8,16,10,16,12,16,194,9,16,1,16,1,16,1,17,1,17,1,17,1,17,3,
  	17,202,8,17,1,17,1,17,1,18,1,18,1,18,1,18,5,18,210,8,18,10,18,12,18,213,
  	9,18,1,18,1,18,1,19,1,19,1,19,1,19,3,19,221,8,19,1,20,3,20,224,8,20,1,
  	20,3,20,227,8,20,1,20,1,20,1,20,1,20,5,20,233,8,20,10,20,12,20,236,9,
  	20,1,20,1,20,1,21,1,21,1,21,1,21,3,21,244,8,21,1,22,1,22,1,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,5,22,256,8,22,10,22,12,22,259,9,22,1,22,1,
  	22,1,22,3,22,264,8,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,274,
  	8,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,287,
  	8,22,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,3,23,326,8,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	1,23,3,23,344,8,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	1,23,1,23,5,23,358,8,23,10,23,12,23,361,9,23,1,23,0,1,46,24,0,2,4,6,8,
  	10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,0,5,1,0,2,3,
  	4,0,6,6,8,8,14,18,49,53,1,0,49,50,1,0,51,52,3,0,6,6,8,8,14,17,405,0,56,
  	1,0,0,0,2,64,1,0,0,0,4,66,1,0,0,0,6,70,1,0,0,0,8,76,1,0,0,0,10,92,1,0,
  	0,0,12,94,1,0,0,0,14,105,1,0,0,0,16,114,1,0,0,0,18,121,1,0,0,0,20,128,
  	1,0,0,0,22,138,1,0,0,0,24,143,1,0,0,0,26,153,1,0,0,0,28,156,1,0,0,0,30,
  	171,1,0,0,0,32,181,1,0,0,0,34,197,1,0,0,0,36,205,1,0,0,0,38,220,1,0,0,
  	0,40,223,1,0,0,0,42,243,1,0,0,0,44,286,1,0,0,0,46,325,1,0,0,0,48,50,3,
  	2,1,0,49,48,1,0,0,0,50,51,1,0,0,0,51,49,1,0,0,0,51,52,1,0,0,0,52,53,1,
  	0,0,0,53,54,5,0,0,1,54,57,1,0,0,0,55,57,5,0,0,1,56,49,1,0,0,0,56,55,1,
  	0,0,0,57,1,1,0,0,0,58,65,3,32,16,0,59,65,3,30,15,0,60,65,3,40,20,0,61,
  	65,3,4,2,0,62,65,3,34,17,0,63,65,3,36,18,0,64,58,1,0,0,0,64,59,1,0,0,
  	0,64,60,1,0,0,0,64,61,1,0,0,0,64,62,1,0,0,0,64,63,1,0,0,0,65,3,1,0,0,
  	0,66,67,3,16,8,0,67,68,5,48,0,0,68,69,5,1,0,0,69,5,1,0,0,0,70,72,7,0,
  	0,0,71,73,5,4,0,0,72,71,1,0,0,0,72,73,1,0,0,0,73,74,1,0,0,0,74,75,5,48,
  	0,0,75,7,1,0,0,0,76,77,5,5,0,0,77,78,5,6,0,0,78,83,3,6,3,0,79,80,5,7,
  	0,0,80,82,3,6,3,0,81,79,1,0,0,0,82,85,1,0,0,0,83,81,1,0,0,0,83,84,1,0,
  	0,0,84,86,1,0,0,0,85,83,1,0,0,0,86,87,5,8,0,0,87,9,1,0,0,0,88,93,3,16,
  	8,0,89,93,3,46,23,0,90,91,5,48,0,0,91,93,5,4,0,0,92,88,1,0,0,0,92,89,
  	1,0,0,0,92,90,1,0,0,0,93,11,1,0,0,0,94,95,5,6,0,0,95,100,3,10,5,0,96,
  	97,5,7,0,0,97,99,3,10,5,0,98,96,1,0,0,0,99,102,1,0,0,0,100,98,1,0,0,0,
  	100,101,1,0,0,0,101,103,1,0,0,0,102,100,1,0,0,0,103,104,5,8,0,0,104,13,
  	1,0,0,0,105,107,5,48,0,0,106,108,3,12,6,0,107,106,1,0,0,0,107,108,1,0,
  	0,0,108,111,1,0,0,0,109,110,5,9,0,0,110,112,3,14,7,0,111,109,1,0,0,0,
  	111,112,1,0,0,0,112,15,1,0,0,0,113,115,5,10,0,0,114,113,1,0,0,0,114,115,
  	1,0,0,0,115,117,1,0,0,0,116,118,5,11,0,0,117,116,1,0,0,0,117,118,1,0,
  	0,0,118,119,1,0,0,0,119,120,3,14,7,0,120,17,1,0,0,0,121,122,3,16,8,0,
  	122,123,5,48,0,0,123,19,1,0,0,0,124,129,3,18,9,0,125,126,5,48,0,0,126,
  	127,5,4,0,0,127,129,5,48,0,0,128,124,1,0,0,0,128,125,1,0,0,0,129,21,1,
  	0,0,0,130,135,3,20,10,0,131,132,5,7,0,0,132,134,3,20,10,0,133,131,1,0,
  	0,0,134,137,1,0,0,0,135,133,1,0,0,0,135,136,1,0,0,0,136,139,1,0,0,0,137,
  	135,1,0,0,0,138,130,1,0,0,0,138,139,1,0,0,0,139,23,1,0,0,0,140,144,3,
  	46,23,0,141,142,5,48,0,0,142,144,5,4,0,0,143,140,1,0,0,0,143,141,1,0,
  	0,0,144,25,1,0,0,0,145,150,3,24,12,0,146,147,5,7,0,0,147,149,3,24,12,
  	0,148,146,1,0,0,0,149,152,1,0,0,0,150,148,1,0,0,0,150,151,1,0,0,0,151,
  	154,1,0,0,0,152,150,1,0,0,0,153,145,1,0,0,0,153,154,1,0,0,0,154,27,1,
  	0,0,0,155,157,3,8,4,0,156,155,1,0,0,0,156,157,1,0,0,0,157,159,1,0,0,0,
  	158,160,5,12,0,0,159,158,1,0,0,0,159,160,1,0,0,0,160,169,1,0,0,0,161,
  	165,3,16,8,0,162,166,5,48,0,0,163,164,5,13,0,0,164,166,7,1,0,0,165,162,
  	1,0,0,0,165,163,1,0,0,0,166,170,1,0,0,0,167,168,5,13,0,0,168,170,3,16,
  	8,0,169,161,1,0,0,0,169,167,1,0,0,0,170,29,1,0,0,0,171,172,3,28,14,0,
  	172,173,5,19,0,0,173,174,3,22,11,0,174,176,5,20,0,0,175,177,5,10,0,0,
  	176,175,1,0,0,0,176,177,1,0,0,0,177,178,1,0,0,0,178,179,5,21,0,0,179,
  	180,5,1,0,0,180,31,1,0,0,0,181,182,3,28,14,0,182,183,5,19,0,0,183,184,
  	3,22,11,0,184,186,5,20,0,0,185,187,5,10,0,0,186,185,1,0,0,0,186,187,1,
  	0,0,0,187,188,1,0,0,0,188,192,5,22,0,0,189,191,3,44,22,0,190,189,1,0,
  	0,0,191,194,1,0,0,0,192,190,1,0,0,0,192,193,1,0,0,0,193,195,1,0,0,0,194,
  	192,1,0,0,0,195,196,5,23,0,0,196,33,1,0,0,0,197,198,5,24,0,0,198,201,
  	5,47,0,0,199,200,5,25,0,0,200,202,5,47,0,0,201,199,1,0,0,0,201,202,1,
  	0,0,0,202,203,1,0,0,0,203,204,5,1,0,0,204,35,1,0,0,0,205,206,5,26,0,0,
  	206,207,5,47,0,0,207,211,5,22,0,0,208,210,3,38,19,0,209,208,1,0,0,0,210,
  	213,1,0,0,0,211,209,1,0,0,0,211,212,1,0,0,0,212,214,1,0,0,0,213,211,1,
  	0,0,0,214,215,5,23,0,0,215,37,1,0,0,0,216,221,3,32,16,0,217,221,3,30,
  	15,0,218,221,3,40,20,0,219,221,3,4,2,0,220,216,1,0,0,0,220,217,1,0,0,
  	0,220,218,1,0,0,0,220,219,1,0,0,0,221,39,1,0,0,0,222,224,3,8,4,0,223,
  	222,1,0,0,0,223,224,1,0,0,0,224,226,1,0,0,0,225,227,5,27,0,0,226,225,
  	1,0,0,0,226,227,1,0,0,0,227,228,1,0,0,0,228,229,5,28,0,0,229,230,5,48,
  	0,0,230,234,5,22,0,0,231,233,3,42,21,0,232,231,1,0,0,0,233,236,1,0,0,
  	0,234,232,1,0,0,0,234,235,1,0,0,0,235,237,1,0,0,0,236,234,1,0,0,0,237,
  	238,5,23,0,0,238,41,1,0,0,0,239,240,3,18,9,0,240,241,5,1,0,0,241,244,
  	1,0,0,0,242,244,3,32,16,0,243,239,1,0,0,0,243,242,1,0,0,0,244,43,1,0,
  	0,0,245,246,3,46,23,0,246,247,5,1,0,0,247,287,1,0,0,0,248,249,3,46,23,
  	0,249,250,5,29,0,0,250,251,3,46,23,0,251,252,5,1,0,0,252,287,1,0,0,0,
  	253,257,5,22,0,0,254,256,3,44,22,0,255,254,1,0,0,0,256,259,1,0,0,0,257,
  	255,1,0,0,0,257,258,1,0,0,0,258,260,1,0,0,0,259,257,1,0,0,0,260,287,5,
  	23,0,0,261,263,5,30,0,0,262,264,3,46,23,0,263,262,1,0,0,0,263,264,1,0,
  	0,0,264,265,1,0,0,0,265,287,5,1,0,0,266,267,5,31,0,0,267,268,5,19,0,0,
  	268,269,3,46,23,0,269,270,5,20,0,0,270,273,3,44,22,0,271,272,5,32,0,0,
  	272,274,3,44,22,0,273,271,1,0,0,0,273,274,1,0,0,0,274,287,1,0,0,0,275,
  	276,5,33,0,0,276,277,5,19,0,0,277,278,3,46,23,0,278,279,5,20,0,0,279,
  	280,3,44,22,0,280,287,1,0,0,0,281,282,5,34,0,0,282,283,5,19,0,0,283,284,
  	5,48,0,0,284,285,5,20,0,0,285,287,3,44,22,0,286,245,1,0,0,0,286,248,1,
  	0,0,0,286,253,1,0,0,0,286,261,1,0,0,0,286,266,1,0,0,0,286,275,1,0,0,0,
  	286,281,1,0,0,0,287,45,1,0,0,0,288,289,6,23,-1,0,289,326,5,44,0,0,290,
  	326,5,45,0,0,291,326,5,46,0,0,292,326,5,47,0,0,293,326,5,43,0,0,294,295,
  	5,35,0,0,295,296,5,19,0,0,296,297,3,46,23,0,297,298,5,20,0,0,298,326,
  	1,0,0,0,299,300,5,35,0,0,300,301,5,19,0,0,301,302,3,16,8,0,302,303,5,
  	20,0,0,303,326,1,0,0,0,304,305,5,35,0,0,305,306,5,4,0,0,306,307,5,19,
  	0,0,307,308,5,48,0,0,308,326,5,20,0,0,309,326,3,18,9,0,310,311,3,14,7,
  	0,311,312,5,19,0,0,312,313,3,26,13,0,313,314,5,20,0,0,314,326,1,0,0,0,
  	315,326,5,48,0,0,316,317,5,19,0,0,317,318,3,16,8,0,318,319,5,20,0,0,319,
  	320,3,46,23,6,320,326,1,0,0,0,321,322,5,19,0,0,322,323,3,46,23,0,323,
  	324,5,20,0,0,324,326,1,0,0,0,325,288,1,0,0,0,325,290,1,0,0,0,325,291,
  	1,0,0,0,325,292,1,0,0,0,325,293,1,0,0,0,325,294,1,0,0,0,325,299,1,0,0,
  	0,325,304,1,0,0,0,325,309,1,0,0,0,325,310,1,0,0,0,325,315,1,0,0,0,325,
  	316,1,0,0,0,325,321,1,0,0,0,326,359,1,0,0,0,327,328,10,5,0,0,328,329,
  	7,2,0,0,329,358,3,46,23,6,330,331,10,4,0,0,331,332,7,3,0,0,332,358,3,
  	46,23,5,333,334,10,3,0,0,334,335,5,53,0,0,335,358,3,46,23,4,336,337,10,
  	2,0,0,337,338,7,4,0,0,338,358,3,46,23,3,339,340,10,10,0,0,340,341,5,36,
  	0,0,341,343,5,48,0,0,342,344,3,12,6,0,343,342,1,0,0,0,343,344,1,0,0,0,
  	344,345,1,0,0,0,345,346,5,19,0,0,346,347,3,26,13,0,347,348,5,20,0,0,348,
  	358,1,0,0,0,349,350,10,8,0,0,350,351,5,37,0,0,351,352,3,46,23,0,352,353,
  	5,38,0,0,353,358,1,0,0,0,354,355,10,7,0,0,355,356,5,36,0,0,356,358,5,
  	48,0,0,357,327,1,0,0,0,357,330,1,0,0,0,357,333,1,0,0,0,357,336,1,0,0,
  	0,357,339,1,0,0,0,357,349,1,0,0,0,357,354,1,0,0,0,358,361,1,0,0,0,359,
  	357,1,0,0,0,359,360,1,0,0,0,360,47,1,0,0,0,361,359,1,0,0,0,39,51,56,64,
  	72,83,92,100,107,111,114,117,128,135,138,143,150,153,156,159,165,169,
  	176,186,192,201,211,220,223,226,234,243,257,263,273,286,325,343,357,359
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
      case braneParser::T__4:
      case braneParser::T__9:
      case braneParser::T__10:
      case braneParser::T__11:
      case braneParser::T__12:
      case braneParser::T__23:
      case braneParser::T__25:
      case braneParser::T__26:
      case braneParser::T__27:
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
          ((1ULL << _la) & 281475463265312) != 0));
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
    antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->input = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == braneParser::T__1

    || _la == braneParser::T__2)) {
      antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->input = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(72);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(71);
      antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->isPack = match(braneParser::T__3);
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
    match(braneParser::T__4);
    setState(77);
    match(braneParser::T__5);
    setState(78);
    templateDefArgument();
    setState(83);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__6) {
      setState(79);
      match(braneParser::T__6);
      setState(80);
      templateDefArgument();
      setState(85);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(86);
    match(braneParser::T__7);
   
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
//----------------- TemplateExprArgContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::TemplateExprArgContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::TemplateExprArgContext::TemplateExprArgContext(TemplateArgContext *ctx) { copyFrom(ctx); }


std::any braneParser::TemplateExprArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitTemplateExprArg(this);
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
    setState(92);
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
      _localctx = _tracker.createInstance<braneParser::TemplateExprArgContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(89);
      antlrcpp::downCast<TemplateExprArgContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::PackExpansionArgContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(90);
      antlrcpp::downCast<PackExpansionArgContext *>(_localctx)->packID = match(braneParser::ID);
      setState(91);
      match(braneParser::T__3);
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
    setState(94);
    match(braneParser::T__5);
    setState(95);
    templateArg();
    setState(100);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__6) {
      setState(96);
      match(braneParser::T__6);
      setState(97);
      templateArg();
      setState(102);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(103);
    match(braneParser::T__7);
   
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
    setState(105);
    antlrcpp::downCast<ScopedIDContext *>(_localctx)->id = match(braneParser::ID);
    setState(107);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__5) {
      setState(106);
      antlrcpp::downCast<ScopedIDContext *>(_localctx)->template_ = templateArgs();
    }
    setState(111);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__8) {
      setState(109);
      match(braneParser::T__8);
      setState(110);
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
    setState(114);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__9) {
      setState(113);
      antlrcpp::downCast<TypeContext *>(_localctx)->isConst = match(braneParser::T__9);
    }
    setState(117);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__10) {
      setState(116);
      antlrcpp::downCast<TypeContext *>(_localctx)->isRef = match(braneParser::T__10);
    }
    setState(119);
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
    setState(121);
    type();
    setState(122);
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
    setState(128);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(124);
      declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(125);
      antlrcpp::downCast<ArgumentListItemContext *>(_localctx)->pack = match(braneParser::ID);
      setState(126);
      match(braneParser::T__3);
      setState(127);
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
    setState(138);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281474976713728) != 0)) {
      setState(130);
      argumentListItem();
      setState(135);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__6) {
        setState(131);
        match(braneParser::T__6);
        setState(132);
        argumentListItem();
        setState(137);
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
    setState(143);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(140);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(141);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->packID = match(braneParser::ID);
      setState(142);
      match(braneParser::T__3);
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
    setState(153);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 554188220664832) != 0)) {
      setState(145);
      argumentPackItem();
      setState(150);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__6) {
        setState(146);
        match(braneParser::T__6);
        setState(147);
        argumentPackItem();
        setState(152);
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
    setState(156);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__4) {
      setState(155);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->template_ = templateDef();
    }
    setState(159);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__11) {
      setState(158);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->isConstexpr = match(braneParser::T__11);
    }
    setState(169);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__9:
      case braneParser::T__10:
      case braneParser::ID: {
        setState(161);
        type();
        setState(165);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case braneParser::ID: {
            setState(162);
            antlrcpp::downCast<FunctionSigContext *>(_localctx)->id = match(braneParser::ID);
            break;
          }

          case braneParser::T__12: {
            setState(163);
            match(braneParser::T__12);
            setState(164);
            antlrcpp::downCast<FunctionSigContext *>(_localctx)->oprID = _input->LT(1);
            _la = _input->LA(1);
            if (!((((_la & ~ 0x3fULL) == 0) &&
              ((1ULL << _la) & 17451448556568896) != 0))) {
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

      case braneParser::T__12: {
        setState(167);
        match(braneParser::T__12);
        setState(168);
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
    setState(171);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->sig = functionSig();
    setState(172);
    match(braneParser::T__18);
    setState(173);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->arguments = argumentList();
    setState(174);
    match(braneParser::T__19);
    setState(176);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__9) {
      setState(175);
      antlrcpp::downCast<FunctionStubContext *>(_localctx)->isConst = match(braneParser::T__9);
    }
    setState(178);
    match(braneParser::T__20);
    setState(179);
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
    setState(181);
    antlrcpp::downCast<FunctionContext *>(_localctx)->sig = functionSig();
    setState(182);
    match(braneParser::T__18);
    setState(183);
    antlrcpp::downCast<FunctionContext *>(_localctx)->arguments = argumentList();
    setState(184);
    match(braneParser::T__19);
    setState(186);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__9) {
      setState(185);
      antlrcpp::downCast<FunctionContext *>(_localctx)->isConst = match(braneParser::T__9);
    }
    setState(188);
    match(braneParser::T__21);
    setState(192);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 554217215888384) != 0)) {
      setState(189);
      antlrcpp::downCast<FunctionContext *>(_localctx)->statements = statement();
      setState(194);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(195);
    match(braneParser::T__22);
   
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
    setState(197);
    match(braneParser::T__23);
    setState(198);
    antlrcpp::downCast<LinkContext *>(_localctx)->library = match(braneParser::STRING);
    setState(201);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__24) {
      setState(199);
      match(braneParser::T__24);
      setState(200);
      antlrcpp::downCast<LinkContext *>(_localctx)->alias = match(braneParser::STRING);
    }
    setState(203);
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
    setState(205);
    match(braneParser::T__25);
    setState(206);
    antlrcpp::downCast<ExportContext *>(_localctx)->libID = match(braneParser::STRING);
    setState(207);
    match(braneParser::T__21);
    setState(211);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281475379379232) != 0)) {
      setState(208);
      exportSegment();
      setState(213);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(214);
    match(braneParser::T__22);
   
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
    setState(220);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(216);
      function();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(217);
      functionStub();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(218);
      structDef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(219);
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
    setState(223);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__4) {
      setState(222);
      antlrcpp::downCast<StructDefContext *>(_localctx)->template_ = templateDef();
    }
    setState(226);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__26) {
      setState(225);
      antlrcpp::downCast<StructDefContext *>(_localctx)->packed = match(braneParser::T__26);
    }
    setState(228);
    match(braneParser::T__27);
    setState(229);
    antlrcpp::downCast<StructDefContext *>(_localctx)->id = match(braneParser::ID);
    setState(230);
    match(braneParser::T__21);
    setState(234);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281474976726048) != 0)) {
      setState(231);
      antlrcpp::downCast<StructDefContext *>(_localctx)->memberVars = structMember();
      setState(236);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(237);
    match(braneParser::T__22);
   
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
    setState(243);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::MemberVariableContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(239);
      antlrcpp::downCast<MemberVariableContext *>(_localctx)->var = declaration();
      setState(240);
      match(braneParser::T__0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::MemberFunctionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(242);
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
    setState(286);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::ExprStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(245);
      expression(0);
      setState(246);
      match(braneParser::T__0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::AssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(248);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->lValue = expression(0);
      setState(249);
      match(braneParser::T__28);
      setState(250);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->rValue = expression(0);
      setState(251);
      match(braneParser::T__0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::ScopeContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(253);
      match(braneParser::T__21);
      setState(257);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 554217215888384) != 0)) {
        setState(254);
        statement();
        setState(259);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(260);
      match(braneParser::T__22);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<braneParser::ReturnContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(261);
      match(braneParser::T__29);
      setState(263);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 554188220664832) != 0)) {
        setState(262);
        expression(0);
      }
      setState(265);
      match(braneParser::T__0);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<braneParser::IfContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(266);
      match(braneParser::T__30);
      setState(267);
      match(braneParser::T__18);
      setState(268);
      antlrcpp::downCast<IfContext *>(_localctx)->cond = expression(0);
      setState(269);
      match(braneParser::T__19);
      setState(270);
      antlrcpp::downCast<IfContext *>(_localctx)->operation = statement();
      setState(273);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
      case 1: {
        setState(271);
        match(braneParser::T__31);
        setState(272);
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
      setState(275);
      match(braneParser::T__32);
      setState(276);
      match(braneParser::T__18);
      setState(277);
      antlrcpp::downCast<WhileContext *>(_localctx)->cond = expression(0);
      setState(278);
      match(braneParser::T__19);
      setState(279);
      antlrcpp::downCast<WhileContext *>(_localctx)->operation = statement();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<braneParser::UnrollContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(281);
      match(braneParser::T__33);
      setState(282);
      match(braneParser::T__18);
      setState(283);
      antlrcpp::downCast<UnrollContext *>(_localctx)->id = match(braneParser::ID);
      setState(284);
      match(braneParser::T__19);
      setState(285);
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
    setState(325);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ConstIntContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(289);
      match(braneParser::INT);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ConstFloatContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(290);
      match(braneParser::FLOAT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ConstCharContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(291);
      match(braneParser::CHAR);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ConstStringContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(292);
      match(braneParser::STRING);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ConstBoolContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(293);
      match(braneParser::BOOL);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SizeOfExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(294);
      match(braneParser::T__34);
      setState(295);
      match(braneParser::T__18);
      setState(296);
      antlrcpp::downCast<SizeOfExprContext *>(_localctx)->expr = expression(0);
      setState(297);
      match(braneParser::T__19);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SizeOfTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(299);
      match(braneParser::T__34);
      setState(300);
      match(braneParser::T__18);
      setState(301);
      antlrcpp::downCast<SizeOfTypeContext *>(_localctx)->t = type();
      setState(302);
      match(braneParser::T__19);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<SizeOfPackContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(304);
      match(braneParser::T__34);
      setState(305);
      match(braneParser::T__3);
      setState(306);
      match(braneParser::T__18);
      setState(307);
      antlrcpp::downCast<SizeOfPackContext *>(_localctx)->id = match(braneParser::ID);
      setState(308);
      match(braneParser::T__19);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<DeclContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(309);
      declaration();
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<FunctionCallContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(310);
      antlrcpp::downCast<FunctionCallContext *>(_localctx)->id = scopedID();
      setState(311);
      match(braneParser::T__18);
      setState(312);
      argumentPack();
      setState(313);
      match(braneParser::T__19);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<IdContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(315);
      match(braneParser::ID);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<CastContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(316);
      match(braneParser::T__18);
      setState(317);
      type();
      setState(318);
      match(braneParser::T__19);
      setState(319);
      expression(6);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<ParenContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(321);
      match(braneParser::T__18);
      setState(322);
      expression(0);
      setState(323);
      match(braneParser::T__19);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(359);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(357);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MuldivContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(327);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(328);
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
          setState(329);
          antlrcpp::downCast<MuldivContext *>(_localctx)->right = expression(6);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddsubContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(330);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(331);
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
          setState(332);
          antlrcpp::downCast<AddsubContext *>(_localctx)->right = expression(5);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<LogicContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(333);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(334);
          antlrcpp::downCast<LogicContext *>(_localctx)->opr = match(braneParser::LOGIC);
          setState(335);
          antlrcpp::downCast<LogicContext *>(_localctx)->right = expression(4);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<ComparisonContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(336);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(337);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->opr = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 246080) != 0))) {
            antlrcpp::downCast<ComparisonContext *>(_localctx)->opr = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(338);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->right = expression(3);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<MemberFunctionCallContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(339);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(340);
          match(braneParser::T__35);
          setState(341);
          antlrcpp::downCast<MemberFunctionCallContext *>(_localctx)->name = match(braneParser::ID);
          setState(343);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == braneParser::T__5) {
            setState(342);
            antlrcpp::downCast<MemberFunctionCallContext *>(_localctx)->template_ = templateArgs();
          }
          setState(345);
          match(braneParser::T__18);
          setState(346);
          argumentPack();
          setState(347);
          match(braneParser::T__19);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<IndexAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(349);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(350);
          match(braneParser::T__36);
          setState(351);
          antlrcpp::downCast<IndexAccessContext *>(_localctx)->arg = expression(0);
          setState(352);
          match(braneParser::T__37);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(354);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(355);
          match(braneParser::T__35);
          setState(356);
          antlrcpp::downCast<MemberAccessContext *>(_localctx)->member = match(braneParser::ID);
          break;
        }

        default:
          break;
        } 
      }
      setState(361);
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


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
      "", "';'", "'typedef'", "'...'", "'template'", "'<'", "','", "'>'", 
      "'::'", "'const'", "'ref'", "'constexpr'", "'opr'", "'=='", "'!='", 
      "'<='", "'>='", "'[]'", "'('", "')'", "'ext'", "'{'", "'}'", "'link'", 
      "'as'", "'export as'", "'packed'", "'struct'", "'='", "'<-'", "'return'", 
      "'if'", "'else'", "'while'", "'unroll'", "'sizeof'", "'['", "']'", 
      "'.'", "", "", "", "", "", "", "", "", "", "", "'*'", "'/'", "'+'", 
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
  	4,1,53,360,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,1,0,4,0,50,8,0,11,0,12,0,51,1,0,1,0,1,0,3,0,57,
  	8,0,1,1,1,1,1,1,1,1,1,1,1,1,3,1,65,8,1,1,2,1,2,1,2,1,2,1,3,1,3,3,3,73,
  	8,3,1,3,3,3,76,8,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,5,4,85,8,4,10,4,12,4,88,
  	9,4,1,4,1,4,1,5,1,5,1,5,1,5,3,5,96,8,5,1,6,1,6,1,6,1,6,5,6,102,8,6,10,
  	6,12,6,105,9,6,1,6,1,6,1,7,1,7,3,7,111,8,7,1,7,1,7,3,7,115,8,7,1,8,3,
  	8,118,8,8,1,8,3,8,121,8,8,1,8,1,8,1,9,1,9,1,9,1,10,1,10,1,10,1,10,3,10,
  	132,8,10,1,11,1,11,1,11,5,11,137,8,11,10,11,12,11,140,9,11,3,11,142,8,
  	11,1,12,1,12,1,12,3,12,147,8,12,1,13,1,13,1,13,5,13,152,8,13,10,13,12,
  	13,155,9,13,3,13,157,8,13,1,14,3,14,160,8,14,1,14,3,14,163,8,14,1,14,
  	1,14,1,14,1,14,3,14,169,8,14,1,14,1,14,3,14,173,8,14,1,15,1,15,1,15,1,
  	15,1,15,3,15,180,8,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,3,16,190,
  	8,16,1,16,1,16,5,16,194,8,16,10,16,12,16,197,9,16,1,16,1,16,1,17,1,17,
  	1,17,1,17,3,17,205,8,17,1,17,1,17,1,18,1,18,1,18,1,18,5,18,213,8,18,10,
  	18,12,18,216,9,18,1,18,1,18,1,19,1,19,1,19,1,19,3,19,224,8,19,1,20,3,
  	20,227,8,20,1,20,3,20,230,8,20,1,20,1,20,1,20,1,20,5,20,236,8,20,10,20,
  	12,20,239,9,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,3,21,248,8,21,1,22,
  	1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,
  	5,22,265,8,22,10,22,12,22,268,9,22,1,22,1,22,1,22,3,22,273,8,22,1,22,
  	1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,283,8,22,1,22,1,22,1,22,1,22,
  	1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,296,8,22,1,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,3,23,325,8,23,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,3,23,353,8,23,5,23,
  	355,8,23,10,23,12,23,358,9,23,1,23,0,1,46,24,0,2,4,6,8,10,12,14,16,18,
  	20,22,24,26,28,30,32,34,36,38,40,42,44,46,0,4,4,0,5,5,7,7,13,17,49,53,
  	1,0,49,50,1,0,51,52,3,0,5,5,7,7,13,16,403,0,56,1,0,0,0,2,64,1,0,0,0,4,
  	66,1,0,0,0,6,72,1,0,0,0,8,79,1,0,0,0,10,95,1,0,0,0,12,97,1,0,0,0,14,108,
  	1,0,0,0,16,117,1,0,0,0,18,124,1,0,0,0,20,131,1,0,0,0,22,141,1,0,0,0,24,
  	146,1,0,0,0,26,156,1,0,0,0,28,159,1,0,0,0,30,174,1,0,0,0,32,184,1,0,0,
  	0,34,200,1,0,0,0,36,208,1,0,0,0,38,223,1,0,0,0,40,226,1,0,0,0,42,247,
  	1,0,0,0,44,295,1,0,0,0,46,324,1,0,0,0,48,50,3,2,1,0,49,48,1,0,0,0,50,
  	51,1,0,0,0,51,49,1,0,0,0,51,52,1,0,0,0,52,53,1,0,0,0,53,54,5,0,0,1,54,
  	57,1,0,0,0,55,57,5,0,0,1,56,49,1,0,0,0,56,55,1,0,0,0,57,1,1,0,0,0,58,
  	65,3,32,16,0,59,65,3,30,15,0,60,65,3,40,20,0,61,65,3,4,2,0,62,65,3,34,
  	17,0,63,65,3,36,18,0,64,58,1,0,0,0,64,59,1,0,0,0,64,60,1,0,0,0,64,61,
  	1,0,0,0,64,62,1,0,0,0,64,63,1,0,0,0,65,3,1,0,0,0,66,67,3,16,8,0,67,68,
  	5,48,0,0,68,69,5,1,0,0,69,5,1,0,0,0,70,73,3,16,8,0,71,73,5,2,0,0,72,70,
  	1,0,0,0,72,71,1,0,0,0,73,75,1,0,0,0,74,76,5,3,0,0,75,74,1,0,0,0,75,76,
  	1,0,0,0,76,77,1,0,0,0,77,78,5,48,0,0,78,7,1,0,0,0,79,80,5,4,0,0,80,81,
  	5,5,0,0,81,86,3,6,3,0,82,83,5,6,0,0,83,85,3,6,3,0,84,82,1,0,0,0,85,88,
  	1,0,0,0,86,84,1,0,0,0,86,87,1,0,0,0,87,89,1,0,0,0,88,86,1,0,0,0,89,90,
  	5,7,0,0,90,9,1,0,0,0,91,96,3,16,8,0,92,96,3,46,23,0,93,94,5,48,0,0,94,
  	96,5,3,0,0,95,91,1,0,0,0,95,92,1,0,0,0,95,93,1,0,0,0,96,11,1,0,0,0,97,
  	98,5,5,0,0,98,103,3,10,5,0,99,100,5,6,0,0,100,102,3,10,5,0,101,99,1,0,
  	0,0,102,105,1,0,0,0,103,101,1,0,0,0,103,104,1,0,0,0,104,106,1,0,0,0,105,
  	103,1,0,0,0,106,107,5,7,0,0,107,13,1,0,0,0,108,110,5,48,0,0,109,111,3,
  	12,6,0,110,109,1,0,0,0,110,111,1,0,0,0,111,114,1,0,0,0,112,113,5,8,0,
  	0,113,115,3,14,7,0,114,112,1,0,0,0,114,115,1,0,0,0,115,15,1,0,0,0,116,
  	118,5,9,0,0,117,116,1,0,0,0,117,118,1,0,0,0,118,120,1,0,0,0,119,121,5,
  	10,0,0,120,119,1,0,0,0,120,121,1,0,0,0,121,122,1,0,0,0,122,123,3,14,7,
  	0,123,17,1,0,0,0,124,125,3,16,8,0,125,126,5,48,0,0,126,19,1,0,0,0,127,
  	132,3,18,9,0,128,129,5,48,0,0,129,130,5,3,0,0,130,132,5,48,0,0,131,127,
  	1,0,0,0,131,128,1,0,0,0,132,21,1,0,0,0,133,138,3,20,10,0,134,135,5,6,
  	0,0,135,137,3,20,10,0,136,134,1,0,0,0,137,140,1,0,0,0,138,136,1,0,0,0,
  	138,139,1,0,0,0,139,142,1,0,0,0,140,138,1,0,0,0,141,133,1,0,0,0,141,142,
  	1,0,0,0,142,23,1,0,0,0,143,147,3,46,23,0,144,145,5,48,0,0,145,147,5,3,
  	0,0,146,143,1,0,0,0,146,144,1,0,0,0,147,25,1,0,0,0,148,153,3,24,12,0,
  	149,150,5,6,0,0,150,152,3,24,12,0,151,149,1,0,0,0,152,155,1,0,0,0,153,
  	151,1,0,0,0,153,154,1,0,0,0,154,157,1,0,0,0,155,153,1,0,0,0,156,148,1,
  	0,0,0,156,157,1,0,0,0,157,27,1,0,0,0,158,160,3,8,4,0,159,158,1,0,0,0,
  	159,160,1,0,0,0,160,162,1,0,0,0,161,163,5,11,0,0,162,161,1,0,0,0,162,
  	163,1,0,0,0,163,172,1,0,0,0,164,168,3,16,8,0,165,169,5,48,0,0,166,167,
  	5,12,0,0,167,169,7,0,0,0,168,165,1,0,0,0,168,166,1,0,0,0,169,173,1,0,
  	0,0,170,171,5,12,0,0,171,173,3,16,8,0,172,164,1,0,0,0,172,170,1,0,0,0,
  	173,29,1,0,0,0,174,175,3,28,14,0,175,176,5,18,0,0,176,177,3,22,11,0,177,
  	179,5,19,0,0,178,180,5,9,0,0,179,178,1,0,0,0,179,180,1,0,0,0,180,181,
  	1,0,0,0,181,182,5,20,0,0,182,183,5,1,0,0,183,31,1,0,0,0,184,185,3,28,
  	14,0,185,186,5,18,0,0,186,187,3,22,11,0,187,189,5,19,0,0,188,190,5,9,
  	0,0,189,188,1,0,0,0,189,190,1,0,0,0,190,191,1,0,0,0,191,195,5,21,0,0,
  	192,194,3,44,22,0,193,192,1,0,0,0,194,197,1,0,0,0,195,193,1,0,0,0,195,
  	196,1,0,0,0,196,198,1,0,0,0,197,195,1,0,0,0,198,199,5,22,0,0,199,33,1,
  	0,0,0,200,201,5,23,0,0,201,204,5,47,0,0,202,203,5,24,0,0,203,205,5,47,
  	0,0,204,202,1,0,0,0,204,205,1,0,0,0,205,206,1,0,0,0,206,207,5,1,0,0,207,
  	35,1,0,0,0,208,209,5,25,0,0,209,210,5,47,0,0,210,214,5,21,0,0,211,213,
  	3,38,19,0,212,211,1,0,0,0,213,216,1,0,0,0,214,212,1,0,0,0,214,215,1,0,
  	0,0,215,217,1,0,0,0,216,214,1,0,0,0,217,218,5,22,0,0,218,37,1,0,0,0,219,
  	224,3,32,16,0,220,224,3,30,15,0,221,224,3,40,20,0,222,224,3,4,2,0,223,
  	219,1,0,0,0,223,220,1,0,0,0,223,221,1,0,0,0,223,222,1,0,0,0,224,39,1,
  	0,0,0,225,227,3,8,4,0,226,225,1,0,0,0,226,227,1,0,0,0,227,229,1,0,0,0,
  	228,230,5,26,0,0,229,228,1,0,0,0,229,230,1,0,0,0,230,231,1,0,0,0,231,
  	232,5,27,0,0,232,233,5,48,0,0,233,237,5,21,0,0,234,236,3,42,21,0,235,
  	234,1,0,0,0,236,239,1,0,0,0,237,235,1,0,0,0,237,238,1,0,0,0,238,240,1,
  	0,0,0,239,237,1,0,0,0,240,241,5,22,0,0,241,41,1,0,0,0,242,243,3,18,9,
  	0,243,244,5,1,0,0,244,248,1,0,0,0,245,248,3,32,16,0,246,248,3,30,15,0,
  	247,242,1,0,0,0,247,245,1,0,0,0,247,246,1,0,0,0,248,43,1,0,0,0,249,250,
  	3,46,23,0,250,251,5,1,0,0,251,296,1,0,0,0,252,253,3,46,23,0,253,254,5,
  	28,0,0,254,255,3,46,23,0,255,256,5,1,0,0,256,296,1,0,0,0,257,258,3,46,
  	23,0,258,259,5,29,0,0,259,260,3,46,23,0,260,261,5,1,0,0,261,296,1,0,0,
  	0,262,266,5,21,0,0,263,265,3,44,22,0,264,263,1,0,0,0,265,268,1,0,0,0,
  	266,264,1,0,0,0,266,267,1,0,0,0,267,269,1,0,0,0,268,266,1,0,0,0,269,296,
  	5,22,0,0,270,272,5,30,0,0,271,273,3,46,23,0,272,271,1,0,0,0,272,273,1,
  	0,0,0,273,274,1,0,0,0,274,296,5,1,0,0,275,276,5,31,0,0,276,277,5,18,0,
  	0,277,278,3,46,23,0,278,279,5,19,0,0,279,282,3,44,22,0,280,281,5,32,0,
  	0,281,283,3,44,22,0,282,280,1,0,0,0,282,283,1,0,0,0,283,296,1,0,0,0,284,
  	285,5,33,0,0,285,286,5,18,0,0,286,287,3,46,23,0,287,288,5,19,0,0,288,
  	289,3,44,22,0,289,296,1,0,0,0,290,291,5,34,0,0,291,292,5,18,0,0,292,293,
  	5,48,0,0,293,294,5,19,0,0,294,296,3,44,22,0,295,249,1,0,0,0,295,252,1,
  	0,0,0,295,257,1,0,0,0,295,262,1,0,0,0,295,270,1,0,0,0,295,275,1,0,0,0,
  	295,284,1,0,0,0,295,290,1,0,0,0,296,45,1,0,0,0,297,298,6,23,-1,0,298,
  	325,5,44,0,0,299,325,5,45,0,0,300,325,5,46,0,0,301,325,5,47,0,0,302,325,
  	5,43,0,0,303,304,5,35,0,0,304,305,5,18,0,0,305,306,3,16,8,0,306,307,5,
  	19,0,0,307,325,1,0,0,0,308,309,5,35,0,0,309,310,5,3,0,0,310,311,5,18,
  	0,0,311,312,5,48,0,0,312,325,5,19,0,0,313,325,3,18,9,0,314,325,3,14,7,
  	0,315,316,5,18,0,0,316,317,3,16,8,0,317,318,5,19,0,0,318,319,3,46,23,
  	6,319,325,1,0,0,0,320,321,5,18,0,0,321,322,3,46,23,0,322,323,5,19,0,0,
  	323,325,1,0,0,0,324,297,1,0,0,0,324,299,1,0,0,0,324,300,1,0,0,0,324,301,
  	1,0,0,0,324,302,1,0,0,0,324,303,1,0,0,0,324,308,1,0,0,0,324,313,1,0,0,
  	0,324,314,1,0,0,0,324,315,1,0,0,0,324,320,1,0,0,0,325,356,1,0,0,0,326,
  	327,10,5,0,0,327,328,7,1,0,0,328,355,3,46,23,6,329,330,10,4,0,0,330,331,
  	7,2,0,0,331,355,3,46,23,5,332,333,10,3,0,0,333,334,5,53,0,0,334,355,3,
  	46,23,4,335,336,10,2,0,0,336,337,7,3,0,0,337,355,3,46,23,3,338,339,10,
  	10,0,0,339,340,5,18,0,0,340,341,3,26,13,0,341,342,5,19,0,0,342,355,1,
  	0,0,0,343,344,10,8,0,0,344,345,5,36,0,0,345,346,3,46,23,0,346,347,5,37,
  	0,0,347,355,1,0,0,0,348,349,10,7,0,0,349,350,5,38,0,0,350,352,5,48,0,
  	0,351,353,3,12,6,0,352,351,1,0,0,0,352,353,1,0,0,0,353,355,1,0,0,0,354,
  	326,1,0,0,0,354,329,1,0,0,0,354,332,1,0,0,0,354,335,1,0,0,0,354,338,1,
  	0,0,0,354,343,1,0,0,0,354,348,1,0,0,0,355,358,1,0,0,0,356,354,1,0,0,0,
  	356,357,1,0,0,0,357,47,1,0,0,0,358,356,1,0,0,0,40,51,56,64,72,75,86,95,
  	103,110,114,117,120,131,138,141,146,153,156,159,162,168,172,179,189,195,
  	204,214,223,226,229,237,247,266,272,282,295,324,352,354,356
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
          ((1ULL << _la) & 281475219987984) != 0));
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

braneParser::TypeContext* braneParser::TemplateDefArgumentContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
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
    setState(72);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__8:
      case braneParser::T__9:
      case braneParser::ID: {
        setState(70);
        antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->exprType = type();
        break;
      }

      case braneParser::T__1: {
        setState(71);
        antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->isTypedef = match(braneParser::T__1);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(75);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__2) {
      setState(74);
      antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->isPack = match(braneParser::T__2);
    }
    setState(77);
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
    setState(79);
    match(braneParser::T__3);
    setState(80);
    match(braneParser::T__4);
    setState(81);
    templateDefArgument();
    setState(86);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__5) {
      setState(82);
      match(braneParser::T__5);
      setState(83);
      templateDefArgument();
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
    setState(95);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::TemplateTypeArgContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(91);
      antlrcpp::downCast<TemplateTypeArgContext *>(_localctx)->t = type();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::TemplateExprArgContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(92);
      antlrcpp::downCast<TemplateExprArgContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::PackExpansionArgContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(93);
      antlrcpp::downCast<PackExpansionArgContext *>(_localctx)->packID = match(braneParser::ID);
      setState(94);
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
    setState(97);
    match(braneParser::T__4);
    setState(98);
    templateArg();
    setState(103);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__5) {
      setState(99);
      match(braneParser::T__5);
      setState(100);
      templateArg();
      setState(105);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(106);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(108);
    antlrcpp::downCast<ScopedIDContext *>(_localctx)->id = match(braneParser::ID);
    setState(110);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(109);
      antlrcpp::downCast<ScopedIDContext *>(_localctx)->template_ = templateArgs();
      break;
    }

    default:
      break;
    }
    setState(114);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(112);
      match(braneParser::T__7);
      setState(113);
      antlrcpp::downCast<ScopedIDContext *>(_localctx)->child = scopedID();
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
    setState(117);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__8) {
      setState(116);
      antlrcpp::downCast<TypeContext *>(_localctx)->isConst = match(braneParser::T__8);
    }
    setState(120);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__9) {
      setState(119);
      antlrcpp::downCast<TypeContext *>(_localctx)->isRef = match(braneParser::T__9);
    }
    setState(122);
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
    setState(124);
    type();
    setState(125);
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
    setState(131);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(127);
      declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(128);
      antlrcpp::downCast<ArgumentListItemContext *>(_localctx)->pack = match(braneParser::ID);
      setState(129);
      match(braneParser::T__2);
      setState(130);
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
    setState(141);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281474976712192) != 0)) {
      setState(133);
      argumentListItem();
      setState(138);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__5) {
        setState(134);
        match(braneParser::T__5);
        setState(135);
        argumentListItem();
        setState(140);
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
    setState(146);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(143);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(144);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->packID = match(braneParser::ID);
      setState(145);
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
    setState(156);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 554188220401152) != 0)) {
      setState(148);
      argumentPackItem();
      setState(153);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__5) {
        setState(149);
        match(braneParser::T__5);
        setState(150);
        argumentPackItem();
        setState(155);
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
    setState(159);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(158);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->template_ = templateDef();
    }
    setState(162);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__10) {
      setState(161);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->isConstexpr = match(braneParser::T__10);
    }
    setState(172);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__8:
      case braneParser::T__9:
      case braneParser::ID: {
        setState(164);
        type();
        setState(168);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case braneParser::ID: {
            setState(165);
            antlrcpp::downCast<FunctionSigContext *>(_localctx)->id = match(braneParser::ID);
            break;
          }

          case braneParser::T__11: {
            setState(166);
            match(braneParser::T__11);
            setState(167);
            antlrcpp::downCast<FunctionSigContext *>(_localctx)->oprID = _input->LT(1);
            _la = _input->LA(1);
            if (!((((_la & ~ 0x3fULL) == 0) &&
              ((1ULL << _la) & 17451448556314784) != 0))) {
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
        setState(170);
        match(braneParser::T__11);
        setState(171);
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
    setState(174);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->sig = functionSig();
    setState(175);
    match(braneParser::T__17);
    setState(176);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->arguments = argumentList();
    setState(177);
    match(braneParser::T__18);
    setState(179);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__8) {
      setState(178);
      antlrcpp::downCast<FunctionStubContext *>(_localctx)->isConst = match(braneParser::T__8);
    }
    setState(181);
    match(braneParser::T__19);
    setState(182);
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
    setState(184);
    antlrcpp::downCast<FunctionContext *>(_localctx)->sig = functionSig();
    setState(185);
    match(braneParser::T__17);
    setState(186);
    antlrcpp::downCast<FunctionContext *>(_localctx)->arguments = argumentList();
    setState(187);
    match(braneParser::T__18);
    setState(189);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__8) {
      setState(188);
      antlrcpp::downCast<FunctionContext *>(_localctx)->isConst = match(braneParser::T__8);
    }
    setState(191);
    match(braneParser::T__20);
    setState(195);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 554217213527552) != 0)) {
      setState(192);
      antlrcpp::downCast<FunctionContext *>(_localctx)->statements = statement();
      setState(197);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(198);
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
    setState(200);
    match(braneParser::T__22);
    setState(201);
    antlrcpp::downCast<LinkContext *>(_localctx)->library = match(braneParser::STRING);
    setState(204);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__23) {
      setState(202);
      match(braneParser::T__23);
      setState(203);
      antlrcpp::downCast<LinkContext *>(_localctx)->alias = match(braneParser::STRING);
    }
    setState(206);
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
    setState(208);
    match(braneParser::T__24);
    setState(209);
    antlrcpp::downCast<ExportContext *>(_localctx)->libID = match(braneParser::STRING);
    setState(210);
    match(braneParser::T__20);
    setState(214);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281475178044944) != 0)) {
      setState(211);
      exportSegment();
      setState(216);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(217);
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
    setState(223);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(219);
      function();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(220);
      functionStub();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(221);
      structDef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(222);
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
    setState(226);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(225);
      antlrcpp::downCast<StructDefContext *>(_localctx)->template_ = templateDef();
    }
    setState(229);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__25) {
      setState(228);
      antlrcpp::downCast<StructDefContext *>(_localctx)->packed = match(braneParser::T__25);
    }
    setState(231);
    match(braneParser::T__26);
    setState(232);
    antlrcpp::downCast<StructDefContext *>(_localctx)->id = match(braneParser::ID);
    setState(233);
    match(braneParser::T__20);
    setState(237);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281474976718352) != 0)) {
      setState(234);
      antlrcpp::downCast<StructDefContext *>(_localctx)->memberVars = structMember();
      setState(239);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(240);
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
//----------------- MemberFunctionStubContext ------------------------------------------------------------------

braneParser::FunctionStubContext* braneParser::MemberFunctionStubContext::functionStub() {
  return getRuleContext<braneParser::FunctionStubContext>(0);
}

braneParser::MemberFunctionStubContext::MemberFunctionStubContext(StructMemberContext *ctx) { copyFrom(ctx); }


std::any braneParser::MemberFunctionStubContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitMemberFunctionStub(this);
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
    setState(247);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::MemberVariableContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(242);
      antlrcpp::downCast<MemberVariableContext *>(_localctx)->var = declaration();
      setState(243);
      match(braneParser::T__0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::MemberFunctionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(245);
      antlrcpp::downCast<MemberFunctionContext *>(_localctx)->func = function();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::MemberFunctionStubContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(246);
      functionStub();
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
//----------------- RefAssignmentContext ------------------------------------------------------------------

std::vector<braneParser::ExpressionContext *> braneParser::RefAssignmentContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::RefAssignmentContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}

braneParser::RefAssignmentContext::RefAssignmentContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::RefAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitRefAssignment(this);
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
    setState(295);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::ExprStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(249);
      expression(0);
      setState(250);
      match(braneParser::T__0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::AssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(252);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->lValue = expression(0);
      setState(253);
      match(braneParser::T__27);
      setState(254);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->rValue = expression(0);
      setState(255);
      match(braneParser::T__0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::RefAssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(257);
      antlrcpp::downCast<RefAssignmentContext *>(_localctx)->lValue = expression(0);
      setState(258);
      match(braneParser::T__28);
      setState(259);
      antlrcpp::downCast<RefAssignmentContext *>(_localctx)->rValue = expression(0);
      setState(260);
      match(braneParser::T__0);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<braneParser::ScopeContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(262);
      match(braneParser::T__20);
      setState(266);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 554217213527552) != 0)) {
        setState(263);
        statement();
        setState(268);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(269);
      match(braneParser::T__21);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<braneParser::ReturnContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(270);
      match(braneParser::T__29);
      setState(272);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 554188220401152) != 0)) {
        setState(271);
        expression(0);
      }
      setState(274);
      match(braneParser::T__0);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<braneParser::IfContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(275);
      match(braneParser::T__30);
      setState(276);
      match(braneParser::T__17);
      setState(277);
      antlrcpp::downCast<IfContext *>(_localctx)->cond = expression(0);
      setState(278);
      match(braneParser::T__18);
      setState(279);
      antlrcpp::downCast<IfContext *>(_localctx)->operation = statement();
      setState(282);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
      case 1: {
        setState(280);
        match(braneParser::T__31);
        setState(281);
        antlrcpp::downCast<IfContext *>(_localctx)->elseOp = statement();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<braneParser::WhileContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(284);
      match(braneParser::T__32);
      setState(285);
      match(braneParser::T__17);
      setState(286);
      antlrcpp::downCast<WhileContext *>(_localctx)->cond = expression(0);
      setState(287);
      match(braneParser::T__18);
      setState(288);
      antlrcpp::downCast<WhileContext *>(_localctx)->operation = statement();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<braneParser::UnrollContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(290);
      match(braneParser::T__33);
      setState(291);
      match(braneParser::T__17);
      setState(292);
      antlrcpp::downCast<UnrollContext *>(_localctx)->id = match(braneParser::ID);
      setState(293);
      match(braneParser::T__18);
      setState(294);
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

braneParser::TemplateArgsContext* braneParser::MemberAccessContext::templateArgs() {
  return getRuleContext<braneParser::TemplateArgsContext>(0);
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

braneParser::ExpressionContext* braneParser::FunctionCallContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
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

braneParser::ScopedIDContext* braneParser::IdContext::scopedID() {
  return getRuleContext<braneParser::ScopedIDContext>(0);
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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ConstIntContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(298);
      match(braneParser::INT);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ConstFloatContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(299);
      match(braneParser::FLOAT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ConstCharContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(300);
      match(braneParser::CHAR);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ConstStringContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(301);
      match(braneParser::STRING);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ConstBoolContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(302);
      match(braneParser::BOOL);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SizeOfTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(303);
      match(braneParser::T__34);
      setState(304);
      match(braneParser::T__17);
      setState(305);
      antlrcpp::downCast<SizeOfTypeContext *>(_localctx)->t = type();
      setState(306);
      match(braneParser::T__18);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SizeOfPackContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(308);
      match(braneParser::T__34);
      setState(309);
      match(braneParser::T__2);
      setState(310);
      match(braneParser::T__17);
      setState(311);
      antlrcpp::downCast<SizeOfPackContext *>(_localctx)->id = match(braneParser::ID);
      setState(312);
      match(braneParser::T__18);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<DeclContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(313);
      declaration();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<IdContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(314);
      scopedID();
      break;
    }

    case 10: {
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

    case 11: {
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
    setState(356);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(354);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
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
          auto newContext = _tracker.createInstance<FunctionCallContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->overrides = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(338);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(339);
          match(braneParser::T__17);
          setState(340);
          argumentPack();
          setState(341);
          match(braneParser::T__18);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<IndexAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(343);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(344);
          match(braneParser::T__35);
          setState(345);
          antlrcpp::downCast<IndexAccessContext *>(_localctx)->arg = expression(0);
          setState(346);
          match(braneParser::T__36);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(348);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(349);
          match(braneParser::T__37);
          setState(350);
          antlrcpp::downCast<MemberAccessContext *>(_localctx)->member = match(braneParser::ID);
          setState(352);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
          case 1: {
            setState(351);
            antlrcpp::downCast<MemberAccessContext *>(_localctx)->template_ = templateArgs();
            break;
          }

          default:
            break;
          }
          break;
        }

        default:
          break;
        } 
      }
      setState(358);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
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

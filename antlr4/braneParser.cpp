
// Generated from /home/wirewhiz/Documents/git/BraneEngine/libraries/BraneScript/antlr4/brane.g4 by ANTLR 4.12.0


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
      "modules", "link", "linkList", "tags", "module", "moduleComponent", 
      "global", "templateDefArgument", "templateDef", "templateArg", "templateArgs", 
      "scopedID", "type", "declaration", "argumentListItem", "argumentList", 
      "argumentPackItem", "argumentPack", "bracketOpr", "functionSig", "functionStub", 
      "function", "capturedVar", "varCapture", "structDef", "structMember", 
      "statement", "expression"
    },
    std::vector<std::string>{
      "", "'public'", "'link'", "'as'", "'['", "','", "']'", "'module'", 
      "'{'", "'}'", "';'", "'typedef'", "'...'", "'template'", "'<'", "'>'", 
      "'Lambda'", "'::'", "'const'", "'ref'", "'('", "')'", "'constexpr'", 
      "'opr'", "'=='", "'!='", "'<='", "'>='", "'!'", "'ext'", "'packed'", 
      "'struct'", "'='", "'<-'", "'return'", "'if'", "'else'", "'while'", 
      "'unroll'", "'sizeof'", "'.'", "", "", "", "", "", "", "", "", "", 
      "", "'*'", "'/'", "'+'", "'-'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "COMMENT", "NEWLINE", "BLOCK_COMMENT", 
      "SPACE", "BOOL", "INT", "FLOAT", "CHAR", "STRING", "ID", "MUL", "DIV", 
      "ADD", "SUB", "LOGIC"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,55,433,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,1,0,5,
  	0,58,8,0,10,0,12,0,61,9,0,1,0,3,0,64,8,0,1,1,3,1,67,8,1,1,1,1,1,1,1,1,
  	1,3,1,73,8,1,1,2,5,2,76,8,2,10,2,12,2,79,9,2,1,3,1,3,1,3,1,3,5,3,85,8,
  	3,10,3,12,3,88,9,3,3,3,90,8,3,1,3,1,3,1,4,3,4,95,8,4,1,4,1,4,1,4,1,4,
  	1,4,5,4,102,8,4,10,4,12,4,105,9,4,1,4,1,4,1,5,1,5,1,5,1,5,3,5,113,8,5,
  	1,6,1,6,1,6,1,6,1,7,1,7,3,7,121,8,7,1,7,3,7,124,8,7,1,7,1,7,1,8,1,8,1,
  	8,1,8,1,8,5,8,133,8,8,10,8,12,8,136,9,8,1,8,1,8,1,9,1,9,1,9,1,9,3,9,144,
  	8,9,1,10,1,10,1,10,1,10,5,10,150,8,10,10,10,12,10,153,9,10,1,10,1,10,
  	1,11,1,11,3,11,159,8,11,1,11,1,11,3,11,163,8,11,1,12,3,12,166,8,12,1,
  	12,3,12,169,8,12,1,12,1,12,1,13,1,13,1,13,1,14,1,14,1,14,1,14,3,14,180,
  	8,14,1,15,1,15,1,15,5,15,185,8,15,10,15,12,15,188,9,15,3,15,190,8,15,
  	1,16,1,16,1,16,3,16,195,8,16,1,17,1,17,1,17,5,17,200,8,17,10,17,12,17,
  	203,9,17,3,17,205,8,17,1,18,1,18,1,18,1,18,3,18,211,8,18,1,19,3,19,214,
  	8,19,1,19,3,19,217,8,19,1,19,3,19,220,8,19,1,19,1,19,1,19,1,19,1,19,3,
  	19,227,8,19,3,19,229,8,19,1,19,1,19,3,19,233,8,19,1,20,1,20,1,20,1,20,
  	1,20,3,20,240,8,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,3,21,250,8,
  	21,1,21,1,21,5,21,254,8,21,10,21,12,21,257,9,21,1,21,1,21,1,22,3,22,262,
  	8,22,1,22,1,22,1,23,1,23,1,23,5,23,269,8,23,10,23,12,23,272,9,23,1,24,
  	3,24,275,8,24,1,24,3,24,278,8,24,1,24,3,24,281,8,24,1,24,1,24,1,24,1,
  	24,5,24,287,8,24,10,24,12,24,290,9,24,1,24,1,24,1,25,1,25,1,25,1,25,1,
  	25,3,25,299,8,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,
  	26,1,26,1,26,1,26,1,26,5,26,316,8,26,10,26,12,26,319,9,26,1,26,1,26,1,
  	26,3,26,324,8,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,3,26,334,8,26,
  	1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,3,26,347,8,26,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,384,8,27,1,27,1,27,1,27,1,27,
  	1,27,5,27,391,8,27,10,27,12,27,394,9,27,1,27,1,27,3,27,398,8,27,1,27,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,426,8,27,
  	5,27,428,8,27,10,27,12,27,431,9,27,1,27,0,1,54,28,0,2,4,6,8,10,12,14,
  	16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,0,5,2,0,16,
  	16,50,50,3,0,14,15,24,28,51,55,1,0,51,52,1,0,53,54,2,0,14,15,24,27,482,
  	0,59,1,0,0,0,2,66,1,0,0,0,4,77,1,0,0,0,6,80,1,0,0,0,8,94,1,0,0,0,10,112,
  	1,0,0,0,12,114,1,0,0,0,14,120,1,0,0,0,16,127,1,0,0,0,18,143,1,0,0,0,20,
  	145,1,0,0,0,22,156,1,0,0,0,24,165,1,0,0,0,26,172,1,0,0,0,28,179,1,0,0,
  	0,30,189,1,0,0,0,32,194,1,0,0,0,34,204,1,0,0,0,36,210,1,0,0,0,38,213,
  	1,0,0,0,40,234,1,0,0,0,42,244,1,0,0,0,44,261,1,0,0,0,46,265,1,0,0,0,48,
  	274,1,0,0,0,50,298,1,0,0,0,52,346,1,0,0,0,54,397,1,0,0,0,56,58,3,8,4,
  	0,57,56,1,0,0,0,58,61,1,0,0,0,59,57,1,0,0,0,59,60,1,0,0,0,60,63,1,0,0,
  	0,61,59,1,0,0,0,62,64,5,0,0,1,63,62,1,0,0,0,63,64,1,0,0,0,64,1,1,0,0,
  	0,65,67,5,1,0,0,66,65,1,0,0,0,66,67,1,0,0,0,67,68,1,0,0,0,68,69,5,2,0,
  	0,69,72,5,49,0,0,70,71,5,3,0,0,71,73,5,49,0,0,72,70,1,0,0,0,72,73,1,0,
  	0,0,73,3,1,0,0,0,74,76,3,2,1,0,75,74,1,0,0,0,76,79,1,0,0,0,77,75,1,0,
  	0,0,77,78,1,0,0,0,78,5,1,0,0,0,79,77,1,0,0,0,80,89,5,4,0,0,81,86,5,49,
  	0,0,82,83,5,5,0,0,83,85,5,49,0,0,84,82,1,0,0,0,85,88,1,0,0,0,86,84,1,
  	0,0,0,86,87,1,0,0,0,87,90,1,0,0,0,88,86,1,0,0,0,89,81,1,0,0,0,89,90,1,
  	0,0,0,90,91,1,0,0,0,91,92,5,6,0,0,92,7,1,0,0,0,93,95,3,6,3,0,94,93,1,
  	0,0,0,94,95,1,0,0,0,95,96,1,0,0,0,96,97,5,7,0,0,97,98,5,49,0,0,98,99,
  	3,4,2,0,99,103,5,8,0,0,100,102,3,10,5,0,101,100,1,0,0,0,102,105,1,0,0,
  	0,103,101,1,0,0,0,103,104,1,0,0,0,104,106,1,0,0,0,105,103,1,0,0,0,106,
  	107,5,9,0,0,107,9,1,0,0,0,108,113,3,42,21,0,109,113,3,40,20,0,110,113,
  	3,48,24,0,111,113,3,12,6,0,112,108,1,0,0,0,112,109,1,0,0,0,112,110,1,
  	0,0,0,112,111,1,0,0,0,113,11,1,0,0,0,114,115,3,24,12,0,115,116,5,50,0,
  	0,116,117,5,10,0,0,117,13,1,0,0,0,118,121,3,24,12,0,119,121,5,11,0,0,
  	120,118,1,0,0,0,120,119,1,0,0,0,121,123,1,0,0,0,122,124,5,12,0,0,123,
  	122,1,0,0,0,123,124,1,0,0,0,124,125,1,0,0,0,125,126,5,50,0,0,126,15,1,
  	0,0,0,127,128,5,13,0,0,128,129,5,14,0,0,129,134,3,14,7,0,130,131,5,5,
  	0,0,131,133,3,14,7,0,132,130,1,0,0,0,133,136,1,0,0,0,134,132,1,0,0,0,
  	134,135,1,0,0,0,135,137,1,0,0,0,136,134,1,0,0,0,137,138,5,15,0,0,138,
  	17,1,0,0,0,139,144,3,24,12,0,140,144,3,54,27,0,141,142,5,50,0,0,142,144,
  	5,12,0,0,143,139,1,0,0,0,143,140,1,0,0,0,143,141,1,0,0,0,144,19,1,0,0,
  	0,145,146,5,14,0,0,146,151,3,18,9,0,147,148,5,5,0,0,148,150,3,18,9,0,
  	149,147,1,0,0,0,150,153,1,0,0,0,151,149,1,0,0,0,151,152,1,0,0,0,152,154,
  	1,0,0,0,153,151,1,0,0,0,154,155,5,15,0,0,155,21,1,0,0,0,156,158,7,0,0,
  	0,157,159,3,20,10,0,158,157,1,0,0,0,158,159,1,0,0,0,159,162,1,0,0,0,160,
  	161,5,17,0,0,161,163,3,22,11,0,162,160,1,0,0,0,162,163,1,0,0,0,163,23,
  	1,0,0,0,164,166,5,18,0,0,165,164,1,0,0,0,165,166,1,0,0,0,166,168,1,0,
  	0,0,167,169,5,19,0,0,168,167,1,0,0,0,168,169,1,0,0,0,169,170,1,0,0,0,
  	170,171,3,22,11,0,171,25,1,0,0,0,172,173,3,24,12,0,173,174,5,50,0,0,174,
  	27,1,0,0,0,175,180,3,26,13,0,176,177,5,50,0,0,177,178,5,12,0,0,178,180,
  	5,50,0,0,179,175,1,0,0,0,179,176,1,0,0,0,180,29,1,0,0,0,181,186,3,28,
  	14,0,182,183,5,5,0,0,183,185,3,28,14,0,184,182,1,0,0,0,185,188,1,0,0,
  	0,186,184,1,0,0,0,186,187,1,0,0,0,187,190,1,0,0,0,188,186,1,0,0,0,189,
  	181,1,0,0,0,189,190,1,0,0,0,190,31,1,0,0,0,191,195,3,54,27,0,192,193,
  	5,50,0,0,193,195,5,12,0,0,194,191,1,0,0,0,194,192,1,0,0,0,195,33,1,0,
  	0,0,196,201,3,32,16,0,197,198,5,5,0,0,198,200,3,32,16,0,199,197,1,0,0,
  	0,200,203,1,0,0,0,201,199,1,0,0,0,201,202,1,0,0,0,202,205,1,0,0,0,203,
  	201,1,0,0,0,204,196,1,0,0,0,204,205,1,0,0,0,205,35,1,0,0,0,206,207,5,
  	20,0,0,207,211,5,21,0,0,208,209,5,4,0,0,209,211,5,6,0,0,210,206,1,0,0,
  	0,210,208,1,0,0,0,211,37,1,0,0,0,212,214,3,6,3,0,213,212,1,0,0,0,213,
  	214,1,0,0,0,214,216,1,0,0,0,215,217,3,16,8,0,216,215,1,0,0,0,216,217,
  	1,0,0,0,217,219,1,0,0,0,218,220,5,22,0,0,219,218,1,0,0,0,219,220,1,0,
  	0,0,220,232,1,0,0,0,221,228,3,24,12,0,222,229,5,50,0,0,223,226,5,23,0,
  	0,224,227,7,1,0,0,225,227,3,36,18,0,226,224,1,0,0,0,226,225,1,0,0,0,227,
  	229,1,0,0,0,228,222,1,0,0,0,228,223,1,0,0,0,229,233,1,0,0,0,230,231,5,
  	23,0,0,231,233,3,24,12,0,232,221,1,0,0,0,232,230,1,0,0,0,233,39,1,0,0,
  	0,234,235,3,38,19,0,235,236,5,20,0,0,236,237,3,30,15,0,237,239,5,21,0,
  	0,238,240,5,18,0,0,239,238,1,0,0,0,239,240,1,0,0,0,240,241,1,0,0,0,241,
  	242,5,29,0,0,242,243,5,10,0,0,243,41,1,0,0,0,244,245,3,38,19,0,245,246,
  	5,20,0,0,246,247,3,30,15,0,247,249,5,21,0,0,248,250,5,18,0,0,249,248,
  	1,0,0,0,249,250,1,0,0,0,250,251,1,0,0,0,251,255,5,8,0,0,252,254,3,52,
  	26,0,253,252,1,0,0,0,254,257,1,0,0,0,255,253,1,0,0,0,255,256,1,0,0,0,
  	256,258,1,0,0,0,257,255,1,0,0,0,258,259,5,9,0,0,259,43,1,0,0,0,260,262,
  	5,19,0,0,261,260,1,0,0,0,261,262,1,0,0,0,262,263,1,0,0,0,263,264,3,22,
  	11,0,264,45,1,0,0,0,265,270,3,44,22,0,266,267,5,5,0,0,267,269,3,44,22,
  	0,268,266,1,0,0,0,269,272,1,0,0,0,270,268,1,0,0,0,270,271,1,0,0,0,271,
  	47,1,0,0,0,272,270,1,0,0,0,273,275,3,6,3,0,274,273,1,0,0,0,274,275,1,
  	0,0,0,275,277,1,0,0,0,276,278,3,16,8,0,277,276,1,0,0,0,277,278,1,0,0,
  	0,278,280,1,0,0,0,279,281,5,30,0,0,280,279,1,0,0,0,280,281,1,0,0,0,281,
  	282,1,0,0,0,282,283,5,31,0,0,283,284,7,0,0,0,284,288,5,8,0,0,285,287,
  	3,50,25,0,286,285,1,0,0,0,287,290,1,0,0,0,288,286,1,0,0,0,288,289,1,0,
  	0,0,289,291,1,0,0,0,290,288,1,0,0,0,291,292,5,9,0,0,292,49,1,0,0,0,293,
  	299,3,40,20,0,294,299,3,42,21,0,295,296,3,26,13,0,296,297,5,10,0,0,297,
  	299,1,0,0,0,298,293,1,0,0,0,298,294,1,0,0,0,298,295,1,0,0,0,299,51,1,
  	0,0,0,300,301,3,54,27,0,301,302,5,10,0,0,302,347,1,0,0,0,303,304,3,54,
  	27,0,304,305,5,32,0,0,305,306,3,54,27,0,306,307,5,10,0,0,307,347,1,0,
  	0,0,308,309,3,54,27,0,309,310,5,33,0,0,310,311,3,54,27,0,311,312,5,10,
  	0,0,312,347,1,0,0,0,313,317,5,8,0,0,314,316,3,52,26,0,315,314,1,0,0,0,
  	316,319,1,0,0,0,317,315,1,0,0,0,317,318,1,0,0,0,318,320,1,0,0,0,319,317,
  	1,0,0,0,320,347,5,9,0,0,321,323,5,34,0,0,322,324,3,54,27,0,323,322,1,
  	0,0,0,323,324,1,0,0,0,324,325,1,0,0,0,325,347,5,10,0,0,326,327,5,35,0,
  	0,327,328,5,20,0,0,328,329,3,54,27,0,329,330,5,21,0,0,330,333,3,52,26,
  	0,331,332,5,36,0,0,332,334,3,52,26,0,333,331,1,0,0,0,333,334,1,0,0,0,
  	334,347,1,0,0,0,335,336,5,37,0,0,336,337,5,20,0,0,337,338,3,54,27,0,338,
  	339,5,21,0,0,339,340,3,52,26,0,340,347,1,0,0,0,341,342,5,38,0,0,342,343,
  	5,20,0,0,343,344,5,50,0,0,344,345,5,21,0,0,345,347,3,52,26,0,346,300,
  	1,0,0,0,346,303,1,0,0,0,346,308,1,0,0,0,346,313,1,0,0,0,346,321,1,0,0,
  	0,346,326,1,0,0,0,346,335,1,0,0,0,346,341,1,0,0,0,347,53,1,0,0,0,348,
  	349,6,27,-1,0,349,398,5,46,0,0,350,398,5,47,0,0,351,398,5,48,0,0,352,
  	398,5,49,0,0,353,398,5,45,0,0,354,355,5,39,0,0,355,356,5,20,0,0,356,357,
  	3,24,12,0,357,358,5,21,0,0,358,398,1,0,0,0,359,360,5,39,0,0,360,361,5,
  	12,0,0,361,362,5,20,0,0,362,363,5,50,0,0,363,398,5,21,0,0,364,398,3,26,
  	13,0,365,398,3,22,11,0,366,367,5,20,0,0,367,368,3,24,12,0,368,369,5,21,
  	0,0,369,370,3,54,27,8,370,398,1,0,0,0,371,372,5,28,0,0,372,398,3,54,27,
  	3,373,374,5,20,0,0,374,375,3,54,27,0,375,376,5,21,0,0,376,398,1,0,0,0,
  	377,378,3,24,12,0,378,383,5,16,0,0,379,380,5,4,0,0,380,381,3,46,23,0,
  	381,382,5,6,0,0,382,384,1,0,0,0,383,379,1,0,0,0,383,384,1,0,0,0,384,385,
  	1,0,0,0,385,386,5,20,0,0,386,387,3,30,15,0,387,388,5,21,0,0,388,392,5,
  	8,0,0,389,391,3,52,26,0,390,389,1,0,0,0,391,394,1,0,0,0,392,390,1,0,0,
  	0,392,393,1,0,0,0,393,395,1,0,0,0,394,392,1,0,0,0,395,396,5,9,0,0,396,
  	398,1,0,0,0,397,348,1,0,0,0,397,350,1,0,0,0,397,351,1,0,0,0,397,352,1,
  	0,0,0,397,353,1,0,0,0,397,354,1,0,0,0,397,359,1,0,0,0,397,364,1,0,0,0,
  	397,365,1,0,0,0,397,366,1,0,0,0,397,371,1,0,0,0,397,373,1,0,0,0,397,377,
  	1,0,0,0,398,429,1,0,0,0,399,400,10,7,0,0,400,401,7,2,0,0,401,428,3,54,
  	27,8,402,403,10,6,0,0,403,404,7,3,0,0,404,428,3,54,27,7,405,406,10,5,
  	0,0,406,407,7,4,0,0,407,428,3,54,27,6,408,409,10,4,0,0,409,410,5,55,0,
  	0,410,428,3,54,27,5,411,412,10,12,0,0,412,413,5,20,0,0,413,414,3,34,17,
  	0,414,415,5,21,0,0,415,428,1,0,0,0,416,417,10,10,0,0,417,418,5,4,0,0,
  	418,419,3,54,27,0,419,420,5,6,0,0,420,428,1,0,0,0,421,422,10,9,0,0,422,
  	423,5,40,0,0,423,425,5,50,0,0,424,426,3,20,10,0,425,424,1,0,0,0,425,426,
  	1,0,0,0,426,428,1,0,0,0,427,399,1,0,0,0,427,402,1,0,0,0,427,405,1,0,0,
  	0,427,408,1,0,0,0,427,411,1,0,0,0,427,416,1,0,0,0,427,421,1,0,0,0,428,
  	431,1,0,0,0,429,427,1,0,0,0,429,430,1,0,0,0,430,55,1,0,0,0,431,429,1,
  	0,0,0,52,59,63,66,72,77,86,89,94,103,112,120,123,134,143,151,158,162,
  	165,168,179,186,189,194,201,204,210,213,216,219,226,228,232,239,249,255,
  	261,270,274,277,280,288,298,317,323,333,346,383,392,397,425,427,429
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


//----------------- ModulesContext ------------------------------------------------------------------

braneParser::ModulesContext::ModulesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::ModuleContext *> braneParser::ModulesContext::module() {
  return getRuleContexts<braneParser::ModuleContext>();
}

braneParser::ModuleContext* braneParser::ModulesContext::module(size_t i) {
  return getRuleContext<braneParser::ModuleContext>(i);
}

tree::TerminalNode* braneParser::ModulesContext::EOF() {
  return getToken(braneParser::EOF, 0);
}


size_t braneParser::ModulesContext::getRuleIndex() const {
  return braneParser::RuleModules;
}


std::any braneParser::ModulesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitModules(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ModulesContext* braneParser::modules() {
  ModulesContext *_localctx = _tracker.createInstance<ModulesContext>(_ctx, getState());
  enterRule(_localctx, 0, braneParser::RuleModules);
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
    setState(59);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__3

    || _la == braneParser::T__6) {
      setState(56);
      module();
      setState(61);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(63);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(62);
      match(braneParser::EOF);
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
  enterRule(_localctx, 2, braneParser::RuleLink);
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
    setState(66);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__0) {
      setState(65);
      antlrcpp::downCast<LinkContext *>(_localctx)->isPublic = match(braneParser::T__0);
    }
    setState(68);
    match(braneParser::T__1);
    setState(69);
    antlrcpp::downCast<LinkContext *>(_localctx)->library = match(braneParser::STRING);
    setState(72);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__2) {
      setState(70);
      match(braneParser::T__2);
      setState(71);
      antlrcpp::downCast<LinkContext *>(_localctx)->alias = match(braneParser::STRING);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LinkListContext ------------------------------------------------------------------

braneParser::LinkListContext::LinkListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::LinkContext *> braneParser::LinkListContext::link() {
  return getRuleContexts<braneParser::LinkContext>();
}

braneParser::LinkContext* braneParser::LinkListContext::link(size_t i) {
  return getRuleContext<braneParser::LinkContext>(i);
}


size_t braneParser::LinkListContext::getRuleIndex() const {
  return braneParser::RuleLinkList;
}


std::any braneParser::LinkListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitLinkList(this);
  else
    return visitor->visitChildren(this);
}

braneParser::LinkListContext* braneParser::linkList() {
  LinkListContext *_localctx = _tracker.createInstance<LinkListContext>(_ctx, getState());
  enterRule(_localctx, 4, braneParser::RuleLinkList);
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
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__0

    || _la == braneParser::T__1) {
      setState(74);
      link();
      setState(79);
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

//----------------- TagsContext ------------------------------------------------------------------

braneParser::TagsContext::TagsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> braneParser::TagsContext::STRING() {
  return getTokens(braneParser::STRING);
}

tree::TerminalNode* braneParser::TagsContext::STRING(size_t i) {
  return getToken(braneParser::STRING, i);
}


size_t braneParser::TagsContext::getRuleIndex() const {
  return braneParser::RuleTags;
}


std::any braneParser::TagsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitTags(this);
  else
    return visitor->visitChildren(this);
}

braneParser::TagsContext* braneParser::tags() {
  TagsContext *_localctx = _tracker.createInstance<TagsContext>(_ctx, getState());
  enterRule(_localctx, 6, braneParser::RuleTags);
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
    setState(80);
    match(braneParser::T__3);
    setState(89);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::STRING) {
      setState(81);
      antlrcpp::downCast<TagsContext *>(_localctx)->tag = match(braneParser::STRING);
      setState(86);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__4) {
        setState(82);
        match(braneParser::T__4);
        setState(83);
        antlrcpp::downCast<TagsContext *>(_localctx)->tag = match(braneParser::STRING);
        setState(88);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(91);
    match(braneParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModuleContext ------------------------------------------------------------------

braneParser::ModuleContext::ModuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::LinkListContext* braneParser::ModuleContext::linkList() {
  return getRuleContext<braneParser::LinkListContext>(0);
}

tree::TerminalNode* braneParser::ModuleContext::STRING() {
  return getToken(braneParser::STRING, 0);
}

std::vector<braneParser::ModuleComponentContext *> braneParser::ModuleContext::moduleComponent() {
  return getRuleContexts<braneParser::ModuleComponentContext>();
}

braneParser::ModuleComponentContext* braneParser::ModuleContext::moduleComponent(size_t i) {
  return getRuleContext<braneParser::ModuleComponentContext>(i);
}

braneParser::TagsContext* braneParser::ModuleContext::tags() {
  return getRuleContext<braneParser::TagsContext>(0);
}


size_t braneParser::ModuleContext::getRuleIndex() const {
  return braneParser::RuleModule;
}


std::any braneParser::ModuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitModule(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ModuleContext* braneParser::module() {
  ModuleContext *_localctx = _tracker.createInstance<ModuleContext>(_ctx, getState());
  enterRule(_localctx, 8, braneParser::RuleModule);
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
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(93);
      antlrcpp::downCast<ModuleContext *>(_localctx)->modTags = tags();
    }
    setState(96);
    match(braneParser::T__6);
    setState(97);
    antlrcpp::downCast<ModuleContext *>(_localctx)->id = match(braneParser::STRING);
    setState(98);
    linkList();
    setState(99);
    match(braneParser::T__7);
    setState(103);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1125903141511184) != 0)) {
      setState(100);
      moduleComponent();
      setState(105);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(106);
    match(braneParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModuleComponentContext ------------------------------------------------------------------

braneParser::ModuleComponentContext::ModuleComponentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::FunctionContext* braneParser::ModuleComponentContext::function() {
  return getRuleContext<braneParser::FunctionContext>(0);
}

braneParser::FunctionStubContext* braneParser::ModuleComponentContext::functionStub() {
  return getRuleContext<braneParser::FunctionStubContext>(0);
}

braneParser::StructDefContext* braneParser::ModuleComponentContext::structDef() {
  return getRuleContext<braneParser::StructDefContext>(0);
}

braneParser::GlobalContext* braneParser::ModuleComponentContext::global() {
  return getRuleContext<braneParser::GlobalContext>(0);
}


size_t braneParser::ModuleComponentContext::getRuleIndex() const {
  return braneParser::RuleModuleComponent;
}


std::any braneParser::ModuleComponentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitModuleComponent(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ModuleComponentContext* braneParser::moduleComponent() {
  ModuleComponentContext *_localctx = _tracker.createInstance<ModuleComponentContext>(_ctx, getState());
  enterRule(_localctx, 10, braneParser::RuleModuleComponent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(112);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(108);
      function();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(109);
      functionStub();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(110);
      structDef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(111);
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
  enterRule(_localctx, 12, braneParser::RuleGlobal);

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
    type();
    setState(115);
    antlrcpp::downCast<GlobalContext *>(_localctx)->id = match(braneParser::ID);
    setState(116);
    match(braneParser::T__9);
   
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
  enterRule(_localctx, 14, braneParser::RuleTemplateDefArgument);
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
    setState(120);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__15:
      case braneParser::T__17:
      case braneParser::T__18:
      case braneParser::ID: {
        setState(118);
        antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->exprType = type();
        break;
      }

      case braneParser::T__10: {
        setState(119);
        antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->isTypedef = match(braneParser::T__10);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(123);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__11) {
      setState(122);
      antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->isPack = match(braneParser::T__11);
    }
    setState(125);
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
  enterRule(_localctx, 16, braneParser::RuleTemplateDef);
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
    match(braneParser::T__12);
    setState(128);
    match(braneParser::T__13);
    setState(129);
    templateDefArgument();
    setState(134);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__4) {
      setState(130);
      match(braneParser::T__4);
      setState(131);
      templateDefArgument();
      setState(136);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(137);
    match(braneParser::T__14);
   
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
  enterRule(_localctx, 18, braneParser::RuleTemplateArg);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::TemplateTypeArgContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(139);
      antlrcpp::downCast<TemplateTypeArgContext *>(_localctx)->t = type();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::TemplateExprArgContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(140);
      antlrcpp::downCast<TemplateExprArgContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::PackExpansionArgContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(141);
      antlrcpp::downCast<PackExpansionArgContext *>(_localctx)->packID = match(braneParser::ID);
      setState(142);
      match(braneParser::T__11);
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
  enterRule(_localctx, 20, braneParser::RuleTemplateArgs);
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
    setState(145);
    match(braneParser::T__13);
    setState(146);
    templateArg();
    setState(151);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__4) {
      setState(147);
      match(braneParser::T__4);
      setState(148);
      templateArg();
      setState(153);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(154);
    match(braneParser::T__14);
   
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
  enterRule(_localctx, 22, braneParser::RuleScopedID);
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
    antlrcpp::downCast<ScopedIDContext *>(_localctx)->id = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == braneParser::T__15

    || _la == braneParser::ID)) {
      antlrcpp::downCast<ScopedIDContext *>(_localctx)->id = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(158);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(157);
      antlrcpp::downCast<ScopedIDContext *>(_localctx)->template_ = templateArgs();
      break;
    }

    default:
      break;
    }
    setState(162);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      setState(160);
      match(braneParser::T__16);
      setState(161);
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
  enterRule(_localctx, 24, braneParser::RuleType);
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
    setState(165);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__17) {
      setState(164);
      antlrcpp::downCast<TypeContext *>(_localctx)->isConst = match(braneParser::T__17);
    }
    setState(168);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__18) {
      setState(167);
      antlrcpp::downCast<TypeContext *>(_localctx)->isRef = match(braneParser::T__18);
    }
    setState(170);
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
  enterRule(_localctx, 26, braneParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(172);
    type();
    setState(173);
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
  enterRule(_localctx, 28, braneParser::RuleArgumentListItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(179);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(175);
      declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(176);
      antlrcpp::downCast<ArgumentListItemContext *>(_localctx)->pack = match(braneParser::ID);
      setState(177);
      match(braneParser::T__11);
      setState(178);
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
  enterRule(_localctx, 30, braneParser::RuleArgumentList);
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
    setState(189);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1125899907694592) != 0)) {
      setState(181);
      argumentListItem();
      setState(186);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__4) {
        setState(182);
        match(braneParser::T__4);
        setState(183);
        argumentListItem();
        setState(188);
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
  enterRule(_localctx, 32, braneParser::RuleArgumentPackItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(194);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(191);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(192);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->packID = match(braneParser::ID);
      setState(193);
      match(braneParser::T__11);
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
  enterRule(_localctx, 34, braneParser::RuleArgumentPack);
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
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2217165467746304) != 0)) {
      setState(196);
      argumentPackItem();
      setState(201);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__4) {
        setState(197);
        match(braneParser::T__4);
        setState(198);
        argumentPackItem();
        setState(203);
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

//----------------- BracketOprContext ------------------------------------------------------------------

braneParser::BracketOprContext::BracketOprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t braneParser::BracketOprContext::getRuleIndex() const {
  return braneParser::RuleBracketOpr;
}


std::any braneParser::BracketOprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitBracketOpr(this);
  else
    return visitor->visitChildren(this);
}

braneParser::BracketOprContext* braneParser::bracketOpr() {
  BracketOprContext *_localctx = _tracker.createInstance<BracketOprContext>(_ctx, getState());
  enterRule(_localctx, 36, braneParser::RuleBracketOpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(210);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__19: {
        enterOuterAlt(_localctx, 1);
        setState(206);
        match(braneParser::T__19);
        setState(207);
        match(braneParser::T__20);
        break;
      }

      case braneParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(208);
        match(braneParser::T__3);
        setState(209);
        match(braneParser::T__5);
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

//----------------- FunctionSigContext ------------------------------------------------------------------

braneParser::FunctionSigContext::FunctionSigContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::TagsContext* braneParser::FunctionSigContext::tags() {
  return getRuleContext<braneParser::TagsContext>(0);
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

braneParser::BracketOprContext* braneParser::FunctionSigContext::bracketOpr() {
  return getRuleContext<braneParser::BracketOprContext>(0);
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
  enterRule(_localctx, 38, braneParser::RuleFunctionSig);
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
    setState(213);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(212);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->funcTags = tags();
    }
    setState(216);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__12) {
      setState(215);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->template_ = templateDef();
    }
    setState(219);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__21) {
      setState(218);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->isConstexpr = match(braneParser::T__21);
    }
    setState(232);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__15:
      case braneParser::T__17:
      case braneParser::T__18:
      case braneParser::ID: {
        setState(221);
        type();
        setState(228);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case braneParser::ID: {
            setState(222);
            antlrcpp::downCast<FunctionSigContext *>(_localctx)->id = match(braneParser::ID);
            break;
          }

          case braneParser::T__22: {
            setState(223);
            match(braneParser::T__22);
            setState(226);
            _errHandler->sync(this);
            switch (_input->LA(1)) {
              case braneParser::T__13:
              case braneParser::T__14:
              case braneParser::T__23:
              case braneParser::T__24:
              case braneParser::T__25:
              case braneParser::T__26:
              case braneParser::T__27:
              case braneParser::MUL:
              case braneParser::DIV:
              case braneParser::ADD:
              case braneParser::SUB:
              case braneParser::LOGIC: {
                setState(224);
                antlrcpp::downCast<FunctionSigContext *>(_localctx)->oprID = _input->LT(1);
                _la = _input->LA(1);
                if (!((((_la & ~ 0x3fULL) == 0) &&
                  ((1ULL << _la) & 69805794744385536) != 0))) {
                  antlrcpp::downCast<FunctionSigContext *>(_localctx)->oprID = _errHandler->recoverInline(this);
                }
                else {
                  _errHandler->reportMatch(this);
                  consume();
                }
                break;
              }

              case braneParser::T__3:
              case braneParser::T__19: {
                setState(225);
                antlrcpp::downCast<FunctionSigContext *>(_localctx)->bracketOprID = bracketOpr();
                break;
              }

            default:
              throw NoViableAltException(this);
            }
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

      case braneParser::T__22: {
        setState(230);
        match(braneParser::T__22);
        setState(231);
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
  enterRule(_localctx, 40, braneParser::RuleFunctionStub);
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
    setState(234);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->sig = functionSig();
    setState(235);
    match(braneParser::T__19);
    setState(236);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->arguments = argumentList();
    setState(237);
    match(braneParser::T__20);
    setState(239);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__17) {
      setState(238);
      antlrcpp::downCast<FunctionStubContext *>(_localctx)->isConst = match(braneParser::T__17);
    }
    setState(241);
    match(braneParser::T__28);
    setState(242);
    match(braneParser::T__9);
   
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
  enterRule(_localctx, 42, braneParser::RuleFunction);
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
    setState(244);
    antlrcpp::downCast<FunctionContext *>(_localctx)->sig = functionSig();
    setState(245);
    match(braneParser::T__19);
    setState(246);
    antlrcpp::downCast<FunctionContext *>(_localctx)->arguments = argumentList();
    setState(247);
    match(braneParser::T__20);
    setState(249);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__17) {
      setState(248);
      antlrcpp::downCast<FunctionContext *>(_localctx)->isConst = match(braneParser::T__17);
    }
    setState(251);
    match(braneParser::T__7);
    setState(255);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2217629324214528) != 0)) {
      setState(252);
      antlrcpp::downCast<FunctionContext *>(_localctx)->statements = statement();
      setState(257);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(258);
    match(braneParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CapturedVarContext ------------------------------------------------------------------

braneParser::CapturedVarContext::CapturedVarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::ScopedIDContext* braneParser::CapturedVarContext::scopedID() {
  return getRuleContext<braneParser::ScopedIDContext>(0);
}


size_t braneParser::CapturedVarContext::getRuleIndex() const {
  return braneParser::RuleCapturedVar;
}


std::any braneParser::CapturedVarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitCapturedVar(this);
  else
    return visitor->visitChildren(this);
}

braneParser::CapturedVarContext* braneParser::capturedVar() {
  CapturedVarContext *_localctx = _tracker.createInstance<CapturedVarContext>(_ctx, getState());
  enterRule(_localctx, 44, braneParser::RuleCapturedVar);
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
    setState(261);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__18) {
      setState(260);
      antlrcpp::downCast<CapturedVarContext *>(_localctx)->isRef = match(braneParser::T__18);
    }
    setState(263);
    antlrcpp::downCast<CapturedVarContext *>(_localctx)->id = scopedID();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarCaptureContext ------------------------------------------------------------------

braneParser::VarCaptureContext::VarCaptureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::CapturedVarContext *> braneParser::VarCaptureContext::capturedVar() {
  return getRuleContexts<braneParser::CapturedVarContext>();
}

braneParser::CapturedVarContext* braneParser::VarCaptureContext::capturedVar(size_t i) {
  return getRuleContext<braneParser::CapturedVarContext>(i);
}


size_t braneParser::VarCaptureContext::getRuleIndex() const {
  return braneParser::RuleVarCapture;
}


std::any braneParser::VarCaptureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitVarCapture(this);
  else
    return visitor->visitChildren(this);
}

braneParser::VarCaptureContext* braneParser::varCapture() {
  VarCaptureContext *_localctx = _tracker.createInstance<VarCaptureContext>(_ctx, getState());
  enterRule(_localctx, 46, braneParser::RuleVarCapture);
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
    setState(265);
    capturedVar();
    setState(270);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__4) {
      setState(266);
      match(braneParser::T__4);
      setState(267);
      capturedVar();
      setState(272);
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

braneParser::TagsContext* braneParser::StructDefContext::tags() {
  return getRuleContext<braneParser::TagsContext>(0);
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
  enterRule(_localctx, 48, braneParser::RuleStructDef);
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
    setState(274);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(273);
      antlrcpp::downCast<StructDefContext *>(_localctx)->structTags = tags();
    }
    setState(277);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__12) {
      setState(276);
      antlrcpp::downCast<StructDefContext *>(_localctx)->template_ = templateDef();
    }
    setState(280);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__29) {
      setState(279);
      antlrcpp::downCast<StructDefContext *>(_localctx)->packed = match(braneParser::T__29);
    }
    setState(282);
    match(braneParser::T__30);
    setState(283);
    antlrcpp::downCast<StructDefContext *>(_localctx)->id = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == braneParser::T__15

    || _la == braneParser::ID)) {
      antlrcpp::downCast<StructDefContext *>(_localctx)->id = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(284);
    match(braneParser::T__7);
    setState(288);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1125899920285712) != 0)) {
      setState(285);
      antlrcpp::downCast<StructDefContext *>(_localctx)->memberVars = structMember();
      setState(290);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(291);
    match(braneParser::T__8);
   
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
  enterRule(_localctx, 50, braneParser::RuleStructMember);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(298);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::MemberFunctionStubContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(293);
      functionStub();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::MemberFunctionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(294);
      antlrcpp::downCast<MemberFunctionContext *>(_localctx)->func = function();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::MemberVariableContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(295);
      antlrcpp::downCast<MemberVariableContext *>(_localctx)->var = declaration();
      setState(296);
      match(braneParser::T__9);
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
  enterRule(_localctx, 52, braneParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(346);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::ExprStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(300);
      expression(0);
      setState(301);
      match(braneParser::T__9);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::AssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(303);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->lValue = expression(0);
      setState(304);
      match(braneParser::T__31);
      setState(305);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->rValue = expression(0);
      setState(306);
      match(braneParser::T__9);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::RefAssignmentContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(308);
      antlrcpp::downCast<RefAssignmentContext *>(_localctx)->lValue = expression(0);
      setState(309);
      match(braneParser::T__32);
      setState(310);
      antlrcpp::downCast<RefAssignmentContext *>(_localctx)->rValue = expression(0);
      setState(311);
      match(braneParser::T__9);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<braneParser::ScopeContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(313);
      match(braneParser::T__7);
      setState(317);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 2217629324214528) != 0)) {
        setState(314);
        statement();
        setState(319);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(320);
      match(braneParser::T__8);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<braneParser::ReturnContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(321);
      match(braneParser::T__33);
      setState(323);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 2217165467746304) != 0)) {
        setState(322);
        expression(0);
      }
      setState(325);
      match(braneParser::T__9);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<braneParser::IfContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(326);
      match(braneParser::T__34);
      setState(327);
      match(braneParser::T__19);
      setState(328);
      antlrcpp::downCast<IfContext *>(_localctx)->cond = expression(0);
      setState(329);
      match(braneParser::T__20);
      setState(330);
      antlrcpp::downCast<IfContext *>(_localctx)->operation = statement();
      setState(333);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
      case 1: {
        setState(331);
        match(braneParser::T__35);
        setState(332);
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
      setState(335);
      match(braneParser::T__36);
      setState(336);
      match(braneParser::T__19);
      setState(337);
      antlrcpp::downCast<WhileContext *>(_localctx)->cond = expression(0);
      setState(338);
      match(braneParser::T__20);
      setState(339);
      antlrcpp::downCast<WhileContext *>(_localctx)->operation = statement();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<braneParser::UnrollContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(341);
      match(braneParser::T__37);
      setState(342);
      match(braneParser::T__19);
      setState(343);
      antlrcpp::downCast<UnrollContext *>(_localctx)->id = match(braneParser::ID);
      setState(344);
      match(braneParser::T__20);
      setState(345);
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
//----------------- NotContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::NotContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::NotContext::NotContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::NotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitNot(this);
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
//----------------- LambdaContext ------------------------------------------------------------------

braneParser::TypeContext* braneParser::LambdaContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}

braneParser::ArgumentListContext* braneParser::LambdaContext::argumentList() {
  return getRuleContext<braneParser::ArgumentListContext>(0);
}

std::vector<braneParser::StatementContext *> braneParser::LambdaContext::statement() {
  return getRuleContexts<braneParser::StatementContext>();
}

braneParser::StatementContext* braneParser::LambdaContext::statement(size_t i) {
  return getRuleContext<braneParser::StatementContext>(i);
}

braneParser::VarCaptureContext* braneParser::LambdaContext::varCapture() {
  return getRuleContext<braneParser::VarCaptureContext>(0);
}

braneParser::LambdaContext::LambdaContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::LambdaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitLambda(this);
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
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, braneParser::RuleExpression, precedence);

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
    setState(397);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ConstIntContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(349);
      match(braneParser::INT);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ConstFloatContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(350);
      match(braneParser::FLOAT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ConstCharContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(351);
      match(braneParser::CHAR);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ConstStringContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(352);
      match(braneParser::STRING);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ConstBoolContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(353);
      match(braneParser::BOOL);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SizeOfTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(354);
      match(braneParser::T__38);
      setState(355);
      match(braneParser::T__19);
      setState(356);
      antlrcpp::downCast<SizeOfTypeContext *>(_localctx)->t = type();
      setState(357);
      match(braneParser::T__20);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SizeOfPackContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(359);
      match(braneParser::T__38);
      setState(360);
      match(braneParser::T__11);
      setState(361);
      match(braneParser::T__19);
      setState(362);
      antlrcpp::downCast<SizeOfPackContext *>(_localctx)->id = match(braneParser::ID);
      setState(363);
      match(braneParser::T__20);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<DeclContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(364);
      declaration();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<IdContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(365);
      scopedID();
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<CastContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(366);
      match(braneParser::T__19);
      setState(367);
      type();
      setState(368);
      match(braneParser::T__20);
      setState(369);
      expression(8);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<NotContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(371);
      match(braneParser::T__27);
      setState(372);
      antlrcpp::downCast<NotContext *>(_localctx)->value = expression(3);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<ParenContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(373);
      match(braneParser::T__19);
      setState(374);
      expression(0);
      setState(375);
      match(braneParser::T__20);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<LambdaContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(377);
      antlrcpp::downCast<LambdaContext *>(_localctx)->returnType = type();
      setState(378);
      antlrcpp::downCast<LambdaContext *>(_localctx)->label = match(braneParser::T__15);
      setState(383);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == braneParser::T__3) {
        setState(379);
        match(braneParser::T__3);
        setState(380);
        antlrcpp::downCast<LambdaContext *>(_localctx)->capture = varCapture();
        setState(381);
        match(braneParser::T__5);
      }
      setState(385);
      match(braneParser::T__19);
      setState(386);
      antlrcpp::downCast<LambdaContext *>(_localctx)->arguments = argumentList();
      setState(387);
      match(braneParser::T__20);
      setState(388);
      match(braneParser::T__7);
      setState(392);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 2217629324214528) != 0)) {
        setState(389);
        statement();
        setState(394);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(395);
      match(braneParser::T__8);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(429);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(427);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MuldivContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(399);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(400);
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
          setState(401);
          antlrcpp::downCast<MuldivContext *>(_localctx)->right = expression(8);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddsubContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(402);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(403);
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
          setState(404);
          antlrcpp::downCast<AddsubContext *>(_localctx)->right = expression(7);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ComparisonContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(405);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(406);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->opr = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 251707392) != 0))) {
            antlrcpp::downCast<ComparisonContext *>(_localctx)->opr = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(407);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->right = expression(6);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<LogicContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(408);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(409);
          antlrcpp::downCast<LogicContext *>(_localctx)->opr = match(braneParser::LOGIC);
          setState(410);
          antlrcpp::downCast<LogicContext *>(_localctx)->right = expression(5);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<FunctionCallContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->overrides = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(411);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(412);
          match(braneParser::T__19);
          setState(413);
          argumentPack();
          setState(414);
          match(braneParser::T__20);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<IndexAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(416);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(417);
          match(braneParser::T__3);
          setState(418);
          antlrcpp::downCast<IndexAccessContext *>(_localctx)->arg = expression(0);
          setState(419);
          match(braneParser::T__5);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(421);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(422);
          match(braneParser::T__39);
          setState(423);
          antlrcpp::downCast<MemberAccessContext *>(_localctx)->member = match(braneParser::ID);
          setState(425);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
          case 1: {
            setState(424);
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
      setState(431);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
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
    case 27: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool braneParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 7);
    case 1: return precpred(_ctx, 6);
    case 2: return precpred(_ctx, 5);
    case 3: return precpred(_ctx, 4);
    case 4: return precpred(_ctx, 12);
    case 5: return precpred(_ctx, 10);
    case 6: return precpred(_ctx, 9);

  default:
    break;
  }
  return true;
}

void braneParser::initialize() {
  ::antlr4::internal::call_once(braneParserOnceFlag, braneParserInitialize);
}

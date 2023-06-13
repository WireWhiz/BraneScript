
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
      "'struct'", "'return'", "'if'", "'else'", "'while'", "'for'", "'sizeof'", 
      "'.'", "'++'", "'--'", "'='", "'<-'", "", "", "", "", "", "", "", 
      "", "", "", "'*'", "'/'", "'+'", "'-'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "COMMENT", "NEWLINE", "BLOCK_COMMENT", 
      "SPACE", "BOOL", "INT", "FLOAT", "CHAR", "STRING", "ID", "MUL", "DIV", 
      "ADD", "SUB", "LOGIC"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,57,456,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,1,0,5,
  	0,58,8,0,10,0,12,0,61,9,0,1,0,3,0,64,8,0,1,1,3,1,67,8,1,1,1,1,1,1,1,1,
  	1,3,1,73,8,1,1,2,5,2,76,8,2,10,2,12,2,79,9,2,1,3,1,3,1,3,1,3,5,3,85,8,
  	3,10,3,12,3,88,9,3,3,3,90,8,3,1,3,1,3,1,4,3,4,95,8,4,1,4,1,4,1,4,1,4,
  	1,4,5,4,102,8,4,10,4,12,4,105,9,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,3,5,
  	115,8,5,1,6,1,6,1,6,1,6,1,7,1,7,3,7,123,8,7,1,7,3,7,126,8,7,1,7,1,7,1,
  	8,1,8,1,8,1,8,1,8,5,8,135,8,8,10,8,12,8,138,9,8,1,8,1,8,1,9,1,9,1,9,1,
  	9,3,9,146,8,9,1,10,1,10,1,10,1,10,5,10,152,8,10,10,10,12,10,155,9,10,
  	1,10,1,10,1,11,1,11,3,11,161,8,11,1,11,1,11,3,11,165,8,11,1,12,3,12,168,
  	8,12,1,12,1,12,1,12,1,12,3,12,174,8,12,1,12,3,12,177,8,12,1,12,1,12,1,
  	13,1,13,1,13,1,14,1,14,1,14,1,14,3,14,188,8,14,1,15,1,15,1,15,5,15,193,
  	8,15,10,15,12,15,196,9,15,3,15,198,8,15,1,16,1,16,1,16,3,16,203,8,16,
  	1,17,1,17,1,17,5,17,208,8,17,10,17,12,17,211,9,17,3,17,213,8,17,1,18,
  	1,18,1,18,1,18,3,18,219,8,18,1,19,3,19,222,8,19,1,19,3,19,225,8,19,1,
  	19,3,19,228,8,19,1,19,1,19,1,19,1,19,1,19,3,19,235,8,19,3,19,237,8,19,
  	1,19,1,19,3,19,241,8,19,1,20,1,20,1,20,1,20,1,20,3,20,248,8,20,1,20,1,
  	20,1,21,1,21,1,21,1,21,1,21,3,21,257,8,21,1,21,1,21,5,21,261,8,21,10,
  	21,12,21,264,9,21,1,21,1,21,1,22,3,22,269,8,22,1,22,1,22,1,23,1,23,1,
  	23,5,23,276,8,23,10,23,12,23,279,9,23,1,24,3,24,282,8,24,1,24,3,24,285,
  	8,24,1,24,3,24,288,8,24,1,24,1,24,1,24,1,24,5,24,294,8,24,10,24,12,24,
  	297,9,24,1,24,1,24,1,25,1,25,1,25,1,25,1,25,1,25,1,25,3,25,308,8,25,1,
  	26,1,26,1,26,1,26,1,26,5,26,315,8,26,10,26,12,26,318,9,26,1,26,1,26,1,
  	26,3,26,323,8,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,3,26,333,8,26,
  	1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,3,26,344,8,26,1,26,1,26,
  	1,26,1,26,3,26,350,8,26,1,26,1,26,1,26,1,26,3,26,356,8,26,1,27,1,27,1,
  	27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,
  	27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,
  	27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,397,8,27,1,27,1,27,1,
  	27,1,27,1,27,5,27,404,8,27,10,27,12,27,407,9,27,1,27,1,27,3,27,411,8,
  	27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,
  	27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,
  	27,1,27,1,27,1,27,1,27,3,27,445,8,27,1,27,1,27,1,27,1,27,5,27,451,8,27,
  	10,27,12,27,454,9,27,1,27,0,1,54,28,0,2,4,6,8,10,12,14,16,18,20,22,24,
  	26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,0,5,2,0,16,16,52,52,3,0,
  	14,15,24,28,53,57,1,0,53,54,1,0,55,56,2,0,14,15,24,27,514,0,59,1,0,0,
  	0,2,66,1,0,0,0,4,77,1,0,0,0,6,80,1,0,0,0,8,94,1,0,0,0,10,114,1,0,0,0,
  	12,116,1,0,0,0,14,122,1,0,0,0,16,129,1,0,0,0,18,145,1,0,0,0,20,147,1,
  	0,0,0,22,158,1,0,0,0,24,167,1,0,0,0,26,180,1,0,0,0,28,187,1,0,0,0,30,
  	197,1,0,0,0,32,202,1,0,0,0,34,212,1,0,0,0,36,218,1,0,0,0,38,221,1,0,0,
  	0,40,242,1,0,0,0,42,251,1,0,0,0,44,268,1,0,0,0,46,272,1,0,0,0,48,281,
  	1,0,0,0,50,307,1,0,0,0,52,355,1,0,0,0,54,410,1,0,0,0,56,58,3,8,4,0,57,
  	56,1,0,0,0,58,61,1,0,0,0,59,57,1,0,0,0,59,60,1,0,0,0,60,63,1,0,0,0,61,
  	59,1,0,0,0,62,64,5,0,0,1,63,62,1,0,0,0,63,64,1,0,0,0,64,1,1,0,0,0,65,
  	67,5,1,0,0,66,65,1,0,0,0,66,67,1,0,0,0,67,68,1,0,0,0,68,69,5,2,0,0,69,
  	72,5,51,0,0,70,71,5,3,0,0,71,73,5,51,0,0,72,70,1,0,0,0,72,73,1,0,0,0,
  	73,3,1,0,0,0,74,76,3,2,1,0,75,74,1,0,0,0,76,79,1,0,0,0,77,75,1,0,0,0,
  	77,78,1,0,0,0,78,5,1,0,0,0,79,77,1,0,0,0,80,89,5,4,0,0,81,86,5,51,0,0,
  	82,83,5,5,0,0,83,85,5,51,0,0,84,82,1,0,0,0,85,88,1,0,0,0,86,84,1,0,0,
  	0,86,87,1,0,0,0,87,90,1,0,0,0,88,86,1,0,0,0,89,81,1,0,0,0,89,90,1,0,0,
  	0,90,91,1,0,0,0,91,92,5,6,0,0,92,7,1,0,0,0,93,95,3,6,3,0,94,93,1,0,0,
  	0,94,95,1,0,0,0,95,96,1,0,0,0,96,97,5,7,0,0,97,98,5,51,0,0,98,99,3,4,
  	2,0,99,103,5,8,0,0,100,102,3,10,5,0,101,100,1,0,0,0,102,105,1,0,0,0,103,
  	101,1,0,0,0,103,104,1,0,0,0,104,106,1,0,0,0,105,103,1,0,0,0,106,107,5,
  	9,0,0,107,9,1,0,0,0,108,115,3,42,21,0,109,110,3,40,20,0,110,111,5,10,
  	0,0,111,115,1,0,0,0,112,115,3,48,24,0,113,115,3,12,6,0,114,108,1,0,0,
  	0,114,109,1,0,0,0,114,112,1,0,0,0,114,113,1,0,0,0,115,11,1,0,0,0,116,
  	117,3,24,12,0,117,118,5,52,0,0,118,119,5,10,0,0,119,13,1,0,0,0,120,123,
  	3,24,12,0,121,123,5,11,0,0,122,120,1,0,0,0,122,121,1,0,0,0,123,125,1,
  	0,0,0,124,126,5,12,0,0,125,124,1,0,0,0,125,126,1,0,0,0,126,127,1,0,0,
  	0,127,128,5,52,0,0,128,15,1,0,0,0,129,130,5,13,0,0,130,131,5,14,0,0,131,
  	136,3,14,7,0,132,133,5,5,0,0,133,135,3,14,7,0,134,132,1,0,0,0,135,138,
  	1,0,0,0,136,134,1,0,0,0,136,137,1,0,0,0,137,139,1,0,0,0,138,136,1,0,0,
  	0,139,140,5,15,0,0,140,17,1,0,0,0,141,146,3,24,12,0,142,146,3,54,27,0,
  	143,144,5,52,0,0,144,146,5,12,0,0,145,141,1,0,0,0,145,142,1,0,0,0,145,
  	143,1,0,0,0,146,19,1,0,0,0,147,148,5,14,0,0,148,153,3,18,9,0,149,150,
  	5,5,0,0,150,152,3,18,9,0,151,149,1,0,0,0,152,155,1,0,0,0,153,151,1,0,
  	0,0,153,154,1,0,0,0,154,156,1,0,0,0,155,153,1,0,0,0,156,157,5,15,0,0,
  	157,21,1,0,0,0,158,160,7,0,0,0,159,161,3,20,10,0,160,159,1,0,0,0,160,
  	161,1,0,0,0,161,164,1,0,0,0,162,163,5,17,0,0,163,165,3,22,11,0,164,162,
  	1,0,0,0,164,165,1,0,0,0,165,23,1,0,0,0,166,168,5,18,0,0,167,166,1,0,0,
  	0,167,168,1,0,0,0,168,176,1,0,0,0,169,177,5,19,0,0,170,171,5,19,0,0,171,
  	173,5,4,0,0,172,174,5,48,0,0,173,172,1,0,0,0,173,174,1,0,0,0,174,175,
  	1,0,0,0,175,177,5,6,0,0,176,169,1,0,0,0,176,170,1,0,0,0,176,177,1,0,0,
  	0,177,178,1,0,0,0,178,179,3,22,11,0,179,25,1,0,0,0,180,181,3,24,12,0,
  	181,182,5,52,0,0,182,27,1,0,0,0,183,188,3,26,13,0,184,185,5,52,0,0,185,
  	186,5,12,0,0,186,188,5,52,0,0,187,183,1,0,0,0,187,184,1,0,0,0,188,29,
  	1,0,0,0,189,194,3,28,14,0,190,191,5,5,0,0,191,193,3,28,14,0,192,190,1,
  	0,0,0,193,196,1,0,0,0,194,192,1,0,0,0,194,195,1,0,0,0,195,198,1,0,0,0,
  	196,194,1,0,0,0,197,189,1,0,0,0,197,198,1,0,0,0,198,31,1,0,0,0,199,203,
  	3,54,27,0,200,201,5,52,0,0,201,203,5,12,0,0,202,199,1,0,0,0,202,200,1,
  	0,0,0,203,33,1,0,0,0,204,209,3,32,16,0,205,206,5,5,0,0,206,208,3,32,16,
  	0,207,205,1,0,0,0,208,211,1,0,0,0,209,207,1,0,0,0,209,210,1,0,0,0,210,
  	213,1,0,0,0,211,209,1,0,0,0,212,204,1,0,0,0,212,213,1,0,0,0,213,35,1,
  	0,0,0,214,215,5,20,0,0,215,219,5,21,0,0,216,217,5,4,0,0,217,219,5,6,0,
  	0,218,214,1,0,0,0,218,216,1,0,0,0,219,37,1,0,0,0,220,222,3,6,3,0,221,
  	220,1,0,0,0,221,222,1,0,0,0,222,224,1,0,0,0,223,225,3,16,8,0,224,223,
  	1,0,0,0,224,225,1,0,0,0,225,227,1,0,0,0,226,228,5,22,0,0,227,226,1,0,
  	0,0,227,228,1,0,0,0,228,240,1,0,0,0,229,236,3,24,12,0,230,237,5,52,0,
  	0,231,234,5,23,0,0,232,235,7,1,0,0,233,235,3,36,18,0,234,232,1,0,0,0,
  	234,233,1,0,0,0,235,237,1,0,0,0,236,230,1,0,0,0,236,231,1,0,0,0,237,241,
  	1,0,0,0,238,239,5,23,0,0,239,241,3,24,12,0,240,229,1,0,0,0,240,238,1,
  	0,0,0,241,39,1,0,0,0,242,243,3,38,19,0,243,244,5,20,0,0,244,245,3,30,
  	15,0,245,247,5,21,0,0,246,248,5,18,0,0,247,246,1,0,0,0,247,248,1,0,0,
  	0,248,249,1,0,0,0,249,250,5,29,0,0,250,41,1,0,0,0,251,252,3,38,19,0,252,
  	253,5,20,0,0,253,254,3,30,15,0,254,256,5,21,0,0,255,257,5,18,0,0,256,
  	255,1,0,0,0,256,257,1,0,0,0,257,258,1,0,0,0,258,262,5,8,0,0,259,261,3,
  	52,26,0,260,259,1,0,0,0,261,264,1,0,0,0,262,260,1,0,0,0,262,263,1,0,0,
  	0,263,265,1,0,0,0,264,262,1,0,0,0,265,266,5,9,0,0,266,43,1,0,0,0,267,
  	269,5,19,0,0,268,267,1,0,0,0,268,269,1,0,0,0,269,270,1,0,0,0,270,271,
  	3,22,11,0,271,45,1,0,0,0,272,277,3,44,22,0,273,274,5,5,0,0,274,276,3,
  	44,22,0,275,273,1,0,0,0,276,279,1,0,0,0,277,275,1,0,0,0,277,278,1,0,0,
  	0,278,47,1,0,0,0,279,277,1,0,0,0,280,282,3,6,3,0,281,280,1,0,0,0,281,
  	282,1,0,0,0,282,284,1,0,0,0,283,285,3,16,8,0,284,283,1,0,0,0,284,285,
  	1,0,0,0,285,287,1,0,0,0,286,288,5,30,0,0,287,286,1,0,0,0,287,288,1,0,
  	0,0,288,289,1,0,0,0,289,290,5,31,0,0,290,291,7,0,0,0,291,295,5,8,0,0,
  	292,294,3,50,25,0,293,292,1,0,0,0,294,297,1,0,0,0,295,293,1,0,0,0,295,
  	296,1,0,0,0,296,298,1,0,0,0,297,295,1,0,0,0,298,299,5,9,0,0,299,49,1,
  	0,0,0,300,301,3,40,20,0,301,302,5,10,0,0,302,308,1,0,0,0,303,308,3,42,
  	21,0,304,305,3,26,13,0,305,306,5,10,0,0,306,308,1,0,0,0,307,300,1,0,0,
  	0,307,303,1,0,0,0,307,304,1,0,0,0,308,51,1,0,0,0,309,310,3,54,27,0,310,
  	311,5,10,0,0,311,356,1,0,0,0,312,316,5,8,0,0,313,315,3,52,26,0,314,313,
  	1,0,0,0,315,318,1,0,0,0,316,314,1,0,0,0,316,317,1,0,0,0,317,319,1,0,0,
  	0,318,316,1,0,0,0,319,356,5,9,0,0,320,322,5,32,0,0,321,323,3,54,27,0,
  	322,321,1,0,0,0,322,323,1,0,0,0,323,324,1,0,0,0,324,356,5,10,0,0,325,
  	326,5,33,0,0,326,327,5,20,0,0,327,328,3,54,27,0,328,329,5,21,0,0,329,
  	332,3,52,26,0,330,331,5,34,0,0,331,333,3,52,26,0,332,330,1,0,0,0,332,
  	333,1,0,0,0,333,356,1,0,0,0,334,335,5,35,0,0,335,336,5,20,0,0,336,337,
  	3,54,27,0,337,338,5,21,0,0,338,339,3,52,26,0,339,356,1,0,0,0,340,341,
  	5,36,0,0,341,343,5,20,0,0,342,344,3,54,27,0,343,342,1,0,0,0,343,344,1,
  	0,0,0,344,345,1,0,0,0,345,346,5,10,0,0,346,347,3,54,27,0,347,349,5,10,
  	0,0,348,350,3,54,27,0,349,348,1,0,0,0,349,350,1,0,0,0,350,351,1,0,0,0,
  	351,352,5,21,0,0,352,353,3,52,26,0,353,356,1,0,0,0,354,356,5,10,0,0,355,
  	309,1,0,0,0,355,312,1,0,0,0,355,320,1,0,0,0,355,325,1,0,0,0,355,334,1,
  	0,0,0,355,340,1,0,0,0,355,354,1,0,0,0,356,53,1,0,0,0,357,358,6,27,-1,
  	0,358,411,5,48,0,0,359,411,5,49,0,0,360,411,5,50,0,0,361,411,5,51,0,0,
  	362,411,5,47,0,0,363,364,5,37,0,0,364,365,5,20,0,0,365,366,3,24,12,0,
  	366,367,5,21,0,0,367,411,1,0,0,0,368,369,5,37,0,0,369,370,5,12,0,0,370,
  	371,5,20,0,0,371,372,5,52,0,0,372,411,5,21,0,0,373,411,3,26,13,0,374,
  	411,3,22,11,0,375,376,5,20,0,0,376,377,3,24,12,0,377,378,5,21,0,0,378,
  	379,3,54,27,14,379,411,1,0,0,0,380,381,5,39,0,0,381,411,3,54,27,13,382,
  	383,5,40,0,0,383,411,3,54,27,12,384,385,5,28,0,0,385,411,3,54,27,5,386,
  	387,5,20,0,0,387,388,3,54,27,0,388,389,5,21,0,0,389,411,1,0,0,0,390,391,
  	3,24,12,0,391,396,5,16,0,0,392,393,5,4,0,0,393,394,3,46,23,0,394,395,
  	5,6,0,0,395,397,1,0,0,0,396,392,1,0,0,0,396,397,1,0,0,0,397,398,1,0,0,
  	0,398,399,5,20,0,0,399,400,3,30,15,0,400,401,5,21,0,0,401,405,5,8,0,0,
  	402,404,3,52,26,0,403,402,1,0,0,0,404,407,1,0,0,0,405,403,1,0,0,0,405,
  	406,1,0,0,0,406,408,1,0,0,0,407,405,1,0,0,0,408,409,5,9,0,0,409,411,1,
  	0,0,0,410,357,1,0,0,0,410,359,1,0,0,0,410,360,1,0,0,0,410,361,1,0,0,0,
  	410,362,1,0,0,0,410,363,1,0,0,0,410,368,1,0,0,0,410,373,1,0,0,0,410,374,
  	1,0,0,0,410,375,1,0,0,0,410,380,1,0,0,0,410,382,1,0,0,0,410,384,1,0,0,
  	0,410,386,1,0,0,0,410,390,1,0,0,0,411,452,1,0,0,0,412,413,10,9,0,0,413,
  	414,7,2,0,0,414,451,3,54,27,10,415,416,10,8,0,0,416,417,7,3,0,0,417,451,
  	3,54,27,9,418,419,10,7,0,0,419,420,7,4,0,0,420,451,3,54,27,8,421,422,
  	10,6,0,0,422,423,5,57,0,0,423,451,3,54,27,7,424,425,10,2,0,0,425,426,
  	5,41,0,0,426,451,3,54,27,3,427,428,10,1,0,0,428,429,5,42,0,0,429,451,
  	3,54,27,2,430,431,10,18,0,0,431,432,5,20,0,0,432,433,3,34,17,0,433,434,
  	5,21,0,0,434,451,1,0,0,0,435,436,10,16,0,0,436,437,5,4,0,0,437,438,3,
  	54,27,0,438,439,5,6,0,0,439,451,1,0,0,0,440,441,10,15,0,0,441,442,5,38,
  	0,0,442,444,5,52,0,0,443,445,3,20,10,0,444,443,1,0,0,0,444,445,1,0,0,
  	0,445,451,1,0,0,0,446,447,10,11,0,0,447,451,5,39,0,0,448,449,10,10,0,
  	0,449,451,5,40,0,0,450,412,1,0,0,0,450,415,1,0,0,0,450,418,1,0,0,0,450,
  	421,1,0,0,0,450,424,1,0,0,0,450,427,1,0,0,0,450,430,1,0,0,0,450,435,1,
  	0,0,0,450,440,1,0,0,0,450,446,1,0,0,0,450,448,1,0,0,0,451,454,1,0,0,0,
  	452,450,1,0,0,0,452,453,1,0,0,0,453,55,1,0,0,0,454,452,1,0,0,0,55,59,
  	63,66,72,77,86,89,94,103,114,122,125,136,145,153,160,164,167,173,176,
  	187,194,197,202,209,212,218,221,224,227,234,236,240,247,256,262,268,277,
  	281,284,287,295,307,316,322,332,343,349,355,396,405,410,444,450,452
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
      ((1ULL << _la) & 4503602862039056) != 0)) {
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
    setState(114);
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
      setState(110);
      match(braneParser::T__9);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(112);
      structDef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(113);
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
    setState(116);
    type();
    setState(117);
    antlrcpp::downCast<GlobalContext *>(_localctx)->id = match(braneParser::ID);
    setState(118);
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
    setState(122);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__15:
      case braneParser::T__17:
      case braneParser::T__18:
      case braneParser::ID: {
        setState(120);
        antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->exprType = type();
        break;
      }

      case braneParser::T__10: {
        setState(121);
        antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->isTypedef = match(braneParser::T__10);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(125);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__11) {
      setState(124);
      antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->isPack = match(braneParser::T__11);
    }
    setState(127);
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
    setState(129);
    match(braneParser::T__12);
    setState(130);
    match(braneParser::T__13);
    setState(131);
    templateDefArgument();
    setState(136);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__4) {
      setState(132);
      match(braneParser::T__4);
      setState(133);
      templateDefArgument();
      setState(138);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(139);
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
    setState(145);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::TemplateTypeArgContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(141);
      antlrcpp::downCast<TemplateTypeArgContext *>(_localctx)->t = type();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::TemplateExprArgContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(142);
      antlrcpp::downCast<TemplateExprArgContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::PackExpansionArgContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(143);
      antlrcpp::downCast<PackExpansionArgContext *>(_localctx)->packID = match(braneParser::ID);
      setState(144);
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
    setState(147);
    match(braneParser::T__13);
    setState(148);
    templateArg();
    setState(153);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__4) {
      setState(149);
      match(braneParser::T__4);
      setState(150);
      templateArg();
      setState(155);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(156);
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
    setState(158);
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
    setState(160);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(159);
      antlrcpp::downCast<ScopedIDContext *>(_localctx)->template_ = templateArgs();
      break;
    }

    default:
      break;
    }
    setState(164);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      setState(162);
      match(braneParser::T__16);
      setState(163);
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

tree::TerminalNode* braneParser::TypeContext::INT() {
  return getToken(braneParser::INT, 0);
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
    setState(167);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__17) {
      setState(166);
      antlrcpp::downCast<TypeContext *>(_localctx)->isConst = match(braneParser::T__17);
    }
    setState(176);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(169);
      antlrcpp::downCast<TypeContext *>(_localctx)->isRef = match(braneParser::T__18);
      break;
    }

    case 2: {
      setState(170);
      antlrcpp::downCast<TypeContext *>(_localctx)->isArrayRef = match(braneParser::T__18);
      setState(171);
      match(braneParser::T__3);
      setState(173);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == braneParser::INT) {
        setState(172);
        antlrcpp::downCast<TypeContext *>(_localctx)->size = match(braneParser::INT);
      }
      setState(175);
      match(braneParser::T__5);
      break;
    }

    default:
      break;
    }
    setState(178);
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
    setState(180);
    type();
    setState(181);
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
    setState(187);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(183);
      declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(184);
      antlrcpp::downCast<ArgumentListItemContext *>(_localctx)->pack = match(braneParser::ID);
      setState(185);
      match(braneParser::T__11);
      setState(186);
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
    setState(197);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503599628222464) != 0)) {
      setState(189);
      argumentListItem();
      setState(194);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__4) {
        setState(190);
        match(braneParser::T__4);
        setState(191);
        argumentListItem();
        setState(196);
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
    setState(202);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(199);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(200);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->packID = match(braneParser::ID);
      setState(201);
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
    setState(212);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8868248743116800) != 0)) {
      setState(204);
      argumentPackItem();
      setState(209);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__4) {
        setState(205);
        match(braneParser::T__4);
        setState(206);
        argumentPackItem();
        setState(211);
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
    setState(218);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__19: {
        enterOuterAlt(_localctx, 1);
        setState(214);
        match(braneParser::T__19);
        setState(215);
        match(braneParser::T__20);
        break;
      }

      case braneParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(216);
        match(braneParser::T__3);
        setState(217);
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
    setState(221);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(220);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->funcTags = tags();
    }
    setState(224);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__12) {
      setState(223);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->template_ = templateDef();
    }
    setState(227);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__21) {
      setState(226);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->isConstexpr = match(braneParser::T__21);
    }
    setState(240);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__15:
      case braneParser::T__17:
      case braneParser::T__18:
      case braneParser::ID: {
        setState(229);
        type();
        setState(236);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case braneParser::ID: {
            setState(230);
            antlrcpp::downCast<FunctionSigContext *>(_localctx)->id = match(braneParser::ID);
            break;
          }

          case braneParser::T__22: {
            setState(231);
            match(braneParser::T__22);
            setState(234);
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
                setState(232);
                antlrcpp::downCast<FunctionSigContext *>(_localctx)->oprID = _input->LT(1);
                _la = _input->LA(1);
                if (!((((_la & ~ 0x3fULL) == 0) &&
                  ((1ULL << _la) & 279223177417113600) != 0))) {
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
                setState(233);
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
        setState(238);
        match(braneParser::T__22);
        setState(239);
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
    setState(242);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->sig = functionSig();
    setState(243);
    match(braneParser::T__19);
    setState(244);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->arguments = argumentList();
    setState(245);
    match(braneParser::T__20);
    setState(247);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__17) {
      setState(246);
      antlrcpp::downCast<FunctionStubContext *>(_localctx)->isConst = match(braneParser::T__17);
    }
    setState(249);
    match(braneParser::T__28);
   
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
    setState(251);
    antlrcpp::downCast<FunctionContext *>(_localctx)->sig = functionSig();
    setState(252);
    match(braneParser::T__19);
    setState(253);
    antlrcpp::downCast<FunctionContext *>(_localctx)->arguments = argumentList();
    setState(254);
    match(braneParser::T__20);
    setState(256);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__17) {
      setState(255);
      antlrcpp::downCast<FunctionContext *>(_localctx)->isConst = match(braneParser::T__17);
    }
    setState(258);
    match(braneParser::T__7);
    setState(262);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8868364707235072) != 0)) {
      setState(259);
      antlrcpp::downCast<FunctionContext *>(_localctx)->statements = statement();
      setState(264);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(265);
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
    setState(268);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__18) {
      setState(267);
      antlrcpp::downCast<CapturedVarContext *>(_localctx)->isRef = match(braneParser::T__18);
    }
    setState(270);
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
    setState(272);
    capturedVar();
    setState(277);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__4) {
      setState(273);
      match(braneParser::T__4);
      setState(274);
      capturedVar();
      setState(279);
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
    setState(281);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(280);
      antlrcpp::downCast<StructDefContext *>(_localctx)->structTags = tags();
    }
    setState(284);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__12) {
      setState(283);
      antlrcpp::downCast<StructDefContext *>(_localctx)->template_ = templateDef();
    }
    setState(287);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__29) {
      setState(286);
      antlrcpp::downCast<StructDefContext *>(_localctx)->packed = match(braneParser::T__29);
    }
    setState(289);
    match(braneParser::T__30);
    setState(290);
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
    setState(291);
    match(braneParser::T__7);
    setState(295);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503599640813584) != 0)) {
      setState(292);
      antlrcpp::downCast<StructDefContext *>(_localctx)->memberVars = structMember();
      setState(297);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(298);
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
    setState(307);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::MemberFunctionStubContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(300);
      functionStub();
      setState(301);
      match(braneParser::T__9);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::MemberFunctionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(303);
      antlrcpp::downCast<MemberFunctionContext *>(_localctx)->func = function();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::MemberVariableContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(304);
      antlrcpp::downCast<MemberVariableContext *>(_localctx)->var = declaration();
      setState(305);
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
//----------------- ForContext ------------------------------------------------------------------

std::vector<braneParser::ExpressionContext *> braneParser::ForContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::ForContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}

braneParser::StatementContext* braneParser::ForContext::statement() {
  return getRuleContext<braneParser::StatementContext>(0);
}

braneParser::ForContext::ForContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::ForContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitFor(this);
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
//----------------- EmptyContext ------------------------------------------------------------------

braneParser::EmptyContext::EmptyContext(StatementContext *ctx) { copyFrom(ctx); }


std::any braneParser::EmptyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitEmpty(this);
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
    setState(355);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__15:
      case braneParser::T__17:
      case braneParser::T__18:
      case braneParser::T__19:
      case braneParser::T__27:
      case braneParser::T__36:
      case braneParser::T__38:
      case braneParser::T__39:
      case braneParser::BOOL:
      case braneParser::INT:
      case braneParser::FLOAT:
      case braneParser::CHAR:
      case braneParser::STRING:
      case braneParser::ID: {
        _localctx = _tracker.createInstance<braneParser::ExprStatementContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(309);
        expression(0);
        setState(310);
        match(braneParser::T__9);
        break;
      }

      case braneParser::T__7: {
        _localctx = _tracker.createInstance<braneParser::ScopeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(312);
        match(braneParser::T__7);
        setState(316);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 8868364707235072) != 0)) {
          setState(313);
          statement();
          setState(318);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(319);
        match(braneParser::T__8);
        break;
      }

      case braneParser::T__31: {
        _localctx = _tracker.createInstance<braneParser::ReturnContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(320);
        match(braneParser::T__31);
        setState(322);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 8868248743116800) != 0)) {
          setState(321);
          expression(0);
        }
        setState(324);
        match(braneParser::T__9);
        break;
      }

      case braneParser::T__32: {
        _localctx = _tracker.createInstance<braneParser::IfContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(325);
        match(braneParser::T__32);
        setState(326);
        match(braneParser::T__19);
        setState(327);
        antlrcpp::downCast<IfContext *>(_localctx)->cond = expression(0);
        setState(328);
        match(braneParser::T__20);
        setState(329);
        antlrcpp::downCast<IfContext *>(_localctx)->operation = statement();
        setState(332);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
        case 1: {
          setState(330);
          match(braneParser::T__33);
          setState(331);
          antlrcpp::downCast<IfContext *>(_localctx)->elseOp = statement();
          break;
        }

        default:
          break;
        }
        break;
      }

      case braneParser::T__34: {
        _localctx = _tracker.createInstance<braneParser::WhileContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(334);
        match(braneParser::T__34);
        setState(335);
        match(braneParser::T__19);
        setState(336);
        antlrcpp::downCast<WhileContext *>(_localctx)->cond = expression(0);
        setState(337);
        match(braneParser::T__20);
        setState(338);
        antlrcpp::downCast<WhileContext *>(_localctx)->operation = statement();
        break;
      }

      case braneParser::T__35: {
        _localctx = _tracker.createInstance<braneParser::ForContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(340);
        match(braneParser::T__35);
        setState(341);
        match(braneParser::T__19);
        setState(343);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 8868248743116800) != 0)) {
          setState(342);
          antlrcpp::downCast<ForContext *>(_localctx)->init = expression(0);
        }
        setState(345);
        match(braneParser::T__9);
        setState(346);
        antlrcpp::downCast<ForContext *>(_localctx)->cond = expression(0);
        setState(347);
        match(braneParser::T__9);
        setState(349);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 8868248743116800) != 0)) {
          setState(348);
          antlrcpp::downCast<ForContext *>(_localctx)->step = expression(0);
        }
        setState(351);
        match(braneParser::T__20);
        setState(352);
        antlrcpp::downCast<ForContext *>(_localctx)->operation = statement();
        break;
      }

      case braneParser::T__9: {
        _localctx = _tracker.createInstance<braneParser::EmptyContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(354);
        match(braneParser::T__9);
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
//----------------- PreDecContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::PreDecContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::PreDecContext::PreDecContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::PreDecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitPreDec(this);
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

braneParser::RefAssignmentContext::RefAssignmentContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::RefAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitRefAssignment(this);
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
//----------------- PostDecContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::PostDecContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::PostDecContext::PostDecContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::PostDecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitPostDec(this);
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
//----------------- PreIncContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::PreIncContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::PreIncContext::PreIncContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::PreIncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitPreInc(this);
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
//----------------- PostIncContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::PostIncContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::PostIncContext::PostIncContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::PostIncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitPostInc(this);
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
    setState(410);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ConstIntContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(358);
      match(braneParser::INT);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ConstFloatContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(359);
      match(braneParser::FLOAT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ConstCharContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(360);
      match(braneParser::CHAR);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ConstStringContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(361);
      match(braneParser::STRING);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ConstBoolContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(362);
      match(braneParser::BOOL);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SizeOfTypeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(363);
      match(braneParser::T__36);
      setState(364);
      match(braneParser::T__19);
      setState(365);
      antlrcpp::downCast<SizeOfTypeContext *>(_localctx)->t = type();
      setState(366);
      match(braneParser::T__20);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SizeOfPackContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(368);
      match(braneParser::T__36);
      setState(369);
      match(braneParser::T__11);
      setState(370);
      match(braneParser::T__19);
      setState(371);
      antlrcpp::downCast<SizeOfPackContext *>(_localctx)->id = match(braneParser::ID);
      setState(372);
      match(braneParser::T__20);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<DeclContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(373);
      declaration();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<IdContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(374);
      scopedID();
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<CastContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(375);
      match(braneParser::T__19);
      setState(376);
      type();
      setState(377);
      match(braneParser::T__20);
      setState(378);
      expression(14);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<PreIncContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(380);
      match(braneParser::T__38);
      setState(381);
      antlrcpp::downCast<PreIncContext *>(_localctx)->value = expression(13);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<PreDecContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(382);
      match(braneParser::T__39);
      setState(383);
      antlrcpp::downCast<PreDecContext *>(_localctx)->value = expression(12);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<NotContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(384);
      match(braneParser::T__27);
      setState(385);
      antlrcpp::downCast<NotContext *>(_localctx)->value = expression(5);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<ParenContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(386);
      match(braneParser::T__19);
      setState(387);
      expression(0);
      setState(388);
      match(braneParser::T__20);
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<LambdaContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(390);
      antlrcpp::downCast<LambdaContext *>(_localctx)->returnType = type();
      setState(391);
      antlrcpp::downCast<LambdaContext *>(_localctx)->label = match(braneParser::T__15);
      setState(396);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == braneParser::T__3) {
        setState(392);
        match(braneParser::T__3);
        setState(393);
        antlrcpp::downCast<LambdaContext *>(_localctx)->capture = varCapture();
        setState(394);
        match(braneParser::T__5);
      }
      setState(398);
      match(braneParser::T__19);
      setState(399);
      antlrcpp::downCast<LambdaContext *>(_localctx)->arguments = argumentList();
      setState(400);
      match(braneParser::T__20);
      setState(401);
      match(braneParser::T__7);
      setState(405);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 8868364707235072) != 0)) {
        setState(402);
        statement();
        setState(407);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(408);
      match(braneParser::T__8);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(452);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(450);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MuldivContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(412);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(413);
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
          setState(414);
          antlrcpp::downCast<MuldivContext *>(_localctx)->right = expression(10);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddsubContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(415);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(416);
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
          setState(417);
          antlrcpp::downCast<AddsubContext *>(_localctx)->right = expression(9);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ComparisonContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(418);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(419);
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
          setState(420);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->right = expression(8);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<LogicContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(421);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(422);
          antlrcpp::downCast<LogicContext *>(_localctx)->opr = match(braneParser::LOGIC);
          setState(423);
          antlrcpp::downCast<LogicContext *>(_localctx)->right = expression(7);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<AssignmentContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lValue = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(424);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(425);
          match(braneParser::T__40);
          setState(426);
          antlrcpp::downCast<AssignmentContext *>(_localctx)->rValue = expression(3);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<RefAssignmentContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lValue = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(427);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(428);
          match(braneParser::T__41);
          setState(429);
          antlrcpp::downCast<RefAssignmentContext *>(_localctx)->rValue = expression(2);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<FunctionCallContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->overrides = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(430);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(431);
          match(braneParser::T__19);
          setState(432);
          argumentPack();
          setState(433);
          match(braneParser::T__20);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<IndexAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(435);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(436);
          match(braneParser::T__3);
          setState(437);
          antlrcpp::downCast<IndexAccessContext *>(_localctx)->arg = expression(0);
          setState(438);
          match(braneParser::T__5);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(440);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(441);
          match(braneParser::T__37);
          setState(442);
          antlrcpp::downCast<MemberAccessContext *>(_localctx)->member = match(braneParser::ID);
          setState(444);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
          case 1: {
            setState(443);
            antlrcpp::downCast<MemberAccessContext *>(_localctx)->template_ = templateArgs();
            break;
          }

          default:
            break;
          }
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<PostIncContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(446);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(447);
          match(braneParser::T__38);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<PostDecContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(448);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(449);
          match(braneParser::T__39);
          break;
        }

        default:
          break;
        } 
      }
      setState(454);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
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
    case 0: return precpred(_ctx, 9);
    case 1: return precpred(_ctx, 8);
    case 2: return precpred(_ctx, 7);
    case 3: return precpred(_ctx, 6);
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);
    case 6: return precpred(_ctx, 18);
    case 7: return precpred(_ctx, 16);
    case 8: return precpred(_ctx, 15);
    case 9: return precpred(_ctx, 11);
    case 10: return precpred(_ctx, 10);

  default:
    break;
  }
  return true;
}

void braneParser::initialize() {
  ::antlr4::internal::call_once(braneParserOnceFlag, braneParserInitialize);
}

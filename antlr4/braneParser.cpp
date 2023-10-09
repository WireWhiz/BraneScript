
// Generated from /home/wirewhiz/CLionProjects/BraneScript/antlr4/brane.g4 by ANTLR 4.13.1


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
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
BraneParserStaticData *braneParserStaticData = nullptr;

void braneParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (braneParserStaticData != nullptr) {
    return;
  }
#else
  assert(braneParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<BraneParserStaticData>(
    std::vector<std::string>{
      "modules", "link", "linkList", "tags", "module", "moduleComponent", 
      "global", "templateDefArgument", "templateDef", "templateArg", "templateArgs", 
      "scopedID", "type", "declaration", "argumentListItem", "argumentList", 
      "argumentPackItem", "argumentPack", "bracketOpr", "functionSig", "functionStub", 
      "function", "capturedVar", "varCapture", "structDef", "structMember", 
      "expression", "switchCase", "matchCase", "magicFunction"
    },
    std::vector<std::string>{
      "", "'public'", "'link'", "'as'", "'['", "','", "']'", "'module'", 
      "'{'", "'}'", "';'", "'typedef'", "'...'", "'template'", "'<'", "'>'", 
      "'lambda'", "'::'", "'const'", "'ref'", "'('", "')'", "'constexpr'", 
      "'opr'", "'=='", "'!='", "'<='", "'>='", "'!'", "'ext'", "'packed'", 
      "'struct'", "'return'", "'if'", "'else'", "'while'", "'for'", "'switch'", 
      "'match'", "'.'", "'++'", "'--'", "'='", "'<-'", "'case'", "'default'", 
      "'sizeof'", "", "", "", "", "", "", "", "", "", "", "'*'", "'/'", 
      "'+'", "'-'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "COMMENT", "NEWLINE", 
      "BLOCK_COMMENT", "SPACE", "BOOL", "INT", "FLOAT", "CHAR", "STRING", 
      "ID", "MUL", "DIV", "ADD", "SUB", "LOGIC"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,61,528,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,1,0,5,0,62,8,0,10,0,12,0,65,9,0,1,0,3,0,68,8,0,1,1,3,1,71,
  	8,1,1,1,1,1,1,1,1,1,3,1,77,8,1,1,2,5,2,80,8,2,10,2,12,2,83,9,2,1,3,1,
  	3,1,3,1,3,5,3,89,8,3,10,3,12,3,92,9,3,3,3,94,8,3,1,3,1,3,1,4,3,4,99,8,
  	4,1,4,1,4,1,4,1,4,1,4,5,4,106,8,4,10,4,12,4,109,9,4,1,4,1,4,1,5,1,5,1,
  	5,1,5,1,5,1,5,3,5,119,8,5,1,6,1,6,1,6,1,6,1,7,1,7,3,7,127,8,7,1,7,3,7,
  	130,8,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,5,8,139,8,8,10,8,12,8,142,9,8,1,8,
  	1,8,1,9,1,9,1,9,1,9,3,9,150,8,9,1,10,1,10,1,10,1,10,5,10,156,8,10,10,
  	10,12,10,159,9,10,1,10,1,10,1,11,1,11,3,11,165,8,11,1,11,1,11,3,11,169,
  	8,11,1,12,3,12,172,8,12,1,12,1,12,1,12,1,12,3,12,178,8,12,1,12,3,12,181,
  	8,12,1,12,1,12,1,13,1,13,1,13,1,14,1,14,1,14,1,14,3,14,192,8,14,1,15,
  	1,15,1,15,5,15,197,8,15,10,15,12,15,200,9,15,3,15,202,8,15,1,16,1,16,
  	1,16,3,16,207,8,16,1,17,1,17,1,17,5,17,212,8,17,10,17,12,17,215,9,17,
  	3,17,217,8,17,1,18,1,18,1,18,1,18,3,18,223,8,18,1,19,3,19,226,8,19,1,
  	19,3,19,229,8,19,1,19,3,19,232,8,19,1,19,1,19,1,19,1,19,1,19,3,19,239,
  	8,19,3,19,241,8,19,1,19,1,19,3,19,245,8,19,1,20,1,20,1,20,1,20,1,20,3,
  	20,252,8,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,3,21,261,8,21,1,21,1,21,
  	5,21,265,8,21,10,21,12,21,268,9,21,1,21,1,21,1,22,3,22,273,8,22,1,22,
  	1,22,1,23,1,23,1,23,5,23,280,8,23,10,23,12,23,283,9,23,1,24,3,24,286,
  	8,24,1,24,3,24,289,8,24,1,24,3,24,292,8,24,1,24,1,24,1,24,1,24,5,24,298,
  	8,24,10,24,12,24,301,9,24,1,24,1,24,1,25,1,25,1,25,1,25,1,25,1,25,1,25,
  	3,25,312,8,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,3,26,322,8,26,1,
  	26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,3,26,332,8,26,1,26,1,26,1,26,1,
  	26,1,26,1,26,1,26,1,26,1,26,3,26,343,8,26,1,26,1,26,1,26,1,26,3,26,349,
  	8,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,5,26,360,8,26,10,26,
  	12,26,363,9,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,5,26,373,8,26,
  	10,26,12,26,376,9,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,
  	1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,5,26,396,8,26,10,26,12,26,399,
  	9,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,3,26,408,8,26,1,26,1,26,1,26,
  	1,26,1,26,5,26,415,8,26,10,26,12,26,418,9,26,1,26,1,26,3,26,422,8,26,
  	1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,
  	1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,
  	1,26,1,26,1,26,1,26,1,26,1,26,3,26,458,8,26,1,26,1,26,1,26,1,26,1,26,
  	1,26,1,26,5,26,467,8,26,10,26,12,26,470,9,26,1,27,1,27,1,27,1,27,5,27,
  	476,8,27,10,27,12,27,479,9,27,1,27,1,27,1,27,1,27,1,27,5,27,486,8,27,
  	10,27,12,27,489,9,27,1,27,3,27,492,8,27,1,28,1,28,1,28,1,28,5,28,498,
  	8,28,10,28,12,28,501,9,28,1,28,1,28,1,28,1,28,1,28,5,28,508,8,28,10,28,
  	12,28,511,9,28,1,28,3,28,514,8,28,1,29,1,29,1,29,1,29,1,29,1,29,1,29,
  	1,29,1,29,1,29,3,29,526,8,29,1,29,0,1,52,30,0,2,4,6,8,10,12,14,16,18,
  	20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,0,5,2,0,16,
  	16,56,56,3,0,14,15,24,28,57,61,1,0,57,58,1,0,59,60,2,0,14,15,24,27,595,
  	0,63,1,0,0,0,2,70,1,0,0,0,4,81,1,0,0,0,6,84,1,0,0,0,8,98,1,0,0,0,10,118,
  	1,0,0,0,12,120,1,0,0,0,14,126,1,0,0,0,16,133,1,0,0,0,18,149,1,0,0,0,20,
  	151,1,0,0,0,22,162,1,0,0,0,24,171,1,0,0,0,26,184,1,0,0,0,28,191,1,0,0,
  	0,30,201,1,0,0,0,32,206,1,0,0,0,34,216,1,0,0,0,36,222,1,0,0,0,38,225,
  	1,0,0,0,40,246,1,0,0,0,42,255,1,0,0,0,44,272,1,0,0,0,46,276,1,0,0,0,48,
  	285,1,0,0,0,50,311,1,0,0,0,52,421,1,0,0,0,54,491,1,0,0,0,56,513,1,0,0,
  	0,58,525,1,0,0,0,60,62,3,8,4,0,61,60,1,0,0,0,62,65,1,0,0,0,63,61,1,0,
  	0,0,63,64,1,0,0,0,64,67,1,0,0,0,65,63,1,0,0,0,66,68,5,0,0,1,67,66,1,0,
  	0,0,67,68,1,0,0,0,68,1,1,0,0,0,69,71,5,1,0,0,70,69,1,0,0,0,70,71,1,0,
  	0,0,71,72,1,0,0,0,72,73,5,2,0,0,73,76,5,55,0,0,74,75,5,3,0,0,75,77,5,
  	55,0,0,76,74,1,0,0,0,76,77,1,0,0,0,77,3,1,0,0,0,78,80,3,2,1,0,79,78,1,
  	0,0,0,80,83,1,0,0,0,81,79,1,0,0,0,81,82,1,0,0,0,82,5,1,0,0,0,83,81,1,
  	0,0,0,84,93,5,4,0,0,85,90,5,55,0,0,86,87,5,5,0,0,87,89,5,55,0,0,88,86,
  	1,0,0,0,89,92,1,0,0,0,90,88,1,0,0,0,90,91,1,0,0,0,91,94,1,0,0,0,92,90,
  	1,0,0,0,93,85,1,0,0,0,93,94,1,0,0,0,94,95,1,0,0,0,95,96,5,6,0,0,96,7,
  	1,0,0,0,97,99,3,6,3,0,98,97,1,0,0,0,98,99,1,0,0,0,99,100,1,0,0,0,100,
  	101,5,7,0,0,101,102,5,55,0,0,102,103,3,4,2,0,103,107,5,8,0,0,104,106,
  	3,10,5,0,105,104,1,0,0,0,106,109,1,0,0,0,107,105,1,0,0,0,107,108,1,0,
  	0,0,108,110,1,0,0,0,109,107,1,0,0,0,110,111,5,9,0,0,111,9,1,0,0,0,112,
  	119,3,42,21,0,113,114,3,40,20,0,114,115,5,10,0,0,115,119,1,0,0,0,116,
  	119,3,48,24,0,117,119,3,12,6,0,118,112,1,0,0,0,118,113,1,0,0,0,118,116,
  	1,0,0,0,118,117,1,0,0,0,119,11,1,0,0,0,120,121,3,24,12,0,121,122,5,56,
  	0,0,122,123,5,10,0,0,123,13,1,0,0,0,124,127,3,24,12,0,125,127,5,11,0,
  	0,126,124,1,0,0,0,126,125,1,0,0,0,127,129,1,0,0,0,128,130,5,12,0,0,129,
  	128,1,0,0,0,129,130,1,0,0,0,130,131,1,0,0,0,131,132,5,56,0,0,132,15,1,
  	0,0,0,133,134,5,13,0,0,134,135,5,14,0,0,135,140,3,14,7,0,136,137,5,5,
  	0,0,137,139,3,14,7,0,138,136,1,0,0,0,139,142,1,0,0,0,140,138,1,0,0,0,
  	140,141,1,0,0,0,141,143,1,0,0,0,142,140,1,0,0,0,143,144,5,15,0,0,144,
  	17,1,0,0,0,145,150,3,24,12,0,146,150,3,52,26,0,147,148,5,56,0,0,148,150,
  	5,12,0,0,149,145,1,0,0,0,149,146,1,0,0,0,149,147,1,0,0,0,150,19,1,0,0,
  	0,151,152,5,14,0,0,152,157,3,18,9,0,153,154,5,5,0,0,154,156,3,18,9,0,
  	155,153,1,0,0,0,156,159,1,0,0,0,157,155,1,0,0,0,157,158,1,0,0,0,158,160,
  	1,0,0,0,159,157,1,0,0,0,160,161,5,15,0,0,161,21,1,0,0,0,162,164,7,0,0,
  	0,163,165,3,20,10,0,164,163,1,0,0,0,164,165,1,0,0,0,165,168,1,0,0,0,166,
  	167,5,17,0,0,167,169,3,22,11,0,168,166,1,0,0,0,168,169,1,0,0,0,169,23,
  	1,0,0,0,170,172,5,18,0,0,171,170,1,0,0,0,171,172,1,0,0,0,172,180,1,0,
  	0,0,173,181,5,19,0,0,174,175,5,19,0,0,175,177,5,4,0,0,176,178,5,52,0,
  	0,177,176,1,0,0,0,177,178,1,0,0,0,178,179,1,0,0,0,179,181,5,6,0,0,180,
  	173,1,0,0,0,180,174,1,0,0,0,180,181,1,0,0,0,181,182,1,0,0,0,182,183,3,
  	22,11,0,183,25,1,0,0,0,184,185,3,24,12,0,185,186,5,56,0,0,186,27,1,0,
  	0,0,187,192,3,26,13,0,188,189,5,56,0,0,189,190,5,12,0,0,190,192,5,56,
  	0,0,191,187,1,0,0,0,191,188,1,0,0,0,192,29,1,0,0,0,193,198,3,28,14,0,
  	194,195,5,5,0,0,195,197,3,28,14,0,196,194,1,0,0,0,197,200,1,0,0,0,198,
  	196,1,0,0,0,198,199,1,0,0,0,199,202,1,0,0,0,200,198,1,0,0,0,201,193,1,
  	0,0,0,201,202,1,0,0,0,202,31,1,0,0,0,203,207,3,52,26,0,204,205,5,56,0,
  	0,205,207,5,12,0,0,206,203,1,0,0,0,206,204,1,0,0,0,207,33,1,0,0,0,208,
  	213,3,32,16,0,209,210,5,5,0,0,210,212,3,32,16,0,211,209,1,0,0,0,212,215,
  	1,0,0,0,213,211,1,0,0,0,213,214,1,0,0,0,214,217,1,0,0,0,215,213,1,0,0,
  	0,216,208,1,0,0,0,216,217,1,0,0,0,217,35,1,0,0,0,218,219,5,20,0,0,219,
  	223,5,21,0,0,220,221,5,4,0,0,221,223,5,6,0,0,222,218,1,0,0,0,222,220,
  	1,0,0,0,223,37,1,0,0,0,224,226,3,6,3,0,225,224,1,0,0,0,225,226,1,0,0,
  	0,226,228,1,0,0,0,227,229,3,16,8,0,228,227,1,0,0,0,228,229,1,0,0,0,229,
  	231,1,0,0,0,230,232,5,22,0,0,231,230,1,0,0,0,231,232,1,0,0,0,232,244,
  	1,0,0,0,233,240,3,24,12,0,234,241,5,56,0,0,235,238,5,23,0,0,236,239,7,
  	1,0,0,237,239,3,36,18,0,238,236,1,0,0,0,238,237,1,0,0,0,239,241,1,0,0,
  	0,240,234,1,0,0,0,240,235,1,0,0,0,241,245,1,0,0,0,242,243,5,23,0,0,243,
  	245,3,24,12,0,244,233,1,0,0,0,244,242,1,0,0,0,245,39,1,0,0,0,246,247,
  	3,38,19,0,247,248,5,20,0,0,248,249,3,30,15,0,249,251,5,21,0,0,250,252,
  	5,18,0,0,251,250,1,0,0,0,251,252,1,0,0,0,252,253,1,0,0,0,253,254,5,29,
  	0,0,254,41,1,0,0,0,255,256,3,38,19,0,256,257,5,20,0,0,257,258,3,30,15,
  	0,258,260,5,21,0,0,259,261,5,18,0,0,260,259,1,0,0,0,260,261,1,0,0,0,261,
  	262,1,0,0,0,262,266,5,8,0,0,263,265,3,52,26,0,264,263,1,0,0,0,265,268,
  	1,0,0,0,266,264,1,0,0,0,266,267,1,0,0,0,267,269,1,0,0,0,268,266,1,0,0,
  	0,269,270,5,9,0,0,270,43,1,0,0,0,271,273,5,19,0,0,272,271,1,0,0,0,272,
  	273,1,0,0,0,273,274,1,0,0,0,274,275,3,22,11,0,275,45,1,0,0,0,276,281,
  	3,44,22,0,277,278,5,5,0,0,278,280,3,44,22,0,279,277,1,0,0,0,280,283,1,
  	0,0,0,281,279,1,0,0,0,281,282,1,0,0,0,282,47,1,0,0,0,283,281,1,0,0,0,
  	284,286,3,6,3,0,285,284,1,0,0,0,285,286,1,0,0,0,286,288,1,0,0,0,287,289,
  	3,16,8,0,288,287,1,0,0,0,288,289,1,0,0,0,289,291,1,0,0,0,290,292,5,30,
  	0,0,291,290,1,0,0,0,291,292,1,0,0,0,292,293,1,0,0,0,293,294,5,31,0,0,
  	294,295,7,0,0,0,295,299,5,8,0,0,296,298,3,50,25,0,297,296,1,0,0,0,298,
  	301,1,0,0,0,299,297,1,0,0,0,299,300,1,0,0,0,300,302,1,0,0,0,301,299,1,
  	0,0,0,302,303,5,9,0,0,303,49,1,0,0,0,304,305,3,40,20,0,305,306,5,10,0,
  	0,306,312,1,0,0,0,307,312,3,42,21,0,308,309,3,26,13,0,309,310,5,10,0,
  	0,310,312,1,0,0,0,311,304,1,0,0,0,311,307,1,0,0,0,311,308,1,0,0,0,312,
  	51,1,0,0,0,313,314,6,26,-1,0,314,422,5,52,0,0,315,422,5,53,0,0,316,422,
  	5,54,0,0,317,422,5,55,0,0,318,422,5,51,0,0,319,321,5,32,0,0,320,322,3,
  	52,26,0,321,320,1,0,0,0,321,322,1,0,0,0,322,323,1,0,0,0,323,422,5,10,
  	0,0,324,325,5,33,0,0,325,326,5,20,0,0,326,327,3,52,26,0,327,328,5,21,
  	0,0,328,331,3,52,26,0,329,330,5,34,0,0,330,332,3,52,26,0,331,329,1,0,
  	0,0,331,332,1,0,0,0,332,422,1,0,0,0,333,334,5,35,0,0,334,335,5,20,0,0,
  	335,336,3,52,26,0,336,337,5,21,0,0,337,338,3,52,26,27,338,422,1,0,0,0,
  	339,340,5,36,0,0,340,342,5,20,0,0,341,343,3,52,26,0,342,341,1,0,0,0,342,
  	343,1,0,0,0,343,344,1,0,0,0,344,345,5,10,0,0,345,346,3,52,26,0,346,348,
  	5,10,0,0,347,349,3,52,26,0,348,347,1,0,0,0,348,349,1,0,0,0,349,350,1,
  	0,0,0,350,351,5,21,0,0,351,352,3,52,26,26,352,422,1,0,0,0,353,354,5,37,
  	0,0,354,355,5,20,0,0,355,356,3,52,26,0,356,357,5,21,0,0,357,361,5,8,0,
  	0,358,360,3,54,27,0,359,358,1,0,0,0,360,363,1,0,0,0,361,359,1,0,0,0,361,
  	362,1,0,0,0,362,364,1,0,0,0,363,361,1,0,0,0,364,365,5,9,0,0,365,422,1,
  	0,0,0,366,367,5,38,0,0,367,368,5,20,0,0,368,369,3,52,26,0,369,370,5,21,
  	0,0,370,374,5,8,0,0,371,373,3,56,28,0,372,371,1,0,0,0,373,376,1,0,0,0,
  	374,372,1,0,0,0,374,375,1,0,0,0,375,377,1,0,0,0,376,374,1,0,0,0,377,378,
  	5,9,0,0,378,422,1,0,0,0,379,422,5,10,0,0,380,422,3,58,29,0,381,422,3,
  	26,13,0,382,422,3,22,11,0,383,384,5,40,0,0,384,422,3,52,26,14,385,386,
  	5,41,0,0,386,422,3,52,26,13,387,388,5,28,0,0,388,422,3,52,26,6,389,390,
  	5,20,0,0,390,391,3,52,26,0,391,392,5,21,0,0,392,422,1,0,0,0,393,397,5,
  	8,0,0,394,396,3,52,26,0,395,394,1,0,0,0,396,399,1,0,0,0,397,395,1,0,0,
  	0,397,398,1,0,0,0,398,400,1,0,0,0,399,397,1,0,0,0,400,422,5,9,0,0,401,
  	402,3,24,12,0,402,407,5,16,0,0,403,404,5,4,0,0,404,405,3,46,23,0,405,
  	406,5,6,0,0,406,408,1,0,0,0,407,403,1,0,0,0,407,408,1,0,0,0,408,409,1,
  	0,0,0,409,410,5,20,0,0,410,411,3,30,15,0,411,412,5,21,0,0,412,416,5,8,
  	0,0,413,415,3,52,26,0,414,413,1,0,0,0,415,418,1,0,0,0,416,414,1,0,0,0,
  	416,417,1,0,0,0,417,419,1,0,0,0,418,416,1,0,0,0,419,420,5,9,0,0,420,422,
  	1,0,0,0,421,313,1,0,0,0,421,315,1,0,0,0,421,316,1,0,0,0,421,317,1,0,0,
  	0,421,318,1,0,0,0,421,319,1,0,0,0,421,324,1,0,0,0,421,333,1,0,0,0,421,
  	339,1,0,0,0,421,353,1,0,0,0,421,366,1,0,0,0,421,379,1,0,0,0,421,380,1,
  	0,0,0,421,381,1,0,0,0,421,382,1,0,0,0,421,383,1,0,0,0,421,385,1,0,0,0,
  	421,387,1,0,0,0,421,389,1,0,0,0,421,393,1,0,0,0,421,401,1,0,0,0,422,468,
  	1,0,0,0,423,424,10,10,0,0,424,425,7,2,0,0,425,467,3,52,26,11,426,427,
  	10,9,0,0,427,428,7,3,0,0,428,467,3,52,26,10,429,430,10,8,0,0,430,431,
  	7,4,0,0,431,467,3,52,26,9,432,433,10,7,0,0,433,434,5,61,0,0,434,467,3,
  	52,26,8,435,436,10,2,0,0,436,437,5,42,0,0,437,467,3,52,26,3,438,439,10,
  	1,0,0,439,440,5,43,0,0,440,467,3,52,26,2,441,442,10,22,0,0,442,467,5,
  	10,0,0,443,444,10,19,0,0,444,445,5,20,0,0,445,446,3,34,17,0,446,447,5,
  	21,0,0,447,467,1,0,0,0,448,449,10,17,0,0,449,450,5,4,0,0,450,451,3,52,
  	26,0,451,452,5,6,0,0,452,467,1,0,0,0,453,454,10,16,0,0,454,455,5,39,0,
  	0,455,457,5,56,0,0,456,458,3,20,10,0,457,456,1,0,0,0,457,458,1,0,0,0,
  	458,467,1,0,0,0,459,460,10,15,0,0,460,461,5,3,0,0,461,467,3,24,12,0,462,
  	463,10,12,0,0,463,467,5,40,0,0,464,465,10,11,0,0,465,467,5,41,0,0,466,
  	423,1,0,0,0,466,426,1,0,0,0,466,429,1,0,0,0,466,432,1,0,0,0,466,435,1,
  	0,0,0,466,438,1,0,0,0,466,441,1,0,0,0,466,443,1,0,0,0,466,448,1,0,0,0,
  	466,453,1,0,0,0,466,459,1,0,0,0,466,462,1,0,0,0,466,464,1,0,0,0,467,470,
  	1,0,0,0,468,466,1,0,0,0,468,469,1,0,0,0,469,53,1,0,0,0,470,468,1,0,0,
  	0,471,472,5,44,0,0,472,473,3,52,26,0,473,477,5,8,0,0,474,476,3,52,26,
  	0,475,474,1,0,0,0,476,479,1,0,0,0,477,475,1,0,0,0,477,478,1,0,0,0,478,
  	480,1,0,0,0,479,477,1,0,0,0,480,481,5,9,0,0,481,492,1,0,0,0,482,483,5,
  	45,0,0,483,487,5,8,0,0,484,486,3,52,26,0,485,484,1,0,0,0,486,489,1,0,
  	0,0,487,485,1,0,0,0,487,488,1,0,0,0,488,490,1,0,0,0,489,487,1,0,0,0,490,
  	492,5,9,0,0,491,471,1,0,0,0,491,482,1,0,0,0,492,55,1,0,0,0,493,494,5,
  	44,0,0,494,495,3,52,26,0,495,499,5,8,0,0,496,498,3,52,26,0,497,496,1,
  	0,0,0,498,501,1,0,0,0,499,497,1,0,0,0,499,500,1,0,0,0,500,502,1,0,0,0,
  	501,499,1,0,0,0,502,503,5,9,0,0,503,514,1,0,0,0,504,505,5,45,0,0,505,
  	509,5,8,0,0,506,508,3,52,26,0,507,506,1,0,0,0,508,511,1,0,0,0,509,507,
  	1,0,0,0,509,510,1,0,0,0,510,512,1,0,0,0,511,509,1,0,0,0,512,514,5,9,0,
  	0,513,493,1,0,0,0,513,504,1,0,0,0,514,57,1,0,0,0,515,516,5,46,0,0,516,
  	517,5,20,0,0,517,518,3,24,12,0,518,519,5,21,0,0,519,526,1,0,0,0,520,521,
  	5,46,0,0,521,522,5,12,0,0,522,523,5,20,0,0,523,524,5,56,0,0,524,526,5,
  	21,0,0,525,515,1,0,0,0,525,520,1,0,0,0,526,59,1,0,0,0,63,63,67,70,76,
  	81,90,93,98,107,118,126,129,140,149,157,164,168,171,177,180,191,198,201,
  	206,213,216,222,225,228,231,238,240,244,251,260,266,272,281,285,288,291,
  	299,311,321,331,342,348,361,374,397,407,416,421,457,466,468,477,487,491,
  	499,509,513,525
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
    setState(63);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__3

    || _la == braneParser::T__6) {
      setState(60);
      module();
      setState(65);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(67);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(66);
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
    setState(70);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__0) {
      setState(69);
      antlrcpp::downCast<LinkContext *>(_localctx)->isPublic = match(braneParser::T__0);
    }
    setState(72);
    match(braneParser::T__1);
    setState(73);
    antlrcpp::downCast<LinkContext *>(_localctx)->library = match(braneParser::STRING);
    setState(76);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__2) {
      setState(74);
      match(braneParser::T__2);
      setState(75);
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
    setState(81);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__0

    || _la == braneParser::T__1) {
      setState(78);
      link();
      setState(83);
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
    setState(84);
    match(braneParser::T__3);
    setState(93);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::STRING) {
      setState(85);
      antlrcpp::downCast<TagsContext *>(_localctx)->tag = match(braneParser::STRING);
      setState(90);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__4) {
        setState(86);
        match(braneParser::T__4);
        setState(87);
        antlrcpp::downCast<TagsContext *>(_localctx)->tag = match(braneParser::STRING);
        setState(92);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(95);
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
    setState(98);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(97);
      antlrcpp::downCast<ModuleContext *>(_localctx)->modTags = tags();
    }
    setState(100);
    match(braneParser::T__6);
    setState(101);
    antlrcpp::downCast<ModuleContext *>(_localctx)->id = match(braneParser::STRING);
    setState(102);
    linkList();
    setState(103);
    match(braneParser::T__7);
    setState(107);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72057597272596496) != 0)) {
      setState(104);
      moduleComponent();
      setState(109);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(110);
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
    setState(118);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(112);
      function();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(113);
      functionStub();
      setState(114);
      match(braneParser::T__9);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(116);
      structDef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(117);
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
    setState(120);
    type();
    setState(121);
    antlrcpp::downCast<GlobalContext *>(_localctx)->id = match(braneParser::ID);
    setState(122);
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
    setState(126);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__15:
      case braneParser::T__17:
      case braneParser::T__18:
      case braneParser::ID: {
        setState(124);
        antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->exprType = type();
        break;
      }

      case braneParser::T__10: {
        setState(125);
        antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->isTypedef = match(braneParser::T__10);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(129);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__11) {
      setState(128);
      antlrcpp::downCast<TemplateDefArgumentContext *>(_localctx)->isPack = match(braneParser::T__11);
    }
    setState(131);
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
    setState(133);
    match(braneParser::T__12);
    setState(134);
    match(braneParser::T__13);
    setState(135);
    templateDefArgument();
    setState(140);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__4) {
      setState(136);
      match(braneParser::T__4);
      setState(137);
      templateDefArgument();
      setState(142);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(143);
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
    setState(149);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::TemplateTypeArgContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(145);
      antlrcpp::downCast<TemplateTypeArgContext *>(_localctx)->t = type();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::TemplateExprArgContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(146);
      antlrcpp::downCast<TemplateExprArgContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::PackExpansionArgContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(147);
      antlrcpp::downCast<PackExpansionArgContext *>(_localctx)->packID = match(braneParser::ID);
      setState(148);
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
    setState(151);
    match(braneParser::T__13);
    setState(152);
    templateArg();
    setState(157);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__4) {
      setState(153);
      match(braneParser::T__4);
      setState(154);
      templateArg();
      setState(159);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(160);
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
    setState(162);
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
    setState(164);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(163);
      antlrcpp::downCast<ScopedIDContext *>(_localctx)->template_ = templateArgs();
      break;
    }

    default:
      break;
    }
    setState(168);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      setState(166);
      match(braneParser::T__16);
      setState(167);
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
    setState(171);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__17) {
      setState(170);
      antlrcpp::downCast<TypeContext *>(_localctx)->isConst = match(braneParser::T__17);
    }
    setState(180);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(173);
      antlrcpp::downCast<TypeContext *>(_localctx)->isRef = match(braneParser::T__18);
      break;
    }

    case 2: {
      setState(174);
      antlrcpp::downCast<TypeContext *>(_localctx)->isArrayRef = match(braneParser::T__18);
      setState(175);
      match(braneParser::T__3);
      setState(177);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == braneParser::INT) {
        setState(176);
        antlrcpp::downCast<TypeContext *>(_localctx)->size = match(braneParser::INT);
      }
      setState(179);
      match(braneParser::T__5);
      break;
    }

    default:
      break;
    }
    setState(182);
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
    setState(184);
    type();
    setState(185);
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
    setState(191);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(187);
      declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(188);
      antlrcpp::downCast<ArgumentListItemContext *>(_localctx)->pack = match(braneParser::ID);
      setState(189);
      match(braneParser::T__11);
      setState(190);
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
    setState(201);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72057594038779904) != 0)) {
      setState(193);
      argumentListItem();
      setState(198);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__4) {
        setState(194);
        match(braneParser::T__4);
        setState(195);
        argumentListItem();
        setState(200);
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
    setState(206);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(203);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(204);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->packID = match(braneParser::ID);
      setState(205);
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
    setState(216);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 141937584092546304) != 0)) {
      setState(208);
      argumentPackItem();
      setState(213);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__4) {
        setState(209);
        match(braneParser::T__4);
        setState(210);
        argumentPackItem();
        setState(215);
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
    setState(222);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__19: {
        enterOuterAlt(_localctx, 1);
        setState(218);
        match(braneParser::T__19);
        setState(219);
        match(braneParser::T__20);
        break;
      }

      case braneParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(220);
        match(braneParser::T__3);
        setState(221);
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
    setState(225);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(224);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->funcTags = tags();
    }
    setState(228);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__12) {
      setState(227);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->template_ = templateDef();
    }
    setState(231);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__21) {
      setState(230);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->isConstexpr = match(braneParser::T__21);
    }
    setState(244);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__15:
      case braneParser::T__17:
      case braneParser::T__18:
      case braneParser::ID: {
        setState(233);
        type();
        setState(240);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case braneParser::ID: {
            setState(234);
            antlrcpp::downCast<FunctionSigContext *>(_localctx)->id = match(braneParser::ID);
            break;
          }

          case braneParser::T__22: {
            setState(235);
            match(braneParser::T__22);
            setState(238);
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
                setState(236);
                antlrcpp::downCast<FunctionSigContext *>(_localctx)->oprID = _input->LT(1);
                _la = _input->LA(1);
                if (!((((_la & ~ 0x3fULL) == 0) &&
                  ((1ULL << _la) & 4467570830871674880) != 0))) {
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
                setState(237);
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
        setState(242);
        match(braneParser::T__22);
        setState(243);
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
    setState(246);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->sig = functionSig();
    setState(247);
    match(braneParser::T__19);
    setState(248);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->arguments = argumentList();
    setState(249);
    match(braneParser::T__20);
    setState(251);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__17) {
      setState(250);
      antlrcpp::downCast<FunctionStubContext *>(_localctx)->isConst = match(braneParser::T__17);
    }
    setState(253);
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

std::vector<braneParser::ExpressionContext *> braneParser::FunctionContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::FunctionContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
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
    setState(255);
    antlrcpp::downCast<FunctionContext *>(_localctx)->sig = functionSig();
    setState(256);
    match(braneParser::T__19);
    setState(257);
    antlrcpp::downCast<FunctionContext *>(_localctx)->arguments = argumentList();
    setState(258);
    match(braneParser::T__20);
    setState(260);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__17) {
      setState(259);
      antlrcpp::downCast<FunctionContext *>(_localctx)->isConst = match(braneParser::T__17);
    }
    setState(262);
    match(braneParser::T__7);
    setState(266);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 141937584092546304) != 0)) {
      setState(263);
      antlrcpp::downCast<FunctionContext *>(_localctx)->expressions = expression(0);
      setState(268);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(269);
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
    setState(272);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__18) {
      setState(271);
      antlrcpp::downCast<CapturedVarContext *>(_localctx)->isRef = match(braneParser::T__18);
    }
    setState(274);
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
    setState(276);
    capturedVar();
    setState(281);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__4) {
      setState(277);
      match(braneParser::T__4);
      setState(278);
      capturedVar();
      setState(283);
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
    setState(285);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__3) {
      setState(284);
      antlrcpp::downCast<StructDefContext *>(_localctx)->structTags = tags();
    }
    setState(288);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__12) {
      setState(287);
      antlrcpp::downCast<StructDefContext *>(_localctx)->template_ = templateDef();
    }
    setState(291);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__29) {
      setState(290);
      antlrcpp::downCast<StructDefContext *>(_localctx)->packed = match(braneParser::T__29);
    }
    setState(293);
    match(braneParser::T__30);
    setState(294);
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
    setState(295);
    match(braneParser::T__7);
    setState(299);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72057594051371024) != 0)) {
      setState(296);
      antlrcpp::downCast<StructDefContext *>(_localctx)->memberVars = structMember();
      setState(301);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(302);
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
    setState(311);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::MemberFunctionStubContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(304);
      functionStub();
      setState(305);
      match(braneParser::T__9);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::MemberFunctionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(307);
      antlrcpp::downCast<MemberFunctionContext *>(_localctx)->func = function();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::MemberVariableContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(308);
      antlrcpp::downCast<MemberVariableContext *>(_localctx)->var = declaration();
      setState(309);
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
//----------------- VoidExpressionContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::VoidExpressionContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::VoidExpressionContext::VoidExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::VoidExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitVoidExpression(this);
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

braneParser::ForContext::ForContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::ForContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitFor(this);
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
//----------------- WhileContext ------------------------------------------------------------------

std::vector<braneParser::ExpressionContext *> braneParser::WhileContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::WhileContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}

braneParser::WhileContext::WhileContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::WhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitWhile(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SwitchContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::SwitchContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

std::vector<braneParser::SwitchCaseContext *> braneParser::SwitchContext::switchCase() {
  return getRuleContexts<braneParser::SwitchCaseContext>();
}

braneParser::SwitchCaseContext* braneParser::SwitchContext::switchCase(size_t i) {
  return getRuleContext<braneParser::SwitchCaseContext>(i);
}

braneParser::SwitchContext::SwitchContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::SwitchContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitSwitch(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EmptyContext ------------------------------------------------------------------

braneParser::EmptyContext::EmptyContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::EmptyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitEmpty(this);
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

std::vector<braneParser::ExpressionContext *> braneParser::LambdaContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::LambdaContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
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
//----------------- MagicFunctionCallContext ------------------------------------------------------------------

braneParser::MagicFunctionContext* braneParser::MagicFunctionCallContext::magicFunction() {
  return getRuleContext<braneParser::MagicFunctionContext>(0);
}

braneParser::MagicFunctionCallContext::MagicFunctionCallContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::MagicFunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitMagicFunctionCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ScopeContext ------------------------------------------------------------------

std::vector<braneParser::ExpressionContext *> braneParser::ScopeContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::ScopeContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}

braneParser::ScopeContext::ScopeContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::ScopeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitScope(this);
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
//----------------- IfContext ------------------------------------------------------------------

std::vector<braneParser::ExpressionContext *> braneParser::IfContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::IfContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}

braneParser::IfContext::IfContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::IfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitIf(this);
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
//----------------- MatchContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::MatchContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

std::vector<braneParser::MatchCaseContext *> braneParser::MatchContext::matchCase() {
  return getRuleContexts<braneParser::MatchCaseContext>();
}

braneParser::MatchCaseContext* braneParser::MatchContext::matchCase(size_t i) {
  return getRuleContext<braneParser::MatchCaseContext>(i);
}

braneParser::MatchContext::MatchContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::MatchContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitMatch(this);
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
//----------------- ReturnContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::ReturnContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::ReturnContext::ReturnContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::ReturnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitReturn(this);
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
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, braneParser::RuleExpression, precedence);

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
    setState(421);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ConstIntContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(314);
      match(braneParser::INT);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ConstFloatContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(315);
      match(braneParser::FLOAT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ConstCharContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(316);
      match(braneParser::CHAR);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ConstStringContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(317);
      match(braneParser::STRING);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ConstBoolContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(318);
      match(braneParser::BOOL);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ReturnContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(319);
      match(braneParser::T__31);
      setState(321);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
      case 1: {
        setState(320);
        expression(0);
        break;
      }

      default:
        break;
      }
      setState(323);
      match(braneParser::T__9);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<IfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(324);
      match(braneParser::T__32);
      setState(325);
      match(braneParser::T__19);
      setState(326);
      antlrcpp::downCast<IfContext *>(_localctx)->cond = expression(0);
      setState(327);
      match(braneParser::T__20);
      setState(328);
      antlrcpp::downCast<IfContext *>(_localctx)->operation = expression(0);
      setState(331);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
      case 1: {
        setState(329);
        match(braneParser::T__33);
        setState(330);
        antlrcpp::downCast<IfContext *>(_localctx)->elseOp = expression(0);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<WhileContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(333);
      match(braneParser::T__34);
      setState(334);
      match(braneParser::T__19);
      setState(335);
      antlrcpp::downCast<WhileContext *>(_localctx)->cond = expression(0);
      setState(336);
      match(braneParser::T__20);
      setState(337);
      antlrcpp::downCast<WhileContext *>(_localctx)->operation = expression(27);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ForContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(339);
      match(braneParser::T__35);
      setState(340);
      match(braneParser::T__19);
      setState(342);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
      case 1: {
        setState(341);
        antlrcpp::downCast<ForContext *>(_localctx)->init = expression(0);
        break;
      }

      default:
        break;
      }
      setState(344);
      match(braneParser::T__9);
      setState(345);
      antlrcpp::downCast<ForContext *>(_localctx)->cond = expression(0);
      setState(346);
      match(braneParser::T__9);
      setState(348);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 141937584092546304) != 0)) {
        setState(347);
        antlrcpp::downCast<ForContext *>(_localctx)->step = expression(0);
      }
      setState(350);
      match(braneParser::T__20);
      setState(351);
      antlrcpp::downCast<ForContext *>(_localctx)->operation = expression(26);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<SwitchContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(353);
      match(braneParser::T__36);
      setState(354);
      match(braneParser::T__19);
      setState(355);
      antlrcpp::downCast<SwitchContext *>(_localctx)->value = expression(0);
      setState(356);
      match(braneParser::T__20);
      setState(357);
      match(braneParser::T__7);
      setState(361);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__43

      || _la == braneParser::T__44) {
        setState(358);
        switchCase();
        setState(363);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(364);
      match(braneParser::T__8);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<MatchContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(366);
      match(braneParser::T__37);
      setState(367);
      match(braneParser::T__19);
      setState(368);
      antlrcpp::downCast<MatchContext *>(_localctx)->value = expression(0);
      setState(369);
      match(braneParser::T__20);
      setState(370);
      match(braneParser::T__7);
      setState(374);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__43

      || _la == braneParser::T__44) {
        setState(371);
        matchCase();
        setState(376);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(377);
      match(braneParser::T__8);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<EmptyContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(379);
      match(braneParser::T__9);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<MagicFunctionCallContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(380);
      magicFunction();
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<DeclContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(381);
      declaration();
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<IdContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(382);
      scopedID();
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<PreIncContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(383);
      match(braneParser::T__39);
      setState(384);
      antlrcpp::downCast<PreIncContext *>(_localctx)->value = expression(14);
      break;
    }

    case 17: {
      _localctx = _tracker.createInstance<PreDecContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(385);
      match(braneParser::T__40);
      setState(386);
      antlrcpp::downCast<PreDecContext *>(_localctx)->value = expression(13);
      break;
    }

    case 18: {
      _localctx = _tracker.createInstance<NotContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(387);
      match(braneParser::T__27);
      setState(388);
      antlrcpp::downCast<NotContext *>(_localctx)->value = expression(6);
      break;
    }

    case 19: {
      _localctx = _tracker.createInstance<ParenContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(389);
      match(braneParser::T__19);
      setState(390);
      expression(0);
      setState(391);
      match(braneParser::T__20);
      break;
    }

    case 20: {
      _localctx = _tracker.createInstance<ScopeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(393);
      match(braneParser::T__7);
      setState(397);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 141937584092546304) != 0)) {
        setState(394);
        expression(0);
        setState(399);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(400);
      match(braneParser::T__8);
      break;
    }

    case 21: {
      _localctx = _tracker.createInstance<LambdaContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(401);
      antlrcpp::downCast<LambdaContext *>(_localctx)->returnType = type();
      setState(402);
      antlrcpp::downCast<LambdaContext *>(_localctx)->label = match(braneParser::T__15);
      setState(407);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == braneParser::T__3) {
        setState(403);
        match(braneParser::T__3);
        setState(404);
        antlrcpp::downCast<LambdaContext *>(_localctx)->capture = varCapture();
        setState(405);
        match(braneParser::T__5);
      }
      setState(409);
      match(braneParser::T__19);
      setState(410);
      antlrcpp::downCast<LambdaContext *>(_localctx)->arguments = argumentList();
      setState(411);
      match(braneParser::T__20);
      setState(412);
      match(braneParser::T__7);
      setState(416);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 141937584092546304) != 0)) {
        setState(413);
        expression(0);
        setState(418);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(419);
      match(braneParser::T__8);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(468);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(466);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MuldivContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(423);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(424);
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
          setState(425);
          antlrcpp::downCast<MuldivContext *>(_localctx)->right = expression(11);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddsubContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(426);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(427);
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
          setState(428);
          antlrcpp::downCast<AddsubContext *>(_localctx)->right = expression(10);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ComparisonContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(429);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(430);
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
          setState(431);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->right = expression(9);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<LogicContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(432);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(433);
          antlrcpp::downCast<LogicContext *>(_localctx)->opr = match(braneParser::LOGIC);
          setState(434);
          antlrcpp::downCast<LogicContext *>(_localctx)->right = expression(8);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<AssignmentContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lValue = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(435);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(436);
          match(braneParser::T__41);
          setState(437);
          antlrcpp::downCast<AssignmentContext *>(_localctx)->rValue = expression(3);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<RefAssignmentContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lValue = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(438);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(439);
          match(braneParser::T__42);
          setState(440);
          antlrcpp::downCast<RefAssignmentContext *>(_localctx)->rValue = expression(2);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<VoidExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(441);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(442);
          match(braneParser::T__9);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<FunctionCallContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->overrides = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(443);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(444);
          match(braneParser::T__19);
          setState(445);
          argumentPack();
          setState(446);
          match(braneParser::T__20);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<IndexAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(448);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(449);
          match(braneParser::T__3);
          setState(450);
          antlrcpp::downCast<IndexAccessContext *>(_localctx)->arg = expression(0);
          setState(451);
          match(braneParser::T__5);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(453);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(454);
          match(braneParser::T__38);
          setState(455);
          antlrcpp::downCast<MemberAccessContext *>(_localctx)->member = match(braneParser::ID);
          setState(457);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
          case 1: {
            setState(456);
            antlrcpp::downCast<MemberAccessContext *>(_localctx)->template_ = templateArgs();
            break;
          }

          default:
            break;
          }
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<CastContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->expr = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(459);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(460);
          match(braneParser::T__2);
          setState(461);
          type();
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<PostIncContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(462);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(463);
          match(braneParser::T__39);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<PostDecContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(464);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(465);
          match(braneParser::T__40);
          break;
        }

        default:
          break;
        } 
      }
      setState(470);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- SwitchCaseContext ------------------------------------------------------------------

braneParser::SwitchCaseContext::SwitchCaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::ExpressionContext *> braneParser::SwitchCaseContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::SwitchCaseContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}


size_t braneParser::SwitchCaseContext::getRuleIndex() const {
  return braneParser::RuleSwitchCase;
}


std::any braneParser::SwitchCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitSwitchCase(this);
  else
    return visitor->visitChildren(this);
}

braneParser::SwitchCaseContext* braneParser::switchCase() {
  SwitchCaseContext *_localctx = _tracker.createInstance<SwitchCaseContext>(_ctx, getState());
  enterRule(_localctx, 54, braneParser::RuleSwitchCase);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(491);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__43: {
        enterOuterAlt(_localctx, 1);
        setState(471);
        match(braneParser::T__43);
        setState(472);
        antlrcpp::downCast<SwitchCaseContext *>(_localctx)->value = expression(0);
        setState(473);
        match(braneParser::T__7);
        setState(477);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 141937584092546304) != 0)) {
          setState(474);
          expression(0);
          setState(479);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(480);
        match(braneParser::T__8);
        break;
      }

      case braneParser::T__44: {
        enterOuterAlt(_localctx, 2);
        setState(482);
        match(braneParser::T__44);
        setState(483);
        match(braneParser::T__7);
        setState(487);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 141937584092546304) != 0)) {
          setState(484);
          expression(0);
          setState(489);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(490);
        match(braneParser::T__8);
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

//----------------- MatchCaseContext ------------------------------------------------------------------

braneParser::MatchCaseContext::MatchCaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::ExpressionContext *> braneParser::MatchCaseContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::MatchCaseContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}


size_t braneParser::MatchCaseContext::getRuleIndex() const {
  return braneParser::RuleMatchCase;
}


std::any braneParser::MatchCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitMatchCase(this);
  else
    return visitor->visitChildren(this);
}

braneParser::MatchCaseContext* braneParser::matchCase() {
  MatchCaseContext *_localctx = _tracker.createInstance<MatchCaseContext>(_ctx, getState());
  enterRule(_localctx, 56, braneParser::RuleMatchCase);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(513);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__43: {
        enterOuterAlt(_localctx, 1);
        setState(493);
        match(braneParser::T__43);
        setState(494);
        antlrcpp::downCast<MatchCaseContext *>(_localctx)->pattern = expression(0);
        setState(495);
        match(braneParser::T__7);
        setState(499);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 141937584092546304) != 0)) {
          setState(496);
          expression(0);
          setState(501);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(502);
        match(braneParser::T__8);
        break;
      }

      case braneParser::T__44: {
        enterOuterAlt(_localctx, 2);
        setState(504);
        match(braneParser::T__44);
        setState(505);
        match(braneParser::T__7);
        setState(509);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 141937584092546304) != 0)) {
          setState(506);
          expression(0);
          setState(511);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(512);
        match(braneParser::T__8);
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

//----------------- MagicFunctionContext ------------------------------------------------------------------

braneParser::MagicFunctionContext::MagicFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t braneParser::MagicFunctionContext::getRuleIndex() const {
  return braneParser::RuleMagicFunction;
}

void braneParser::MagicFunctionContext::copyFrom(MagicFunctionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SizeOfPackContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::SizeOfPackContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::SizeOfPackContext::SizeOfPackContext(MagicFunctionContext *ctx) { copyFrom(ctx); }


std::any braneParser::SizeOfPackContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitSizeOfPack(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SizeOfTypeContext ------------------------------------------------------------------

braneParser::TypeContext* braneParser::SizeOfTypeContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}

braneParser::SizeOfTypeContext::SizeOfTypeContext(MagicFunctionContext *ctx) { copyFrom(ctx); }


std::any braneParser::SizeOfTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitSizeOfType(this);
  else
    return visitor->visitChildren(this);
}
braneParser::MagicFunctionContext* braneParser::magicFunction() {
  MagicFunctionContext *_localctx = _tracker.createInstance<MagicFunctionContext>(_ctx, getState());
  enterRule(_localctx, 58, braneParser::RuleMagicFunction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(525);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::SizeOfTypeContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(515);
      match(braneParser::T__45);
      setState(516);
      match(braneParser::T__19);
      setState(517);
      antlrcpp::downCast<SizeOfTypeContext *>(_localctx)->t = type();
      setState(518);
      match(braneParser::T__20);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::SizeOfPackContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(520);
      match(braneParser::T__45);
      setState(521);
      match(braneParser::T__11);
      setState(522);
      match(braneParser::T__19);
      setState(523);
      antlrcpp::downCast<SizeOfPackContext *>(_localctx)->id = match(braneParser::ID);
      setState(524);
      match(braneParser::T__20);
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

bool braneParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 26: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool braneParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 10);
    case 1: return precpred(_ctx, 9);
    case 2: return precpred(_ctx, 8);
    case 3: return precpred(_ctx, 7);
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);
    case 6: return precpred(_ctx, 22);
    case 7: return precpred(_ctx, 19);
    case 8: return precpred(_ctx, 17);
    case 9: return precpred(_ctx, 16);
    case 10: return precpred(_ctx, 15);
    case 11: return precpred(_ctx, 12);
    case 12: return precpred(_ctx, 11);

  default:
    break;
  }
  return true;
}

void braneParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  braneParserInitialize();
#else
  ::antlr4::internal::call_once(braneParserOnceFlag, braneParserInitialize);
#endif
}

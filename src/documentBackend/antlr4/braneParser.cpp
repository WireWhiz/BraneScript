
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
      "modules", "tags", "module", "module_item", "imports", "exports", 
      "mod_import", "mod_export", "global", "templateDefArg", "templateDef", 
      "templateArg", "templateArgs", "scopedID", "type", "valueType", "refType", 
      "sliceType", "declaration", "argumentListItem", "argumentList", "argumentPackItem", 
      "argumentPack", "bracketOpr", "functionSig", "functionStub", "function", 
      "capturedVar", "varCapture", "structDef", "structMember", "expressions", 
      "expression", "switchCase", "matchCase", "magicFunction"
    },
    std::vector<std::string>{
      "", "'['", "','", "']'", "'module'", "'imports'", "'{'", "'}'", "'exports'", 
      "';'", "'memory'", "'typedef'", "'...'", "'template'", "'<'", "'>'", 
      "'lambda'", "'::'", "'&'", "'mut'", "'('", "')'", "'constexpr'", "'opr'", 
      "'=='", "'!='", "'<='", "'>='", "'!'", "'const'", "'ext'", "'packed'", 
      "'struct'", "'return'", "'if'", "'else'", "'while'", "'for'", "'switch'", 
      "'match'", "'++'", "'--'", "'.'", "'as'", "'='", "'case'", "'default'", 
      "'sizeof'", "'fail'", "", "", "", "", "", "", "", "", "", "", "'*'", 
      "'/'", "'+'", "'-'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "COMMENT", 
      "NEWLINE", "BLOCK_COMMENT", "SPACE", "BOOL", "INT", "FLOAT", "CHAR", 
      "STRING", "ID", "MUL", "DIV", "ADD", "SUB", "LOGIC"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,63,542,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,1,0,5,0,74,8,0,10,0,12,0,77,9,0,1,0,3,0,80,8,0,1,1,1,1,1,1,1,1,5,1,
  	86,8,1,10,1,12,1,89,9,1,3,1,91,8,1,1,1,1,1,1,2,3,2,96,8,2,1,2,1,2,1,2,
  	5,2,101,8,2,10,2,12,2,104,9,2,1,3,1,3,3,3,108,8,3,1,4,1,4,1,4,5,4,113,
  	8,4,10,4,12,4,116,9,4,1,4,1,4,1,5,1,5,1,5,5,5,123,8,5,10,5,12,5,126,9,
  	5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,3,6,136,8,6,1,7,1,7,1,7,3,7,141,8,7,
  	1,8,1,8,1,8,1,8,1,9,1,9,3,9,149,8,9,1,9,3,9,152,8,9,1,9,1,9,1,10,1,10,
  	1,10,1,10,1,10,5,10,161,8,10,10,10,12,10,164,9,10,1,10,1,10,1,11,1,11,
  	1,11,1,11,3,11,172,8,11,1,12,1,12,1,12,1,12,5,12,178,8,12,10,12,12,12,
  	181,9,12,1,12,1,12,1,13,1,13,3,13,187,8,13,1,13,1,13,3,13,191,8,13,1,
  	14,1,14,1,14,3,14,196,8,14,1,15,1,15,1,16,1,16,3,16,202,8,16,1,16,1,16,
  	1,17,1,17,1,17,1,17,3,17,210,8,17,1,17,1,17,1,18,3,18,215,8,18,1,18,1,
  	18,1,18,1,19,1,19,1,19,1,19,3,19,224,8,19,1,20,1,20,1,20,5,20,229,8,20,
  	10,20,12,20,232,9,20,3,20,234,8,20,1,21,1,21,1,21,3,21,239,8,21,1,22,
  	1,22,1,22,5,22,244,8,22,10,22,12,22,247,9,22,3,22,249,8,22,1,23,1,23,
  	1,23,1,23,3,23,255,8,23,1,24,3,24,258,8,24,1,24,3,24,261,8,24,1,24,3,
  	24,264,8,24,1,24,1,24,1,24,1,24,1,24,3,24,271,8,24,3,24,273,8,24,1,24,
  	1,24,3,24,277,8,24,1,25,1,25,1,25,1,25,1,25,3,25,284,8,25,1,25,1,25,1,
  	26,1,26,1,26,1,26,1,26,3,26,293,8,26,1,26,1,26,1,26,1,26,1,27,3,27,300,
  	8,27,1,27,1,27,1,28,1,28,1,28,5,28,307,8,28,10,28,12,28,310,9,28,1,29,
  	3,29,313,8,29,1,29,3,29,316,8,29,1,29,3,29,319,8,29,1,29,1,29,1,29,1,
  	29,5,29,325,8,29,10,29,12,29,328,9,29,1,29,1,29,1,30,1,30,1,30,1,30,1,
  	30,1,30,1,30,3,30,339,8,30,1,31,1,31,1,31,1,31,5,31,345,8,31,10,31,12,
  	31,348,9,31,1,31,3,31,351,8,31,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,
  	1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,3,32,369,8,32,1,32,1,32,1,32,
  	1,32,1,32,1,32,1,32,1,32,3,32,379,8,32,1,32,1,32,1,32,1,32,1,32,1,32,
  	1,32,1,32,1,32,3,32,390,8,32,1,32,1,32,1,32,1,32,3,32,396,8,32,1,32,1,
  	32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,5,32,407,8,32,10,32,12,32,410,9,
  	32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,5,32,420,8,32,10,32,12,32,
  	423,9,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,3,32,435,8,
  	32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,
  	32,1,32,1,32,1,32,1,32,3,32,455,8,32,1,32,1,32,1,32,1,32,1,32,1,32,1,
  	32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,
  	32,1,32,1,32,3,32,480,8,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,
  	32,1,32,1,32,1,32,1,32,5,32,495,8,32,10,32,12,32,498,9,32,1,33,1,33,1,
  	33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,3,33,511,8,33,1,34,1,34,1,
  	34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,3,34,524,8,34,1,35,1,35,1,
  	35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,3,35,540,8,
  	35,1,35,0,1,64,36,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,
  	38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,0,5,2,0,16,16,58,58,
  	3,0,14,15,24,28,59,63,1,0,59,60,1,0,61,62,2,0,14,15,24,27,600,0,75,1,
  	0,0,0,2,81,1,0,0,0,4,95,1,0,0,0,6,107,1,0,0,0,8,109,1,0,0,0,10,119,1,
  	0,0,0,12,135,1,0,0,0,14,140,1,0,0,0,16,142,1,0,0,0,18,148,1,0,0,0,20,
  	155,1,0,0,0,22,171,1,0,0,0,24,173,1,0,0,0,26,184,1,0,0,0,28,195,1,0,0,
  	0,30,197,1,0,0,0,32,199,1,0,0,0,34,205,1,0,0,0,36,214,1,0,0,0,38,223,
  	1,0,0,0,40,233,1,0,0,0,42,238,1,0,0,0,44,248,1,0,0,0,46,254,1,0,0,0,48,
  	257,1,0,0,0,50,278,1,0,0,0,52,287,1,0,0,0,54,299,1,0,0,0,56,303,1,0,0,
  	0,58,312,1,0,0,0,60,338,1,0,0,0,62,346,1,0,0,0,64,454,1,0,0,0,66,510,
  	1,0,0,0,68,523,1,0,0,0,70,539,1,0,0,0,72,74,3,4,2,0,73,72,1,0,0,0,74,
  	77,1,0,0,0,75,73,1,0,0,0,75,76,1,0,0,0,76,79,1,0,0,0,77,75,1,0,0,0,78,
  	80,5,0,0,1,79,78,1,0,0,0,79,80,1,0,0,0,80,1,1,0,0,0,81,90,5,1,0,0,82,
  	87,5,57,0,0,83,84,5,2,0,0,84,86,5,57,0,0,85,83,1,0,0,0,86,89,1,0,0,0,
  	87,85,1,0,0,0,87,88,1,0,0,0,88,91,1,0,0,0,89,87,1,0,0,0,90,82,1,0,0,0,
  	90,91,1,0,0,0,91,92,1,0,0,0,92,93,5,3,0,0,93,3,1,0,0,0,94,96,3,2,1,0,
  	95,94,1,0,0,0,95,96,1,0,0,0,96,97,1,0,0,0,97,98,5,4,0,0,98,102,5,57,0,
  	0,99,101,3,6,3,0,100,99,1,0,0,0,101,104,1,0,0,0,102,100,1,0,0,0,102,103,
  	1,0,0,0,103,5,1,0,0,0,104,102,1,0,0,0,105,108,3,8,4,0,106,108,3,10,5,
  	0,107,105,1,0,0,0,107,106,1,0,0,0,108,7,1,0,0,0,109,110,5,5,0,0,110,114,
  	5,6,0,0,111,113,3,12,6,0,112,111,1,0,0,0,113,116,1,0,0,0,114,112,1,0,
  	0,0,114,115,1,0,0,0,115,117,1,0,0,0,116,114,1,0,0,0,117,118,5,7,0,0,118,
  	9,1,0,0,0,119,120,5,8,0,0,120,124,5,6,0,0,121,123,3,14,7,0,122,121,1,
  	0,0,0,123,126,1,0,0,0,124,122,1,0,0,0,124,125,1,0,0,0,125,127,1,0,0,0,
  	126,124,1,0,0,0,127,128,5,7,0,0,128,11,1,0,0,0,129,130,5,4,0,0,130,131,
  	5,57,0,0,131,136,5,9,0,0,132,133,5,10,0,0,133,134,5,57,0,0,134,136,5,
  	9,0,0,135,129,1,0,0,0,135,132,1,0,0,0,136,13,1,0,0,0,137,141,3,52,26,
  	0,138,141,3,58,29,0,139,141,3,16,8,0,140,137,1,0,0,0,140,138,1,0,0,0,
  	140,139,1,0,0,0,141,15,1,0,0,0,142,143,3,28,14,0,143,144,5,58,0,0,144,
  	145,5,9,0,0,145,17,1,0,0,0,146,149,3,28,14,0,147,149,5,11,0,0,148,146,
  	1,0,0,0,148,147,1,0,0,0,149,151,1,0,0,0,150,152,5,12,0,0,151,150,1,0,
  	0,0,151,152,1,0,0,0,152,153,1,0,0,0,153,154,5,58,0,0,154,19,1,0,0,0,155,
  	156,5,13,0,0,156,157,5,14,0,0,157,162,3,18,9,0,158,159,5,2,0,0,159,161,
  	3,18,9,0,160,158,1,0,0,0,161,164,1,0,0,0,162,160,1,0,0,0,162,163,1,0,
  	0,0,163,165,1,0,0,0,164,162,1,0,0,0,165,166,5,15,0,0,166,21,1,0,0,0,167,
  	172,3,28,14,0,168,172,3,64,32,0,169,170,5,58,0,0,170,172,5,12,0,0,171,
  	167,1,0,0,0,171,168,1,0,0,0,171,169,1,0,0,0,172,23,1,0,0,0,173,174,5,
  	14,0,0,174,179,3,22,11,0,175,176,5,2,0,0,176,178,3,22,11,0,177,175,1,
  	0,0,0,178,181,1,0,0,0,179,177,1,0,0,0,179,180,1,0,0,0,180,182,1,0,0,0,
  	181,179,1,0,0,0,182,183,5,15,0,0,183,25,1,0,0,0,184,186,7,0,0,0,185,187,
  	3,24,12,0,186,185,1,0,0,0,186,187,1,0,0,0,187,190,1,0,0,0,188,189,5,17,
  	0,0,189,191,3,26,13,0,190,188,1,0,0,0,190,191,1,0,0,0,191,27,1,0,0,0,
  	192,196,3,30,15,0,193,196,3,32,16,0,194,196,3,34,17,0,195,192,1,0,0,0,
  	195,193,1,0,0,0,195,194,1,0,0,0,196,29,1,0,0,0,197,198,3,26,13,0,198,
  	31,1,0,0,0,199,201,5,18,0,0,200,202,3,26,13,0,201,200,1,0,0,0,201,202,
  	1,0,0,0,202,203,1,0,0,0,203,204,3,28,14,0,204,33,1,0,0,0,205,206,5,1,
  	0,0,206,209,3,28,14,0,207,208,5,9,0,0,208,210,5,54,0,0,209,207,1,0,0,
  	0,209,210,1,0,0,0,210,211,1,0,0,0,211,212,5,3,0,0,212,35,1,0,0,0,213,
  	215,5,19,0,0,214,213,1,0,0,0,214,215,1,0,0,0,215,216,1,0,0,0,216,217,
  	3,28,14,0,217,218,5,58,0,0,218,37,1,0,0,0,219,224,3,36,18,0,220,221,5,
  	58,0,0,221,222,5,12,0,0,222,224,5,58,0,0,223,219,1,0,0,0,223,220,1,0,
  	0,0,224,39,1,0,0,0,225,230,3,38,19,0,226,227,5,2,0,0,227,229,3,38,19,
  	0,228,226,1,0,0,0,229,232,1,0,0,0,230,228,1,0,0,0,230,231,1,0,0,0,231,
  	234,1,0,0,0,232,230,1,0,0,0,233,225,1,0,0,0,233,234,1,0,0,0,234,41,1,
  	0,0,0,235,239,3,64,32,0,236,237,5,58,0,0,237,239,5,12,0,0,238,235,1,0,
  	0,0,238,236,1,0,0,0,239,43,1,0,0,0,240,245,3,42,21,0,241,242,5,2,0,0,
  	242,244,3,42,21,0,243,241,1,0,0,0,244,247,1,0,0,0,245,243,1,0,0,0,245,
  	246,1,0,0,0,246,249,1,0,0,0,247,245,1,0,0,0,248,240,1,0,0,0,248,249,1,
  	0,0,0,249,45,1,0,0,0,250,251,5,20,0,0,251,255,5,21,0,0,252,253,5,1,0,
  	0,253,255,5,3,0,0,254,250,1,0,0,0,254,252,1,0,0,0,255,47,1,0,0,0,256,
  	258,3,2,1,0,257,256,1,0,0,0,257,258,1,0,0,0,258,260,1,0,0,0,259,261,3,
  	20,10,0,260,259,1,0,0,0,260,261,1,0,0,0,261,263,1,0,0,0,262,264,5,22,
  	0,0,263,262,1,0,0,0,263,264,1,0,0,0,264,276,1,0,0,0,265,272,3,28,14,0,
  	266,273,5,58,0,0,267,270,5,23,0,0,268,271,7,1,0,0,269,271,3,46,23,0,270,
  	268,1,0,0,0,270,269,1,0,0,0,271,273,1,0,0,0,272,266,1,0,0,0,272,267,1,
  	0,0,0,273,277,1,0,0,0,274,275,5,23,0,0,275,277,3,28,14,0,276,265,1,0,
  	0,0,276,274,1,0,0,0,277,49,1,0,0,0,278,279,3,48,24,0,279,280,5,20,0,0,
  	280,281,3,40,20,0,281,283,5,21,0,0,282,284,5,29,0,0,283,282,1,0,0,0,283,
  	284,1,0,0,0,284,285,1,0,0,0,285,286,5,30,0,0,286,51,1,0,0,0,287,288,3,
  	48,24,0,288,289,5,20,0,0,289,290,3,40,20,0,290,292,5,21,0,0,291,293,5,
  	29,0,0,292,291,1,0,0,0,292,293,1,0,0,0,293,294,1,0,0,0,294,295,5,6,0,
  	0,295,296,3,62,31,0,296,297,5,7,0,0,297,53,1,0,0,0,298,300,5,18,0,0,299,
  	298,1,0,0,0,299,300,1,0,0,0,300,301,1,0,0,0,301,302,3,26,13,0,302,55,
  	1,0,0,0,303,308,3,54,27,0,304,305,5,2,0,0,305,307,3,54,27,0,306,304,1,
  	0,0,0,307,310,1,0,0,0,308,306,1,0,0,0,308,309,1,0,0,0,309,57,1,0,0,0,
  	310,308,1,0,0,0,311,313,3,2,1,0,312,311,1,0,0,0,312,313,1,0,0,0,313,315,
  	1,0,0,0,314,316,3,20,10,0,315,314,1,0,0,0,315,316,1,0,0,0,316,318,1,0,
  	0,0,317,319,5,31,0,0,318,317,1,0,0,0,318,319,1,0,0,0,319,320,1,0,0,0,
  	320,321,5,32,0,0,321,322,5,58,0,0,322,326,5,6,0,0,323,325,3,60,30,0,324,
  	323,1,0,0,0,325,328,1,0,0,0,326,324,1,0,0,0,326,327,1,0,0,0,327,329,1,
  	0,0,0,328,326,1,0,0,0,329,330,5,7,0,0,330,59,1,0,0,0,331,332,3,50,25,
  	0,332,333,5,9,0,0,333,339,1,0,0,0,334,339,3,52,26,0,335,336,3,36,18,0,
  	336,337,5,9,0,0,337,339,1,0,0,0,338,331,1,0,0,0,338,334,1,0,0,0,338,335,
  	1,0,0,0,339,61,1,0,0,0,340,341,3,64,32,0,341,342,5,9,0,0,342,345,1,0,
  	0,0,343,345,5,9,0,0,344,340,1,0,0,0,344,343,1,0,0,0,345,348,1,0,0,0,346,
  	344,1,0,0,0,346,347,1,0,0,0,347,350,1,0,0,0,348,346,1,0,0,0,349,351,3,
  	64,32,0,350,349,1,0,0,0,350,351,1,0,0,0,351,63,1,0,0,0,352,353,6,32,-1,
  	0,353,455,5,53,0,0,354,455,5,54,0,0,355,455,5,55,0,0,356,455,5,56,0,0,
  	357,455,5,57,0,0,358,359,5,6,0,0,359,360,3,62,31,0,360,361,5,7,0,0,361,
  	455,1,0,0,0,362,363,5,20,0,0,363,364,3,64,32,0,364,365,5,21,0,0,365,455,
  	1,0,0,0,366,368,5,33,0,0,367,369,3,64,32,0,368,367,1,0,0,0,368,369,1,
  	0,0,0,369,370,1,0,0,0,370,455,5,9,0,0,371,372,5,34,0,0,372,373,5,20,0,
  	0,373,374,3,64,32,0,374,375,5,21,0,0,375,378,3,64,32,0,376,377,5,35,0,
  	0,377,379,3,64,32,0,378,376,1,0,0,0,378,379,1,0,0,0,379,455,1,0,0,0,380,
  	381,5,36,0,0,381,382,5,20,0,0,382,383,3,64,32,0,383,384,5,21,0,0,384,
  	385,3,64,32,24,385,455,1,0,0,0,386,387,5,37,0,0,387,389,5,20,0,0,388,
  	390,3,64,32,0,389,388,1,0,0,0,389,390,1,0,0,0,390,391,1,0,0,0,391,392,
  	5,9,0,0,392,393,3,64,32,0,393,395,5,9,0,0,394,396,3,64,32,0,395,394,1,
  	0,0,0,395,396,1,0,0,0,396,397,1,0,0,0,397,398,5,21,0,0,398,399,3,64,32,
  	23,399,455,1,0,0,0,400,401,5,38,0,0,401,402,5,20,0,0,402,403,3,64,32,
  	0,403,404,5,21,0,0,404,408,5,6,0,0,405,407,3,66,33,0,406,405,1,0,0,0,
  	407,410,1,0,0,0,408,406,1,0,0,0,408,409,1,0,0,0,409,411,1,0,0,0,410,408,
  	1,0,0,0,411,412,5,7,0,0,412,455,1,0,0,0,413,414,5,39,0,0,414,415,5,20,
  	0,0,415,416,3,64,32,0,416,417,5,21,0,0,417,421,5,6,0,0,418,420,3,68,34,
  	0,419,418,1,0,0,0,420,423,1,0,0,0,421,419,1,0,0,0,421,422,1,0,0,0,422,
  	424,1,0,0,0,423,421,1,0,0,0,424,425,5,7,0,0,425,455,1,0,0,0,426,455,3,
  	36,18,0,427,455,3,26,13,0,428,429,3,28,14,0,429,434,5,16,0,0,430,431,
  	5,1,0,0,431,432,3,56,28,0,432,433,5,3,0,0,433,435,1,0,0,0,434,430,1,0,
  	0,0,434,435,1,0,0,0,435,436,1,0,0,0,436,437,5,20,0,0,437,438,3,40,20,
  	0,438,439,5,21,0,0,439,440,5,6,0,0,440,441,3,62,31,0,441,442,5,7,0,0,
  	442,455,1,0,0,0,443,444,5,40,0,0,444,455,3,64,32,17,445,446,5,41,0,0,
  	446,455,3,64,32,16,447,448,5,28,0,0,448,455,3,64,32,13,449,450,5,59,0,
  	0,450,455,3,64,32,12,451,452,5,18,0,0,452,455,3,64,32,11,453,455,3,70,
  	35,0,454,352,1,0,0,0,454,354,1,0,0,0,454,355,1,0,0,0,454,356,1,0,0,0,
  	454,357,1,0,0,0,454,358,1,0,0,0,454,362,1,0,0,0,454,366,1,0,0,0,454,371,
  	1,0,0,0,454,380,1,0,0,0,454,386,1,0,0,0,454,400,1,0,0,0,454,413,1,0,0,
  	0,454,426,1,0,0,0,454,427,1,0,0,0,454,428,1,0,0,0,454,443,1,0,0,0,454,
  	445,1,0,0,0,454,447,1,0,0,0,454,449,1,0,0,0,454,451,1,0,0,0,454,453,1,
  	0,0,0,455,496,1,0,0,0,456,457,10,7,0,0,457,458,7,2,0,0,458,495,3,64,32,
  	8,459,460,10,6,0,0,460,461,7,3,0,0,461,495,3,64,32,7,462,463,10,5,0,0,
  	463,464,7,4,0,0,464,495,3,64,32,6,465,466,10,4,0,0,466,467,5,63,0,0,467,
  	495,3,64,32,5,468,469,10,3,0,0,469,470,5,44,0,0,470,495,3,64,32,4,471,
  	472,10,15,0,0,472,495,5,40,0,0,473,474,10,14,0,0,474,495,5,41,0,0,475,
  	476,10,10,0,0,476,477,5,42,0,0,477,479,5,58,0,0,478,480,3,24,12,0,479,
  	478,1,0,0,0,479,480,1,0,0,0,480,495,1,0,0,0,481,482,10,9,0,0,482,483,
  	5,1,0,0,483,484,3,64,32,0,484,485,5,3,0,0,485,495,1,0,0,0,486,487,10,
  	8,0,0,487,488,5,43,0,0,488,495,3,28,14,0,489,490,10,2,0,0,490,491,5,20,
  	0,0,491,492,3,44,22,0,492,493,5,21,0,0,493,495,1,0,0,0,494,456,1,0,0,
  	0,494,459,1,0,0,0,494,462,1,0,0,0,494,465,1,0,0,0,494,468,1,0,0,0,494,
  	471,1,0,0,0,494,473,1,0,0,0,494,475,1,0,0,0,494,481,1,0,0,0,494,486,1,
  	0,0,0,494,489,1,0,0,0,495,498,1,0,0,0,496,494,1,0,0,0,496,497,1,0,0,0,
  	497,65,1,0,0,0,498,496,1,0,0,0,499,500,5,45,0,0,500,501,3,64,32,0,501,
  	502,5,6,0,0,502,503,3,62,31,0,503,504,5,7,0,0,504,511,1,0,0,0,505,506,
  	5,46,0,0,506,507,5,6,0,0,507,508,3,62,31,0,508,509,5,7,0,0,509,511,1,
  	0,0,0,510,499,1,0,0,0,510,505,1,0,0,0,511,67,1,0,0,0,512,513,5,45,0,0,
  	513,514,3,64,32,0,514,515,5,6,0,0,515,516,3,62,31,0,516,517,5,7,0,0,517,
  	524,1,0,0,0,518,519,5,46,0,0,519,520,5,6,0,0,520,521,3,62,31,0,521,522,
  	5,7,0,0,522,524,1,0,0,0,523,512,1,0,0,0,523,518,1,0,0,0,524,69,1,0,0,
  	0,525,526,5,47,0,0,526,527,5,20,0,0,527,528,3,28,14,0,528,529,5,21,0,
  	0,529,540,1,0,0,0,530,531,5,47,0,0,531,532,5,12,0,0,532,533,5,20,0,0,
  	533,534,5,58,0,0,534,540,5,21,0,0,535,536,5,48,0,0,536,537,5,20,0,0,537,
  	538,5,57,0,0,538,540,5,21,0,0,539,525,1,0,0,0,539,530,1,0,0,0,539,535,
  	1,0,0,0,540,71,1,0,0,0,61,75,79,87,90,95,102,107,114,124,135,140,148,
  	151,162,171,179,186,190,195,201,209,214,223,230,233,238,245,248,254,257,
  	260,263,270,272,276,283,292,299,308,312,315,318,326,338,344,346,350,368,
  	378,389,395,408,421,434,454,479,494,496,510,523,539
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
    setState(75);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__0

    || _la == braneParser::T__3) {
      setState(72);
      module();
      setState(77);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(79);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(78);
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
  enterRule(_localctx, 2, braneParser::RuleTags);
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
    match(braneParser::T__0);
    setState(90);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::STRING) {
      setState(82);
      antlrcpp::downCast<TagsContext *>(_localctx)->tag = match(braneParser::STRING);
      setState(87);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__1) {
        setState(83);
        match(braneParser::T__1);
        setState(84);
        antlrcpp::downCast<TagsContext *>(_localctx)->tag = match(braneParser::STRING);
        setState(89);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(92);
    match(braneParser::T__2);
   
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

tree::TerminalNode* braneParser::ModuleContext::STRING() {
  return getToken(braneParser::STRING, 0);
}

std::vector<braneParser::Module_itemContext *> braneParser::ModuleContext::module_item() {
  return getRuleContexts<braneParser::Module_itemContext>();
}

braneParser::Module_itemContext* braneParser::ModuleContext::module_item(size_t i) {
  return getRuleContext<braneParser::Module_itemContext>(i);
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
  enterRule(_localctx, 4, braneParser::RuleModule);
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
    setState(95);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__0) {
      setState(94);
      antlrcpp::downCast<ModuleContext *>(_localctx)->modTags = tags();
    }
    setState(97);
    match(braneParser::T__3);
    setState(98);
    antlrcpp::downCast<ModuleContext *>(_localctx)->id = match(braneParser::STRING);
    setState(102);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__4

    || _la == braneParser::T__7) {
      setState(99);
      module_item();
      setState(104);
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

//----------------- Module_itemContext ------------------------------------------------------------------

braneParser::Module_itemContext::Module_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::ImportsContext* braneParser::Module_itemContext::imports() {
  return getRuleContext<braneParser::ImportsContext>(0);
}

braneParser::ExportsContext* braneParser::Module_itemContext::exports() {
  return getRuleContext<braneParser::ExportsContext>(0);
}


size_t braneParser::Module_itemContext::getRuleIndex() const {
  return braneParser::RuleModule_item;
}


std::any braneParser::Module_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitModule_item(this);
  else
    return visitor->visitChildren(this);
}

braneParser::Module_itemContext* braneParser::module_item() {
  Module_itemContext *_localctx = _tracker.createInstance<Module_itemContext>(_ctx, getState());
  enterRule(_localctx, 6, braneParser::RuleModule_item);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(107);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__4: {
        enterOuterAlt(_localctx, 1);
        setState(105);
        imports();
        break;
      }

      case braneParser::T__7: {
        enterOuterAlt(_localctx, 2);
        setState(106);
        exports();
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

//----------------- ImportsContext ------------------------------------------------------------------

braneParser::ImportsContext::ImportsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::Mod_importContext *> braneParser::ImportsContext::mod_import() {
  return getRuleContexts<braneParser::Mod_importContext>();
}

braneParser::Mod_importContext* braneParser::ImportsContext::mod_import(size_t i) {
  return getRuleContext<braneParser::Mod_importContext>(i);
}


size_t braneParser::ImportsContext::getRuleIndex() const {
  return braneParser::RuleImports;
}


std::any braneParser::ImportsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitImports(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ImportsContext* braneParser::imports() {
  ImportsContext *_localctx = _tracker.createInstance<ImportsContext>(_ctx, getState());
  enterRule(_localctx, 8, braneParser::RuleImports);
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
    setState(109);
    match(braneParser::T__4);
    setState(110);
    match(braneParser::T__5);
    setState(114);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__3

    || _la == braneParser::T__9) {
      setState(111);
      mod_import();
      setState(116);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(117);
    match(braneParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExportsContext ------------------------------------------------------------------

braneParser::ExportsContext::ExportsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::Mod_exportContext *> braneParser::ExportsContext::mod_export() {
  return getRuleContexts<braneParser::Mod_exportContext>();
}

braneParser::Mod_exportContext* braneParser::ExportsContext::mod_export(size_t i) {
  return getRuleContext<braneParser::Mod_exportContext>(i);
}


size_t braneParser::ExportsContext::getRuleIndex() const {
  return braneParser::RuleExports;
}


std::any braneParser::ExportsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitExports(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ExportsContext* braneParser::exports() {
  ExportsContext *_localctx = _tracker.createInstance<ExportsContext>(_ctx, getState());
  enterRule(_localctx, 10, braneParser::RuleExports);
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
    setState(119);
    match(braneParser::T__7);
    setState(120);
    match(braneParser::T__5);
    setState(124);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 288230382607081474) != 0)) {
      setState(121);
      mod_export();
      setState(126);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(127);
    match(braneParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Mod_importContext ------------------------------------------------------------------

braneParser::Mod_importContext::Mod_importContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t braneParser::Mod_importContext::getRuleIndex() const {
  return braneParser::RuleMod_import;
}

void braneParser::Mod_importContext::copyFrom(Mod_importContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ImportModuleContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::ImportModuleContext::STRING() {
  return getToken(braneParser::STRING, 0);
}

braneParser::ImportModuleContext::ImportModuleContext(Mod_importContext *ctx) { copyFrom(ctx); }


std::any braneParser::ImportModuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitImportModule(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ImportMemoryContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::ImportMemoryContext::STRING() {
  return getToken(braneParser::STRING, 0);
}

braneParser::ImportMemoryContext::ImportMemoryContext(Mod_importContext *ctx) { copyFrom(ctx); }


std::any braneParser::ImportMemoryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitImportMemory(this);
  else
    return visitor->visitChildren(this);
}
braneParser::Mod_importContext* braneParser::mod_import() {
  Mod_importContext *_localctx = _tracker.createInstance<Mod_importContext>(_ctx, getState());
  enterRule(_localctx, 12, braneParser::RuleMod_import);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(135);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__3: {
        _localctx = _tracker.createInstance<braneParser::ImportModuleContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(129);
        match(braneParser::T__3);
        setState(130);
        antlrcpp::downCast<ImportModuleContext *>(_localctx)->id = match(braneParser::STRING);
        setState(131);
        match(braneParser::T__8);
        break;
      }

      case braneParser::T__9: {
        _localctx = _tracker.createInstance<braneParser::ImportMemoryContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(132);
        match(braneParser::T__9);
        setState(133);
        antlrcpp::downCast<ImportMemoryContext *>(_localctx)->id = match(braneParser::STRING);
        setState(134);
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

//----------------- Mod_exportContext ------------------------------------------------------------------

braneParser::Mod_exportContext::Mod_exportContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::FunctionContext* braneParser::Mod_exportContext::function() {
  return getRuleContext<braneParser::FunctionContext>(0);
}

braneParser::StructDefContext* braneParser::Mod_exportContext::structDef() {
  return getRuleContext<braneParser::StructDefContext>(0);
}

braneParser::GlobalContext* braneParser::Mod_exportContext::global() {
  return getRuleContext<braneParser::GlobalContext>(0);
}


size_t braneParser::Mod_exportContext::getRuleIndex() const {
  return braneParser::RuleMod_export;
}


std::any braneParser::Mod_exportContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitMod_export(this);
  else
    return visitor->visitChildren(this);
}

braneParser::Mod_exportContext* braneParser::mod_export() {
  Mod_exportContext *_localctx = _tracker.createInstance<Mod_exportContext>(_ctx, getState());
  enterRule(_localctx, 14, braneParser::RuleMod_export);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(140);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(137);
      function();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(138);
      structDef();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(139);
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
  enterRule(_localctx, 16, braneParser::RuleGlobal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(142);
    type();
    setState(143);
    antlrcpp::downCast<GlobalContext *>(_localctx)->id = match(braneParser::ID);
    setState(144);
    match(braneParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateDefArgContext ------------------------------------------------------------------

braneParser::TemplateDefArgContext::TemplateDefArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* braneParser::TemplateDefArgContext::ID() {
  return getToken(braneParser::ID, 0);
}

braneParser::TypeContext* braneParser::TemplateDefArgContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}


size_t braneParser::TemplateDefArgContext::getRuleIndex() const {
  return braneParser::RuleTemplateDefArg;
}


std::any braneParser::TemplateDefArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitTemplateDefArg(this);
  else
    return visitor->visitChildren(this);
}

braneParser::TemplateDefArgContext* braneParser::templateDefArg() {
  TemplateDefArgContext *_localctx = _tracker.createInstance<TemplateDefArgContext>(_ctx, getState());
  enterRule(_localctx, 18, braneParser::RuleTemplateDefArg);
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
    setState(148);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__0:
      case braneParser::T__15:
      case braneParser::T__17:
      case braneParser::ID: {
        setState(146);
        antlrcpp::downCast<TemplateDefArgContext *>(_localctx)->exprType = type();
        break;
      }

      case braneParser::T__10: {
        setState(147);
        antlrcpp::downCast<TemplateDefArgContext *>(_localctx)->isTypedef = match(braneParser::T__10);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(151);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__11) {
      setState(150);
      antlrcpp::downCast<TemplateDefArgContext *>(_localctx)->isPack = match(braneParser::T__11);
    }
    setState(153);
    antlrcpp::downCast<TemplateDefArgContext *>(_localctx)->id = match(braneParser::ID);
   
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

std::vector<braneParser::TemplateDefArgContext *> braneParser::TemplateDefContext::templateDefArg() {
  return getRuleContexts<braneParser::TemplateDefArgContext>();
}

braneParser::TemplateDefArgContext* braneParser::TemplateDefContext::templateDefArg(size_t i) {
  return getRuleContext<braneParser::TemplateDefArgContext>(i);
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
  enterRule(_localctx, 20, braneParser::RuleTemplateDef);
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
    match(braneParser::T__12);
    setState(156);
    match(braneParser::T__13);
    setState(157);
    templateDefArg();
    setState(162);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__1) {
      setState(158);
      match(braneParser::T__1);
      setState(159);
      templateDefArg();
      setState(164);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(165);
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
  enterRule(_localctx, 22, braneParser::RuleTemplateArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(171);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::TemplateTypeArgContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(167);
      antlrcpp::downCast<TemplateTypeArgContext *>(_localctx)->t = type();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::TemplateExprArgContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(168);
      antlrcpp::downCast<TemplateExprArgContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::PackExpansionArgContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(169);
      antlrcpp::downCast<PackExpansionArgContext *>(_localctx)->packID = match(braneParser::ID);
      setState(170);
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
  enterRule(_localctx, 24, braneParser::RuleTemplateArgs);
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
    setState(173);
    match(braneParser::T__13);
    setState(174);
    templateArg();
    setState(179);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__1) {
      setState(175);
      match(braneParser::T__1);
      setState(176);
      templateArg();
      setState(181);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(182);
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
  enterRule(_localctx, 26, braneParser::RuleScopedID);
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
    setState(186);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      setState(185);
      antlrcpp::downCast<ScopedIDContext *>(_localctx)->template_ = templateArgs();
      break;
    }

    default:
      break;
    }
    setState(190);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      setState(188);
      match(braneParser::T__16);
      setState(189);
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

braneParser::ValueTypeContext* braneParser::TypeContext::valueType() {
  return getRuleContext<braneParser::ValueTypeContext>(0);
}

braneParser::RefTypeContext* braneParser::TypeContext::refType() {
  return getRuleContext<braneParser::RefTypeContext>(0);
}

braneParser::SliceTypeContext* braneParser::TypeContext::sliceType() {
  return getRuleContext<braneParser::SliceTypeContext>(0);
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
  enterRule(_localctx, 28, braneParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(195);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__15:
      case braneParser::ID: {
        setState(192);
        valueType();
        break;
      }

      case braneParser::T__17: {
        setState(193);
        refType();
        break;
      }

      case braneParser::T__0: {
        setState(194);
        sliceType();
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

//----------------- ValueTypeContext ------------------------------------------------------------------

braneParser::ValueTypeContext::ValueTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::ScopedIDContext* braneParser::ValueTypeContext::scopedID() {
  return getRuleContext<braneParser::ScopedIDContext>(0);
}


size_t braneParser::ValueTypeContext::getRuleIndex() const {
  return braneParser::RuleValueType;
}


std::any braneParser::ValueTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitValueType(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ValueTypeContext* braneParser::valueType() {
  ValueTypeContext *_localctx = _tracker.createInstance<ValueTypeContext>(_ctx, getState());
  enterRule(_localctx, 30, braneParser::RuleValueType);

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
    antlrcpp::downCast<ValueTypeContext *>(_localctx)->name = scopedID();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RefTypeContext ------------------------------------------------------------------

braneParser::RefTypeContext::RefTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::TypeContext* braneParser::RefTypeContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}

braneParser::ScopedIDContext* braneParser::RefTypeContext::scopedID() {
  return getRuleContext<braneParser::ScopedIDContext>(0);
}


size_t braneParser::RefTypeContext::getRuleIndex() const {
  return braneParser::RuleRefType;
}


std::any braneParser::RefTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitRefType(this);
  else
    return visitor->visitChildren(this);
}

braneParser::RefTypeContext* braneParser::refType() {
  RefTypeContext *_localctx = _tracker.createInstance<RefTypeContext>(_ctx, getState());
  enterRule(_localctx, 32, braneParser::RuleRefType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
    match(braneParser::T__17);
    setState(201);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(200);
      antlrcpp::downCast<RefTypeContext *>(_localctx)->refSource = scopedID();
      break;
    }

    default:
      break;
    }
    setState(203);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SliceTypeContext ------------------------------------------------------------------

braneParser::SliceTypeContext::SliceTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

braneParser::TypeContext* braneParser::SliceTypeContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}

tree::TerminalNode* braneParser::SliceTypeContext::INT() {
  return getToken(braneParser::INT, 0);
}


size_t braneParser::SliceTypeContext::getRuleIndex() const {
  return braneParser::RuleSliceType;
}


std::any braneParser::SliceTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitSliceType(this);
  else
    return visitor->visitChildren(this);
}

braneParser::SliceTypeContext* braneParser::sliceType() {
  SliceTypeContext *_localctx = _tracker.createInstance<SliceTypeContext>(_ctx, getState());
  enterRule(_localctx, 34, braneParser::RuleSliceType);
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
    match(braneParser::T__0);
    setState(206);
    type();
    setState(209);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__8) {
      setState(207);
      match(braneParser::T__8);
      setState(208);
      antlrcpp::downCast<SliceTypeContext *>(_localctx)->size = match(braneParser::INT);
    }
    setState(211);
    match(braneParser::T__2);
   
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
  enterRule(_localctx, 36, braneParser::RuleDeclaration);
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
    setState(214);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__18) {
      setState(213);
      antlrcpp::downCast<DeclarationContext *>(_localctx)->mut = match(braneParser::T__18);
    }
    setState(216);
    type();
    setState(217);
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
  enterRule(_localctx, 38, braneParser::RuleArgumentListItem);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(219);
      declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(220);
      antlrcpp::downCast<ArgumentListItemContext *>(_localctx)->pack = match(braneParser::ID);
      setState(221);
      match(braneParser::T__11);
      setState(222);
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
  enterRule(_localctx, 40, braneParser::RuleArgumentList);
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
    setState(233);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 288230376152563714) != 0)) {
      setState(225);
      argumentListItem();
      setState(230);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__1) {
        setState(226);
        match(braneParser::T__1);
        setState(227);
        argumentListItem();
        setState(232);
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
  enterRule(_localctx, 42, braneParser::RuleArgumentPackItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(238);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(235);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->expr = expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(236);
      antlrcpp::downCast<ArgumentPackItemContext *>(_localctx)->packID = match(braneParser::ID);
      setState(237);
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
  enterRule(_localctx, 44, braneParser::RuleArgumentPack);
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
    setState(248);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1144340873184346178) != 0)) {
      setState(240);
      argumentPackItem();
      setState(245);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__1) {
        setState(241);
        match(braneParser::T__1);
        setState(242);
        argumentPackItem();
        setState(247);
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
  enterRule(_localctx, 46, braneParser::RuleBracketOpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(254);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__19: {
        enterOuterAlt(_localctx, 1);
        setState(250);
        match(braneParser::T__19);
        setState(251);
        match(braneParser::T__20);
        break;
      }

      case braneParser::T__0: {
        enterOuterAlt(_localctx, 2);
        setState(252);
        match(braneParser::T__0);
        setState(253);
        match(braneParser::T__2);
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
  enterRule(_localctx, 48, braneParser::RuleFunctionSig);
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
    setState(257);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      setState(256);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->funcTags = tags();
      break;
    }

    default:
      break;
    }
    setState(260);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__12) {
      setState(259);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->template_ = templateDef();
    }
    setState(263);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__21) {
      setState(262);
      antlrcpp::downCast<FunctionSigContext *>(_localctx)->isConstexpr = match(braneParser::T__21);
    }
    setState(276);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__0:
      case braneParser::T__15:
      case braneParser::T__17:
      case braneParser::ID: {
        setState(265);
        type();
        setState(272);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case braneParser::ID: {
            setState(266);
            antlrcpp::downCast<FunctionSigContext *>(_localctx)->id = match(braneParser::ID);
            break;
          }

          case braneParser::T__22: {
            setState(267);
            match(braneParser::T__22);
            setState(270);
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
                setState(268);
                antlrcpp::downCast<FunctionSigContext *>(_localctx)->oprID = _input->LT(1);
                _la = _input->LA(1);
                if (!((((_la & ~ 0x3fULL) == 0) &&
                  ((1ULL << _la) & -576460751783280640) != 0))) {
                  antlrcpp::downCast<FunctionSigContext *>(_localctx)->oprID = _errHandler->recoverInline(this);
                }
                else {
                  _errHandler->reportMatch(this);
                  consume();
                }
                break;
              }

              case braneParser::T__0:
              case braneParser::T__19: {
                setState(269);
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
        setState(274);
        match(braneParser::T__22);
        setState(275);
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
  enterRule(_localctx, 50, braneParser::RuleFunctionStub);
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
    setState(278);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->sig = functionSig();
    setState(279);
    match(braneParser::T__19);
    setState(280);
    antlrcpp::downCast<FunctionStubContext *>(_localctx)->arguments = argumentList();
    setState(281);
    match(braneParser::T__20);
    setState(283);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__28) {
      setState(282);
      antlrcpp::downCast<FunctionStubContext *>(_localctx)->isConst = match(braneParser::T__28);
    }
    setState(285);
    match(braneParser::T__29);
   
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

braneParser::ExpressionsContext* braneParser::FunctionContext::expressions() {
  return getRuleContext<braneParser::ExpressionsContext>(0);
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
  enterRule(_localctx, 52, braneParser::RuleFunction);
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
    setState(287);
    antlrcpp::downCast<FunctionContext *>(_localctx)->sig = functionSig();
    setState(288);
    match(braneParser::T__19);
    setState(289);
    antlrcpp::downCast<FunctionContext *>(_localctx)->arguments = argumentList();
    setState(290);
    match(braneParser::T__20);
    setState(292);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__28) {
      setState(291);
      antlrcpp::downCast<FunctionContext *>(_localctx)->isConst = match(braneParser::T__28);
    }
    setState(294);
    match(braneParser::T__5);
    setState(295);
    antlrcpp::downCast<FunctionContext *>(_localctx)->content = expressions();
    setState(296);
    match(braneParser::T__6);
   
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
  enterRule(_localctx, 54, braneParser::RuleCapturedVar);
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
    setState(299);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__17) {
      setState(298);
      antlrcpp::downCast<CapturedVarContext *>(_localctx)->isRef = match(braneParser::T__17);
    }
    setState(301);
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
  enterRule(_localctx, 56, braneParser::RuleVarCapture);
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
    setState(303);
    capturedVar();
    setState(308);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == braneParser::T__1) {
      setState(304);
      match(braneParser::T__1);
      setState(305);
      capturedVar();
      setState(310);
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
  enterRule(_localctx, 58, braneParser::RuleStructDef);
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
    setState(312);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__0) {
      setState(311);
      antlrcpp::downCast<StructDefContext *>(_localctx)->structTags = tags();
    }
    setState(315);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__12) {
      setState(314);
      antlrcpp::downCast<StructDefContext *>(_localctx)->template_ = templateDef();
    }
    setState(318);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == braneParser::T__30) {
      setState(317);
      antlrcpp::downCast<StructDefContext *>(_localctx)->packed = match(braneParser::T__30);
    }
    setState(320);
    match(braneParser::T__31);
    setState(321);
    antlrcpp::downCast<StructDefContext *>(_localctx)->id = match(braneParser::ID);
    setState(322);
    match(braneParser::T__5);
    setState(326);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 288230376165154818) != 0)) {
      setState(323);
      antlrcpp::downCast<StructDefContext *>(_localctx)->memberVars = structMember();
      setState(328);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(329);
    match(braneParser::T__6);
   
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
  enterRule(_localctx, 60, braneParser::RuleStructMember);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(338);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::MemberFunctionStubContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(331);
      functionStub();
      setState(332);
      match(braneParser::T__8);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::MemberFunctionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(334);
      antlrcpp::downCast<MemberFunctionContext *>(_localctx)->func = function();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::MemberVariableContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(335);
      antlrcpp::downCast<MemberVariableContext *>(_localctx)->var = declaration();
      setState(336);
      match(braneParser::T__8);
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

//----------------- ExpressionsContext ------------------------------------------------------------------

braneParser::ExpressionsContext::ExpressionsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<braneParser::ExpressionContext *> braneParser::ExpressionsContext::expression() {
  return getRuleContexts<braneParser::ExpressionContext>();
}

braneParser::ExpressionContext* braneParser::ExpressionsContext::expression(size_t i) {
  return getRuleContext<braneParser::ExpressionContext>(i);
}


size_t braneParser::ExpressionsContext::getRuleIndex() const {
  return braneParser::RuleExpressions;
}


std::any braneParser::ExpressionsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitExpressions(this);
  else
    return visitor->visitChildren(this);
}

braneParser::ExpressionsContext* braneParser::expressions() {
  ExpressionsContext *_localctx = _tracker.createInstance<ExpressionsContext>(_ctx, getState());
  enterRule(_localctx, 62, braneParser::RuleExpressions);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(346);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(344);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case braneParser::T__0:
          case braneParser::T__5:
          case braneParser::T__15:
          case braneParser::T__17:
          case braneParser::T__18:
          case braneParser::T__19:
          case braneParser::T__27:
          case braneParser::T__32:
          case braneParser::T__33:
          case braneParser::T__35:
          case braneParser::T__36:
          case braneParser::T__37:
          case braneParser::T__38:
          case braneParser::T__39:
          case braneParser::T__40:
          case braneParser::T__46:
          case braneParser::T__47:
          case braneParser::BOOL:
          case braneParser::INT:
          case braneParser::FLOAT:
          case braneParser::CHAR:
          case braneParser::STRING:
          case braneParser::ID:
          case braneParser::MUL: {
            setState(340);
            expression(0);
            setState(341);
            match(braneParser::T__8);
            break;
          }

          case braneParser::T__8: {
            setState(343);
            match(braneParser::T__8);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(348);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    }
    setState(350);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1144340873184346178) != 0)) {
      setState(349);
      antlrcpp::downCast<ExpressionsContext *>(_localctx)->returnValue = expression(0);
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

//----------------- DerefContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::DerefContext::MUL() {
  return getToken(braneParser::MUL, 0);
}

braneParser::ExpressionContext* braneParser::DerefContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::DerefContext::DerefContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::DerefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitDeref(this);
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
//----------------- CastContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::CastContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::TypeContext* braneParser::CastContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
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
//----------------- LambdaContext ------------------------------------------------------------------

braneParser::TypeContext* braneParser::LambdaContext::type() {
  return getRuleContext<braneParser::TypeContext>(0);
}

braneParser::ArgumentListContext* braneParser::LambdaContext::argumentList() {
  return getRuleContext<braneParser::ArgumentListContext>(0);
}

braneParser::ExpressionsContext* braneParser::LambdaContext::expressions() {
  return getRuleContext<braneParser::ExpressionsContext>(0);
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
//----------------- RefContext ------------------------------------------------------------------

braneParser::ExpressionContext* braneParser::RefContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::RefContext::RefContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any braneParser::RefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitRef(this);
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

braneParser::ExpressionsContext* braneParser::ScopeContext::expressions() {
  return getRuleContext<braneParser::ExpressionsContext>(0);
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
  size_t startState = 64;
  enterRecursionRule(_localctx, 64, braneParser::RuleExpression, precedence);

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
    setState(454);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ConstBoolContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(353);
      match(braneParser::BOOL);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ConstIntContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(354);
      match(braneParser::INT);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ConstFloatContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(355);
      match(braneParser::FLOAT);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ConstCharContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(356);
      match(braneParser::CHAR);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<ConstStringContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(357);
      match(braneParser::STRING);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<ScopeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(358);
      match(braneParser::T__5);
      setState(359);
      antlrcpp::downCast<ScopeContext *>(_localctx)->content = expressions();
      setState(360);
      match(braneParser::T__6);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ParenContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(362);
      match(braneParser::T__19);
      setState(363);
      expression(0);
      setState(364);
      match(braneParser::T__20);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<ReturnContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(366);
      match(braneParser::T__32);
      setState(368);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1144340873184346178) != 0)) {
        setState(367);
        expression(0);
      }
      setState(370);
      match(braneParser::T__8);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<IfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(371);
      match(braneParser::T__33);
      setState(372);
      match(braneParser::T__19);
      setState(373);
      antlrcpp::downCast<IfContext *>(_localctx)->cond = expression(0);
      setState(374);
      match(braneParser::T__20);
      setState(375);
      antlrcpp::downCast<IfContext *>(_localctx)->operation = expression(0);
      setState(378);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
      case 1: {
        setState(376);
        match(braneParser::T__34);
        setState(377);
        antlrcpp::downCast<IfContext *>(_localctx)->elseOp = expression(0);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<WhileContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(380);
      match(braneParser::T__35);
      setState(381);
      match(braneParser::T__19);
      setState(382);
      antlrcpp::downCast<WhileContext *>(_localctx)->cond = expression(0);
      setState(383);
      match(braneParser::T__20);
      setState(384);
      antlrcpp::downCast<WhileContext *>(_localctx)->operation = expression(24);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<ForContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(386);
      match(braneParser::T__36);
      setState(387);
      match(braneParser::T__19);
      setState(389);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1144340873184346178) != 0)) {
        setState(388);
        antlrcpp::downCast<ForContext *>(_localctx)->init = expression(0);
      }
      setState(391);
      match(braneParser::T__8);
      setState(392);
      antlrcpp::downCast<ForContext *>(_localctx)->cond = expression(0);
      setState(393);
      match(braneParser::T__8);
      setState(395);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1144340873184346178) != 0)) {
        setState(394);
        antlrcpp::downCast<ForContext *>(_localctx)->step = expression(0);
      }
      setState(397);
      match(braneParser::T__20);
      setState(398);
      antlrcpp::downCast<ForContext *>(_localctx)->operation = expression(23);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<SwitchContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(400);
      match(braneParser::T__37);
      setState(401);
      match(braneParser::T__19);
      setState(402);
      antlrcpp::downCast<SwitchContext *>(_localctx)->value = expression(0);
      setState(403);
      match(braneParser::T__20);
      setState(404);
      match(braneParser::T__5);
      setState(408);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__44

      || _la == braneParser::T__45) {
        setState(405);
        switchCase();
        setState(410);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(411);
      match(braneParser::T__6);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<MatchContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(413);
      match(braneParser::T__38);
      setState(414);
      match(braneParser::T__19);
      setState(415);
      antlrcpp::downCast<MatchContext *>(_localctx)->value = expression(0);
      setState(416);
      match(braneParser::T__20);
      setState(417);
      match(braneParser::T__5);
      setState(421);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == braneParser::T__44

      || _la == braneParser::T__45) {
        setState(418);
        matchCase();
        setState(423);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(424);
      match(braneParser::T__6);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<DeclContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(426);
      declaration();
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<IdContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(427);
      scopedID();
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<LambdaContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(428);
      antlrcpp::downCast<LambdaContext *>(_localctx)->returnType = type();
      setState(429);
      antlrcpp::downCast<LambdaContext *>(_localctx)->label = match(braneParser::T__15);
      setState(434);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == braneParser::T__0) {
        setState(430);
        match(braneParser::T__0);
        setState(431);
        antlrcpp::downCast<LambdaContext *>(_localctx)->capture = varCapture();
        setState(432);
        match(braneParser::T__2);
      }
      setState(436);
      match(braneParser::T__19);
      setState(437);
      antlrcpp::downCast<LambdaContext *>(_localctx)->arguments = argumentList();
      setState(438);
      match(braneParser::T__20);
      setState(439);
      match(braneParser::T__5);
      setState(440);
      antlrcpp::downCast<LambdaContext *>(_localctx)->content = expressions();
      setState(441);
      match(braneParser::T__6);
      break;
    }

    case 17: {
      _localctx = _tracker.createInstance<PreIncContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(443);
      match(braneParser::T__39);
      setState(444);
      antlrcpp::downCast<PreIncContext *>(_localctx)->value = expression(17);
      break;
    }

    case 18: {
      _localctx = _tracker.createInstance<PreDecContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(445);
      match(braneParser::T__40);
      setState(446);
      antlrcpp::downCast<PreDecContext *>(_localctx)->value = expression(16);
      break;
    }

    case 19: {
      _localctx = _tracker.createInstance<NotContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(447);
      match(braneParser::T__27);
      setState(448);
      antlrcpp::downCast<NotContext *>(_localctx)->value = expression(13);
      break;
    }

    case 20: {
      _localctx = _tracker.createInstance<DerefContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(449);
      match(braneParser::MUL);
      setState(450);
      antlrcpp::downCast<DerefContext *>(_localctx)->value = expression(12);
      break;
    }

    case 21: {
      _localctx = _tracker.createInstance<RefContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(451);
      match(braneParser::T__17);
      setState(452);
      antlrcpp::downCast<RefContext *>(_localctx)->value = expression(11);
      break;
    }

    case 22: {
      _localctx = _tracker.createInstance<MagicFunctionCallContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(453);
      magicFunction();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(496);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(494);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MuldivContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(456);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(457);
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
          setState(458);
          antlrcpp::downCast<MuldivContext *>(_localctx)->right = expression(8);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddsubContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(459);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(460);
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
          setState(461);
          antlrcpp::downCast<AddsubContext *>(_localctx)->right = expression(7);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ComparisonContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(462);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(463);
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
          setState(464);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->right = expression(6);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<LogicContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(465);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(466);
          antlrcpp::downCast<LogicContext *>(_localctx)->opr = match(braneParser::LOGIC);
          setState(467);
          antlrcpp::downCast<LogicContext *>(_localctx)->right = expression(5);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<AssignmentContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(468);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(469);
          match(braneParser::T__43);
          setState(470);
          antlrcpp::downCast<AssignmentContext *>(_localctx)->right = expression(4);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<PostIncContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(471);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(472);
          match(braneParser::T__39);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<PostDecContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(473);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(474);
          match(braneParser::T__40);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(475);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(476);
          match(braneParser::T__41);
          setState(477);
          antlrcpp::downCast<MemberAccessContext *>(_localctx)->member = match(braneParser::ID);
          setState(479);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
          case 1: {
            setState(478);
            antlrcpp::downCast<MemberAccessContext *>(_localctx)->template_ = templateArgs();
            break;
          }

          default:
            break;
          }
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<IndexAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->base = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(481);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(482);
          match(braneParser::T__0);
          setState(483);
          antlrcpp::downCast<IndexAccessContext *>(_localctx)->arg = expression(0);
          setState(484);
          match(braneParser::T__2);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<CastContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->expr = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(486);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(487);
          match(braneParser::T__42);
          setState(488);
          antlrcpp::downCast<CastContext *>(_localctx)->targetType = type();
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<FunctionCallContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->overrides = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(489);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(490);
          match(braneParser::T__19);
          setState(491);
          argumentPack();
          setState(492);
          match(braneParser::T__20);
          break;
        }

        default:
          break;
        } 
      }
      setState(498);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
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

braneParser::ExpressionContext* braneParser::SwitchCaseContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::ExpressionsContext* braneParser::SwitchCaseContext::expressions() {
  return getRuleContext<braneParser::ExpressionsContext>(0);
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
  enterRule(_localctx, 66, braneParser::RuleSwitchCase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(510);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__44: {
        enterOuterAlt(_localctx, 1);
        setState(499);
        match(braneParser::T__44);
        setState(500);
        antlrcpp::downCast<SwitchCaseContext *>(_localctx)->value = expression(0);
        setState(501);
        match(braneParser::T__5);
        setState(502);
        antlrcpp::downCast<SwitchCaseContext *>(_localctx)->content = expressions();
        setState(503);
        match(braneParser::T__6);
        break;
      }

      case braneParser::T__45: {
        enterOuterAlt(_localctx, 2);
        setState(505);
        match(braneParser::T__45);
        setState(506);
        match(braneParser::T__5);
        setState(507);
        antlrcpp::downCast<SwitchCaseContext *>(_localctx)->content = expressions();
        setState(508);
        match(braneParser::T__6);
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

braneParser::ExpressionContext* braneParser::MatchCaseContext::expression() {
  return getRuleContext<braneParser::ExpressionContext>(0);
}

braneParser::ExpressionsContext* braneParser::MatchCaseContext::expressions() {
  return getRuleContext<braneParser::ExpressionsContext>(0);
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
  enterRule(_localctx, 68, braneParser::RuleMatchCase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(523);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case braneParser::T__44: {
        enterOuterAlt(_localctx, 1);
        setState(512);
        match(braneParser::T__44);
        setState(513);
        antlrcpp::downCast<MatchCaseContext *>(_localctx)->pattern = expression(0);
        setState(514);
        match(braneParser::T__5);
        setState(515);
        antlrcpp::downCast<MatchCaseContext *>(_localctx)->content = expressions();
        setState(516);
        match(braneParser::T__6);
        break;
      }

      case braneParser::T__45: {
        enterOuterAlt(_localctx, 2);
        setState(518);
        match(braneParser::T__45);
        setState(519);
        match(braneParser::T__5);
        setState(520);
        antlrcpp::downCast<MatchCaseContext *>(_localctx)->content = expressions();
        setState(521);
        match(braneParser::T__6);
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

//----------------- FailContext ------------------------------------------------------------------

tree::TerminalNode* braneParser::FailContext::STRING() {
  return getToken(braneParser::STRING, 0);
}

braneParser::FailContext::FailContext(MagicFunctionContext *ctx) { copyFrom(ctx); }


std::any braneParser::FailContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<braneVisitor*>(visitor))
    return parserVisitor->visitFail(this);
  else
    return visitor->visitChildren(this);
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
  enterRule(_localctx, 70, braneParser::RuleMagicFunction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(539);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<braneParser::SizeOfTypeContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(525);
      match(braneParser::T__46);
      setState(526);
      match(braneParser::T__19);
      setState(527);
      antlrcpp::downCast<SizeOfTypeContext *>(_localctx)->t = type();
      setState(528);
      match(braneParser::T__20);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<braneParser::SizeOfPackContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(530);
      match(braneParser::T__46);
      setState(531);
      match(braneParser::T__11);
      setState(532);
      match(braneParser::T__19);
      setState(533);
      antlrcpp::downCast<SizeOfPackContext *>(_localctx)->id = match(braneParser::ID);
      setState(534);
      match(braneParser::T__20);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<braneParser::FailContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(535);
      match(braneParser::T__47);
      setState(536);
      match(braneParser::T__19);
      setState(537);
      antlrcpp::downCast<FailContext *>(_localctx)->message = match(braneParser::STRING);
      setState(538);
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
    case 32: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

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
    case 4: return precpred(_ctx, 3);
    case 5: return precpred(_ctx, 15);
    case 6: return precpred(_ctx, 14);
    case 7: return precpred(_ctx, 10);
    case 8: return precpred(_ctx, 9);
    case 9: return precpred(_ctx, 8);
    case 10: return precpred(_ctx, 2);

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

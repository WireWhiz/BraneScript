#ifndef BRANESCRIPT_COMPILER_H
#define BRANESCRIPT_COMPILER_H

#include <vector>
#include "../ir/ir.h"
#include "../parser/documentParser.h"
#include <unordered_map>

/// List of pipelines and functions provided by the runtime that we are compiling for
struct EnvDefs
{
    std::unordered_map<std::string, void*> pipelines;
    std::unordered_map<std::string, void*> functions;
};

enum class CompilerMessageType
{
    Critical = 0,
    Error = 1,
    Warning = 2,
    Log = 3,
    Verbose = 4,
};

struct CompilerFileSource 
{
    std::string path;
    std::optional<TSRange> range;
};

using CompilerSource = std::variant<CompilerFileSource>;

struct CompilerMessage
{
    CompilerMessageType type;
    CompilerSource source;
    std::string message;
};

struct CompileResult
{
    std::vector<Module> modules;
    std::vector<CompilerMessage> messages;
};


using Identifiable = std::variant<std::shared_ptr<Module>, std::shared_ptr<Pipeline>, std::shared_ptr<Function>, std::shared_ptr<PipelineStage>>;

class Compiler
{
    SymbolLookupTable _lut;
    std::optional<EnvDefs> _env;
    std::unordered_map<std::string, std::shared_ptr<ParsedDocument>> _sources;
    std::unordered_map<std::string, std::shared_ptr<Module>> _modules;
    std::unordered_map<std::string, Identifiable> _identifers;


    void indexSymbolsPass_recursive(TSNode node, ScopedIdentifier& currentScope, const ParsedDocument& doc);

    void indexSymbolsPass();
    void constructGenericsPass();
    void generateIRPass();

    void generatePipeline(std::shared_ptr<Pipeline> pipe);

    void recordMessage(CompilerMessage message);
public:

    Compiler(SymbolLookupTable lut);
    CompileResult compile(const std::vector<std::shared_ptr<ParsedDocument>>& documents);
};

#endif

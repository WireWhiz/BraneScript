#include "compiler.h"

#include <expected>
#include <tree_sitter/api.h>

void Compiler::recordMessage(CompilerMessage message)
{
    _result.messages.push_back(std::move(message));
}


CompileResult Compiler::compile(const std::vector<std::shared_ptr<ParsedDocument>>& documents)
{
    _result = CompileResult();
    _identifers.clear();
    _modules.clear();

    _sources.clear();
    for(auto& source: documents)
        _sources.emplace(source->source(), source);

    auto globalMod = std::make_shared<Module>("global");
    _identifers.insert({"global", globalMod});
    _modules.insert({"global", globalMod});

    indexSymbolsPass();
    generateModulesPass();
    
    for(auto& mod: _modules)
        _result.modules.push_back(std::move(*mod.second));
    return std::move(_result);
}

std::expected<ScopedIdentifier, CompilerMessage> parseScopedIdentifier(TSNode idRoot, const ParsedDocument& doc)
{
    ScopedIdentifier id;

    while(!ts_node_is_null(idRoot))
    {
        TSNode idNameNode = ts_node_child_by_field_name(idRoot, "id", 2);
        std::optional<std::vector<TemplateArg>> templateArgs;

        // TODO actually parse templateArgs

        id.scopes.emplace_back(doc.nodeToString(idNameNode), templateArgs);
        idRoot = ts_node_child_by_field_name(idRoot, "child", 5);
    }

    return id;
}

void Compiler::indexSymbolsPass()
{
    for(auto& [path, doc]: _sources)
    {
        TSNode root = doc->docRoot();
        
        ScopedIdentifier currentScope;
        indexSymbolsPass_recursive(root, currentScope, *doc);
    }
}

void Compiler::indexSymbolsPass_recursive(TSNode node, ScopedIdentifier& currentScope, const ParsedDocument& doc)
{
    size_t parentScopeLength = currentScope.scopes.size();

    NodeType nodeType;
    if(_lut.tryToNodeType(ts_node_symbol(node), nodeType))
    {
        switch(nodeType)
        {
            case NodeType::Pipeline:
                {
                    auto pipe = std::make_shared<Pipeline>();

                    TSNode idNode = ts_node_child_by_field_name(node, "id", 2);
                    Identifier identifier{
                        doc.nodeToString(idNode)
                    };
                    
                    pipe->name = identifier.name;

                    std::get<std::shared_ptr<Module>>(_identifers["global"])->pipelines.insert({identifier.name, pipe});
                    currentScope.scopes.push_back(std::move(identifier));

                    _identifers.insert({currentScope.longName(), pipe});

                    break;
                }
            default:
                break;
        }
    }

    for (int i = 0; i < ts_node_named_child_count(node); i++) {
        indexSymbolsPass_recursive(ts_node_named_child(node, i), currentScope, doc);
    }
    currentScope.scopes.resize(parentScopeLength);
}

void Compiler::generateIRPass()
{
    for(auto& [modId, mod]: _modules)
    {
        
        // GeneratePipelines defined in our sources
        for(auto& [pipeId, pipe]: mod->pipelines)
        {
            if (!pipe->debugInfo.has_value())
                continue;
            if (!_sources.contains(pipe->name))
                continue;
            

        }

    }
}




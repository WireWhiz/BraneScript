//
// Created by WireWhiz on 10/28/2024.
//

#include "documentParser.h"

#include "tree_sitter_branescript.h"
#include <tree_sitter/api.h>
#include <cassert>
#include <expected>
#include <functional>
#include <memory>

namespace BraneScript
{
    enum class TSNodeType: uint16_t
    {
        Number = 0,
        Identifier,
        ScopedIdentifier,
        Type,
        TemplateArgument,
        TemplateArguments,
        Add,
        Sub,
        Mul,
        Div,
        Assign,
        Block,
        VarDefPrefix,
        SinkDef,
        SinkList,
        SourceDef,
        SourceList,
        Call,
        AsyncOperation,
        Function,
        Pipeline,
        Module,
        SourceFile
    };

    void foreachNodeChild(TSNode node, const std::function<void(TSNode)>& f)
    {
        uint32_t childCount = ts_node_child_count(node);
        for(uint32_t i = 0; i < childCount; ++i)
            f(ts_node_child(node, i));
    }

    TSRange nodeRange(TSNode node)
    {
        return {
            ts_node_start_point(node),
            ts_node_end_point(node),
            ts_node_start_byte(node),
            ts_node_end_byte(node)
        };
    }

    std::string_view nodeName(TSNode node)
    {
        return ts_language_symbol_name(tree_sitter_branescript(), ts_node_symbol(node));    
    }


    std::string_view nodeText(TSNode node, std::string_view sourceText)
    {
        auto start = ts_node_start_byte(node);
        auto end = ts_node_end_byte(node);
        return {
            sourceText.data() + start, 
            end - start
        };
    }
    

    class TSSymbolLookupTable
    {
      private:
        std::vector<TSNodeType> symbolToNodeType;
        std::vector<TSSymbol> nodeTypeToSymbol;

        void add_entry(const TSLanguage* lang, std::string_view ident, TSNodeType nodeType)
        {
            auto symbol = ts_language_symbol_for_name(lang, ident.data(), ident.size(), true);
            if(symbol >= symbolToNodeType.size())
                symbolToNodeType.resize(symbol + 1, (TSNodeType)UINT16_MAX);
            if((uint16_t)nodeType >= nodeTypeToSymbol.size())
                nodeTypeToSymbol.resize((uint16_t)nodeType + 1, (TSSymbol)UINT16_MAX);
            symbolToNodeType[symbol] = nodeType;
            nodeTypeToSymbol[(uint16_t)nodeType] = symbol;
        }
      public:
        TSSymbolLookupTable(const TSLanguage* lang)
        {
            add_entry(lang, "number", TSNodeType::Number);
            add_entry(lang, "module", TSNodeType::Module);
            add_entry(lang, "identifier", TSNodeType::Identifier);
            add_entry(lang, "scopedIdentifier", TSNodeType::ScopedIdentifier);
            add_entry(lang, "type", TSNodeType::Type);
            add_entry(lang, "templateArgument", TSNodeType::TemplateArgument);
            add_entry(lang, "templateArguments", TSNodeType::TemplateArguments);
            add_entry(lang, "add", TSNodeType::Add);
            add_entry(lang, "sub", TSNodeType::Sub);
            add_entry(lang, "mul", TSNodeType::Mul);
            add_entry(lang, "div", TSNodeType::Div);
            add_entry(lang, "assign", TSNodeType::Assign);
            add_entry(lang, "block", TSNodeType::Block);
            add_entry(lang, "varDefPrefix", TSNodeType::VarDefPrefix);
            add_entry(lang, "sinkDef", TSNodeType::SinkDef);
            add_entry(lang, "sinkList", TSNodeType::SinkList);
            add_entry(lang, "sourceDef", TSNodeType::SourceDef);
            add_entry(lang, "sourceList", TSNodeType::SinkList);
            add_entry(lang, "call", TSNodeType::Call);
            add_entry(lang, "asyncOperation", TSNodeType::AsyncOperation);
            add_entry(lang, "function", TSNodeType::Function);
            add_entry(lang, "pipeline", TSNodeType::Pipeline);
            add_entry(lang, "sourceFile", TSNodeType::SourceFile);
        }

        std::optional<TSNodeType> tryToNodeType(TSSymbol symbol) const
        {
            if (symbol > symbolToNodeType.size())
                return std::nullopt;
            auto nodeType = symbolToNodeType[symbol];
            return (uint16_t)nodeType == UINT16_MAX ? std::nullopt : std::make_optional(nodeType);
        }
        
        std::optional<TSSymbol> tryToSymbol(TSNodeType nodeType) const
        {
            if ((uint16_t)nodeType > nodeTypeToSymbol.size())
                return std::nullopt;
            auto symbol = nodeTypeToSymbol[(uint16_t)nodeType];
            return symbol == UINT16_MAX ? std::nullopt : std::make_optional(symbol);
        }
    };

    enum class TSFieldName: uint16_t
    {
        Id = 0,
        Child,
        Defs,
        Sources,
        Sinks,
        TemplateArgs,
    };

    class TSFieldLookupTable
    {
      private:
        std::vector<TSFieldId> _fieldIds;

        void add_entry(const TSLanguage* lang, std::string_view textName, TSFieldName fieldName)
        {
            auto fID = ts_language_field_id_for_name(lang, textName.data(), textName.size());

            if((uint16_t)fieldName >= _fieldIds.size())
                _fieldIds.resize((uint16_t)fieldName + 1, (TSFieldId)0);
            _fieldIds[(uint16_t)fieldName] = fID;
        }
      public:
        TSFieldLookupTable(const TSLanguage* lang)
        {
            add_entry(lang, "child", TSFieldName::Child);
            add_entry(lang, "defs", TSFieldName::Defs);
            add_entry(lang, "id", TSFieldName::Id);
            add_entry(lang, "sinks", TSFieldName::Sinks);
            add_entry(lang, "sources", TSFieldName::Sources);
            add_entry(lang, "templateArgs", TSFieldName::TemplateArgs);
        }
        
        TSFieldId get(TSFieldName name) const
        {
            assert((uint16_t)name < _fieldIds.size() && "Make sure all fields are defined in the constructor");
            return _fieldIds[(uint16_t)name];
        }
    };

    const TSSymbolLookupTable symbolLookupTable = TSSymbolLookupTable(tree_sitter_branescript());
    const TSFieldLookupTable fieldLookupTable = TSFieldLookupTable(tree_sitter_branescript());

    std::string_view typeToName(TSNodeType type)
    {
        auto symbol = symbolLookupTable.tryToSymbol(type);
        if(!symbol)
            return "Unknown";
        return ts_language_symbol_name(tree_sitter_branescript(), symbol.value());
    }
 
    struct ParserCtx 
    {
        std::filesystem::path path;
        std::string_view source;
        std::shared_ptr<BraneScriptParser> parser;
        std::vector<ParserError> errors;
        TSTree* tree;

        std::optional<TSNode> getField(TSNode node, TSFieldName field)
        {
            auto result = ts_node_child_by_field_id(node, fieldLookupTable.get(field));
            if(ts_node_is_null(result))
                return std::nullopt;
            return result;
        }

        bool expectNode(TSNode node, const std::vector<TSNodeType>& types)
        {
            auto nodeType = symbolLookupTable.tryToNodeType(ts_node_symbol(node));
            if(nodeType)
            {
                for(auto t: types)
                {
                    if(t == nodeType)
                        return true;
                }
            }

            std::string message = std::vformat("Found \"{}\", but was expecting one of the following:\n", std::make_format_args(nodeText(node, source))); 
            for(auto t: types)
                message += std::vformat("{}\n",std::make_format_args(typeToName(t)));
            errors.push_back({
                nodeRange(node),
                message
            });
            return false;
        }
    };

    std::optional<Node<ModuleContext>> parseModule(TSNode root, ParserCtx& ctx)
    {
        if(!ctx.expectNode(root, {TSNodeType::Module}))
            return std::nullopt;

        auto identifier = ctx.getField(root, TSFieldName::Id);
        if(!identifier)
        {
            ctx.errors.push_back({
                nodeRange(root),
                "Expected Identifier!"
            });
            return std::nullopt;
        }
            
        auto mod = std::make_shared<ModuleContext>();

        mod->identifier = Identifier{
            nodeRange(*identifier),
            (std::string)nodeText(*identifier, ctx.source)
        };

        

        return mod;
    }

    ParserResult<DocumentContext> parseDocument(ParserCtx& ctx)
    {
        ctx.tree = ts_parser_parse_string(
            ctx.parser->parser(),
            nullptr,
            ctx.source.data(),
            ctx.source.size()
        );

        auto doc = std::make_shared<DocumentContext>();

        doc->source = ctx.path;
        
        TSNode root = ts_tree_root_node(ctx.tree);

        foreachNodeChild(root, [&](TSNode node){
            auto newMod = parseModule(node, ctx);
            if(newMod)
                doc->modules.insert({newMod.value()->identifier.text, newMod.value()});
        });

        return {
            doc,
            ctx.errors
        };
    }

    BraneScriptParser::BraneScriptParser()
    {
        _value = ts_parser_new();
        ts_parser_set_language(_value, tree_sitter_branescript());
    }

    BraneScriptParser::BraneScriptParser(BraneScriptParser&& other) noexcept
    {
        _value = other._value;
        other._value = nullptr;
    }

    BraneScriptParser::~BraneScriptParser()
    {
        if (_value)
            ts_parser_delete(_value);
    }

    TSParser* BraneScriptParser::parser() const 
    {
        return _value;
    }

    

    ParsedDocument::ParsedDocument(std::filesystem::path path, std::string source, std::shared_ptr<BraneScriptParser> parser): _path(std::move(path)), _source(std::move(source)), _parser(std::move(parser))
    {
    }

    std::string_view ParsedDocument::source() const
    {
        return _source;
    }

    void ParsedDocument::update(TSRange updateRange, std::string newText)
    {
        //TODO implement
        assert(false && "Update not implemented!");
    }

    ParserResult<DocumentContext> ParsedDocument::getDocumentContext()
    {
        if (_cachedResult)
            return _cachedResult.value();
        ParserCtx ctx{
            _path,
            _source,
            _parser
        };
        _cachedResult = std::make_optional(parseDocument(ctx));
        return _cachedResult.value();
    }


} // namespace BraneScript

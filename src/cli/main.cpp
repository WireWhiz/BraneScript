//
// Created by WireWhiz on 10/22/2024.
//

#include <fstream>
#include <iostream>
#include <string_view>
#include <string>
#include <filesystem>
#include <charconv>

#include "tree_sitter/api.h"
#include "../parser/SymbolLookupTable.h"
#include "../parser/tree_sitter_branescript.h"

//#include "TSBindings.h"


void print_tree(TSNode node, std::string_view source, int currentDepth = 0)
{
    for (int i = 0; i < currentDepth; i++)
        printf(" | ");

    if (ts_node_is_null(node))
    {
        printf("NULL!");
        return;
    }

    auto start = ts_node_start_byte(node);
    auto end = ts_node_end_byte(node);

    printf("%s   [   %.*s   ]", ts_node_type(node), end - start, source.data() + start);

    if (ts_node_is_extra(node))
        printf(" - Extra");
    if (ts_node_is_missing(node))
        printf(" - Missing");
    if (!ts_node_is_named(node))
        printf(" - Unnamed");

    printf("\n");

    for (int i = 0; i < ts_node_child_count(node); i++)
        print_tree(ts_node_child(node, i), source, currentDepth + 1);
}




class Evaluator
{
  private:
    SymbolLookupTable _lut;
    std::string _source;
  public:
    Evaluator(SymbolLookupTable lut, std::string sourceCode): _lut(std::move(lut)), _source(std::move(sourceCode))
    {
    }

    float run(TSNode node)
    {
        NodeType type;
        if(!_lut.tryToNodeType(ts_node_symbol(node), type))
            return NAN;

        switch(type)
        {
            case NodeType::Number:
            {
                float parsed;
                auto res = std::from_chars(_source.data() + ts_node_start_byte(node),
                                           _source.data() + ts_node_end_byte(node),
                                           parsed,
                                           (std::chars_format)(std::chars_format::general));
                if(res.ec != std::errc{})
                    std::cerr << "Failed to parse number!";

                return parsed;
            }
            case NodeType::Add:
            {
                auto left = ts_node_named_child(node, 0);
                auto right = ts_node_named_child(node, 1);

                return run(left) + run(right);
            }
            case NodeType::Sub:
            {
                auto left = ts_node_named_child(node, 0);
                auto right = ts_node_named_child(node, 1);

                return run(left) - run(right);
            }
            case NodeType::Mul:
            {
                auto left = ts_node_named_child(node, 0);
                auto right = ts_node_named_child(node, 1);

                return run(left) * run(right);
            }
            case NodeType::Div:
            {
                auto left = ts_node_named_child(node, 0);
                auto right = ts_node_named_child(node, 1);

                return run(left) / run(right);
            }
        }
    }
};

int main(int argc, char* argv[])
{
    std::cout << "Hello world!" << std::endl;
    std::cout << "Running in dir: " << std::filesystem::current_path() << std::endl;

    if (argc < 2)
    {
        std::cout << "Must provide file to parse!" << std::endl;
        return 1;
    }

    std::ifstream f(argv[1], std::ios::binary | std::ios::ate);
    if (!f.is_open())
    {
        std::cout << "File \"" << argv[1] << "\" does not exist!" << std::endl;
        return 1;
    }
    std::string source_code;
    auto count = f.tellg();

    source_code.resize(count);
    f.seekg(0);
    f.read(source_code.data(), count);
    f.close();

    std::cout << "Parsing: \n" << source_code << std::endl;
    TSParser* parser = ts_parser_new();
    const TSLanguage* braneScriptLang = tree_sitter_branescript();
    ts_parser_set_language(parser, braneScriptLang);

    TSTree *tree = ts_parser_parse_string(
        parser,
        nullptr,
        source_code.c_str(),
        source_code.size()
    );

    TSNode root_node = ts_tree_root_node(tree);

    char *string = ts_node_string(root_node);
    printf("Syntax tree: %s\n", string);
    free(string);

    print_tree(root_node, source_code);

    SymbolLookupTable lut(braneScriptLang);
    Evaluator evaluator(lut, source_code);

    for(int i = 0; i < ts_node_child_count(root_node); ++i)
    {
        TSNode expression = ts_node_child(root_node, i);
        float result = evaluator.run(expression);
        std::cout << std::string_view(
            source_code.data() + ts_node_start_byte(expression),
            ts_node_end_byte(expression) - ts_node_start_byte(expression)
            ) << " = " << result << std::endl;
    }

    ts_tree_delete(tree);
    ts_parser_delete(parser);

    return 0;
}

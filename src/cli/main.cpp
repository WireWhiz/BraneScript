//
// Created by WireWhiz on 10/22/2024.
//

#include <fstream>
#include <iostream>
#include <string_view>
#include <filesystem>

#include "tree_sitter/api.h"

extern "C"{
    const TSLanguage *tree_sitter_BraneScript(void);
}

int main(int argc, char* argv[])
{
    std::cout << "Hello world!" << std::endl;

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
    ts_parser_set_language(parser, tree_sitter_BraneScript());

    TSTree *tree = ts_parser_parse_string(
        parser,
        NULL,
        source_code.c_str(),
        source_code.size()
    );

    TSNode root_node = ts_tree_root_node(tree);

    char *string = ts_node_string(root_node);
    printf("Syntax tree: %s\n", string);
    free(string);

    return 0;
}
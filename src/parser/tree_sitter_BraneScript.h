//
// Created by WireWhiz on 10/28/2024.
//

#ifndef BRANESCRIPT_TREE_SITTER_BRANESCRIPT_H
#define BRANESCRIPT_TREE_SITTER_BRANESCRIPT_H

#include <tree_sitter/api.h>
#include <string>
#include <string_view>
#include <filesystem>

extern "C"{
    const TSLanguage *tree_sitter_branescript(void);
}



#endif // BRANESCRIPT_TREE_SITTER_BRANESCRIPT_H

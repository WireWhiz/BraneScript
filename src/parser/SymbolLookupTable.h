//
// Created by WireWhiz on 10/28/2024.
//

#ifndef BRANESCRIPT_SYMBOLLOOKUPTABLE_H
#define BRANESCRIPT_SYMBOLLOOKUPTABLE_H

#include <cstdint>
#include <vector>
#include <string_view>
#include "tree_sitter/api.h"

enum class NodeType: uint16_t
{
    Number = 0,
    Add,
    Sub,
    Mul,
    Div
};

class SymbolLookupTable
{
  private:
    std::vector<NodeType> symbolToNodeType;
    std::vector<TSSymbol> nodeTypeToSymbol;

    void add_entry(const TSLanguage* lang, std::string_view ident, NodeType nodeType);

  public:
    SymbolLookupTable(const TSLanguage* lang);

    bool tryToNodeType(TSSymbol symbol, NodeType& nodeType);

    bool tryToSymbol(NodeType nodeType, TSSymbol& symbol);
};


#endif // BRANESCRIPT_SYMBOLLOOKUPTABLE_H

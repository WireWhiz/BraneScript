//
// Created by WireWhiz on 10/28/2024.
//

#include "SymbolLookupTable.h"

SymbolLookupTable::SymbolLookupTable(const TSLanguage* lang)
{
    add_entry(lang, "number", NodeType::Number);
    add_entry(lang, "add", NodeType::Add);
    add_entry(lang, "sub", NodeType::Sub);
    add_entry(lang, "mul", NodeType::Mul);
    add_entry(lang, "div", NodeType::Div);
}

void SymbolLookupTable::add_entry(const TSLanguage* lang, std::string_view ident, NodeType nodeType)
{
    auto symbol = ts_language_symbol_for_name(lang, ident.data(), ident.size(), true);
    if(symbol >= symbolToNodeType.size())
    {
        symbolToNodeType.resize(symbol + 1, (NodeType)UINT16_MAX);
        nodeTypeToSymbol.resize((uint16_t)nodeType + 1, (TSSymbol)UINT16_MAX);
    }
    symbolToNodeType[symbol] = nodeType;
    nodeTypeToSymbol[(uint16_t)nodeType] = symbol;
}

bool SymbolLookupTable::tryToNodeType(TSSymbol symbol, NodeType& nodeType)
{
    if (symbol > symbolToNodeType.size())
        return false;
    nodeType = symbolToNodeType[symbol];
    return (uint16_t)nodeType != UINT16_MAX;
}

bool SymbolLookupTable::tryToSymbol(NodeType nodeType, TSSymbol& symbol)
{
    if ((uint16_t)nodeType > nodeTypeToSymbol.size())
        return false;
    symbol = nodeTypeToSymbol[(uint16_t)nodeType];
    return symbol != UINT16_MAX;
}
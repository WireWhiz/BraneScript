//
// Created by wirewhiz on 1/31/23.
//

#ifndef BRANESCRIPT_TOKENSERIALIZER_H
#define BRANESCRIPT_TOKENSERIALIZER_H

#include <cstdint>
#include <json/value.h>
#include <string>
#include <vector>
namespace lsp
{

    std::vector<uint32_t> extractSemanticTokens(const std::string& document);
    Json::Value semanticTokensOptions();

} // namespace lsp

#endif // BRANESCRIPT_TOKENSERIALIZER_H

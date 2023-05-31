#include "lspMessage.h"
#include "lspServer.h"
#include "robin_hood.h"
#include "staticAnalysis/staticAnalyzer.h"
#include <filesystem>
#include <iostream>
#include "tokenSerializer.h"

using namespace BraneScript;

std::string uriToPath(const std::string& uri)
{
    return uri.substr(7);
}

int main()
{
    lsp::LspServer server;

    server.capabilities["textDocumentSync"]["openClose"] = true;
    server.capabilities["textDocumentSync"]["change"] = 2;
    server.capabilities["semanticTokensProvider"] = lsp::semanticTokensOptions();
    server.addListener("textDocument/didOpen", [&](lsp::LspSession* session, lsp::LspMessageRequest* req) {
        auto& documentData = req->params["textDocument"];
        auto path = uriToPath(documentData["uri"].asString());
        session->analyzer.load(path, documentData["text"].asString(), true);
        session->analyzer.validate(path);

        auto res = std::make_unique<lsp::LspMessageRequest>();
        res->method = "textDocument/publishDiagnostics";
        res->params["uri"] = req->params["textDocument"]["uri"];
        res->params["version"] = req->params["textDocument"]["version"];
        res->params["diagnostics"] = Json::arrayValue;

        auto* ctx = session->analyzer.getCtx(path);
        for(auto& w : ctx->warnings) {
            Json::Value diagnostic;
            diagnostic["message"] = w.message;
            diagnostic["severity"] = 2;
            diagnostic["range"] = w.range.toJson();
            res->params["diagnostics"].append(diagnostic);
        }
        for(auto& e : ctx->errors) {
            Json::Value diagnostic;
            diagnostic["message"] = e.message;
            diagnostic["severity"] = 1;
            diagnostic["range"] = e.range.toJson();
            res->params["diagnostics"].append(diagnostic);
        }

        /* update diagnostics */
        server.sendMessage(session, std::move(res));
    });
    server.addListener("textDocument/didChange", [&](lsp::LspSession* session, lsp::LspMessageRequest* req) {
        auto path = uriToPath(req->params["textDocument"]["uri"].asString());
        auto* ctx = session->analyzer.getCtx(path);
        {
            std::scoped_lock lock(ctx->lock);
            std::string& document = ctx->document;
            for(auto& change : req->params["contentChanges"])
            {
                auto range = TextRange::fromJson(change["range"]);
                auto bounds = range.getBoundsForText(document);
                std::string newText = change["text"].asString();
                std::cout << "[" << std::string{document.begin() + std::max<int>(bounds.first - 5, 0), document.begin() + std::min<int>(bounds.second + 5, document.size())} << "] <- before. " << std::endl;
                if(bounds.first != bounds.second)
                    document.erase(document.begin() + bounds.first, document.begin() + bounds.second);
                if(!newText.empty())
                    document.insert(document.begin() + bounds.first, newText.begin(), newText.end());
                std::cout << "[" << std::string{document.begin() + std::max<int>(bounds.first - 5, 0), document.begin() + std::min<int>(bounds.second + 5, document.size())} << "] <- result" << std::endl;
            }
        }
        session->analyzer.reload(path);
        session->analyzer.validate(path);

        auto res = std::make_unique<lsp::LspMessageRequest>();
        res->method = "textDocument/publishDiagnostics";
        res->params["uri"] = req->params["textDocument"]["uri"];
        res->params["version"] = req->params["textDocument"]["version"];
        res->params["diagnostics"] = Json::arrayValue;
        for(auto& w : ctx->warnings) {
            Json::Value diagnostic;
            diagnostic["message"] = w.message;
            diagnostic["severity"] = 2;
            diagnostic["range"] = w.range.toJson();
            res->params["diagnostics"].append(diagnostic);
        }
        for(auto& e : ctx->errors) {
            Json::Value diagnostic;
            diagnostic["message"] = e.message;
            diagnostic["severity"] = 1;
            diagnostic["range"] = e.range.toJson();
            res->params["diagnostics"].append(diagnostic);
        }

        /* update diagnostics */
        server.sendMessage(session, std::move(res));

    });
    server.addListener("textDocument/didClose", [&](lsp::LspSession* session, lsp::LspMessageRequest* req, lsp::LspResponseMessage* res) {
        std::string path = uriToPath(req->params["textDocument"]["uri"].asString());
        auto* ctx = session->analyzer.getCtx(path);
        std::scoped_lock lock(ctx->lock);
        ctx->document.clear();
        std::cout << "Closed " << path << std::endl;
    });
    server.addListener("textDocument/semanticTokens/full",
                       [&](lsp::LspSession* session, lsp::LspMessageRequest* req, lsp::LspResponseMessage* res) {
        std::string path = uriToPath(req->params["textDocument"]["uri"].asString());
        auto ctx = session->analyzer.getCtx(path);
        std::scoped_lock lock(ctx->lock);
        auto tokens = lsp::extractSemanticTokens(ctx->document);
        Json::Value data;
        for(auto token : tokens)
            data.append(token);
        res->result["data"] = std::move(data);
    });

    server.start(2001);
    while(true)
    {
        server.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
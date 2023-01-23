#include "lspServer.h"
#include "lspMessage.h"

int main()
{
    lsp::LspServer server;


    server.capabilities["hoverProvider"] = true;
    server.addListener("textDocument/hover",
                       [](lsp::LspSession* session, lsp::LspMessageRequest* req, lsp::LspResponseMessage* res){
        res->result["contents"] = "Hovering in " + req->params["textDocument"]["uri"].asString() + " at line " +
            std::to_string(req->params["position"]["line"].asUInt()) + " character " +
            std::to_string(req->params["position"]["character"].asUInt()) + ".";
    });

    server.start(2001);
    while(true) {
        server.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
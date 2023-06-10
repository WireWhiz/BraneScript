#ifndef BRANESCRIPT_NETPROTOCALL_H
#define BRANESCRIPT_NETPROTOCALL_H

#include "asio.hpp"
#include "lspMessage.h"
#include "robin_hood.h"
#include "analyzer.h"
#include <functional>
#include <thread>

namespace lsp
{
    struct SerializedMessage
    {
        enum Encoding {
            utf8,
            utf16,
            utf32
        } encoding = utf8;
        std::string message;
    };

    struct LspSession
    {
        LspSession(asio::ip::tcp::socket connection);
        asio::streambuf buffer;
        asio::ip::tcp::socket connection;
        std::unique_ptr<SerializedMessage> iMessage;
        std::unique_ptr<std::string> oMessage;
        std::deque<std::unique_ptr<LspMessage>> messagesIn;
        std::deque<std::unique_ptr<LspMessage>> messagesOut;
        uint32_t requestIDCounter = 0;
        robin_hood::unordered_map<std::string, std::function<void(std::unique_ptr<LspResponseMessage> response)>> responseListeners;
        std::recursive_mutex lock;
        bool initialized = false;

        BraneScript::Analyzer analyzer;
    };

    class LspServer
    {
        std::thread _netThread;
        asio::io_context _netCtx;
        std::unique_ptr<asio::ip::tcp::acceptor> _acceptor;
        std::mutex _sessionsLock;
        std::vector<std::unique_ptr<LspSession>> _sessions;

        robin_hood::unordered_map<std::string, std::function<void(LspSession* session, LspMessageRequest*)>> _notificationListeners;
        robin_hood::unordered_map<std::string, std::function<void(LspSession* session, LspMessageRequest*, LspResponseMessage*)>> _requestListeners;

        void listenForNewSession();
        void initializeSession(LspSession* session);

        void readMessage(LspSession* session, std::function<void(std::unique_ptr<SerializedMessage>)> callback, bool recursive = true);


    public:
        Json::Value capabilities;

        LspServer();
        ~LspServer();

        void start(uint16_t port);
        void stop();

        void addListener(std::string name, std::function<void(LspSession* session, LspMessageRequest*, LspResponseMessage*)> callback);
        void addListener(std::string name, std::function<void(LspSession* session, LspMessageRequest*)> callback);
        void sendRequest(LspSession* session, std::unique_ptr<LspMessageRequest> request,
                         std::function<void(std::unique_ptr<LspResponseMessage> response)> callback);

        void sendMessage(LspSession* session, std::unique_ptr<LspMessage> message);
        void removeSession(LspSession* session);

        void update();
    };
}



#endif //BRANESCRIPT_NETPROTOCALL_H

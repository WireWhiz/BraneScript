#include "lspServer.h"
#include <iostream>

namespace lsp {

    LspSession::LspSession(asio::ip::tcp::socket connection) : connection(std::move(connection)) {}

    LspServer::LspServer()
    {
    }

    LspServer::~LspServer() { stop(); }

    void LspServer::start(uint16_t port)
    {
        try {
            _acceptor =
                std::make_unique<asio::ip::tcp::acceptor>(_netCtx, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
        }
        catch(const std::exception& e) {
            std::cerr << "error opening port " << port << '\n' << e.what() << std::endl;
            throw e;
        }
        listenForNewSession();
        _netThread = std::thread([this]() { _netCtx.run(); });
    }

    void LspServer::stop()
    {
        _netCtx.stop();
        if(_netThread.joinable())
            _netThread.join();
    }

    void LspServer::listenForNewSession()
    {
        _sessionsLock.lock();
        _sessions.push_back(std::make_unique<LspSession>(asio::ip::tcp::socket(_netCtx)));
        auto newSession = (--_sessions.end())->get();
        _sessionsLock.unlock();
        _acceptor->async_accept(newSession->connection, [this, newSession](std::error_code ec) {
            if(ec) {
                removeSession(newSession);
                return;
            }
            initializeSession(newSession);
            listenForNewSession();
        });
    }

    void LspServer::initializeSession(LspSession* session)
    {
        readMessage(
            session,
            [this, session](auto initMessage) {
            Json::CharReaderBuilder builder;
            std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
            Json::Value value;
            std::string errors;
            if(!reader->parse(
                   initMessage->message.data(),
                   initMessage->message.data() + initMessage->message.size(),
                   &value,
                   &errors)) {
                std::cerr << "Json parsing error! " << errors << std::endl;
                return;
            }
            LspMessageRequest request;
            request.deserialize(value);

            std::cout << "Request to connect from client: " << request.params["clientInfo"]["name"].asString()
                      << std::endl;

            readMessage(session, [session](auto message) {
                Json::CharReaderBuilder builder;
                std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

                Json::Value value;
                std::string errors;
                if(!reader->parse(
                       message->message.data(), message->message.data() + message->message.size(), &value, &errors)) {
                    std::cerr << "Json parsing error! " << errors << std::endl;
                    return;
                }
                std::unique_ptr<LspMessageRequest> request(new LspMessageRequest{});
                request->deserialize(value);


                session->lock.lock();
                if(session->initialized)
                    session->messagesIn.push_back(std::move(request));
                else if(request->method == "initialized")
                    session->initialized = true;
                else
                    ;//TODO send error code: -32002 here
                session->lock.unlock();
            });

            std::unique_ptr<LspResponseMessage> response = std::make_unique<LspResponseMessage>();
            response->id = request.id;

            response->result["capabilities"] = capabilities;
            response->result["serverInfo"]["name"] = "BS Intelligence";
            response->result["serverInfo"]["version"] = "0.0.1";

            sendMessage(session, std::move(response));
            },
            false);
    }

    void LspServer::removeSession(LspSession* session)
    {
        _sessionsLock.lock();
        for(auto i = _sessions.begin(); i != _sessions.end(); ++i) {
            if(session == i->get()) {
                _sessions.erase(i);
                break;
            }
        }
        _sessionsLock.unlock();
    }

    void LspServer::addListener(std::string name, std::function<void(LspSession* session, LspMessageRequest*)> callback)
    {
        assert(!_notificationListeners.contains(name));
        _notificationListeners.insert({std::move(name), std::move(callback)});
    }

    void LspServer::addListener(
        std::string name, std::function<void(LspSession* session, LspMessageRequest*, LspResponseMessage*)> callback)
    {
        assert(!_requestListeners.contains(name));
        _requestListeners.insert({std::move(name), std::move(callback)});
    }

    void LspServer::update()
    {
        _sessionsLock.lock();
        for(auto& session : _sessions) {
            session->lock.lock();
            while(!session->messagesIn.empty()) {
                auto message = std::move(session->messagesIn.front());
                session->messagesIn.pop_front();
                session->lock.unlock();

                auto* request = dynamic_cast<LspMessageRequest*>(message.get());
                if(request) {
                    auto reqListener = _requestListeners.find(request->method);
                    if(reqListener != _requestListeners.end()) {
                        auto response = std::make_unique<LspResponseMessage>();
                        response->id = request->id;
                        reqListener->second(session.get(), request, response.get());

                        session->lock.lock();
                        sendMessage(session.get(), std::move(response));
                        continue;
                    }
                    auto notifListener = _notificationListeners.find(request->method);
                    if(notifListener != _notificationListeners.end()) {
                        notifListener->second(session.get(), request);

                        session->lock.lock();
                        continue;
                    }
                }
                auto* response = dynamic_cast<LspResponseMessage*>(message.get());
                if(response) {
                    session->lock.lock();
                    auto listener = session->responseListeners.find(response->id);
                    if(listener != session->responseListeners.end()) {
                        message.release();
                        listener->second(std::unique_ptr<LspResponseMessage>(response));
                        session->responseListeners.erase(listener);
                        continue;
                    }
                }
                session->lock.lock();
            }
            session->lock.unlock();
        }
        _sessionsLock.unlock();
    }

    void LspServer::sendMessage(LspSession* session, std::unique_ptr<LspMessage> message)
    {
        session->lock.lock();
        if(session->oMessage) {
            session->messagesOut.push_back(std::move(message));
            return;
        }
        session->oMessage = std::make_unique<std::string>();
        session->lock.unlock();

        Json::Value value;
        message->serialize(value);

        Json::StreamWriterBuilder builder;
        builder["indentation"] = "";

        std::string body = Json::writeString(builder, value);

        *session->oMessage = "Content-Length: " + std::to_string(body.size()) + "\r\n\r\n" + body;

#ifndef NDEBUG
        std::cout << "Sending message: " << *session->oMessage << std::endl;
#endif
        asio::async_write(
            session->connection,
            asio::buffer(session->oMessage->data(), session->oMessage->size()),
            [this, session](std::error_code ec, size_t sentCount) {
            if(ec) {
                std::cerr << "Problem sending message! " << ec.message() << std::endl;
                removeSession(session);
            }
#ifndef NDEBUG
            std::cout << "Message sent" << std::endl;
#endif

            session->lock.lock();
            session->oMessage = nullptr;
            if(!session->messagesIn.empty()) {
                auto nextMessage = std::move(session->messagesOut.front());
                session->messagesOut.pop_front();
                sendMessage(session, std::move(nextMessage));
            }
            session->lock.unlock();
            });
    }

    void LspServer::readMessage(
        LspSession* session, std::function<void(std::unique_ptr<SerializedMessage>)> callback, bool recursive)
    {
        if(!session->iMessage)
            session->iMessage = std::make_unique<SerializedMessage>();
        auto callbackPtr =
            std::make_shared<std::function<void(std::unique_ptr<SerializedMessage>)>>(std::move(callback));
        asio::async_read_until(
            session->connection,
            session->buffer,
            "\r\n",
            [this, session, callbackPtr, recursive](std::error_code ec, size_t len) {
            if(ec) {
                removeSession(session);
                return;
            }
            std::string data = {buffers_begin(session->buffer.data()), buffers_end(session->buffer.data())};
            session->buffer.consume(len);
#ifndef NDEBUG
            std::cout << "Received message segment: " << data << std::endl;
#endif

            auto& message = session->iMessage;
            // If length is more than 2 that means that we're still reading the header
            if(len > 2) {
                assert(len >= 9); // TODO make this an actual check
                // The spec only defines two valid header fields, so for now we can be hacky about testing which one
                // is which
                if(data[8] == 'L') {
                    // Extract number from "Content-Length: [number]\r\n"
                    size_t size = std::stoull({data.data() + 16, len - 18});
                    message->message.resize(size);
                }
                else {
                    // Extract number from "Content-Type [type]\r\n"
                    std::string_view encoding = {data.data() + 14, len - 16};
                    if(encoding == "utf-8" || encoding == "utf8")
                        message->encoding = SerializedMessage::utf8;
                    else
                        return; // TODO Spec says we should respond with an error if it's anything else atm
                }
                readMessage(session, std::move(*callbackPtr), recursive);
                return;
            }

            if(message->message.empty()) {
                std::cerr << "No size header in message!";
                // TODO error;
                return;
            }
            asio::async_read(
                session->connection,
                asio::buffer(message->message.data(), message->message.size()),
                [this, session, callbackPtr, recursive](std::error_code ec, size_t len) {
                if(ec) {
                    removeSession(session);
                    return;
                }
                std::string& data = session->iMessage->message;
#ifndef NDEBUG
                std::cout << "received message body: " << data << std::endl;
#endif

                (*callbackPtr)(std::move(session->iMessage));
                if(recursive)
                    readMessage(session, std::move(*callbackPtr), recursive);
                });
            });
    }

    void LspServer::sendRequest(
        LspSession* session,
        std::unique_ptr<LspMessageRequest> request,
        std::function<void(std::unique_ptr<LspResponseMessage>)> callback)
    {
        session->lock.lock();
        auto id = session->requestIDCounter++;
        session->responseListeners.insert({std::to_string(id), callback});
        session->lock.unlock();

        request->id = id;
        sendMessage(session, std::move(request));
    }

} // namespace lsp

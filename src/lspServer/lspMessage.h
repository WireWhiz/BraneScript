//
// Created by wirewhiz on 18/01/23.
//

#ifndef BRANESCRIPT_LSPMESSAGE_H
#define BRANESCRIPT_LSPMESSAGE_H

#include "json/json.h"
#include <string>

namespace lsp
{
    struct LspMessageId {
        enum Type {
            null,
            integer,
            string
        } type;
        std::string id;
        void deserialize(const Json::Value& json);
        void serialize(Json::Value& json);
        void operator=(const std::string& newID);
        void operator=(uint32_t newID);
        operator std::string&();
    };

    struct LspMessage
    {
        virtual ~LspMessage() = default;
        virtual void deserialize(const Json::Value& json) = 0;
        virtual void serialize(Json::Value& json);
    };

    struct LspMessageRequest : public LspMessage
    {
        LspMessageId id;
        std::string method;
        Json::Value params;
        virtual void deserialize(const Json::Value& json);
        virtual void serialize(Json::Value& json);
    };

    struct LspResponseError
    {
        int code;
        std::string message;
        Json::Value data;
        void deserialize(const Json::Value& json);
        void serialize(Json::Value& json);
    };

    struct LspResponseMessage : public LspMessage
    {
        LspMessageId id;
        Json::Value result;
        std::unique_ptr<LspResponseError> error;

        virtual void deserialize(const Json::Value& json);
        void serialize(Json::Value& json) override;
    };
}



#endif //BRANESCRIPT_LSPMESSAGE_H

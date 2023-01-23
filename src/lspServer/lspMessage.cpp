//
// Created by wirewhiz on 18/01/23.
//

#include "lspMessage.h"

void lsp::LspMessageId::deserialize(const Json::Value& json)
{
    if(json["id"].isNull())
    {
        id = "";
        type = null;
    }
    else if(json["id"].isString())
    {
        id = json["id"].asString();
        type = string;
    }
    else
    {
        id = std::to_string(json["id"].asInt());
        type = integer;
    }
}

void lsp::LspMessageId::serialize(Json::Value& json)
{
    switch(type)
    {
    case null:
        json["id"] = Json::nullValue;
        break;
    case integer:
        json["id"] = std::stoi(id);
        break;
    case string:
        json["id"] = id;
        break;
    }
}

lsp::LspMessageId::operator std::string&() { return id; }
void lsp::LspMessageId::operator=(const std::string& newID) {
    type = string;
    id = newID;
}
void lsp::LspMessageId::operator=(uint32_t newID) {
    type = integer;
    id = std::to_string(newID);
}

void lsp::LspMessage::serialize(Json::Value& json)
{
    json["jsonrpc"] = "2.0";
}

void lsp::LspMessageRequest::deserialize(const Json::Value& json)
{
    id.deserialize(json);
    method = json["method"].asString();
    params = json["params"];
}

void lsp::LspMessageRequest::serialize(Json::Value& json)
{
    LspMessage::serialize(json);
    id.serialize(json);
    json["method"] = method;
    json["params"] = params;
}

void lsp::LspResponseError::deserialize(const Json::Value& json)
{
    code = json["code"].asInt();
    message = json["message"].asString();
    data = json["data"];
}

void lsp::LspResponseError::serialize(Json::Value& json)
{
    json["code"] = code;
    json["message"] = message;
    if(!data.isNull())
        json["data"] = data;
}

void lsp::LspResponseMessage::deserialize(const Json::Value& json)
{
    id.deserialize(json);
    result = json["result"];
    if(json.isMember("error"))
    {
        error = std::make_unique<LspResponseError>();
        error->deserialize(json["error"]);
    }
}

void lsp::LspResponseMessage::serialize(Json::Value& json)
{
    LspMessage::serialize(json);
    id.serialize(json);
    json["result"] = result;
    if(error)
        error->serialize(json["error"]);
}


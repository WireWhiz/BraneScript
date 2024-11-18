
#include "documentContext.h"
#include <cassert>

namespace BraneScript
{
    std::optional<TextContextNode> TextContext::getNodeAtChar(TSPoint pos) { return std::nullopt; }

    std::optional<TextContextNode> TextContext::findIdentifier(std::string_view identifier)
    {
        return findIdentifier(identifier, 0);
    }

    std::optional<TextContextNode> TextContext::findIdentifier(std::string_view identifier, uint8_t searchOptions)
    {
        return std::nullopt;
    }

    std::string TextContext::longId() const { return ""; }

    std::string ValueContext::signature() const
    {
        assert(false && "Unimplemented");
        std::string sig;
        return sig;
    }

    std::string ValueContext::longId() const
    {
        std::string id;
        if(parent)
        {
            if(auto p = parent->lock())
                id += p->longId() + "::";
        }
        if(label)
            id += label.value()->text;
        else
            id += "unnamed_value";
        return id;
    }

    std::optional<TextContextNode> PipelineContext::findIdentifier(std::string_view identifier, uint8_t searchOptions)
    {
        return std::nullopt;
    }

    std::string PipelineContext::longId() const
    {
        std::string idText;
        if(parent)
        {
            if(auto p = parent->lock())
                idText += p->longId() + "::";
        }
        idText += identifier->text;
        return idText;
    }

    std::optional<TextContextNode> ModuleContext::getNodeAtChar(TSPoint pos) { return std::nullopt; }

    std::optional<TextContextNode> ModuleContext::findIdentifier(std::string_view identifier, uint8_t searchOptions)
    {
        return std::nullopt;
    }

    std::optional<TextContextNode> DocumentContext::getNodeAtChar(TSPoint pos) { return std::nullopt; }

    std::optional<TextContextNode> DocumentContext::findIdentifier(std::string_view identifier, uint8_t searchOptions)
    {
        return std::nullopt;
    }

    std::string ModuleContext::longId() const
    {
        std::string id;
        if(parent)
        {
            if(auto p = parent->lock())
                id += p->longId() + "::";
        }
        return id + identifier->text;
    }
} // namespace BraneScript

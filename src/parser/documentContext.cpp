
#include "documentContext.h"
#include <cassert>

namespace BraneScript
{
    std::optional<DocumentContextNode> TextContext::getNodeAtChar(TSPoint pos)
    {
        return std::nullopt;
    }

    std::optional<DocumentContextNode> TextContext::findIdentifier(std::string_view identifier)
    {
        return findIdentifier(identifier, 0);
    }

    std::optional<DocumentContextNode> TextContext::findIdentifier(std::string_view identifier, uint8_t searchOptions)
    {
        return std::nullopt;
    }

    std::string TextContext::longId() const
    {
        return "";
    }


    std::string ValueContext::signature() const
    {
        assert(false && "Unimplemented");
        std::string sig;
        return sig;
    }


    std::string ValueContext::longId() const
    {
        std::string id;
        if(auto p = parent.lock())
            id += p->longId() + "::"; 
        if(label)
            id += label.value().text;
        else
            id += "unnamed_value";
        return id;
    }

    std::optional<DocumentContextNode> ModuleContext::getNodeAtChar(TSPoint pos)
    {
        return std::nullopt;
    }

    std::optional<DocumentContextNode> ModuleContext::findIdentifier(std::string_view identifier, uint8_t searchOptions)
    {
        return std::nullopt;
    }
    
    std::optional<DocumentContextNode> DocumentContext::getNodeAtChar(TSPoint pos)
    {
        return std::nullopt;
    }

    std::optional<DocumentContextNode> DocumentContext::findIdentifier(std::string_view identifier, uint8_t searchOptions)
    {
        return std::nullopt;
    }
    
    std::string ModuleContext::longId() const
    {
        std::string id;
        if(auto p = parent.lock())
            id += p->longId() + "::" ;
        return id + identifier.text;
    }
}




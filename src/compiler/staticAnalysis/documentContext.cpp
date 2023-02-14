//
// Created by wirewhiz on 1/23/23.
//

#include "documentContext.h"

namespace BraneScript
{
    Identifier::operator std::string&() { return text; }
    bool Identifier::operator==(const Identifier& o) const { return text == o.text; }
    bool Identifier::operator!=(const Identifier& o) const { return text == o.text; }

    bool TypeContext::operator==(const TypeContext& o) const
    {
        return identifier == o.identifier && storageType == o.storageType;
    }
    bool TypeContext::operator!=(const TypeContext& o) const
    {
        return identifier != o.identifier || storageType != o.storageType;
    }
    bool TypeContext::isScalar() const
    {
        return ValueType::Scalar_Begin <= storageType && storageType <= ValueType::Scalar_End;
    }
    bool TypeContext::isUnsigned() const
    {
        return ValueType::Unsigned_Begin <= storageType && storageType <= ValueType::Unsigned_End;
    }
    bool TypeContext::isInt() const { return ValueType::Int_Begin <= storageType && storageType <= ValueType::Int_End; }
    bool TypeContext::isFloat() const
    {
        return ValueType::Float_Begin <= storageType && storageType <= ValueType::Float_End;
    }
    uint8_t TypeContext::size() const
    {
        switch(storageType)
        {
        case ValueType::Void:
        case ValueType::Bool:
        case ValueType::Char:
            return 1;
        case ValueType::UInt32:
        case ValueType::Int32:
        case ValueType::Float32:
            return 4;
        case ValueType::UInt64:
        case ValueType::Int64:
        case ValueType::Float64:
            return 8;
        case ValueType::Struct:
            return sizeof(void*); // Not too important, these values are mostly used for casting cost calculations
        }
        return 1;
    }

    bool ValueContext::operator==(const ValueContext& o) const
    {
        if(type != o.type)
            return false;
        if(isConst != o.isConst)
            return false;
        if(isRef != o.isRef)
            return false;
        return true;
    }

    bool ValueContext::operator!=(const ValueContext& o) const
    {
        if(type != o.type)
            return true;
        if(isConst != o.isConst)
            return true;
        if(isRef != o.isRef)
            return true;
        return false;
    }

    void ValueContext::operator=(const LabeledValueContext& o)
    {
        type = o.type;
        isConst = o.isConst;
        isRef = o.isRef;
        isLValue = o.isLValue;
    }

    DocumentContext* DocumentContext::getNodeAtChar(TextPos pos)
    {
        if(range.posInRange(pos))
            return this;
        return nullptr;
    }

    DocumentContext* DocumentContext::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        if(!parent || searchOptions & IDSearchOptions_ChildrenOnly)
            return nullptr;
        return parent->findIdentifier(identifier, searchOptions);
    }

    void DocumentContext::getFunction(const std::string& identifier, std::list<FunctionContext*>& overrides)
    {
        if(parent)
            parent->getFunction(identifier, overrides);
    }

    std::string DocumentContext::getLongID() const
    {
        if(!parent)
            return "";
        return parent->getLongID();
    }

    std::string ValueContext::signature() const
    {
        std::string sig;
        if(isConst)
            sig += "const ";
        if(isRef)
            sig += "ref ";
        sig += type.identifier;
        return sig;
    }

    std::string LabeledValueContext::signature() const { return ValueContext::signature() + " " + identifier.text; }
    std::string LabeledValueContext::getLongID() const
    {
        auto prefix = DocumentContext::getLongID();
        if(prefix.empty())
            return identifier.text;
        return prefix + "::" + identifier.text;
    }

    DocumentContext* ScopeContext::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        for(auto& lv : localVariables)
        {
            if(lv->identifier.text == identifier)
                return lv.get();
        }
        return DocumentContext::findIdentifier(identifier, searchOptions);
    }

    ConstBoolContext::ConstBoolContext()
    {
        returnType.type = {"bool", ValueType::Bool};
        returnType.isConst = true;
    }

    ConstCharContext::ConstCharContext()
    {
        returnType.type = {"char", ValueType::Char};
        returnType.isConst = true;
    }

    ConstIntContext::ConstIntContext()
    {
        returnType.type = {"int", ValueType::Int32};
        returnType.isConst = true;
    }

    ConstFloatContext::ConstFloatContext()
    {
        returnType.type = {"float", ValueType::Float32};
        returnType.isConst = true;
    }

    ConstStringContext::ConstStringContext()
    {
        returnType.type = {"string", ValueType::Struct};
        returnType.isConst = true;
    }

    DocumentContext* FunctionContext::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        for(auto& arg : arguments)
        {
            if(arg.identifier.text == identifier)
                return &arg;
        }
        return DocumentContext::findIdentifier(identifier, searchOptions);
    }

    std::string FunctionContext::getLongID() const
    {
        auto prefix = DocumentContext::getLongID();
        if(prefix.empty())
            return identifier.text;
        return prefix + "::" + identifier.text;
    }

    DocumentContext* StructContext::getNodeAtChar(TextPos pos)
    {
        if(!DocumentContext::getNodeAtChar(pos))
            return nullptr;
        for(auto& f : functions)
        {
            auto node = f->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& v : variables)
        {
            auto node = v->getNodeAtChar(pos);
            if(node)
                return node;
        }

        return this;
    }

    DocumentContext* StructContext::findIdentifier(const std::string& id, uint8_t searchOptions)
    {
        for(auto& v : variables)
        {
            if(v->identifier.text == id)
                return v.get();
        }

        for(auto& f : functions)
        {
            if(f->identifier.text == id)
                return f.get();
        }
        return DocumentContext::findIdentifier(id, searchOptions);
    }

    void StructContext::getFunction(const std::string& identifier, std::list<FunctionContext*>& overrides)
    {
        for(auto& f : functions)
        {
            if(f->identifier.text == identifier)
                overrides.push_back(f.get());
        }
        DocumentContext::getFunction(identifier, overrides);
    }
    std::string StructContext::getLongID() const
    {
        auto prefix = DocumentContext::getLongID();
        if(prefix.empty())
            return identifier.text;
        return prefix + "::" + identifier.text;
    }

    DocumentContext* LibraryContext::getNodeAtChar(TextPos pos)
    {
        for(auto& f : functions)
        {
            auto node = f->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& s : structs)
        {
            auto node = s.second->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& g : globals)
        {
            auto node = g.second->getNodeAtChar(pos);
            if(node)
                return node;
        }
        if(!range.posInRange(pos))
            return nullptr;
        return this;
    }

    DocumentContext* LibraryContext::findIdentifier(const std::string& id, uint8_t searchOptions)
    {
        auto v = globals.find(id);
        if(v != globals.end())
            return v->second.get();

        for(auto& f : functions)
        {
            if(f->identifier.text == id)
                return f.get();
        }

        auto s = structs.find(id);
        if(s != structs.end())
            return s->second.get();

        if(searchOptions & IDSearchOptions_ChildrenOnly)
            return nullptr;
        return DocumentContext::findIdentifier(id, searchOptions);
    }

    void LibraryContext::getFunction(const std::string& identifier, std::list<FunctionContext*>& overrides)
    {
        for(auto& f : functions)
        {
            if(f->identifier.text == identifier)
                overrides.push_back(f.get());
        }
    }
    std::string LibraryContext::getLongID() const
    {
        auto prefix = DocumentContext::getLongID();
        if(prefix.empty())
            return identifier.text;
        return prefix + "::" + identifier.text;
    }

    DocumentContext* ScriptContext::getNodeAtChar(TextPos pos)
    {
        for(auto& f : functions)
        {
            auto node = f->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& s : structs)
        {
            auto node = s.second->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& g : globals)
        {
            auto node = g.second->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& lib : exports)
        {
            auto node = lib.second->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& i : imports)
        {
            auto node = i.getNodeAtChar(pos);
            if(node)
                return node;
        }
        if(!range.posInRange(pos))
            return nullptr;
        return this;
    }

    DocumentContext* ScriptContext::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        auto l = exports.find(identifier);
        if(l != exports.end())
            return l->second.get();

        auto v = globals.find(identifier);
        if(v != globals.end())
            return v->second.get();

        for(auto& f : functions)
        {
            if(f->identifier.text == identifier)
                return f.get();
        }

        auto s = structs.find(identifier);
        if(s != structs.end())
            return s->second.get();
        return nullptr;
    }

    void ScriptContext::getFunction(const std::string& identifier, std::list<FunctionContext*>& overrides)
    {
        for(auto& f : functions)
        {
            if(f->identifier.text == identifier)
                overrides.push_back(f.get());
        }
    }

    DocumentContext* LibrarySet::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        for(auto& lib : exports)
        {
            auto* ident = lib->findIdentifier(identifier, 0);
            if(ident)
                return ident;
        }
        return nullptr;
    }

    void LibrarySet::getFunction(const std::string& identifier, std::list<FunctionContext*>& overrides)
    {
        for(auto& lib : exports)
            lib->getFunction(identifier, overrides);
    }
} // namespace BraneScript
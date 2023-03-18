//
// Created by wirewhiz on 1/23/23.
//

#include "documentContext.h"
#include <cassert>

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

    std::string DocumentContext::longId() const
    {
        if(!parent)
            return "";
        return parent->longId();
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
    std::string LabeledValueContext::longId() const
    {
        auto prefix = DocumentContext::longId();
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

    StatementContext* ScopeContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        return nullptr;
    }

    ConstBoolContext::ConstBoolContext()
    {
        returnType.type = {"bool", ValueType::Bool};
        returnType.isConst = true;
    }

    StatementContext* ConstBoolContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        return new ConstBoolContext(*this);
    }

    ConstCharContext::ConstCharContext()
    {
        returnType.type = {"char", ValueType::Char};
        returnType.isConst = true;
    }

    StatementContext* ConstCharContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        return new ConstCharContext(*this);
    }

    ConstIntContext::ConstIntContext()
    {
        returnType.type = {"int", ValueType::Int32};
        returnType.isConst = true;
    }

    StatementContext* ConstIntContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        return new ConstIntContext(*this);
    }

    ConstFloatContext::ConstFloatContext()
    {
        returnType.type = {"float", ValueType::Float32};
        returnType.isConst = true;
    }

    StatementContext* ConstFloatContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        return new ConstFloatContext(*this);
    }

    ConstStringContext::ConstStringContext()
    {
        returnType.type = {"BraneScript::string", ValueType::Struct};
        returnType.isConst = true;
    }

    StatementContext* ConstStringContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        return new ConstStringContext(*this);
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

    std::string FunctionContext::longId() const
    {
        auto prefix = DocumentContext::longId();
        if(prefix.empty())
            return identifier.text;
        return prefix + "::" + identifier.text;
    }

    std::string FunctionContext::signature() const {
        std::string sig = longId();
        sig += "(";

        size_t argIndex = 0;
        for(auto itr = arguments.begin();itr != arguments.end();)
        {
            auto& arg = *itr;
            if(arg.isConst)
                sig += "const ";
            if(arg.isRef)
                sig += "ref ";
            sig += arg.type.identifier;
            if(++itr != arguments.end())
                sig += ",";
            else
                break;
        }
        sig+= ")";
        return sig;
    }

    FunctionContext* FunctionContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        auto* func = new FunctionContext{};
        func->arguments = arguments;
        for(auto& arg : func->arguments)
        {
            if(args.contains(arg.type.identifier))
            {
                arg.type = ((TemplateTypeArgContext*)(args.at(arg.type.identifier).get()))->type;
            }
        }
        return nullptr;
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

    std::string StructContext::longId() const
    {
        auto prefix = DocumentContext::longId();
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
            auto node = s->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& g : globals)
        {
            auto node = g->getNodeAtChar(pos);
            if(node)
                return node;
        }
        if(!range.posInRange(pos))
            return nullptr;
        return this;
    }

    DocumentContext* LibraryContext::findIdentifier(const std::string& id, uint8_t searchOptions)
    {
        for(auto& g : globals)
        {
            if(g->identifier.text == id)
                return g.get();
        }

        for(auto& f : functions)
        {
            if(f->identifier.text == id)
                return f.get();
        }

        for(auto& s : structs)
        {
            if(s->identifier.text == id)
                return s.get();
        }

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
    std::string LibraryContext::longId() const
    {
        auto prefix = DocumentContext::longId();
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
            auto node = s->getNodeAtChar(pos);
            if(node)
                return node;
        }
        for(auto& g : globals)
        {
            auto node = g->getNodeAtChar(pos);
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

        for(auto& g : globals)
        {
            if(g->identifier.text == identifier)
                return g.get();
        }

        for(auto& f : functions)
        {
            if(f->identifier.text == identifier)
                return f.get();
        }

        for(auto& s : structs)
        {
            if(s->identifier.text == identifier)
                return s.get();
        }
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

    StatementContext* StatementErrorContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        return new StatementErrorContext(*this);
    }

    StatementContext* ExpressionErrorContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        return new ExpressionErrorContext(*this);
    }

    StatementContext* ReturnContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        auto output = new ReturnContext();
        if(output->value)
            output->value.reset(value->instantiateTemplate(analyzer, args)->as<ExpressionContext>());
        assert((bool)output->value == (bool)value);
        if(output->value)
            output->value->parent = output;
        output->range = range;
        output->version = version;

        return output;
    }

    StatementContext* IfContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        auto output = new IfContext();
        output->condition.reset(condition->instantiateTemplate(analyzer, args)->as<ExpressionContext>());
        output->body.reset(body->instantiateTemplate(analyzer, args)->as<ExpressionContext>());
        if(elseBody)
            output->elseBody.reset(elseBody->instantiateTemplate(analyzer, args)->as<ExpressionContext>());
        assert(output->condition);
        assert(output->body);
        assert((bool)elseBody == (bool)output->elseBody);
        output->condition->parent = output;
        output->body->parent = output;
        if(output->elseBody)
            output->elseBody->parent = output;

        output->range = range;
        output->version = version;

        return output;
    }

    StatementContext* WhileContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        auto output = new WhileContext();
        output->condition.reset(condition->instantiateTemplate(analyzer, args)->as<ExpressionContext>());
        output->body.reset(body->instantiateTemplate(analyzer, args)->as<ExpressionContext>());
        assert(output->condition);
        assert(output->body);
        output->condition->parent = output;
        output->body->parent = output;

        output->range = range;
        output->version = version;

        return output;
    }

    StatementContext* AssignmentContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        auto output = new AssignmentContext();
        output->lValue.reset(lValue->instantiateTemplate(analyzer, args)->as<ExpressionContext>());
        output->rValue.reset(rValue->instantiateTemplate(analyzer, args)->as<ExpressionContext>());
        assert(output->lValue);
        assert(output->rValue);
        output->lValue->parent = output;
        output->rValue->parent = output;

        output->range = range;
        output->version = version;

        return output;
    }

    LabeledValueConstructionContext::LabeledValueConstructionContext(const LabeledValueContext& value)
    {
        identifier = value.longId();
        returnType = value;
    }

    LabeledValueReferenceContext::LabeledValueReferenceContext(const LabeledValueContext& value)
    {
        identifier = value.longId();
        returnType = value;

    }

    StatementContext* LabeledValueReferenceContext::instantiateTemplate(StaticAnalyzer& analyzer,
                                                                        const TemplateArgs& args)
    {
        return new LabeledValueReferenceContext(*this);
    }

    MemberAccessContext::MemberAccessContext(ExpressionContext* base, StructContext* baseType, size_t member)
    {
        baseExpression.reset(base);
        assert(base->returnType.type.identifier == baseType->longId());
        assert(member < baseType->variables.size());
        returnType = *baseType->variables[member];
        this->member = member;
    }

    StatementContext* MemberAccessContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        auto output = new MemberAccessContext();
        output->baseExpression.reset(baseExpression->instantiateTemplate(analyzer, args)->as<ExpressionContext>());
        assert(baseExpression);
        output->baseExpression->parent = output;
        output->range = range;
        output->version = version;

        return output;
    }

    StatementContext* FunctionCallContext::instantiateTemplate(StaticAnalyzer& analyzer, const TemplateArgs& args)
    {
        return new FunctionCallContext(*this);
    }
} // namespace BraneScript
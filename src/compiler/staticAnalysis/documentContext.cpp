//
// Created by wirewhiz on 1/23/23.
//

#include "documentContext.h"
#include <cassert>

namespace BraneScript
{
    template<typename T, typename Arg>
    T* assertCast(Arg* arg)
    {
        T* result = dynamic_cast<T*>(arg);
        assert(result);
        return result;
    }

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

    void DocumentContext::getFunction(const std::string& identifier,
                                      std::list<FunctionContext*>& overrides,
                                      uint8_t searchOptions)
    {
        if(parent && !(searchOptions & IDSearchOptions_ChildrenOnly))
            parent->getFunction(identifier, overrides, searchOptions);
    }

    std::string DocumentContext::longId() const
    {
        if(!parent)
            return "";
        return parent->longId();
    }

    void DocumentContext::copyBase(DocumentContext* src, DocumentContext* dest)
    {
        dest->range = src->range;
        dest->version = src->version;
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
        if(parent && getParent<FunctionContext>())
            return identifier.text;
        auto prefix = DocumentContext::longId();
        if(prefix.empty())
            return identifier.text;
        return prefix + "::" + identifier.text;
    }

    DocumentContext* LabeledValueContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return callback(new LabeledValueContext(*this));
    }

    LabeledValueContext::LabeledValueContext(std::string identifier, ValueContext value) : ValueContext(value)
    {
        this->identifier.text = std::move(identifier);
    }

    DocumentContext* StatementErrorContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return callback(new StatementErrorContext{*this});
    }

    DocumentContext* ExpressionErrorContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return callback(new ExpressionErrorContext{*this});
    }

    void ExpressionContext::copyBase(DocumentContext* src, DocumentContext* dest)
    {
        DocumentContext::copyBase(src, dest);
        auto srcExpr = (ExpressionContext*)src;
        auto destExpr = (ExpressionContext*)dest;
        destExpr->returnType = srcExpr->returnType;
        destExpr->isConstexpr = srcExpr->isConstexpr;
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

    DocumentContext* ScopeContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        auto* copy = new ScopeContext{};
        copyBase(this, copy);
        for(auto& var : localVariables)
        {
            auto varCopy = assertCast<LabeledValueContext>(var->deepCopy(callback));
            varCopy->parent = copy;
            copy->localVariables.emplace_back(varCopy);
        }
        for(auto& stmt : statements)
        {
            auto stmtCopy = assertCast<StatementContext>(stmt->deepCopy(callback));
            stmtCopy->parent = copy;
            copy->statements.emplace_back(stmtCopy);
        }
        return callback(copy);
    }

    DocumentContext* ReturnContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        auto* copy = new ReturnContext{};
        copyBase(this, copy);
        copy->value.reset(assertCast<ExpressionContext>(value->deepCopy(callback)));
        copy->value->parent = copy;
        return callback(copy);
    }

    DocumentContext* IfContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        auto* copy = new IfContext{};
        copyBase(this, copy);
        copy->condition.reset(assertCast<ExpressionContext>(condition->deepCopy(callback)));
        copy->condition->parent = copy;
        copy->body.reset(assertCast<StatementContext>(body->deepCopy(callback)));
        copy->condition->parent = copy;
        if(elseBody)
        {
            copy->elseBody.reset(assertCast<StatementContext>(elseBody->deepCopy(callback)));
            copy->elseBody->parent = copy;
        }
        return callback(copy);
    }

    DocumentContext* WhileContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        auto* copy = new WhileContext{};
        copyBase(this, copy);
        copy->condition.reset(assertCast<ExpressionContext>(condition->deepCopy(callback)));
        copy->condition->parent = copy;
        copy->body.reset(assertCast<StatementContext>(body->deepCopy(callback)));
        copy->body->parent = copy;
        return callback(copy);
    }

    DocumentContext* AssignmentContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        auto* copy = new AssignmentContext{};
        copyBase(this, copy);
        copy->lValue.reset(assertCast<ExpressionContext>(lValue->deepCopy(callback)));
        copy->lValue->parent = copy;
        copy->rValue.reset(assertCast<ExpressionContext>(rValue->deepCopy(callback)));
        copy->rValue->parent = copy;
        return callback(copy);
    }

    ConstBoolContext::ConstBoolContext()
    {
        returnType.type = {"bool", ValueType::Bool};
        returnType.isConst = true;
    }

    DocumentContext* ConstBoolContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return callback(new ConstBoolContext{*this});
    }

    ConstCharContext::ConstCharContext()
    {
        returnType.type = {"char", ValueType::Char};
        returnType.isConst = true;
    }

    DocumentContext* ConstCharContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return callback(new ConstCharContext{*this});
    }

    ConstIntContext::ConstIntContext()
    {
        returnType.type = {"int", ValueType::Int32};
        returnType.isConst = true;
    }

    DocumentContext* ConstIntContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return callback(new ConstIntContext{*this});
    }

    ConstFloatContext::ConstFloatContext()
    {
        returnType.type = {"float", ValueType::Float32};
        returnType.isConst = true;
    }

    DocumentContext* ConstFloatContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return callback(new ConstFloatContext{*this});
    }

    ConstStringContext::ConstStringContext()
    {
        returnType.type = {"BraneScript::string", ValueType::Struct};
        returnType.isConst = true;
    }

    DocumentContext* ConstStringContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return callback(new ConstStringContext{*this});
    }

    LabeledValueConstructionContext::LabeledValueConstructionContext(const LabeledValueContext& value)
    {
        identifier = value.longId();
        returnType = value;
    }

    DocumentContext* LabeledValueConstructionContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return callback(new LabeledValueConstructionContext{*this});
    }

    LabeledValueReferenceContext::LabeledValueReferenceContext(const LabeledValueContext& value)
    {
        identifier = value.longId();
        returnType = value;

    }

    DocumentContext*
    LabeledValueReferenceContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return callback(new LabeledValueReferenceContext{*this});
    }

    MemberAccessContext::MemberAccessContext(ExpressionContext* base, StructContext* baseType, size_t member)
    {
        baseExpression.reset(base);
        assert(base->returnType.type.identifier == baseType->longId());
        assert(member < baseType->variables.size());
        returnType = *baseType->variables[member];
        this->member = member;
    }

    DocumentContext* MemberAccessContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        auto* copy = new MemberAccessContext{};
        copyBase(this, copy);
        copy->baseExpression.reset(assertCast<ExpressionContext>(baseExpression->deepCopy(callback)));
        copy->baseExpression->parent = copy;
        copy->member = member;
        return callback(copy);
    }

    DocumentContext* FunctionCallContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        auto* copy = new FunctionCallContext{};
        copyBase(this, copy);
        copy->function = function;
        for(auto& arg : arguments)
            copy->arguments.emplace_back(assertCast<ExpressionContext>(arg->deepCopy(callback)));
        return callback(copy);
    }

    DocumentContext* FunctionContext::findIdentifier(const std::string& identifier, uint8_t searchOptions)
    {
        for(auto& arg : arguments)
        {
            if(arg->identifier.text == identifier)
                return arg.get();
        }
        auto argPack = argPackInstances.find(identifier);
        if(argPack != argPackInstances.end())
            return &argPack->second;
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
            if(arg->isConst)
                sig += "const ";
            if(arg->isRef)
                sig += "ref ";
            sig += arg->type.identifier;
            if(++itr != arguments.end())
                sig += ",";
            else
                break;
        }
        sig+= ")";
        return sig;
    }

    DocumentContext* FunctionContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        auto* copy = new FunctionContext{};
        copyBase(this, copy);
        copy->identifier = identifier;
        copy->returnType = returnType;
        for(auto& arg : arguments)
        {
            auto* newArg = assertCast<LabeledValueContext>(arg->deepCopy(callback));
            copy->arguments.emplace_back(newArg);
            delete newArg;
        }

        copy->isConst = isConst;
        copy->isConstexpr = isConstexpr;
        if(body)
        {
            copy->body.reset(assertCast<ScopeContext>(body->deepCopy(callback)));
            copy->body->parent = copy;
        }

        return callback(copy);
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

    void StructContext::getFunction(const std::string& identifier,
                                    std::list<FunctionContext*>& overrides,
                                    uint8_t searchOptions)
    {
        for(auto& f : functions)
        {
            if(f->identifier.text == identifier)
                overrides.push_back(f.get());
        }
        DocumentContext::getFunction(identifier, overrides, searchOptions);
    }

    std::string StructContext::longId() const
    {
        auto prefix = DocumentContext::longId();
        if(prefix.empty())
            return identifier.text;
        return prefix + "::" + identifier.text;
    }

    DocumentContext* StructContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        auto* copy = new StructContext{};
        copyBase(this, copy);
        copy->identifier = identifier;

        for(auto& var : variables)
            copy->variables.emplace_back(assertCast<LabeledValueContext>(var->deepCopy(callback)));
        for(auto& func : functions)
            copy->functions.emplace_back(assertCast<FunctionContext>(func->deepCopy(callback)));
        copy->packed = packed;

        return callback(copy);
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

    void
    LibraryContext::getFunction(const std::string& id, std::list<FunctionContext*>& overrides, uint8_t searchOptions)
    {
        DocumentContext::getFunction(id, overrides, searchOptions);
        for(auto& f : functions)
        {
            if(f->identifier.text == id)
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

    DocumentContext* LibraryContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        auto* copy = new LibraryContext{};
        copyBase(this, copy);
        copy->identifier = identifier;

        for(auto& var : globals)
            copy->globals.emplace_back(assertCast<LabeledValueContext>(var->deepCopy(callback)));
        for(auto& s : structs)
            copy->structs.emplace_back(assertCast<StructContext>(s->deepCopy(callback)));
        for(auto& func : functions)
            copy->functions.emplace_back(assertCast<FunctionContext>(func->deepCopy(callback)));

        return callback(copy);
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

    void ScriptContext::getFunction(const std::string& identifier,
                                    std::list<FunctionContext*>& overrides,
                                    uint8_t searchOptions)
    {
        for(auto& f : functions)
        {
            if(f->identifier.text == identifier)
                overrides.push_back(f.get());
        }

        if(!(searchOptions & IDSearchOptions_ParentsOnly))
        {
            for(auto& lib : exports)
                lib.second->getFunction(identifier, overrides, searchOptions);
        }
    }

    DocumentContext* ScriptContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        auto* copy = new ScriptContext{};
        copyBase(this, copy);

        for(auto& var : globals)
            copy->globals.emplace_back(assertCast<LabeledValueContext>(var->deepCopy(callback)));
        for(auto& s : structs)
            copy->structs.emplace_back(assertCast<StructContext>(s->deepCopy(callback)));
        for(auto& func : functions)
            copy->functions.emplace_back(assertCast<FunctionContext>(func->deepCopy(callback)));
        for(auto& lib : exports)
            copy->exports.insert({lib.first, assertCast<LibraryContext>(lib.second->deepCopy(callback))});
        for(auto& lib : imports)
        {
            auto* imp = assertCast<ImportContext>(lib.deepCopy(callback));
            copy->imports.emplace_back(*imp);
            delete imp;
        }

        return callback(copy);
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

    void LibrarySet::getFunction(const std::string& identifier,
                                 std::list<FunctionContext*>& overrides,
                                 uint8_t searchOptions)
    {
        for(auto& lib : exports)
            lib->getFunction(identifier, overrides, searchOptions);
    }

    DocumentContext* LibrarySet::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return callback(new LibrarySet{*this});
    }

    std::string LibrarySet::longId() const
    {
        if(exports.empty())
            return "";
        return (*exports.begin())->longId();
    }

    DocumentContext* ImportContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return callback(new ImportContext{*this});
    }

    TemplateTypeArgContext::TemplateTypeArgContext(std::string id, ValueContext value) : value(std::move(value)) {
        identifier = std::move(id);
    }

    DocumentContext* ArgPackInstanceContext::deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback)
    {
        return new ArgPackInstanceContext{*this};
    }
} // namespace BraneScript
//
// Created by wirewhiz on 1/23/23.
//

#ifndef BRANESCRIPT_FUNCTIONCONTEXT_H
#define BRANESCRIPT_FUNCTIONCONTEXT_H

#include "robin_hood.h"
#include "src/scriptRuntime/valueIndex.h"
#include "textPos.h"
#include <string>
#include <vector>
#include <json/json.h>
#include <list>

namespace BraneScript
{
    struct Identifier
    {
        TextRange range;
        std::string text;
        operator std::string&();
        bool operator ==(const Identifier&) const;
        bool operator!=(const Identifier&) const;

    };

    struct TypeContext
    {
        std::string identifier = "void";
        ValueType storageType = ValueType::Void;
        bool operator ==(const TypeContext&) const;
        bool operator!=(const TypeContext&) const;
        bool isScalar() const;
        bool isUnsigned() const;
        bool isInt() const;
        bool isFloat() const;
        uint8_t size() const;
    };

    struct LabeledValueContext;
    struct ValueContext
    {
        // reference to the type this value holds
        TypeContext type;

        // Is stored on the heap or the stack, instead of being a temporary value holder
        bool isLValue = false;
        // Value can not be changed, mostly for use with references
        bool isConst = false;
        // Is this a reference
        bool isRef = false;

        bool operator ==(const ValueContext& o) const;
        bool operator !=(const ValueContext& o) const;

        void operator=(const LabeledValueContext& o);

        virtual std::string signature() const;
    };

    template<typename T>
    using LabeledNodeMap = robin_hood::unordered_flat_map<std::string, std::unique_ptr<T>>;
    template<typename T>
    using LabeledNodeList = std::vector<std::unique_ptr<T>>;

    struct FunctionContext;
    struct StructContext;

    // Not yet implemented
    enum IDSearchOptions : uint8_t
    {
        IDSearchOptions_ChildrenOnly = 1 << 0, // Don't search upwards through the tree
        IDSearchOptions_ParentsOnly  = 1 << 1, // Don't search downwards through the tree
        IDSearchOptions_ValuesOnly   = 1 << 2 // Will only return values from scopes, functions, and global variables.
                                              // excludes struct member variables so that "this" pointer must be used
    };

    struct DocumentContext
    {
        TextRange range;
        DocumentContext* parent = nullptr;
        uint16_t version = 0;

        virtual DocumentContext* getNodeAtChar(TextPos pos);
        virtual DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions = 0);
        virtual void getFunction(const std::string& identifier, std::list<FunctionContext*>& overrides);
        virtual std::string getLongID() const;

        template<typename T>
        T* as()
        {
            return dynamic_cast<T*>(this);
        }

        template<typename T>
        bool is()
        {
            return dynamic_cast<T*>(this);
        }

        template<typename T>
        T* getParent()
        {
            if(!parent)
                return nullptr;
            auto p = parent->as<T>();
            if(p)
                return p;
            return parent->getParent<T>();
        }
    };

    struct LabeledValueReferenceContext;
    struct LabeledValueContext : public DocumentContext, ValueContext
    {
        Identifier identifier;
        /* Last assignment to check if this value is a constant expression */
        struct Reference
        {
            LabeledValueReferenceContext* ctx;
            bool isAssignment = false;
        };
        std::list<Reference> references;

        std::string signature() const override;
        std::string getLongID() const override;
    };

    struct StatementContext : public DocumentContext
    {
    };

    struct StatementErrorContext : public StatementContext
    {
    };

    struct ExpressionContext : public StatementContext
    {
        ValueContext returnType;
        // Is the result of this expression a constant?
        bool isConstexpr = false;
    };

    struct ExpressionErrorContext : public ExpressionContext
    {
    };

    struct ScopeContext : public StatementContext
    {
        // This must be a list so that we can keep construction/destruction order consistent
        std::vector<std::unique_ptr<LabeledValueContext>> localVariables;
        std::vector<std::unique_ptr<StatementContext>> statements;

        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
    };

    struct ReturnContext : public StatementContext
    {
        std::unique_ptr<ExpressionContext> value;
    };

    struct IfContext : public StatementContext
    {
        std::unique_ptr<ExpressionContext> condition;
        std::unique_ptr<StatementContext> body;
        std::unique_ptr<StatementContext> elseBody;
    };

    struct WhileContext : public StatementContext
    {
        std::unique_ptr<ExpressionContext> condition;
        std::unique_ptr<StatementContext> body;
    };

    struct AssignmentContext : public StatementContext
    {
        std::unique_ptr<ExpressionContext> lValue;
        std::unique_ptr<ExpressionContext> rValue;
    };

    struct ConstValueContext : public ExpressionContext
    {

    };

    struct ConstBoolContext : public ConstValueContext
    {
        bool value;
        ConstBoolContext();
    };

    struct ConstCharContext : public ConstValueContext
    {
        char value;
        ConstCharContext();
    };

    struct ConstIntContext : public ConstValueContext
    {
        int value;
        ConstIntContext();
    };

    struct ConstFloatContext : public ConstValueContext
    {
        float value;
        ConstFloatContext();
    };

    struct ConstStringContext : public ConstValueContext
    {
        std::string value;
        ConstStringContext();
    };

    struct LabeledValueConstructionContext : public ExpressionContext
    {
        LabeledValueContext* value = nullptr;
    };

    struct LabeledValueReferenceContext : public ExpressionContext
    {
        LabeledValueContext* value = nullptr;
        uint32_t referenceIndex = 0;
        bool isAssignment = false;
    };

    struct MemberAccessContext : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> baseExpression;
        size_t member = 0;
    };

    struct FunctionCallContext : public ExpressionContext
    {
        FunctionContext* function;
        std::vector<std::unique_ptr<ExpressionContext>> arguments;
    };

    struct FunctionContext : public DocumentContext
    {
        Identifier identifier;
        // Type identifier
        ValueContext returnType;
        // Arguments
        std::vector<LabeledValueContext> arguments;
        // Does not change state (globals/parent struct members)
        bool isConst = false;
        // Can be evaluated at compile time
        bool isConstexpr = false;

        std::unique_ptr<ScopeContext> body;

        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        std::string getLongID() const override;
    };

    struct StructContext : public DocumentContext
    {
        Identifier identifier;
        LabeledNodeList<LabeledValueContext> variables;
        LabeledNodeList<FunctionContext> functions;
        bool packed = false;

        DocumentContext* getNodeAtChar(TextPos pos) override;
        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        void getFunction(const std::string& identifier, std::list<FunctionContext*>& overrides) override;
        std::string getLongID() const override;
    };

    struct LibraryContext : public DocumentContext
    {
        Identifier identifier;
        LabeledNodeMap<LabeledValueContext> globals;
        LabeledNodeMap<StructContext> structs;
        LabeledNodeList<FunctionContext> functions;

        DocumentContext* getNodeAtChar(TextPos pos) override;
        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        void getFunction(const std::string& identifier, std::list<FunctionContext*>& overrides) override;
        std::string getLongID() const override;
    };

    struct LibrarySet : public DocumentContext
    {
        robin_hood::unordered_set<LibraryContext*> exports;
        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        void getFunction(const std::string& identifier, std::list<FunctionContext*>& overrides) override;
    };

    struct ImportContext : public DocumentContext
    {
        std::string library;
        // If alias is empty, that means that the library is imported without a prefix (like a using namespace)
        std::string alias;
    };

    struct ScriptContext : public DocumentContext
    {
        LabeledNodeMap<LabeledValueContext> globals;
        LabeledNodeMap<StructContext> structs;
        LabeledNodeList<FunctionContext> functions;
        LabeledNodeMap<LibraryContext> exports;
        std::vector<ImportContext> imports;

        DocumentContext* getNodeAtChar(TextPos pos) override;
        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        void getFunction(const std::string& identifier, std::list<FunctionContext*>& overrides) override;
    };
} // namespace BraneScript

#endif // BRANESCRIPT_FUNCTIONCONTEXT_H

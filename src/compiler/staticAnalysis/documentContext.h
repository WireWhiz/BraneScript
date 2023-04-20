//
// Created by wirewhiz on 1/23/23.
//

#ifndef BRANESCRIPT_FUNCTIONCONTEXT_H
#define BRANESCRIPT_FUNCTIONCONTEXT_H

#include <cstdarg>
#include <list>
#include <string>
#include <vector>
#include "robin_hood.h"
#include "src/scriptRuntime/valueIndex.h"
#include "textPos.h"
#include <json/json.h>

namespace antlr4
{
    class TokenStream;
}

namespace BraneScript
{
    class StaticAnalyzer;
    struct FunctionContext;
    struct StructContext;

    struct Identifier
    {
        TextRange range;
        std::string text;
        operator std::string&();
        bool operator==(const Identifier&) const;
        bool operator!=(const Identifier&) const;
    };

    struct TypeContext
    {
        std::string identifier = "void";
        ValueType storageType = ValueType::Void;
        StructContext* structDef = nullptr;

        bool operator==(const TypeContext&) const;
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

        bool operator==(const ValueContext& o) const;
        bool operator!=(const ValueContext& o) const;

        void operator=(const LabeledValueContext& o);

        virtual std::string signature() const;
    };

    template<typename T>
    using LabeledNodeMap = robin_hood::unordered_flat_map<std::string, std::unique_ptr<T>>;
    template<typename T>
    using LabeledNodeList = std::vector<std::unique_ptr<T>>;

    struct TemplateDefArgumentContext
    {
        std::string identifier;
        enum ArgType {
            Typedef,
            TypedefPack,
            Constant
        } type = Typedef;
        TypeContext expectedType;
    };

    struct TemplateArgContext
    {
        std::string identifier;
        virtual ~TemplateArgContext() = default;
    };

    struct TypedefArgContext : public TemplateArgContext
    {
        ValueContext value;
        TypedefArgContext(std::string id, ValueContext value);
    };

    struct TypedefPackArgContext : public TemplateArgContext
    {
        std::vector<ValueContext> values;
    };

    struct ConstValueContext;
    struct ConstantArgContext : public TemplateArgContext
    {
        std::unique_ptr<ConstValueContext> values;
    };

    // Not yet implemented
    enum IDSearchOptions : uint8_t
    {
        IDSearchOptions_ChildrenOnly = 1 << 0, // Don't search upwards through the tree
        IDSearchOptions_ParentsOnly = 1 << 1,  // Don't search downwards through the tree
        IDSearchOptions_ValuesOnly = 1 << 2    // Will only return values from scopes, functions, and global variables.
                                               // excludes struct member variables so that "this" pointer must be used
    };

    struct DocumentContext
    {
        TextRange range;
        DocumentContext* parent = nullptr;
        uint16_t version = 0;

        virtual ~DocumentContext() = default;
        virtual DocumentContext* getNodeAtChar(TextPos pos);
        virtual DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions = 0);
        virtual void  getFunction(const std::string& identifier, std::list<FunctionContext*>& overrides, uint8_t searchOptions = 0);
        virtual std::string longId() const;

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
        T* getParent() const
        {
            if(!parent)
                return nullptr;
            auto p = parent->as<T>();
            if(p)
                return p;
            return parent->getParent<T>();
        }

        /** Creates a deep copy of this node and it's children
         * @param callback called each time a node is copied, said node is passed to the callback.
         * This is intended to allow for modification of nodes
         */
        virtual DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const = 0;
      protected:
        virtual void copyBase(const DocumentContext* src, DocumentContext* dest) const;
    };

    struct LabeledValueReferenceContext;

    struct LabeledValueContext : public DocumentContext, public ValueContext
    {
        Identifier identifier;

        std::string signature() const override;
        std::string longId() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
        LabeledValueContext() = default;
        LabeledValueContext(std::string identifier, ValueContext value);
    };


    struct ArgPackInstanceContext : public DocumentContext
    {
        std::string identifier;
        std::vector<LabeledValueContext*> values;
        virtual DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const;
    };

    struct ErrorContext
    {
        std::string message;
        size_t line = 0;
    };

    struct StatementContext : public DocumentContext
    {
        virtual bool isConstexpr() const = 0;
    };

    struct StatementErrorContext : public StatementContext, ErrorContext
    {
        inline StatementErrorContext(std::string message, size_t line)
        {
            this->message = std::move(message);
            this->line = line;
        }
        bool isConstexpr() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ExpressionContext : public StatementContext
    {
        ValueContext returnType;
        // Is the result of this expression a constant?
      protected:
        void copyBase(const DocumentContext* src, DocumentContext* dest) const override;
    };

    struct ExpressionErrorContext : public ExpressionContext, ErrorContext
    {
        inline ExpressionErrorContext(std::string message, size_t line)
        {
            this->message = std::move(message);
            this->line = line;
        }
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
        bool isConstexpr() const override;
    };

    struct ScopeContext : public StatementContext
    {
        // This must be a list so that we can keep construction/destruction order consistent
        std::vector<std::unique_ptr<LabeledValueContext>> localVariables;
        std::vector<std::unique_ptr<StatementContext>> statements;

        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
        bool isConstexpr() const override;
    };

    struct ReturnContext : public StatementContext
    {
        std::unique_ptr<ExpressionContext> value;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
        bool isConstexpr() const override;
    };

    struct IfContext : public StatementContext
    {
        std::unique_ptr<ExpressionContext> condition;
        std::unique_ptr<StatementContext> body;
        std::unique_ptr<StatementContext> elseBody;
        bool isConstexpr() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct WhileContext : public StatementContext
    {
        std::unique_ptr<ExpressionContext> condition;
        std::unique_ptr<StatementContext> body;
        bool isConstexpr() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct AssignmentContext : public StatementContext
    {
        std::unique_ptr<ExpressionContext> lValue;
        std::unique_ptr<ExpressionContext> rValue;
        bool isConstexpr() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ConstValueContext : public ExpressionContext
    {
        bool isConstexpr() const override;
    };

    struct ConstBoolContext : public ConstValueContext
    {
        bool value;
        ConstBoolContext();
        ConstBoolContext(bool value);
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ConstCharContext : public ConstValueContext
    {
        char value;
        ConstCharContext();
        ConstCharContext(char value);
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ConstIntContext : public ConstValueContext
    {
        int value;
        ConstIntContext();
        ConstIntContext(int value);
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ConstFloatContext : public ConstValueContext
    {
        float value;
        ConstFloatContext();
        ConstFloatContext(float value);
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ConstStringContext : public ConstValueContext
    {
        std::string value;
        ConstStringContext();
        ConstStringContext(std::string value);
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct LabeledValueConstructionContext : public ExpressionContext
    {
        std::string identifier;
        LabeledValueConstructionContext(const LabeledValueContext& value);
        LabeledValueConstructionContext() = default;

        bool isConstexpr() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct LabeledValueReferenceContext : public ExpressionContext
    {
        std::string identifier;
        LabeledValueReferenceContext(const LabeledValueContext& value);

        bool isConstexpr() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct MemberAccessContext : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> baseExpression;
        size_t member = -1;
        MemberAccessContext() = default;
        MemberAccessContext(ExpressionContext* base, StructContext* baseType, size_t member);

        bool isConstexpr() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct FunctionCallContext : public ExpressionContext
    {
        FunctionContext* function;
        std::vector<std::unique_ptr<ExpressionContext>> arguments;

        bool isConstexpr() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct FunctionContext : public DocumentContext
    {
        Identifier identifier;
        // Type identifier
        ValueContext returnType;
        // Arguments
        LabeledNodeList<LabeledValueContext> arguments;
        // Template arg pack instances
        robin_hood::unordered_map<std::string, ArgPackInstanceContext> argPackInstances;
        // Does not change state (globals/parent struct members)
        bool isConst = false;
        // Can be evaluated at compile time
        bool isConstexpr = false;

        std::unique_ptr<ScopeContext> body;

        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        std::string longId() const override;
        std::string signature() const;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct StructContext : public DocumentContext
    {
        Identifier identifier;
        LabeledNodeList<LabeledValueContext> variables;
        LabeledNodeList<FunctionContext> functions;
        bool packed = false;

        FunctionContext* constructor = nullptr;
        FunctionContext* destructor = nullptr;
        FunctionContext* copyConstructor = nullptr;
        FunctionContext* moveConstructor = nullptr;

        DocumentContext* getNodeAtChar(TextPos pos) override;
        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        void getFunction(const std::string& identifier,
                         std::list<FunctionContext*>& overrides,
                         uint8_t searchOptions) override;
        std::string longId() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct LibraryContext : public DocumentContext
    {
        Identifier identifier;
        LabeledNodeList<LabeledValueContext> globals;
        LabeledNodeList<StructContext> structs;
        LabeledNodeList<FunctionContext> functions;

        DocumentContext* getNodeAtChar(TextPos pos) override;
        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        void getFunction(const std::string& identifier,
                         std::list<FunctionContext*>& overrides,
                         uint8_t searchOptions) override;
        std::string longId() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct LibrarySet : public DocumentContext
    {
        robin_hood::unordered_set<LibraryContext*> exports;
        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        void getFunction(const std::string& identifier,
                         std::list<FunctionContext*>& overrides,
                         uint8_t searchOptions) override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
        std::string longId() const override;
    };

    struct ImportContext : public DocumentContext
    {
        std::string library;
        // If alias is empty, that means that the library is imported without a prefix (like a using namespace)
        std::string alias;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ScriptContext : public DocumentContext
    {
        LabeledNodeList<LabeledValueContext> globals;
        LabeledNodeList<StructContext> structs;
        LabeledNodeList<FunctionContext> functions;
        LabeledNodeMap<LibraryContext> exports;
        std::vector<ImportContext> imports;

        std::vector<FunctionContext*> callOrder;

        DocumentContext* getNodeAtChar(TextPos pos) override;
        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        void getFunction(const std::string& identifier,
                         std::list<FunctionContext*>& overrides,
                         uint8_t searchOptions) override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };
} // namespace BraneScript

#endif // BRANESCRIPT_FUNCTIONCONTEXT_H

#ifndef BRANESCRIPT_DOCUMENTCONTEXT_H
#define BRANESCRIPT_DOCUMENTCONTEXT_H

#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>
#include <tree_sitter/api.h>
#include "../types/valueType.h"
#include <unordered_map>
#include <filesystem>

namespace BraneScript
{
    template<class T>
    using Node = std::shared_ptr<T>;
    template<typename T>
    using LabeledNodeMap = std::unordered_map<std::string, Node<T>>;
    template<typename T>
    using LabeledNodeList = std::vector<Node<T>>;
     
    struct Identifier
    {
        TSRange range;
        std::string text;
        operator std::string&();
        bool operator==(const Identifier&) const;
        bool operator!=(const Identifier&) const;
    };
    
    struct BaseType
    {
        ValueType value = ValueType::Void;

        bool operator==(const BaseType&) const;
        bool operator!=(const BaseType&) const;
        bool isScalar() const;
        bool isUnsigned() const;
        bool isInt() const;
        bool isFloat() const;
        uint8_t size() const;
    };

    struct RefTypeContext;
    struct StructContext;

    using TypeContext = std::variant<
        Node<RefTypeContext>, 
        Node<StructContext>, 
        Node<BaseType>
    >;

    struct RefTypeContext
    {
        bool isMut = false;
        // If this is a local pointer we don't need a handle value, otherwise we describe this with a wide pointer.
        bool isLocal = false;
        TypeContext containedType;
    };


   
    struct TextContext;
    struct ValueContext;
    using DocumentContextNode = std::variant<
        Node<TextContext>,
        Node<ValueContext>
    >;

    enum IDSearchOptions : uint8_t
    {
        IDSearchOptions_ChildrenOnly = 1 << 0, // Don't search upwards through the tree
        IDSearchOptions_ParentsOnly = 1 << 1,  // Don't search downwards through the tree
    };


    struct TextContext : public std::enable_shared_from_this<TextContext>
    {
        TSRange range;
        std::weak_ptr<TextContext> parent;

        virtual ~TextContext() = default;
        virtual std::optional<DocumentContextNode> getNodeAtChar(TSPoint pos);
        virtual std::optional<DocumentContextNode> findIdentifier(std::string_view identifier);
        virtual std::optional<DocumentContextNode> findIdentifier(std::string_view identifier, uint8_t searchOptions);
        virtual std::string longId() const;

        template<typename T>
        Node<T> as()
        {
            static_assert(std::is_base_of<TextContext, T>::value, "T must be a subclass of DocumentContext");
            auto* r = std::dynamic_pointer_cast<T>(shared_from_this());
            return r;
        }

        template<typename T>
        Node<T> as() const
        {
            static_assert(std::is_base_of<TextContext, T>::value, "T must be a subclass of DocumentContext");
            auto* r = std::dynamic_pointer_cast<T>(shared_from_this());
            return r;
        }

        template<typename T>
        bool is()
        {
            return std::dynamic_pointer_cast<T>(shared_from_this());
        }

        template<typename T>
        Node<T> getParent() const
        {
            if(auto p = parent.lock())
            {
                auto pt = p->as<T>();
                if(pt)
                    return pt;
                return p->getParent<T>();
            }
            return nullptr;
        }
        template<typename T>
        Node<T> getLast()
        {
            auto o = as<T>();
            if(o)
                return o;
            return getParent<T>();
        }

        template<typename T>
        Node<T> getLast() const
        {
            auto o = as<T>();
            if(o)
                return o;
            return getParent<T>();
        }

    };

    struct ValueContext: public TextContext
    {
        //What data does this value store
        std::optional<Identifier> label;
        TypeContext type;

        // Is stored on the heap or the stack, instead of being a temporary value holder
        bool isLValue = false;

        /*bool operator==(const ValueContext& o) const;*/
        /*bool operator!=(const ValueContext& o) const;*/
        /**/
        /*// SameBaseType compares everything but isConst and isLValue*/
        /*bool sameBaseType(const ValueContext& o) const;*/
        /**/
        /*uint32_t castCost(const ValueContext& target) const;*/

        ValueContext() = default;
        /*ValueContext(TypeContext type, bool isLValue, bool isConst, bool isRef);*/
        /*ValueContext(std::string label, TypeContext type, bool isLValue, bool isConst, bool isRef);*/
        /**/
        virtual std::string signature() const;
        std::string longId() const override;
    };

    struct TemplateDefArgumentContext
    {
        std::string identifier;
        enum ArgType {
            Typedef,
            TypedefPack,
            Value
        } type = Typedef;
        TypeContext valueType;
    };

    struct ConstValueContext;
    struct TemplateArgContext
    {
        std::string identifier;
        std::variant<ValueContext, std::vector<ValueContext>, Node<ConstValueContext>> value;
    };

    struct ErrorContext
    {
        std::string message;
        size_t line = 0;
    };

    struct ExpressionContext : public TextContext
    {
        ValueContext returnType;
        // Is the result of this expression a constant?
        virtual bool isConstexpr() const = 0;
    };

    struct ExpressionErrorContext;
    struct ScopeContext;
    struct UnaryOperatorContext;
    struct BinaryOperatorContext;

    using ExpressionContextNode = std::variant<
Node<ExpressionErrorContext>,
Node<ScopeContext>,
Node<UnaryOperatorContext>,
Node<BinaryOperatorContext>
>;

    struct AsyncExpressionContext : public TextContext
    {
        
    };

    struct ExpressionErrorContext : public ExpressionContext, ErrorContext
    {
        inline ExpressionErrorContext(std::string message, size_t line)
        {
            this->message = std::move(message);
            this->line = line;
        }
        bool isConstexpr() const override;
    };

    struct ScopeContext : public ExpressionContext
    {
        // This must be a list so that we can keep construction/destruction order consistent
        std::vector<Node<ValueContext>> localVariables;
        std::vector<ExpressionContextNode> expressions;

        virtual std::optional<DocumentContextNode> findIdentifier(std::string_view identifier, uint8_t searchOptions);

        bool isConstexpr() const override;
    };

    struct PipelineStageContext : public TextContext
    {
        std::vector<Node<ValueContext>> localVariables;
        std::vector<ExpressionContextNode> expressions;            
        std::vector<Node<AsyncExpressionContext>> asyncExpressions;
    };

    struct IfContext : public ExpressionContext
    {
        Node<ScopeContext> branchScope;
        ExpressionContextNode condition;
        ExpressionContextNode body;
        ExpressionContextNode elseBody;
        bool isConstexpr() const override;
    };

    struct WhileContext : public ExpressionContext
    {
        Node<ScopeContext> loopScope;
        ExpressionContextNode condition;
        ExpressionContextNode body;
        bool isConstexpr() const override;
    };

    struct ForContext : public ExpressionContext
    {
        Node<ScopeContext> loopScope;
        ExpressionContextNode init;
        ExpressionContextNode condition;
        ExpressionContextNode step;
        ExpressionContextNode body;
        bool isConstexpr() const override;
    };

    struct AssignmentContext : public ExpressionContext
    {
        ExpressionContextNode lValue;
        ExpressionContextNode rValue;
        bool isConstexpr() const override;

        AssignmentContext() = default;
        AssignmentContext(ExpressionContext* lValue, ExpressionContext* rValue);
        void setArgs(ExpressionContext* lValue, ExpressionContext* rValue);
    };

    struct ConstValueContext : public ExpressionContext
    {
        std::variant<bool, char, int64_t, uint64_t, double, std::string> value;
        virtual std::string toString() const = 0;
        bool isConstexpr() const override;
    };

    struct LabeledValueReferenceContext : public ExpressionContext
    {
        std::string identifier;
        LabeledValueReferenceContext(const ValueContext& value);

        bool isConstexpr() const override;
    };

    struct MemberAccessContext : public ExpressionContext
    {
        ExpressionContextNode baseExpression;
        size_t member = -1;
        MemberAccessContext() = default;
        MemberAccessContext(ExpressionContext* base, StructContext* baseType, size_t member);

        bool isConstexpr() const override;
    };

    struct CreateReferenceContext : public ExpressionContext
    {
        ExpressionContextNode _source;
        CreateReferenceContext(ExpressionContext* source);

        bool isConstexpr() const override;
    };

    struct DereferenceContext : public ExpressionContext
    {
        ExpressionContextNode _source;
        DereferenceContext(ExpressionContext* source);

        bool isConstexpr() const override;
    };

    /*struct FunctionCallContext : public ExpressionContext*/
    /*{*/
    /*    FunctionContext* function = nullptr;*/
    /*    ExpressionContextNode functionRef;*/
    /*    std::vector<ExpressionContextNode> arguments;*/
    /**/
    /*    bool isConstexpr() const override;*/
    /*};*/

    struct FunctionDescriptionContext : public TextContext
    {
        Identifier identifier;
        LabeledNodeList<ValueContext> sources;
        LabeledNodeList<ValueContext> sinks;
        std::string longId() const override;
    };

    struct FunctionContext : public TextContext
    {
        FunctionDescriptionContext description;

        Node<ScopeContext> body;

        std::optional<DocumentContextNode> findIdentifier(std::string_view identifier, uint8_t searchOptions) override;
        std::string longId() const override;
        std::string signature() const;
    };

    struct ImplContext: public TextContext 
    {
        TypeContext type;
        LabeledNodeMap<FunctionContext> methods;
        std::string longId() const override;
    };

    struct TraitContext : public TextContext
    {
        Identifier identifier;  
        LabeledNodeList<FunctionDescriptionContext> methods;       
        std::string longId() const override;
    };

    struct TraitImplContext: public ImplContext
    {
        Identifier trait;
        TypeContext type;
        std::string longId() const override;
    };

    struct PipelineContext : public TextContext
    {
        Identifier identifier;
        // Arguments
        LabeledNodeList<ValueContext> sources;
        LabeledNodeList<ValueContext> sinks;

        LabeledNodeList<PipelineStageContext> stages;

        std::optional<DocumentContextNode> findIdentifier(std::string_view identifier, uint8_t searchOptions) override;
        std::string longId() const override;
        std::string argSig() const;
        std::string signature() const;
    };


    struct StructContext : public TextContext
    {
        Identifier identifier;

        LabeledNodeList<ValueContext> variables;
        LabeledNodeList<FunctionContext> functions;
        bool packed = false;

        std::optional<DocumentContextNode> getNodeAtChar(TSPoint pos) override;
        std::optional<DocumentContextNode> findIdentifier(std::string_view identifier, uint8_t searchOptions) override;
        std::string longId() const override;
    };

    struct ModuleContext : public TextContext
    {
        Identifier identifier;
        LabeledNodeList<StructContext> structs;
        LabeledNodeList<FunctionContext> functions;

        std::optional<DocumentContextNode> getNodeAtChar(TSPoint pos) override;
        std::optional<DocumentContextNode> findIdentifier(std::string_view identifier, uint8_t searchOptions) override;
        std::string longId() const override;
    };

    struct DocumentContext : public TextContext
    {
        std::filesystem::path source;
        LabeledNodeMap<ModuleContext> modules;

        std::optional<DocumentContextNode> getNodeAtChar(TSPoint pos) override;
        std::optional<DocumentContextNode> findIdentifier(std::string_view identifier, uint8_t searchOptions) override;
    };
}

#endif

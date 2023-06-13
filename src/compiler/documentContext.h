//
// Created by wirewhiz on 1/23/23.
//

#ifndef BRANESCRIPT_FUNCTIONCONTEXT_H
#define BRANESCRIPT_FUNCTIONCONTEXT_H

#include <cstdarg>
#include <filesystem>
#include <list>
#include <ParserRuleContext.h>
#include <string>
#include <vector>
#include "robin_hood.h"
#include "src/scriptRuntime/valueIndex.h"
#include "structDef.h"
#include "textPos.h"
#include <json/json.h>
#include <llvm/IR/PassManager.h>

#include "irScript.h"
#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

namespace antlr4
{
    class TokenStream;
}

namespace llvm
{
    class Value;
    class Module;
}

namespace BraneScript
{
    class Analyzer;
    struct FunctionContext;
    struct StructContext;
    class TypeDef;
    class StructDef;

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
        StructContext* structCtx = nullptr;

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
        size_t arraySize = 0;

        bool operator==(const ValueContext& o) const;
        bool operator!=(const ValueContext& o) const;

        // SameBaseType compares everything but isConst and isLValue
        bool sameBaseType(const ValueContext& o) const;

        uint32_t castCost(const ValueContext& target) const;

        ValueContext& operator=(const LabeledValueContext& o);
        ValueContext() = default;
        ValueContext(TypeContext type, bool isLValue, bool isConst, bool isRef);
        ValueContext(const LabeledValueContext& o);



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
            Value
        } type = Typedef;
        TypeContext valueType;
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
    struct ValueArgContext : public TemplateArgContext
    {
        std::unique_ptr<ConstValueContext> value;
    };

    struct ScriptContext;
    struct StatementContext;

    enum CompileFlags : uint8_t
    {
        CompileFlags_None        = 0,
        CompileFlags_Optimize    = 1 << 0,
        CompileFlags_DebugInfo   = 1 << 1,
        CompileFlags_PrintIR     = 1 << 2,
    };

    struct ASTContext
    {
        llvm::LLVMContext* llvmCtx;
        llvm::IRBuilder<> builder;
        std::unique_ptr<llvm::Module> module;

        std::unique_ptr<llvm::DIBuilder> dBuilder;
        llvm::DICompileUnit* diCompileUnit = nullptr;
        llvm::DIFile* diFile = nullptr;

        uint8_t flags = CompileFlags_None;

        std::unique_ptr<llvm::FunctionAnalysisManager> fam;
        std::unique_ptr<llvm::ModuleAnalysisManager> mam;
        std::unique_ptr<llvm::ModulePassManager> mpm;
        std::unique_ptr<llvm::FunctionPassManager> fpm;

        llvm::Function* func = nullptr;
        llvm::BasicBlock* currentBlock = nullptr;

        llvm::DISubprogram* diFunction = nullptr;

        struct StructEntry
        {
            IRStructDef def;
            llvm::StructType* llvmType = nullptr;
            bool exported = false;
        };

        robin_hood::unordered_map<std::string, StructEntry> definedStructs;

        robin_hood::unordered_map<std::string, llvm::Constant*> globals;
        robin_hood::unordered_map<std::string, llvm::Function*> functions;
        std::vector<IRFunction> exportedFunctions;
        std::vector<IRGlobal> exportedGlobals;

        robin_hood::unordered_set<std::string> linkedModules;


        robin_hood::unordered_map<std::string, llvm::DIType*> debugTypes;
        robin_hood::unordered_map<std::string, llvm::DISubprogram*> debugSubprograms;

        struct Scope
        {
            struct ScopeEntry
            {
                llvm::Value* value;
                ValueContext context;
            };
            robin_hood::unordered_map<std::string, ScopeEntry> values;
            std::vector<ScopeEntry> unnamedValues;
            llvm::DIScope* debugScope = nullptr;
        };
        std::list<Scope> scopes;

        void pushScope();
        void popScope();

        void setDebugScope(llvm::DIScope* scope);
        llvm::DIScope* debugScope() const;
        void setDebugLocation(const StatementContext* ctx);

        void addValue(std::string id, llvm::Value* value, ValueContext context);
        void addValue(llvm::Value* value, ValueContext context);
        llvm::Value* findValue(const std::string& id);
        //Very rare usage, only for function arguments at the moment
        bool setValue(llvm::Value* old, llvm::Value* newValue);

        ASTContext(llvm::LLVMContext* llvmCtx, std::string moduleSource);
        llvm::Type* getLLVMType(const ValueContext& valueCtx);
        llvm::DIType* getDebugType(ValueContext valueCtx);
        llvm::StructType* getStructDef(const StructContext* structCtx);

        std::function<llvm::GlobalVariable*()> makeGlobalVariable(LabeledValueContext& valueContext, bool shouldExport);
        std::function<llvm::GlobalVariable*()> makeExternGlobalVariable(LabeledValueContext& valueContext);

        void setInsertPoint(llvm::BasicBlock* block);

        void destructStack(bool onlyLocal = false);

        void printModule() const;
        static size_t pointerDepth(llvm::Type* type);
        llvm::Value* dereferenceToDepth(llvm::Value* value, size_t maxPointerDepth);

        ~ASTContext();
    };

    // Not yet implemented
    enum IDSearchOptions : uint8_t
    {
        IDSearchOptions_ChildrenOnly = 1 << 0, // Don't search upwards through the tree
        IDSearchOptions_ParentsOnly = 1 << 1,  // Don't search downwards through the tree
    };

    struct FunctionOverridesContext;
    struct DocumentContext
    {
        TextRange range;
        DocumentContext* parent = nullptr;
        uint16_t version = 0;

        virtual ~DocumentContext() = default;
        virtual DocumentContext* getNodeAtChar(TextPos pos);
        DocumentContext* findIdentifier(const std::string& identifier);
        void getFunction(const std::string& identifier, FunctionOverridesContext* overrides);
        virtual DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions);
        virtual void  getFunction(const std::string& identifier, FunctionOverridesContext* overrides, uint8_t searchOptions);
        virtual std::string longId() const;

        template<typename T>
        T* as()
        {
            static_assert(std::is_base_of<DocumentContext, T>::value, "T must be a subclass of DocumentContext");
            auto* r = dynamic_cast<T*>(this);
            return r;
        }

        template<typename T>
        T* as() const
        {
            static_assert(std::is_base_of<DocumentContext, T>::value, "T must be a subclass of DocumentContext");
            auto* r = dynamic_cast<T*>(this);
            return r;
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
        template<typename T>
        T* getLast()
        {
            auto o = this->as<T>();
            if(o)
                return o;
            return getParent<T>();
        }

        template<typename T>
        T* getLast() const
        {
            auto o = this->as<T>();
            if(o)
                return o;
            return getParent<T>();
        }

        /** Creates a deep copy of this node and it's children
         * @param callback called each time a node is copied, said node is passed to the callback.
         * This is intended to allow for modification of nodes
         */
        virtual llvm::Value* createAST(ASTContext& ctx) const = 0;

         DocumentContext* deepCopy() const;
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
        llvm::Value* createAST(ASTContext& ctx) const override;
        LabeledValueContext(std::string identifier, ValueContext value);
    };


    struct ArgPackInstanceContext : public DocumentContext
    {
        std::string identifier;
        std::vector<LabeledValueContext*> values;

        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
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
        llvm::Value* createAST(ASTContext& ctx) const override;
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
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
        bool isConstexpr() const override;
    };

    struct ScopeContext : public StatementContext
    {
        // This must be a list so that we can keep construction/destruction order consistent
        std::vector<std::unique_ptr<LabeledValueContext>> localVariables;
        std::vector<std::unique_ptr<StatementContext>> expressions;

        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;

        void beginScope(ASTContext& ctx) const;
        void endScope(ASTContext& ctx) const;

        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
        bool isConstexpr() const override;
    };

    struct ReturnContext : public StatementContext
    {
        std::unique_ptr<ExpressionContext> value;

        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
        bool isConstexpr() const override;
    };

    struct IfContext : public StatementContext
    {
        std::unique_ptr<ScopeContext> branchScope;
        std::unique_ptr<ExpressionContext> condition;
        std::unique_ptr<StatementContext> body;
        std::unique_ptr<StatementContext> elseBody;
        bool isConstexpr() const override;

        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct WhileContext : public StatementContext
    {
        std::unique_ptr<ScopeContext> loopScope;
        std::unique_ptr<ExpressionContext> condition;
        std::unique_ptr<StatementContext> body;
        bool isConstexpr() const override;

        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ForContext : public StatementContext
    {
        std::unique_ptr<ScopeContext> loopScope;
        std::unique_ptr<StatementContext> init;
        std::unique_ptr<ExpressionContext> condition;
        std::unique_ptr<StatementContext> step;
        std::unique_ptr<StatementContext> body;
        bool isConstexpr() const override;

        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct AssignmentContext : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> lValue;
        std::unique_ptr<ExpressionContext> rValue;
        bool isConstexpr() const override;

        AssignmentContext() = default;
        AssignmentContext(ExpressionContext* lValue, ExpressionContext* rValue);
        void setArgs(ExpressionContext* lValue, ExpressionContext* rValue);
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct RefAssignmentContext : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> lValue;
        std::unique_ptr<ExpressionContext> rValue;
        bool isConstexpr() const override;

        RefAssignmentContext() = default;
        RefAssignmentContext(ExpressionContext* lValue, ExpressionContext* rValue);
        void setArgs(ExpressionContext* lValue, ExpressionContext* rValue);
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct TypeSizeContext : public ExpressionContext
    {
        ValueContext value;

        TypeSizeContext(ValueContext);
        llvm::Value* createAST(ASTContext& ctx) const override;

        bool isConstexpr() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;

    };

    struct ConstValueContext : public ExpressionContext
    {
        virtual std::string toString() const = 0;
        bool isConstexpr() const override;
    };

    struct ConstBoolContext : public ConstValueContext
    {
        bool value;
        ConstBoolContext();
        ConstBoolContext(bool value);
        std::string toString() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ConstCharContext : public ConstValueContext
    {
        char value;
        ConstCharContext();
        ConstCharContext(char value);
        std::string toString() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ConstIntContext : public ConstValueContext
    {
        int value;
        ConstIntContext();
        ConstIntContext(int value);
        std::string toString() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ConstFloatContext : public ConstValueContext
    {
        float value;
        ConstFloatContext();
        ConstFloatContext(float value);
        std::string toString() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ConstStringContext : public ConstValueContext
    {
        std::string value;
        ConstStringContext();
        ConstStringContext(std::string value);
        std::string toString() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct LabeledValueConstructionContext : public ExpressionContext
    {
        std::string identifier;
        LabeledValueConstructionContext(const LabeledValueContext& value);
        LabeledValueConstructionContext() = default;

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct LabeledValueDestructionContext : public ExpressionContext
    {
        std::string identifier;
        LabeledValueDestructionContext(const LabeledValueContext& value);
        LabeledValueDestructionContext() = default;

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct LabeledValueReferenceContext : public ExpressionContext
    {
        std::string identifier;
        LabeledValueReferenceContext(const LabeledValueContext& value);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct TemplateArgs
    {
        enum class Type
        {
            Value,
            Typedef
        };

        struct Arg
        {
            ValueContext typeDef;
            std::unique_ptr<ConstValueContext> value;
            Type type;

            Arg(ValueContext arg) : typeDef(std::move(arg)), type(Type::Typedef) {}

            Arg(ConstValueContext* arg) : value(arg), type(Type::Value) {}

            Arg(const Arg& o)
            {
                typeDef = o.typeDef;
                if(o.value)
                    value.reset((ConstValueContext*)o.value->deepCopy([](auto _) { return _; }));
                type = o.type;
            }

            Arg(Arg&& o)
            {
                typeDef = std::move(o.typeDef);
                value = std::move(o.value);
                type = o.type;
            }
        };

        std::vector<Arg> args;

        void addArg(ValueContext typeDef)
        {
            assert(typeDef.type.storageType != ValueType::Struct || typeDef.type.structCtx);
            args.emplace_back(std::move(typeDef));
        }

        void addArg(ConstValueContext* value) { args.emplace_back(value); }
    };

    struct TemplateHandle : public DocumentContext
    {
        Identifier identifier;
        enum Type
        {
            Function,
            Struct
        } type;

        antlr4::ParserRuleContext* root;
        std::vector<std::unique_ptr<TemplateDefArgumentContext>> args;

        TemplateHandle(Type type,
                       antlr4::ParserRuleContext* root,
                       DocumentContext* parent,
                       const std::vector<TemplateDefArgumentContext*>& args);

        llvm::Value* createAST(ASTContext& ctx) const override;
        std::string longId() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct FunctionOverridesContext : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> thisRef;
        std::vector<FunctionContext*> overrides;
        std::vector<TemplateHandle*> templates;
        TemplateArgs templateArgs;


        enum MatchFlags
        {
            None = 0,
            Constexpr = 1
        };
        // CastCallback is called to check if an implicit cast is possible
        using CastCallback = std::function<bool(const ValueContext& from, const ValueContext& to)>;

        std::string longId() const override;

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;

    };

    struct FunctionReferenceContext : public ExpressionContext
    {
        FunctionContext* function;
        explicit FunctionReferenceContext(FunctionContext* function);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;

        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct MemberAccessContext : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> baseExpression;
        size_t member = -1;
        MemberAccessContext() = default;
        MemberAccessContext(ExpressionContext* base, StructContext* baseType, size_t member);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct CreateReferenceContext : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> _source;
        CreateReferenceContext(ExpressionContext* source);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct DereferenceContext : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> _source;
        DereferenceContext(ExpressionContext* source);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct NativeCastContext : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> sourceExpr;

        NativeCastContext(ValueContext targetType, ExpressionContext* source);
        static bool validCast(const ValueContext& from, const ValueContext& to);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct NativeArithmeticContext : public ExpressionContext
    {
        enum Operation
        {
            ADD,
            SUB,
            MUL,
            DIV
        } op;

        std::unique_ptr<ExpressionContext> lValue;
        std::unique_ptr<ExpressionContext> rValue;

        static bool validArithmetic(const ValueContext& left, const ValueContext& right);
        NativeArithmeticContext(Operation op, ExpressionContext* lValue, ExpressionContext* rValue);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct NativeNegateContext : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> value;

        NativeNegateContext(ExpressionContext* value);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;

        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct NativeIncrementContext : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> value;
        bool isPrefix;

        NativeIncrementContext(ExpressionContext* value, bool isPrefix);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;

        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct NativeDecrementContext : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> value;
        bool isPrefix;

        NativeDecrementContext(ExpressionContext* value, bool isPrefix);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;

        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct NativeNotContext  : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> value;

        NativeNotContext(ExpressionContext* value);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct NativeLogicContext : public ExpressionContext
    {
        enum Operation
        {
            AND,
            OR
        } op;

        std::unique_ptr<ExpressionContext> lValue;
        std::unique_ptr<ExpressionContext> rValue;

        NativeLogicContext(Operation op, ExpressionContext* lValue, ExpressionContext* rValue);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct NativeCompareContext : public ExpressionContext
    {
        enum Operation
        {
            EQ,
            NEQ,
            GT,
            GE,
            LT,
            LE
        } op;

        std::unique_ptr<ExpressionContext> lValue;
        std::unique_ptr<ExpressionContext> rValue;

        static bool validCompare(const ValueContext& left, const ValueContext& right);
        NativeCompareContext(Operation op, ExpressionContext* lValue, ExpressionContext* rValue);

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct FunctionCallContext : public ExpressionContext
    {
        FunctionContext* function = nullptr;
        std::unique_ptr<ExpressionContext> functionRef;
        std::vector<std::unique_ptr<ExpressionContext>> arguments;

        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct NativeIndexOperator : public ExpressionContext
    {
        std::unique_ptr<ExpressionContext> source;
        std::unique_ptr<ExpressionContext> index;

        NativeIndexOperator(ExpressionContext* source, ExpressionContext* index);
        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct LambdaInstanceContext : public ExpressionContext
    {
        StructContext* lambdaType = nullptr;
        StructContext* captureType = nullptr;
        std::vector<std::unique_ptr<ExpressionContext>> captures;
        FunctionContext* func = nullptr;
        FunctionContext* allocFunc = nullptr;
        FunctionContext* copyFunc = nullptr;

        DocumentContext* findIdentifier(const std::string &identifier, uint8_t searchOptions) override;
        bool isConstexpr() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct FunctionContext : public DocumentContext
    {
        Identifier identifier;
        std::vector<std::string> tags;
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

        bool isTemplateInstance = false;

        std::unique_ptr<ScopeContext> body;

        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        std::string longId() const override;
        std::string argSig() const;
        std::string signature() const;

        llvm::Value* createAST(ASTContext& ctx) const override;
        void registerFunction(ASTContext& ctx, bool isLinked) const;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct StructContext : public DocumentContext
    {
        Identifier identifier;
        std::vector<std::string> tags;

        LabeledNodeList<LabeledValueContext> variables;
        LabeledNodeList<FunctionContext> functions;
        LabeledNodeMap<TemplateHandle> templates;
        bool packed = false;

        FunctionContext* constructor = nullptr;
        FunctionContext* destructor = nullptr;
        FunctionContext* copyConstructor = nullptr;
        FunctionContext* moveConstructor = nullptr;

        DocumentContext* getNodeAtChar(TextPos pos) override;
        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        void getFunction(const std::string& identifier, FunctionOverridesContext* overrides,
                         uint8_t searchOptions) override;
        std::string longId() const override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ModuleContext;
    struct LinkContext : public DocumentContext
    {
        std::string moduleName;
        // If alias is empty, that means that the library is imported without a prefix (like a using namespace)
        std::string alias;
        bool isPublic = false;

        ModuleContext* module = nullptr;
        llvm::Value* createAST(ASTContext& ctx) const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ModuleContext : public DocumentContext
    {
        Identifier identifier;
        std::vector<std::string> tags;
        LabeledNodeList<LabeledValueContext> globals;
        LabeledNodeList<StructContext> structs;
        LabeledNodeList<FunctionContext> functions;
        LabeledNodeMap<LinkContext> links;
        LabeledNodeMap<TemplateHandle> templates;

        DocumentContext* getNodeAtChar(TextPos pos) override;
        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        void getFunction(const std::string& identifier, FunctionOverridesContext* overrides,
                         uint8_t searchOptions) override;
        llvm::Value* createAST(ASTContext& ctx) const override;
        IRModule compile(llvm::LLVMContext* ctx, uint8_t flags = CompileFlags_Optimize) const;
        std::string longId() const override;
        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };

    struct ScriptContext : public DocumentContext
    {
        std::filesystem::path source;
        LabeledNodeMap<ModuleContext> modules;

        DocumentContext* getNodeAtChar(TextPos pos) override;
        DocumentContext* findIdentifier(const std::string& identifier, uint8_t searchOptions) override;
        void getFunction(const std::string& identifier, FunctionOverridesContext* overrides,
                         uint8_t searchOptions) override;

        llvm::Value* createAST(ASTContext& ctx) const override;

        IRScript compile(llvm::LLVMContext* ctx, uint8_t flags);

        DocumentContext* deepCopy(const std::function<DocumentContext*(DocumentContext*)>& callback) const override;
    };
} // namespace BraneScript

#endif // BRANESCRIPT_FUNCTIONCONTEXT_H

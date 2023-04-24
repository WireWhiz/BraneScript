//
// Created by wirewhiz on 4/19/23.
//

#include "constexprEvaluator.h"
#include "linker.h"

namespace BraneScript
{

    robin_hood::unordered_map<std::string, std::unique_ptr<ConstexprFunction>> ConstexprEvaluator::_inlineFunctions;

    struct Value
    {
        std::string identifier;
        std::unique_ptr<ConstValueContext> value;
        Value() = default;
        Value(std::string identifier, std::unique_ptr<ConstValueContext> value) : identifier(std::move(identifier)), value(std::move(value)){};
        Value(const Value& o)
        {
            identifier = o.identifier;
            value.reset((ConstValueContext*)o.value->deepCopy());
        }
        Value(Value&& o) noexcept
        {
            identifier = std::move(o.identifier);
            value = std::move(o.value);
        }
        Value& operator=(Value&& o) noexcept
        {
            identifier = std::move(o.identifier);
            value = std::move(o.value);
            return *this;
        }
        Value& operator=(const Value& o) noexcept
        {
            identifier = o.identifier;
            value.reset((ConstValueContext*)o.value->deepCopy());
            return *this;
        }
        bool empty() const { return value == nullptr; }
    };

    class ConstexprFunction
    {
      public:
        virtual ~ConstexprFunction() = default;
        std::string identifier;
        virtual Value evaluate(const std::vector<Value>& args) const = 0;
    };

#define ConstructConstexprBinaryOperator(className, symbol)                                 \
    template<typename T, typename RetT = T>                                                 \
    class className : public ConstexprFunction                                              \
    {                                                                                       \
      public:                                                                               \
        explicit className(const std::string& typeName)                                     \
        {                                                                                   \
            identifier = "BraneScript::opr " #symbol "(" + std::string(typeName) + ","  + typeName + ")";\
        }                                                                                   \
        Value evaluate(const std::vector<Value>& args) const override               \
        {                                                                                   \
             static_assert(std::is_base_of<ConstValueContext, T>());                        \
             assert(args.size() == 2);                                                      \
             T* lvalue = dynamic_cast<T*>(args[0].value.get());                             \
             T* rvalue = dynamic_cast<T*>(args[1].value.get());                             \
             assert(lvalue && rvalue);                                                      \
             return Value("", std::make_unique<RetT>(lvalue->value symbol rvalue->value));  \
        }                                                                                   \
    };

    ConstructConstexprBinaryOperator(ConstexprAdd, +)
    ConstructConstexprBinaryOperator(ConstexprSub, -)
    ConstructConstexprBinaryOperator(ConstexprMul, *)
    ConstructConstexprBinaryOperator(ConstexprDiv, /)

    ConstructConstexprBinaryOperator(ConstexprEq, ==)
    ConstructConstexprBinaryOperator(ConstexprNotEq, !=)
    ConstructConstexprBinaryOperator(ConstexprLess, <)
    ConstructConstexprBinaryOperator(ConstexprLessEq, <=)
    ConstructConstexprBinaryOperator(ConstexprGreater, >)
    ConstructConstexprBinaryOperator(ConstexprGreaterEq, >=)

    template<typename From, typename To>
    class ConstexprCast : public ConstexprFunction
    {
      public:
        ConstexprCast(const std::string& from, const std::string& to)
        {
            identifier = "BraneScript::opr " + to + "(" + from + ")";
        }
        Value evaluate(const std::vector<Value>& args) const override
        {
            static_assert(std::is_base_of<ConstValueContext, From>());
            static_assert(std::is_base_of<ConstValueContext, To>());
            assert(args.size() == 1);
            auto value = dynamic_cast<From*>(args[0].value.get());
            assert(value);
            return Value("", std::make_unique<To>(value->value));
        }
    };

    class ConstexprEvaluatorWalker
    {
        std::string errorMessage;
        ConstexprEvaluator& _evaluator;

        struct Scope
        {
            robin_hood::unordered_map<std::string, Value> localValues;
        };

        uint32_t recursionDepth = 0;
        std::list<Scope> _scopes;

        Value _returnValue;

        void pushScope() { _scopes.emplace_back(); }

        void popScope() { _scopes.pop_back(); }

        Scope& currentScope() { return _scopes.back(); }

        Value getVar(const std::string& identifier)
        {
            for(auto i = _scopes.rbegin(); i != _scopes.rend(); ++i)
            {
                auto v = i->localValues.find(identifier);
                if(v != i->localValues.end())
                    return v->second;
            }
            assert(false);
        }

        void setVar(const std::string& identifier, std::unique_ptr<ConstValueContext> value)
        {
            for(auto i = _scopes.rbegin(); i != _scopes.rend(); ++i)
            {
                auto v = i->localValues.find(identifier);
                if(v != i->localValues.end())
                {
                    v->second.value = std::move(value);
                    break;
                }
            }
            assert(false);
        }

        Value visitConst(const ConstValueContext* ctx)
        {
            return {"", std::unique_ptr<ConstValueContext>((ConstValueContext*)ctx->deepCopy())};
        }

        Value visitDeclaration(const LabeledValueConstructionContext* ctx)
        {
            currentScope().localValues.insert({ctx->identifier, Value{ctx->identifier, nullptr}});
            return currentScope().localValues.at(ctx->identifier);
        }

        Value visitFunctionCall(const FunctionCallContext* ctx)
        {
            const uint32_t maxRecursionDepth = 1000000;
            if(++recursionDepth == maxRecursionDepth)
                throw std::runtime_error("Max constexpr recursion depth reached!");
            std::vector<Value> args;
            for(auto& arg : ctx->arguments)
                args.push_back(visitExpression(arg.get()));

            if(const ConstexprFunction* inlineFunc = _evaluator.getInlineFunction(ctx->function->signature()))
                return inlineFunc->evaluate(args);

            if(ctx->function->body)
            {
                pushScope();
                for(int i = 0; i < args.size(); ++i)
                {
                    std::string& id = ctx->function->arguments[i]->identifier;
                    _scopes.back().localValues.insert({id, Value(id, std::move(args[i].value))});
                }

                visitStatement(ctx->function->body.get());

                popScope();
            }
            else
                assert(false); //TODO allow for extern constexpr functions

            --recursionDepth;
            assert(!_returnValue.empty());
            Value returnValue = std::move(_returnValue);
            assert(_returnValue.empty());
            return returnValue;
        }

        Value visitValueAccess(const LabeledValueReferenceContext* ctx)
        {
            return getVar(ctx->identifier);
        }

        Value visitExpression(const ExpressionContext* ctx)
        {
            assert(ctx);
            if(auto* node = dynamic_cast<const ConstValueContext*>(ctx))
                return visitConst(node);
            if(auto* node = dynamic_cast<const LabeledValueConstructionContext*>(ctx))
                return visitDeclaration(node);
            if(auto* node = dynamic_cast<const FunctionCallContext*>(ctx))
                return visitFunctionCall(node);
            if(auto* node = dynamic_cast<const LabeledValueReferenceContext*>(ctx))
                return visitValueAccess(node);
            if(auto error = dynamic_cast<const ExpressionErrorContext*>(ctx))
                throw std::runtime_error("Document with expression error node cannot be compiled (error: " +
                                         error->message + ". line: " + std::to_string(error->line) + ")");
            assert(false);
            return {};
        }

        Value visitAssignment(const AssignmentContext* ctx)
        {
            Value newValue = visitExpression(ctx->lValue.get());
            setVar(newValue.identifier, std::move(newValue.value));
            return newValue;
        }

        void visitReturn(const ReturnContext* ctx)
        {
            _returnValue = visitExpression(ctx->value.get());
        }

        bool checkConditionExpr(ExpressionContext* ctx)
        {
            Value condition = visitExpression(ctx);
            auto* conditionBool = dynamic_cast<ConstBoolContext*>(condition.value.get());
            assert(conditionBool);
            return conditionBool->value;
        }

        void visitIf(const IfContext* ctx)
        {
            if(checkConditionExpr(ctx->condition.get()))
                visitStatement(ctx->body.get());
            else if(ctx->elseBody)
                visitStatement(ctx->elseBody.get());
        }

        void visitWhile(const WhileContext* ctx)
        {
            const uint32_t maxIterations = 10000000;

            uint32_t i = 0;
            while(checkConditionExpr(ctx->condition.get()) && i < maxIterations)
            {
                visitStatement(ctx->body.get());
                if(!_returnValue.empty())
                    break;
                i++;
            }
        }

        void visitScope(const ScopeContext* ctx)
        {
            pushScope();
            for(auto& stmt : ctx->statements)
            {
                visitStatement(stmt.get());
                if(!_returnValue.empty())
                    break;
            }
            popScope();
        }

        void visitStatement(const StatementContext* ctx)
        {
            assert(ctx);
            if(auto expr = dynamic_cast<const ExpressionContext*>(ctx))
                visitExpression(expr);
            if(auto scopeStmt = dynamic_cast<const ScopeContext*>(ctx))
                visitScope(scopeStmt);
            if(auto assignment = dynamic_cast<const AssignmentContext*>(ctx))
                visitAssignment(assignment);
            if(auto ret = dynamic_cast<const ReturnContext*>(ctx))
                visitReturn(ret);
            if(auto ifStmt = dynamic_cast<const IfContext*>(ctx))
                visitIf(ifStmt);
            if(auto whileStmt = dynamic_cast<const WhileContext*>(ctx))
                visitWhile(whileStmt);
            if(auto error = dynamic_cast<const StatementErrorContext*>(ctx))
                throw std::runtime_error("Document with statement error node cannot be compiled (error: " +
                                         error->message + ". line: " + std::to_string(error->line) + ")");
        }

      public:
        ConstexprEvaluatorWalker(ConstexprEvaluator& evaluator) : _evaluator(evaluator)
        {

        }
        ConstValueContext* evaluate(const ExpressionContext* expr)
        {
            return visitExpression(expr).value.release();
        }
    };

    template<int index, typename T, typename... Args>
    void addScalarOperators(ConstexprEvaluator& evaluator, const std::vector<std::string>& typenames)
    {
        evaluator.addInlineFunction(new ConstexprAdd<T>(typenames[index]));
        evaluator.addInlineFunction(new ConstexprSub<T>(typenames[index]));
        evaluator.addInlineFunction(new ConstexprMul<T>(typenames[index]));
        evaluator.addInlineFunction(new ConstexprDiv<T>(typenames[index]));

        evaluator.addInlineFunction(new ConstexprEq<T, ConstBoolContext>(typenames[index]));
        evaluator.addInlineFunction(new ConstexprNotEq<T, ConstBoolContext>(typenames[index]));
        evaluator.addInlineFunction(new ConstexprGreater<T, ConstBoolContext>(typenames[index]));
        evaluator.addInlineFunction(new ConstexprGreaterEq<T, ConstBoolContext>(typenames[index]));
        evaluator.addInlineFunction(new ConstexprLess<T, ConstBoolContext>(typenames[index]));
        evaluator.addInlineFunction(new ConstexprLessEq<T, ConstBoolContext>(typenames[index]));

        if constexpr(sizeof...(Args) > 0)
            addScalarOperators<index + 1, Args...>(evaluator, typenames);
    }

    ConstexprEvaluator::ConstexprEvaluator()
    {
        _linker = nullptr;
        _runtime = nullptr;

        if(!_inlineFunctions.empty())
            return;
        // Define our native operators as inline functions, to be inserted directly into the Aot tree
        std::vector<std::string> scalarNames = {
            "int",
            "float"
        };

        addScalarOperators<0, ConstIntContext, ConstFloatContext>(*this, scalarNames);

        addInlineFunction(new ConstexprCast<ConstIntContext, ConstFloatContext>("int", "float"));
        addInlineFunction(new ConstexprCast<ConstIntContext, ConstFloatContext>("float", "int"));

        addInlineFunction(new ConstexprCast<ConstIntContext, ConstCharContext>("int", "char"));
        addInlineFunction(new ConstexprCast<ConstCharContext, ConstFloatContext>("char", "int"));

        addInlineFunction(new ConstexprEq<ConstCharContext, ConstBoolContext>("char"));
        addInlineFunction(new ConstexprNotEq<ConstCharContext, ConstBoolContext>("char"));
        addInlineFunction(new ConstexprEq<ConstBoolContext, ConstBoolContext>("bool"));
        addInlineFunction(new ConstexprNotEq<ConstBoolContext, ConstBoolContext>("bool"));
    }

    bool ConstexprEvaluator::isNativeFunction(const std::string& sig) { return _linker->getFunction(sig); }

    AotConstNode* ConstexprEvaluator::evaluateNativeFunction(const std::string& sig,
                                                             const TypeDef* resType,
                                                             std::vector<AotConstNode*>& args,
                                                             ScriptCompilerCtx& scriptCtx)
    {
        assert(resType);
        auto funcContainer = std::make_unique<IRFunction>();
        funcContainer->sig = "constantFuncContainer()";
        funcContainer->returnType.type = resType->name();

        FunctionCompilerCtx compileCtx(scriptCtx, funcContainer->sig);
        compileCtx.function = funcContainer.get();
        std::vector<AotValue*> argValues;
        argValues.reserve(args.size());
        for(auto arg : args)
            argValues.push_back(compileCtx.castReg(arg->generateBytecode(compileCtx)));

        auto retVal = compileCtx.newReg(resType, AotValue::Temp);

        compileCtx.appendCode(Operand::CALL, int16_t(-1));
        compileCtx.appendCode(compileCtx.serialize(retVal));
        for(auto arg : argValues)
            compileCtx.appendCode(compileCtx.serialize(arg));
        compileCtx.appendCode(Operand::RETV, compileCtx.serialize(retVal));

        ScriptAssembleContext assembleContext{};

        assembleContext.linkedFunctions.push_back(_linker->getFunction(sig));

        FunctionData container = _runtime->loadFunction(funcContainer.get(), &assembleContext);

        switch(resType->type())
        {
            case ValueType::Bool:
                return new AotConstNode(FunctionHandle<bool>(container.pointer)());
            case ValueType::Char:
                return new AotConstNode(FunctionHandle<char>(container.pointer)());
            case ValueType::UInt32:
                return new AotConstNode(FunctionHandle<uint32_t>(container.pointer)());
            case ValueType::UInt64:
                return new AotConstNode(FunctionHandle<uint64_t>(container.pointer)());
            case ValueType::Int32:
                return new AotConstNode(FunctionHandle<int32_t>(container.pointer)());
            case ValueType::Int64:
                return new AotConstNode(FunctionHandle<int64_t>(container.pointer)());
            case ValueType::Float32:
                return new AotConstNode(FunctionHandle<float>(container.pointer)());
            case ValueType::Float64:
                return new AotConstNode(FunctionHandle<double>(container.pointer)());
            default:
                assert(false);
                break;
        }
        return nullptr;
    }

    ConstexprFunction* ConstexprEvaluator::getInlineFunction(const std::string& sig)
    {
        if(!_inlineFunctions.contains(sig))
            return nullptr;
        return _inlineFunctions.at(sig).get();
    }

    void ConstexprEvaluator::addInlineFunction(ConstexprFunction* func)
    {
        _inlineFunctions.emplace(func->identifier, func);
    }

    ConstValueContext* ConstexprEvaluator::evaluateConstexpr(const ExpressionContext* expr)
    {
        return ConstexprEvaluatorWalker(*this).evaluate(expr);
    }

} // namespace BraneScript

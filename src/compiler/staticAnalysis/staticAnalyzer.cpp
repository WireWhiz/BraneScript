//
// Created by wirewhiz on 1/23/23.
//

#include "staticAnalyzer.h"
#include <typeinfo>
#include "antlr4/braneBaseVisitor.h"
#include "antlr4/braneLexer.h"
#include "constexprEvaluator.h"
#include "functionCallTree.h"

namespace BraneScript
{
#define NULL_EXPR                                                                                                      \
    (ExpressionContext*)new ExpressionErrorContext { "null expr", __LINE__ }
#define RETURN_EXPR(expr) return (ExpressionContext*)expr
#define RETURN_STMT(expr) return (StatementContext*)expr
#define ASSERT_EXISTS(ptr)                                                                                             \
    if(!(ptr))                                                                                                         \
        return {}
#define EXPR_ASSERT_EXISTS(ptr, message)                                                                               \
    if(!(ptr))                                                                                                         \
    {                                                                                                                  \
        recordError(ctx, message);                                                                                     \
        return (ExpressionContext*)new ExpressionErrorContext{message, __LINE__};                                      \
    }
#define STMT_ASSERT_EXISTS(ptr, message)                                                                               \
    if(!(ptr))                                                                                                         \
    {                                                                                                                  \
        recordError(ctx, message);                                                                                     \
        return (StatementContext*)new StatementErrorContext{message, __LINE__};                                        \
    }

    class Analyzer;

    class Analyzer : public braneBaseVisitor
    {
        class LexerErrorListener : public antlr4::BaseErrorListener
        {
            Analyzer& _analyzer;

          public:
            LexerErrorListener(Analyzer& analyzer) : _analyzer(analyzer){};

            void syntaxError(antlr4::Recognizer* recognizer,
                             antlr4::Token* offendingSymbol,
                             size_t line,
                             size_t charPositionInLine,
                             const std::string& msg,
                             std::exception_ptr e) override
            {
                if(offendingSymbol)
                    _analyzer.recordError(offendingSymbol, msg);
                else
                    _analyzer.recordError({0, 0}, msg);
            }
        };

        class ParserErrorListener : public antlr4::BaseErrorListener
        {
            Analyzer& _analyzer;

          public:
            ParserErrorListener(Analyzer& analyzer) : _analyzer(analyzer) {}

            void syntaxError(antlr4::Recognizer* recognizer,
                             antlr4::Token* offendingSymbol,
                             size_t line,
                             size_t charPositionInLine,
                             const std::string& msg,
                             std::exception_ptr e) override
            {
                if(offendingSymbol)
                    _analyzer.recordError(offendingSymbol, msg);
                else
                    _analyzer.recordError({0, 0}, msg);
            }
        };

        StaticAnalyzer& _analyzer;
        StaticAnalyzer::AnalyzationContext& _result;
        std::stack<DocumentContext*> _documentContext;
        std::string* _rawText;
        bool _extractOnlyIdentifiers;
        bool _allowUnsafe;

        bool _functionHasReturn = false;
        bool _enforceConstexpr = false;

        size_t _headerSize = 0;

        std::vector<LabeledValueContext*> globals;
        robin_hood::unordered_map<std::string, LibraryContext*> _linkedLibraries;
        robin_hood::unordered_map<std::string, TypeContext> _nativeTypes = {{"bool", {"bool", ValueType::Bool}},
                                                                            {"char", {"char", ValueType::Char}},
                                                                            {"uint", {"uint", ValueType::UInt32}},
                                                                            {"uint64", {"uint64", ValueType::UInt64}},
                                                                            {"int", {"int", ValueType::Int32}},
                                                                            {"int64", {"int64", ValueType::Int64}},
                                                                            {"float", {"float", ValueType::Float32}},
                                                                            {"double", {"double", ValueType::Float64}}};

        FunctionCallTree callTree;

        struct TemplateHandle
        {
            enum Type
            {
                Any,
                Function,
                Struct
            } type;

            DocumentContext* parent = nullptr;
            antlr4::ParserRuleContext* root;
            std::vector<std::unique_ptr<TemplateDefArgumentContext>> args;

            TemplateHandle(Type type,
                           antlr4::ParserRuleContext* root,
                           DocumentContext* parent,
                           const std::vector<TemplateDefArgumentContext*>& args)
            {
                this->type = type;
                this->root = root;
                this->parent = parent;
                for(auto& arg : args)
                    this->args.emplace_back(arg);
            }
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

        using MappedTemplateArgs = robin_hood::unordered_map<std::string, std::unique_ptr<TemplateArgContext>>;

        robin_hood::unordered_map<std::string, std::vector<std::unique_ptr<TemplateHandle>>> _registeredTemplates;
        std::list<MappedTemplateArgs> _templateArgs;
        bool _instantiatingTemplate = false;

        TemplateArgContext* getTemplateArg(const std::string& id)
        {
            for(auto i = _templateArgs.rbegin(); i != _templateArgs.rend(); i++)
            {
                auto arg = i->find(id);
                if(arg == i->end())
                    continue;
                return arg->second.get();
            }
            return nullptr;
        }

        std::unique_ptr<ExpressionContext> asExpr(std::any value)
        {
            if(!value.has_value())
                return std::make_unique<ExpressionErrorContext>("internal null value error", __LINE__);
            if(value.type() != typeid(ExpressionContext*))
                return std::make_unique<ExpressionErrorContext>("internal casting error, attempted to cast type " +
                                                                    std::string(value.type().name()) + " to expression",
                                                                __LINE__);
            return std::unique_ptr<ExpressionContext>(std::any_cast<ExpressionContext*>(value));
        }

        std::unique_ptr<StatementContext> asStmt(std::any value)
        {
            if(!value.has_value())
                return std::make_unique<StatementErrorContext>("internal null value error", __LINE__);
            if(value.type() == typeid(ExpressionContext*))
                return std::unique_ptr<StatementContext>(std::any_cast<ExpressionContext*>(value));
            if(value.type() == typeid(StatementContext*))
                return std::unique_ptr<StatementContext>(std::any_cast<StatementContext*>(value));
            return std::make_unique<StatementErrorContext>("internal casting error, attempted to cast type " +
                                                               std::string(value.type().name()) + " to statement",
                                                           __LINE__);
        }

        TextRange toRange(antlr4::Token* token)
        {
            if(!token)
                return _documentContext.top()->range;
            return TextRange{token->getLine() - _headerSize - 1,
                             token->getCharPositionInLine(),
                             token->getLine() - _headerSize - 1,
                             token->getCharPositionInLine() + (token->getStopIndex() - token->getStartIndex()) + 1};
        };

        TextRange toRange(antlr4::ParserRuleContext* ctx)
        {
            if(!ctx)
                return _documentContext.top()->range;
            return TextRange{ctx->getStart()->getLine() - _headerSize - 1,
                             ctx->getStart()->getCharPositionInLine(),
                             ctx->getStop()->getLine() - _headerSize - 1,
                             ctx->getStop()->getCharPositionInLine() +
                                 (ctx->getStop()->getStopIndex() - ctx->getStop()->getStartIndex()) + 1};
        };

        void initDoc(DocumentContext* doc, TextRange range)
        {
            doc->parent = lastNode();
            doc->range = range;
            doc->version = _result.version;
            _documentContext.push(doc);
        }

        void initDoc(DocumentContext* doc) { initDoc(doc, _documentContext.top()->range); }

        void initDoc(DocumentContext* doc, antlr4::Token* token) { initDoc(doc, toRange(token)); }

        void initDoc(DocumentContext* doc, antlr4::ParserRuleContext* ctx) { initDoc(doc, toRange(ctx)); }

        void popDoc(DocumentContext* doc)
        {
            assert(_documentContext.top() == doc);
            _documentContext.pop();
        }

        /**
         * @brief Checks node version numbers to determine if a node is still present in a document, and deletes it if
         * it does not
         * @param vector list to prune
         */
        template<typename T>
        void pruneNodes(LabeledNodeMap<T>& nodes)
        {
            auto itr = nodes.begin();
            while(itr != nodes.end())
            {
                if(itr->second->version != _result.version)
                    itr = nodes.erase(itr);
                else
                    ++itr;
            }
        }

        template<typename T>
        void pruneNodes(LabeledNodeList<T>& nodes)
        {
            nodes.erase(
                std::remove_if(nodes.begin(), nodes.end(), [this](auto& n) { return n->version != _result.version; }),
                nodes.end());
        }

        /**
         * @brief Get an existing node from the passed list, or create a new one if one does not exist
         * Node type must have an "identifier" member
         * @tparam T The type of node we need
         */
        template<typename T>
        T* getNode(LabeledNodeMap<T>& nodes, const std::string& identifier)
        {
            auto n = nodes.find(identifier);
            if(n != nodes.end())
                return n->second.get();
            auto newNode = new T{};
            newNode->identifier.text = identifier;
            nodes.insert({identifier, std::unique_ptr<T>(newNode)});
            return newNode;
        }

        template<typename T>
        T* getNode(LabeledNodeList<T>& nodes, const std::string& identifier)
        {
            for(auto& n : nodes)
            {
                if(n->identifier.text == identifier)
                    return n.get();
            }
            auto newNode = new T{};
            newNode->identifier.text = identifier;
            nodes.push_back(std::unique_ptr<T>(newNode));
            return newNode;
        }

        std::string safeGetText(antlr4::Token* token)
        {
            if(!token)
                return "";
            return token->getText();
        }

        std::string templateArgsToString(const TemplateArgs& args)
        {
            std::string str = "<";
            for(int i = 0; i < args.args.size(); ++i)
            {
                auto& arg = args.args[i];
                if(arg.type == TemplateArgs::Type::Typedef)
                    str += arg.typeDef.signature();
                else if(arg.type == TemplateArgs::Type::Value)
                    str += arg.value->toString();
                if(i != args.args.size() - 1)
                    str += ",";
            }
            str += ">";
            return str;
        }

        std::string templateDefToString(braneParser::TemplateDefContext* tempDef)
        {
            std::string str = "<";
            auto argDefs = std::any_cast<std::vector<TemplateDefArgumentContext*>>(visitTemplateDef(tempDef));
            size_t index = 0;
            for(auto& arg : argDefs)
            {
                auto* argInstance = getTemplateArg(arg->identifier);
                assert(argInstance);
                if(auto typeArg = dynamic_cast<ValueArgContext*>(argInstance))
                    str += typeArg->value->toString();
                if(auto typeArg = dynamic_cast<TypedefArgContext*>(argInstance))
                    str += typeArg->value.signature();
                if(auto typePackArg = dynamic_cast<TypedefPackArgContext*>(argInstance))
                {
                    for(auto& value : typePackArg->values)
                        str += value.signature() + ",";
                }

                delete arg;
                index++;
                if(index != argDefs.size())
                    str += ",";
            }
            str += ">";
            return str;
        }

        std::string functionSig(const std::string& identifier, const std::vector<ValueContext> args)
        {
            std::string sig = identifier + "(";
            for(int i = 0; i < args.size(); ++i)
            {
                sig += args[i].signature();
                if(i != args.size() - 1)
                    sig += ",";
            }
            sig += ")";
            return sig;
        }

        std::string functionSig(const std::string& identifier, const LabeledNodeList<LabeledValueContext>& args)
        {
            std::string sig = identifier + "(";
            for(int i = 0; i < args.size(); ++i)
            {
                sig += args[i]->signature();
                if(i != args.size() - 1)
                    sig += ",";
            }
            sig += ")";
            return sig;
        }

        /**
         * Is this DocumentContext a child of the current ScriptContext being constructed
         */
        bool isLocal(const DocumentContext* node) const
        {
            if(!node)
                return false;
            return node->getParent<const ScriptContext>() == _result.scriptContext.get();
        }

        /**
         * Is this DocumentContext a child of a library
         */
        bool isExported(const DocumentContext* node) const
        {
            if(!node)
                return false;
            return node->getParent<const LibraryContext>();
        }

        DocumentContext* getIdentifierContextFromLibs(const std::string& identifier)
        {
            for(auto& imp : _result.scriptContext->imports)
            {
                if(!imp.second->alias.empty())
                    continue;
                auto lib = _analyzer.getLibrary(imp.second->library);
                if(!lib)
                    continue;
                if(auto* ident = lib->findIdentifier(identifier, IDSearchOptions_ChildrenOnly))
                    return ident;
            }
            return nullptr;
        }

        DocumentContext* getIdentifierContext(const std::string& identifier)
        {
            if(auto* libCtx = _analyzer.getLibrary(identifier))
                return libCtx;
            if(auto* localCtx = lastNode()->findIdentifier(identifier, IDSearchOptions_ParentsOnly))
                return localCtx;
            if(auto* libMemberCtx = getIdentifierContextFromLibs(identifier))
                return libMemberCtx;

            for(auto& alias : _result.scriptContext->imports)
            {
                if(identifier == alias.second->alias)
                    return _analyzer.getLibrary(alias.second->library);
            }
            return nullptr;
        }

        DocumentContext* getIdentifierContext(braneParser::ScopedIDContext* ctx, DocumentContext* parent = nullptr)
        {
            ASSERT_EXISTS(ctx->id);

            DocumentContext* found = nullptr;
            std::string id = ctx->id->getText();

            if(ctx->template_)
            {
                TemplateArgs args = std::any_cast<TemplateArgs>(visitTemplateArgs(ctx->template_));
                found = getTemplateInstance(id, args);
                if(!found)
                {
                    std::string longId;
                    if(auto* lib = lastNode()->as<LibraryContext>())
                        longId = lib->longId() + "::" + id;
                    else if(auto* lib = lastNode()->getParent<LibraryContext>())
                        longId = lib->longId() + "::" + id;
                    found = getTemplateInstance(longId, args);
                }
                if(!found)
                {
                    for(auto& lib : _result.scriptContext->imports)
                    {
                        if(!lib.second->alias.empty())
                            continue;
                        auto libCtx = _analyzer.getLibrary(lib.second->library);
                        if(!libCtx)
                            continue;
                        found = getTemplateInstance(libCtx->longId() + "::" + id, args);
                        if(found)
                            break;
                    }
                }
                if(!found)
                    recordError(ctx->template_, +"\"" + id + "\" is not a template!");
                return found;
            }

            if(!parent)
                found = getIdentifierContext(id);
            else
                found = parent->findIdentifier(id, IDSearchOptions_ChildrenOnly);

            if(!found)
                return nullptr;

            if(ctx->child)
                return getIdentifierContext(ctx->child, found);
            return found;
        }

        TypeContext getTypeContext(braneParser::ScopedIDContext* ctx)
        {
            ASSERT_EXISTS(ctx->id);
            TypeContext output;
            output.identifier = ctx->id->getText();
            if(output.identifier == "void")
                return output;

            if(_nativeTypes.contains(output.identifier))
            {
                output.storageType = _nativeTypes.at(output.identifier).storageType;
                if(ctx->template_)
                    recordError(ctx->child, "Native type " + output.identifier + " is not a template");
                if(ctx->child)
                    recordError(ctx->child, "Native type " + output.identifier + " has no members");
                return output;
            }

            auto sCtx = dynamic_cast<StructContext*>(getIdentifierContext(ctx));
            if(!sCtx)
                sCtx = dynamic_cast<StructContext*>(getIdentifierContextFromLibs(output.identifier));
            if(sCtx)
            {
                output.identifier = sCtx->longId();
                output.structCtx = sCtx;
                output.storageType = ValueType::Struct;

                if(!_extractOnlyIdentifiers && isLocal(sCtx))
                {
                    if(auto* parentFunc = lastNode()->getParent<FunctionContext>())
                    {
                        callTree.addDependency(parentFunc, sCtx->destructor);
                        callTree.addDependency(parentFunc, sCtx->moveConstructor);
                        callTree.addDependency(parentFunc, sCtx->copyConstructor);
                    }
                }
                return output;
            }

            return output;
        }

        bool implicitCastViable(const ValueContext& current, const ValueContext& target)
        {
            if(current.isRef && target.isRef &&
               (current.type.storageType == ValueType::Void || target.type.storageType == ValueType::Void))
                return true;
            return current.type.isScalar() && target.type.isScalar();
        }

        bool
        castSame(std::unique_ptr<ExpressionContext>& left, std::unique_ptr<ExpressionContext>& right, std::string& err)
        {
            left.reset(asRValue(left.release()));
            right.reset(asRValue(right.release()));

            if(left->returnType.sameBaseType(right->returnType))
                return true;

            if(left->returnType.castCost(right->returnType) < right->returnType.castCost(left->returnType))
            {
                auto* oldLeft = left.release();
                auto* newLeft = resolveCast(oldLeft, right->returnType, err);
                if(!newLeft)
                {
                    right.reset(oldLeft);
                    return false;
                }
                left.reset(newLeft);
            }
            else
            {
                auto* oldRight = right.release();
                auto* newRight = resolveCast(oldRight, left->returnType, err);
                if(!newRight)
                {
                    right.reset(oldRight);
                    return false;
                }
                right.reset(newRight);
            }
            return true;
        }

        /**
         * @return Returns a pair, with the first member being the parent context of the last element in the scoped id
         * and the second is the last child. The first member is null if there is only one element in the scoped id.
         */
        std::pair<DocumentContext*, braneParser::ScopedIDContext*>
        getLastScopedID(braneParser::ScopedIDContext* idCtx, braneParser::ScopedIDContext* first = nullptr)
        {
            if(!first)
                first = idCtx;
            if(idCtx->child)
                return getLastScopedID(idCtx->child, first);

            std::pair<DocumentContext*, braneParser::ScopedIDContext*> output = {nullptr, idCtx};

            if(first != idCtx)
            {
                auto parent = dynamic_cast<braneParser::ScopedIDContext*>(idCtx->parent);
                parent->child = nullptr;
                output.first = getIdentifierContext(first);
                parent->child = idCtx;
            }
            return output;
        }

        FunctionOverridesContext* getFunctionOverrides(const std::string& name,
                                                       DocumentContext* scope = nullptr,
                                                       braneParser::TemplateArgsContext* tempArgsCtx = nullptr)
        {
            std::list<FunctionContext*> overrides;
            if(tempArgsCtx)
            {

                TemplateArgs tempArgs = std::any_cast<TemplateArgs>(visitTemplateArgs(tempArgsCtx));

                auto tempFunction =
                    dynamic_cast<FunctionContext*>(getTemplateInstance(name, tempArgs, TemplateHandle::Function));
                for(auto& e : _result.scriptContext->exports)
                {
                    std::string longID = e.first + "::" + name;
                    tempFunction =
                        dynamic_cast<FunctionContext*>(getTemplateInstance(longID, tempArgs, TemplateHandle::Function));
                    if(tempFunction)
                        break;
                }
                if(tempFunction)
                    overrides.push_back(tempFunction);
            }
            else
            {
                if(scope)
                    scope->getFunction(name, overrides, IDSearchOptions_ChildrenOnly);
                else
                {
                    lastNode()->getFunction(name, overrides, IDSearchOptions_ParentsOnly);
                    for(auto& imp : _result.scriptContext->imports)
                    {
                        if(!imp.second->alias.empty())
                            continue;
                        auto lib = _analyzer.getLibrary(imp.second->library);
                        if(!lib)
                            continue;
                        lib->getFunction(name, overrides, IDSearchOptions_ChildrenOnly);
                    }
                }

                // this is where automatically finding templates without explicit arguments would go
            }

            std::vector<FunctionContext*> output(overrides.size());
            std::copy(overrides.begin(), overrides.end(), output.begin());
            auto node = new FunctionOverridesContext(std::move(output));
            initDoc(node);
            popDoc(node);
            return node;
        }

        /** Converts references to non-references */
        ExpressionContext* asRValue(ExpressionContext* value)
        {
            if(!value->returnType.isRef)
                return value;
            auto deref = new DereferenceContext(value);
            initDoc(deref);
            popDoc(deref);
            return deref;
        }

        ExpressionContext* resolveCast(ExpressionContext* from, const ValueContext& to, std::string& error)
        {
            /* We want to insert the error at the position that would make the most sense, which would be right after
             * the last one before a cast was attempted, but not after we get the error about the casting operator not
             * being found.
             */
            if(from->returnType.type == to.type)
            {
                if(!from->returnType.isRef && to.isRef && from->returnType.isLValue)
                {
                    auto createRef = new CreateReferenceContext(from);
                    initDoc(createRef);
                    popDoc(createRef);
                    return createRef;
                }
                if(from->returnType.isRef && !to.isRef)
                    return asRValue(from);
            }


            if(NativeCastContext::validCast(from->returnType, to))
            {
                auto castCtx = new NativeCastContext(to, from);
                initDoc(castCtx);
                popDoc(castCtx);
                return castCtx;
            }

            size_t errorPos = error.size();
            auto castCall = new FunctionCallContext{};
            castCall->arguments.emplace_back(from);

            auto castOverrides = getFunctionOverrides("opr " + to.signature(), nullptr, nullptr);
            castCall->function = castOverrides->bestMatch(
                {castCall->arguments[0]->returnType},
                [](auto from, auto to) { return false; },
                _enforceConstexpr ? FunctionOverridesContext::Constexpr : FunctionOverridesContext::None);
            if(!castCall->function)
            {
                std::string castError =
                    "No casting operator found for " + from->returnType.signature() + " to " + to.signature() + "!\n";
                error.insert(error.begin() + errorPos, castError.begin(), castError.end());
                castCall->arguments[0].release();
                delete castCall;
                return nullptr;
            }

            castCall->returnType = to;
            initDoc(castCall);
            popDoc(castCall);

            return castCall;
        }

        ExpressionContext* resolveOperator(const std::string opr, std::string& error, std::unique_ptr<ExpressionContext> lValue, std::unique_ptr<ExpressionContext> rValue = nullptr)
        {
            size_t errorPos = error.size();
            auto oprCall = new FunctionCallContext{};
            oprCall->arguments.emplace_back(std::move(lValue));
            if(rValue)
                oprCall->arguments.emplace_back(std::move(rValue));

            auto oprOverrides = getFunctionOverrides("opr " + opr, nullptr, nullptr);
            std::vector<ValueContext> argTypes;
            if(oprCall->arguments.size() == 2)
                argTypes = {oprCall->arguments[0]->returnType, oprCall->arguments[1]->returnType};
            else
                argTypes = {oprCall->arguments[0]->returnType};

            oprCall->function = oprOverrides->bestMatch(
                argTypes,
                [this](auto from, auto to) { return implicitCastViable(from, to); },
                _enforceConstexpr ? FunctionOverridesContext::Constexpr : FunctionOverridesContext::None);
            if(!oprCall->function)
            {
                if(oprCall->arguments.size() == 1)
                    error = "No operator \"" + opr + "\" found with argument " + oprCall->arguments[0]->returnType.signature() + "!\n";
                else
                    error = "No operator \"" + opr + "\" found with arguments " + oprCall->arguments[0]->returnType.signature() +
                            " and " + oprCall->arguments[1]->returnType.signature() + "!\n";
                delete oprCall;
                return nullptr;
            }
            initDoc(oprCall);
            popDoc(oprCall);
            oprCall->returnType = oprCall->function->returnType;

            return oprCall;
        }

      public:
        Analyzer(StaticAnalyzer& analyzer,
                 StaticAnalyzer::AnalyzationContext& result,
                 bool extractOnlyIdentifiers,
                 bool allowUnsafe)
            : _analyzer(analyzer), _result(result), _extractOnlyIdentifiers(extractOnlyIdentifiers),
              _allowUnsafe(allowUnsafe){};

        std::any visitExprStatement(braneParser::ExprStatementContext* ctx) override
        {
            return visit(ctx->expression());
        }

        std::any visitExport(braneParser::ExportContext* ctx) override
        {
            ASSERT_EXISTS(ctx->libID);
            assert(lastNode()->is<ScriptContext>());
            std::string identifier = safeGetText(ctx->libID);
            if(identifier.size() < 2)
                return {};

            identifier = identifier.substr(1, identifier.size() - 2);
            auto lib = getNode(lastNode()->as<ScriptContext>()->exports, identifier);
            lib->identifier.range = toRange(ctx->libID);

            if(_extractOnlyIdentifiers)
                lib->templateDefinitions.clear();

            initDoc(lib, ctx);
            visitChildren(ctx);
            popDoc(lib);
            pruneNodes(lib->globals);
            pruneNodes(lib->structs);
            pruneNodes(lib->functions);
            if(_extractOnlyIdentifiers)
                _analyzer.registerLibrary(lib);

            return {};
        }

        std::any visitGlobal(braneParser::GlobalContext* ctx) override
        {
            ASSERT_EXISTS(ctx->id);
            ASSERT_EXISTS(ctx->type());
            LabeledNodeList<LabeledValueContext>* values = nullptr;
            if(lastNode()->is<ScriptContext>())
                values = &lastNode()->as<ScriptContext>()->globals;
            else if(lastNode()->is<LibraryContext>())
                values = &lastNode()->as<LibraryContext>()->globals;
            assert(values);

            auto globVar = getNode(*values, safeGetText(ctx->id));
            globVar->identifier.range = toRange(ctx->id);
            initDoc(globVar, ctx);
            auto value = std::any_cast<ValueContext>(visit(ctx->type()));
            globVar->type = value.type;
            globVar->isConst = value.isConst;
            globVar->isRef = value.isRef;
            globVar->isLValue = true;
            globals.push_back(globVar);
            popDoc(globVar);
            return {};
        }

        std::any visitTemplateDefArgument(braneParser::TemplateDefArgumentContext* ctx) override
        {
            auto arg = new TemplateDefArgumentContext{};
            if(ctx->isTypedef)
                arg->type = ctx->isPack ? TemplateDefArgumentContext::TypedefPack : TemplateDefArgumentContext::Typedef;
            else if(ctx->exprType)
            {
                if(ctx->isPack)
                    recordError(ctx->isPack, "Expression arguments can not have variable length");
                arg->type = TemplateDefArgumentContext::Value;
                arg->valueType = std::any_cast<ValueContext>(visitType(ctx->exprType)).type;
            }
            arg->identifier = ctx->id->getText();
            return arg;
        }

        std::any visitTemplateDef(braneParser::TemplateDefContext* ctx) override
        {
            std::vector<TemplateDefArgumentContext*> args;
            auto argsCtx = ctx->templateDefArgument();
            for(auto arg : argsCtx)
            {
                auto newArg = std::any_cast<TemplateDefArgumentContext*>(visitTemplateDefArgument(arg));
                args.push_back(newArg);
                if(arg->isPack && args.size() != argsCtx.size())
                    recordError(arg->isPack, "Only the last template argument may be a pack!");
            }
            return std::move(args);
        }

        std::any visitTemplateArgs(braneParser::TemplateArgsContext* ctx) override
        {
            TemplateArgs args;
            for(auto* arg : ctx->templateArg())
            {
                if(auto* exprArg = dynamic_cast<braneParser::TemplateExprArgContext*>(arg))
                {
                    auto expr = asExpr(visit(exprArg->expr));
                    if(!expr->isConstexpr())
                    {
                        recordError(exprArg, "Template arguments must be constant expressions");
                        continue;
                    }
                    if(!_analyzer.constexprEvaluator())
                        throw std::runtime_error("Static analyzer must have an attached constexpr evaluator to use "
                                                 "expressions as template arguments");
                    auto exprResult = _analyzer.constexprEvaluator()->evaluateConstexpr(expr.get());
                    if(!exprResult)
                    {
                        recordError(exprArg, "Could not evaluate expression");
                        continue;
                    }
                    args.addArg(exprResult);

                    continue;
                }
                if(auto* typeArg = dynamic_cast<braneParser::TemplateTypeArgContext*>(arg))
                {
                    args.addArg(std::any_cast<ValueContext>(visit(typeArg)));
                    continue;
                }
                if(auto* packArg = dynamic_cast<braneParser::PackExpansionArgContext*>(arg))
                {
                    std::string packID = safeGetText(packArg->packID);
                    auto* argInstance = getTemplateArg(packID);
                    if(!argInstance)
                    {
                        recordError(arg, packID + " does not refer to a template argument!");
                        continue;
                    }
                    auto* pack = dynamic_cast<TypedefPackArgContext*>(argInstance);
                    if(!pack)
                    {
                        recordError(arg, packID + " is not a pack argument!");
                        continue;
                    }
                    for(auto& value : pack->values)
                        args.addArg(value);
                    break;
                }
            }
            return std::move(args);
        }

        std::any visitScopedID(braneParser::ScopedIDContext* ctx) override
        {
            assert(false && "Allways call getIdentifier instead visit");
            return {};
        }

        std::any visitType(braneParser::TypeContext* ctx) override
        {
            ValueContext output;
            output.type = getTypeContext(ctx->name);
            output.isConst = ctx->isConst;
            output.isRef = ctx->isRef;

            if(output.type.storageType == ValueType::Void && output.type.identifier != "void")
            {
                auto* arg = getTemplateArg(output.type.identifier);
                if(_instantiatingTemplate && arg)
                {
                    if(auto* tempType = dynamic_cast<TypedefArgContext*>(arg))
                    {
                        output.type = tempType->value.type;
                        output.isConst = output.isConst || tempType->value.isConst;
                        output.isRef = output.isRef || tempType->value.isRef;
                    }
                    else if(auto* tempTypePack = dynamic_cast<TypedefPackArgContext*>(arg))
                        recordError(ctx->name, "Cannot use an argument pack as a type!");
                }
                else
                    recordError(ctx->name, "Type " + output.signature() + " could not be found!");
            }

            if(_enforceConstexpr && ctx->isRef)
                recordError(ctx, "References not supported in constexpr scopes!");

            if(_enforceConstexpr && output.type.storageType == ValueType::Struct)
                recordError(ctx, "Types of struct not supported in constexpr scopes");

            assert(output.type.storageType != ValueType::Struct || output.type.structCtx);
            return output;
        }

        std::any visitDeclaration(braneParser::DeclarationContext* ctx) override
        {
            LabeledValueContext valueContext{};
            if(!ctx->type())
                return valueContext;
            initDoc(&valueContext, ctx);
            auto type = std::any_cast<ValueContext>(visitType(ctx->type()));
            valueContext.type = std::move(type.type);
            valueContext.isConst = type.isConst;
            valueContext.isRef = type.isRef;
            if(ctx->id)
            {
                valueContext.identifier.text = safeGetText(ctx->id);
                valueContext.identifier.range = toRange(ctx->id);
            }
            if(valueContext.type.structCtx && !valueContext.isRef)
            {
                if(auto* parentFunc = lastNode()->getParent<FunctionContext>())
                {
                    if(isLocal(valueContext.type.structCtx))
                        callTree.addDependency(parentFunc, valueContext.type.structCtx->constructor);
                }
            }

            popDoc(&valueContext);
            return valueContext;
        }

        std::any visitArgumentList(braneParser::ArgumentListContext* ctx) override
        {
            assert(false);
            return {};
        }

        LabeledNodeList<LabeledValueContext> constructArgumentList(braneParser::ArgumentListContext* ctx,
                                                                   ArgPackInstanceContext** argPackInstance = nullptr)
        {
            LabeledNodeList<LabeledValueContext> args;
            for(auto& item : ctx->argumentListItem())
            {
                if(auto* declaration = item->declaration())
                    args.emplace_back(
                        new LabeledValueContext{std::any_cast<LabeledValueContext>(visitDeclaration(declaration))});
                else
                {
                    if(!_instantiatingTemplate)
                    {
                        recordError(item, "argument packs may only be used in templates!");
                        continue;
                    }
                    std::string packID = safeGetText(item->pack);
                    auto* argInstance = getTemplateArg(packID);
                    if(!argInstance)
                    {
                        recordError(item->id, packID + " is not a template argument!");
                        continue;
                    }
                    auto* pack = dynamic_cast<TypedefPackArgContext*>(argInstance);
                    if(!pack)
                    {
                        recordError(item->id, packID + " is not an argument pack!");
                        continue;
                    }

                    std::string prefix = safeGetText(item->id);
                    size_t labelIndex = 0;
                    if(argPackInstance)
                    {
                        if(*argPackInstance)
                        {
                            recordError(item, "Only one argument pack is in an argument list is allowed!");
                            continue;
                        }
                        *argPackInstance = new ArgPackInstanceContext{};
                        (*argPackInstance)->identifier = prefix;
                    }
                    for(auto& value : pack->values)
                    {
                        auto* valueInstance =
                            new LabeledValueContext{prefix + " " + std::to_string(labelIndex++), value};
                        if(argPackInstance)
                            (*argPackInstance)->values.emplace_back(valueInstance);
                        args.emplace_back(valueInstance);
                    }
                }
            }
            return std::move(args);
        }

        bool populateTemplateArgs(TemplateHandle* temp, const TemplateArgs& args)
        {
            if(args.args.size() < temp->args.size())
                return false;
            size_t arg = 0;
            MappedTemplateArgs argsToPush;
            for(size_t argDef = 0; argDef < temp->args.size(); ++argDef)
            {
                if(arg == args.args.size())
                    return false;

                std::string identifier = temp->args[argDef]->identifier;
                if(temp->args[argDef]->type == TemplateDefArgumentContext::Value)
                {
                    if(args.args[arg].type != TemplateArgs::Type::Value)
                        return false;
                    if(temp->args[argDef]->valueType != args.args[arg].value->returnType.type)
                        return false;
                    auto valueArg = new ValueArgContext{};
                    valueArg->identifier = identifier;
                    valueArg->value.reset((ConstValueContext*)args.args[arg++].value->deepCopy());
                    argsToPush.emplace(identifier, valueArg);
                }
                else if(temp->args[argDef]->type == TemplateDefArgumentContext::Typedef)
                {
                    if(args.args[arg].type != TemplateArgs::Type::Typedef)
                        return false;
                    argsToPush.emplace(identifier, new TypedefArgContext{identifier, args.args[arg++].typeDef});
                }
                else if(temp->args[argDef]->type == TemplateDefArgumentContext::TypedefPack)
                {
                    if(argDef != temp->args.size() - 1)
                        return false;
                    auto pack = new TypedefPackArgContext{};
                    pack->identifier = identifier;
                    while(arg != args.args.size())
                    {
                        if(args.args[arg].type != TemplateArgs::Type::Typedef)
                            return false;
                        pack->values.push_back(args.args[arg++].typeDef);
                    }
                    argsToPush.emplace(std::move(identifier), pack);
                }
            }
            if(arg != args.args.size())
                return false;
            _templateArgs.push_back(std::move(argsToPush));
            return true;
        }

        DocumentContext* getTemplateInstance(const std::string& identifier,
                                             const TemplateArgs& args,
                                             TemplateHandle::Type expectedType = TemplateHandle::Any)
        {
            if(!_registeredTemplates.contains(identifier))
                return nullptr;

            auto& templateInstances = _registeredTemplates.at(identifier);
            for(auto& temp : templateInstances)
            {
                if(expectedType != TemplateHandle::Any && temp->type != expectedType)
                    continue;
                if(!populateTemplateArgs(temp.get(), args))
                    continue;

                _instantiatingTemplate = true;
                DocumentContext* generated = nullptr;

                _documentContext.push(temp->parent);
                if(auto* structDef = dynamic_cast<braneParser::StructDefContext*>(temp->root))
                    generated = std::any_cast<StructContext*>(visitStructDef(structDef));
                if(auto* functionDef = dynamic_cast<braneParser::FunctionContext*>(temp->root))
                    generated = std::any_cast<FunctionContext*>(visitFunction(functionDef));
                _documentContext.pop();

                _templateArgs.pop_back();
                _instantiatingTemplate = !_templateArgs.empty();
                return generated;
            }
            return nullptr;
        }

        FunctionContext* getFunctionNode(const std::string& identifier,
                                         const LabeledNodeList<LabeledValueContext>& args)
        {
            LabeledNodeList<FunctionContext>* functions = nullptr;
            if(auto* s = getLast<StructContext>())
                functions = &s->functions;
            else if(auto* l = getLast<LibraryContext>())
                functions = &l->functions;
            else
                functions = &_result.scriptContext->functions;
            assert(functions);

            // See if a function with this overload already exists
            for(auto& f : *functions)
            {
                if(f->identifier.text != identifier)
                    continue;
                if(f->arguments.size() != args.size())
                    continue;
                bool argumentsMatch = true;
                for(size_t a = 0; a < args.size(); ++a)
                {
                    if(*f->arguments[a] != *args[a])
                    {
                        argumentsMatch = false;
                        break;
                    }
                }
                if(argumentsMatch)
                    return f.get();
            }
            // If the function was not found, add it
            auto func = new FunctionContext{};
            func->identifier.text = identifier;
            func->version = -1;
            functions->emplace_back(func);
            return func;
        }

        // I despise std::any
        struct FunctionSig
        {
            std::string id;
            ValueContext returnType;
        };

        virtual std::any visitFunctionSig(braneParser::FunctionSigContext* ctx) override
        {
            ASSERT_EXISTS(ctx->type() || ctx->castType);
            ASSERT_EXISTS(ctx->id || ctx->oprID || ctx->castType);

            FunctionSig o;
            o.returnType = std::any_cast<ValueContext>((ctx->castType) ? visit(ctx->castType) : visit(ctx->type()));
            if(ctx->id)
                o.id = safeGetText(ctx->id);
            else if(ctx->oprID)
                o.id = "opr " + safeGetText(ctx->oprID);
            else if(ctx->castType)
                o.id = "opr " + o.returnType.signature();

            // Modify id if we are instantiating a template
            if(_instantiatingTemplate && ctx->template_)
                o.id += templateDefToString(ctx->template_);

            if(_enforceConstexpr && o.returnType.type.storageType == ValueType::Struct)
                recordError((ctx->castType) ? ctx->castType : ctx->type(),
                            "Return types of struct are not yet supported in constexpr functions");

            return o;
        }

        std::any visitFunctionStub(braneParser::FunctionStubContext* ctx) override
        {
            ASSERT_EXISTS(ctx->sig);
            auto sigAny = visitFunctionSig(ctx->functionSig());
            if(!sigAny.has_value())
                return (FunctionContext*)nullptr;
            FunctionSig sig = std::move(std::any_cast<FunctionSig>(sigAny));
            auto arguments = constructArgumentList(ctx->arguments);

            auto parentStruct = lastNode()->getLast<StructContext>();
            if(parentStruct)
            {
                auto* thisRef = new LabeledValueContext{};
                thisRef->type = TypeContext{parentStruct->longId(), ValueType::Struct, parentStruct};
                thisRef->identifier.text = "this";
                thisRef->isLValue = true;
                thisRef->isRef = true;
                thisRef->isConst = ctx->isConst;
                arguments.emplace(arguments.begin(), thisRef);
            }

            FunctionContext* func = getFunctionNode(sig.id, arguments);
            func->identifier.range = toRange(ctx->sig->id);
            func->returnType = sig.returnType;
            for(auto& arg : arguments)
                assert(arg->type.storageType != ValueType::Struct || arg->type.structCtx);
            func->arguments = std::move(arguments);
            func->isConstexpr = ctx->functionSig()->isConstexpr;

            for(auto& a : func->arguments)
            {
                a->parent = func;
                a->isLValue = true;
            }

            if(func->version == _result.version)
                recordError(ctx->sig->id, "Redefinition of already existing function!");

            initDoc(func, ctx);
            popDoc(func);
            return (FunctionContext*)func;
        }

        std::any visitFunction(braneParser::FunctionContext* ctx) override
        {
            ASSERT_EXISTS(ctx->sig);

            if(ctx->sig->template_ && !_instantiatingTemplate)
            {
                std::string id = safeGetText(ctx->sig->id);
                std::string prefix = lastNode()->longId();
                if(!prefix.empty())
                    id = prefix + "::" + id;
                auto args = std::any_cast<std::vector<TemplateDefArgumentContext*>>(visit(ctx->sig->template_));
                _registeredTemplates[id].emplace_back(
                    new TemplateHandle(TemplateHandle::Function, ctx, lastNode(), args));
                if(_extractOnlyIdentifiers)
                {
                    if(auto parentLib = getLast<LibraryContext>())
                    {
                        auto textRange = toRange(ctx).getBoundsForText(*_rawText);
                        std::string templateText =
                            _rawText->substr(textRange.first, textRange.second - textRange.first);
                        parentLib->templateDefinitions[id] = templateText;
                    }
                }
                return (FunctionContext*)nullptr;
            }

            auto sigAny = visitFunctionSig(ctx->sig);
            if(!sigAny.has_value())
                return (FunctionContext*)nullptr;

            FunctionSig sig = std::move(std::any_cast<FunctionSig>(sigAny));

            ArgPackInstanceContext* argPackInstanceContext = nullptr;
            auto arguments = std::move(constructArgumentList(ctx->arguments, &argPackInstanceContext));

            auto parentStruct = lastNode()->getLast<StructContext>();
            if(parentStruct)
            {
                auto* thisRef = new LabeledValueContext{};
                thisRef->type = TypeContext{parentStruct->longId(), ValueType::Struct, parentStruct};
                thisRef->identifier.text = "this";
                thisRef->isLValue = true;
                thisRef->isRef = true;
                thisRef->isConst = ctx->isConst;
                arguments.emplace(arguments.begin(), thisRef);
            }

            FunctionContext* func = getFunctionNode(sig.id, arguments);
            if(!_extractOnlyIdentifiers && isExported(func))
                callTree.addFunction(func);

            func->identifier.range = toRange(ctx->sig->id);
            func->returnType = sig.returnType;
            func->arguments = std::move(arguments);
            func->isConstexpr = ctx->functionSig()->isConstexpr;
            if(argPackInstanceContext)
            {
                func->argPackInstances.insert({argPackInstanceContext->identifier, std::move(*argPackInstanceContext)});
                delete argPackInstanceContext;
            }

            for(size_t i = 0; i < func->arguments.size(); i++)
            {
                auto& a = func->arguments[i];
                a->parent = func;
                a->isLValue = true;
                if(a->type.storageType == ValueType::Struct && !a->isRef)
                    recordError(
                        a->identifier.range,
                        R"(Structs may only be passed by reference, consider adding the "ref" and "const" descriptors instead)");
            }

            if(func->version == _result.version)
            {
                // If we are attempting to instantiate a template, but it turns out we already have, just return the
                // existing one
                if(_instantiatingTemplate)
                    return func;
                recordError(ctx->functionSig()->id, "Redefinition of already existing function!");
            }

            bool cachedFHR = _functionHasReturn;
            bool cachedConstexpr = _enforceConstexpr;
            _functionHasReturn = false;
            _enforceConstexpr = func->isConstexpr;

            initDoc(func, ctx);

            if(!_extractOnlyIdentifiers)
            {
                func->body = std::make_unique<ScopeContext>();
                initDoc(func->body.get(), ctx);
                for(auto stmt : ctx->statement())
                {
                    auto statement = asStmt(visit(stmt));
                    if(statement)
                        func->body->expressions.push_back(std::move(statement));
                }
                popDoc(func->body.get());

                if(!_functionHasReturn && func->returnType.type.storageType != ValueType::Void)
                    recordError(ctx->sig->id, "Function never returns " + func->returnType.type.identifier);
            }
            popDoc(func);


            _functionHasReturn = cachedFHR;
            _enforceConstexpr = cachedConstexpr;

            return func;
        }

        std::any visitLink(braneParser::LinkContext* ctx) override
        {
            ASSERT_EXISTS(ctx->library);
            ImportContext i;
            if(ctx->alias)
            {
                i.alias = safeGetText(ctx->alias);
                if(i.alias.size() >= 2)
                    i.alias = i.alias.substr(1, i.alias.size() - 2);
            }
            i.library = safeGetText(ctx->library);
            if(i.library.size() >= 2)
                i.library = i.library.substr(1, i.library.size() - 2);
            initDoc(&i, ctx);
            popDoc(&i);
            auto libraries = _analyzer.getLibrary(i.library);
            if(!libraries && !_extractOnlyIdentifiers)
                recordError(ctx->library, "Library exported with identifier \"" + i.library + "\" not found!");
            if(libraries)
            {
                auto localLibItr = _result.scriptContext->exports.find(i.library);
                LibraryContext* localLib = nullptr;
                if(localLibItr != _result.scriptContext->exports.end())
                    localLib = localLibItr->second.get();
                i.importedModules.reserve(libraries->exports.size() - (localLib ? 1 : 0));
                for(auto import : libraries->exports)
                {
                    if(import != localLib)
                        i.importedModules.push_back(import);
                }
            }

            if(!_extractOnlyIdentifiers && !_allowUnsafe && i.library == "unsafe")
                recordError(ctx->library, "Unsafe code is not allowed for this script");

            lastNode()->as<ScriptContext>()->imports[i.library] = std::make_unique<ImportContext>(std::move(i));
            return {};
        }

        std::any visitMemberVariable(braneParser::MemberVariableContext* ctx) override
        {
            ASSERT_EXISTS(ctx->var);
            ASSERT_EXISTS(ctx->var->id);
            auto var = getNode(lastNode()->as<StructContext>()->variables, safeGetText(ctx->var->id));
            *var = std::any_cast<LabeledValueContext>(visit(ctx->var));
            var->isLValue = true;
            initDoc(var, ctx);
            // TODO default value
            popDoc(var);
            return {};
        }

        std::any visitMemberFunction(braneParser::MemberFunctionContext* ctx) override
        {
            return visitFunction(ctx->func);
        }

        std::any visitStructDef(braneParser::StructDefContext* ctx) override
        {
            ASSERT_EXISTS(ctx->id);
            LabeledNodeList<StructContext>* structs = nullptr;
            if(lastNode()->as<ScriptContext>())
                structs = &lastNode()->as<ScriptContext>()->structs;
            else if(lastNode()->is<LibraryContext>())
                structs = &lastNode()->as<LibraryContext>()->structs;
            assert(structs);

            std::string id = safeGetText(ctx->id);

            // Register template
            if(ctx->template_ && !_instantiatingTemplate)
            {
                std::string prefix = lastNode()->longId();
                if(!prefix.empty())
                    id = prefix + "::" + id;
                auto args = std::any_cast<std::vector<TemplateDefArgumentContext*>>(visitTemplateDef(ctx->template_));
                _registeredTemplates[id].emplace_back(
                    new TemplateHandle(TemplateHandle::Struct, ctx, lastNode(), args));
                return (StructContext*)nullptr;
            }

            // Modify id if we are instantiating a template
            if(ctx->template_)
                id += templateDefToString(ctx->template_);

            auto structCtx = getNode(*structs, id);
            if(structCtx->version == _result.version)
            {
                if(_instantiatingTemplate)
                    return structCtx;
                recordError(ctx->id, "Structure with this identifier has already been defined!");
            }

            initDoc(structCtx, ctx);
            for(auto& m : ctx->structMember())
                visit(m);

            structCtx->constructor = nullptr;
            structCtx->copyConstructor = nullptr;
            structCtx->moveConstructor = nullptr;
            structCtx->destructor = nullptr;
            for(auto& f : structCtx->functions)
            {
                // If this is an out of date function, skip (this will make it so we always regenerate auto-created
                // constructors)
                if(f->version != _result.version)
                    continue;
                if(f->identifier.text == "_construct")
                    structCtx->constructor = f.get();
                if(f->identifier.text == "_copy")
                    structCtx->copyConstructor = f.get();
                if(f->identifier.text == "_move")
                    structCtx->moveConstructor = f.get();
                if(f->identifier.text == "_destruct")
                    structCtx->destructor = f.get();
            }
            const bool structExported = isExported(structCtx);
            // Make constructor
            if(!structCtx->constructor)
            {
                LabeledValueContext thisRef{};
                thisRef.identifier.text = "this";
                thisRef.isRef = true;
                thisRef.type = {structCtx->longId(), ValueType::Struct, structCtx};

                LabeledNodeList<LabeledValueContext> args;
                args.emplace_back(new LabeledValueContext{thisRef});
                auto func = getFunctionNode("_construct", args);
                initDoc(func, ctx->id);
                popDoc(func);
                func->arguments = std::move(args);
                func->body = std::make_unique<ScopeContext>();

                size_t varIndex = 0;
                for(auto& var : structCtx->variables)
                {
                    if(var->type.storageType == ValueType::Struct)
                    {
                        auto memberBase = new LabeledValueReferenceContext(*func->arguments[0]);

                        auto memberAccess = new MemberAccessContext{};
                        memberAccess->member = varIndex;
                        memberAccess->returnType = *var;
                        memberAccess->returnType.isRef = true;
                        memberAccess->baseExpression.reset(memberBase);

                        auto constructCall = new FunctionCallContext{};
                        constructCall->arguments.emplace_back(memberAccess);
                        constructCall->function = var->type.structCtx->constructor;
                        if(!constructCall->function)
                            recordError(ctx->start,
                                        "Could not find constructor for struct \"" + var->type.structCtx->longId() +
                                            "\"");

                        if(isLocal(constructCall->function))
                            callTree.addDependency(func, constructCall->function);
                        func->body->expressions.emplace_back(constructCall);
                    }
                    varIndex++;
                }
                if(structExported)
                    callTree.addFunction(func);
                structCtx->constructor = func;
            }
            // Make copy constructor
            if(!structCtx->copyConstructor)
            {
                LabeledValueContext thisRef{};
                thisRef.identifier.text = "this";
                thisRef.isRef = true;
                thisRef.type = {structCtx->longId(), ValueType::Struct, structCtx};

                LabeledValueContext otherRef{};
                otherRef.identifier.text = "other";
                otherRef.isRef = true;
                otherRef.isConst = true;
                otherRef.type = {structCtx->longId(), ValueType::Struct, structCtx};

                LabeledNodeList<LabeledValueContext> args;
                args.emplace_back(new LabeledValueContext{thisRef});
                args.emplace_back(new LabeledValueContext{otherRef});
                auto func = getFunctionNode("_copy", args);
                initDoc(func, ctx->id);
                popDoc(func);
                func->arguments = std::move(args);
                func->body = std::make_unique<ScopeContext>();

                size_t varIndex = 0;
                for(auto& var : structCtx->variables)
                {
                    auto memberBase = new LabeledValueReferenceContext{*func->arguments[0]};

                    auto memberAccess = new MemberAccessContext{};
                    memberAccess->member = varIndex;
                    memberAccess->returnType = *var;
                    memberAccess->returnType.isRef = true;
                    memberAccess->baseExpression.reset(memberBase);

                    auto otherBase = new LabeledValueReferenceContext{*func->arguments[1]};

                    auto otherAccess = new MemberAccessContext{};
                    otherAccess->member = varIndex;
                    otherAccess->returnType = *var;
                    otherAccess->returnType.isRef = true;
                    otherAccess->returnType.isConst = true;
                    otherAccess->baseExpression.reset(otherBase);

                    if(var->type.storageType == ValueType::Struct)
                    {
                        auto constructCall = new FunctionCallContext{};
                        constructCall->arguments.emplace_back(memberAccess);
                        constructCall->arguments.emplace_back(otherAccess);
                        std::string error;
                        constructCall->function = var->type.structCtx->copyConstructor;
                        if(!constructCall->function)
                            recordError(ctx->start,
                                        "Could not find copy constructor for struct \"" +
                                            var->type.structCtx->longId() + "\"");
                        if(isLocal(constructCall->function))
                            callTree.addDependency(func, constructCall->function);
                        func->body->expressions.emplace_back(constructCall);
                    }
                    else
                    {
                        auto move = new AssignmentContext{memberAccess, otherAccess};
                        func->body->expressions.emplace_back(move);
                    }
                    varIndex++;
                }
                if(structExported)
                    callTree.addFunction(func);
                structCtx->copyConstructor = func;
            }
            // Make move constructor
            if(!structCtx->moveConstructor)
            {
                LabeledValueContext thisRef{};
                thisRef.identifier.text = "this";
                thisRef.isRef = true;
                thisRef.type = {structCtx->longId(), ValueType::Struct, structCtx};

                LabeledValueContext otherRef{};
                otherRef.identifier.text = "other";
                otherRef.isRef = true;
                otherRef.type = {structCtx->longId(), ValueType::Struct, structCtx};

                LabeledNodeList<LabeledValueContext> args;
                args.emplace_back(new LabeledValueContext{thisRef});
                args.emplace_back(new LabeledValueContext{otherRef});
                auto func = getFunctionNode("_move", args);
                initDoc(func, ctx->id);
                popDoc(func);
                func->arguments = std::move(args);
                func->body = std::make_unique<ScopeContext>();

                size_t varIndex = 0;
                for(auto& var : structCtx->variables)
                {
                    auto memberBase = new LabeledValueReferenceContext{*func->arguments[0]};

                    auto memberAccess = new MemberAccessContext{};
                    memberAccess->returnType = *var;
                    memberAccess->returnType.isRef = true;
                    memberAccess->member = varIndex;
                    memberAccess->baseExpression.reset(memberBase);

                    auto otherBase = new LabeledValueReferenceContext{*func->arguments[1]};

                    auto otherAccess = new MemberAccessContext{};
                    otherAccess->member = varIndex;
                    otherAccess->returnType = *var;
                    otherAccess->returnType.isRef = true;
                    otherAccess->baseExpression.reset(otherBase);

                    if(var->type.storageType == ValueType::Struct)
                    {
                        auto constructCall = new FunctionCallContext{};
                        constructCall->arguments.emplace_back(memberAccess);
                        constructCall->arguments.emplace_back(otherAccess);
                        std::string error;
                        constructCall->function = var->type.structCtx->moveConstructor;
                        if(!constructCall->function)
                            recordError(ctx->start,
                                        "Could not find move constructor for struct \"" +
                                            var->type.structCtx->longId() + "\"");
                        if(isLocal(constructCall->function))
                            callTree.addDependency(func, constructCall->function);
                        func->body->expressions.emplace_back(constructCall);
                    }
                    else
                    {
                        auto move = new AssignmentContext{memberAccess, otherAccess};
                        func->body->expressions.emplace_back(move);
                    }
                    varIndex++;
                }
                if(structExported)
                    callTree.addFunction(func);
                structCtx->moveConstructor = func;
            }
            // Make destructor
            if(!structCtx->destructor)
            {
                LabeledValueContext thisRef{};
                thisRef.identifier.text = "this";
                thisRef.isRef = true;
                thisRef.type = {structCtx->longId(), ValueType::Struct, structCtx};

                LabeledNodeList<LabeledValueContext> args;
                args.emplace_back(new LabeledValueContext{thisRef});
                auto func = getFunctionNode("_destruct", args);
                initDoc(func, ctx->id);
                popDoc(func);
                func->arguments = std::move(args);
                func->body = std::make_unique<ScopeContext>();

                size_t varIndex = 0;
                for(auto& var : structCtx->variables)
                {
                    if(var->type.storageType == ValueType::Struct)
                    {
                        auto memberBase = new LabeledValueReferenceContext{*func->arguments[0]};

                        auto memberAccess = new MemberAccessContext{};
                        memberAccess->member = varIndex;
                        memberAccess->returnType = *var;
                        memberAccess->returnType.isRef = true;
                        memberAccess->baseExpression.reset(memberBase);

                        auto constructCall = new FunctionCallContext{};
                        constructCall->arguments.emplace_back(memberAccess);
                        std::string error;
                        constructCall->function = var->type.structCtx->destructor;
                        if(!constructCall->function)
                            recordError(ctx->start,
                                        "Could not find destructor for struct \"" + var->type.structCtx->longId() +
                                            "\"");
                        if(isLocal(constructCall->function))
                            callTree.addDependency(func, constructCall->function);
                        func->body->expressions.emplace_back(constructCall);
                    }
                    varIndex++;
                }
                if(structExported)
                    callTree.addFunction(func);
                structCtx->destructor = func;
            }
            structCtx->packed = ctx->packed;
            popDoc(structCtx);
            pruneNodes(structCtx->variables);
            pruneNodes(structCtx->functions);

            return structCtx;
        }

        std::any visitScope(braneParser::ScopeContext* ctx) override
        {
            auto scope = new ScopeContext{};
            initDoc(scope, ctx);
            for(auto& s : ctx->statement())
            {
                auto stmt = asStmt(visit(s));
                if(stmt)
                    scope->expressions.push_back(std::move(stmt));
            }

            for(auto& var : scope->localVariables)
            {
                if(!var->type.structCtx)
                    continue;
                auto destructor = new LabeledValueDestructionContext(*var);
                scope->expressions.emplace_back(destructor);
            }

            popDoc(scope);
            RETURN_STMT(scope);
        }

        std::any visitReturn(braneParser::ReturnContext* ctx) override
        {
            auto retCtx = new ReturnContext{};
            initDoc(retCtx, ctx);
            if(ctx->expression())
                retCtx->value = asExpr(visit(ctx->expression()));

            auto& functionType = lastNode()->getParent<FunctionContext>()->returnType;
            if(retCtx->value && !retCtx->value->returnType.sameBaseType(functionType))
            {
                std::string castError;
                if(auto castCtx = resolveCast(retCtx->value.release(), functionType, castError))
                    retCtx->value.reset(castCtx);
                else
                    recordError(ctx, castError);
            }
            if(retCtx->value && retCtx->value->returnType.type.storageType == ValueType::Struct)
            {
                auto* sCtx = retCtx->value->returnType.type.structCtx;
                retCtx->value->returnType.type.identifier = sCtx->longId();
                auto* parentFunc = lastNode()->getParent<FunctionContext>();
                if(isLocal(sCtx))
                    callTree.addDependency(parentFunc, sCtx->constructor);
            }

            popDoc(retCtx);
            _functionHasReturn = true;
            RETURN_STMT(retCtx);
        }

        std::any visitIf(braneParser::IfContext* ctx) override
        {
            STMT_ASSERT_EXISTS(ctx->cond, "If missing condition");
            STMT_ASSERT_EXISTS(ctx->operation, "If statement missing body");
            auto ifCtx = new IfContext{};
            initDoc(ifCtx, ctx);
            ifCtx->condition = asExpr(visit(ctx->cond));
            if(ifCtx->condition->returnType.type.storageType != ValueType::Bool)
                recordError(ctx->cond, "Condition must be a Boolean value");

            if(_instantiatingTemplate && _analyzer.constexprEvaluator() && ifCtx->condition->isConstexpr() &&
               _result.errors.empty())
            {
                auto condRes = std::unique_ptr<ConstValueContext>(
                    _analyzer.constexprEvaluator()->evaluateConstexpr(ifCtx->condition.get()));
                popDoc(ifCtx);
                delete ifCtx;
                if(dynamic_cast<ConstBoolContext*>(condRes.get())->value)
                    RETURN_STMT(asStmt(visit(ctx->operation)).release());
                if(ctx->elseOp)
                    RETURN_STMT(asStmt(visit(ctx->elseOp)).release());
                RETURN_STMT(new ScopeContext{});
            }


            ifCtx->body = asStmt(visit(ctx->operation));
            if(ctx->elseOp)
                ifCtx->elseBody = asStmt(visit(ctx->elseOp));
            popDoc(ifCtx);

            RETURN_STMT(ifCtx);
        }

        std::any visitWhile(braneParser::WhileContext* ctx) override
        {
            STMT_ASSERT_EXISTS(ctx->cond, "while loop condition missing");
            STMT_ASSERT_EXISTS(ctx->operation, "while loop body missing");
            auto whileCtx = new WhileContext{};
            initDoc(whileCtx, ctx);
            whileCtx->condition = asExpr(visit(ctx->cond));
            whileCtx->body = asStmt(visit(ctx->operation));
            popDoc(whileCtx);
            RETURN_STMT(whileCtx);
        }

        std::any visitDecl(braneParser::DeclContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->declaration(), "declaration expected");
            auto* scope = lastNode()->as<ScopeContext>();
            if(!scope)
                scope = lastNode()->getParent<ScopeContext>();
            assert(scope);

            auto result = new LabeledValueConstructionContext{};
            initDoc(result, ctx);
            auto decl = std::make_unique<LabeledValueContext>(
                std::any_cast<LabeledValueContext>(visitDeclaration(ctx->declaration())));

            if(decl->type.storageType == ValueType::Struct)
            {
                auto* s = decl->type.structCtx;
                if(isLocal(s))
                    callTree.addDependency(lastNode()->getParent<FunctionContext>(), s->constructor);
            }

            decl->isLValue = true;

            scope->localVariables.push_back(std::move(decl));
            popDoc(result);
            auto value = (--scope->localVariables.end())->get();
            result->identifier = value->identifier;
            result->returnType = *value;

            RETURN_EXPR(result);
        }

        std::any visitAssignment(braneParser::AssignmentContext* ctx) override
        {
            STMT_ASSERT_EXISTS(ctx->lValue, "lValue expected");
            STMT_ASSERT_EXISTS(ctx->rValue, "rValue expected");
            auto assignmentCtx = new AssignmentContext{};
            initDoc(assignmentCtx, ctx);
            auto lValue = asExpr(visit(ctx->lValue));
            assert(lValue);
            if(!lValue->returnType.isLValue)
                recordError(ctx->lValue, "Expression is not an lValue!");
            if(lValue->returnType.isConst)
                recordError(ctx->lValue, "Can not modify a constant value!");

            auto rValue = asExpr(visit(ctx->rValue));
            assert(rValue);
            if(lValue->returnType.type != rValue->returnType.type)
            {
                std::string error;
                if(auto castCtx = resolveCast(rValue.release(), lValue->returnType, error))
                    rValue.reset(castCtx);
                else
                    recordError(ctx->rValue, error);
            }
            assignmentCtx->setArgs(lValue.release(), rValue.release());
            popDoc(assignmentCtx);
            RETURN_STMT(assignmentCtx);
        }

        std::any visitRefAssignment(braneParser::RefAssignmentContext* ctx) override
        {
            STMT_ASSERT_EXISTS(ctx->lValue, "lValue expected");
            STMT_ASSERT_EXISTS(ctx->rValue, "rValue expected");
            auto assignmentCtx = new RefAssignmentContext{};
            initDoc(assignmentCtx, ctx);
            auto lValue = asExpr(visit(ctx->lValue));
            assert(lValue);
            if(!lValue->returnType.isRef)
                recordError(ctx->lValue, "Expression is not a reference!");
            if(!lValue->returnType.isLValue)
                recordError(ctx->lValue, "Expression is not an lValue!");
            if(lValue->returnType.isConst)
                recordError(ctx->lValue, "Can not modify a constant value!");

            auto rValue = asExpr(visit(ctx->rValue));
            assert(rValue);
            if(!rValue->returnType.isRef || rValue->returnType.isLValue)
                recordError(ctx->rValue, "Can not reference a temporary value!");
            if(lValue->returnType.type != rValue->returnType.type)
                recordError(ctx, "Can not reference a value of different type!");
            assignmentCtx->setArgs(lValue.release(), rValue.release());
            popDoc(assignmentCtx);
            RETURN_STMT(assignmentCtx);
        }

        std::any visitConstBool(braneParser::ConstBoolContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->BOOL(), "constant missing");
            auto constCtx = new ConstBoolContext{};
            initDoc(constCtx, ctx);
            constCtx->value = (ctx->getText() == "true");
            popDoc(constCtx);
            RETURN_EXPR(constCtx);
        }

        std::any visitConstInt(braneParser::ConstIntContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->INT(), "constant missing");
            auto constCtx = new ConstIntContext{};
            initDoc(constCtx, ctx);
            constCtx->value = std::stoi(ctx->getText());
            popDoc(constCtx);
            RETURN_EXPR(constCtx);
        }

        std::any visitConstFloat(braneParser::ConstFloatContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->FLOAT(), "constant missing");
            auto constCtx = new ConstFloatContext{};
            initDoc(constCtx, ctx);
            constCtx->value = std::stof(ctx->getText());
            popDoc(constCtx);
            RETURN_EXPR(constCtx);
        }

        std::any visitConstChar(braneParser::ConstCharContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->CHAR(), "constant missing");
            auto constCtx = new ConstCharContext{};
            initDoc(constCtx, ctx);
            constCtx->value = ctx->getText()[1];
            popDoc(constCtx);
            RETURN_EXPR(constCtx);
        }

        std::any visitConstString(braneParser::ConstStringContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->STRING(), "constant missing");
            auto constCtx = new ConstStringContext{};
            initDoc(constCtx, ctx);
            constCtx->returnType.type.structCtx =
                dynamic_cast<StructContext*>(getIdentifierContext("string")->as<LibrarySet>()->findIdentifier(
                    "string", IDSearchOptions_ChildrenOnly));
            if(!constCtx->returnType.type.structCtx)
                recordError(ctx, "To use the string type, the BraneScript library must be imported.");
            constCtx->value = ctx->getText();
            constCtx->value = {constCtx->value.data() + 1, constCtx->value.size() - 2};
            popDoc(constCtx);
            RETURN_EXPR(constCtx);
        }

        std::any visitSizeOfType(braneParser::SizeOfTypeContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->t, "type expected");
            auto value = std::any_cast<ValueContext>(visitType(ctx->t));
            auto constCtx = new TypeSizeContext{value};
            initDoc(constCtx, ctx);
            popDoc(constCtx);
            RETURN_EXPR(constCtx);
        };

        std::any visitSizeOfPack(braneParser::SizeOfPackContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->id, "expression missing");
            auto constCtx = new ConstIntContext{};
            initDoc(constCtx, ctx);
            constCtx->value = 1;
            popDoc(constCtx);
            if(!_instantiatingTemplate)
            {
                recordError(ctx, "sizeof... can only be used inside templates");
                RETURN_EXPR(constCtx);
            }
            std::string id = safeGetText(ctx->id);
            auto* argInstance = getTemplateArg(id);
            if(argInstance)
            {
                recordError(ctx, id + " is not a template parameter!");
                RETURN_EXPR(constCtx);
            }
            auto* pack = dynamic_cast<TypedefPackArgContext*>(argInstance);
            if(!pack)
            {
                recordError(ctx, id + " is not a type pack!");
                RETURN_EXPR(constCtx);
            }
            constCtx->value = pack->values.size();
            popDoc(constCtx);
            RETURN_EXPR(constCtx);
        };

        std::any visitParen(braneParser::ParenContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->expression(), "expression expected");
            return visit(ctx->expression());
        }

        std::any visitCast(braneParser::CastContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->type(), "type expected");
            EXPR_ASSERT_EXISTS(ctx->expression(), "expression expected");

            auto returnType = std::any_cast<ValueContext>(visitType(ctx->type()));
            std::string error;
            if(auto* castCtx = resolveCast(asExpr(visit(ctx->expression())).release(), returnType, error))
            {
                initDoc(castCtx, ctx);
                popDoc(castCtx);
                RETURN_EXPR(castCtx);
            }
            else
                recordError(ctx, error);
            return NULL_EXPR;
        }

        std::any visitAddsub(braneParser::AddsubContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->left, "expression expected");
            EXPR_ASSERT_EXISTS(ctx->opr, "operator expected");
            EXPR_ASSERT_EXISTS(ctx->right, "expression expected");

            auto left = asExpr(visit(ctx->left));
            auto right = asExpr(visit(ctx->right));
            std::string op = ctx->opr->getText();

            if(NativeArithmeticContext::validArithmetic(left->returnType, right->returnType))
            {
                std::string err;
                castSame(left, right, err);
                RETURN_EXPR(new NativeArithmeticContext((op == "+") ? NativeArithmeticContext::ADD
                                                                    : NativeArithmeticContext::SUB,
                                                        left.release(),
                                                        right.release()));
            }

            std::string error;
            if(auto callCtx = resolveOperator(op, error, std::move(left), std::move(right)))
               RETURN_EXPR(callCtx);
            recordError(ctx->opr, error);
            return NULL_EXPR;
        }

        std::any visitMuldiv(braneParser::MuldivContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->left, "expression expected");
            EXPR_ASSERT_EXISTS(ctx->opr, "operator expected");
            EXPR_ASSERT_EXISTS(ctx->right, "expression expected");

            auto left = asExpr(visit(ctx->left));
            auto right = asExpr(visit(ctx->right));
            std::string op = ctx->opr->getText();

            if(NativeArithmeticContext::validArithmetic(left->returnType, right->returnType))
            {
                std::string err;
                castSame(left, right, err);
                RETURN_EXPR(new NativeArithmeticContext((op == "*") ? NativeArithmeticContext::MUL
                                                                    : NativeArithmeticContext::DIV,
                                                        left.release(),
                                                        right.release()));
            }

            std::string error;
            if(auto callCtx = resolveOperator(op, error, std::move(left), std::move(right)))
                RETURN_EXPR(callCtx);
            recordError(ctx->opr, error);
            return NULL_EXPR;
        }

        std::any visitLogic(braneParser::LogicContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->left, "expression expected");
            EXPR_ASSERT_EXISTS(ctx->opr, "operator expected");
            EXPR_ASSERT_EXISTS(ctx->right, "expression expected");

            auto left = asExpr(visit(ctx->left));
            auto right = asExpr(visit(ctx->right));
            assert(false); // TODO implement this

            std::string error;
            if(auto callCtx = resolveOperator("&&", error, std::move(left), std::move(right)))
                RETURN_EXPR(callCtx);
            recordError(ctx->opr, error);
            return NULL_EXPR;
        }

        std::any visitComparison(braneParser::ComparisonContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->left, "expression expected");
            EXPR_ASSERT_EXISTS(ctx->opr, "operator expected");
            EXPR_ASSERT_EXISTS(ctx->right, "expression expected");

            auto left = asExpr(visit(ctx->left));
            auto right = asExpr(visit(ctx->right));
            std::string opText = ctx->opr->getText();

            if(NativeCompareContext::validCompare(left->returnType, right->returnType))
            {
                NativeCompareContext::Operation op;
                if(opText == "==")
                    op = NativeCompareContext::EQ;
                else if(opText == "!=")
                    op = NativeCompareContext::NEQ;
                else if(opText == ">")
                    op = NativeCompareContext::GT;
                else if(opText == ">=")
                    op = NativeCompareContext::GE;
                else if(opText == "<")
                    op = NativeCompareContext::LT;
                else if(opText == "<=")
                    op = NativeCompareContext::LE;
                else
                    assert(false);

                std::string err;
                castSame(left, right, err);
                RETURN_EXPR(new NativeCompareContext(op, left.release(), right.release()));
            }

            std::string error;
            if(auto callCtx = resolveOperator(opText, error, std::move(left), std::move(right)))
                RETURN_EXPR(callCtx);
            recordError(ctx->opr, error);
            return NULL_EXPR;
        }

        std::any visitIndexAccess(braneParser::IndexAccessContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->base, "expression expected");
            EXPR_ASSERT_EXISTS(ctx->arg, "expression expected");
            auto left = asExpr(visit(ctx->base));
            auto right = asExpr(visit(ctx->arg));

            std::string error;
            if(auto callCtx = resolveOperator("[]", error, std::move(left), std::move(right)))
                RETURN_EXPR(callCtx);
            recordError(ctx, error);
            return NULL_EXPR;
        }

        std::any visitId(braneParser::IdContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->scopedID(), "identifier expected");
            auto node = getIdentifierContext(ctx->scopedID());

            if(!node)
            {
                std::string id = ctx->getText();
                if(_instantiatingTemplate)
                {
                    auto* tempArg = getTemplateArg(id);
                    if(auto* tempValueArg = dynamic_cast<ValueArgContext*>(tempArg))
                        RETURN_EXPR(tempValueArg->value->deepCopy([](auto _) { return _; }));
                }
                recordError(ctx, "\"" + id + "\" is not an identifier!");
                return NULL_EXPR;
            }

            if(auto valueContext = node->as<LabeledValueContext>())
            {
                // Do we implicitly need to reference this?
                if(node->parent && node->parent->is<StructContext>())
                {
                    auto memberAccess = new MemberAccessContext{};
                    initDoc(memberAccess, ctx);
                    auto thisRef =
                        lastNode()->findIdentifier("this", IDSearchOptions_ParentsOnly)->as<LabeledValueContext>();
                    assert(thisRef);
                    auto valueAccess = new LabeledValueReferenceContext{*thisRef};
                    initDoc(valueAccess, ctx);

                    memberAccess->baseExpression.reset(valueAccess);

                    auto parent = node->parent->as<StructContext>();
                    memberAccess->member = 0;
                    for(auto& m : parent->variables)
                    {
                        if(m->identifier.text == valueContext->identifier.text)
                            break;
                        memberAccess->member++;
                    }

                    assert(memberAccess->member < parent->variables.size());
                    memberAccess->returnType = *parent->variables[memberAccess->member];

                    popDoc(valueAccess);
                    popDoc(memberAccess);
                    RETURN_EXPR(memberAccess);
                }

                auto valueAccess = new LabeledValueReferenceContext{*node->as<LabeledValueContext>()};
                initDoc(valueAccess, ctx);
                popDoc(valueAccess);
                RETURN_EXPR(valueAccess);
            }
            if(auto funcContext = node->as<FunctionContext>())
            {


                braneParser::ScopedIDContext* idNode = ctx->scopedID();
                braneParser::ScopedIDContext* scope = nullptr;
                while(idNode->child)
                {
                    scope = idNode;
                    idNode = idNode->child;
                }

                //If this function is a template, getValueContext will have already instantiated it
                if(idNode->template_)
                {
                    auto funcOverrides = new FunctionOverridesContext({funcContext});
                    initDoc(funcOverrides, ctx);
                    popDoc(funcOverrides);
                    RETURN_EXPR(funcOverrides);
                }

                DocumentContext* scopeContext = nullptr;
                if(scope)
                {
                    scope->child = nullptr;
                    scopeContext = getIdentifierContext(ctx->scopedID());
                    scope->child = idNode;
                    if(!scopeContext)
                    {
                        recordError(ctx, "Could not find scope \"" + scope->getText() + "\"");
                        return NULL_EXPR;
                    }
                }
                auto funcOverrides = getFunctionOverrides(idNode->id->getText(), scopeContext);
                if(!funcOverrides->overrides.empty())
                    RETURN_EXPR(funcOverrides);
                delete funcOverrides;
            }



            recordError(ctx, ctx->getText() + " is not an expression!");
            return NULL_EXPR;
        }

        std::any visitMemberAccess(braneParser::MemberAccessContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->base, "expected base expression");
            EXPR_ASSERT_EXISTS(ctx->member, "expected member identifier");

            auto base = asExpr(visit(ctx->base));
            if(base->returnType.type.storageType != ValueType::Struct)
            {
                recordError(ctx, "Cannot access members of non-struct objects");
                return NULL_EXPR;
            }

            auto& typeName = base->returnType.type.identifier;
            auto type = base->returnType.type.structCtx;
            assert(type);

            std::string memberName = safeGetText(ctx->member);
            auto memberOverrides = getFunctionOverrides(memberName, type, ctx->template_);
            if(!memberOverrides->overrides.empty())
            {
                memberOverrides->thisRef = std::move(base);
                RETURN_EXPR(memberOverrides);
            }

            auto accessCtx = new MemberAccessContext{};
            accessCtx->baseExpression = std::move(base);
            initDoc(accessCtx, ctx);

            accessCtx->member = 0;
            for(auto& m : type->variables)
            {
                if(m->identifier.text == memberName)
                    break;
                accessCtx->member++;
            }
            if(accessCtx->member == type->variables.size())
                recordError(ctx->member, "Struct " + typeName + " does not have a member " + memberName);
            else
            {
                accessCtx->returnType.type = type->variables[accessCtx->member]->type;
                accessCtx->returnType.isRef = accessCtx->returnType.type.storageType == ValueType::Struct;
                accessCtx->returnType.isConst = accessCtx->baseExpression->returnType.isConst;
                accessCtx->returnType.isLValue = accessCtx->baseExpression->returnType.isLValue;
            }

            popDoc(accessCtx);
            RETURN_EXPR(accessCtx);
        }

        std::vector<std::unique_ptr<ExpressionContext>> populateFunctionArgs(braneParser::ArgumentPackContext* ctx)
        {
            std::vector<std::unique_ptr<ExpressionContext>> args;
            for(auto& item : ctx->argumentPackItem())
            {
                if(item->expr)
                {
                    args.push_back(asExpr(visit(item->expr)));
                    continue;
                }

                if(!_instantiatingTemplate)
                {
                    recordError(item, "argument packs may only be used in templates!");
                    continue;
                }

                std::string packID = safeGetText(item->packID);
                auto* argPack = dynamic_cast<ArgPackInstanceContext*>(lastNode()->findIdentifier(packID));
                if(!argPack)
                {
                    recordError(item->packID, packID + " is not an argument pack!");
                    continue;
                }

                for(auto& value : argPack->values)
                    args.emplace_back(new LabeledValueReferenceContext{*value});
            }
            return args;
        }

        std::any visitFunctionCall(braneParser::FunctionCallContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->expression(), "expected expression");
            auto callCtx = new FunctionCallContext{};
            initDoc(callCtx, ctx);
            callCtx->arguments = populateFunctionArgs(ctx->argumentPack());

            auto source = asExpr(visit(ctx->expression()));
            if(auto overridesCtx = source->as<FunctionOverridesContext>())
            {
                bool isMember = false;
                if(overridesCtx->thisRef)
                {
                    callCtx->arguments.insert(callCtx->arguments.begin(), std::move(overridesCtx->thisRef));
                    isMember = true;
                }
                std::vector<ValueContext> argTypes;
                for(auto& arg : callCtx->arguments)
                    argTypes.push_back(arg->returnType);
                callCtx->function = overridesCtx->bestMatch(
                    argTypes,
                    [this](const ValueContext& a, const ValueContext& b) { return implicitCastViable(a, b); },
                    _enforceConstexpr ? FunctionOverridesContext::Constexpr : FunctionOverridesContext::None);

                if(!callCtx->function && !isMember && getLast<StructContext>())
                {
                    auto& structCtx = *getLast<StructContext>();
                    auto* thisRef =
                        lastNode()->findIdentifier("this", IDSearchOptions_ParentsOnly)->as<LabeledValueContext>();
                    auto valueAccess = new LabeledValueReferenceContext{*thisRef};
                    initDoc(valueAccess, ctx);
                    popDoc(valueAccess);

                    callCtx->arguments.emplace(callCtx->arguments.begin(), valueAccess);
                    argTypes.emplace(argTypes.begin(), valueAccess->returnType);

                    callCtx->function = overridesCtx->bestMatch(
                        argTypes,
                        [this](const ValueContext& a, const ValueContext& b) { return implicitCastViable(a, b); },
                        _enforceConstexpr ? FunctionOverridesContext::Constexpr : FunctionOverridesContext::None);
                }

                if(!callCtx->function)
                {
                    std::string error = "Could not find override of function \"" + source->longId();
                    error += "\" with arguments: ";
                    for(auto& arg : argTypes)
                        error += arg.signature() + ", ";
                    if(!overridesCtx->overrides.empty())
                    {
                        error += "\nDid you mean to use one of these overrides?\n-----\n";
                        for(auto o : overridesCtx->overrides)
                            error += functionSig(o->longId(), o->arguments) + "\n";
                        error += "-----";
                        if(_enforceConstexpr)
                            error += "\nVerify the functions you call in a constexpr scope are also constexpr.";
                    }
                    recordError(ctx->expression(), error);
                    popDoc(callCtx);
                    RETURN_EXPR(callCtx);
                }

                callCtx->returnType = callCtx->function->returnType;
                if(isLocal(callCtx->function))
                    callTree.addDependency(lastNode()->getParent<FunctionContext>(), callCtx->function);

                for(int i = 0; i < callCtx->arguments.size(); ++i)
                {
                    if(callCtx->arguments[i]->returnType.sameBaseType(*callCtx->function->arguments[i]))
                        continue;

                    // Find the cast operator, should never return false ideally, but I can see configuration bugs
                    // triggering this in the future.
                    std::string error;
                    auto* arg = callCtx->arguments[i].release();
                    if(auto* castCtx = resolveCast(arg, *callCtx->function->arguments[i], error))
                        callCtx->arguments[i].reset(castCtx);
                    else
                    {
                        callCtx->arguments[i].reset(arg);
                        recordError(callCtx->arguments[i]->range, error);
                        popDoc(callCtx);
                        RETURN_EXPR(callCtx);
                    }
                }
            }

            // TODO call function pointers here

            popDoc(callCtx);
            RETURN_EXPR(callCtx);
        }

        std::any visitProgram(braneParser::ProgramContext* ctx) override
        {
            visitChildren(ctx);
            if(globals.empty())
                return {};

            LabeledNodeList<LabeledValueContext> args = {};
            // Make constructor
            {
                auto func = getFunctionNode("_construct", args);
                initDoc(func, ctx->start);
                popDoc(func);
                func->body = std::make_unique<ScopeContext>();

                size_t varIndex = 0;
                for(auto var : globals)
                {
                    if(var->type.storageType == ValueType::Struct)
                    {
                        auto globalRef = new LabeledValueReferenceContext{*var};

                        auto constructCall = new FunctionCallContext{};
                        constructCall->arguments.emplace_back(globalRef);
                        constructCall->function = var->type.structCtx->constructor;
                        if(!constructCall->function)
                            recordError(ctx->start,
                                        "Could not find constructor for struct \"" + var->type.structCtx->longId() +
                                            "\"");
                        if(isLocal(constructCall->function))
                            callTree.addDependency(func, constructCall->function);
                        func->body->expressions.emplace_back(constructCall);
                    }
                    varIndex++;
                }
                callTree.addFunction(func);
            }
            // Make destructor
            {
                auto func = getFunctionNode("_destruct", args);
                initDoc(func, ctx->start);
                popDoc(func);
                func->body = std::make_unique<ScopeContext>();

                size_t varIndex = 0;
                for(auto var : globals)
                {
                    if(var->type.storageType == ValueType::Struct)
                    {
                        auto globalRef = new LabeledValueReferenceContext{*var};

                        auto constructCall = new FunctionCallContext{};
                        constructCall->arguments.emplace_back(globalRef);
                        constructCall->function = var->type.structCtx->destructor;
                        if(!constructCall->function)
                            recordError(ctx->start,
                                        "Could not find destructor for struct \"" + var->type.structCtx->longId() +
                                            "\"");
                        if(isLocal(constructCall->function))
                            callTree.addDependency(func, constructCall->function);
                        func->body->expressions.emplace_back(constructCall);
                    }
                    varIndex++;
                }
                callTree.addFunction(func);
            }
            return {};
        }

        void recordError(TextRange range, const std::string& message) { _result.errors.push_back({range, message}); }

        void recordError(antlr4::Token* token, const std::string& message) { recordError(toRange(token), message); }

        void recordError(antlr4::ParserRuleContext* ctx, const std::string& message)
        {
            recordError(toRange(ctx), message);
        }

        DocumentContext* lastNode() { return _documentContext.top(); }

        template<typename T>
        T* getLast()
        {
            if(lastNode()->is<T>())
                return lastNode()->as<T>();
            return lastNode()->getParent<T>();
        }

        bool analyze()
        {
            _result.scriptContext->range = {0, _result.document.size()};
            _result.version++;
            _result.errors.clear();
            _result.warnings.clear();

            /* To avoid invalid pointers being left over, we just remove all exports this script has defined in the past
             * This shouldn't affect script analyzation since inter-script linking is still recursively possible through
             * the script context */

            std::string document;
            _rawText = &document;

            if(_extractOnlyIdentifiers)
            {
                for(auto& lib : _result.scriptContext->exports)
                    _analyzer.deregisterLibrary(lib.second.get());
                _result.scriptContext->imports.clear();
            }
            else
            {
                // Import template text into document so that we can read it
                for(auto& lib : _result.scriptContext->imports)
                    _analyzer.appendTemplateHeaders(lib.second->library, _result.scriptContext.get(), document);
                // TODO figure out a clean way to associate sections of the header with external files, instead of
                // returning negative line numbers in errors
                document += '\n';
                for(char c : document)
                    _headerSize += c == '\n';
            }

            std::cout << "template headers:\n" << document << std::endl;

            document += _result.document;

            antlr4::ANTLRInputStream input(document);

            LexerErrorListener lexErrListener(*this);
            braneLexer lexer(&input);
            lexer.removeErrorListeners();
            lexer.addErrorListener(&lexErrListener);
            antlr4::CommonTokenStream tokens(&lexer);

            ParserErrorListener parserErrListener(*this);
            braneParser parser(&tokens);
            parser.removeErrorListeners();
            parser.addErrorListener(&parserErrListener);

            _documentContext.push(_result.scriptContext.get());
            visit(parser.program());
            _documentContext.pop();
            pruneNodes(_result.scriptContext->globals);
            pruneNodes(_result.scriptContext->structs);
            pruneNodes(_result.scriptContext->functions);
            pruneNodes(_result.scriptContext->exports);
            _result.scriptContext->callOrder.clear();
            if(!_extractOnlyIdentifiers && !callTree.resolveCallOrder(_result.scriptContext->callOrder))
                recordError(TextRange{}, "Unable to resolve function call order due to circular function calls");

            return _result.errors.empty();
        }
    };

    StaticAnalyzer::StaticAnalyzer() { addWorkspace("include", true); }

    bool StaticAnalyzer::isLoaded(const std::string& path) { return _analyzationContexts.contains(path); }

    std::string readDocument(const std::string& path)
    {
        std::ifstream f(path, std::ios::ate | std::ios::binary);
        if(!f.is_open())
            throw std::runtime_error("Could not load " + path + "!");
        std::string document;
        document.resize(f.tellg());
        f.seekg(0);
        f.read(document.data(), document.size());
        f.close();
        return std::move(document);
    }

    void StaticAnalyzer::load(const std::string& path, bool cacheDocument)
    {
        load(path, readDocument(path), cacheDocument);
    }

    void StaticAnalyzer::load(const std::string& path, std::string document, bool cacheDocument)
    {
        if(!_analyzationContexts.contains(path))
        {
            _analyzationContexts.insert({path, std::make_unique<AnalyzationContext>()});
            _analyzationContexts.at(path)->source = path;
        }
        auto& context = _analyzationContexts.at(path);
        std::scoped_lock lock(context->lock);
        context->document = std::move(document);
        if(!context->scriptContext)
            context->scriptContext = std::make_unique<ScriptContext>();
        context->complete = false;
        context->scriptContext->id = path;

        Analyzer(*this, *context, true, false).analyze();

        if(!cacheDocument)
            context->document.clear();
    }

    void StaticAnalyzer::reload(const std::string& path)
    {
        assert(_analyzationContexts.contains(path));
        auto& context = _analyzationContexts.at(path);
        std::scoped_lock lock(context->lock);

        bool cacheDocument = !context->document.empty();
        if(!cacheDocument)
            context->document = readDocument(path);

        Analyzer(*this, *context, true, false).analyze();
        context->complete = false;

        if(!cacheDocument)
            context->document.clear();
    }

    bool StaticAnalyzer::validate(const std::string& path, bool allowUnsafe)
    {
        assert(_analyzationContexts.contains(path));
        auto& context = _analyzationContexts.at(path);
        std::scoped_lock lock(context->lock);
        Analyzer(*this, *context, false, allowUnsafe).analyze();
        context->complete = true;
        return context->errors.empty();
    }

    StaticAnalyzer::AnalyzationContext* StaticAnalyzer::getCtx(const std::string& path)
    {
        return _analyzationContexts.at(path).get();
    }

    void StaticAnalyzer::addWorkspace(const std::string& path, bool allowUnsafe)
    {
        std::cout << "Loading workspace " << path << std::endl;
        assert(std::filesystem::exists(path));
        for(auto& entry : std::filesystem::recursive_directory_iterator(
                path, std::filesystem::directory_options::skip_permission_denied))
        {
            assert(std::filesystem::exists(entry));
            if(!entry.is_regular_file())
                continue;
            if(entry.path().extension() != ".bs")
                continue;
            load(entry.path().generic_string(), false);
            auto& context = _analyzationContexts.at(entry.path().generic_string());
            if(!context->errors.empty())
            {
                std::cout << "Errors in loaded file " << entry.path().generic_string() << std::endl;
                for(auto& err : context->errors)
                    std::cout << "(" << err.range.start.line << ", " << err.range.start.charPos << ") " << err.message
                              << std::endl;
            }
        }
        _workspaceRoots.push_back(path);
    }

    void StaticAnalyzer::registerLibrary(LibraryContext* lib)
    {
        if(!_libraries.contains(lib->identifier.text))
            _libraries.insert({lib->identifier.text, std::make_unique<LibrarySet>()});
        auto& libSet = _libraries.at(lib->identifier.text);
        if(libSet->exports.contains(lib))
            return;
        libSet->exports.insert(lib);
    }

    void StaticAnalyzer::deregisterLibrary(LibraryContext* lib)
    {
        auto libSet = _libraries.find(lib->identifier.text);
        if(libSet == _libraries.end())
            return;
        if(libSet->second->exports.contains(lib))
            libSet->second->exports.erase(lib);
        if(libSet->second->exports.empty())
            _libraries.erase(libSet);
    }

    LibrarySet* StaticAnalyzer::getLibrary(const std::string& id)
    {
        auto libSet = _libraries.find(id);
        if(libSet == _libraries.end())
            return nullptr;
        return (libSet->second->exports.empty()) ? nullptr : libSet->second.get();
    }

    void StaticAnalyzer::appendTemplateHeaders(const std::string& lib,
                                               const ScriptContext* currentDocument,
                                               std::string& stream)
    {
        auto libSet = _libraries.find(lib);
        if(libSet == _libraries.end())
            return;

        for(auto& lib : libSet->second->exports)
        {
            if(lib->getParent<ScriptContext>() == currentDocument)
                continue;
            if(lib->templateDefinitions.empty())
                continue;
            stream += "export as \"" + lib->identifier.text + "\"{";
            for(auto& t : lib->templateDefinitions)
                stream += t.second;
            stream += "}\n";
        }
    }

    void StaticAnalyzer::setConstexprEvaluator(ConstexprEvaluator* evaluator) { _evaluator = evaluator; }

    ConstexprEvaluator* StaticAnalyzer::constexprEvaluator() const { return _evaluator; }

    bool StaticAnalyzer::isValid(const std::string& path)
    {
        if(!_analyzationContexts.contains(path))
            return false;
        return _analyzationContexts.at(path)->errors.empty();
    }

    IRScript StaticAnalyzer::compile(const std::string& path)
    {
        assert(isValid(path));
        assert(_analyzationContexts.at(path)->complete); // validate() must be called before compile()
        llvm::LLVMContext llvmContext;
        return _analyzationContexts.at(path)->scriptContext->compile(&llvmContext);
    }
} // namespace BraneScript
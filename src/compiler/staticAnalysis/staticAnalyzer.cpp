//
// Created by wirewhiz on 1/23/23.
//

#include "staticAnalyzer.h"
#include <typeinfo>
#include "antlr4/braneBaseVisitor.h"
#include "antlr4/braneLexer.h"
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
        bool _extractOnlyIdentifiers;

        bool _functionHasReturn = false;

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

        using TemplateArgs = robin_hood::unordered_map<std::string, std::unique_ptr<TemplateArgContext>>;


        robin_hood::unordered_map<std::string, std::vector<std::unique_ptr<TemplateHandle>>> _registeredTemplates;
        std::list<TemplateArgs> _templateArgs;
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
                return {};
            return TextRange{token->getLine() - _headerSize - 1,
                             token->getCharPositionInLine(),
                             token->getLine() - _headerSize - 1,
                             token->getCharPositionInLine() + (token->getStopIndex() - token->getStartIndex()) + 1};
        };

        TextRange toRange(antlr4::ParserRuleContext* ctx)
        {
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

        std::string templateArgsToString(const std::vector<ValueContext>& args)
        {
            std::string str = "<";
            for(int i = 0; i < args.size(); ++i)
            {
                str += args[i].signature();
                if(i != args.size() - 1)
                    str += ",";
            }
            str += ">";
            return str;
        }

        std::string templateDefToString(braneParser::TemplateDefContext* tempDef)
        {
            std::vector<ValueContext> args;
            auto argDefs = std::any_cast<std::vector<TemplateDefArgumentContext*>>(visitTemplateDef(tempDef));
            for(auto& arg : argDefs)
            {
                auto* argInstance = getTemplateArg(arg->identifier);
                assert(argInstance);
                if(auto typeArg = dynamic_cast<TemplateTypeArgContext*>(argInstance))
                    args.push_back(typeArg->value);
                if(auto typePackArg = dynamic_cast<TemplateTypePackArgContext*>(argInstance))
                {
                    for(auto& value : typePackArg->values)
                        args.push_back(value);
                }

                delete arg;
            }
            return templateArgsToString(args);
        }

        std::string functionSig(const std::string& identifier, const std::vector<ValueContext> args)
        {
            std::string sig = identifier + "(";
            for(int i = 0; i < args.size(); ++i)
            {
                sig += args[i].signature();
                if(i != args.size() - 1)
                    sig += ", ";
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
                    sig += ", ";
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
                if(!imp.alias.empty())
                    continue;
                auto lib = _analyzer.getLibrary(imp.library);
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
                if(identifier == alias.alias)
                    return _analyzer.getLibrary(alias.library);
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
                auto args = std::any_cast<std::vector<ValueContext>>(visitTemplateArgs(ctx->template_));
                if(parent)
                    id = parent->longId() + "::" + id;
                found = getTemplateInstance(id, args);
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

            if(auto* sCtx = dynamic_cast<StructContext*>(getIdentifierContext(ctx)))
            {
                output.identifier = sCtx->longId();
                output.structDef = sCtx;
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
            }

            return output;
        }

        bool implicitCastViable(const ValueContext& current, const ValueContext& target)
        {
            return current.type.isScalar() && target.type.isScalar();
        }

        uint32_t calculateCastCost(const ValueContext& current, const ValueContext& target)
        {
            /* Costs subject to change, I just threw random values here. Generally I went with lower costs on things
             * that preserve data, and much higher costs on things that have a chance of loosing data.
             */

            uint32_t cost = 0;
            // Very minor cost to dereferencing, since we want to favor references
            if(current.isRef && !target.isRef)
                cost += 1;
            // Prefer up-casting to down-casting
            if(current.type.size() < target.type.size())
                cost += 2;
            else if(current.type.size() > target.type.size())
                cost += 20;

            // Prefer casting from unsigned integers to signed integers over casts to floats, but prefer casting signed
            // ints to floats
            if(current.type.isUnsigned() && !target.type.isUnsigned())
                cost += 7;
            else if(!current.type.isUnsigned() && target.type.isUnsigned())
                cost += 15;
            if(current.type.isInt() && target.type.isFloat())
                cost += 7;
            // Avoid casts from floats to ints like the plague (when implicit)
            if(current.type.isFloat() && target.type.isInt())
                cost += 30;
            return cost;
        }

        struct FunctionCompareResult
        {
            bool argsMatch = false;
            uint8_t castCount = 0;
            uint16_t castCost = 0;
        };

        FunctionCompareResult compareFunctionArgs(const FunctionContext* f, const std::vector<ValueContext>& args)
        {
            FunctionCompareResult result;
            if(f->arguments.size() != args.size())
                return result;
            result.argsMatch = true;
            for(size_t i = 0; i < args.size(); ++i)
            {
                if(f->arguments[i]->type != args[i].type)
                {
                    if(!implicitCastViable(*f->arguments[i], args[i]))
                    {
                        result.argsMatch = false;
                        break;
                    }
                    result.castCount++;
                    result.castCost += calculateCastCost(args[i], *f->arguments[i]);
                }
                // Honor constness
                if(args[i].isConst && f->arguments[i]->isRef && !f->arguments[i]->isConst)
                {
                    result.argsMatch = false;
                    break;
                }
            }
            return result;
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

        bool resolveFunctionCall(braneParser::ScopedIDContext* idCtx,
                                 FunctionCallContext* context,
                                 std::string& error,
                                 bool autoCast = true)
        {
            auto functionID = getLastScopedID(idCtx);
            std::string name = safeGetText(functionID.second->id);
            if(idCtx->child && !functionID.first)
            {
                error += "Namespace could not be found";
                return false;
            }
            return resolveFunctionCall(name, context, error, functionID.first, functionID.second->template_, autoCast);
        }

        bool resolveFunctionCall(const std::string& name,
                                 FunctionCallContext* context,
                                 std::string& error,
                                 DocumentContext* scope = nullptr,
                                 braneParser::TemplateArgsContext* tempArgsCtx = nullptr,
                                 bool autoCast = true)
        {

            std::list<FunctionContext*> overrides;

            if(tempArgsCtx)
            {
                std::string longID = name;
                if(scope)
                    longID = scope->longId() + "::" + name;
                auto tempArgs = std::any_cast<std::vector<ValueContext>>(visitTemplateArgs(tempArgsCtx));

                auto tempFunction =
                    dynamic_cast<FunctionContext*>(getTemplateInstance(longID, tempArgs, TemplateHandle::Function));
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
                        if(!imp.alias.empty())
                            continue;
                        auto lib = _analyzer.getLibrary(imp.library);
                        if(!lib)
                            continue;
                        lib->getFunction(name, overrides, IDSearchOptions_ChildrenOnly);
                    }
                }

                // this is where automatically finding templates without explicit arguments would go
            }

            /* We want to find the best match with the lowest amount of implicit casts. So we store the cast count for
             * each candidate function and try to find the closest one. Cast cost is a measure of the desirability of
             * casts the casts. For instance a cast from uint32 to uint64 is more desirable than a cast from uint32_t to
             * a float.
             * */
            uint16_t castCount = -1;
            uint32_t castCost = -1;
            FunctionContext* bestMatch = nullptr;

            std::vector<ValueContext> args;
            for(auto& arg : context->arguments)
                args.push_back(arg->returnType);
            for(auto f : overrides)
            {
                auto result = compareFunctionArgs(f, args);
                if(!result.argsMatch)
                    continue;
                // This is the best match if it requires fewer casts or has the same amount and just costs lest
                if(result.castCount < castCount || (result.castCount == castCount && result.castCost < castCost))
                {
                    bestMatch = f;
                    castCount = result.castCount;
                    castCost = result.castCost;
                }
            }

            if(!bestMatch)
            {
                error += "Could not find override of function \"" + (scope ? scope->longId() + "::" + name : name) +
                         "\" with arguments: ";
                for(auto& arg : args)
                    error += arg.signature() + ", ";
                if(!overrides.empty())
                {
                    error += "\nDid you mean to use one of these overrides?\n-----\n";
                    for(auto o : overrides)
                        error += functionSig(o->longId(), o->arguments) + "\n";
                    error += "-----";
                }
                return false;
            }

            context->function = bestMatch;
            context->returnType = bestMatch->returnType;

            if(castCount)
            {
                for(size_t i = 0; i < args.size(); ++i)
                {
                    if(bestMatch->arguments[i]->type == args[i].type)
                        continue;
                    auto* castCtx = new FunctionCallContext{};
                    castCtx->arguments.push_back(std::unique_ptr<ExpressionContext>(context->arguments[i].release()));
                    context->arguments[i].reset(castCtx);

                    // Find the cast operator, should never return false ideally, but I can see configuration bugs
                    // triggering this in the future.
                    if(!resolveCast(castCtx, bestMatch->arguments[i]->type, error))
                        return false;
                }
            }

            return true;
        }

        bool resolveCast(FunctionCallContext* context, const TypeContext& targetType, std::string& error)
        {
            assert(context->arguments.size() == 1);
            /* We want to insert the error at the position that would make the most sense, which would be right after
             * the last one before a cast was attempted, but not after we get the error about the casting operator not
             * being found.
             */
            size_t errorPos = error.size();
            bool result = resolveFunctionCall("opr " + targetType.identifier, context, error);
            if(!result)
            {
                std::string castError = "Could not cast " + context->arguments[0]->returnType.type.identifier + " to " +
                                        targetType.identifier + "!\n";
                error.insert(error.begin() + errorPos, castError.begin(), castError.end());
            }

            return result;
        }

      public:
        Analyzer(StaticAnalyzer& analyzer, StaticAnalyzer::AnalyzationContext& result, bool extractOnlyIdentifiers)
            : _analyzer(analyzer), _result(result), _extractOnlyIdentifiers(extractOnlyIdentifiers){};

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
            arg->type = ctx->isPack ? TemplateDefArgumentContext::ValueTypePack : TemplateDefArgumentContext::ValueType;
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
            std::vector<ValueContext> args;
            for(auto* arg : ctx->templateArg())
            {
                if(auto* typeArg = dynamic_cast<braneParser::TemplateTypeArgContext*>(arg))
                {
                    args.push_back(std::any_cast<ValueContext>(visit(typeArg)));
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
                    auto* pack = dynamic_cast<TemplateTypePackArgContext*>(argInstance);
                    if(!pack)
                    {
                        recordError(arg, packID + " is not a pack argument!");
                        continue;
                    }
                    for(auto& value : pack->values)
                        args.push_back(value);
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
                    if(auto* tempType = dynamic_cast<TemplateTypeArgContext*>(arg))
                        output = tempType->value;
                    else if(auto* tempTypePack = dynamic_cast<TemplateTypePackArgContext*>(arg))
                        recordError(ctx->name, "Cannot use an argument pack as a type!");
                }
                else
                    recordError(ctx->name, "Type could not be found!");
            }

            if(ctx->isRef && output.type.storageType != ValueType::Struct)
                recordError(ctx, "Only struct types may be marked as ref!");

            assert(output.type.storageType != ValueType::Struct || output.type.structDef);
            return output;
        }

        std::any visitDeclaration(braneParser::DeclarationContext* ctx) override
        {
            LabeledValueContext valueContext{};
            if(!ctx->type())
                return valueContext;
            initDoc(&valueContext, ctx);
            auto type = std::any_cast<ValueContext>(visit(ctx->type()));
            valueContext.type = std::move(type.type);
            valueContext.isConst = type.isConst;
            valueContext.isRef = type.isRef;
            if(ctx->id)
            {
                valueContext.identifier.text = safeGetText(ctx->id);
                valueContext.identifier.range = toRange(ctx->id);
            }
            if(valueContext.type.structDef && !valueContext.isRef)
            {
                if(auto* parentFunc = lastNode()->getParent<FunctionContext>())
                {
                    if(isLocal(valueContext.type.structDef))
                        callTree.addDependency(parentFunc, valueContext.type.structDef->constructor);
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

        LabeledNodeList<LabeledValueContext> constructArgumentList(braneParser::ArgumentListContext* ctx, ArgPackInstanceContext** argPackInstance = nullptr)
        {
            LabeledNodeList<LabeledValueContext> args;
            for(auto& item : ctx->argumentListItem())
            {
                if(auto* declaration = item->declaration())
                    args.emplace_back(new LabeledValueContext{std::any_cast<LabeledValueContext>(visit(declaration))});
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
                    auto* pack = dynamic_cast<TemplateTypePackArgContext*>(argInstance);
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
                        *argPackInstance =  new ArgPackInstanceContext{};
                        (*argPackInstance)->identifier = prefix;
                    }
                    for(auto& value : pack->values)
                    {
                        auto* valueInstance = new LabeledValueContext{prefix + " " + std::to_string(labelIndex++), value};
                        if(argPackInstance)
                            (*argPackInstance)->values.emplace_back(valueInstance);
                        args.emplace_back(valueInstance);
                    }
                }
            }
            return std::move(args);
        }

        bool populateTemplateArgs(TemplateHandle* temp, const std::vector<ValueContext>& args)
        {
            if(args.size() < temp->args.size())
                return false;
            size_t arg = 0;
            TemplateArgs argsToPush;
            for(size_t argDef = 0; argDef < temp->args.size(); ++argDef)
            {
                if(arg == args.size())
                    return false;

                std::string identifier = temp->args[argDef]->identifier;
                if(temp->args[argDef]->type == TemplateDefArgumentContext::ValueType)
                    argsToPush.emplace(identifier, new TemplateTypeArgContext{identifier, args[arg++]});
                else if(temp->args[argDef]->type == TemplateDefArgumentContext::ValueTypePack)
                {
                    if(argDef != temp->args.size() - 1)
                        return false;
                    auto pack = new TemplateTypePackArgContext{};
                    pack->identifier = identifier;
                    while(arg != args.size())
                        pack->values.push_back(args[arg++]);
                    argsToPush.emplace(std::move(identifier), pack);
                }
            }
            if(arg != args.size())
                return false;
            _templateArgs.push_back(std::move(argsToPush));
            return true;
        }

        DocumentContext* getTemplateInstance(const std::string& identifier,
                                             const std::vector<ValueContext>& args,
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

        FunctionContext* getFunctionNode(const std::string& identifier, const LabeledNodeList<LabeledValueContext>& args)
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
            functions->push_back(std::unique_ptr<FunctionContext>(func));
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

            return o;
        }

        virtual std::any visitFunctionStub(braneParser::FunctionStubContext* ctx) override
        {
            ASSERT_EXISTS(ctx->sig);
            auto sigAny = visitFunctionSig(ctx->functionSig());
            if(!sigAny.has_value())
                return (FunctionContext*)nullptr;
            FunctionSig sig = std::move(std::any_cast<FunctionSig>(sigAny));
            auto arguments = constructArgumentList(ctx->arguments);

            bool isMember = lastNode()->is<StructContext>();

            if(isMember)
            {
                auto* thisRef = new LabeledValueContext{};
                thisRef->type = TypeContext{lastNode()->as<StructContext>()->longId(), ValueType::Struct};
                thisRef->identifier.text = "this";
                thisRef->isLValue = true;
                thisRef->isRef = true;
                thisRef->isConst = ctx->isConst;
                arguments.emplace(arguments.begin(), thisRef);
            }

            FunctionContext* func = getFunctionNode(sig.id, arguments);
            func->identifier.range = toRange(ctx->sig->id);
            func->returnType = sig.returnType;
            func->arguments = std::move(arguments);
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
                return (FunctionContext*)nullptr;
            }

            auto sigAny = visitFunctionSig(ctx->sig);
            if(!sigAny.has_value())
                return (FunctionContext*)nullptr;

            FunctionSig sig = std::move(std::any_cast<FunctionSig>(sigAny));

            ArgPackInstanceContext* argPackInstanceContext = nullptr;
            auto arguments = std::move(constructArgumentList(ctx->arguments, &argPackInstanceContext));


            bool isMember = lastNode()->is<StructContext>();
            if(isMember)
            {
                auto* thisRef = new LabeledValueContext{};
                thisRef->type = TypeContext{lastNode()->as<StructContext>()->longId(), ValueType::Struct};
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
            _functionHasReturn = false;

            initDoc(func, ctx);

            if(!_extractOnlyIdentifiers)
            {
                func->body = std::make_unique<ScopeContext>();
                initDoc(func->body.get(), ctx);
                for(auto stmt : ctx->statement())
                {
                    auto statement = asStmt(visit(stmt));
                    if(statement)
                        func->body->statements.push_back(std::move(statement));
                }
                popDoc(func->body.get());
            }
            popDoc(func);

            if(!_functionHasReturn && func->returnType.type.storageType != ValueType::Void)
                recordError(ctx->sig->id, "Function never returns " + func->returnType.type.identifier);

            _functionHasReturn = cachedFHR;

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
            if(!_analyzer.getLibrary(i.library))
                recordError(ctx->library, "Library exported with identifier \"" + i.library + "\" not found!");
            if(!i.library.empty())
                lastNode()->as<ScriptContext>()->imports.push_back(std::move(i));
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
                auto args = std::any_cast<std::vector<TemplateDefArgumentContext*>>(visit(ctx->template_));
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
                thisRef.type = {structCtx->longId(), ValueType::Struct};

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
                        std::string error;
                        if(!resolveFunctionCall("_construct", constructCall, error, var->type.structDef))
                            recordError(ctx->id, error);

                        if(isLocal(constructCall->function))
                            callTree.addDependency(func, constructCall->function);
                        func->body->statements.emplace_back(constructCall);
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
                thisRef.type = {structCtx->longId(), ValueType::Struct};

                LabeledValueContext otherRef{};
                otherRef.identifier.text = "other";
                otherRef.isRef = true;
                otherRef.isConst = true;
                otherRef.type = {structCtx->longId(), ValueType::Struct};

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
                        if(!resolveFunctionCall("_copy", constructCall, error, var->type.structDef))
                            recordError(ctx->id, error);
                        if(isLocal(constructCall->function))
                            callTree.addDependency(func, constructCall->function);
                        func->body->statements.emplace_back(constructCall);
                    }
                    else
                    {
                        auto move = new AssignmentContext{};
                        move->lValue.reset(memberAccess);
                        move->rValue.reset(otherAccess);
                        func->body->statements.emplace_back(move);
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
                thisRef.type = {structCtx->longId(), ValueType::Struct};

                LabeledValueContext otherRef{};
                otherRef.identifier.text = "other";
                otherRef.isRef = true;
                otherRef.type = {structCtx->longId(), ValueType::Struct};

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
                        if(!resolveFunctionCall("_move", constructCall, error, var->type.structDef))
                            recordError(ctx->id, error);
                        if(isLocal(constructCall->function))
                            callTree.addDependency(func, constructCall->function);
                        func->body->statements.emplace_back(constructCall);
                    }
                    else
                    {
                        auto move = new AssignmentContext{};
                        move->lValue.reset(memberAccess);
                        move->rValue.reset(otherAccess);
                        func->body->statements.emplace_back(move);
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
                thisRef.type = {structCtx->longId(), ValueType::Struct};

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
                        if(!resolveFunctionCall("_destruct", constructCall, error, var->type.structDef))
                            recordError(ctx->id, error);
                        if(isLocal(constructCall->function))
                            callTree.addDependency(func, constructCall->function);
                        func->body->statements.emplace_back(constructCall);
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
                    scope->statements.push_back(std::move(stmt));
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
            popDoc(retCtx);

            auto& functionType = lastNode()->getParent<FunctionContext>()->returnType.type;
            if(retCtx->value && retCtx->value->returnType.type != functionType)
            {
                auto castCtx = std::make_unique<FunctionCallContext>();
                std::string castError;
                castCtx->arguments.push_back(std::move(retCtx->value));
                if(!resolveCast(castCtx.get(), lastNode()->getParent<FunctionContext>()->returnType.type, castError))
                    recordError(ctx,
                                "Returned value of type " + castCtx->arguments[0]->returnType.type.identifier +
                                    " does not match the function's declared return type of " +
                                    functionType.identifier);

                retCtx->value = std::move(castCtx);
            }
            if(retCtx->value && retCtx->value->returnType.type.storageType == ValueType::Struct)
            {
                auto* sCtx = retCtx->value->returnType.type.structDef;
                retCtx->value->returnType.type.identifier = sCtx->longId();
                auto* parentFunc = lastNode()->getParent<FunctionContext>();
                if(isLocal(sCtx))
                    callTree.addDependency(parentFunc, sCtx->constructor);
            }

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
                auto* s = decl->type.structDef;
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
            assignmentCtx->lValue = asExpr(visit(ctx->lValue));
            if(!assignmentCtx->lValue->returnType.isLValue)
                recordError(ctx->lValue, "Expression is not an lValue!");
            if(assignmentCtx->lValue->returnType.isConst)
                recordError(ctx->lValue, "Can not modify a constant value!");

            assignmentCtx->rValue = asExpr(visit(ctx->rValue));
            if(assignmentCtx->lValue->returnType.type != assignmentCtx->rValue->returnType.type)
            {
                auto castCtx = new FunctionCallContext{};
                castCtx->arguments.push_back(std::unique_ptr<ExpressionContext>(assignmentCtx->rValue.release()));
                assignmentCtx->rValue.reset(castCtx);
                std::string error;
                if(!resolveCast(castCtx, assignmentCtx->lValue->returnType.type, error))
                    recordError(ctx->rValue, error);
            }
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
            constCtx->returnType.type.structDef =
                dynamic_cast<StructContext*>(getIdentifierContext("BraneScript")->findIdentifier("string"));
            if(!constCtx->returnType.type.structDef)
                recordError(ctx, "To use the string type, the BraneScript library must be imported.");
            constCtx->value = ctx->getText();
            constCtx->value = {constCtx->value.data() + 1, constCtx->value.size() - 2};
            popDoc(constCtx);
            RETURN_EXPR(constCtx);
        }

        std::any visitSizeOfType(braneParser::SizeOfTypeContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->t, "type expected");
            auto constCtx = new ConstIntContext{};
            initDoc(constCtx, ctx);
            auto value = std::any_cast<ValueContext>(visitType(ctx->t));
            constCtx->value = value.type.size();
            popDoc(constCtx);
            RETURN_EXPR(constCtx);
        };

        std::any visitSizeOfExpr(braneParser::SizeOfExprContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->expr, "expression missing");
            auto constCtx = new ConstIntContext{};
            initDoc(constCtx, ctx);
            std::unique_ptr<ExpressionContext> expr = asExpr(visit(ctx->expr));
            constCtx->value = expr->returnType.type.size();
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
            auto* pack = dynamic_cast<TemplateTypePackArgContext*>(argInstance);
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
            auto callCtx = new FunctionCallContext{};
            initDoc(callCtx, ctx);
            auto returnType = std::any_cast<ValueContext>(visit(ctx->type()));
            callCtx->arguments.push_back(asExpr(visit(ctx->expression())));
            popDoc(callCtx);
            std::string error;
            if(!resolveCast(callCtx, returnType.type, error))
                recordError(ctx, error);
            RETURN_EXPR(callCtx);
        }

        std::any visitAddsub(braneParser::AddsubContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->left, "expression expected");
            EXPR_ASSERT_EXISTS(ctx->opr, "operator expected");
            EXPR_ASSERT_EXISTS(ctx->right, "expression expected");
            auto callCtx = new FunctionCallContext{};
            initDoc(callCtx, ctx);
            callCtx->arguments.push_back(asExpr(visit(ctx->left)));
            callCtx->arguments.push_back(asExpr(visit(ctx->right)));
            popDoc(callCtx);
            std::string error;
            if(!resolveFunctionCall("opr " + ctx->opr->getText(), callCtx, error))
                recordError(ctx->opr, error);
            RETURN_EXPR(callCtx);
        }

        std::any visitMuldiv(braneParser::MuldivContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->left, "expression expected");
            EXPR_ASSERT_EXISTS(ctx->opr, "operator expected");
            EXPR_ASSERT_EXISTS(ctx->right, "expression expected");
            auto callCtx = new FunctionCallContext{};
            initDoc(callCtx, ctx);
            callCtx->arguments.push_back(asExpr(visit(ctx->left)));
            callCtx->arguments.push_back(asExpr(visit(ctx->right)));
            popDoc(callCtx);
            std::string error;
            if(!resolveFunctionCall("opr " + ctx->opr->getText(), callCtx, error))
                recordError(ctx->opr, error);
            RETURN_EXPR(callCtx);
        }

        std::any visitLogic(braneParser::LogicContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->left, "expression expected");
            EXPR_ASSERT_EXISTS(ctx->opr, "operator expected");
            EXPR_ASSERT_EXISTS(ctx->right, "expression expected");
            auto callCtx = new FunctionCallContext{};
            initDoc(callCtx, ctx);
            callCtx->arguments.push_back(asExpr(visit(ctx->left)));
            callCtx->arguments.push_back(asExpr(visit(ctx->right)));
            popDoc(callCtx);
            std::string error;
            if(!resolveFunctionCall("opr " + ctx->opr->getText(), callCtx, error))
                recordError(ctx->opr, error);
            RETURN_EXPR(callCtx);
        }

        std::any visitComparison(braneParser::ComparisonContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->left, "expression expected");
            EXPR_ASSERT_EXISTS(ctx->opr, "operator expected");
            EXPR_ASSERT_EXISTS(ctx->right, "expression expected");
            auto callCtx = new FunctionCallContext{};
            initDoc(callCtx, ctx);
            callCtx->arguments.push_back(asExpr(visit(ctx->left)));
            callCtx->arguments.push_back(asExpr(visit(ctx->right)));
            popDoc(callCtx);
            std::string error;
            if(!resolveFunctionCall("opr " + ctx->opr->getText(), callCtx, error))
                recordError(ctx->opr, error);
            RETURN_EXPR(callCtx);
        }

        std::any visitIndexAccess(braneParser::IndexAccessContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->base, "expression expected");
            EXPR_ASSERT_EXISTS(ctx->arg, "expression expected");
            auto callCtx = new FunctionCallContext{};
            initDoc(callCtx, ctx);
            callCtx->arguments.push_back(asExpr(visit(ctx->base)));
            callCtx->arguments.push_back(asExpr(visit(ctx->arg)));
            popDoc(callCtx);
            std::string error;
            if(!resolveFunctionCall("opr []", callCtx, error))
                recordError(ctx, error);
            RETURN_EXPR(callCtx);
        }

        std::any visitId(braneParser::IdContext* ctx) override
        {
            std::string identifier = ctx->getText();
            auto node = lastNode()->findIdentifier(identifier, 0);
            if(!node)
            {
                recordError(ctx, "\"" + identifier + "\" is not a variable!");
                return NULL_EXPR;
            }
            if(!node->is<LabeledValueContext>())
            {
                recordError(ctx, identifier + " is not a value!");
                return NULL_EXPR;
            }
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
                    if(m->identifier.text == identifier)
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

        std::any visitMemberAccess(braneParser::MemberAccessContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->base, "expected base expression");
            EXPR_ASSERT_EXISTS(ctx->member, "expected member identifier");
            auto accessCtx = new MemberAccessContext{};
            initDoc(accessCtx, ctx);
            accessCtx->baseExpression = asExpr(visit(ctx->base));
            if(accessCtx->baseExpression->returnType.type.storageType != ValueType::Struct)
                recordError(ctx, "Cannot access members of non-struct objects");
            else
            {
                auto& typeName = accessCtx->baseExpression->returnType.type.identifier;
                auto type = accessCtx->baseExpression->returnType.type.structDef;
                if(!type)
                    recordError(ctx, "Type " + typeName + " is not a struct");
                if(type)
                {
                    std::string memberName = safeGetText(ctx->member);
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
                        accessCtx->isConstexpr = accessCtx->baseExpression->isConstexpr;
                        accessCtx->returnType.type = type->variables[accessCtx->member]->type;
                        accessCtx->returnType.isRef = accessCtx->returnType.type.storageType == ValueType::Struct;
                        accessCtx->returnType.isConst = accessCtx->baseExpression->returnType.isConst;
                        accessCtx->returnType.isLValue = accessCtx->baseExpression->returnType.isLValue;
                    }
                }
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

        std::any visitMemberFunctionCall(braneParser::MemberFunctionCallContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->base, "expected base expression");
            EXPR_ASSERT_EXISTS(ctx->name, "expected member function call");
            auto callCtx = new FunctionCallContext{};
            initDoc(callCtx, ctx);
            callCtx->arguments = populateFunctionArgs(ctx->argumentPack());
            callCtx->arguments.insert(callCtx->arguments.begin(), asExpr(visit(ctx->base)));
            popDoc(callCtx);
            std::string error;
            if(!resolveFunctionCall(ctx->name->getText(),
                                    callCtx,
                                    error,
                                    callCtx->arguments[0]->returnType.type.structDef,
                                    ctx->template_))
                recordError(ctx, error);
            else
            {
                if(isLocal(callCtx->function))
                    callTree.addDependency(lastNode()->getParent<FunctionContext>(), callCtx->function);
            }
            RETURN_EXPR(callCtx);
        }

        std::any visitFunctionCall(braneParser::FunctionCallContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->id, "expected function identifier");
            auto callCtx = new FunctionCallContext{};
            initDoc(callCtx, ctx);
            callCtx->arguments = populateFunctionArgs(ctx->argumentPack());

            std::string error;
            if(resolveFunctionCall(ctx->id, callCtx, error))
            {
                if(isLocal(callCtx->function))
                    callTree.addDependency(lastNode()->getParent<FunctionContext>(), callCtx->function);
                popDoc(callCtx);
                RETURN_EXPR(callCtx);
            }

            if(ctx->id->child || !lastNode()->getParent<StructContext>())
            {
                recordError(ctx->id, error);
                popDoc(callCtx);
                RETURN_EXPR(callCtx);
            }
            // If a non-member function was not found and this scope is in a member function, try to implicitly
            // reference "this" variable
            error += "\n";
            auto* thisRef = lastNode()->findIdentifier("this", IDSearchOptions_ParentsOnly)->as<LabeledValueContext>();
            auto valueAccess = new LabeledValueReferenceContext{*thisRef};
            initDoc(valueAccess, ctx);

            callCtx->arguments.emplace(callCtx->arguments.begin(), valueAccess);
            if(!resolveFunctionCall(
                   ctx->id->id->getText(), callCtx, error, valueAccess->returnType.type.structDef, ctx->id->template_))
                recordError(ctx->id, error);
            {
                if(isLocal(callCtx->function))
                    callTree.addDependency(lastNode()->getParent<FunctionContext>(), callCtx->function);
            }

            popDoc(valueAccess);
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
                        std::string error;
                        if(!resolveFunctionCall("_construct", constructCall, error, var->type.structDef))
                            recordError(ctx->start, error);
                        if(isLocal(constructCall->function))
                            callTree.addDependency(func, constructCall->function);
                        func->body->statements.emplace_back(constructCall);
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
                        std::string error;
                        if(!resolveFunctionCall("_destruct", constructCall, error, var->type.structDef))
                            recordError(ctx->start, error);
                        if(isLocal(constructCall->function))
                            callTree.addDependency(func, constructCall->function);
                        func->body->statements.emplace_back(constructCall);
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
                    _analyzer.appendTemplateHeaders(lib.library, _result.source, document);
                // TODO figure out a clean way to associate sections of the header with external files, instead of
                // returning negative line numbers in errors
                document += '\n';
                for(char c : document)
                    _headerSize += c == '\n';
            }

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

    StaticAnalyzer::StaticAnalyzer() { addWorkspace("include"); }

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

        Analyzer(*this, *context, true).analyze();

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

        Analyzer(*this, *context, true).analyze();
        context->complete = false;

        if(!cacheDocument)
            context->document.clear();
    }

    bool StaticAnalyzer::validate(const std::string& path)
    {
        assert(_analyzationContexts.contains(path));
        auto& context = _analyzationContexts.at(path);
        std::scoped_lock lock(context->lock);
        if(!context->complete)
            Analyzer(*this, *context, false).analyze();
        context->complete = true;
        return context->errors.empty();
    }

    StaticAnalyzer::AnalyzationContext* StaticAnalyzer::getCtx(const std::string& path)
    {
        return _analyzationContexts.at(path).get();
    }

    void StaticAnalyzer::addWorkspace(const std::string& path)
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
                                               const std::string& currentDocument,
                                               std::string& stream)
    {
        if(!exportedTemplateText.contains(lib))
            return;

        for(auto& temp : exportedTemplateText.at(lib))
        {
            if(temp.first == currentDocument)
                continue;
            stream += temp.second;
        }
    }

} // namespace BraneScript
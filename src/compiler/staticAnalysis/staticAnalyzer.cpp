//
// Created by wirewhiz on 1/23/23.
//

#include "staticAnalyzer.h"
#include <typeinfo>
#include "antlr4/braneBaseVisitor.h"
#include "antlr4/braneLexer.h"

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
            return TextRange{token->getLine() - 1,
                             token->getCharPositionInLine(),
                             token->getLine() - 1,
                             token->getCharPositionInLine() + (token->getStopIndex() - token->getStartIndex()) + 1};
        };

        TextRange toRange(antlr4::ParserRuleContext* ctx)
        {
            return TextRange{ctx->getStart()->getLine() - 1,
                             ctx->getStart()->getCharPositionInLine(),
                             ctx->getStop()->getLine() - 1,
                             ctx->getStop()->getCharPositionInLine() +
                                 (ctx->getStop()->getStopIndex() - ctx->getStop()->getStartIndex()) + 1};
        };

        void initDoc(DocumentContext* doc, antlr4::Token* token)
        {
            doc->parent = lastNode();
            doc->range = toRange(token);
            doc->version = _result.version;
            _documentContext.push(doc);
        }

        void initDoc(DocumentContext* doc, antlr4::ParserRuleContext* ctx)
        {
            doc->parent = lastNode();
            doc->range = toRange(ctx);
            doc->version = _result.version;
            _documentContext.push(doc);
        }

        void popDoc() { _documentContext.pop(); }

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

        std::string functionSig(const std::string& identifier, const std::vector<LabeledValueContext> args)
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

        ValueType getValueType(const std::string& identifier)
        {
            if(_nativeTypes.contains(identifier))
                return _nativeTypes.at(identifier).storageType;
            if(getStructCtx(identifier))
                return ValueType::Struct;
            return ValueType::Void;
        }

        /**
         * @brief Get the document node corresponding to an identifier respecting namespaces
         */
        DocumentContext* getIdentifierContext(const std::string& identifier, DocumentContext* base = nullptr)
        {
            if(identifier.empty())
                return nullptr;
            if(base == nullptr)
                base = lastNode();

            // Extract library/struct name
            std::string prefix;
            auto delimPos = identifier.find("::");
            bool delimFound = delimPos != std::string::npos;
            if(delimFound)
                prefix = {identifier.data(), delimPos};
            else
                prefix = identifier;

            // Search libraries aliases first, so we don't accidentally get restricted to the scope of a local export
            DocumentContext* ident = nullptr;
            for(auto& imp : _result.scriptContext->imports)
            {
                if(!imp.alias.empty() && imp.alias != prefix)
                    continue;
                if(imp.alias.empty() && imp.library != prefix)
                    continue;
                ident = _analyzer.getLibrary(imp.library);
                if(ident)
                    break;
            }

            if(!ident)
                ident = base->findIdentifier(prefix, IDSearchOptions_ParentsOnly);

            // Search linked libraries
            if(!ident)
            {
                for(auto& imp : _result.scriptContext->imports)
                {
                    if(!imp.alias.empty())
                        continue;
                    auto lib = _analyzer.getLibrary(imp.library);
                    if(!lib)
                        continue;
                    ident = lib->findIdentifier(identifier, IDSearchOptions_ChildrenOnly);
                    if(ident)
                        return ident;
                }
            }

            if(!delimFound)
                return ident;

            // Find sub-symbols. Mostly used when linking to external libraries.
            if(ident->is<LibrarySet>() || ident->is<LibraryContext>() || ident->is<StructContext>())
                return getIdentifierContext({identifier.data() + delimPos + 2, identifier.size() - delimPos - 2},
                                            ident);

            return ident;
        }

        StructContext* getStructCtx(const std::string& identifier)
        {
            return getIdentifierContext(identifier)->as<StructContext>();
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

        bool resolveFunctionCall(const std::string& identifier,
                                 FunctionCallContext* context,
                                 std::string& error,
                                 bool autoCast = true)
        {
            DocumentContext* base = lastNode();
            // Extract library/struct name path
            auto delimPos = identifier.find_last_of("::");
            bool delimFound = delimPos != std::string::npos;
            std::string postfix;
            if(delimFound)
            {
                std::string prefix = {identifier.data(), delimPos - 1};
                base = getIdentifierContext(prefix);
                if(!base)
                {
                    error += "Could not find library or object \"" + prefix + "\"";
                    return false;
                }
                postfix = std::string{identifier.data() + delimPos + 1, identifier.size() - delimPos - 1};
            }
            else
                postfix = identifier;
            std::list<FunctionContext*> overrides;
            base->getFunction(postfix, overrides);

            for(auto& imp : _result.scriptContext->imports)
            {
                if(!imp.alias.empty())
                    continue;
                auto lib = _analyzer.getLibrary(imp.library);
                if(!lib)
                    continue;
                lib->getFunction(identifier, overrides);
            }

            /* We want to find the best match with the lowest amount of implicit casts. So we store the cast count for
             * each candidate function and try to find the closest one. Cast cost is a measure of the desirability of
             * casts the casts. For instance a cast from uint32 to uint64 is more desirable than a cast from uint32_t to
             * a float.
             * */
            uint16_t castCount = -1;
            uint32_t castCost = -1;
            FunctionContext* bestMatch = nullptr;

            auto& args = context->arguments;
            for(auto f : overrides)
            {
                if(f->arguments.size() != args.size())
                    continue;
                bool argsMatch = true;
                uint16_t requiredCasts = 0;
                uint32_t requiredCost = 0;
                for(size_t i = 0; i < args.size(); ++i)
                {
                    if(f->arguments[i].type != args[i]->returnType.type)
                    {
                        if(!implicitCastViable(f->arguments[i], args[i]->returnType))
                        {
                            argsMatch = false;
                            break;
                        }
                        requiredCasts++;
                        requiredCost += calculateCastCost(args[i]->returnType, f->arguments[i]);
                    }
                    // Honor constness
                    if(args[i]->returnType.isConst && f->arguments[i].isRef && !f->arguments[i].isConst)
                    {
                        argsMatch = false;
                        break;
                    }
                }
                if(!argsMatch)
                    continue;
                // This is the best match if it requires fewer casts or has the same amount and just costs lest
                if(requiredCasts < castCount || (requiredCasts == castCount && requiredCost < castCost))
                {
                    bestMatch = f;
                    castCount = requiredCasts;
                    castCost = requiredCost;
                }
            }

            if(!bestMatch)
            {
                error += "Could not find override of function \"" + identifier + "\" with arguments: ";
                for(auto& arg : args)
                    error += arg->returnType.signature() + ", ";
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
            context->returnType = context->function->returnType;

            if(castCount)
            {
                for(size_t i = 0; i < args.size(); ++i)
                {
                    if(context->function->arguments[i].type == args[i]->returnType.type)
                        continue;
                    auto* castCtx = new FunctionCallContext{};
                    castCtx->arguments.push_back(std::unique_ptr<ExpressionContext>(args[i].release()));
                    args[i].reset(castCtx);

                    // Find the cast operator, should never return false ideally, but I can see configuration bugs
                    // triggering this in the future.
                    if(!resolveCast(castCtx, context->function->arguments[i].type, error))
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
            popDoc();
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
            popDoc();
            return {};
        }

        std::any visitType(braneParser::TypeContext* ctx) override
        {
            TypeContext type = {safeGetText(ctx->id), ValueType::Void};
            type.storageType = getValueType(type.identifier);
            if(type.storageType == ValueType::Struct)
            {
                auto* sCtx = getStructCtx(type.identifier);
                type.identifier = sCtx->longId();
            }
            if(type.storageType == ValueType::Void && type.identifier != "void")
                recordError(ctx->id, "Type " + type.identifier + " does not exist!");
            if(ctx->isRef && type.storageType != ValueType::Struct)
                recordError(ctx, "Only struct types may be marked as ref!");
            ValueContext output;
            output.type = std::move(type);
            output.isConst = ctx->isConst;
            output.isRef = ctx->isRef;
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
            popDoc();
            return valueContext;
        }

        std::any visitArgumentList(braneParser::ArgumentListContext* ctx) override
        {
            std::vector<LabeledValueContext> args;
            for(auto& arg : ctx->declaration())
                args.push_back(std::any_cast<LabeledValueContext>(visit(arg)));
            return std::move(args);
        }

        FunctionContext* getFunctionNode(const std::string& identifier, const std::vector<LabeledValueContext>& args)
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
                    if(f->arguments[a] != args[a])
                    {
                        argumentsMatch = false;
                        break;
                    }
                }
                if(!argumentsMatch)
                    continue;
                return f.get();
            }
            // If the function was not found, add it
            auto func = new FunctionContext{};
            func->identifier.text = identifier;
            func->version = -1;
            functions->push_back(std::unique_ptr<FunctionContext>(func));
            return func;
        }

        virtual std::any visitFunctionStub(braneParser::FunctionStubContext* ctx) override
        {
            ASSERT_EXISTS(ctx->type() || ctx->castType);
            ASSERT_EXISTS(ctx->id || ctx->oprID || ctx->castType);
            bool isMember = lastNode()->is<StructContext>();

            auto returnType = std::any_cast<ValueContext>((ctx->castType) ? visit(ctx->castType) : visit(ctx->type()));
            std::string id;
            if(ctx->id)
                id = safeGetText(ctx->id);
            else if(ctx->oprID)
                id = "opr " + safeGetText(ctx->oprID);
            else if(ctx->castType)
                id = "opr " + returnType.signature();
            auto arguments = std::move(std::any_cast<std::vector<LabeledValueContext>>(visit(ctx->arguments)));

            if(isMember)
            {
                LabeledValueContext thisRef;
                thisRef.type = TypeContext{lastNode()->as<StructContext>()->longId(), ValueType::Struct};
                thisRef.identifier.text = "this";
                thisRef.isLValue = true;
                thisRef.isRef = true;
                thisRef.isConst = ctx->isConst;
                arguments.insert(arguments.begin(), thisRef);
            }

            FunctionContext* func = getFunctionNode(id, arguments);
            func->identifier.range = toRange(ctx->id);
            func->returnType = returnType;
            func->arguments = std::move(arguments);
            for(auto& a : func->arguments)
            {
                a.parent = func;
                a.isLValue = true;
            }

            if(func->version == _result.version)
                recordError(ctx->id, "Redefinition of already existing function!");

            initDoc(func, ctx);
            popDoc();
            return {};
        }

        std::any visitFunction(braneParser::FunctionContext* ctx) override
        {
            ASSERT_EXISTS(ctx->type() || ctx->castType);
            ASSERT_EXISTS(ctx->id || ctx->oprID || ctx->castType);
            bool isMember = lastNode()->is<StructContext>();

            auto returnType = std::any_cast<ValueContext>((ctx->castType) ? visit(ctx->castType) : visit(ctx->type()));
            std::string id;
            if(ctx->id)
                id = safeGetText(ctx->id);
            else if(ctx->oprID)
                id = "opr " + safeGetText(ctx->oprID);
            else if(ctx->castType)
                id = "opr " + returnType.signature();
            auto arguments = std::move(std::any_cast<std::vector<LabeledValueContext>>(visit(ctx->arguments)));

            if(isMember)
            {
                LabeledValueContext thisRef;
                thisRef.type = TypeContext{lastNode()->as<StructContext>()->longId(), ValueType::Struct};
                thisRef.identifier.text = "this";
                thisRef.isLValue = true;
                thisRef.isRef = true;
                thisRef.isConst = ctx->isConst;
                arguments.insert(arguments.begin(), thisRef);
            }

            FunctionContext* func = getFunctionNode(id, arguments);
            func->identifier.range = toRange(ctx->id);
            func->returnType = returnType;
            func->arguments = std::move(arguments);
            for(size_t i = 0; i < func->arguments.size(); i++)
            {
                auto& a = func->arguments[i];
                a.parent = func;
                a.isLValue = true;
                if(a.type.storageType == ValueType::Struct && !a.isRef)
                    recordError(
                        ctx->arguments->declaration()[i]->type(),
                        R"(Structs may only be passed by reference, consider adding the "ref" and "const" descriptors instead)");
            }

            if(func->version == _result.version)
                recordError(ctx->id, "Redefinition of already existing function!");
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
                popDoc();
            }

            popDoc();

            if(!_functionHasReturn && func->returnType.type.storageType != ValueType::Void)
                recordError(ctx->id, "Function never returns " + func->returnType.type.identifier);

            _functionHasReturn = cachedFHR;

            _result.scriptContext->functionOrder.push_back(func);
            return {};
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
            popDoc();
            if(!_analyzer.getLibrary(i.library))
                recordError(ctx->library, "Library exported with identifier \"" + i.library + "\" not found!");
            if(!i.library.empty())
                lastNode()->as<ScriptContext>()->imports.push_back(std::move(i));
            return {};
        }

        std::any visitStructMember(braneParser::StructMemberContext* ctx) override
        {
            assert(lastNode()->is<StructContext>());
            if(!ctx->var)
                return visitChildren(ctx);
            ASSERT_EXISTS(ctx->var);
            ASSERT_EXISTS(ctx->var->id);
            auto var = getNode(lastNode()->as<StructContext>()->variables, safeGetText(ctx->var->id));
            *var = std::any_cast<LabeledValueContext>(visit(ctx->var));
            var->isLValue = true;
            initDoc(var, ctx);
            // TODO default value
            popDoc();
            return {};
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

            auto structCtx = getNode(*structs, safeGetText(ctx->id));
            initDoc(structCtx, ctx);
            visitChildren(ctx);

            bool hasConstructor[4] = {false, false, false, false};
            for(auto& f : structCtx->functions)
            {
                // If this is an out of date function, skip (this will make it so we always regenerate auto-created
                // constructors)
                if(f->version != _result.version)
                    continue;
                if(f->identifier.text == "_construct")
                    hasConstructor[0] = true;
                if(f->identifier.text == "_copy")
                    hasConstructor[1] = true;
                if(f->identifier.text == "_move")
                    hasConstructor[2] = true;
                if(f->identifier.text == "_destruct")
                    hasConstructor[3] = true;
            }
            // Make constructor
            if(!hasConstructor[0])
            {
                LabeledValueContext thisRef{};
                thisRef.identifier.text = "this";
                thisRef.isRef = true;
                thisRef.type = {structCtx->longId(), ValueType::Struct};

                std::vector<LabeledValueContext> args = {thisRef};
                auto func = getFunctionNode("_construct", args);
                initDoc(func, ctx->id);
                popDoc();
                func->arguments = std::move(args);
                func->body = std::make_unique<ScopeContext>();

                size_t varIndex = 0;
                for(auto& var : structCtx->variables)
                {
                    if(var->type.storageType == ValueType::Struct)
                    {
                        auto memberBase = new LabeledValueReferenceContext{};
                        memberBase->value = &func->arguments[0];
                        memberBase->returnType = func->arguments[0];

                        auto memberAccess = new MemberAccessContext{};
                        memberAccess->member = varIndex;
                        memberAccess->returnType = *var;
                        memberAccess->returnType.isRef = true;
                        memberAccess->baseExpression.reset(memberBase);

                        auto constructCall = new FunctionCallContext{};
                        constructCall->arguments.emplace_back(memberAccess);
                        std::string error;
                        if(!resolveFunctionCall(var->type.identifier + "::_construct", constructCall, error))
                            recordError(ctx->id, error);
                        func->body->statements.emplace_back(constructCall);
                    }
                    varIndex++;
                }
            }
            // Make copy constructor
            if(!hasConstructor[1])
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

                std::vector<LabeledValueContext> args = {thisRef, otherRef};
                auto func = getFunctionNode("_copy", args);
                initDoc(func, ctx->id);
                popDoc();
                func->arguments = std::move(args);
                func->body = std::make_unique<ScopeContext>();

                size_t varIndex = 0;
                for(auto& var : structCtx->variables)
                {
                    auto memberBase = new LabeledValueReferenceContext{};
                    memberBase->value = &func->arguments[0];
                    memberBase->returnType = func->arguments[0];

                    auto memberAccess = new MemberAccessContext{};
                    memberAccess->member = varIndex;
                    memberAccess->returnType = *var;
                    memberAccess->returnType.isRef = true;
                    memberAccess->baseExpression.reset(memberBase);

                    auto otherBase = new LabeledValueReferenceContext{};
                    otherBase->value = &func->arguments[1];
                    otherBase->returnType = func->arguments[1];

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
                        if(!resolveFunctionCall(var->type.identifier + "::_copy", constructCall, error))
                            recordError(ctx->id, error);
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
            }
            // Make move constructor
            if(!hasConstructor[2])
            {
                LabeledValueContext thisRef{};
                thisRef.identifier.text = "this";
                thisRef.isRef = true;
                thisRef.type = {structCtx->longId(), ValueType::Struct};

                LabeledValueContext otherRef{};
                otherRef.identifier.text = "other";
                otherRef.isRef = true;
                otherRef.type = {structCtx->longId(), ValueType::Struct};

                std::vector<LabeledValueContext> args = {thisRef, otherRef};
                auto func = getFunctionNode("_move", {thisRef, otherRef});
                initDoc(func, ctx->id);
                popDoc();
                func->arguments = std::move(args);
                func->body = std::make_unique<ScopeContext>();

                size_t varIndex = 0;
                for(auto& var : structCtx->variables)
                {
                    auto memberBase = new LabeledValueReferenceContext{};
                    memberBase->value = &func->arguments[0];
                    memberBase->returnType = func->arguments[0];

                    auto memberAccess = new MemberAccessContext{};
                    memberAccess->returnType = *var;
                    memberAccess->returnType.isRef = true;
                    memberAccess->member = varIndex;
                    memberAccess->baseExpression.reset(memberBase);

                    auto otherBase = new LabeledValueReferenceContext{};
                    otherBase->value = &func->arguments[1];
                    otherBase->returnType = func->arguments[1];

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
                        if(!resolveFunctionCall(var->type.identifier + "::_move", constructCall, error))
                            recordError(ctx->id, error);
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
            }
            // Make destructor
            if(!hasConstructor[3])
            {
                LabeledValueContext thisRef{};
                thisRef.identifier.text = "this";
                thisRef.isRef = true;
                thisRef.type = {structCtx->longId(), ValueType::Struct};

                std::vector<LabeledValueContext> args = {thisRef};
                auto func = getFunctionNode("_destruct", args);
                initDoc(func, ctx->id);
                popDoc();
                func->arguments = std::move(args);
                func->body = std::make_unique<ScopeContext>();

                size_t varIndex = 0;
                for(auto& var : structCtx->variables)
                {
                    if(var->type.storageType == ValueType::Struct)
                    {
                        auto memberBase = new LabeledValueReferenceContext{};
                        memberBase->value = &func->arguments[0];
                        memberBase->returnType = func->arguments[0];

                        auto memberAccess = new MemberAccessContext{};
                        memberAccess->member = varIndex;
                        memberAccess->returnType = *var;
                        memberAccess->returnType.isRef = true;
                        memberAccess->baseExpression.reset(memberBase);

                        auto constructCall = new FunctionCallContext{};
                        constructCall->arguments.emplace_back(memberAccess);
                        std::string error;
                        if(!resolveFunctionCall(var->type.identifier + "::_destruct", constructCall, error))
                            recordError(ctx->id, error);
                        func->body->statements.emplace_back(constructCall);
                    }
                    varIndex++;
                }
            }
            structCtx->packed = ctx->packed;
            popDoc();
            pruneNodes(structCtx->variables);
            pruneNodes(structCtx->functions);

            return {};
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
            popDoc();
            RETURN_STMT(scope);
        }

        std::any visitReturn(braneParser::ReturnContext* ctx) override
        {
            auto retCtx = new ReturnContext{};
            initDoc(retCtx, ctx);
            if(ctx->expression())
                retCtx->value = asExpr(visit(ctx->expression()));
            popDoc();

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
            popDoc();
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
            popDoc();
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
            decl->isLValue = true;

            scope->localVariables.push_back(std::move(decl));
            popDoc();
            result->value = (--scope->localVariables.end())->get();
            if(result->value)
                result->returnType = *result->value;

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
            popDoc();
            RETURN_STMT(assignmentCtx);
        }

        std::any visitConstBool(braneParser::ConstBoolContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->BOOL(), "constant missing");
            auto constCtx = new ConstBoolContext{};
            initDoc(constCtx, ctx);
            constCtx->value = (ctx->getText() == "true");
            popDoc();
            RETURN_EXPR(constCtx);
        }

        std::any visitConstInt(braneParser::ConstIntContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->INT(), "constant missing");
            auto constCtx = new ConstIntContext{};
            initDoc(constCtx, ctx);
            constCtx->value = std::stoi(ctx->getText());
            popDoc();
            RETURN_EXPR(constCtx);
        }

        std::any visitConstFloat(braneParser::ConstFloatContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->FLOAT(), "constant missing");
            auto constCtx = new ConstFloatContext{};
            initDoc(constCtx, ctx);
            constCtx->value = std::stof(ctx->getText());
            popDoc();
            RETURN_EXPR(constCtx);
        }

        std::any visitConstChar(braneParser::ConstCharContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->CHAR(), "constant missing");
            auto constCtx = new ConstCharContext{};
            initDoc(constCtx, ctx);
            constCtx->value = ctx->getText()[1];
            popDoc();
            RETURN_EXPR(constCtx);
        }

        std::any visitConstString(braneParser::ConstStringContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->STRING(), "constant missing");
            auto constCtx = new ConstStringContext{};
            initDoc(constCtx, ctx);
            constCtx->value = ctx->getText();
            constCtx->value = {constCtx->value.data() + 1, constCtx->value.size() - 2};
            popDoc();
            RETURN_EXPR(constCtx);
        }

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
            popDoc();
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
            popDoc();
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
            popDoc();
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
            popDoc();
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
            popDoc();
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
            popDoc();
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
                auto valueAccess = new LabeledValueReferenceContext{};
                initDoc(valueAccess, ctx);

                valueAccess->value =
                    lastNode()->findIdentifier("this", IDSearchOptions_ParentsOnly)->as<LabeledValueContext>();
                valueAccess->returnType = *valueAccess->value;

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

                popDoc();
                popDoc();
                RETURN_EXPR(memberAccess);
            }

            auto valueAccess = new LabeledValueReferenceContext{};
            initDoc(valueAccess, ctx);
            popDoc();
            valueAccess->value = node->as<LabeledValueContext>();

            valueAccess->returnType = *valueAccess->value;
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
                auto type = getStructCtx(typeName);
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
            popDoc();
            RETURN_EXPR(accessCtx);
        }

        std::any visitMemberFunctionCall(braneParser::MemberFunctionCallContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->base, "expected base expression");
            EXPR_ASSERT_EXISTS(ctx->name, "expected member function call");
            auto callCtx = new FunctionCallContext{};
            initDoc(callCtx, ctx);
            callCtx->arguments.push_back(asExpr(visit(ctx->base)));
            for(auto* a : ctx->argumentPack()->expression())
                callCtx->arguments.push_back(asExpr(visit(a)));
            popDoc();
            std::string error;
            if(!resolveFunctionCall(
                   callCtx->arguments[0]->returnType.type.identifier + "::" + ctx->name->getText(), callCtx, error))
                recordError(ctx, error);
            RETURN_EXPR(callCtx);
        }

        std::any visitFunctionCall(braneParser::FunctionCallContext* ctx) override
        {
            EXPR_ASSERT_EXISTS(ctx->name, "expected function identifier");
            auto callCtx = new FunctionCallContext{};
            initDoc(callCtx, ctx);
            for(auto* a : ctx->argumentPack()->expression())
                callCtx->arguments.push_back(asExpr(visit(a)));

            std::string identifier = ctx->name->getText();
            std::string error;
            if(resolveFunctionCall(identifier, callCtx, error))
            {
                popDoc();
                RETURN_EXPR(callCtx);
            }
            if(!lastNode()->getParent<StructContext>())
            {
                recordError(ctx->name, error);
                RETURN_EXPR(callCtx);
            }
            // If a non-member function was not found and this scope is in a member function, try to implicitly
            // reference "this" variable
            error += "\n";
            auto valueAccess = new LabeledValueReferenceContext{};
            initDoc(valueAccess, ctx);

            valueAccess->value =
                lastNode()->findIdentifier("this", IDSearchOptions_ParentsOnly)->as<LabeledValueContext>();
            valueAccess->returnType = *valueAccess->value;

            callCtx->arguments.insert(callCtx->arguments.begin(), std::unique_ptr<ExpressionContext>(valueAccess));
            if(!resolveFunctionCall(
                   valueAccess->returnType.type.identifier + "::" + ctx->name->getText(), callCtx, error))
                recordError(ctx->name, error);

            popDoc();
            popDoc();
            RETURN_EXPR(callCtx);
        }

        std::any visitProgram(braneParser::ProgramContext* ctx) override
        {
            visitChildren(ctx);
            if(globals.empty())
                return {};

            std::vector<LabeledValueContext> args = {};
            // Make constructor
            {
                auto func = getFunctionNode("_construct", args);
                initDoc(func, ctx->start);
                popDoc();
                func->body = std::make_unique<ScopeContext>();

                size_t varIndex = 0;
                for(auto var : globals)
                {
                    if(var->type.storageType == ValueType::Struct)
                    {
                        auto globalRef = new LabeledValueReferenceContext{};
                        globalRef->value = var;
                        globalRef->returnType = *var;

                        auto constructCall = new FunctionCallContext{};
                        constructCall->arguments.emplace_back(globalRef);
                        std::string error;
                        if(!resolveFunctionCall(var->type.identifier + "::_construct", constructCall, error))
                            recordError(ctx->start, error);
                        func->body->statements.emplace_back(constructCall);
                    }
                    varIndex++;
                }
            }
            // Make destructor
            {
                auto func = getFunctionNode("_destruct", args);
                initDoc(func, ctx->start);
                popDoc();
                func->body = std::make_unique<ScopeContext>();

                size_t varIndex = 0;
                for(auto var : globals)
                {
                    if(var->type.storageType == ValueType::Struct)
                    {
                        auto globalRef = new LabeledValueReferenceContext{};
                        globalRef->value = var;
                        globalRef->returnType = *var;

                        auto constructCall = new FunctionCallContext{};
                        constructCall->arguments.emplace_back(globalRef);
                        std::string error;
                        if(!resolveFunctionCall(var->type.identifier + "::_destruct", constructCall, error))
                            recordError(ctx->start, error);
                        func->body->statements.emplace_back(constructCall);
                    }
                    varIndex++;
                }
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
            _result.scriptContext->functionOrder.clear();

            /* To avoid invalid pointers being left over, we just remove all exports this script has defined in the past
             * This shouldn't affect script analyzation since inter-script linking is still recursively possible through
             * the script context */
            if(_extractOnlyIdentifiers)
            {
                for(auto& lib : _result.scriptContext->exports)
                    _analyzer.deregisterLibrary(lib.second.get());
                _result.scriptContext->imports.clear();
            }

            antlr4::ANTLRInputStream input(_result.document);

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
            _analyzationContexts.insert({path, std::make_unique<AnalyzationContext>()});
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
        assert(std::filesystem::exists(path));
        for(const auto& entry : std::filesystem::recursive_directory_iterator{path})
        {
            if(!entry.is_regular_file())
                continue;
            if(entry.path().extension() != ".bs")
                continue;
            load(entry.path().string(), false);
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

} // namespace BraneScript
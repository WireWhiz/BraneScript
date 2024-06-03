//
// Created by wirewhiz on 10/8/23.
//

#include "documentReader.h"
#include "antlr4/braneBaseVisitor.h"
#include "braneLexer.h"
#include "documentSource.h"

#include <list>
#include "ast/module.h"
#include "ast/expressions.h"
#include <type_traits>

namespace BraneScript
{
    class DocumentParser : public braneBaseVisitor
    {
        std::list<ast::Message> _logs;
        std::shared_ptr<ast::DocSource> _rootSource;

        std::stack<ast::AstNode*> _lastNode;

        class BetterAny
        {
            void* value;
            std::function<void(void*)> destructor;
            std::function<void*(void*)> copy;

          public:
            BetterAny()
            {
                value = nullptr;
                destructor = nullptr;
            }

            BetterAny(BetterAny&& other)
            {
                value = other.value;
                destructor = other.destructor;
                copy = other.copy;
                other.value = nullptr;
                other.destructor = nullptr;
                other.copy = nullptr;
            }

            BetterAny(const BetterAny& other)
            {
                value = other.copy(other.value);
                destructor = other.destructor;
                copy = other.copy;
            }

            template<typename T>
            BetterAny(T* value)
            {
                this->value = value;
                destructor = [](void* value) { delete (T*)value; };
                copy = [](void* value) { return new T(*(T*)value); };
            }

            template<typename T>
            BetterAny(T value)
            {
                this->value = new T(std::move(value));
                destructor = [](void* value) { delete (T*)value; };
                copy = [](void* value) { return new T(*(T*)value); };
            }

            ~BetterAny()
            {
                if(value && destructor)
                    destructor(value);
            }

            template<typename T>
            T* as()
            {
                return (T*)value;
            }

            /**
             * Casts the value to a pointer of type T, but only if the value is a subclass of Base.
             * Slightly safer than a normal cast.
             * @tparam Base
             * @tparam T
             * @return
             */
            template<typename Base, typename T>
            T* as_with_base()
            {
                return dynamic_cast<T*>((Base*)value);
            }

            template<typename T>
            T take()
            {
                T result = std::move(*as<T>());
                delete as<T>();
                value = nullptr;
                destructor = nullptr;
                return result;
            }
        };

        class BraneErrorListener : public antlr4::BaseErrorListener
        {
            DocumentParser& _parser;

          public:
            BraneErrorListener(DocumentParser& parser) : _parser(parser)
            {
            }

            void syntaxError(antlr4::Recognizer* recognizer,
                             antlr4::Token* offendingSymbol,
                             size_t line,
                             size_t charPositionInLine,
                             const std::string& msg,
                             std::exception_ptr e) override
            {
                if(offendingSymbol)
                    _parser.recordError(offendingSymbol,
                                           "Unexpected token: " + offendingSymbol->getText() + "\n" + msg);
                else
                    _parser.recordMessage(msg, {}, ast::Message::Severity::Error);
            }
        };

        TextRange toRange(const antlr4::Token* token)
        {
            if(!token)
                return _rootSource->range;
            return TextRange{token->getLine() - 1,
                             token->getCharPositionInLine(),
                             token->getLine() - 1,
                             token->getCharPositionInLine() + (token->getStopIndex() - token->getStartIndex()) + 1};
        };

        TextRange toRange(const antlr4::ParserRuleContext* ctx)
        {
            if(!ctx)
                return _rootSource->range;
            return TextRange{ctx->getStart()->getLine() - 1,
                             ctx->getStart()->getCharPositionInLine(),
                             ctx->getStop()->getLine() - 1,
                             ctx->getStop()->getCharPositionInLine() +
                                 (ctx->getStop()->getStopIndex() - ctx->getStop()->getStartIndex()) + 1};
        };

        void recordLog(const antlr4::Token* token, const std::string& message)
        {
            recordMessage(message, toRange(token), ast::Message::Severity::Info);
        }

        void recordLog(const antlr4::ParserRuleContext* ctx, const std::string& message)
        {
            recordMessage(message, toRange(ctx), ast::Message::Severity::Info);
        }

        void recordWarning(const antlr4::Token* token, const std::string& message)
        {
            recordMessage(message, toRange(token), ast::Message::Severity::Warning);
        }

        void recordWarning(const antlr4::ParserRuleContext* ctx, const std::string& message)
        {
            recordMessage(message, toRange(ctx), ast::Message::Severity::Warning);
        }

        void recordError(const antlr4::Token* token, const std::string& message)
        {
            recordMessage(message, toRange(token), ast::Message::Severity::Error);
        }

        void recordError(const antlr4::ParserRuleContext* ctx, const std::string& message)
        {
            recordMessage(message, toRange(ctx), ast::Message::Severity::Error);
        }

        void recordMessage(const std::string& message, const TextRange& range, ast::Message::Severity severity)
        {
            _logs.push_back(ast::Message{
                message,
                std::make_shared<ast::DocSource>(range, _rootSource->file),
                severity
            });
        }

        std::expected<ast::Ast, std::string> parseDocument(const std::string& text, std::optional<std::string> file = std::nullopt)
        {
            try {
                BraneErrorListener errorListener(*this);
                antlr4::ANTLRInputStream input(text);
                braneLexer lexer(&input);
                antlr4::CommonTokenStream tokens(&lexer);
                braneParser parser(&tokens);

                lexer.removeErrorListeners();
                lexer.addErrorListener(&errorListener);
                parser.removeErrorListeners();
                parser.addErrorListener(&errorListener);

                // Determine the number of lines and the last character of the document
                size_t lines = 0;
                size_t endChar = 0;
                for(char c : text)
                {
                    if(c != '\n')
                        endChar++;
                    else
                    {
                        lines++;
                        endChar = 0;
                    }
                }

                // Create the root source that represents the entire document
                _rootSource = std::make_shared<ast::DocSource>(TextRange{0, 0, lines, endChar},
                                                               std::make_shared<std::string>(file.value_or("")));

                // Parse the document
                auto ast = std::any_cast<ast::Ast>(std::move(visit(parser.modules())));
                ast.isValid = true;
                return ast;
            }
#if NDEBUG
            catch(std::exception& e)
            {
                return std::unexpected(e.what());
            }
#else
            catch(std::exception_ptr& e)
            {
                // If in debug mode, we want to rethrow the exception so we can see the stack trace
                rethrow_exception(e);
            }
#endif
        }

        /// Parsing code
        template<typename R, typename T>
        R visitT(T* ctx)
        {
            std::any result = visit(ctx);
            if(result.has_value())
                return std::any_cast<BetterAny>(result).take<R>();
            throw std::runtime_error("Invalid result type");
        }


        std::any visitModules(braneParser::ModulesContext *ctx) override {
            ast::Ast ast;
            for(auto& module : ctx->module())
            {
                auto result = visitT<ast::Module>(module);

                ast.modules.insert();
            }


            return ast;
        }

        std::any visitTags(braneParser::TagsContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitModule(braneParser::ModuleContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitModule_item(braneParser::Module_itemContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitImports(braneParser::ImportsContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitExports(braneParser::ExportsContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitImportModule(braneParser::ImportModuleContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitImportMemory(braneParser::ImportMemoryContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitMod_export(braneParser::Mod_exportContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitGlobal(braneParser::GlobalContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitTemplateDefArg(braneParser::TemplateDefArgContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitTemplateDef(braneParser::TemplateDefContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitTemplateTypeArg(braneParser::TemplateTypeArgContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitTemplateExprArg(braneParser::TemplateExprArgContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitPackExpansionArg(braneParser::PackExpansionArgContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitTemplateArgs(braneParser::TemplateArgsContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitScopedID(braneParser::ScopedIDContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitType(braneParser::TypeContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitValueType(braneParser::ValueTypeContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitRefType(braneParser::RefTypeContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitSliceType(braneParser::SliceTypeContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitDeclaration(braneParser::DeclarationContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitArgumentListItem(braneParser::ArgumentListItemContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitArgumentList(braneParser::ArgumentListContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitArgumentPackItem(braneParser::ArgumentPackItemContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitArgumentPack(braneParser::ArgumentPackContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitBracketOpr(braneParser::BracketOprContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitFunctionSig(braneParser::FunctionSigContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitFunctionStub(braneParser::FunctionStubContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitFunction(braneParser::FunctionContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitCapturedVar(braneParser::CapturedVarContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitVarCapture(braneParser::VarCaptureContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitStructDef(braneParser::StructDefContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitMemberFunctionStub(braneParser::MemberFunctionStubContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitMemberFunction(braneParser::MemberFunctionContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitMemberVariable(braneParser::MemberVariableContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitExpressions(braneParser::ExpressionsContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitDeref(braneParser::DerefContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitDecl(braneParser::DeclContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitFor(braneParser::ForContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitAddsub(braneParser::AddsubContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitPreDec(braneParser::PreDecContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitWhile(braneParser::WhileContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitSwitch(braneParser::SwitchContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitCast(braneParser::CastContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitParen(braneParser::ParenContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitLambda(braneParser::LambdaContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitNot(braneParser::NotContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitRef(braneParser::RefContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitMagicFunctionCall(braneParser::MagicFunctionCallContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitScope(braneParser::ScopeContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitId(braneParser::IdContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitIf(braneParser::IfContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitConstChar(braneParser::ConstCharContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitMemberAccess(braneParser::MemberAccessContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitComparison(braneParser::ComparisonContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitAssignment(braneParser::AssignmentContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitMatch(braneParser::MatchContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitConstBool(braneParser::ConstBoolContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitConstInt(braneParser::ConstIntContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitPostDec(braneParser::PostDecContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitMuldiv(braneParser::MuldivContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitPreInc(braneParser::PreIncContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitPostInc(braneParser::PostIncContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitIndexAccess(braneParser::IndexAccessContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitConstString(braneParser::ConstStringContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitFunctionCall(braneParser::FunctionCallContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitConstFloat(braneParser::ConstFloatContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitLogic(braneParser::LogicContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitReturn(braneParser::ReturnContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitSwitchCase(braneParser::SwitchCaseContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitMatchCase(braneParser::MatchCaseContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitSizeOfType(braneParser::SizeOfTypeContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitSizeOfPack(braneParser::SizeOfPackContext *ctx) override {
            return visitChildren(ctx);
        }

        std::any visitFail(braneParser::FailContext *ctx) override {
            return visitChildren(ctx);
        }
    };

    std::expected<ast::Ast, std::string> DocumentReader::readDocument(const std::string& text, std::optional<std::string> file)
    {
        DocumentParser parser;

        return std::unexpected("Not implemented yet!");
    }
}

#undef RETURN_ANY
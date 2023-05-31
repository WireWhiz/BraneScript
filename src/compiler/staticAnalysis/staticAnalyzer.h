#ifndef BRANESCRIPT_STATICANALYZER_H
#define BRANESCRIPT_STATICANALYZER_H

#include "documentContext.h"
#include "textPos.h"
#include <filesystem>
#include <string>
#include <vector>
#include <mutex>
#include <antlr4-runtime/ANTLRErrorListener.h>

namespace antlr4
{
    class ParserRuleContext;
    class ANTLRInputStream;
    class CommonTokenStream;
}
class braneLexer;
class braneParser;

namespace BraneScript
{

    class Library;
    class ConstexprEvaluator;

    struct AnalyzationMessage
    {
        TextRange range;
        std::string message;
    };

    class StaticAnalyzer
    {
      public:
        struct AnalyzationContext
        {
            std::string source;
            std::string document;
            struct ParseContext
            {
                std::unique_ptr<antlr4::ANTLRErrorListener> lexErrorListener;
                std::unique_ptr<antlr4::ANTLRErrorListener> parseErrorListener;
                std::unique_ptr<antlr4::ANTLRInputStream> inputStream;
                std::unique_ptr<braneLexer> lexer;
                std::unique_ptr<antlr4::CommonTokenStream> tokenStream;
                std::unique_ptr<braneParser> parser;
            } parseCtx;

            std::unique_ptr<ScriptContext> scriptContext;
            std::vector<AnalyzationMessage> errors;
            std::vector<AnalyzationMessage> warnings;
            bool complete = false;
            uint16_t version = 0;
            std::mutex lock;
        };
      private:

        std::vector<std::string> _workspaceRoots;
        robin_hood::unordered_set<ModuleContext*> _nativeModules;
        robin_hood::unordered_map<std::string, ModuleContext*> _modules;
        robin_hood::unordered_map<std::string, std::unique_ptr<AnalyzationContext>> _analyzationContexts;

        ConstexprEvaluator* _evaluator = nullptr;
      public:
        StaticAnalyzer();
        ~StaticAnalyzer();

        /** @brief Register a workspace
         * This folder and it's children will be searched for brane script related files and scanned so that references
         * can be made correctly
         */
        void addWorkspace(const std::string& path, bool allowUnsafe = false);

        bool isLoaded(const std::string& path);
        void load(const std::string& path, bool cacheDocument = true, bool allowUnsafe = false);
        void load(const std::string& path, std::string document, bool cacheDocument = true,  bool allowUnsafe = false);
        void reload(const std::string& path);

        bool isValid(const std::string& path);
        IRScript compile(const std::string& path);

        AnalyzationContext* getCtx(const std::string& path);

        bool registerModule(ModuleContext* lib);
        void deregisterModule(ModuleContext* lib);
        ModuleContext* getModule(const std::string& id) const;

        void setConstexprEvaluator(ConstexprEvaluator* evaluator);
        ConstexprEvaluator* constexprEvaluator() const;

        /**
         * @brief Validates a document will successfully compile, and populates all the fields of AnalyzationResult
         * @return Document will compile
         * */
        bool validate(const std::string& path, bool allowUnsafe = false);

    };

} // namespace BraneScript

#endif // BRANESCRIPT_STATICANALYZER_H

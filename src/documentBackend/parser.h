#ifndef BRANESCRIPT_ANALYZER_H
#define BRANESCRIPT_ANALYZER_H

#include <ANTLRErrorListener.h>
#include <filesystem>
#include <mutex>
#include <string>
#include <vector>
#include "documentContext.h"
#include "textPos.h"

namespace antlr4
{
    class ParserRuleContext;
    class ANTLRInputStream;
    class CommonTokenStream;
} // namespace antlr4
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

    class Parser
    {
      public:
        struct ParserContext
        {
            std::string source;
            std::string document;

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
        robin_hood::unordered_map<std::string, std::unique_ptr<ParserContext>> _analyzationContexts;

        ConstexprEvaluator* _evaluator = nullptr;

      public:
        Parser();
        ~Parser();

        /** @brief Register a workspace
         * This folder and it's children will be searched for brane script related files and scanned so that references
         * can be made correctly
         */
        void addWorkspace(const std::string& path, bool allowUnsafe = false);

        bool isLoaded(const std::string& path);
        void load(const std::string& path, bool cacheDocument = true, bool allowUnsafe = false);
        void load(const std::string& path, std::string document, bool cacheDocument = true, bool allowUnsafe = false);
        void reload(const std::string& path);

        bool isValid(const std::string& path);
        IRScript compile(const std::string& path, uint8_t flags = CompileFlags_Optimize);

        ParserContext* getCtx(const std::string& path);

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

#endif // BRANESCRIPT_ANALYZER_H

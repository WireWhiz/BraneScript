#ifndef BRANESCRIPT_STATICANALYZER_H
#define BRANESCRIPT_STATICANALYZER_H

#include "documentContext.h"
#include "textPos.h"
#include <filesystem>
#include <string>
#include <vector>
#include <mutex>

namespace antlr4
{
    class ParserRuleContext;
}

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
            std::unique_ptr<ScriptContext> scriptContext;
            std::vector<AnalyzationMessage> errors;
            std::vector<AnalyzationMessage> warnings;
            bool complete = false;
            uint16_t version = 0;
            std::mutex lock;
        };
      private:

        std::vector<std::string> _workspaceRoots;
        robin_hood::unordered_map<const Library*, std::unique_ptr<LibraryContext>> _nativeLibraries;
        robin_hood::unordered_map<std::string, std::unique_ptr<LibrarySet>> _libraries;
        robin_hood::unordered_map<std::string, std::unique_ptr<AnalyzationContext>> _analyzationContexts;

        // First key is library/export name, second is the document that the section of text was exported from
        robin_hood::unordered_map<std::string, robin_hood::unordered_map<std::string, std::string>> exportedTemplateText;


        ConstexprEvaluator* _evaluator;

      public:
        StaticAnalyzer();

        /** @brief Register a workspace
         * This folder and it's children will be searched for brane script related files and scanned so that references
         * can be made correctly
         */
        void addWorkspace(const std::string& path);

        bool isLoaded(const std::string& path);
        void load(const std::string& path, bool cacheDocument = false);
        void load(const std::string& path, std::string document, bool cacheDocument = true);
        void reload(const std::string& path);

        AnalyzationContext* getCtx(const std::string& path);

        void registerLibrary(LibraryContext* lib);
        void deregisterLibrary(LibraryContext* lib);
        LibrarySet* getLibrary(const std::string& id);

        void appendTemplateHeaders(const std::string& lib, const std::string& currentDocument, std::string& stream);

        void setConstexprEvaluator(ConstexprEvaluator* evaluator);

        /**
         * @brief Validates a document will successfully compile, and populates all the fields of AnalyzationResult
         * @return Document will compile
         * */
        bool validate(const std::string& path);

    };

} // namespace BraneScript

#endif // BRANESCRIPT_STATICANALYZER_H

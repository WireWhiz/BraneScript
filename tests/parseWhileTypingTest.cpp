#include "testing.h"

#include "constexprEvaluator.h"
#include "analyzer.h"

using namespace BraneScript;

//Test to weed out any errors that might be caused by incomplete grammar or tokens.
TEST(BraneScript, ParseWhileTyping)
{
    std::string path = "testScripts/parseWhileTypingTest.bs";
    std::string targetString;
    std::ifstream targetFile(path, std::ios::ate | std::ios::binary);
    if (targetFile.is_open())
    {
        auto fileSize = targetFile.tellg();
        targetString.resize(fileSize);
        targetFile.seekg(0);
        targetFile.read(targetString.data(), fileSize);
        targetFile.close();
    }
    else
        FAIL() << "Failed to open file: " << path;

    std::string testString;

    ConstexprEvaluator evaluator;
    Parser analyzer;
    analyzer.setConstexprEvaluator(&evaluator);
    analyzer.load(path, testString);

    for (size_t i = 0; i < targetString.size(); i++)
    {
        //Copy characters over, one at a time to simulate the act of typing.
        analyzer.getCtx(path)->document += targetString[i];
        analyzer.load(path);
        analyzer.validate(path);
    }
}
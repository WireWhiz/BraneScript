#include "testing.h"

#include "constexprEvaluator.h"
#include "analyzer.h"

using namespace BraneScript;

//Test to weed out any errors that might be caused by incomplete grammar or tokens.
TEST(BraneScript, ParseWhileTyping)
{
    std::string path = "testScripts/parseWhileTypingTest.bs";
    std::string targetString = R"(
module "tests0"
link "string"
{
    string testConst()
    {
        return "Hello World!";
    }
    char returnE()
    {
        return "ABCDE"[4];
    }
    string concat(ref string a, ref string b)
    {
        return a + b;
    }
    bool strEQ(ref string a, ref string b)
    {
        return a == b;
    }
    bool strNEQ(ref string a, ref string b)
    {
        return a != b;
    }
}
module "tests1"
{
    template<typedef Arg1, typedef Arg2>
    Arg1 add(Arg1 a, Arg2 b)
    {
        return a + b;
    }

    int addIntExplicit(int a, int b)
    {
        return add<int, int>(a, b);
    }

    int addIntExplicit2(int a, int b)
    {
        return add<int, int>(a, b) + add<int, int>(a, b);
    }

    float addFloatExplicit(float a, float b)
    {
        return add<float, float>(a, b);
    }

    template<typedef T1, typedef T2>
    struct TestPair
    {
        T1 first;
        T2 second;
    }

    TestPair<int, float> generatePair(int a, float b)
    {
        TestPair<int, float> output;
        output.first = a;
        output.second = b;
        return output;
    }

    template<typedef T, typedef... Args>
    T sumRecursive(T value, Args... args)
    {
        if(sizeof...(Args) != 0)
            return value + sumRecursive<Args...>(args...);
        return value;
    }

    int sum4(int v1, int v2, int v3, int v4)
    {
        return sumRecursive<int, int, int, int>(v1, v2, v3, v4);
    }

    template<int i>
    int sumTemplate()
    {
        if(i > 1)
            return i + sumTemplate<i - 1>();
        return 1;
    }

    int testTemplateExprArg()
    {
        return sumTemplate<6>();
    }
}
module "tests2"
{
    bool func(int a, float b, bool c)
    {
        return true;
    }
    int func(int a)
    {
        return 1;
    }
    int func()
    {
        return 0;
    }
    int func(int a, float b)
    {
        return 2;
    }
}
module "tests3"
link "lambda"
link "string"
{
    int testSimpleRefCapture(int value)
    {
        int testValue = 0;
        void Lambda[ref testValue](int v)
        {
            testValue = v;
        }(value);
        return testValue;
    }

    string testStructRefCapture(ref string value)
    {
        string testValue = "";
        void Lambda[ref testValue](ref string v)
        {
            testValue = v;
        }(value);
        return testValue;
    }

    Lambda<int> returnInt(int value)
    {
        float capturedValue = value;
        return int Lambda[capturedValue]()
        {
            return capturedValue;
        };
    }

    int callIntLambda(ref Lambda<int> lambda)
    {
        return lambda();
    }

    Lambda<string> returnString(ref string value)
    {
        return string Lambda[value]()
        {
            return value;
        };
    }

    string callStringLambda(ref Lambda<string> lambda)
    {
        return lambda();
    }
}
)";

    std::string testString;

    ConstexprEvaluator evaluator;
    Analyzer analyzer;
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
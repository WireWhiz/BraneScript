#include <iostream>
#include <list>
#include <ncurses.h>

std::list<std::string> prompts;

std::string getPrompt()
{
    std::cout << "> ";

    std::string newPrompt;
    auto currentPrompt = prompts.end();

    bool prompting = true;
    while(prompting)
    {
        char c = getchar();
        std::cout << "entered char: " << c << std::endl;
        if(c == '\n')
            prompting = false;
        newPrompt += c;
    }
    prompts.push_back(newPrompt);
    if(prompts.size() > 30)
        prompts.pop_front();
    return newPrompt;
}

int main(int argc, char* argv[])
{
    std::cout << "BraneScript console interface version 0.0.0\n"
                 "type \"help\" for a list of commands" << std::endl;

    bool running = argc > 0;
    do
    {
        running = getPrompt() != "exit";
    }
    while(running);
    std::cout << "Exiting BraneScript console interface." << std::endl;
    return 0;
}

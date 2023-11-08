
#include <cstdio>
#include <filesystem>
#include <string>
#include <vector>

#include <analyzer.h>

using namespace BraneScript;

bool isOption(std::string_view arg)
{
    return arg[0] == '-';
}

bool hasOption(std::string_view arg, const std::vector<std::string_view>& args)
{
    for(auto it = args.begin(); it != args.end(); ++it)
    {
        if(*it == arg)
            return true;
    }
    return false;
}

std::string_view getOptionValue(std::string_view arg, const std::vector<std::string_view>& args)
{
    for(auto it = args.begin(); it != args.end(); ++it)
    {
        if(*it == arg)
        {
            if(it + 1 != args.end())
                return *(it + 1);
            else
                return "";
        }
    }
    return "";
}

std::vector<std::string_view> getOptionValues(std::string_view arg, const std::vector<std::string_view>& args)
{
    std::vector<std::string_view> values;
    for(auto it = args.begin(); it != args.end(); ++it)
    {
        if(*it == arg)
        {
            for(auto vit = it + 1; vit != args.end() && !isOption(*vit); ++vit)
                values.emplace_back(*vit);
            break;
        }
    }
    return values;
}

int main(int argc, char** argv)
{
    std::vector<std::string_view> args;
    args.reserve(argc);
    for(int i = 0; i < argc; ++i)
        args.emplace_back(argv[i]);

    if(hasOption("-h", args) || hasOption("--help", args))
    {
        printf("Brane Script CLI Tool v0.1\n"
               "This tool is intended for internal use, specifically generating modules for the native include files.\n"
               "However, feel free to use it for whatever else you want\n"
               "Usage: bsCLI file [options]\n"
               "File must always be the first argument, followed by options if desired, otherwise default settings will be used and a module file(s) will be created in the same directory as the source.\n"
               "Options:\n"
               "-h, --help: Display this help message.\n"
               "-o, --output: Specify the output directory, outputted files will still be named after the modules they contain.\n"
               "-m, -module: If this option is used, only the specified module(s) will be output. (However all will still be analyzed and compiled internally)\n"
               "-l, --link: Specify file(s) or directory(s) with definitions of modules you want to link to.\n"
               "-u, --unsafe: Allow the use of the unsafe modules.\n"
               "-O: Toggle optimization level, 0 for off, 1 for on. More granular control may be added in the future (Default is 0)\n"
               "--no-debug: Disable emitting debug info.\n"
               "-p, --print: Print the generated IR.\n");
        return 0;
    }

    if(argc < 2)
    {
        printf("Error: No input file specified.\n");
        return 1;
    }
    std::string_view filename = argv[1];
    if(filename[0] == '-')
    {
            printf("Error: Input file must be the first argument.\n");
            return 1;
    }
    std::filesystem::path inputPath = filename;
    if(!std::filesystem::exists(inputPath))
    {
            printf("Error: Input file does not exist.\n");
            return 1;
    }
    if(!std::filesystem::is_regular_file(inputPath))
    {
        printf("Error: Input file path does not point to a file.\n");
        return 1;
    }

    std::filesystem::path outputPath = getOptionValue("-o", args);
    if(outputPath.empty())
        outputPath = getOptionValue("--output", args);
    if(outputPath.empty())
        outputPath = inputPath.parent_path();
    if(!std::filesystem::exists(outputPath))
        std::filesystem::create_directory(outputPath);

    Parser analyzer;

    const bool allowUnsafe = hasOption("-u", args) || hasOption("--unsafe", args);

    std::vector<std::string_view> linkPaths = getOptionValues("-l", args);
    if(linkPaths.empty())
        linkPaths = getOptionValues("--link", args);

    for(auto& linkPath : linkPaths)
    {
        if(std::filesystem::is_regular_file(linkPath))
            analyzer.load((std::string)linkPath, true, allowUnsafe);
        else if(std::filesystem::is_directory(linkPath))
            analyzer.addWorkspace((std::string)linkPath, allowUnsafe);
        else
        {
            printf("Error: Link path '%s' does not point to a file or directory.\n", linkPath.data());
            return 1;
        }
    }

    int optimizationLevel = 0;
    std::string_view optimizationLevelStr = getOptionValue("-O", args);
    if(!optimizationLevelStr.empty())
    {
        try {
            optimizationLevel = std::stoi(optimizationLevelStr.data());
        } catch(std::invalid_argument& e) {
            printf("Error: Optimization level must be an int value between 0 and 1 '%s'.\n", optimizationLevelStr.data());
            return 1;
        }
        if(optimizationLevel > 1 || optimizationLevel < 0)
        {
            printf("Error: Optimization level must be an int value between 0 and 1 '%s'.\n", optimizationLevelStr.data());
            return 1;
        }
    }

    const bool emitDebugInfo = !hasOption("--no-debug", args);
    const bool printIR = hasOption("-p", args) || hasOption("--print", args);

    analyzer.load(inputPath.string(), true, allowUnsafe);
    analyzer.validate(inputPath.string(), allowUnsafe);
    auto ctx = analyzer.getCtx(inputPath.string());
    if(!ctx->errors.empty())
    {
        printf("Compilation failed:\n");
        for(auto& err : ctx->errors)
            fprintf(stderr, "  (%zu, %zu) %s\n", err.range.start.line, err.range.start.charPos, err.message.c_str());
        return 1;
    }
    if((!ctx->warnings.empty()))
    {
        printf("Compilation succeeded with warnings:\n");
        for(auto& warn : ctx->warnings)
        printf("  (%zu, %zu) %s\n", warn.range.start.line, warn.range.start.charPos, warn.message.c_str());
    }

    uint8_t flags = 0;
    if(optimizationLevel == 1)
        flags |= CompileFlags_Optimize;
    if(emitDebugInfo)
        flags |= CompileFlags_DebugInfo;
    if(printIR)
        flags |= CompileFlags_PrintIR;
    IRScript script = analyzer.compile(inputPath.string(), flags);

    robin_hood::unordered_set<std::string_view> outputtedModules;
    for(auto m : getOptionValues("-m", args))
        outputtedModules.emplace(m);
    for(auto m : getOptionValues("--module", args))
        outputtedModules.emplace(m);

    if(outputtedModules.empty())
    {
        for(auto& module : script.modules)
            outputtedModules.emplace(module.first);
    }

    for(auto& module : script.modules)
    {
        if(!outputtedModules.contains(module.first))
            continue;
        std::filesystem::path modulePath = outputPath / (module.first + ".bsm");
        std::ofstream file(modulePath, std::ios::binary);
        if(!file.is_open())
        {
            printf("Error: Failed to write to '%s'!\n", modulePath.string().c_str());
            return 1;
        }
        SerializedData moduleData;

        OutputSerializer serializer(moduleData);
        module.second.serialize(serializer);

        printf("Writing module '%s' to '%s'...\n", module.first.c_str(), modulePath.string().c_str());
        file.write((const char*)moduleData.data(), moduleData.size());
        file.close();
    }
    printf("Operation successful.\n");
    return 0;
}

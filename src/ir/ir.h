#ifndef BRANESCRIPT_IR_H
#define BRANESCRIPT_IR_H

#include <string>
#include <variant>
#include <unordered_map>
#include "nodes.h"
#include "tree_sitter/api.h"

struct SourceInfo
{
    std::string source;
    TSRange range;
};

struct TemplateArg
{

};

struct Identifier
{
    std::string name;  
    std::optional<std::vector<TemplateArg>> templateArgs;
};

struct ScopedIdentifier
{
    std::vector<Identifier> scopes;

    std::string longName() const;

    void operator+=(ScopedIdentifier& other);
    void operator+=(ScopedIdentifier&& other);
};

using Expression = void*; //TODO 
using AsyncOperation = void*; //TODO

struct PipelineStage: IRNode
{
    std::vector<Expression> expressions;
    std::vector<AsyncOperation> asyncOps;
};

struct PipelineDebugInfo
{
    SourceInfo source;
};

struct Pipeline: IRNode
{
    std::string name;
    std::optional<PipelineDebugInfo> debugInfo;
    //std::vector<Type> inputs;
    //std::vector<Type> outputs;
    std::vector<PipelineStage> stages;
};

struct Function: IRNode
{

};

struct Module: IRNode
{
    std::string name;
    std::unordered_map<std::string, std::shared_ptr<Pipeline>> pipelines;
};

#endif

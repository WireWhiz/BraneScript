//
// Created by wirewhiz on 15/10/22.
//

#include "irScript.h"

void BraneScript::IRStructDef::serialize(OutputSerializer out)
{
    out << name;
    out << (uint32_t)members.size();
    for(auto& m : members)
    {
        out << m.name;
        out << m.type;
        out << m.isRef;
    }
    out << constructorSig;
    out << destructorSig;
    out << copyConstructorSig;
    out << moveConstructorSig;
    out << tags;
}

void BraneScript::IRStructDef::deserialize(InputSerializer in)
{
    in >> name;
    uint32_t numMembers;
    in >> numMembers;
    members.resize(numMembers);
    for(auto& m : members)
    {
        in >> m.name;
        in >> m.type;
        in >> m.isRef;
    }
    in >> constructorSig;
    in >> destructorSig;
    in >> copyConstructorSig;
    in >> moveConstructorSig;
    in >> tags;
}

void BraneScript::IRFunction::serialize(OutputSerializer out)
{
    out << name;
    out << returnType;
    out << tags;
}

void BraneScript::IRFunction::deserialize(InputSerializer in)
{
    in >> name;
    in >> returnType;
    in >> tags;
}

void BraneScript::IRGlobal::serialize(OutputSerializer out) {
        out << name;
        out << type;
}

void BraneScript::IRGlobal::deserialize(InputSerializer in) {
        in >> name;
        in >> type;
}

void BraneScript::IRModule::serialize(OutputSerializer out) {
        out << id;
        out << bitcode;
        out << tags;
        out << (uint32_t)functions.size();
        for(auto& f : functions)
            f.serialize(out);
        out << (uint32_t)globals.size();
        for(auto& g : globals)
            g.serialize(out);
        out << (uint32_t)structs.size();
        for(auto& s : structs)
            s.serialize(out);
        out << links;
}

void BraneScript::IRModule::deserialize(InputSerializer in)
{
        in >> id;
        in >> bitcode;
        in >> tags;
        uint32_t numFunctions;
        in >> numFunctions;
        functions.resize(numFunctions);
        for(auto& f : functions)
            f.deserialize(in);
        uint32_t numGlobals;
        in >> numGlobals;
        globals.resize(numGlobals);
        for(auto& g : globals)
            g.deserialize(in);
        uint32_t numStructs;
        in >> numStructs;
        structs.resize(numStructs);
        for(auto& s : structs)
            s.deserialize(in);
        in >> links;
}

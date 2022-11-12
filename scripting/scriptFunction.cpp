//
// Created by wirewhiz on 14/10/22.
//

#include "scriptFunction.h"
#include <cassert>
#include <stdexcept>

namespace BraneScript
{
    void ScriptFunction::appendCode(Operand op)
    {
        code.push_back(op);
    }

    void ScriptFunction::appendCode(const std::string& string)
    {
        assert(string.size() < 256);
        code.reserve(code.size() + string.size() + 1);
        code.push_back(string.size());
        for(char c : string)
            code.push_back(c);
    }


    std::string ScriptFunction::readString(size_t& index)
    {
        if(index >= code.size())
            throw std::runtime_error("Tried to read past end of data");
        size_t strSize = code[index];
        ++index;
        if(index + strSize > code.size())
            throw std::runtime_error("Tried to read past end of data");
        std::string string;
        string.resize(strSize);
        std::memcpy(string.data(), code.data() + index, strSize);
        index += strSize;
        return std::move(string);
    }
}
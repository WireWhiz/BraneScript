#include "irFunction.h"
#include <cassert>
#include <stdexcept>
#include <cstring>

namespace BraneScript
{
    void IRFunction::appendCode(Operand op)
    {
        code.push_back(op);
    }

    void IRFunction::appendCode(const std::string& string)
    {
        assert(string.size() < 256);
        code.reserve(code.size() + string.size() + 1);
        code.push_back(string.size());
        for(char c : string)
            code.push_back(c);
    }

    void IRFunction::appendCode(Operand op, Value a)
    {
        size_t index = code.size();
        code.resize(code.size() + sizeof(op) + sizeof(a));
        code[index] = op;
        index += sizeof(Operand);
        *(Value*)(code.data() + index) = a;
    }

    void IRFunction::appendCode(Operand op, Value a, Value b)
    {
        size_t index = code.size();
        code.resize(code.size() + sizeof(op) + sizeof(a) + sizeof(b));
        code[index] = op;
        index += sizeof(Operand);
        *(Value*)(code.data() + index) = a;
        index += sizeof(Value);
        *(Value*)(code.data() + index) = b;
    }

    void IRFunction::appendCode(Operand op, int16_t index)
    {
        appendCode(op);
        appendCode(index);
    }

    void IRFunction::appendCode(Operand op, uint16_t index)
    {
        appendCode(op);
        appendCode(index);
    }

    void IRFunction::appendCode(Operand op, uint32_t index)
    {
        appendCode(op);
        appendCode(index);
    }
}
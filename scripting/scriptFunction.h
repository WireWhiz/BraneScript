//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_SCRIPTFUNCTION_H
#define BRANESCRIPT_SCRIPTFUNCTION_H

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include "baseTypes.h"
#include "aotNode/aotNode.h"
#include "operands.h"
namespace BraneScript
{
    class ScriptFunction
    {
    public:


        std::vector<uint8_t> code;
        std::vector<std::string> arguments;
        std::string returnType = "void";
        std::string name;

        void appendCode(Operand op);
        void appendCode(const std::string& string);

        template<typename A>
        void appendCode(Operand op, A a)
        {
            static_assert(!std::is_same<A, AotNode>());
            size_t index = code.size();
            code.resize(code.size() + sizeof(op) + sizeof(a));
            code[index] = op;
            index += sizeof(Operand);
            *(A*)(code.data() + index) = a;
        }

        template<typename A, typename B>
        void appendCode(Operand op, A a, B b)
        {
            static_assert(!std::is_same<A, AotNode>() && !std::is_same<B, AotNode>());
            size_t index = code.size();
            code.resize(code.size() + sizeof(op) + sizeof(a) + sizeof(b));
            code[index] = op;
            index += sizeof(Operand);
            *(A*)(code.data() + index) = a;
            index += sizeof(A);
            *(B*)(code.data() + index) = b;
        }

        template<typename T>
        void appendCode(T value)
        {
            static_assert(!std::is_same<T, AotNode>());
            size_t index = code.size();
            code.resize(code.size() + sizeof(T));
            *(T*)(code.data() + index) = value;
        }

        template<typename T>
        T readCode(size_t& index)
        {
            T value = *(T*)&code[index];
            index += sizeof(T);
            return value;
        }

        std::string readString(size_t& index);
    };
}

#endif //BRANESCRIPT_SCRIPTFUNCTION_H

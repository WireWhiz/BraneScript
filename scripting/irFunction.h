//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_IRFUNCTION_H
#define BRANESCRIPT_IRFUNCTION_H

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include "baseTypes.h"
#include "aotNode/aotNode.h"
#include "operands.h"
#include "typeInfo.h"

namespace BraneScript
{
    class IRFunction
    {
    public:

        std::vector<uint8_t> code;

        std::vector<TypeInfo> arguments;
        TypeInfo returnType = {"void"};
        std::string name;

        void appendCode(Operand op);
        void appendCode(const std::string& string);

        void appendCode(Operand op, Value a);
        void appendCode(Operand op, Value a, Value b);
        void appendCode(Operand op, uint16_t index);
        void appendCode(Operand op, uint32_t index);

        template<typename T>
        void appendCode(Operand op, Value a, T value)
        {
            appendCode(op, a);
            static_assert(!std::is_same<AotValue, T>());
            size_t index = code.size();
            code.resize(code.size() + sizeof(T));
            *(T*)(code.data() + index) = value;
        }

        template<typename T>
        void appendCode(T value)
        {
            static_assert(!std::is_same<AotValue, T>());
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

#endif //BRANESCRIPT_IRFUNCTION_H

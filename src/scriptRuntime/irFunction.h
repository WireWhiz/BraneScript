//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_IRFUNCTION_H
#define BRANESCRIPT_IRFUNCTION_H

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include "operands.h"
#include "typeInfo.h"

namespace BraneScript
{
    class IRFunction
    {
    public:
        std::string sig;
        TypeInfo returnType = {"void"};
        std::vector<TypeInfo> arguments;
        std::vector<uint8_t> code;
        uint16_t maxRegs = 0;
        uint16_t maxMemLocations = 0;

        template<typename T>
        T readCode(size_t& index)
        {
            T value = *(T*)&code[index];
            index += sizeof(T);
            return value;
        }
    };
}

#endif //BRANESCRIPT_IRFUNCTION_H

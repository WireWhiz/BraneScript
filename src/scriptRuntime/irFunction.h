//
// Created by wirewhiz on 14/10/22.
//

#ifndef BRANESCRIPT_IRFUNCTION_H
#define BRANESCRIPT_IRFUNCTION_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>
#include "operands.h"
#include "typeInfo.h"
#include <unordered_map>

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
        bool isExported = false;

        template<typename T>
        T readCode(size_t& index)
        {
            if(index + sizeof(T) > code.size())
                throw std::runtime_error("Attempted to read past end of code!");
            T value = *(T*)&code[index];
            index += sizeof(T);
            return value;
        }
    };
} // namespace BraneScript

#endif // BRANESCRIPT_IRFUNCTION_H

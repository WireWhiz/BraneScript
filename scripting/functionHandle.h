//
// Created by eli on 11/4/2022.
//

#ifndef BRANESCRIPT_FUNCTIONHANDLE_H
#define BRANESCRIPT_FUNCTIONHANDLE_H

#include <string>
#include <unordered_map>
#include <cassert>

namespace BraneScript
{
#define BS_API_CALL __cdecl

    template<typename Ret, typename... Args>
    using FunctionHandle = Ret (BS_API_CALL*)(Args...);

    template<typename T>
    std::string typeName()
    {
        std::string name;
        if constexpr(std::is_same<T, bool>())
            name = "bool";
        if constexpr(std::is_same<T, int32_t>())
            name = "int";
        if constexpr(std::is_same<T, float>())
            name = "float";
        if constexpr(std::is_same<T, double>())
            name = "double";
        return name;
    }

    template<typename T, typename... Types>
    std::string argsToString()
    {
        std::string name = typeName<T>();

        assert(!name.empty());
        if constexpr(sizeof...(Types))
            return name + "," + argsToString<Types...>();
        else
            return name;
    }

    std::vector<std::string> extractArgs(const std::string& funcDecl);
}


#endif //BRANESCRIPT_FUNCTIONHANDLE_H

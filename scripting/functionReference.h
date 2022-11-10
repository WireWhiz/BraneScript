//
// Created by eli on 11/4/2022.
//

#ifndef BRANESCRIPT_FUNCTIONREFERENCE_H
#define BRANESCRIPT_FUNCTIONREFERENCE_H

#include <string>
#include <unordered_map>
#include <cassert>

namespace BraneScript
{
    template<typename Ret, typename... Args>
    using FunctionHandle = Ret (__cdecl*)(Args...);

    template<typename T, typename... Types>
    static std::string argsToString()
    {
        std::string typeName;
        if constexpr(std::is_same<T, bool>())
            typeName = "bool";
        if constexpr(std::is_same<T, int32_t>())
            typeName = "int";
        if constexpr(std::is_same<T, float>())
            typeName = "float";
        if constexpr(std::is_same<T, double>())
            typeName = "double";

        assert(!typeName.empty());
        if constexpr(sizeof...(Types))
            return typeName  + "," + argsToString<Types...>();
        else
            return typeName;
    }
}


#endif //BRANESCRIPT_FUNCTIONREFERENCE_H

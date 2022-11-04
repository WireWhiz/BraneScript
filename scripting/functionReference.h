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

    class FunctionReference
    {
        template<typename T, typename... Types>
        static std::string argNames()
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
                return typeName  + "," + argNames<Types...>();
            else
                return typeName;
        }
    public:
        std::string name;
        std::unordered_map<std::string, void*> overrides;

        template<typename Ret, typename... Args>
        FunctionHandle<Ret, Args...> getOverride()
        {

            std::string args;
            if constexpr(sizeof...(Args))
                args = argNames<Args...>();

            auto f = overrides.find(args);
            if (f == overrides.end())
                return nullptr;
            return (FunctionHandle<Ret, Args...>)f->second;
        }
    };
}


#endif //BRANESCRIPT_FUNCTIONREFERENCE_H

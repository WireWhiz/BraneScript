//
// Created by eli on 11/4/2022.
//

#ifndef BRANESCRIPT_FUNCTIONHANDLE_H
#define BRANESCRIPT_FUNCTIONHANDLE_H

#include <string>
#include <unordered_map>
#include <cassert>
#include <vector>

namespace BraneScript
{
    class Linker;
#if _WIN32
#define BS_API_CALL __cdecl
#elif __unix__
#define BS_API_CALL __attribute__((cdecl))
#endif

    template<typename Ret, typename... Args>
    using FunctionHandle = Ret (BS_API_CALL*)(Args...);

    /**
     * @brief Class for extracting data about arguments from a function definition.
     *
     * Format to be used: name(type,const type,const ref type,ref type)
     */
    class FuncDef
    {
        std::string _def;
        uint16_t _nameEnd;
        enum ArgFlags
        {
            ArgFlags_Const = 1,
            ArgFlags_Ref = 1 << 1
        };
        struct ArgData
        {
            uint16_t tStart = 0;
            uint16_t tEnd = 0;
            uint8_t  flags = 0;
        };
        std::vector<ArgData> _argIndices;
    public:
        FuncDef(std::string def);
        size_t argCount() const;
        std::string_view name() const;
        std::string_view argType(size_t index) const;
        bool argIsConst(size_t index) const;
        bool argIsRef(size_t index) const;
    };

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
        if constexpr(sizeof...(Types) > 0)
            return name + "," + argsToString<Types...>();
        else
            return name;
    }
}


#endif //BRANESCRIPT_FUNCTIONHANDLE_H

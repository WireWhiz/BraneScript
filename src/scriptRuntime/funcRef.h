//
// Created by eli on 11/4/2022.
//

#ifndef BRANESCRIPT_FUNCREF_H
#define BRANESCRIPT_FUNCREF_H

#include <string>
#include <unordered_map>
#include <cassert>
#include <vector>
#include <cstdint>

namespace BraneScript
{
#if _WIN32
#define BS_API_CALL __cdecl
#elif __unix__
#define BS_API_CALL __attribute__((cdecl))
#endif

    template<typename Ret, typename... Args>
    using FuncRef = Ret (*)(Args...);

    /**
     * @brief Class for extracting data about arguments from a function definition.
     *
     * Format to be used: name(type,const type,const ref type,ref type)
     */


    class FuncDef
    {
        std::string_view _def;
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
        FuncDef(std::string_view def);
        size_t argCount() const;
        std::string_view name() const;
        std::string_view argType(size_t index) const;
        bool argIsConst(size_t index) const;
        bool argIsRef(size_t index) const;
    };

    template<typename T>
    std::string typeName()
    {
        if constexpr(std::is_pointer<T>())
            return "ref " + typeName<typename std::remove_pointer<T>::type>();

        std::string name;
        if constexpr(std::is_same<T, void>())
            name = "void";
        if constexpr(std::is_same<T, bool>())
            name = "bool";
        if constexpr(std::is_same<T, int32_t>())
            name = "int";
        if constexpr(std::is_same<T, uint32_t>())
            name = "uint";
        if constexpr(std::is_same<T, int64_t>())
            name = "int64";
        if constexpr(std::is_same<T, uint64_t>())
            name = "uint64";
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

    struct FunctionData
    {
        std::string name;
        std::string ret;
        size_t argCount = 0;
        FuncDef def;
        void* pointer;

        FunctionData(std::string name, std::string ret, size_t argCount, void* pointer);
        FunctionData(const FunctionData&);
        FunctionData(FunctionData&&) noexcept ;

        template<typename Ret, typename... Args>
        FuncRef<Ret, Args...> as() const
        {
            return (FuncRef<Ret, Args...>)pointer;
        }

    };
}


#endif // BRANESCRIPT_FUNCREF_H

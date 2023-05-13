//
// Created by wirewhiz on 5/11/23.
//

#include "BSString.h"
#include <cstring>

namespace BraneScript
{
    BSString::BSString(const BSString& other)
    {
        _size = other._size;
        _data = new char[_size + 1];
        memcpy(_data, other._data, _size);
        ((char*)_data)[_size] = '\0';
    }

    BSString::BSString(BSString&& other) noexcept
    {
        _size = other._size;
        _data = other._data;
        other._data = nullptr;
        other._size = 0;
    }

    BSString::BSString(char c)
    {
        _size = 1;
        _data = new char[2];
        _data[0] = c;
        _data[1] = '\0';
    }

    BSString::BSString(const char* cstr)
    {
        _size = strlen(cstr);
        _data = new char[_size + 1];
        memcpy(_data, cstr, _size);
        ((char*)_data)[_size] = '\0';
    }

    BSString::~BSString()
    {
        delete[] _data;
    }

    BSString& BSString::operator=(const BSString& other)
    {
        delete[] _data;
        _size = other._size;
        _data = new char[_size + 1];
        memcpy(_data, other._data, _size);
        ((char*)_data)[_size] = '\0';
        return *this;
    }

    BSString& BSString::operator=(BSString&& other) noexcept {
        delete[] _data;
        _size = other._size;
        _data = other._data;
        other._data = nullptr;
        other._size = 0;
        return *this;
    }

    bool BSString::operator==(const BSString& other) const
    {
        return _size == other._size && memcmp(_data, other._data, _size) == 0;
    }

    bool BSString::operator!=(const BSString& other) const
    {
        return !(*this == other);
    }

    void BSString::append(const BSString& string)
    {
        char* newData = new char[_size + string._size + 1];
        memcpy(newData, _data, _size);
        memcpy(newData + _size, string._data, string._size);
        newData[_size + string._size] = '\0';
        delete[] _data;
        _data = newData;
        _size += string._size;
    }

    void BSString::append(const char* cstr)
    {
        auto newSize = _size + strlen(cstr);
        char* newData = new char[newSize + 1];
        memcpy(newData, _data, _size);
        memcpy(newData + _size, cstr, newSize - _size);
        newData[newSize] = '\0';
        delete[] _data;
        _data = newData;
        _size = newSize;
    }

    std::ostream& operator<<(std::ostream& os, const BSString& string)
    {
        os << string._data;
        return os;
    }

    NativeLibrary BSString::library()
    {
        NativeLibrary lib("string");
        lib.addFunction("string::string::_construct(ref string::string)", (FunctionHandle<void, void*>)[](void* ptr)
        {
            new(ptr) BSString();
        });
        lib.addFunction("string::string::_move(ref string::string,ref string::string)", (FunctionHandle<void, void*, void*>)[](void* ptr, void* other)
        {
            new(ptr) BSString(std::move(*(BSString*)other));
        });
        lib.addFunction("string::string::_copy(ref string::string,const ref string::string)", (FunctionHandle<void, void*, const void*>)[](void* ptr, const void* other)
        {
            new(ptr) BSString(*(BSString*)other);
        });
        lib.addFunction("string::string::_destruct(ref string::string)", (FunctionHandle<void, void*>)[](void* ptr)
        {
            ((BSString*)ptr)->~BSString();
        });
        lib.addFunction("string::string opr +(ref string::string res,const ref string::string,const ref string::string)", (FunctionHandle<void, BSString&, const BSString&, const BSString&>)[](BSString& res, const BSString& a, const BSString& b)
        {
            res = a + b;
        });
        lib.addFunction("string::string::opr [](ref string::string,uint)", (FunctionHandle<char*, BSString&, uint32_t>)[](BSString& str, uint32_t index)
        {
            return &str._data[index];
        });
        lib.addFunction("string::string::opr [](const ref string::string,uint)", (FunctionHandle<char, const BSString&, uint32_t>)[](const BSString& str, uint32_t index)
        {
            return str._data[index];
        });
        lib.addFunction("string::string::length(const ref string::string)", (FunctionHandle<uint32_t, const BSString&>)[](const BSString& str)
        {
            return str._size;
        });
        lib.addFunction("string::string::opr ==(const ref string::string,const ref string::string)", (FunctionHandle<bool, const BSString&, const BSString&>)[](const BSString& a, const BSString& b)
        {
            return a == b;
        });
        lib.addFunction("string::string::opr !=(const ref string::string,const ref string::string)", (FunctionHandle<bool, const BSString&, const BSString&>)[](const BSString& a, const BSString& b)
        {
            return a != b;
        });
        lib.addFunction("string::string::opr +(ref string:::string ret, char l,char r)", (FunctionHandle<void, BSString&, char, char>)[](BSString& ret, char l, char r)
        {
            ret = BSString(l) + r;
        });
        lib.addFunction("string::string::opr +(ref string::string,const ref string::string,const ref string::string)", (FunctionHandle<void, BSString&, const BSString&, const BSString&>)[](BSString& ret, const BSString& l, const BSString& r)
        {
            ret = l + r;
        });

        // This constructor hidden from the script api since ref string casts might go wrong, it also expects an uninitialized BSString, which goes against the BS calling convention
        lib.addFunction("string::stringFromCharArr(ref string::string, const ref char)", (FunctionHandle<void, BSString*, const char*>)[](BSString* str, const char* cstr)
        {
            new(str) BSString(cstr);
        });
        return std::move(lib);
    }

    BSString::BSString(std::string str) : BSString(str.c_str()) { }

    //Obviously very inefficient, will refactor later to decrease allocations
    void BSString::append(char c) {
        char* newData = new char[_size + 2];
        memcpy(newData, _data, _size);
        newData[_size] = c;
        newData[_size + 1] = '\0';
        delete[] _data;
        _data = newData;
        _size++;
    }

} // namespace BraneScript
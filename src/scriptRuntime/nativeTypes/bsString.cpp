//
// Created by wirewhiz on 5/11/23.
//

#include "bsString.h"
#include <cstring>
#include "scriptRuntime/structDef.h"

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
        if(_size > 0)
            delete[] _data;
    }

    BSString& BSString::operator=(const BSString& other)
    {
        if(_size > 0)
            delete[] _data;
        _size = other._size;
        _data = new char[_size + 1];
        memcpy(_data, other._data, _size);
        ((char*)_data)[_size] = '\0';
        return *this;
    }

    BSString& BSString::operator=(BSString&& other) noexcept {
        if(_size > 0)
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

    NativeLibrary getStringLibrary()
    {
        NativeLibrary lib("string");
        lib.addFunction("string::string::_construct(ref string::string)", (FuncRef<void, void*>)[](void* ptr)
        {
            new(ptr) BSString();
        });
        lib.addFunction("string::string::_move(ref string::string,ref string::string)", (FuncRef<void, void*, void*>)[](void* ptr, void* other)
        {
            *(BSString*)ptr = std::move(*(BSString*)other);
        });
        lib.addFunction("string::string::_copy(ref string::string,const ref string::string)", (FuncRef<void, void*, const void*>)[](void* ptr, const void* other)
        {
            *(BSString*)ptr = *(BSString*)other;
        });
        lib.addFunction("string::string::_destruct(ref string::string)", (FuncRef<void, void*>)[](void* ptr)
        {
            ((BSString*)ptr)->~BSString();
        });
        lib.addFunction("string::string opr +(ref string::string res,const ref string::string,const ref string::string)", (FuncRef<void, BSString&, const BSString&, const BSString&>)[](BSString& res, const BSString& a, const BSString& b)
        {
            res = a + b;
        });
        lib.addFunction("string::string::opr [](ref string::string,uint)", (FuncRef<char*, BSString&, uint32_t>)[](BSString& str, uint32_t index)
        {
            return &str[index];
        });
        lib.addFunction("string::string::opr [](const ref string::string,uint)", (FuncRef<char, const BSString&, uint32_t>)[](const BSString& str, uint32_t index)
        {
            return str[index];
        });
        lib.addFunction("string::string::length(const ref string::string)", (FuncRef<uint32_t, const BSString&>)[](const BSString& str)
        {
            return str.size();
        });
        lib.addFunction("string::string::opr ==(const ref string::string,const ref string::string)", (FuncRef<bool, const BSString&, const BSString&>)[](const BSString& a, const BSString& b)
        {
            return a == b;
        });
        lib.addFunction("string::string::opr !=(const ref string::string,const ref string::string)", (FuncRef<bool, const BSString&, const BSString&>)[](const BSString& a, const BSString& b)
        {
            return a != b;
        });
        lib.addFunction("string::opr +(ref string::string,char,char)", (FuncRef<void, BSString&, char, char>)[](BSString& ret, char l, char r)
        {
            ret = BSString(l) + r;
        });
        lib.addFunction("string::string::opr +(ref string::string,const ref string::string,const ref string::string)", (FuncRef<void, BSString&, const BSString&, const BSString&>)[](BSString& ret, const BSString& l, const BSString& r)
        {
            ret = l + r;
        });
        lib.addFunction("string::string::opr +(ref string::string,const ref string::string,char)", (FuncRef<void, BSString&, const BSString&, char>)[](BSString& ret, const BSString& l, char r)
        {
            ret = l + r;
        });

        // This constructor hidden from the script api since ref string casts might go wrong, it also expects an uninitialized BSString, which goes against the BS calling convention
        lib.addFunction("string::_stringFromCharArr(ref string::string,const ref char)", (FuncRef<void, BSString*, const char*>)[](BSString* str, const char* cstr)
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
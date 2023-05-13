//
// Created by wirewhiz on 5/11/23.
//

#ifndef BRANESCRIPT_BSSTRING_H
#define BRANESCRIPT_BSSTRING_H

#include <cstdint>
#include <ostream>
#include "nativeLibrary.h"

namespace BraneScript
{
    class BSString
    {
        char* _data = nullptr;
        uint32_t _size = 0;
      public:
        BSString() = default;
        BSString(const BSString& other);
        BSString(BSString&& other) noexcept;
        BSString(char c);
        BSString(const char* cstr);
        BSString(std::string str);
        ~BSString();

        BSString& operator=(const BSString& other);
        BSString& operator=(BSString&& other) noexcept;

        bool operator==(const BSString& other) const;
        bool operator!=(const BSString& other) const;
        BSString& operator+=(const BSString& other) { append(other); return *this; }
        BSString& operator+=(const char* other) { append(other); return *this; }
        BSString operator+(const BSString& other) const { BSString s(*this); s.append(other); return s; }
        BSString operator+(const char* other) const { BSString s(*this); s.append(other); return s; }
        BSString operator+(char c) const { BSString s(*this); s.append(c); return s; }
        operator std::string() const { return { _data, _size}; }

        void append(const BSString& string);
        void append(const char* cstr);
        void append(char c);
        const char* data() const { return _data; }
        uint32_t size() const { return _size; }

        friend std::ostream& operator<<(std::ostream& os, const BSString& string);
        static NativeLibrary library();
    };

} // namespace BraneScript

#endif // BRANESCRIPT_BSSTRING_H

//
// Created by wirewhiz on 6/10/23.
//

#ifndef BRANESCRIPT_BSVECTOR_H
#define BRANESCRIPT_BSVECTOR_H

#include <cstdint>
#include <cassert>

namespace BraneScript
{
    template<typename T>
    class BSVector
    {
        T* _data = nullptr;
        uint32_t _size = 0;
        uint32_t _allocSize = 0;

        void destructCurrent()
        {
            for(uint32_t i = 0; i < _size; i++)
                _data[i].~T();
        }

        void grow(uint32_t minSize)
        {
            if(minSize <= _allocSize)
                return;

            uint32_t newSize = minSize * 1.5;
            T* newData = ::operator new(newSize * sizeof(T));
            for(uint32_t i = 0; i < _size; i++)
                new(newData + i) T(std::move(_data[i]));
            destructCurrent();
            ::operator delete(_data);
            _data = newData;
            _allocSize = newSize;
        }

      public:
        BSVector(const BSVector<T>& o)
        {
            _size = o._size;
            destructCurrent();
            if(_allocSize < o._allocSize)
            {
                ::operator delete(_data);
                _data = ::operator new(o._allocSize * sizeof(T));
                _allocSize = o._allocSize;
            }
            for(uint32_t i = 0; i < _size; i++)
                new(_data + i) T(_data[i]);
            return *this;
        }
        BSVector(BSVector<T>&& o)
        {
            _data = o._data;
            _size = o._size;
            _allocSize = o._allocSize;
            o._data = nullptr;
            o._size = 0;
            o._allocSize = 0;
        }
        ~BSVector()
        {
            destructCurrent();
        }

        BSVector<T>& operator=(const BSVector<T>& o)
        {
            _size = o._size;
            destructCurrent();
            if(_allocSize < o._allocSize)
            {
                ::operator delete(_data);
                _data = ::operator new(o._allocSize * sizeof(T));
                _allocSize = o._allocSize;
            }
            for(uint32_t i = 0; i < _size; i++)
                new (_data + i) T(o._data[i]);
            return *this;
        }
        BSVector<T>& operator=(BSVector<T>&& o)
        {
            destructCurrent();
            ::operator delete(_data);
            _data = o._data;
            _size = o._size;
            _allocSize = o._allocSize;
            o._data = nullptr;
            o._size = 0;
            o._allocSize = 0;
            return *this;
        }

        T& operator[](uint32_t index)
        {
            assert(index < _size);
            return _data[index];
        }
        const T& operator[](uint32_t index) const
        {
            assert(index < _size);
            return _data[index];
        }

        void push_back(const T& value)
        {
            grow(_size + 1);
            new(_data + _size) T(value);
            _size++;
        }

        void push_back(T&& value)
        {
            grow(_size + 1);
            new(_data + _size) T(std::move(value));
            _size++;
        }

        void resize(uint32_t size)
        {
            if (size > _allocSize)
                grow(size);
            for(uint32_t i = _size; i < size; i++)
                new(_data + i) T();
            _size = size;
        }
        void reserve(uint32_t size)
        {
            if (size > _allocSize)
                grow(size);
        }

        uint32_t size() const
        {
            return _size;
        }
        uint32_t capacity() const
        {
            return _allocSize;
        }

        T* data()
        {
            return _data;
        }
        const T* data() const
        {
            return _data;
        }

        void clear()
        {
            destructCurrent();
            _size = 0;
        }
    };
}


#endif // BRANESCRIPT_BSVECTOR_H

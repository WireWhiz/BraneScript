//
// Created by wirewhiz on 5/16/23.
//

#ifndef BRANESCRIPT_BSLAMBDA_H
#define BRANESCRIPT_BSLAMBDA_H

#include "funcRef.h"

namespace BraneScript
{
    template<typename Ret, typename... Args>
    class BSLambda
    {
        void* _data = nullptr;
        FuncRef<Ret, void*, Args...> _f = nullptr;
        FuncRef<void, void*> _destructor = nullptr;
        FuncRef<void, void*, const void*> _copyData = nullptr;
        uint32_t _dataSize = 0;
      public:
        BSLambda() = default;

        template<typename... CapturedVars>
        BSLambda(FuncRef<Ret, void*, Args...> f,  CapturedVars&&... capturedVars) : _f(f)
        {
            _data = new std::tuple<CapturedVars...>(std::forward<CapturedVars>(capturedVars)...);
            _dataSize = sizeof(std::tuple<CapturedVars...>);
            _destructor = [](void* data){
                ((std::tuple<CapturedVars...>*)data)->~tuple();
            };
            _copyData = [](void* data, const void* other) {
                new(data) std::tuple<CapturedVars...>(*(std::tuple<CapturedVars...>*)other);
            };
        }
        BSLambda(const BSLambda& o)
        {
            if(_data == o._data)
                return;
            if(_dataSize)
            {
                _destructor(_data);
                ::operator delete(_data);
            }
            if(o._dataSize)
            {
                _copyData = o._copyData;
                _data = ::operator new(o._dataSize);
                _copyData(_data, o._data);
                _dataSize = o._dataSize;
                _destructor = o._destructor;
            }
            else
            {
                _data = nullptr;
                _dataSize = 0;
                _destructor = nullptr;
                _copyData = nullptr;
            }
            _f = o._f;
        }

        BSLambda(BSLambda&& o)
        {
            if(_dataSize)
            {
                _destructor(_data);
                ::operator delete(_data);
            }
            _data = o._data;
            _dataSize = o._dataSize;
            _destructor = o._destructor;
            _copyData = o._copyData;
            _f = o._f;
            o._data = nullptr;
            o._destructor = nullptr;
            o._copyData = nullptr;
            o._f = nullptr;
        }

        BSLambda& operator=(const BSLambda& o)
        {
            if(_data == o._data)
                return *this;
            if(_dataSize)
            {
                _destructor(_data);
                ::operator delete(_data);
            }
            if(o._dataSize)
            {
                _copyData = o._copyData;
                _data = ::operator new(o._dataSize);
                _copyData(_data, o._data);
                _dataSize = o._dataSize;
                _destructor = o._destructor;
            }
            else
            {
                _data = nullptr;
                _dataSize = 0;
                _destructor = nullptr;
                _copyData = nullptr;
            }
            _f = o._f;
            return *this;
        }
        ~BSLambda()
        {
            if(_dataSize)
            {
                _destructor(_data);
                ::operator delete(_data);
            }
        }

        operator bool() const{ return _f;}

        Ret operator()(Args... args) const
        {
            assert(_f);
            return _f(_data, args...);
        }
        void* data() const
        {
            if(!_dataSize)
                return nullptr;
            return _data;
        }
        uint32_t captureSize() const
        {
            return _dataSize;
        }
    };

    struct NativeLibrary;
    //Empty library so link target is fulfilled
    NativeLibrary getLambdaLibrary();

} // namespace BraneScript

#endif // BRANESCRIPT_BSLAMBDA_H

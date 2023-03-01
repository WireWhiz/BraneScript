//
// Created by wirewhiz on 2/24/23.
//

#include "nativeLibrary.h"

namespace BraneScript
{
    Library* _nativeLib = nullptr;

    Library* getNativeLibrary()
    {
        if(_nativeLib)
            return _nativeLib;
        _nativeLib = new Library("BraneScript");

        _nativeLib->addFunction("BraneScript::string::_construct(ref BraneScript::string)", "void", 1, (void*)(FunctionHandle<void, void*>)[](void* data){
            new (data)std::string;
        });
        _nativeLib->addFunction("BraneScript::string::_copy(ref BraneScript::string,const ref BraneScript::string)", "void", 2, (void*)(FunctionHandle<void, std::string*, std::string*>)[](std::string* thisRef, std::string* other){
            *thisRef = *other;
        });
        _nativeLib->addFunction("BraneScript::string::_move(ref BraneScript::string,ref BraneScript::string)", "void", 2, (void*)(FunctionHandle<void, std::string*, std::string*>)[](std::string* thisRef, std::string* other){
            *thisRef = std::move(*other);
        });
        _nativeLib->addFunction("BraneScript::string::_destruct(ref BraneScript::string)", "void", 1, (void*)(FunctionHandle<void, std::string*>)[](std::string* data){
            delete data;
        });
        _nativeLib->addFunction("BraneScript::opr ==(const ref BraneScript::string,const ref BraneScript::string)", "BraneScript::string", 2, (void*)(FunctionHandle<bool, const std::string*, const std::string*>)[](const std::string* a, const std::string* b){
            return *a == *b;
        });
        _nativeLib->addFunction("BraneScript::opr !=(const ref BraneScript::string,const ref BraneScript::string)", "BraneScript::string", 2, (void*)(FunctionHandle<bool, const std::string*, const std::string*>)[](const std::string* a, const std::string* b){
            return *a != *b;
        });
        _nativeLib->addFunction("BraneScript::opr +(const ref BraneScript::string,const ref BraneScript::string)", "BraneScript::string", 2, (void*)(FunctionHandle<std::string*, const std::string*, const std::string*>)[](const std::string* a, const std::string* b){
            return new std::string(*a + *b);
        });
        _nativeLib->addFunction("BraneScript::opr [](const ref BraneScript::string,int)", "char", 2, (void*)(FunctionHandle<char, const std::string*, uint32_t>)[](const std::string* str, uint32_t index){
            return (*str)[index];
        });

        return _nativeLib;
    }
}
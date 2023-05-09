//
// Created by wirewhiz on 2/24/23.
//

#include "nativeLibrary.h"

namespace BraneScript
{
    void addNativeFunctions(Linker& linker)
    {
        /*linker.addFunction("BraneScript::string::_construct(ref BraneScript::string)", "void", 1, (void*)(FunctionHandle<void, void*>)[](void* data){
            new (data)std::string;
        });
        linker.addFunction("BraneScript::string::_copy(ref BraneScript::string,const ref BraneScript::string)", "void", 2, (void*)(FunctionHandle<void, std::string*, std::string*>)[](std::string* thisRef, std::string* other){
            *thisRef = *other;
        });
        linker.addFunction("BraneScript::string::_move(ref BraneScript::string,ref BraneScript::string)", "void", 2, (void*)(FunctionHandle<void, std::string*, std::string*>)[](std::string* thisRef, std::string* other){
            *thisRef = std::move(*other);
        });
        linker.addFunction("BraneScript::string::_destruct(ref BraneScript::string)", "void", 1, (void*)(FunctionHandle<void, std::string*>)[](std::string* data){
            data->~basic_string();
        });
        linker.addFunction("BraneScript::opr ==(const ref BraneScript::string,const ref BraneScript::string)", "bool", 2, (void*)(FunctionHandle<bool, const std::string*, const std::string*>)[](const std::string* a, const std::string* b){
            return *a == *b;
        });
        linker.addFunction("BraneScript::opr !=(const ref BraneScript::string,const ref BraneScript::string)", "bool", 2, (void*)(FunctionHandle<bool, const std::string*, const std::string*>)[](const std::string* a, const std::string* b){
            return *a != *b;
        });
        linker.addFunction("BraneScript::opr +(ref BraneScript::string,const ref BraneScript::string,const ref BraneScript::string)", "void", 3, (void*)(FunctionHandle<void, std::string*, const std::string*, const std::string*>)[](std::string* retRef, const std::string* a, const std::string* b){
            *retRef = *a + *b;
        });
        linker.addFunction("BraneScript::opr [](const ref BraneScript::string,int)", "char", 2, (void*)(FunctionHandle<char, const std::string*, uint32_t>)[](const std::string* str, uint32_t index){
            return (*str)[index];
        });*/
    }

    void NativeLibrary::addFunction(std::string signature, void* f) {
        functions.emplace_back(std::move(signature), f);
    }
}
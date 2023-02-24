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

        //TODO add string functions here

        return _nativeLib;
    }
}
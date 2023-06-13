//
// Created by wirewhiz on 5/16/23.
//

#include "bsLambda.h"
#include "nativeLibrary.h"

namespace BraneScript
{
    NativeLibrary getLambdaLibrary()
    {
        return NativeLibrary{"lambda"};
    }
} // namespace BraneScript
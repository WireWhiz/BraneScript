//
// Created by wirewhiz on 5/16/23.
//

#include "BSLambda.h"
#include "nativeLibrary.h"

namespace BraneScript
{
    NativeLibrary lambdaLibrary("lambda");
    NativeLibrary& getLambdaLibrary()
    {
        return lambdaLibrary;
    }
} // namespace BraneScript
find_package(robin_hood)

add_library(BraneScriptRuntime STATIC
        typeDef.cpp
        scriptRuntime.cpp
        irScript.cpp
        valueType.cpp
        funcRef.cpp
        structDef.cpp
        script.cpp
        nativeLibrary.cpp
        nativeTypes/bsString.cpp
        nativeTypes/bsLambda.cpp
        nativeTypes/bsVector.cpp)

target_link_libraries(BraneScriptRuntime PUBLIC -lLLVM-16)
target_include_directories(BraneScriptRuntime PUBLIC ${robin_hood_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/.. /usr/lib/llvm-16/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
find_package(asmjit)
find_package(robin_hood)

add_library(BraneScriptRuntime STATIC
        typeDef.cpp
        scriptRuntime.cpp
        irScript.cpp
        nativeTypes.cpp
        valueIndex.cpp
        functionHandle.cpp
        linker.cpp
        structDefinition.cpp
        script.cpp
        nativeLibrary.cpp)
target_link_libraries(BraneScriptRuntime PUBLIC antlr4 asmjit::asmjit)
target_compile_definitions(BraneScriptRuntime PUBLIC ${asmjit_COMPILE_DEFINITIONS})
target_include_directories(BraneScriptRuntime PUBLIC ${asmjit_INCLUDE_DIRS} ${robin_hood_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
add_library(scripting STATIC
        compiler.cpp
        typeDef.cpp
        scriptRuntime.cpp
        irScript.cpp
        nativeTypes.cpp
        scriptFunction.cpp)
target_link_libraries(scripting PUBLIC antlr4 asmjit)
target_compile_definitions(scripting PUBLIC ASMJIT_EMBED)
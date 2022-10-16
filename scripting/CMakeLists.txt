add_library(scripting STATIC
        compiler.cpp
        typeDef.cpp
        linker.cpp
        irScript.cpp
        nativeTypes.cpp
        scriptFunction.cpp)
target_link_libraries(scripting PUBLIC antlr4)
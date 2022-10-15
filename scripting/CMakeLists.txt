add_library(scripting STATIC
        operandNode.cpp
        compiler.cpp
        typeDef.cpp)
target_link_libraries(scripting PUBLIC antlr4)
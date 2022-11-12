add_library(scripting STATIC
        compiler.cpp
        typeDef.cpp
        scriptRuntime.cpp
        irScript.cpp
        nativeTypes.cpp
        scriptFunction.cpp
        valueIndex.cpp
        aotNode/aotNode.cpp
        aotNode/aotOperationNodes.cpp
        aotNode/aotValueNodes.cpp
        aotNode/aotFlowNodes.cpp
        library.cpp
        operands.h functionHandle.cpp functionHandle.h linker.cpp linker.h)
target_link_libraries(scripting PUBLIC antlr4 asmjit)
target_compile_definitions(scripting PUBLIC ASMJIT_EMBED)
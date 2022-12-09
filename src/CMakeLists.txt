add_library(BraneScript STATIC
        compiler.cpp
        typeDef.cpp
        scriptRuntime.cpp
        irScript.cpp
        nativeTypes.cpp
        irFunction.cpp
        valueIndex.cpp
        aotNode/aotNode.cpp
        aotNode/aotOperationNodes.cpp
        aotNode/aotValueNodes.cpp
        aotNode/aotFlowNodes.cpp
        library.cpp
        operands.h functionHandle.cpp functionHandle.h linker.cpp linker.h structDefinition.cpp structDefinition.h typeInfo.h)
target_link_libraries(BraneScript PUBLIC antlr4 asmjit)
target_compile_definitions(BraneScript PUBLIC ASMJIT_EMBED)
target_include_directories(BraneScript PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
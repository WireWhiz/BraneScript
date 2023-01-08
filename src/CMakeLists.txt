find_package(asmjit)

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
        functionHandle.cpp
        linker.cpp
        structDefinition.cpp operator.cpp operator.h)
target_link_libraries(BraneScript PUBLIC antlr4 asmjit::asmjit)
target_compile_definitions(BraneScript PUBLIC ${asmjit_COMPILE_DEFINITIONS})
target_include_directories(BraneScript PUBLIC ${asmjit_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ../robin_hood)
add_library(BraneScriptCompiler STATIC
        compiler.cpp
        operator.cpp)
target_link_libraries(BraneScriptCompiler PUBLIC BraneScriptRuntime)
target_include_directories(BraneScriptCompiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})
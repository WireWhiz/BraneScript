cmake_minimum_required(VERSION 3.23)
project(BraneScript)

set(CMAKE_CXX_STANDARD 17)
option(BE_BUILD_EXECUTABLE "Build standalone compiler/interpreter" ON)

if(BE_BUILD_EXECUTABLE)
    add_executable(BraneScriptCompiler main.cpp)
    target_link_libraries(BraneScriptCompiler antlr4 ast)
endif()

add_subdirectory(antlr4)
add_subdirectory(ast)
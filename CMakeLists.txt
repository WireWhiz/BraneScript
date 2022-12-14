cmake_minimum_required(VERSION 3.22)
project(BraneScript)

set(CMAKE_CXX_STANDARD 17)
option(BS_BUILD_EXECUTABLE "Build standalone compiler/interpreter" ON)
option(BS_BUILD_TESTS "Build tests" ON)

execute_process(COMMAND conan install ..
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

if(BS_BUILD_EXECUTABLE)
    add_executable(BraneScriptCompiler main.cpp)
    target_link_libraries(BraneScriptCompiler antlr4 BraneScript)
endif()

add_subdirectory(antlr4)
add_subdirectory(src)

if(BS_BUILD_TESTS)
    add_subdirectory(tests)
endif()
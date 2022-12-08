cmake_minimum_required(VERSION 3.22)
project(BraneScript)

set(CMAKE_CXX_STANDARD 20)
option(BS_BUILD_EXECUTABLE "Build standalone compiler/interpreter" ON)
option(BS_BUILD_TESTS "Build tests" ON)
option(BS_FETCH_GTEST "Turn off if your project already includes gtest" ON)

if(BS_BUILD_EXECUTABLE)
    add_executable(BraneScriptCompiler main.cpp)
    target_link_libraries(BraneScriptCompiler antlr4 scripting)
endif()

add_subdirectory(antlr4)
add_subdirectory(scripting)

set(ASMJIT_STATIC TRUE)
set(ASMJIT_TEST)
add_subdirectory(asmjit)

if(BS_BUILD_TESTS)
    add_subdirectory(tests)
endif()
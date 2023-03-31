cmake_minimum_required(VERSION 3.23)
project(BraneScript)

set(CMAKE_CXX_STANDARD 17)
option(BS_BUILD_EXECUTABLE "Build standalone compiler/interpreter" ON)
option(BS_BUILD_TESTS "Build tests" ON)

execute_process(COMMAND conan install ${CMAKE_CURRENT_SOURCE_DIR} -s  build_type=${CMAKE_BUILD_TYPE} --output-folder=${CMAKE_CURRENT_BINARY_DIR}/conan --build=missing
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
include(${CMAKE_CURRENT_BINARY_DIR}/conan/conan_toolchain.cmake)

if(BS_BUILD_EXECUTABLE)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/executables)
    add_executable(BraneScriptApplication main.cpp)
    target_link_libraries(BraneScriptApplication antlr4 BraneScriptCompiler)
endif()

add_subdirectory(antlr4)
add_subdirectory(src)

if(BS_BUILD_TESTS)
    add_subdirectory(tests)
endif()
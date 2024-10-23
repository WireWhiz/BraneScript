cmake_minimum_required(VERSION 3.23)
project(BraneScript
        VERSION "0.2.0"
        DESCRIPTION "BraneScript"
        HOMEPAGE_URL "https://github.com/wirewhiz/branescript"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
#option(BS_BUILD_EXECUTABLE "Build standalone compiler/interpreter" ON)
option(BS_BUILD_TESTS "Build tests" ON)

#[[execute_process(COMMAND conan install ${CMAKE_CURRENT_SOURCE_DIR} --build=missing
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})]]
#include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/executables)

add_subdirectory(src)
execute_process(
        COMMAND ${CMAKE_COMMAND} -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON -S ${CMAKE_SOURCE_DIR}/tree-sitter-BraneScript -B ${CMAKE_BINARY_DIR}/tree-sitter-bs-build -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/tree-sitter-bs
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/tree-sitter-bs-build --config Release --target install
        COMMAND ${CMAKE_COMMAND} -E touch tree_sitter_bs
)
add_custom_target(tree_sitter_bs_project ALL DEPENDS tree_sitter_bs)

add_library(TreeSitterBraneScript INTERFACE)
add_dependencies(TreeSitterBraneScript tree_sitter_bs_project)

target_link_libraries(TreeSitterBraneScript INTERFACE ${CMAKE_BINARY_DIR}/tree-sitter-bs/lib/tree-sitter-branescript_parser${CMAKE_STATIC_LIBRARY_SUFFIX})
target_include_directories(TreeSitterBraneScript INTERFACE ${CMAKE_BINARY_DIR}/tree-sitter-bs/include)

if(BS_BUILD_TESTS)
    add_subdirectory(tests)
endif()
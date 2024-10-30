cmake_minimum_required(VERSION 3.23)
project(BraneScript
        VERSION "0.2.0"
        DESCRIPTION "BraneScript"
        HOMEPAGE_URL "https://github.com/wirewhiz/branescript"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(BS_BUILD_TESTS "Build tests" ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/executables/$<0:>)

set(GRAMMAR_DIR ${CMAKE_SOURCE_DIR}/TreeSitterBraneScript)
set(GRAMMAR_FILE ${CMAKE_SOURCE_DIR}/TreeSitterBraneScript/grammar.js)
set(GRAMMAR_BUILD_DIR ${CMAKE_BINARY_DIR}/ts-branescript)
set(GENERATE_PARSER_CMD tree-sitter generate -b ${GRAMMAR_FILE})
set(PARSER_LIB_NAME parser${CMAKE_SHARED_LIBRARY_SUFFIX})
set(BUILD_PARSER_CMD tree-sitter build -o ${GRAMMAR_BUILD_DIR}/${PARSER_LIB_NAME})

file(MAKE_DIRECTORY ${GRAMMAR_BUILD_DIR})

message("Watching grammar at ${GRAMMAR_FILE}")
add_custom_command(
    OUTPUT ${GRAMMAR_BUILD_DIR}/ts-build-command.stamp
    COMMAND echo ${GENERATE_PARSER_CMD} 
    COMMAND ${GENERATE_PARSER_CMD} 
    COMMAND echo ${BUILD_PARSER_CMD}
    COMMAND ${BUILD_PARSER_CMD}
    COMMAND 
        ${CMAKE_COMMAND} -E rm
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PARSER_LIB_NAME}
    COMMAND 
        ${CMAKE_COMMAND} -E copy
        ${GRAMMAR_BUILD_DIR}/${PARSER_LIB_NAME}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PARSER_LIB_NAME}

    WORKING_DIRECTORY ${GRAMMAR_BUILD_DIR}
    DEPENDS ${GRAMMAR_FILE}
    COMMENT "Generate ts parser because grammar.js changed"
)
add_custom_target(
    tree_sitter_bs_parser 
    DEPENDS 
    ${GRAMMAR_BUILD_DIR}/ts-build-command.stamp
)

add_library(TreeSitterBraneScript INTERFACE)
add_dependencies(TreeSitterBraneScript tree_sitter_bs_parser)

target_link_libraries(TreeSitterBraneScript INTERFACE ${GRAMMAR_BUILD_DIR}/parser${CMAKE_STATIC_LIBRARY_SUFFIX}) 
target_include_directories(TreeSitterBraneScript INTERFACE ${GRAMMAR_DIR}/bindings/c)

add_subdirectory(src)

if(BS_BUILD_TESTS)
    add_subdirectory(tests)
endif()

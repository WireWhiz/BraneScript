find_package(GTest)

enable_testing()

add_executable(bs_tests emptyPlaceholder.cpp)
#target_link_libraries(bs_tests PUBLIC GTest::gtest_main BraneScriptCompiler)
target_compile_definitions(bs_tests PUBLIC TESTS)

include(GoogleTest)
gtest_discover_tests(bs_tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/executables)

file(GLOB TEST_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/*.bs)
file(COPY ${TEST_SCRIPTS} DESTINATION ${CMAKE_BINARY_DIR}/executables/testScripts)
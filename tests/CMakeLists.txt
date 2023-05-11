find_package(GTest)

enable_testing()

add_executable(bs_tests
        operatorTests.cpp
        testing.cpp
        flowStatementTests.cpp
        overrideTests.cpp
        recursionTest.cpp
        apiTests.cpp
        objectTests.cpp
        speedTests.cpp
        #stringTests.cpp
        templateTests.cpp
        globalVariableTests.cpp
        #lambdaTests.cpp
        refTests.cpp
        unsafeTests.cpp
        )
target_link_libraries(bs_tests PUBLIC GTest::gtest_main BraneScriptCompiler)
target_compile_definitions(bs_tests PUBLIC TESTS)

include(GoogleTest)
gtest_discover_tests(bs_tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/executables)
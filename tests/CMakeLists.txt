find_package(GTest)

enable_testing()

add_executable(bs_tests
        operatorTests.cpp
        testing.cpp
        flowStatementTests.cpp
        overrideTests.cpp
        recursionTest.cpp
        libraryTests.cpp
        objectTests.cpp
        speedTests.cpp
        funcDefTests.cpp
        stringTests.cpp
        globalVariables.cpp)
target_link_libraries(bs_tests PUBLIC GTest::gtest_main BraneScript)
target_compile_definitions(bs_tests PUBLIC TESTS)

include(GoogleTest)
gtest_discover_tests(bs_tests)
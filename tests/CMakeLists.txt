
if(BS_FETCH_GTEST)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

enable_testing()

add_executable(bs_tests operatorTests.cpp testing.cpp testing.h flowStatementTests.cpp)
target_link_libraries(bs_tests PUBLIC gtest_main scripting)

include(GoogleTest)
gtest_discover_tests(bs_tests)
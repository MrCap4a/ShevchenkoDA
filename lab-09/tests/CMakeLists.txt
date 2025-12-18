# Add tests
add_executable(run_tests
    test_dynamic_programming.cpp
)

target_link_libraries(run_tests 
    dp_lib 
    gtest_main 
    gtest
)

include(GoogleTest)
gtest_discover_tests(run_tests)

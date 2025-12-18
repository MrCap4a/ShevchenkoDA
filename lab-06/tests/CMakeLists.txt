# Add tests
add_executable(run_tests
    test_binary_search_tree.cpp
)

target_link_libraries(run_tests 
    trees_lib 
    gtest_main 
    gtest
)

include(GoogleTest)
gtest_discover_tests(run_tests)
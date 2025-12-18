# Add tests
add_executable(run_tests
    test_heap.cpp
)

target_link_libraries(run_tests 
    heaps_lib 
    gtest_main 
    gtest
)

include(GoogleTest)
gtest_discover_tests(run_tests)


# Тесты для жадных алгоритмов
add_executable(run_tests
    test_greedy_algorithms.cpp
)

target_link_libraries(run_tests
    greedy_lib
    gtest_main
    gtest
)

include(GoogleTest)
gtest_discover_tests(run_tests)

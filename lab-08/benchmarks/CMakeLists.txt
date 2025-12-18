# Бенчмарки для жадных алгоритмов
add_executable(run_benchmarks
    benchmark_greedy.cpp
)

target_link_libraries(run_benchmarks
    greedy_lib
    benchmark
    benchmark_main
)

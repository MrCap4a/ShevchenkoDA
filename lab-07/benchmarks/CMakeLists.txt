# Add benchmarks
add_executable(run_benchmarks
    benchmark_heap.cpp
)

target_link_libraries(run_benchmarks 
    heaps_lib 
    benchmark
    benchmark_main
)


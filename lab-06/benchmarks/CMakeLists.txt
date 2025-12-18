# Add benchmarks
add_executable(run_benchmarks
    benchmark_bst.cpp
)

target_link_libraries(run_benchmarks 
    trees_lib 
    benchmark
    benchmark_main
)
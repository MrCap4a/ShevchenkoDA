# Add benchmarks
add_executable(run_benchmarks
    benchmark_dp.cpp
)

target_link_libraries(run_benchmarks 
    dp_lib 
    benchmark
    benchmark_main
)

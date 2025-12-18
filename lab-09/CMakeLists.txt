cmake_minimum_required(VERSION 3.16)
project(lab09_dynamic_programming VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Build tests" ON)
option(BUILD_BENCHMARKS "Build benchmarks" ON)

include(FetchContent)

# Find or fetch Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Find or fetch Google Benchmark
FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
)

FetchContent_MakeAvailable(googletest benchmark)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/fibonacci.cpp
    src/knapsack.cpp
    src/lcs.cpp
    src/levenshtein.cpp
    src/coin_change.cpp
    src/lis.cpp
)

# Header files
set(HEADERS
    include/fibonacci.h
    include/knapsack.h
    include/lcs.h
    include/levenshtein.h
    include/coin_change.h
    include/lis.h
)

# Create library
add_library(dp_lib ${SOURCES} ${HEADERS})
target_include_directories(dp_lib PUBLIC include)

# Tests
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

# Benchmarks
if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

# Examples
add_executable(dp_example examples/example.cpp)
target_link_libraries(dp_example dp_lib)

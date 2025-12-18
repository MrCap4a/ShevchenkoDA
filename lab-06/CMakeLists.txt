cmake_minimum_required(VERSION 3.16)
project(lab06_trees VERSION 1.0.0 LANGUAGES CXX)

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
    src/binary_search_tree.cpp
    src/tree_traversal.cpp
)

# Header files
set(HEADERS
    include/binary_search_tree.h
    include/tree_traversal.h
)

# Create library
add_library(trees_lib ${SOURCES} ${HEADERS})
target_include_directories(trees_lib PUBLIC include)

# Tests
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

# Benchmarks
if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

# Examples
add_executable(tree_example examples/example.cpp)
target_link_libraries(tree_example trees_lib)
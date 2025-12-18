cmake_minimum_required(VERSION 3.16)
project(lab08_greedy VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Build tests" ON)
option(BUILD_BENCHMARKS "Build benchmarks" ON)

include(FetchContent)

# Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Google Benchmark
FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
)

FetchContent_MakeAvailable(googletest benchmark)

include_directories(include)

set(SOURCES
    src/greedy_algorithms.cpp
)

set(HEADERS
    include/greedy_algorithms.h
)

add_library(greedy_lib ${SOURCES} ${HEADERS})
target_include_directories(greedy_lib PUBLIC include)

# Пример с демонстрацией жадных алгоритмов
add_executable(run_example examples/example.cpp)
target_link_libraries(run_example greedy_lib)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

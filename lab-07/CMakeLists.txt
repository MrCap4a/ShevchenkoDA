cmake_minimum_required(VERSION 3.16)
project(lab07_heaps VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Build tests" ON)
option(BUILD_BENCHMARKS "Build benchmarks" ON)

include(FetchContent)

set(SOURCES
  src/main.cpp
)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
)

FetchContent_MakeAvailable(googletest benchmark)

include_directories(include)

set(HEADERS
    include/heap.h
    include/heapsort.h
    include/priority_queue.h
)

add_library(heaps_lib ${SOURCES} ${HEADERS})
target_include_directories(heaps_lib PUBLIC include)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

add_executable(heap_example examples/example.cpp)
target_link_libraries(heap_example heaps_lib)


#include "../include/heap.h"
#include "../include/heapsort.h"
#include <benchmark/benchmark.h>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>

// Бенчмарк вставки элементов (последовательная вставка)
static void BM_InsertSequential(benchmark::State& state) {
    const int n = state.range(0);
    
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dist(1, 1000000);
    
    for (auto _ : state) {
        Heap<int> heap(true);
        for (int i = 0; i < n; ++i) {
            heap.insert(dist(gen));
        }
        benchmark::DoNotOptimize(heap);
    }
    state.SetComplexityN(n);
}

// Бенчмарк построения кучи из массива (buildHeap)
static void BM_BuildHeap(benchmark::State& state) {
    const int n = state.range(0);
    
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dist(1, 1000000);
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = dist(gen);
    }
    
    for (auto _ : state) {
        Heap<int> heap(true);
        heap.buildHeap(arr);
        benchmark::DoNotOptimize(heap);
    }
    state.SetComplexityN(n);
}

// Бенчмарк извлечения элементов
static void BM_Extract(benchmark::State& state) {
    const int n = state.range(0);
    
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dist(1, 1000000);
    
    Heap<int> heap(true);
    for (int i = 0; i < n; ++i) {
        heap.insert(dist(gen));
    }
    
    for (auto _ : state) {
        Heap<int> tempHeap = heap;
        while (!tempHeap.isEmpty()) {
            benchmark::DoNotOptimize(tempHeap.extract());
        }
    }
    state.SetComplexityN(n);
}

// Бенчмарк Heapsort
static void BM_Heapsort(benchmark::State& state) {
    const int n = state.range(0);
    
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dist(1, 1000000);
    
    for (auto _ : state) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = dist(gen);
        }
        
        heapsort(arr);
        benchmark::DoNotOptimize(arr);
    }
    state.SetComplexityN(n);
}

// Бенчмарк Heapsort на отсортированном массиве
static void BM_HeapsortSorted(benchmark::State& state) {
    const int n = state.range(0);
    
    for (auto _ : state) {
        std::vector<int> arr(n);
        std::iota(arr.begin(), arr.end(), 1);
        
        heapsort(arr);
        benchmark::DoNotOptimize(arr);
    }
    state.SetComplexityN(n);
}

// Бенчмарк Heapsort на обратно отсортированном массиве
static void BM_HeapsortReverseSorted(benchmark::State& state) {
    const int n = state.range(0);
    
    for (auto _ : state) {
        std::vector<int> arr(n);
        std::iota(arr.begin(), arr.end(), 1);
        std::reverse(arr.begin(), arr.end());
        
        heapsort(arr);
        benchmark::DoNotOptimize(arr);
    }
    state.SetComplexityN(n);
}

// Сравнение последовательной вставки и buildHeap
static void BM_InsertVsBuildHeap(benchmark::State& state) {
    const int n = state.range(0);
    
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dist(1, 1000000);
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = dist(gen);
    }
    
    for (auto _ : state) {
        Heap<int> heap(true);
        heap.buildHeap(arr);
        benchmark::DoNotOptimize(heap);
    }
    state.SetComplexityN(n);
}

// Регистрация бенчмарков
BENCHMARK(BM_InsertSequential)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oNLogN);

BENCHMARK(BM_BuildHeap)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oN);

BENCHMARK(BM_Extract)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oNLogN);

BENCHMARK(BM_Heapsort)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oNLogN);

BENCHMARK(BM_HeapsortSorted)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oNLogN);

BENCHMARK(BM_HeapsortReverseSorted)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oNLogN);

BENCHMARK(BM_InsertVsBuildHeap)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oN);

BENCHMARK_MAIN();


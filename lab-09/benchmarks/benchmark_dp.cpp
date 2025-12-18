#include "../include/coin_change.h"
#include "../include/fibonacci.h"
#include "../include/knapsack.h"
#include "../include/lcs.h"
#include "../include/levenshtein.h"
#include "../include/lis.h"
#include <benchmark/benchmark.h>
#include <random>
#include <string>
#include <vector>

static void BM_FibonacciNaive(benchmark::State &state) {
  int n = state.range(0);
  for (auto _ : state) {
    benchmark::DoNotOptimize(dp::fibonacci_naive(n));
  }
  state.SetComplexityN(n);
}

static void BM_FibonacciMemoization(benchmark::State &state) {
  int n = state.range(0);
  for (auto _ : state) {
    benchmark::DoNotOptimize(dp::fibonacci_memoization(n));
  }
  state.SetComplexityN(n);
}

static void BM_FibonacciIterative(benchmark::State &state) {
  int n = state.range(0);
  for (auto _ : state) {
    benchmark::DoNotOptimize(dp::fibonacci_iterative(n));
  }
  state.SetComplexityN(n);
}

static void BM_Knapsack01(benchmark::State &state) {
  int n = state.range(0);
  int capacity = n * 10;

  std::mt19937 gen(42);
  std::uniform_int_distribution<int> weight_dist(1, 20);
  std::uniform_int_distribution<int> value_dist(1, 100);

  std::vector<dp::Item> items;
  for (int i = 0; i < n; ++i) {
    items.emplace_back(weight_dist(gen), value_dist(gen));
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(dp::knapsack_01(items, capacity));
  }
  state.SetComplexityN(n);
}

static void BM_Knapsack01Optimized(benchmark::State &state) {
  int n = state.range(0);
  int capacity = n * 10;

  std::mt19937 gen(42);
  std::uniform_int_distribution<int> weight_dist(1, 20);
  std::uniform_int_distribution<int> value_dist(1, 100);

  std::vector<dp::Item> items;
  for (int i = 0; i < n; ++i) {
    items.emplace_back(weight_dist(gen), value_dist(gen));
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(dp::knapsack_01_optimized(items, capacity));
  }
  state.SetComplexityN(n);
}

static void BM_LCSLength(benchmark::State &state) {
  int len = state.range(0);

  std::mt19937 gen(42);
  std::uniform_int_distribution<int> char_dist('a', 'z');

  std::string s1(len, 'a');
  std::string s2(len, 'a');
  for (int i = 0; i < len; ++i) {
    s1[i] = static_cast<char>(char_dist(gen));
    s2[i] = static_cast<char>(char_dist(gen));
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(dp::lcs_length(s1, s2));
  }
  state.SetComplexityN(len);
}

static void BM_LCSLengthOptimized(benchmark::State &state) {
  int len = state.range(0);

  std::mt19937 gen(42);
  std::uniform_int_distribution<int> char_dist('a', 'z');

  std::string s1(len, 'a');
  std::string s2(len, 'a');
  for (int i = 0; i < len; ++i) {
    s1[i] = static_cast<char>(char_dist(gen));
    s2[i] = static_cast<char>(char_dist(gen));
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(dp::lcs_length_optimized(s1, s2));
  }
  state.SetComplexityN(len);
}

static void BM_Levenshtein(benchmark::State &state) {
  int len = state.range(0);

  std::mt19937 gen(42);
  std::uniform_int_distribution<int> char_dist('a', 'z');

  std::string s1(len, 'a');
  std::string s2(len, 'a');
  for (int i = 0; i < len; ++i) {
    s1[i] = static_cast<char>(char_dist(gen));
    s2[i] = static_cast<char>(char_dist(gen));
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(dp::levenshtein_distance(s1, s2));
  }
  state.SetComplexityN(len);
}

static void BM_LevenshteinOptimized(benchmark::State &state) {
  int len = state.range(0);

  std::mt19937 gen(42);
  std::uniform_int_distribution<int> char_dist('a', 'z');

  std::string s1(len, 'a');
  std::string s2(len, 'a');
  for (int i = 0; i < len; ++i) {
    s1[i] = static_cast<char>(char_dist(gen));
    s2[i] = static_cast<char>(char_dist(gen));
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(dp::levenshtein_distance_optimized(s1, s2));
  }
  state.SetComplexityN(len);
}

static void BM_CoinChangeMin(benchmark::State &state) {
  int amount = state.range(0);
  std::vector<int> coins = {1, 3, 4, 5, 10, 25};

  for (auto _ : state) {
    benchmark::DoNotOptimize(dp::coin_change_min(coins, amount));
  }
  state.SetComplexityN(amount);
}

static void BM_LISLength(benchmark::State &state) {
  int n = state.range(0);

  std::mt19937 gen(42);
  std::uniform_int_distribution<int> dist(1, 1000);

  std::vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    nums[i] = dist(gen);
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(dp::lis_length(nums));
  }
  state.SetComplexityN(n);
}

static void BM_LISLengthOptimized(benchmark::State &state) {
  int n = state.range(0);

  std::mt19937 gen(42);
  std::uniform_int_distribution<int> dist(1, 1000);

  std::vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    nums[i] = dist(gen);
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(dp::lis_length_optimized(nums));
  }
  state.SetComplexityN(n);
}

BENCHMARK(BM_FibonacciNaive)->Range(10, 30)->Complexity(benchmark::oNSquared);
BENCHMARK(BM_FibonacciMemoization)->Range(10, 100)->Complexity(benchmark::oN);
BENCHMARK(BM_FibonacciIterative)->Range(10, 100)->Complexity(benchmark::oN);

BENCHMARK(BM_Knapsack01)->Range(10, 100)->Complexity(benchmark::oNSquared);
BENCHMARK(BM_Knapsack01Optimized)
    ->Range(10, 100)
    ->Complexity(benchmark::oNSquared);

BENCHMARK(BM_LCSLength)->Range(10, 200)->Complexity(benchmark::oNSquared);
BENCHMARK(BM_LCSLengthOptimized)
    ->Range(10, 200)
    ->Complexity(benchmark::oNSquared);

BENCHMARK(BM_Levenshtein)->Range(10, 200)->Complexity(benchmark::oNSquared);
BENCHMARK(BM_LevenshteinOptimized)
    ->Range(10, 200)
    ->Complexity(benchmark::oNSquared);

BENCHMARK(BM_CoinChangeMin)->Range(100, 1000)->Complexity(benchmark::oN);

BENCHMARK(BM_LISLength)->Range(100, 1000)->Complexity(benchmark::oNSquared);
BENCHMARK(BM_LISLengthOptimized)
    ->Range(100, 1000)
    ->Complexity(benchmark::oNLogN);

BENCHMARK_MAIN();

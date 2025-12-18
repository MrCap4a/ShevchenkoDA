#include "../include/binary_search_tree.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <random>
#include <vector>

static void BM_InsertBalanced(benchmark::State &state) {
  const int n = state.range(0);
  std::vector<int> elements(n);
  for (int i = 0; i < n; ++i) {
    elements[i] = i;
  }

  std::mt19937 g(42);
  std::shuffle(elements.begin(), elements.end(), g);

  for (auto _ : state) {
    BinarySearchTree<int> bst;
    for (int elem : elements) {
      bst.insert(elem);
    }
    benchmark::DoNotOptimize(bst);
  }
  state.SetComplexityN(n);
}

static void BM_InsertDegenerate(benchmark::State &state) {
  const int n = state.range(0);

  for (auto _ : state) {
    BinarySearchTree<int> bst;
    for (int i = 0; i < n; ++i) {
      bst.insert(i); // Insert in sorted order - worst case
    }
    benchmark::DoNotOptimize(bst);
  }
  state.SetComplexityN(n);
}

static void BM_SearchBalanced(benchmark::State &state) {
  const int n = state.range(0);
  const int num_searches = state.range(1);

  // Build a balanced tree
  std::vector<int> elements(n);
  for (int i = 0; i < n; ++i) {
    elements[i] = i;
  }
  std::mt19937 g(42);
  std::shuffle(elements.begin(), elements.end(), g);

  BinarySearchTree<int> bst;
  for (int elem : elements) {
    bst.insert(elem);
  }

  // Generate random search values
  std::vector<int> search_values(num_searches);
  std::mt19937 g2(43);
  std::uniform_int_distribution<> dist(0, n - 1);
  for (int i = 0; i < num_searches; ++i) {
    search_values[i] = dist(g2);
  }

  for (auto _ : state) {
    for (int value : search_values) {
      benchmark::DoNotOptimize(bst.search(value));
    }
  }
  state.SetComplexityN(n);
}

static void BM_SearchDegenerate(benchmark::State &state) {
  const int n = state.range(0);
  const int num_searches = state.range(1);

  // Build a degenerate tree
  BinarySearchTree<int> bst;
  for (int i = 0; i < n; ++i) {
    bst.insert(i); // Insert in sorted order
  }

  // Generate random search values
  std::vector<int> search_values(num_searches);
  std::mt19937 g(42);
  std::uniform_int_distribution<> dist(0, n - 1);
  for (int i = 0; i < num_searches; ++i) {
    search_values[i] = dist(g);
  }

  for (auto _ : state) {
    for (int value : search_values) {
      benchmark::DoNotOptimize(bst.search(value));
    }
  }
  state.SetComplexityN(n);
}

static void BM_HeightBalanced(benchmark::State &state) {
  const int n = state.range(0);

  // Build a balanced tree
  std::vector<int> elements(n);
  for (int i = 0; i < n; ++i) {
    elements[i] = i;
  }
  std::mt19937 g(42);
  std::shuffle(elements.begin(), elements.end(), g);

  for (auto _ : state) {
    BinarySearchTree<int> bst;
    for (int elem : elements) {
      bst.insert(elem);
    }
    benchmark::DoNotOptimize(bst.height());
  }
  state.SetComplexityN(n);
}

static void BM_HeightDegenerate(benchmark::State &state) {
  const int n = state.range(0);

  for (auto _ : state) {
    BinarySearchTree<int> bst;
    for (int i = 0; i < n; ++i) {
      bst.insert(i); // Insert in sorted order
    }
    benchmark::DoNotOptimize(bst.height());
  }
  state.SetComplexityN(n);
}

BENCHMARK(BM_InsertBalanced)
    ->Range(1 << 5, 1 << 12)
    ->Complexity(benchmark::oNLogN);
BENCHMARK(BM_InsertDegenerate)
    ->Range(1 << 5, 1 << 12)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(BM_SearchBalanced)
    ->Args({1000, 1000})
    ->Args({2000, 1000})
    ->Args({4000, 1000})
    ->Args({8000, 1000})
    ->Complexity(benchmark::oLogN);
BENCHMARK(BM_SearchDegenerate)
    ->Args({1000, 1000})
    ->Args({2000, 1000})
    ->Args({4000, 1000})
    ->Args({8000, 1000})
    ->Complexity(benchmark::oN);
BENCHMARK(BM_HeightBalanced)->Range(1 << 5, 1 << 12)->Complexity(benchmark::oN);
BENCHMARK(BM_HeightDegenerate)
    ->Range(1 << 5, 1 << 12)
    ->Complexity(benchmark::oN);

BENCHMARK_MAIN();

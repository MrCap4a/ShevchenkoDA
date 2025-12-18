#include <benchmark/benchmark.h>

#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "greedy_algorithms.h"

using namespace greedy;

// Генерация случайной строки заданной длины над алфавитом из 26 букв
static std::string generateRandomString(std::size_t n) {
  static std::mt19937 rng(42);
  std::uniform_int_distribution<int> dist(0, 25);

  std::string s;
  s.reserve(n);
  for (std::size_t i = 0; i < n; ++i) {
    s.push_back(static_cast<char>('a' + dist(rng)));
  }
  return s;
}

// Подсчет частот символов в строке
static std::unordered_map<char, int> computeFrequencies(const std::string &s) {
  std::unordered_map<char, int> freq;
  for (char c : s) {
    ++freq[c];
  }
  return freq;
}

// Бенчмарк для построения кодов Хаффмана при разной длине входа
static void BM_HuffmanBuild(benchmark::State &state) {
  std::size_t n = static_cast<std::size_t>(state.range(0));
  std::string data = generateRandomString(n);
  auto freq = computeFrequencies(data);

  for (auto _ : state) {
    auto codes = buildHuffmanCodes(freq);
    benchmark::DoNotOptimize(codes);
  }

  state.SetComplexityN(n);
}

// Простые бенчмарки для задач выбора заявок и рюкзака

static void BM_IntervalScheduling(benchmark::State &state) {
  int n = static_cast<int>(state.range(0));
  std::mt19937 rng(123);
  std::uniform_int_distribution<int> start_dist(0, 1000);
  std::uniform_int_distribution<int> len_dist(1, 100);

  std::vector<Interval> intervals;
  intervals.reserve(n);
  for (int i = 0; i < n; ++i) {
    int start = start_dist(rng);
    int len = len_dist(rng);
    intervals.push_back({start, start + len});
  }

  for (auto _ : state) {
    auto res = selectIntervalsGreedy(intervals);
    benchmark::DoNotOptimize(res);
  }

  state.SetComplexityN(n);
}

static void BM_FractionalKnapsack(benchmark::State &state) {
  int n = static_cast<int>(state.range(0));
  std::mt19937 rng(321);
  std::uniform_real_distribution<double> value_dist(1.0, 100.0);
  std::uniform_real_distribution<double> weight_dist(1.0, 50.0);

  std::vector<Item> items;
  items.reserve(n);
  double total_weight = 0.0;
  for (int i = 0; i < n; ++i) {
    double v = value_dist(rng);
    double w = weight_dist(rng);
    items.push_back({v, w});
    total_weight += w;
  }

  double capacity = total_weight / 2.0;

  for (auto _ : state) {
    auto res = fractionalKnapsackGreedy(items, capacity);
    benchmark::DoNotOptimize(res);
  }

  state.SetComplexityN(n);
}

BENCHMARK(BM_HuffmanBuild)
    ->RangeMultiplier(2)
    ->Range(1 << 8, 1 << 18)
    ->Complexity();

BENCHMARK(BM_IntervalScheduling)
    ->RangeMultiplier(2)
    ->Range(1 << 8, 1 << 18)
    ->Complexity();

BENCHMARK(BM_FractionalKnapsack)
    ->RangeMultiplier(2)
    ->Range(1 << 8, 1 << 18)
    ->Complexity();

BENCHMARK_MAIN();

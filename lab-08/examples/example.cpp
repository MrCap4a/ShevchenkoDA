#include <iostream>
#include <unordered_map>
#include <vector>

#include "greedy_algorithms.h"

using namespace greedy;

void demoIntervalScheduling() {
  std::cout << " Задача о выборе заявок \n";
  std::vector<Interval> intervals{{1, 4},  {3, 5},  {0, 6},  {5, 7},
                                  {3, 8},  {5, 9},  {6, 10}, {8, 11},
                                  {8, 12}, {2, 13}, {12, 14}};

  auto selected = selectIntervalsGreedy(intervals);

  std::cout << "Выбранные интервалы (start, end):\n";
  for (const auto &in : selected) {
    std::cout << "(" << in.start << ", " << in.end << ") ";
  }
  std::cout << "\n\n";
}

void demoCoinChange() {
  std::cout << " Задача о монетах \n";
  std::vector<int> coins{10, 5, 2, 1};
  int amount = 28;

  auto cnt = coinChangeGreedy(amount, coins);

  std::cout << "Сумма: " << amount << "\n";
  std::cout << "Номиналы: ";
  for (int c : coins)
    std::cout << c << " ";
  std::cout << "\nКоличество монет по номиналам: ";
  for (int x : cnt)
    std::cout << x << " ";
  std::cout << "\n\n";
}

void demoHuffman() {
  std::cout << " Алгоритм Хаффмана \n";
  std::unordered_map<char, int> freq{{'a', 5}, {'b', 7}, {'c', 10}, {'d', 15}};

  auto codes = buildHuffmanCodes(freq);

  std::cout << "Символы и их частоты:\n";
  for (const auto &p : freq) {
    std::cout << p.first << ": " << p.second << "\n";
  }

  std::cout << "\nПостроенные коды Хаффмана:\n";
  for (const auto &p : codes) {
    std::cout << p.first << " -> " << p.second << "\n";
  }
  std::cout << "\n";
}

void demoKnapsack() {
  std::cout << " Сравнение рюкзаков: жадный дробный vs точный 0-1 \n";

  std::vector<Item> items{{60, 10}, {100, 20}, {120, 30}};
  double capacity = 50.0;

  auto greedy_res = fractionalKnapsackGreedy(items, capacity);

  std::cout << "Предметы (ценность, вес):\n";
  for (const auto &it : items) {
    std::cout << "(" << it.value << ", " << it.weight << ") ";
  }
  std::cout << "\nВместимость: " << capacity << "\n";

  std::cout << "\nЖадный дробный рюкзак:\n";
  std::cout << "Максимальная стоимость: " << greedy_res.max_value << "\n";
  std::cout << "Доли предметов: ";
  for (double f : greedy_res.fractions) {
    std::cout << f << " ";
  }
  std::cout << "\n";
}

int main() {
  std::cout << "Демонстрация жадных алгоритмов (C++)\n\n";

  demoIntervalScheduling();
  demoCoinChange();
  demoHuffman();
  demoKnapsack();

  return 0;
}


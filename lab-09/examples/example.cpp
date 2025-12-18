#include "../include/coin_change.h"
#include "../include/fibonacci.h"
#include "../include/knapsack.h"
#include "../include/lcs.h"
#include "../include/levenshtein.h"
#include "../include/lis.h"
#include <iostream>
#include <vector>

void demo_fibonacci() {
  std::cout << "1. Числа Фибоначчи\n";
  std::cout << "   n = 10:\n";
  std::cout << "   Наивная рекурсия: " << dp::fibonacci_naive(10) << "\n";
  std::cout << "   С мемоизацией: " << dp::fibonacci_memoization(10) << "\n";
  std::cout << "   Итеративная: " << dp::fibonacci_iterative(10) << "\n";

  std::cout << "\n   n = 30:\n";
  std::cout << "   С мемоизацией: " << dp::fibonacci_memoization(30) << "\n";
  std::cout << "   Итеративная: " << dp::fibonacci_iterative(30) << "\n";
}

void demo_knapsack() {
  std::cout << "2. Задача о рюкзаке 0-1\n";
  std::vector<dp::Item> items = {{10, 60}, {20, 100}, {30, 120}};
  int capacity = 50;

  std::cout << "   Предметы: (вес, стоимость)\n";
  for (size_t i = 0; i < items.size(); ++i) {
    std::cout << "   " << i + 1 << ": (" << items[i].weight << ", "
              << items[i].value << ")\n";
  }
  std::cout << "   Вместимость: " << capacity << "\n";

  int max_value = dp::knapsack_01(items, capacity);
  std::cout << "   Максимальная стоимость: " << max_value << "\n";

  auto result = dp::knapsack_01_with_items(items, capacity);
  std::cout << "   Выбранные предметы: ";
  for (int idx : result.second) {
    std::cout << idx + 1 << " ";
  }
  std::cout << "\n";
}

void demo_lcs() {
  std::cout << "3. Наибольшая общая подпоследовательность (LCS)\n";
  std::string s1 = "ABCDGH";
  std::string s2 = "AEDFHR";

  std::cout << "   Строка 1: " << s1 << "\n";
  std::cout << "   Строка 2: " << s2 << "\n";

  int length = dp::lcs_length(s1, s2);
  std::cout << "   Длина LCS: " << length << "\n";

  std::string lcs = dp::lcs_string(s1, s2);
  std::cout << "   LCS: " << lcs << "\n";
}

void demo_levenshtein() {
  std::cout << "4. Расстояние Левенштейна\n";
  std::string s1 = "kitten";
  std::string s2 = "sitting";

  std::cout << "   Строка 1: " << s1 << "\n";
  std::cout << "   Строка 2: " << s2 << "\n";

  int distance = dp::levenshtein_distance(s1, s2);
  std::cout << "   Расстояние: " << distance << "\n";
}

void demo_coin_change() {
  std::cout << "5. Размен монет\n";
  std::vector<int> coins = {1, 3, 4};
  int amount = 6;

  std::cout << "   Монеты: ";
  for (int coin : coins) {
    std::cout << coin << " ";
  }
  std::cout << "\n";
  std::cout << "   Сумма: " << amount << "\n";

  int min_coins = dp::coin_change_min(coins, amount);
  std::cout << "   Минимальное количество монет: " << min_coins << "\n";

  auto result = dp::coin_change_with_coins(coins, amount);
  std::cout << "   Использованные монеты: ";
  for (int coin : result.second) {
    std::cout << coin << " ";
  }
  std::cout << "\n";
}

void demo_lis() {
  std::cout << "6. Наибольшая возрастающая подпоследовательность (LIS)\n";
  std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

  std::cout << "   Последовательность: ";
  for (int num : nums) {
    std::cout << num << " ";
  }
  std::cout << "\n";

  int length = dp::lis_length(nums);
  std::cout << "   Длина LIS: " << length << "\n";

  std::vector<int> lis = dp::lis_sequence(nums);
  std::cout << "   LIS: ";
  for (int num : lis) {
    std::cout << num << " ";
  }
  std::cout << "\n";
}

int main() {
  std::cout << "Демонстрация алгоритмов динамического программирования\n";

  demo_fibonacci();

  demo_knapsack();

  demo_lcs();

  demo_levenshtein();

  demo_coin_change();

  demo_lis();

  return 0;
}

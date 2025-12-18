#pragma once

#include <unordered_map>

namespace dp {

// Наивная рекурсивная реализация
// Временная сложность: O(2^n)
// Пространственная сложность: O(n)
long long fibonacci_naive(int n);

// Рекурсивная реализация с мемоизацией (нисходящий подход)
// Временная сложность: O(n)
// Пространственная сложность: O(n)
long long fibonacci_memoization(int n);

// Итеративная реализация (восходящий подход)
// Временная сложность: O(n)
// Пространственная сложность: O(1)
long long fibonacci_iterative(int n);

// Вспомогательная функция для мемоизации
long long fibonacci_memoization_helper(int n, std::unordered_map<int, long long>& memo);

} // namespace dp

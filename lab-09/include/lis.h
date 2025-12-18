#pragma once

#include <vector>

namespace dp {

// Наибольшая возрастающая подпоследовательность (длина)
// Временная сложность: O(n^2)
// Пространственная сложность: O(n)
int lis_length(const std::vector<int>& nums);

// LIS с восстановлением подпоследовательности
// Временная сложность: O(n^2)
// Пространственная сложность: O(n)
std::vector<int> lis_sequence(const std::vector<int>& nums);

// Оптимизированная версия с бинарным поиском (только длина)
// Временная сложность: O(n log n)
// Пространственная сложность: O(n)
int lis_length_optimized(const std::vector<int>& nums);

} // namespace dp

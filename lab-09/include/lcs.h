#pragma once

#include <string>
#include <vector>

namespace dp {

// Наибольшая общая подпоследовательность (восходящий подход)
// Временная сложность: O(m * n)
// Пространственная сложность: O(m * n)
int lcs_length(const std::string& s1, const std::string& s2);

// LCS с восстановлением подпоследовательности
// Временная сложность: O(m * n)
// Пространственная сложность: O(m * n)
std::string lcs_string(const std::string& s1, const std::string& s2);

// Оптимизированная версия с одномерным массивом (только длина)
// Временная сложность: O(m * n)
// Пространственная сложность: O(min(m, n))
int lcs_length_optimized(const std::string& s1, const std::string& s2);

} // namespace dp

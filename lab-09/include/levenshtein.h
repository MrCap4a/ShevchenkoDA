#pragma once

#include <string>

namespace dp {

// Расстояние Левенштейна (редакционное расстояние)
// Временная сложность: O(m * n)
// Пространственная сложность: O(m * n)
int levenshtein_distance(const std::string& s1, const std::string& s2);

// Оптимизированная версия с одномерным массивом
// Временная сложность: O(m * n)
// Пространственная сложность: O(min(m, n))
int levenshtein_distance_optimized(const std::string& s1, const std::string& s2);

} // namespace dp

#pragma once

#include <vector>

namespace dp {

// Размен монет: минимальное количество монет для суммы
// Временная сложность: O(amount * coins.size())
// Пространственная сложность: O(amount)
int coin_change_min(const std::vector<int>& coins, int amount);

// Размен монет: количество способов составить сумму
// Временная сложность: O(amount * coins.size())
// Пространственная сложность: O(amount)
int coin_change_ways(const std::vector<int>& coins, int amount);

// Размен монет с восстановлением решения
// Возвращает пару: (минимальное количество монет, номиналы монет)
std::pair<int, std::vector<int>> coin_change_with_coins(
    const std::vector<int>& coins, 
    int amount
);

} // namespace dp

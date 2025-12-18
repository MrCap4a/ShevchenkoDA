#pragma once

#include <vector>
#include <utility>

namespace dp {

// Структура для предмета
struct Item {
    int weight;
    int value;
    
    Item(int w, int v) : weight(w), value(v) {}
};

// Задача о рюкзаке 0-1 (восходящий подход)
// Временная сложность: O(n * capacity)
// Пространственная сложность: O(n * capacity)
int knapsack_01(const std::vector<Item>& items, int capacity);

// Задача о рюкзаке 0-1 с восстановлением решения
// Возвращает пару: (максимальная стоимость, индексы выбранных предметов)
std::pair<int, std::vector<int>> knapsack_01_with_items(
    const std::vector<Item>& items, 
    int capacity
);

// Оптимизированная версия с одномерным массивом
// Временная сложность: O(n * capacity)
// Пространственная сложность: O(capacity)
int knapsack_01_optimized(const std::vector<Item>& items, int capacity);

} // namespace dp

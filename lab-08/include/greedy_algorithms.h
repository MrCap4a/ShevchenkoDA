#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace greedy {

// Интервал для задачи о выборе заявок
struct Interval {
    int start;
    int end;
};

// Элемент для задачи о рюкзаке
struct Item {
    double value;   // ценность
    double weight;  // вес
};

// Результат дробного рюкзака: максимальная стоимость и доли взятых предметов
struct FractionalKnapsackResult {
    double max_value;
    std::vector<double> fractions; // доля для каждого предмета из исходного массива
};

// Жадный выбор заявок (interval scheduling)
// Возвращает подмножество непересекающихся интервалов максимального размера
std::vector<Interval> selectIntervalsGreedy(std::vector<Interval> intervals);

// Жадный алгоритм для дробного рюкзака
FractionalKnapsackResult fractionalKnapsackGreedy(const std::vector<Item>& items, double capacity);

// Жадный алгоритм для задачи о сдаче (монеты в убывающем порядке)
// Возвращает минимальное количество монет и их разбиение
std::vector<int> coinChangeGreedy(int amount, const std::vector<int>& coins);

// Узел дерева Хаффмана
struct HuffmanNode {
    char symbol;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char s, int f, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr)
        : symbol(s), frequency(f), left(l), right(r) {}
};

// Построение кодов Хаффмана по частотам символов
// Возвращает отображение символ -> двоичный код в виде строки
std::unordered_map<char, std::string> buildHuffmanCodes(const std::unordered_map<char, int>& frequencies);

// Утилита для освобождения дерева Хаффмана
void freeHuffmanTree(HuffmanNode* root);

} // namespace greedy

#include <gtest/gtest.h>

#include "greedy_algorithms.h"

using namespace greedy;

// --------- Тесты для выбора заявок ---------

TEST(IntervalSchedulingTest, NonOverlappingIntervals) {
    std::vector<Interval> intervals{{1, 3}, {3, 5}, {0, 2}, {5, 7}};
    auto result = selectIntervalsGreedy(intervals);
    // Здесь можно выбрать все интервалы
    ASSERT_EQ(result.size(), 4);
}

TEST(IntervalSchedulingTest, OverlappingIntervals) {
    std::vector<Interval> intervals{{1, 4}, {2, 5}, {3, 6}, {4, 7}};
    auto result = selectIntervalsGreedy(intervals);
    // Максимум два интервала: [1,4] и [4,7]
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].start, 1);
    EXPECT_EQ(result[0].end, 4);
    EXPECT_EQ(result[1].start, 4);
    EXPECT_EQ(result[1].end, 7);
}

// --------- Тесты для дробного рюкзака ---------

TEST(FractionalKnapsackTest, SimpleCase) {
    std::vector<Item> items{{60, 10}, {100, 20}, {120, 30}}; // value, weight
    double capacity = 50;

    auto res = fractionalKnapsackGreedy(items, capacity);

    // Оптимальное значение: 240
    EXPECT_NEAR(res.max_value, 240.0, 1e-6);
    // Проверяем, что доли корректны
    EXPECT_DOUBLE_EQ(res.fractions[0], 1.0);
    EXPECT_DOUBLE_EQ(res.fractions[1], 1.0);
    EXPECT_DOUBLE_EQ(res.fractions[2], 2.0 / 3.0);
}

// --------- Тесты для задачи о монетах ---------

TEST(CoinChangeGreedyTest, RubleCoinsSystem) {
    // Моделируем стандартную систему монет: 10, 5, 2, 1
    std::vector<int> coins{10, 5, 2, 1};
    int amount = 28;

    auto res = coinChangeGreedy(amount, coins);

    // 2*10 + 1*5 + 1*2 + 1*1 = 28
    ASSERT_EQ(res.size(), 4);
    EXPECT_EQ(res[0], 2); // 10
    EXPECT_EQ(res[1], 1); // 5
    EXPECT_EQ(res[2], 1); // 2
    EXPECT_EQ(res[3], 1); // 1
}

// --------- Тесты для алгоритма Хаффмана ---------

TEST(HuffmanTest, SingleSymbol) {
    std::unordered_map<char, int> freq{{'a', 10}};
    auto codes = buildHuffmanCodes(freq);

    ASSERT_EQ(codes.size(), 1);
    // Для одного символа код может быть "0"
    EXPECT_FALSE(codes['a'].empty());
}

TEST(HuffmanTest, SimpleFrequencies) {
    std::unordered_map<char, int> freq{{'a', 5}, {'b', 7}, {'c', 10}, {'d', 15}};
    auto codes = buildHuffmanCodes(freq);

    // Должны быть коды для всех символов
    EXPECT_EQ(codes.size(), 4);

    // Проверяем, что более частые символы имеют не длиннее коды, чем редкие
    EXPECT_LE(codes['d'].size(), codes['a'].size());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

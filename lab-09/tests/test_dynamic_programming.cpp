#include <gtest/gtest.h>
#include "../include/fibonacci.h"
#include "../include/knapsack.h"
#include "../include/lcs.h"
#include "../include/levenshtein.h"
#include "../include/coin_change.h"
#include "../include/lis.h"

// Тесты для чисел Фибоначчи
TEST(FibonacciTest, Naive) {
    EXPECT_EQ(dp::fibonacci_naive(0), 0);
    EXPECT_EQ(dp::fibonacci_naive(1), 1);
    EXPECT_EQ(dp::fibonacci_naive(5), 5);
    EXPECT_EQ(dp::fibonacci_naive(10), 55);
}

TEST(FibonacciTest, Memoization) {
    EXPECT_EQ(dp::fibonacci_memoization(0), 0);
    EXPECT_EQ(dp::fibonacci_memoization(1), 1);
    EXPECT_EQ(dp::fibonacci_memoization(5), 5);
    EXPECT_EQ(dp::fibonacci_memoization(10), 55);
    EXPECT_EQ(dp::fibonacci_memoization(20), 6765);
}

TEST(FibonacciTest, Iterative) {
    EXPECT_EQ(dp::fibonacci_iterative(0), 0);
    EXPECT_EQ(dp::fibonacci_iterative(1), 1);
    EXPECT_EQ(dp::fibonacci_iterative(5), 5);
    EXPECT_EQ(dp::fibonacci_iterative(10), 55);
    EXPECT_EQ(dp::fibonacci_iterative(20), 6765);
}

TEST(FibonacciTest, Consistency) {
    for (int i = 0; i <= 20; ++i) {
        EXPECT_EQ(dp::fibonacci_memoization(i), dp::fibonacci_iterative(i));
    }
}

// Тесты для задачи о рюкзаке
TEST(KnapsackTest, Basic) {
    std::vector<dp::Item> items = {
        {10, 60}, {20, 100}, {30, 120}
    };
    EXPECT_EQ(dp::knapsack_01(items, 50), 220);
}

TEST(KnapsackTest, WithItems) {
    std::vector<dp::Item> items = {
        {10, 60}, {20, 100}, {30, 120}
    };
    auto result = dp::knapsack_01_with_items(items, 50);
    EXPECT_EQ(result.first, 220);
    EXPECT_FALSE(result.second.empty());
}

TEST(KnapsackTest, Optimized) {
    std::vector<dp::Item> items = {
        {10, 60}, {20, 100}, {30, 120}
    };
    EXPECT_EQ(dp::knapsack_01_optimized(items, 50), 220);
    EXPECT_EQ(dp::knapsack_01(items, 50), dp::knapsack_01_optimized(items, 50));
}

// Тесты для LCS
TEST(LCSTest, Basic) {
    EXPECT_EQ(dp::lcs_length("ABCDGH", "AEDFHR"), 3);
    EXPECT_EQ(dp::lcs_length("AGGTAB", "GXTXAYB"), 4);
}

TEST(LCSTest, String) {
    std::string s1 = "ABCDGH";
    std::string s2 = "AEDFHR";
    std::string lcs = dp::lcs_string(s1, s2);
    EXPECT_EQ(lcs.length(), 3);
    
    s1 = "AGGTAB";
    s2 = "GXTXAYB";
    lcs = dp::lcs_string(s1, s2);
    EXPECT_EQ(lcs.length(), 4);
}

TEST(LCSTest, Optimized) {
    std::string s1 = "ABCDGH";
    std::string s2 = "AEDFHR";
    EXPECT_EQ(dp::lcs_length(s1, s2), dp::lcs_length_optimized(s1, s2));
}

// Тесты для расстояния Левенштейна
TEST(LevenshteinTest, Basic) {
    EXPECT_EQ(dp::levenshtein_distance("kitten", "sitting"), 3);
    EXPECT_EQ(dp::levenshtein_distance("saturday", "sunday"), 3);
    EXPECT_EQ(dp::levenshtein_distance("", "abc"), 3);
    EXPECT_EQ(dp::levenshtein_distance("abc", ""), 3);
    EXPECT_EQ(dp::levenshtein_distance("", ""), 0);
}

TEST(LevenshteinTest, Optimized) {
    EXPECT_EQ(dp::levenshtein_distance("kitten", "sitting"), 
              dp::levenshtein_distance_optimized("kitten", "sitting"));
    EXPECT_EQ(dp::levenshtein_distance("saturday", "sunday"), 
              dp::levenshtein_distance_optimized("saturday", "sunday"));
}

// Тесты для размена монет
TEST(CoinChangeTest, MinCoins) {
    std::vector<int> coins = {1, 3, 4};
    EXPECT_EQ(dp::coin_change_min(coins, 6), 2);
    
    coins = {1, 2, 5};
    EXPECT_EQ(dp::coin_change_min(coins, 11), 3);
    EXPECT_EQ(dp::coin_change_min(coins, 0), 0);
}

TEST(CoinChangeTest, Ways) {
    std::vector<int> coins = {1, 2, 5};
    EXPECT_EQ(dp::coin_change_ways(coins, 5), 4);
}

TEST(CoinChangeTest, WithCoins) {
    std::vector<int> coins = {1, 3, 4};
    auto result = dp::coin_change_with_coins(coins, 6);
    EXPECT_EQ(result.first, 2);
    EXPECT_FALSE(result.second.empty());
}

// Тесты для LIS
TEST(LISTest, Length) {
    std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    EXPECT_EQ(dp::lis_length(nums), 4);
    
    nums = {0, 1, 0, 3, 2, 3};
    EXPECT_EQ(dp::lis_length(nums), 4);
}

TEST(LISTest, Sequence) {
    std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    auto seq = dp::lis_sequence(nums);
    EXPECT_EQ(seq.size(), 4);
    
    for (size_t i = 1; i < seq.size(); ++i) {
        EXPECT_LT(seq[i - 1], seq[i]);
    }
}

TEST(LISTest, Optimized) {
    std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    EXPECT_EQ(dp::lis_length(nums), dp::lis_length_optimized(nums));
}

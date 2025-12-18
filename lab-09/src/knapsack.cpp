#include "../include/knapsack.h"
#include <vector>
#include <algorithm>

namespace dp {

int knapsack_01(const std::vector<Item>& items, int capacity) {
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = std::max(
                    dp[i - 1][w],
                    dp[i - 1][w - items[i - 1].weight] + items[i - 1].value
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    
    return dp[n][capacity];
}

std::pair<int, std::vector<int>> knapsack_01_with_items(
    const std::vector<Item>& items, 
    int capacity
) {
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = std::max(
                    dp[i - 1][w],
                    dp[i - 1][w - items[i - 1].weight] + items[i - 1].value
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    
    std::vector<int> selected_items;
    int w = capacity;
    for (int i = n; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected_items.push_back(i - 1);
            w -= items[i - 1].weight;
        }
    }
    
    std::reverse(selected_items.begin(), selected_items.end());
    return {dp[n][capacity], selected_items};
}

int knapsack_01_optimized(const std::vector<Item>& items, int capacity) {
    std::vector<int> dp(capacity + 1, 0);
    
    for (const auto& item : items) {
        for (int w = capacity; w >= item.weight; --w) {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }
    
    return dp[capacity];
}

} // namespace dp

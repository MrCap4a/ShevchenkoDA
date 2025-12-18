#include "../include/coin_change.h"
#include <vector>
#include <algorithm>
#include <climits>

namespace dp {

int coin_change_min(const std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    
    for (int i = 1; i <= amount; ++i) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INT_MAX) {
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int coin_change_ways(const std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    
    for (int coin : coins) {
        for (int i = coin; i <= amount; ++i) {
            dp[i] += dp[i - coin];
        }
    }
    
    return dp[amount];
}

std::pair<int, std::vector<int>> coin_change_with_coins(
    const std::vector<int>& coins, 
    int amount
) {
    std::vector<int> dp(amount + 1, INT_MAX);
    std::vector<int> parent(amount + 1, -1);
    dp[0] = 0;
    
    for (int i = 1; i <= amount; ++i) {
        for (size_t j = 0; j < coins.size(); ++j) {
            int coin = coins[j];
            if (coin <= i && dp[i - coin] != INT_MAX) {
                if (dp[i] > dp[i - coin] + 1) {
                    dp[i] = dp[i - coin] + 1;
                    parent[i] = j;
                }
            }
        }
    }
    
    if (dp[amount] == INT_MAX) {
        return {-1, {}};
    }
    
    std::vector<int> result_coins;
    int current = amount;
    while (current > 0) {
        int coin_idx = parent[current];
        result_coins.push_back(coins[coin_idx]);
        current -= coins[coin_idx];
    }
    
    return {dp[amount], result_coins};
}

} // namespace dp

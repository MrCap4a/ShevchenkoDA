#include "../include/lis.h"
#include <vector>
#include <algorithm>

namespace dp {

int lis_length(const std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    
    int n = nums.size();
    std::vector<int> dp(n, 1);
    
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }
    
    return *std::max_element(dp.begin(), dp.end());
}

std::vector<int> lis_sequence(const std::vector<int>& nums) {
    if (nums.empty()) {
        return {};
    }
    
    int n = nums.size();
    std::vector<int> dp(n, 1);
    std::vector<int> parent(n, -1);
    
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }
    
    int max_idx = 0;
    for (int i = 1; i < n; ++i) {
        if (dp[i] > dp[max_idx]) {
            max_idx = i;
        }
    }
    
    std::vector<int> result;
    int idx = max_idx;
    while (idx != -1) {
        result.push_back(nums[idx]);
        idx = parent[idx];
    }
    
    std::reverse(result.begin(), result.end());
    return result;
}

int lis_length_optimized(const std::vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    
    std::vector<int> tail;
    
    for (int num : nums) {
        auto it = std::lower_bound(tail.begin(), tail.end(), num);
        if (it == tail.end()) {
            tail.push_back(num);
        } else {
            *it = num;
        }
    }
    
    return tail.size();
}

} // namespace dp

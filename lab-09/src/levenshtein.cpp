#include "../include/levenshtein.h"
#include <vector>
#include <algorithm>

namespace dp {

int levenshtein_distance(const std::string& s1, const std::string& s2) {
    int m = s1.length();
    int n = s2.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j;
    }
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + std::min({
                    dp[i - 1][j],      // удаление
                    dp[i][j - 1],      // вставка
                    dp[i - 1][j - 1]   // замена
                });
            }
        }
    }
    
    return dp[m][n];
}

int levenshtein_distance_optimized(const std::string& s1, const std::string& s2) {
    if (s1.length() < s2.length()) {
        return levenshtein_distance_optimized(s2, s1);
    }
    
    int m = s1.length();
    int n = s2.length();
    std::vector<int> prev(n + 1);
    std::vector<int> curr(n + 1);
    
    for (int j = 0; j <= n; ++j) {
        prev[j] = j;
    }
    
    for (int i = 1; i <= m; ++i) {
        curr[0] = i;
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1];
            } else {
                curr[j] = 1 + std::min({
                    prev[j],
                    curr[j - 1],
                    prev[j - 1]
                });
            }
        }
        prev = curr;
    }
    
    return curr[n];
}

} // namespace dp

#include "../include/fibonacci.h"
#include <unordered_map>

namespace dp {

long long fibonacci_naive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

long long fibonacci_memoization_helper(int n, std::unordered_map<int, long long>& memo) {
    if (n <= 1) {
        return n;
    }
    
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    
    memo[n] = fibonacci_memoization_helper(n - 1, memo) + 
              fibonacci_memoization_helper(n - 2, memo);
    return memo[n];
}

long long fibonacci_memoization(int n) {
    std::unordered_map<int, long long> memo;
    return fibonacci_memoization_helper(n, memo);
}

long long fibonacci_iterative(int n) {
    if (n <= 1) {
        return n;
    }
    
    long long prev2 = 0;
    long long prev1 = 1;
    
    for (int i = 2; i <= n; ++i) {
        long long current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
}

} // namespace dp

class Solution {
public:
    int fib(int n) { // top-down with DP
        if (n <= 1){
            return n;
        }
        static vector<int> dp(31,-1);
        if(dp[n] != -1){
            return dp[n];
        }
        dp[n] = fib(n-1) + fib(n-2);
        return dp[n];
    }
};
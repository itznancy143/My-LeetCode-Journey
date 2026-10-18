class Solution {
    static const int MOD = 1e9 + 7;
    vector<vector<long long>> comb;

    long long solve(vector<int>& nums) {
        int n = nums.size();

        if (n <= 2)
            return 1;

        vector<int> left, right;

        int root = nums[0];

        for (int i = 1; i < n; i++) {
            if (nums[i] < root)
                left.push_back(nums[i]);
            else
                right.push_back(nums[i]);
        }

        long long leftWays = solve(left);
        long long rightWays = solve(right);

        long long interleavings = comb[n - 1][left.size()];

        return (((interleavings * leftWays) % MOD)
                * rightWays) % MOD;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();

        // Precompute combinations using Pascal's triangle
        comb.assign(n + 1, vector<long long>(n + 1, 0));

        for (int i = 0; i <= n; i++) {
            comb[i][0] = comb[i][i] = 1;

            for (int j = 1; j < i; j++) {
                comb[i][j] =
                    (comb[i - 1][j - 1] +
                     comb[i - 1][j]) % MOD;
            }
        }

        return (solve(nums) - 1 + MOD) % MOD;
    }
};
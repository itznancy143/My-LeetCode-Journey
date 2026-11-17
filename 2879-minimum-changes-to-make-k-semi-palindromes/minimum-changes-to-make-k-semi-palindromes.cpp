
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();

        const int INF = 1e9;

        vector<vector<int>> cost(n, vector<int>(n, INF));

        // Step 1: Precompute semi-palindrome costs
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r < n; r++) {

                int len = r - l + 1;

                // Find all proper divisors
                for (int d = 1; d < len; d++) {

                    if (len % d != 0)
                        continue;

                    int changes = 0;

                    // Check each group
                    for (int offset = 0; offset < d; offset++) {

                        int left = offset;
                        int right = len - d + offset;

                        while (left < right) {

                            if (s[l + left] != s[l + right])
                                changes++;

                            left += d;
                            right -= d;
                        }
                    }

                    cost[l][r] = min(cost[l][r], changes);
                }
            }
        }

        // Step 2: DP
        vector<vector<int>> dp(
            n + 1, vector<int>(k + 1, INF)
        );

        dp[0][0] = 0;

        for (int j = 1; j <= k; j++) {

            for (int i = 2 * j; i <= n; i++) {

                for (int p = 2 * (j - 1); p < i; p++) {

                    if (dp[p][j - 1] == INF)
                        continue;

                    dp[i][j] = min(
                        dp[i][j],
                        dp[p][j - 1] + cost[p][i - 1]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<long long> cost(n - x + 1);

        // Two multisets to maintain the median
        multiset<int> left, right;

        long long sumLeft = 0, sumRight = 0;

        auto balance = [&]() {
            while (left.size() > right.size() + 1) {
                int val = *left.rbegin();
                left.erase(prev(left.end()));
                sumLeft -= val;

                right.insert(val);
                sumRight += val;
            }

            while (left.size() < right.size()) {
                int val = *right.begin();
                right.erase(right.begin());
                sumRight -= val;

                left.insert(val);
                sumLeft += val;
            }
        };

        auto add = [&](int val) {
            if (left.empty() || val <= *left.rbegin()) {
                left.insert(val);
                sumLeft += val;
            } else {
                right.insert(val);
                sumRight += val;
            }

            balance();
        };

        auto remove = [&](int val) {
            auto it = left.find(val);

            if (it != left.end()) {
                left.erase(it);
                sumLeft -= val;
            } else {
                it = right.find(val);
                right.erase(it);
                sumRight -= val;
            }

            balance();
        };

        auto getCost = [&]() -> long long {
            long long median = *left.rbegin();

            return median * (long long)left.size() - sumLeft
                 + sumRight - median * (long long)right.size();
        };

        // Calculate costs for all windows
        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                cost[i - x + 1] = getCost();
            }
        }

        // Dynamic Programming
        const long long INF = 1e18;

        vector<vector<long long>> dp(
            n + 1, vector<long long>(k + 1, INF)
        );

        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {

                // Skip current element
                dp[i][j] = dp[i - 1][j];

                // Select a window of size x
                if (i >= x && dp[i - x][j - 1] != INF) {
                    dp[i][j] = min(
                        dp[i][j],
                        dp[i - x][j - 1] + cost[i - x]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
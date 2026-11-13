
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 20;

        vector<int> nge(n, -1);
        vector<int> st;

        // Next Greater Element
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.back()] <= nums[i]) {
                st.pop_back();
            }

            if (!st.empty()) {
                nge[i] = st.back();
            }

            st.push_back(i);
        }

        vector<vector<int>> up(LOG, vector<int>(n, -1));
        vector<vector<long long>> sum(
            LOG, vector<long long>(n, 0)
        );

        // Binary lifting preprocessing
        for (int i = 0; i < n; i++) {
            up[0][i] = nge[i];

            if (nge[i] != -1) {
                sum[0][i] = 1LL * nums[i] * (nge[i] - i);
            }
        }

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                int mid = up[j - 1][i];

                if (mid != -1) {
                    up[j][i] = up[j - 1][mid];

                    sum[j][i] = sum[j - 1][i]
                              + sum[j - 1][mid];
                }
            }
        }

        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
        }

        // Calculate minimum operations for [l, r]
        auto getCost = [&](int l, int r) -> long long {
            long long total = 0;
            int p = l;

            for (int j = LOG - 1; j >= 0; j--) {
                int nxt = up[j][p];

                if (nxt != -1 && nxt <= r) {
                    total += sum[j][p];
                    p = nxt;
                }
            }

            total += 1LL * nums[p] * (r - p + 1);

            return total - (pref[r + 1] - pref[l]);
        };

        long long ans = 0;

        // Binary search for each right endpoint
        for (int r = 0; r < n; r++) {
            int low = 0, high = r;

            while (low < high) {
                int mid = low + (high - low) / 2;

                if (getCost(mid, r) <= k) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }

            ans += (r - low + 1);
        }

        return ans;
    }
};
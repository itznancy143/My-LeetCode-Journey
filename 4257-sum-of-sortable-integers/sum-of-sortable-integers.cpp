class Solution {
public:
    bool isRotation(vector<int>& a, vector<int>& b) {
        int k = a.size();

        vector<int> lps(k, 0);

        // Build LPS array for pattern b
        for (int i = 1, len = 0; i < k; ) {
            if (b[i] == b[len]) {
                lps[i++] = ++len;
            } else if (len > 0) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }

        // Search a in b + b, considering starts < k
        for (int i = 0, j = 0; i < 2 * k - 1; i++) {
            int x = b[i % k];

            while (j > 0 && x != a[j])
                j = lps[j - 1];

            if (x == a[j])
                j++;

            if (j == k)
                return true;
        }

        return false;
    }

    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> sortedNums = nums;
        sort(sortedNums.begin(), sortedNums.end());

        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0)
                continue;

            bool valid = true;

            for (int start = 0; start < n; start += k) {
                vector<int> a(nums.begin() + start,
                              nums.begin() + start + k);
                vector<int> b(sortedNums.begin() + start,
                              sortedNums.begin() + start + k);

                if (!isRotation(a, b)) {
                    valid = false;
                    break;
                }
            }

            if (valid)
                ans += k;
        }

        return ans;
    }
};
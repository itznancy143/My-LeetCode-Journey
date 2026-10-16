
class Solution {
    static const int MOD = 1'000'000'007;

    struct Node {
        long long sum = 0;
        long long sumSq = 0;
        long long lazy = 0;
    };

    vector<Node> tree;
    int n;

    void apply(int node, int left, int right, long long val) {
        long long len = right - left + 1;
        long long oldSum = tree[node].sum;

        tree[node].sumSq =
            (tree[node].sumSq
             + 2LL * val % MOD * oldSum % MOD
             + len % MOD * val % MOD * val % MOD) % MOD;

        tree[node].sum = (oldSum + len * val) % MOD;
        tree[node].lazy = (tree[node].lazy + val) % MOD;
    }

    void push(int node, int left, int right) {
        if (tree[node].lazy == 0 || left == right)
            return;

        int mid = left + (right - left) / 2;
        long long val = tree[node].lazy;

        apply(node * 2, left, mid, val);
        apply(node * 2 + 1, mid + 1, right, val);

        tree[node].lazy = 0;
    }

    void update(int node, int left, int right,
                int ql, int qr, long long val) {
        if (qr < left || right < ql)
            return;

        if (ql <= left && right <= qr) {
            apply(node, left, right, val);
            return;
        }

        push(node, left, right);

        int mid = left + (right - left) / 2;

        update(node * 2, left, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, right, ql, qr, val);

        tree[node].sum =
            (tree[node * 2].sum + tree[node * 2 + 1].sum) % MOD;

        tree[node].sumSq =
            (tree[node * 2].sumSq + tree[node * 2 + 1].sumSq) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n, Node());

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int x = nums[r];
            int prev = last[x];

            // Distinct counts increase for starts in [prev + 1, r].
            update(1, 0, n - 1, prev + 1, r, 1);

            // Sum of squared distinct counts for subarrays ending at r.
            ans = (ans + tree[1].sumSq) % MOD;

            last[x] = r;
        }

        return static_cast<int>(ans);
    }
};

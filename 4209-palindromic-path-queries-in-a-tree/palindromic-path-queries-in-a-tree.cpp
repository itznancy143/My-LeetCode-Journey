class Solution {
    struct Fenwick {
        int n;
        vector<int> bit;

        Fenwick(int n) : n(n), bit(n + 2, 0) {}

        void update(int i, int val) {
            for (; i <= n; i += i & -i)
                bit[i] ^= val;
        }

        int query(int i) {
            int res = 0;
            for (; i > 0; i -= i & -i)
                res ^= bit[i];
            return res;
        }
    };

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> up(n, vector<int>(LOG));
        vector<int> depth(n), tin(n), tout(n);
        int timer = 0;

        function<void(int, int)> dfs = [&](int u, int p) {
            tin[u] = ++timer;
            up[u][0] = p;

            for (int j = 1; j < LOG; j++)
                up[u][j] = up[up[u][j - 1]][j - 1];

            for (int v : adj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }

            tout[u] = timer;
        };

        dfs(0, 0);

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v])
                swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++)
                if (diff & (1 << j))
                    u = up[u][j];

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[u][j] != up[v][j]) {
                    u = up[u][j];
                    v = up[v][j];
                }
            }

            return up[u][0];
        };

        Fenwick fw(n + 1);

        auto rangeUpdate = [&](int u, int mask) {
            fw.update(tin[u], mask);
            fw.update(tout[u] + 1, mask);
        };

        for (int u = 0; u < n; u++)
            rangeUpdate(u, 1 << (s[u] - 'a'));

        auto pathMask = [&](int u, int v) {
            int w = lca(u, v);

            int pu = fw.query(tin[u]);
            int pv = fw.query(tin[v]);

            return pu ^ pv ^ (1 << (s[w] - 'a'));
        };

        vector<bool> ans;

        for (string& q : queries) {
            string type;
            int u;
            string third;

            stringstream ss(q);
            ss >> type >> u >> third;

            if (type == "update") {
                char c = third[0];

                int delta = (1 << (s[u] - 'a')) ^
                            (1 << (c - 'a'));

                if (delta != 0) {
                    rangeUpdate(u, delta);
                    s[u] = c;
                }
            } else {
                int v = stoi(third);
                int mask = pathMask(u, v);

                ans.push_back(
                    mask == 0 || (mask & (mask - 1)) == 0
                );
            }
        }

        return ans;
    }
};
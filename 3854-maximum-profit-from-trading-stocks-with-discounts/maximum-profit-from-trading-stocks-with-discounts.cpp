class Solution {
public:
    int B;
    vector<vector<int>> tree;
    vector<int> present, future;

    // merge two knapsack dp arrays
    vector<int> mergeDP(const vector<int>& A, const vector<int>& Bdp) {
        vector<int> res(B + 1, INT_MIN);
        for (int i = 0; i <= B; i++) {
            if (A[i] < 0) continue;
            for (int j = 0; j + i <= B; j++) {
                if (Bdp[j] < 0) continue;
                res[i + j] = max(res[i + j], A[i] + Bdp[j]);
            }
        }
        return res;
    }

    pair<vector<int>, vector<int>> dfs(int u) {
        vector<int> dp0(B + 1, 0); // no discount
        vector<int> dp1(B + 1, 0); // discount available

        for (int v : tree[u]) {
            auto [c0, c1] = dfs(v);
            dp0 = mergeDP(dp0, c0);
            dp1 = mergeDP(dp1, c1);
        }

        vector<int> new0 = dp0;
        vector<int> new1 = dp0;

        int fullCost = present[u];
        int halfCost = present[u] / 2;

        // buy at full price
        for (int b = fullCost; b <= B; b++) {
            new0[b] = max(new0[b],
                          dp1[b - fullCost] + future[u] - fullCost);
        }

        // buy at discounted price
        for (int b = halfCost; b <= B; b++) {
            new1[b] = max(new1[b],
                          dp1[b - halfCost] + future[u] - halfCost);
        }

        return {new0, new1};
    }

    int maxProfit(int n, vector<int>& present_,
                  vector<int>& future_,
                  vector<vector<int>>& hierarchy,
                  int budget) {

        B = budget;
        present = present_;
        future = future_;
        tree.assign(n, {});

        for (auto &e : hierarchy) {
            tree[e[0] - 1].push_back(e[1] - 1);
        }

        auto res = dfs(0); // CEO (root)
        return *max_element(res.first.begin(), res.first.end());
    }
};

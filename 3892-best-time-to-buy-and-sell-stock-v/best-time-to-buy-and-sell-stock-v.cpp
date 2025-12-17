class Solution {
public:
    long long maximumProfit(vector<int>& prices, int k) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;

        const long long NEG = -1e18;  // very small value

        // dp[j][state]
        vector<vector<long long>> prev(k + 1, vector<long long>(3, NEG));
        vector<vector<long long>> curr(k + 1, vector<long long>(3, NEG));

        // Day 0 initialization
        for (int j = 0; j <= k; j++) {
            prev[j][0] = 0;  // no position
            if (j > 0) {
                prev[j][1] = -prices[0]; // long
                prev[j][2] = prices[0];  // short
            }
        }

        // DP transitions
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= k; j++) {

                // No position
                curr[j][0] = prev[j][0];
                if (j > 0) {
                    curr[j][0] = max(curr[j][0],
                        max(prev[j][1] + prices[i],   // sell long
                            prev[j][2] - prices[i])  // close short
                    );
                }

                // Holding long
                curr[j][1] = prev[j][1];
                if (j > 0)
                    curr[j][1] = max(curr[j][1],
                                     prev[j - 1][0] - prices[i]);

                // Holding short
                curr[j][2] = prev[j][2];
                if (j > 0)
                    curr[j][2] = max(curr[j][2],
                                     prev[j - 1][0] + prices[i]);
            }
            prev = curr;
        }

        return prev[k][0];  // must end with no open position
    }
};

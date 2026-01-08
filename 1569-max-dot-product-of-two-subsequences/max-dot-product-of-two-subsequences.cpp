class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, LLONG_MIN));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                long long product = 1LL * nums1[i - 1] * nums2[j - 1];

                long long take = product;
                if (dp[i - 1][j - 1] != LLONG_MIN) {
                    take = max(take, product + dp[i - 1][j - 1]);
                }

                dp[i][j] = max({
                    take,
                    dp[i - 1][j],
                    dp[i][j - 1]
                });
            }
        }
        return (int)dp[n][m];
    }
};

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        
        // Use long long to prevent overflow during summation
        vector<long long> pref_original(n + 1, 0);
        vector<long long> pref_prices(n + 1, 0);
        
        // 1. Precompute prefix sums
        for (int i = 0; i < n; ++i) {
            pref_original[i + 1] = pref_original[i] + (long long)prices[i] * strategy[i];
            pref_prices[i + 1] = pref_prices[i] + prices[i];
        }
        
        long long total_original_profit = pref_original[n];
        long long max_total_profit = total_original_profit;
        
        // 2. Slide a window of size k across the array
        // i is the starting index of the modified window
        for (int i = 0; i <= n - k; ++i) {
            // Original profit contributed by the segment [i, i + k - 1]
            long long original_segment_profit = pref_original[i + k] - pref_original[i];
            
            // New profit for this segment:
            // Days [i, i + k/2 - 1] -> 0 (hold)
            // Days [i + k/2, i + k - 1] -> price * 1 (sell)
            long long modified_segment_profit = pref_prices[i + k] - pref_prices[i + k / 2];
            
            // Calculate potential profit: Total - Old Segment + New Segment
            long long current_profit = total_original_profit - original_segment_profit + modified_segment_profit;
            
            max_total_profit = max(max_total_profit, current_profit);
        }
        
        return max_total_profit;
    }
};
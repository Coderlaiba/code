class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        // Sort events by start time
        sort(events.begin(), events.end());

        int n = events.size();
        vector<int> maxSuffix(n + 1, 0);

        // Build suffix max array
        for (int i = n - 1; i >= 0; i--) {
            maxSuffix[i] = max(maxSuffix[i + 1], events[i][2]);
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            int currValue = events[i][2];

            // Binary search for next non-overlapping event
            int low = i + 1, high = n - 1, nextIdx = n;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (events[mid][0] > events[i][1]) {
                    nextIdx = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            currValue += maxSuffix[nextIdx];
            ans = max(ans, currValue);
        }

        return ans;
    }
};

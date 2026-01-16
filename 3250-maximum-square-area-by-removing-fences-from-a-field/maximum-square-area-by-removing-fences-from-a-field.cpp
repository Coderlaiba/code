class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        // Add boundaries to the fence lists
        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);
        
        // Sort to calculate distances easily
        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());

        unordered_set<int> hGaps;
        for (int i = 0; i < hFences.size(); ++i) {
            for (int j = i + 1; j < hFences.size(); ++j) {
                hGaps.insert(hFences[j] - hFences[i]);
            }
        }

        long long maxSide = -1;
        for (int i = 0; i < vFences.size(); ++i) {
            for (int j = i + 1; j < vFences.size(); ++j) {
                int gap = vFences[j] - vFences[i];
                if (hGaps.count(gap)) {
                    maxSide = max(maxSide, (long long)gap);
                }
            }
        }

        if (maxSide == -1) return -1;
        return (maxSide * maxSide) % 1000000007;
    }
};
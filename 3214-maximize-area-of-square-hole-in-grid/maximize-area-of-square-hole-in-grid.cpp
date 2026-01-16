class Solution {
public:
    int getMaxGap(vector<int>& bars) {
        sort(bars.begin(), bars.end());
        int max_gap = 1;
        int current_streak = 1;
        
        for (int i = 1; i < bars.size(); ++i) {
            if (bars[i] == bars[i - 1] + 1) {
                current_streak++;
            } else {
                max_gap = max(max_gap, current_streak + 1);
                current_streak = 1;
            }
        }
        return max(max_gap, current_streak + 1);
    }

    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        int max_h = getMaxGap(hBars);
        int max_v = getMaxGap(vBars);
        int side = min(max_h, max_v);
        return side * side;
    }
};
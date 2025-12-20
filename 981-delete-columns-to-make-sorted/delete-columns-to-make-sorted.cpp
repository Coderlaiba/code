class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int m = strs.size();
        int n = strs[0].size();
        int count = 0;

        for (int col = 0; col < n; col++) {
            for (int row = 0; row < m - 1; row++) {
                if (strs[row][col] > strs[row + 1][col]) {
                    count++;
                    break; // delete this column
                }
            }
        }
        return count;
    }
};

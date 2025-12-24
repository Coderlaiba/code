class Solution {
public:
    int minimumBoxes(vector<int>& apples, vector<int>& capacity) {
        int totalApples = 0;
        for (int a : apples) {
            totalApples += a;
        }

        sort(capacity.begin(), capacity.end(), greater<int>());

        int boxes = 0;
        for (int cap : capacity) {
            totalApples -= cap;
            boxes++;
            if (totalApples <= 0) {
                return boxes;
            }
        }

        return boxes;
    }
};

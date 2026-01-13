class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        double low = 0, high = 1e9;

        for (int i = 0; i < 100; i++) { // precision loop
            double mid = (low + high) / 2.0;
            double above = 0, below = 0;

            for (auto &sq : squares) {
                double y = sq[1];
                double side = sq[2];
                double area = side * side;

                if (y >= mid) {
                    above += area;
                } 
                else if (y + side <= mid) {
                    below += area;
                } 
                else {
                    double upper = (y + side - mid) * side;
                    double lower = (mid - y) * side;
                    above += upper;
                    below += lower;
                }
            }

            if (above > below)
                low = mid;
            else
                high = mid;
        }

        return low;
    }
};

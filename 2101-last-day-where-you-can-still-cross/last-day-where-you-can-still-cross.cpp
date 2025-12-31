class Solution {
public:
    int row, col;
    vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};

    bool canCross(int day, vector<vector<int>>& cells) {
        vector<vector<int>> grid(row, vector<int>(col, 0));

        // Flood cells up to 'day'
        for (int i = 0; i < day; i++) {
            grid[cells[i][0] - 1][cells[i][1] - 1] = 1;
        }

        queue<pair<int,int>> q;

        // Start BFS from top row
        for (int j = 0; j < col; j++) {
            if (grid[0][j] == 0) {
                q.push({0, j});
                grid[0][j] = 1;
            }
        }

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if (x == row - 1) return true;

            for (auto &d : dirs) {
                int nx = x + d[0];
                int ny = y + d[1];

                if (nx >= 0 && ny >= 0 && nx < row && ny < col && grid[nx][ny] == 0) {
                    grid[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }

        return false;
    }

    int latestDayToCross(int r, int c, vector<vector<int>>& cells) {
        row = r;
        col = c;

        int low = 1, high = r * c, ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (canCross(mid, cells)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};

#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class SegmentTree {
    int n;
    vector<int> count; // How many squares cover this interval
    vector<long long> len; // Total length covered in this node's range
    vector<int>& coords;

public:
    SegmentTree(vector<int>& x_coords) : coords(x_coords) {
        n = x_coords.size();
        count.assign(4 * n, 0);
        len.assign(4 * n, 0);
    }

    void update(int node, int start, int end, int L, int R, int val) {
        if (L <= start && end <= R) {
            count[node] += val;
        } else {
            int mid = (start + end) / 2;
            if (L < mid) update(2 * node, start, mid, L, R, val);
            if (R > mid) update(2 * node + 1, mid, end, L, R, val);
        }
        
        if (count[node] > 0) {
            len[node] = coords[end] - coords[start];
        } else {
            if (end - start > 1) {
                len[node] = len[2 * node] + len[2 * node + 1];
            } else {
                len[node] = 0;
            }
        }
    }

    long long query() { return len[1]; }
};

struct Event {
    int y, type, x1, x2;
    bool operator<(const Event& other) const {
        return y < other.y;
    }
};

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        vector<int> x_coords;
        vector<Event> events;
        for (auto& s : squares) {
            int x = s[0], y = s[1], l = s[2];
            x_coords.push_back(x);
            x_coords.push_back(x + l);
            events.push_back({y, 1, x, x + l});
            events.push_back({y + l, -1, x, x + l});
        }
        
        sort(x_coords.begin(), x_coords.end());
        x_coords.erase(unique(x_coords.begin(), x_coords.end()), x_coords.end());
        sort(events.begin(), events.end());

        auto get_idx = [&](int val) {
            return lower_bound(x_coords.begin(), x_coords.end(), val) - x_coords.begin();
        };

        SegmentTree st(x_coords);
        double total_area = 0;
        for (int i = 0; i < events.size() - 1; ++i) {
            st.update(1, 0, x_coords.size() - 1, get_idx(events[i].x1), get_idx(events[i].x2), events[i].type);
            total_area += (double)st.query() * (events[i+1].y - events[i].y);
        }

        // Second pass to find the y-level for half area
        double target = total_area / 2.0;
        double current_area = 0;
        
        // Reset tree for second sweep
        SegmentTree st2(x_coords);
        for (int i = 0; i < events.size() - 1; ++i) {
            st2.update(1, 0, x_coords.size() - 1, get_idx(events[i].x1), get_idx(events[i].x2), events[i].type);
            double width = st2.query();
            double area_step = width * (events[i+1].y - events[i].y);
            
            if (current_area + area_step >= target) {
                return events[i].y + (target - current_area) / width;
            }
            current_area += area_step;
        }
        
        return events.back().y;
    }
};
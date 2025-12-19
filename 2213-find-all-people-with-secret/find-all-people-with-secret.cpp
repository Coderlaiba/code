class Solution {
public:
    vector<int> parent;

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y)
            parent[y] = x;
    }

    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);

        vector<bool> knows(n, false);
        knows[0] = true;
        knows[firstPerson] = true;

        sort(meetings.begin(), meetings.end(),
             [](auto &a, auto &b) { return a[2] < b[2]; });

        int i = 0;
        while (i < meetings.size()) {
            int time = meetings[i][2];
            vector<int> people;

            // Process all meetings at same time
            while (i < meetings.size() && meetings[i][2] == time) {
                int x = meetings[i][0];
                int y = meetings[i][1];
                unite(x, y);
                people.push_back(x);
                people.push_back(y);
                i++;
            }

            // Check which groups know the secret
            unordered_set<int> secretGroups;
            for (int p : people) {
                if (knows[p]) {
                    secretGroups.insert(find(p));
                }
            }

            // Spread secret within valid groups
            for (int p : people) {
                if (secretGroups.count(find(p))) {
                    knows[p] = true;
                }
            }

            // Reset DSU for next time frame
            for (int p : people) {
                parent[p] = p;
            }
        }

        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (knows[i])
                result.push_back(i);
        }
        return result;
    }
};

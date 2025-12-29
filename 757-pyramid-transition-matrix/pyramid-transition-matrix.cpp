class Solution {
public:
    unordered_map<string, vector<char>> mp;
    unordered_map<string, bool> memo;

    bool dfs(string curr) {
        // ✅ Base case
        if (curr.size() == 1) return true;

        // ✅ Memo check
        if (memo.count(curr)) return memo[curr];

        string next = "";
        bool possible = buildNext(curr, 0, next);

        return memo[curr] = possible;
    }

    bool buildNext(string &curr, int idx, string &next) {
        if (idx == curr.size() - 1) {
            return dfs(next);
        }

        string key = curr.substr(idx, 2);
        if (!mp.count(key)) return false;

        for (char c : mp[key]) {
            next.push_back(c);
            if (buildNext(curr, idx + 1, next))
                return true;
            next.pop_back(); // backtrack
        }

        return false;
    }

    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for (string &s : allowed) {
            mp[s.substr(0, 2)].push_back(s[2]);
        }
        return dfs(bottom);
    }
};

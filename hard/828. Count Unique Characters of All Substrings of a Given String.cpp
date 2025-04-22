class Solution {
public:
    int uniqueLetterString(string s) {
        int n = s.size();
        vector<vector<int>> memo(26, vector<int>(2, -1));
        int res = 0;
        for (int i = 0; i < n; ++i) {
            int cid = s[i] - 'A';
            int cur = memo[cid][1];
            int pre = memo[cid][0];
            if (cur != -1) {
                res += (cur - pre) * (i - cur);
            }
            memo[cid][0] = memo[cid][1];
            memo[cid][1] = i;
        }

        for (int c = 0; c < 26; ++c) {
            int cur = memo[c][1];
            int pre = memo[c][0];
            if (cur != -1) {
                res += (cur - pre) * (n - cur);
            }
        }
        return res;
    }
};

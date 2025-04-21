const int MAX_N = 1000;
int mn[MAX_N * 4], todo[MAX_N * 4], last[MAX_N], last2[MAX_N];

class Solution {
    inline void _do(int o, int v) {
        mn[o] += v;
        todo[o] += v;
    }

    inline void spread(int o) {
        if (todo[o]) {
            _do(o * 2, todo[o]);
            _do(o * 2 + 1, todo[o]);
            todo[o] = 0;
        }
    }

    void update(int o, int l, int r, int L, int R, int v) {
        if (L > r || R < l) return;
        if (L <= l && r <= R) return _do(o, v);
        spread(o);
        int m = (l + r) >> 1;
        update(o * 2, l, m, L, R, v);
        update(o * 2 + 1, m + 1, r, L, R, v);
        mn[o] = min(mn[o * 2], mn[o * 2 + 1]);
    }

    int query(int o, int l, int r, int L, int R) {
        if (L > r || R < l) return INT_MAX;
        if (L <= l && r <= R) return mn[o];
        spread(o);
        int m = (l + r) >> 1;
        return min(query(o * 2, l, m, L, R), query(o * 2 + 1, m + 1, r, L, R));
    }

public:
    int minCost(vector<int>& nums, int k) {
        const int n = nums.size();
        memset(mn, 0, sizeof(int) * 4 * n);
        memset(todo, 0, sizeof(int) * 4 * n);
        memset(last, 0, sizeof(int) * n);
        memset(last2, 0, sizeof(int) * n);

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int x = nums[i - 1];
            update(1, 1, n, i, i, ans);
            update(1, 1, n, last[x] + 1, i, -1);
            if (last[x]) {
                update(1, 1, n, last2[x] + 1, last[x], 1);
            }
            ans = k + query(1, 1, n, 1, i);
            last2[x] = last[x];
            last[x] = i;
        }
        return ans + n;
    }
};

#include <bits/stdc++.h>
using namespace std;

static const int MAXK = 5;

struct node {
    int prod;
    int cnt[MAXK];
    node(int k = 0) {
        prod = 1 % max(1, k);
        memset(cnt, 0, sizeof(cnt));
    }
};

class Solution {
    int n, k, sizeST;
    vector<node> seg;
    
    // Merge two nodes to create a parent node
    node mergeNode(const node &L, const node &R) const {
        node res(k);
        res.prod = int((1LL * L.prod * R.prod) % k);
        
        // Copy counts from left node
        for (int r = 0; r < k; ++r) res.cnt[r] = L.cnt[r];
        
        // Update counts by considering all possibilities from right node
        for (int r2 = 0; r2 < k; ++r2) {
            int c = R.cnt[r2];
            if (c) {
                // Calculate new remainder when combined with left product
                int r = int((1LL * L.prod * r2) % k);
                res.cnt[r] += c;
            }
        }
        return res;
    }

    // Build the segment tree from array a
    void build(const vector<int> &a) {
        sizeST = 1;
        while (sizeST < n) sizeST <<= 1;
        seg.assign(2 * sizeST, node(k));
        
        // Initialize leaf nodes
        for (int i = 0; i < n; ++i) {
            int v = a[i] % k;
            node &nd = seg[sizeST + i];
            nd = node(k);
            nd.prod = v;
            nd.cnt[v] = 1;
        }
        
        // Build parent nodes
        for (int p = sizeST - 1; p > 0; --p) {
            seg[p] = mergeNode(seg[2*p], seg[2*p + 1]);
        }
    }

    // Update a single element in the segment tree
    void updateSeg(int idx, int vmod) {
        int p = sizeST + idx;
        seg[p] = node(k);
        seg[p].prod = vmod;
        seg[p].cnt[vmod] = 1;
        
        // Update all ancestor nodes
        for (p >>= 1; p > 0; p >>= 1) {
            seg[p] = mergeNode(seg[2*p], seg[2*p + 1]);
        }
    }

    // Query the segment tree for range [l, r]
    node querySeg(int l, int r) const {
        node resL(k), resR(k);
        for (l += sizeST, r += sizeST; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)  resL = mergeNode(resL, seg[l++]);
            if (!(r & 1)) resR = mergeNode(seg[r--], resR);
        }
        return mergeNode(resL, resR);
    }

public:
    vector<int> resultArray(vector<int>& nums, int kk, vector<vector<int>>& queries) {
        n = nums.size();
        k = kk;
        build(nums);
        
        int q = queries.size();
        vector<int> ans(q);
        
        for (int i = 0; i < q; ++i) {
            // Update element at queries[i][0] to queries[i][1]
            updateSeg(queries[i][0], queries[i][1] % k);
            
            // Query for range [start, end] after removing prefix
            node nd = querySeg(queries[i][2], n - 1);
            
            // Answer is the count of ways to get remainder queries[i][3]
            ans[i] = nd.cnt[queries[i][3]];
        }
        return ans;
    }
};

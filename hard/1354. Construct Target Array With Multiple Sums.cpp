class Solution {
public:
    bool isPossible(vector<int>& target) {
        priority_queue<int> pq;
        long long total = 0;

        for (int t : target) {
            pq.push(t);
            total += t;
        }

        while (true) {
            int val = pq.top(); pq.pop();
            long long rest = total - val;

            if (val == 1 || rest == 1) return true;
            if (rest == 0 || val <= rest) return false;

            int updated = val % rest;
            if (updated == 0) return false;

            total = rest + updated;
            pq.push(updated);
        }
    }
};

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int total = accumulate(machines.begin(), machines.end(), 0);
        int n = machines.size();
        if (total % n != 0) {
            return -1;
        }
        int target = total / n;
        int moves = 0;
        int cumulative_diff = 0;
        for (int i = 0; i < n; ++i) {
            int diff = machines[i] - target;
            cumulative_diff += diff;
            moves = max(moves, max(abs(cumulative_diff), diff));
        }
        return moves;
    }
};

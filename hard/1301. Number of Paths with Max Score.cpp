#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        const int MOD = 1e9 + 7;
        int n = board.size();
        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, {-1, 0}));
        
        // Initialize the starting point 'E' at (0,0)
        dp[0][0] = {0, 1};

        // Directions: down, right, diagonal down-right
        int dirs[3][2] = {{1, 0}, {0, 1}, {1, 1}};
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'X' || dp[i][j].second == 0) continue;
                
                for (auto& dir : dirs) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];
                    if (ni >= n || nj >= n || board[ni][nj] == 'X') continue;

                    int val = 0;
                    if (board[ni][nj] != 'S') {
                        val = board[ni][nj] - '0';
                    }

                    int new_sum = dp[i][j].first + val;
                    if (new_sum > dp[ni][nj].first) {
                        dp[ni][nj] = {new_sum, dp[i][j].second};
                    } else if (new_sum == dp[ni][nj].first) {
                        dp[ni][nj].second = (dp[ni][nj].second + dp[i][j].second) % MOD;
                    }
                }
            }
        }

        auto [maxScore, ways] = dp[n-1][n-1];
        if (ways == 0) return {0, 0};
        return {maxScore, ways};
    }
};

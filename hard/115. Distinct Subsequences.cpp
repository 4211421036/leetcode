#include <vector>
#include <string>

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size();
        int n = t.size();
        
        if (m < n) return 0;
        
        vector<unsigned int> dp(n + 1, 0);
        dp[0] = 1;
        
        for (int i = 1; i <= m; ++i) {
            int prev = dp[0];
            for (int j = 1; j <= n; ++j) {
                int temp = dp[j];
                if (s[i-1] == t[j-1]) {
                    dp[j] += prev;
                }
                prev = temp;
            }
        }
        
        return dp[n];
    }
};

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        if (m == 0) return 0;
        
        // Preprocess the pattern (needle)
        vector<int> lps(m, 0);
        for (int i = 1, len = 0; i < m; ) {
            if (needle[i] == needle[len]) {
                lps[i++] = ++len;
            } else if (len) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }
        
        // Search using the preprocessed pattern
        for (int i = 0, j = 0; i < n; ) {
            if (haystack[i] == needle[j]) {
                i++, j++;
                if (j == m) return i - j;
            } else if (j) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
        
        return -1;
    }
};

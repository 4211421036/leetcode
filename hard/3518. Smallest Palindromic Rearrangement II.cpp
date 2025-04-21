class Solution {
public:
    string smallestPalindrome(string s, int k) {
        // Combination calculator
        auto comb = [](int n, int r, long long max_value) -> long long {
            if (r > n) return 0;
            r = min(r, n - r);
            
            long long result = 1;
            for (int i = 1; i <= r; i++) {
                result = result * (n - r + i) / i;
                if (result >= max_value) return max_value;
            }
            return result;
        };
        
        // Permutation counter
        auto countPerms = [&comb](const vector<int>& counts, int positions, long long max_value) -> long long {
            long long perms = 1;
            int remaining = positions;
            
            for (int count : counts) {
                long long ways = comb(remaining, count, max_value);
                perms *= ways;
                if (perms >= max_value) return max_value;
                remaining -= count;
            }
            return perms;
        };
        
        // Maximum needed
        long long max_perms_needed = k + 1LL;
        
        // Character counts
        vector<int> char_freq(26, 0);
        for (char c : s) {
            char_freq[c - 'a']++;
        }
        
        // Process characters
        string middle = "";
        vector<int> half_counts(26, 0);
        
        for (int i = 0; i < 26; i++) {
            if (char_freq[i] % 2 == 1) {
                middle = string(1, 'a' + i);
            }
            half_counts[i] = char_freq[i] / 2;
        }
        
        // Calculate half length
        int half_len = 0;
        for (int count : half_counts) {
            half_len += count;
        }
        
        // Count total possible palindromes
        long long total_palindromes = countPerms(half_counts, half_len, max_perms_needed);
        
        // Check if k is valid
        if (k > total_palindromes) {
            return "";
        }
        
        // Build the first half
        string first_half = "";
        for (int pos = 0; pos < half_len; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half_counts[c] == 0) continue;
                
                // Try this character
                half_counts[c]--;
                
                // Count palindromes with this prefix
                long long palindromes_with_prefix = countPerms(
                    half_counts, half_len - pos - 1, max_perms_needed
                );
                
                if (k > palindromes_with_prefix) {
                    // Skip this character
                    k -= palindromes_with_prefix;
                    half_counts[c]++;
                } else {
                    // Use this character
                    first_half += ('a' + c);
                    break;
                }
            }
        }
        
        // Build the full palindrome
        string result = first_half + middle;
        for (int i = first_half.size() - 1; i >= 0; i--) {
            result += first_half[i];
        }
        
        return result;
    }
};

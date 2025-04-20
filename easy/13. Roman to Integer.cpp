class Solution {
public:
    int romanToInt(string s) {
        // Map to store Roman numeral values
        unordered_map<char, int> romanMap = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };
        
        int result = 0;
        int n = s.length();
        
        for (int i = 0; i < n; i++) {
            // If current value is less than next value, it's a subtractive pair
            if (i < n - 1 && romanMap[s[i]] < romanMap[s[i + 1]]) {
                result -= romanMap[s[i]];
            } else {
                result += romanMap[s[i]];
            }
        }
        
        return result;
    }
};

#include <climits>
#include <string>

using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        int i = 0;
        int sign = 1;
        long result = 0;
        
        // 1. Skip leading whitespace
        while (i < s.size() && s[i] == ' ') {
            i++;
        }
        
        // 2. Handle sign
        if (i < s.size() && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        
        // 3. Convert digits
        while (i < s.size() && isdigit(s[i])) {
            int digit = s[i] - '0';
            
            // Check for overflow
            if (result > (INT_MAX - digit) / 10) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            
            result = result * 10 + digit;
            i++;
        }
        
        return sign * result;
    }
};

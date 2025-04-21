class Solution {
public:
    bool isNumber(string s) {
        bool digitSeen = false;
        bool dotSeen = false;
        bool eSeen = false;
        int countPlusMinus = 0;
        
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            
            if (isdigit(c)) {
                digitSeen = true;
            }
            else if (c == '+' || c == '-') {
                // Sign must be at start or after e/E
                if (i > 0 && (s[i-1] != 'e' && s[i-1] != 'E')) {
                    return false;
                }
            }
            else if (c == '.') {
                // Can't have more than one dot or dot after e
                if (dotSeen || eSeen) {
                    return false;
                }
                dotSeen = true;
            }
            else if (c == 'e' || c == 'E') {
                // Must have digit before and after e
                if (eSeen || !digitSeen) {
                    return false;
                }
                eSeen = true;
                digitSeen = false; // Reset for digits after e
            }
            else {
                // Invalid character
                return false;
            }
        }
        
        return digitSeen;
    }
};

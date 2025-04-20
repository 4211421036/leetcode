class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        
        vector<string> result;
        string current;
        vector<string> digitToLetters = {
            "",     // 0
            "",     // 1
            "abc",  // 2
            "def",  // 3
            "ghi",  // 4
            "jkl",  // 5
            "mno",  // 6
            "pqrs", // 7
            "tuv",  // 8
            "wxyz"  // 9
        };
        
        backtrack(digits, 0, digitToLetters, current, result);
        return result;
    }
    
    void backtrack(const string& digits, int index, const vector<string>& digitToLetters, 
                   string& current, vector<string>& result) {
        if (index == digits.size()) {
            result.push_back(current);
            return;
        }
        
        int digit = digits[index] - '0';
        const string& letters = digitToLetters[digit];
        
        for (char letter : letters) {
            current.push_back(letter);
            backtrack(digits, index + 1, digitToLetters, current, result);
            current.pop_back();
        }
    }
};

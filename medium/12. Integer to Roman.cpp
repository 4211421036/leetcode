class Solution {
public:
    string intToRoman(int num) {
        // Define value-symbol pairs from largest to smallest
        vector<pair<int, string>> valueSymbols = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
            {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
            {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
        };
        
        string result = "";
        
        // Iterate through the value-symbol pairs
        for (auto &pair : valueSymbols) {
            // While the current value can be subtracted from num
            while (num >= pair.first) {
                // Add the symbol to the result
                result += pair.second;
                // Subtract the value from num
                num -= pair.first;
            }
        }
        
        return result;
    }
};

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        
        int m = num1.size(), n = num2.size();
        vector<int> result(m + n, 0);
        
        // Multiply each digit and sum at the appropriate position
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int product = (num1[i] - '0') * (num2[j] - '0');
                int sum = product + result[i + j + 1];
                
                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
            }
        }
        
        // Convert to string and remove leading zeros
        string ans;
        for (int num : result) {
            if (!(ans.empty() && num == 0)) { // Skip leading zeros
                ans.push_back(num + '0');
            }
        }
        
        return ans.empty() ? "0" : ans;
    }
};

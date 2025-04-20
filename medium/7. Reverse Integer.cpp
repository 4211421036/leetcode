class Solution {
public:
    int reverse(int x) {
        int rev = 0;
        
        while (x != 0) {
            int pop = x % 10;
            x /= 10;
            
            // Periksa overflow positif sebelum menambahkan digit
            if (rev > INT_MAX/10 || (rev == INT_MAX/10 && pop > 7)) return 0;
            // Periksa overflow negatif sebelum menambahkan digit
            if (rev < INT_MIN/10 || (rev == INT_MIN/10 && pop < -8)) return 0;
            
            rev = rev * 10 + pop;
        }
        
        return rev;
    }
};

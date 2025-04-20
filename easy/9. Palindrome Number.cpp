class Solution {
public:
    bool isPalindrome(int x) {
        // Bilangan negatif bukan palindrom
        // Angka 0 adalah palindrom, angka berakhiran 0 hanya 0 yang palindrom
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        
        int reversed = 0;
        int original = x;
        
        // Membalik setengah digit dari x
        while (x > reversed) {
            reversed = reversed * 10 + x % 10;
            x /= 10;
        }
        
        // Kasus untuk digit ganjil dan genap
        return x == reversed || x == reversed / 10;
    }
};

#include <string>
#include <utility>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); i++) {
            auto [left1, right1] = expandAroundCenter(s, i, i);      // Kasus ganjil
            auto [left2, right2] = expandAroundCenter(s, i, i + 1);  // Kasus genap
            
            // Cari yang lebih panjang antara keduanya
            if (right1 - left1 > end - start) {
                start = left1;
                end = right1;
            }
            if (right2 - left2 > end - start) {
                start = left2;
                end = right2;
            }
        }
        
        return s.substr(start, end - start + 1);
    }
    
private:
    pair<int, int> expandAroundCenter(const string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }
        // Kembalikan posisi sebelum loop berakhir
        return {left + 1, right - 1};
    }
};

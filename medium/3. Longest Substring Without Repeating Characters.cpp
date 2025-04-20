#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;
        int left = 0;
        int maxLength = 0;
        
        for (int right = 0; right < s.size(); right++) {
            // Jika karakter saat ini sudah ada di set
            while (charSet.find(s[right]) != charSet.end()) {
                charSet.erase(s[left]);  // Hapus karakter dari kiri window
                left++;                 // Geser window ke kanan
            }
            
            // Tambahkan karakter saat ini ke set
            charSet.insert(s[right]);
            
            // Update panjang maksimum
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};

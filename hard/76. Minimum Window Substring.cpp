class Solution {
public:
    string minWindow(string s, string t) {
        // Jika s atau t kosong atau s lebih pendek dari t, return ""
        if (s.empty() || t.empty() || s.size() < t.size()) return "";
        
        // Hitung frekuensi karakter di string t
        vector<int> charCount(128, 0);  // Asumsi ASCII
        for (char c : t) {
            charCount[c]++;
        }
        
        // Inisialisasi variabel untuk sliding window
        int left = 0;
        int right = 0;
        int required = t.size();  // Jumlah karakter yang perlu ditemukan
        int minLen = INT_MAX;
        int minStart = 0;
        
        // Gerakkan sliding window
        while (right < s.size()) {
            // Karakter saat ini berkontribusi untuk memenuhi target?
            if (charCount[s[right]] > 0) {
                required--;
            }
            
            // Kurangi hitungan untuk karakter saat ini
            charCount[s[right]]--;
            right++;
            
            // Ketika semua karakter t sudah ditemukan
            while (required == 0) {
                // Update jika window saat ini lebih kecil
                if (right - left < minLen) {
                    minLen = right - left;
                    minStart = left;
                }
                
                // Mencoba kecilkan window dari kiri
                charCount[s[left]]++;
                
                // Jika karakter yang dikeluarkan merupakan karakter yang dibutuhkan
                if (charCount[s[left]] > 0) {
                    required++;
                }
                
                left++;
            }
        }
        
        return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
    }
};

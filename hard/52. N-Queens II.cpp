class Solution {
public:
    int totalNQueens(int n) {
        // Gunakan bit manipulation untuk tracking lebih cepat
        vector<bool> cols(n, false);
        vector<bool> diag1(2*n-1, false);  // diagonal: r+c
        vector<bool> diag2(2*n-1, false);  // anti-diagonal: r-c+n-1
        
        int count = 0;
        backtrack(0, n, count, cols, diag1, diag2);
        return count;
    }
    
private:
    void backtrack(int row, int n, int& count, 
                  vector<bool>& cols, 
                  vector<bool>& diag1, 
                  vector<bool>& diag2) {
        // Base case: semua queen sudah ditempatkan
        if (row == n) {
            count++;
            return;
        }
        
        // Coba tempatkan queen di setiap kolom pada baris saat ini
        for (int col = 0; col < n; col++) {
            int d1 = row + col;          // Index diagonal utama
            int d2 = row - col + n - 1;  // Index anti-diagonal
            
            // Periksa apakah posisi aman dari serangan
            if (cols[col] || diag1[d1] || diag2[d2]) {
                continue;  // Posisi tidak aman, lanjut ke kolom berikutnya
            }
            
            // Tandai posisi sebagai terisi
            cols[col] = true;
            diag1[d1] = true;
            diag2[d2] = true;
            
            // Rekursi ke baris berikutnya
            backtrack(row + 1, n, count, cols, diag1, diag2);
            
            // Backtrack: hapus queen
            cols[col] = false;
            diag1[d1] = false;
            diag2[d2] = false;
        }
    }
};

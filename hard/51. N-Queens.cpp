class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> results;
        vector<string> board(n, string(n, '.'));
        
        // Use sets to track occupied columns and diagonals
        vector<bool> cols(n, false);
        vector<bool> diag1(2*n-1, false);  // Main diagonals (r+c)
        vector<bool> diag2(2*n-1, false);  // Anti-diagonals (r-c+n-1)
        
        backtrack(results, board, 0, n, cols, diag1, diag2);
        return results;
    }
    
private:
    void backtrack(vector<vector<string>>& results, vector<string>& board, 
                  int row, int n, vector<bool>& cols, 
                  vector<bool>& diag1, vector<bool>& diag2) {
        // Base case: All queens are placed
        if (row == n) {
            results.push_back(board);
            return;
        }
        
        // Try placing queen in each column of current row
        for (int col = 0; col < n; col++) {
            int d1 = row + col;              // Main diagonal index
            int d2 = row - col + n - 1;      // Anti-diagonal index
            
            // Check if position is under attack
            if (cols[col] || diag1[d1] || diag2[d2]) {
                continue;
            }
            
            // Place the queen
            board[row][col] = 'Q';
            cols[col] = true;
            diag1[d1] = true;
            diag2[d2] = true;
            
            // Move to next row
            backtrack(results, board, row + 1, n, cols, diag1, diag2);
            
            // Backtrack: remove the queen
            board[row][col] = '.';
            cols[col] = false;
            diag1[d1] = false;
            diag2[d2] = false;
        }
    }
};

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for(int row = 0;row<9;row++)
        {
            int arr[9] = {};
            for(int col = 0;col<9;col++)
            {
                if (board[row][col] != '.')
                {
                    int no = board[row][col] - '1';
                    arr[no] ++;
                    if(arr[no] > 1)
                        return false;
                }
            }
        }
        for(int col = 0;col<9;col++)
        {                 
            int arr[9] = {};
            for(int row = 0;row<9;row++)
            {
                if (board[row][col] != '.')
                {
                    int no = board[row][col] - '1';
                    arr[no] ++;
                    if(arr[no] > 1)
                        return false;
                }
            }
        }
        int js= 0;
        while(js < 9)
        {
            int is = 0;
            while(is < 9)
            {
                int arr[9] = {};
                for(int row = 0;row<3;row++)
                {
                    for(int col = 0;col<3;col++)
                    {
                        if (board[row+js][col+is] != '.')
                        {
                            int no = board[row+js][col+is] - '1';
                            arr[no] ++;
                            if(arr[no] > 1)
                                return false;
                        }
                    }
                }
                is +=3;
            }
            js += 3;
    }
        return true;
    }
};

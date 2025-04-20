#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthLongestPath(string input) {
        vector<int> levelLengths;
        int maxLength = 0;
        int i = 0;
        int n = input.size();
        
        while (i < n) {
            // Determine the current level
            int level = 0;
            while (i < n && input[i] == '\t') {
                level++;
                i++;
            }
            
            // Get the length of the current name
            int start = i;
            bool isFile = false;
            while (i < n && input[i] != '\n') {
                if (input[i] == '.') {
                    isFile = true;
                }
                i++;
            }
            int length = i - start;
            
            // Calculate the current path length
            int currentLength;
            if (level == 0) {
                currentLength = length;
            } else {
                currentLength = levelLengths[level - 1] + 1 + length;
            }
            
            if (isFile) {
                maxLength = max(maxLength, currentLength);
            } else {
                if (level >= levelLengths.size()) {
                    levelLengths.push_back(currentLength);
                } else {
                    levelLengths[level] = currentLength;
                }
            }
            
            // Move past the newline character
            i++;
        }
        
        return maxLength;
    }
};

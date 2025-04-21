class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int n = words.size();
        int i = 0;
        
        while (i < n) {
            // Step 1: Find words for current line
            int j = i, lineLength = 0;
            while (j < n && lineLength + words[j].size() + (j - i) <= maxWidth) {
                lineLength += words[j].size();
                j++;
            }
            
            // Step 2: Build the line
            string line;
            int numWords = j - i;
            int totalSpaces = maxWidth - lineLength;
            
            // Case 1: Single word or last line - left justified
            if (numWords == 1 || j == n) {
                for (int k = i; k < j; k++) {
                    line += words[k];
                    if (k < j - 1) line += " ";
                }
                line += string(maxWidth - line.size(), ' ');
            }
            // Case 2: Fully justified
            else {
                int baseSpaces = totalSpaces / (numWords - 1);
                int extraSpaces = totalSpaces % (numWords - 1);
                
                for (int k = i; k < j; k++) {
                    line += words[k];
                    if (k < j - 1) {
                        line += string(baseSpaces + (k - i < extraSpaces ? 1 : 0), ' ');
                    }
                }
            }
            
            result.push_back(line);
            i = j;
        }
        
        return result;
    }
};

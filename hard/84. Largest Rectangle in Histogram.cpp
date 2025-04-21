#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> s; // Stack to store bar indices
        int max_area = 0; // Initialize maximum area
        int n = heights.size(); // Number of bars in the histogram
        
        for (int i = 0; i <= n; ++i) {
            // If i == n, set h = 0 to process remaining bars in the stack
            int h = (i == n) ? 0 : heights[i];
            
            // While the stack is not empty and the current bar is shorter than the bar at the top
            while (!s.empty() && h < heights[s.top()]) {
                int height = heights[s.top()]; // Height of the bar at the top
                s.pop(); // Pop the bar from the stack
                
                // Calculate width: if stack is empty, width = i; else, width = i - s.top() - 1
                int width = s.empty() ? i : (i - s.top() - 1);
                
                // Update the maximum area
                max_area = max(max_area, height * width);
            }
            s.push(i); // Push the current index onto the stack
        }
        
        return max_area; // Return the maximum area found
    }
};

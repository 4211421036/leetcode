class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int maxWater = 0;
        
        while (left < right) {
            // Calculate width between lines
            int width = right - left;
            
            // Calculate area (min height × width)
            int area = min(height[left], height[right]) * width;
            
            // Update maximum area
            maxWater = max(maxWater, area);
            
            // Move the pointer with smaller height inward
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxWater;
    }
};

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        
        // Step 1: Replace non-positive numbers and numbers > n with (n+1)
        for (int i = 0; i < n; i++) {
            if (nums[i] <= 0 || nums[i] > n) {
                nums[i] = n + 1;
            }
        }
        
        // Step 2: Mark present numbers by making nums[abs(num)-1] negative
        for (int i = 0; i < n; i++) {
            int num = abs(nums[i]);
            if (num <= n && nums[num - 1] > 0) {
                nums[num - 1] *= -1;
            }
        }
        
        // Step 3: Find first positive index
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                return i + 1;
            }
        }
        
        // If all numbers 1..n are present, return n+1
        return n + 1;
    }
};

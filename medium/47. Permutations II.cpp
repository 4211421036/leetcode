class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end()); // Sort to handle duplicates
        backtrack(nums, 0, result);
        return result;
    }
    
private:
    void backtrack(vector<int> nums, int start, vector<vector<int>>& result) {
        if (start == nums.size()) {
            result.push_back(nums);
            return;
        }
        
        for (int i = start; i < nums.size(); i++) {
            // Skip duplicates to avoid redundant permutations
            if (i > start && nums[i] == nums[start]) continue;
            
            // Swap and recurse
            swap(nums[start], nums[i]);
            backtrack(nums, start + 1, result);
            // No need to swap back since we're passing nums by value
        }
    }
};

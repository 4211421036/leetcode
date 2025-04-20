class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        int n = nums.size();
        if (n < 4) return result;
        
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < n - 3; i++) {
            // Skip duplicate elements for the first number
            if (i > 0 && nums[i] == nums[i-1]) continue;
            
            for (int j = i + 1; j < n - 2; j++) {
                // Skip duplicate elements for the second number
                if (j > i + 1 && nums[j] == nums[j-1]) continue;
                
                int left = j + 1;
                int right = n - 1;
                long long remaining = (long long)target - nums[i] - nums[j];
                
                while (left < right) {
                    long long sum = (long long)nums[left] + nums[right];
                    
                    if (sum == remaining) {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});
                        
                        // Skip duplicates for the third number
                        while (left < right && nums[left] == nums[left+1]) left++;
                        // Skip duplicates for the fourth number
                        while (left < right && nums[right] == nums[right-1]) right--;
                        
                        left++;
                        right--;
                    } else if (sum < remaining) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        
        return result;
    }
};

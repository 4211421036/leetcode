class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0; // Pointer for non-val elements
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[k] = nums[i];
                k++;
            }
        }
        
        return k;
    }
};

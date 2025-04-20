#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num_map;
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            // Cek apakah complement sudah ada di map
            if (num_map.find(complement) != num_map.end()) {
                return {num_map[complement], i};
            }
            
            // Simpan nilai dan indexnya ke map
            num_map[nums[i]] = i;
        }
        
        // Karena dijamin ada solusi, baris ini sebenarnya tidak akan pernah tercapai
        return {};
    }
};

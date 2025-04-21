class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};
        
        // Sort intervals based on start time
        sort(intervals.begin(), intervals.end());
        
        vector<vector<int>> merged;
        merged.push_back(intervals[0]);
        
        for (int i = 1; i < intervals.size(); i++) {
            // If current interval overlaps with last merged interval
            if (intervals[i][0] <= merged.back()[1]) {
                // Merge them by updating the end time
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
            } else {
                // Add new interval to merged list
                merged.push_back(intervals[i]);
            }
        }
        
        return merged;
    }
};

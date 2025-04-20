class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0; // Tidak bisa menampung air dengan kurang dari 3 batang
        
        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int result = 0;
        
        while (left < right) {
            // Jika height[left] lebih kecil, proses dari sisi kiri
            if (height[left] < height[right]) {
                // Update max dari sisi kiri
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    // Tambahkan air yang terperangkap di posisi ini
                    result += leftMax - height[left];
                }
                left++;
            } 
            // Jika height[right] lebih kecil atau sama, proses dari sisi kanan
            else {
                // Update max dari sisi kanan
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    // Tambahkan air yang terperangkap di posisi ini
                    result += rightMax - height[right];
                }
                right--;
            }
        }
        
        return result;
    }
};

class Solution {
public:
    int divide(int dividend, int divisor) {
        // Handle edge case of INT_MIN / -1 (would overflow)
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }
        
        // Determine the sign of the result
        bool negative = (dividend < 0) ^ (divisor < 0);
        
        // Work with absolute values to simplify calculation
        // Convert to long to handle INT_MIN case
        long dvd = labs(dividend);
        long dvs = labs(divisor);
        long result = 0;
        
        while (dvd >= dvs) {
            long temp = dvs;
            long multiple = 1;
            while (dvd >= (temp << 1)) {
                temp <<= 1;
                multiple <<= 1;
            }
            dvd -= temp;
            result += multiple;
        }
        
        // Apply the sign
        if (negative) {
            result = -result;
        }
        
        // Clamp the result to 32-bit signed integer range
        if (result > INT_MAX) return INT_MAX;
        if (result < INT_MIN) return INT_MIN;
        
        return result;
    }
};

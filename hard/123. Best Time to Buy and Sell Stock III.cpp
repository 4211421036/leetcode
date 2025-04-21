#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int firstBuy = INT_MAX;
        int secondBuy = INT_MAX;
        int firstProfit = 0;
        int secondProfit = 0;
        
        for (int price : prices) {
            firstBuy = min(firstBuy, price);
            firstProfit = max(firstProfit, price - firstBuy);
            secondBuy = min(secondBuy, price - firstProfit);
            secondProfit = max(secondProfit, price - secondBuy);
        }
        
        return secondProfit;
    }
};

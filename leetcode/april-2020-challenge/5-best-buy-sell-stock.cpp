class Solution {
    const int INF = 1e9 + 5;
public:
    int maxProfit(vector<int>& prices) {
        int best_without_stock = 0, best_with_stock = -INF;
        for(int x : prices) {
            best_with_stock = max(best_with_stock, best_without_stock - x);
            best_without_stock = max(best_without_stock, best_with_stock + x);
        }
        return best_without_stock;
    }
};

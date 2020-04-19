class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        const int n = nums.size();
        int product = 1;
        int count_zeros = 0;
        int product_of_non_zeros = 1;
        for(int x : nums) {
            product *= x;
            if(x == 0) {
                count_zeros++;
            }
            else {
                product_of_non_zeros *= x;
            }
        }
        vector<int> answer(n);
        if(product != 0) {
            for(int i = 0; i < n; i++) {
                answer[i] = product / nums[i];
            }
        }
        else if(count_zeros == 1) {
            for(int i = 0; i < n; i++) {
                if(nums[i] == 0) {
                    answer[i] = product_of_non_zeros;
                }
            }
        }
        else {
            // do nothing
        }
        return answer;
        
            /*
        const int n = nums.size();
        vector<int> pref_product;
        pref_product.push_back(1);
        for(int x : nums) {
            pref_product.push_back(pref_product.back() * x);
        }
        //pref[0] = 1
        //pref[1] = a[0]
        //pref[2] = a[0] * a[1]
        //pref[i] == a[i-1] * ... * a[0]
        
        vector<int> suf_product(n + 1);
        suf_product[n] = 1;
        for(int i = n - 1; i >= 0; --i) {
            suf_product[i] = suf_product[i+1] * nums[i];
        }
        vector<int> answer(n);
        for(int i = 0; i < n; i++) {
            answer[i] = pref_product[i] * suf_product[i+1];
        }
        return answer;*/
    }
};

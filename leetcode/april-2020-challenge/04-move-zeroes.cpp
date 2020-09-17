class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int nxt = 0;
        for(int x : nums) {
            if(x != 0) {
                nums[nxt] = x;
                nxt++;
            }
        }
        for(int i = nxt; i < n; i++) {
            nums[i] = 0;
        }   
        //return nums;
    }
};

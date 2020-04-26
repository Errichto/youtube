class Solution {
public:
    bool canJump(vector<int>& nums) {
        // minimize the number of jumps
        if(n <= 1) {
            cout << 0 << endl;
            return true; // 0 jumps
        }
        pair<int,int> interval{0, 0};
        int jumps = 0;
        while(true) {
            jumps++;
            int can_reach = -1;
            for(int i = interval.first; i <= interval.second; ++i) {
                can_reach = max(can_reach, i + nums[i]);
            }
            if(can_reach >= n - 1) {
                cout << jumps << endl;
                return true; // jumps
            }
            interval = {interval.second+1, can_reach};
            //cout << interval.first << " " << interval.second << endl;
            if(interval.first > interval.second) {
                return false;
            }
        }
        assert(false);
        /*
        int n = nums.size();
        int can_reach = 0;
        for(int i = 0; i <= can_reach; ++i) {
            if(i == n - 1) {
                return true;
            }
            can_reach = max(can_reach, i + nums[i]);
        }
        return false;
        */
    }
};

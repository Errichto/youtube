// https://leetcode.com/problems/maximum-equal-frequency/
class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        const int n = nums.size();
        int answer = 0;
        map<int,int> freq;
        map<int,int> freq_freq;
        for(int i = 0; i < n; i++) {
            int x = nums[i];
            if(freq[x] > 0) {
                if(--freq_freq[freq[x]] == 0) {
                    freq_freq.erase(freq[x]);
                }
            }
            ++freq[nums[i]];
            ++freq_freq[freq[x]];
            bool flag = false;
            if((int) freq_freq.size() <= 2) {
                // 3 3 3 3
                pair<int,int> p = *freq_freq.begin();
                if((int) freq_freq.size() == 1) {
                    if(p.first == 1) {
                        flag = true; // (1, 1, 1) -> (1, 1)
                    }
                    // (5)
                    if(p.second == 1) {
                        flag = true;
                    }
                }
                else {
                    pair<int,int> q = *freq_freq.rbegin();
                    // 5 5 5 1
                    if(p.first == 1 && p.second == 1) {
                        flag = true;
                    }
                    // 5 4 4 4 4
                    if(p.first + 1 == q.first && q.second == 1) {
                        flag = true;
                    }
                }
            }
            if(flag) {
                answer = i + 1;
            }
        }
        return answer;
    }
};

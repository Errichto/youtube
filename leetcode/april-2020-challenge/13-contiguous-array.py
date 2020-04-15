class Solution:
    def findMaxLength(self, nums: List[int]) -> int:
        first_oc = {}
        first_oc[0] = 0
        answer = 0
        pref = 0
        n = len(nums)
        for i in range(n):
            pref += (1 if nums[i] == 1 else -1)
            if pref in first_oc:
                answer = max(answer, i + 1 - first_oc[pref])
            else:
                first_oc[pref] = i + 1
        return answer
        
        
"""class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> first_oc;
        first_oc[0] = 0;
        int answer = 0;
        int pref = 0;
        for(int i = 0; i < (int) nums.size(); ++i) {
            pref += (nums[i] == 0 ? -1 : 1);
            auto it = first_oc.find(pref);
            if(it != first_oc.end()) { // exists
                answer = max(answer, i + 1 - first_oc[pref]);
            }
            else {
                first_oc[pref] = i + 1;
            }
        }
        return answer;
        // O(N) space and time
    }
};"""

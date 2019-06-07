// Find Minimum in Rotated Sorted Array, https://leetcode.com/explore/learn/card/binary-search/126/template-ii/949/

class Solution {
public:
    int findMin(vector<int>& a) {
        int n = a.size();
        int left = 0, right = n - 1;
        int ans = -1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(a[mid] <= a[n-1]) {
                ans = a[mid];
                right = mid - 1; // look for something even smaller on the left
            }
            else {
                left = mid + 1;
            }
        }
        return ans;
    }
};

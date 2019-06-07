// First Bad Version, https://leetcode.com/explore/learn/card/binary-search/126/template-ii/947/

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n;
        int ans = -1; // returned if there is no bad version (impossible in this problem though)
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(isBadVersion(mid)) {
                ans = mid;
                right = mid - 1; // maybe there is even ealier bad version on the left
            }
            else {
                left = mid + 1;
            }
        }
        return ans;
    }
};

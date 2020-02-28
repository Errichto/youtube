// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
// video tutorial: https://youtu.be/dVXy6hmE_0U
class Solution {
    int first_pos(vector<int>& a, int x) {
        int n = a.size();
        int first_pos = n; // first >= x
        int low = 0, high = n - 1;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(a[mid] >= x) {
                first_pos = mid;
                high = mid - 1;
            }
            else { // a[mid] < x
                low = mid + 1;
            }
        }
        return first_pos;
    }
public:
    vector<int> searchRange(vector<int>& a, int x) {
        // lower_bound(a.begin(), a.end(), x);
        int first = first_pos(a, x);
        int last = first_pos(a, x + 1) - 1;
        if(first <= last) {
            return {first, last};
        }
        return {-1, -1};
    }
};

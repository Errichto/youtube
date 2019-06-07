// Sqrt(x), https://leetcode.com/explore/learn/card/binary-search/125/template-i/950/
/*
int f() {
	int left = 0, right = n - 1;
    int ans = -1;
	while(left <= right) {
		int mid = left + (right - left) / 2;
		if(property(mid)) {
			ans = mid;
            right = mid - 1; // if we're looking for the first (leftmost element)
		}
		else {
			left = mid + 1;
		}
	}
	return ans;
}
*/

// Find the last number M that M*M <= x.

class Solution {
public:
    int mySqrt(int x) {
       int left = 0, right = x;
        int ans = -1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if((long long) mid * mid <= x) {
                ans = mid;
                left = mid + 1; // we're looking for the last element satisfying the condition
            }
            else {
                right = mid - 1;
            }
        }
        return ans;
    }
};

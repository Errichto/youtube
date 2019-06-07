# Sqrt(x), https://leetcode.com/explore/learn/card/binary-search/125/template-i/950/
# Find the last M such that M*M <= X.
class Solution:
    def mySqrt(self, x: int) -> int:
        L, R = 0, x
        ans = -1 # this -1 shouldn't be returned because we will find some M such that M*M <= x, e.g. M=0 is fine
        while L <= R:
            mid = L + (R - L) // 2
            if mid * mid <= x:
                ans = mid
                L = mid + 1 # look for the last (rightmost) element satisfying the condition
            else:
                R = mid - 1
        return ans
            

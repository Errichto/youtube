# First Bad Version, https://leetcode.com/explore/learn/card/binary-search/126/template-ii/947/

# The isBadVersion API is already defined for you.
# @param version, an integer
# @return a bool
# def isBadVersion(version):

class Solution:
    def firstBadVersion(self, n):
        left, right = 1, n
        ans = -1 # returned if there is no bad version (impossible in this problem though)
        while left <= right:
            mid = left + (right - left) // 2
            if isBadVersion(mid):
                ans = mid
                right = mid - 1 # maybe there is even ealier bad version on the left
            else :
                left = mid + 1
        return ans
        

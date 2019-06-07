# Find Minimum in Rotated Sorted Array, https://leetcode.com/explore/learn/card/binary-search/126/template-ii/949/

class Solution:
    def findMin(self, a: List[int]) -> int:
        n = len(a)
        left, right = 0, len(a) - 1
        ans = -1 # this value won't be returned anyway because there are some elements satisfying the condition "smaller/equal than the last element"
        while left <= right:
            mid = left + (right - left) // 2
            if a[mid] <= a[n-1]:
                ans = a[mid]
                right = mid - 1 # look for something even smaller on the left
            else:
                left = mid + 1;
        return ans

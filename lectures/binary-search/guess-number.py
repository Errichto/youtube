# Guess Number Higher or Lower, https://leetcode.com/explore/learn/card/binary-search/125/template-i/951/

# The guess API is already defined for you.
# @param num, your guess
# @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
# def guess(num):

class Solution(object):
    def guessNumber(self, n):
        left = 1
        right = n
        while left <= right:
            mid = left + (right - left) // 2
            x = guess(mid) # let's remember this value not to repeat the query in ifs below
            if x == 0:
                return mid
            if x == 1:
                left = mid + 1
            else:
                right = mid - 1
        assert False # we shouldn't get here because it's guaranteed the target value is in the array

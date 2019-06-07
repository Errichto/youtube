// Guess Number Higher or Lower, https://leetcode.com/explore/learn/card/binary-search/125/template-i/951/

// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int left = 1, right = n;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            int x = guess(mid); // let's remember this value not to repeat the query in ifs below
            if(x == 0) {
                return mid;
            }
            if(x == 1) {
                left = mid + 1;
            }
            else { // x == -1
                right = mid - 1;
            }
        }
        assert(false); // we shouldn't get here
    }
};

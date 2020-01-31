// https://leetcode.com/problems/break-a-palindrome/
// video: https://youtu.be/iXbJ1qvKg28
class Solution {
public:
    string breakPalindrome(string s) { // O(N)
        int n = s.length();
        if(n == 1) {
            return "";
        }
        for(int i = 0; i < n; i++) {
            int j = n - 1 - i;
            if(i == j) {
                continue;
            }
            if(s[i] != 'a') {
                s[i] = 'a';
                return s;
            }
        }
        s[n-1] = 'b';
        return s;
    }
};

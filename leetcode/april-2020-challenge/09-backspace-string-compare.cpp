// This is not the best solution! Read one without modifying input strings in leetcode solution tab:
// https://leetcode.com/problems/backspace-string-compare/solution/
class Solution {
    void remove(string& s, int& len) {
        for(int i = 0; i < (int) s.length(); ++i) {
            if(s[i] == '#') {
                if(len > 0) {
                    len--;
                }
            }
            else {
                s[len] = s[i];
                len++;
            }
        }
    }
public:
    bool backspaceCompare(string S, string T) {
        int len_s = 0, len_t = 0;
        remove(S, len_s);
        remove(T, len_t);
        if(len_s != len_t) {
            return false;
        }
        for(int i = 0; i < len_s; ++i) {
            if(S[i] != T[i]) {
                return false;
            }
        }
        return true;
        // return len_s == len_t && S == T;
    }
};

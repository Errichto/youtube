// O(N^2 log(N)) solution first, then O(N^2) below
bool is_palindrome(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    return s == rev;
}
// returns true if there is a palindrome of length x
int good(int x, string s) {
    int n = s.length();
    for(int L = 0; L + x <= n; L++) {
        if(is_palindrome(s.substr(L, x))) {
            return L;
        }
    }
    return -1;
}
class Solution {
public:
    string longestPalindrome(string s) {
        int best_len = 0;
        string best_s = "";
        int n = s.length();
        for(int parity : {0, 1}) {
            int low = 1, high = n;
            if(low % 2 != parity) low++;
            if(high % 2 != parity) high--;
            while(low <= high) {
                int mid = (low + high) / 2;
                if(mid % 2 != parity) {
                    mid++;
                }
                if(mid > high) {
                    break;
                }
                int tmp = good(mid, s);
                if(tmp != -1) {
                    if(mid > best_len) {
                        best_len = mid;
                        best_s = s.substr(tmp, mid);
                    }
                    low = mid + 2;
                }
                else {
                    high = mid - 2;
                }
            }
        }
        return best_s;
    }
};

// ===================

class Solution {
public:
    string longestPalindrome(string s) {
        int best_len = 0;
        string best_s = "";
        int n = s.length();
        for(int mid = 0; mid < n; mid++) {
            for(int x = 0; mid - x >= 0 && mid + x < n; x++) {
                if(s[mid-x] != s[mid+x]) {
                    break;
                }
                int len = 2 * x + 1;
                if(len > best_len) {
                    best_len = len;
                    best_s = s.substr(mid - x, len);
                }
            }
        }
        for(int mid = 0; mid < n - 1; mid++) {
            for(int x = 1; mid - x + 1 >= 0 && mid + x < n; x++) {
                if(s[mid-x+1] != s[mid+x]) {
                    break;
                }
                int len = 2 * x;
                if(len > best_len) {
                    best_len = len;
                    best_s = s.substr(mid - x + 1, len);
                }
            }
        }
        return best_s;
    }
};

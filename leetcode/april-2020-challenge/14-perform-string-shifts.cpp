class Solution {
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        int total = 0;
        for(vector<int> pp : shift) {
            if(pp[0] == 0) {
                total -= pp[1];
            }
            else {
                total += pp[1];
            }
        }
        int n = s.length();
        total %= n;
        if(total < 0) {
            total += n;
        }
        // ABCDE
        return s.substr(n-total) + s.substr(0, n-total);
    }
};

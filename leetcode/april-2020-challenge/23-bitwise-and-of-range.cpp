class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int answer = 0;
        for(int bit = 30; bit >= 0; bit--) {
            if((m & (1 << bit)) != (n & (1 << bit))) {
                break;
            }
            else {
                answer |= (m & (1 << bit));
            }
        }
        return answer;
    }
};

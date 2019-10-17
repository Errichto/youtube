// https://leetcode.com/problems/dice-roll-simulation/
class Solution {
    const int mod = 1e9 + 7;
    void add_self(int& a, int b) {
        a = (a + b) % mod;
    }
public:
    int dieSimulator(int n,
                    vector<int>& rollMax) {
        vector<vector<int>> ways(n + 1, vector<int>(6));
        for(int a = 0; a < 6; ++a) {
            for(int len = 1; len <= min(n, rollMax[a]); ++len) {
                ways[len][a]++;
            }
        }
        // O(n * rollMax * poly(6))
        for(int i = 1; i <= n; ++i) {
            for(int prv = 0; prv < 6; ++prv) {
                for(int nxt = 0; nxt < 6; ++nxt) {
                    if(prv == nxt) {
                        continue;
                    }
        for(int len = 1; len <= rollMax[nxt] && i - len >= 0; ++len) {
            add_self(ways[i][nxt], ways[i-len][prv]);
        }
                }
            }
        }
        int answer = 0;
        for(int a = 0; a < 6; a++) {
            add_self(answer, ways[n][a]);
        }
        return answer;
    }
};

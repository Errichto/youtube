// O(n*q*skipped)
#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9 + 5;
void max_self(int& a, int b) {
    a = max(a, b);
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    vector<pair<int,int>> intervals(q);
    for(pair<int,int>& p : intervals) {
        scanf("%d%d", &p.first, &p.second);
        --p.first;
        --p.second;
    }
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> dp(n + 1, vector<int>(3, -INF));
    // dp[x][y] - max number of covered cells if
    // the next cell to paint is 'x' and we skipped 'y' painters so far
    dp[0][0] = 0;
    for(pair<int,int> p : intervals) {
        for(int x = n; x >= 0; --x) {
            int extra = max(0, p.second - max(x, p.first) + 1);
            for(int skipped = 2; skipped >= 0; --skipped) {
                if(skipped != 2) {
                    max_self(dp[x][skipped+1], dp[x][skipped]);
                }
                max_self(dp[max(x, p.second + 1)][skipped], dp[x][skipped] + extra);
            }
        }
    }
    int answer = 0;
    for(int i = 0; i <= n; ++i) {
        answer = max(answer, dp[i][2]); // 2 painters must be skipped
    }
    printf("%d\n", answer);
}

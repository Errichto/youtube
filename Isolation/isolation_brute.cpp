// O(N^2)
#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int MAX_N = 1e5 + 5; // 100,005
vector<int> occurrences[MAX_N];
int cnt[MAX_N], dp[MAX_N];

void add(int a, int b, int diff) {
    for(int i = a; i <= b; ++i) {
        cnt[i] += diff;
    }
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for(int x = 1; x <= n; ++x) {
        occurrences[x].push_back(-1); // fake position
    }
    dp[0] = 1;
    for(int R = 0; R < n; ++R) {
        int x;
        scanf("%d", &x);
        vector<int>& vec = occurrences[x];
        if((int) vec.size() >= 2) {
            add(vec.end()[-2] + 1, vec.back(), -1);
        }
        add(vec.back() + 1, R, 1);
        vec.push_back(R);
        for(int L = 0; L <= R; ++L) {
            if(cnt[L] <= k) {
                dp[R+1] += dp[L];
                if(dp[R+1] >= mod) {
                    dp[R+1] -= mod;
                }
            }
        }
    }
    printf("%d\n", dp[n]);
}

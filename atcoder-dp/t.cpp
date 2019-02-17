#include "bits/stdc++.h"
using namespace std;
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

using ll = long long;

// dp[i][j] - the number of ways to put numbers in prefix of size 'i'
// such that the last number is 'j'

const int nax = 3005;
char cmp[nax];
int dp[nax][nax], pref[nax][nax];

const int mod = 1e9 + 7;

void add_self(int& a, int b) {
    a += b;
    if(a >= mod) {
        a -= mod;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", cmp);
    dp[1][1] = 1;
    for(int len = 2; len <= n; ++len) {
        // let's compute prefix sums on dp[len-1]
        for(int i = 1; i <= len - 1; ++i) {
            pref[len-1][i] = (pref[len-1][i-1] + dp[len-1][i]) % mod;
        }
        for(int b = 1; b <= len; ++b) {
            int L, R;
            if(cmp[len-2] == '<') {
                L = 1, R = b - 1;
            }
            else {
                L = b, R = len - 1;
            }
            if(L <= R) {
                add_self(dp[len][b], (pref[len-1][R] - pref[len-1][L-1] + mod) % mod);
            }
            //~ for(int i = L; i <= R; ++i) {
                //~ add_self(dp[len][b], dp[len-1][i]);
            //~ }
            
            //~ for(int a = 1; a <= len - 1; ++a) {
                //~ int real_a = a;
                //~ if(a >= b) {
                    //~ ++real_a;
                //~ }
                //~ assert(real_a != b);
                //~ if((real_a < b) != (cmp[len-2] == '<')) {
                    //~ continue;
                //~ }
                //~ add_self(dp[len][b], dp[len-1][a]);
            //~ }
        }
    }
    int answer = 0;
    for(int b = 1; b <= n; ++b) {
        add_self(answer, dp[n][b]);
    }
    printf("%d\n", answer);
}

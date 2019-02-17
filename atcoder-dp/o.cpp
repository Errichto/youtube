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
    vector<vector<int>> can(n, vector<int>(n));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            scanf("%d", &can[i][j]);
        }
    }
    vector<int> dp(1 << n); // 2^n
    dp[0] = 1;
    //~ for(int a = 0; a < n; ++a) {
    for(int mask = 0; mask < (1 << n) - 1; ++mask) {
        int a = __builtin_popcount(mask); // the number of bits set to 1
        for(int b = 0; b < n; ++b) {
            if(can[a][b] && !(mask & (1 << b))) {
                int m2 = mask ^ (1 << b);
                //~ debug() << imie(mask) imie(m2) imie(dp[mask]);
                add_self(dp[m2], dp[mask]);
            }
        }
    }
    //~ }
    printf("%d\n", dp[(1<<n)-1]);
}

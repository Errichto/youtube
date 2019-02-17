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

void max_self(ll& a, ll b) {
    a = max(a, b);
}


int main() {
    int n;
    scanf("%d", &n);
    
    int base = 1;
    while(base <= n) {
        base *= 2;
    }
    // base is the smallest power of 2 that is not smaller than n
    vector<ll> tree(2 * base);
    
    vector<int> h(n), a(n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &h[i]);
    }
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    vector<ll> dp(n + 1);
    // dp[i] - the max total beauty so far if the last taken flower has height i
    for(int flower = 0; flower < n; ++flower) {
        
        // max dp[i] for i in [0, h[flower]-1]
        int x = h[flower] + base;
        ll best = 0;
        while(x > 1) {
            if(x % 2 == 1) {
                max_self(best, tree[x-1]);
            }
            x /= 2;
        }
        dp[h[flower]] = best + a[flower];
        
        for(int i = base + h[flower]; i >= 1; i /= 2) {
            max_self(tree[i], dp[h[flower]]);
        }
        
        //~ for(int i = 0; i < h[flower]; ++i) {
            //~ max_self(dp[h[flower]], dp[i] + a[flower]);
        //~ }
    }
    ll answer = 0;
    for(int i = 0; i <= n; ++i) {
        max_self(answer, dp[i]);
    }
    printf("%lld\n", answer);
}

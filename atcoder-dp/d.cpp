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

// O(n * W)

int main() {
    int n, W;
    scanf("%d%d", &n, &W);
    vector<ll> dp(W + 1); // 0 ... W
    // dp[i] - the maximum total value of items with total weight exactly i
    for(int item = 0; item < n; ++item) {
        int weight, value;
        scanf("%d%d", &weight, &value);
        // dp[0] -> dp[3] -> dp[6]
        for(int weight_already = W - weight; weight_already >= 0; --weight_already) {
        //~ for(int weight_already = 0; weight_already <= W - weight; ++weight_already) {
            max_self(dp[weight_already+weight], dp[weight_already] + value);
        }
    }
    ll answer = 0;
    for(int i = 0; i <= W; ++i) {
        max_self(answer, dp[i]);
    }
    printf("%lld\n", answer);
}

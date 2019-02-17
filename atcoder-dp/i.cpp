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



int main() {
    int n;
    scanf("%d", &n);
    // dp[heads]
    // if we had i tosses, then tails=i-heads
    vector<double> dp(n + 1);
    // dp[i] - p-bility that there are i heads so far
    dp[0] = 1;
    for(int coin = 0; coin < n; ++coin) {
        double p_heads;
        scanf("%lf", &p_heads);
        for(int i = coin + 1; i >= 0; --i) {
            dp[i] = (i == 0 ? 0 : dp[i-1] * p_heads) + dp[i] * (1 - p_heads);
        }
    }
    double answer = 0;
    for(int heads = 0; heads <= n; ++heads) {
        int tails = n - heads;
        if(heads > tails) {
            answer += dp[heads];
        }
    }
    printf("%.10lf\n", answer);
}

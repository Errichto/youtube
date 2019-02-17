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
void min_self(ll& a, ll b) {
    a = min(a, b);
}

const ll INF = 1e18L + 5;

int main() {
    int n, W;
    scanf("%d%d", &n, &W);
    vector<int> weight(n), value(n);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", &weight[i], &value[i]);
    }
    int sum_value = 0;
    for(int x : value) {
        sum_value += x;
    }
    vector<ll> dp(sum_value + 1, INF); // 0 ... W
    dp[0] = 0;
    // dp[i] - the minimum total weight of items with total value exactly i
    for(int item = 0; item < n; ++item) {
        for(int value_already = sum_value - value[item]; value_already >= 0; --value_already) {
        //~ for(int weight_already = 0; weight_already <= W - weight; ++weight_already) {
            min_self(dp[value_already+value[item]], dp[value_already] + weight[item]);
        }
    }
    ll answer = 0;
    for(int i = 0; i <= sum_value; ++i) {
        if(dp[i] <= W) {
            answer = max(answer, (ll) i);
        }
        //~ min_self(answer, dp[i]);
    }
    printf("%lld\n", answer);
}

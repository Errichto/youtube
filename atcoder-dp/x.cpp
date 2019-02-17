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

struct S {
    int w, s, v;
    void read() {
        scanf("%d%d%d", &w, &s, &v);
    }
    bool operator <(const S& b) const {
        return w + s < b.w + b.s;
    }
};

int main() {
    int n;
    scanf("%d", &n);
    vector<S> in(n);
    int MAX_S = 20123;
    for(int i = 0; i < n; ++i) {
        in[i].read();
        //~ MAX_S = max(MAX_S, in[i].s + in[i].w);
    }
    sort(in.begin(), in.end());
    vector<ll> dp(MAX_S + 1);
    // dp[i] - best score of boxes with total weight i
    for(S block : in) {
        for(int w = min(block.s, MAX_S - block.w); w >= 0; --w) {
            dp[w+block.w] = max(dp[w+block.w], dp[w] + block.v);
        }
    }
    ll answer = 0;
    for(int i = 0; i <= MAX_S; ++i) {
        answer = max(answer, dp[i]);
    }
    printf("%lld\n", answer);
}

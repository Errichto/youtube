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

const int nax = 405;
const ll INF = 1e18L + 5; // 10^18+5
ll dp[nax][nax];
// dp[i][j] - the minimum total cost of combining interval [i,j] into one vertex

int main() {
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    for(int& x : a) {
        scanf("%d", &x);
    }
    auto sum = [&](int L, int R) {
        ll s = 0;
        for(int i = L; i <= R; ++i) {
            s += a[i];
        }
        return s;
    };
    for(int L = n - 1; L >= 0; --L) {
        for(int R = L; R < n; ++R) {
            if(L == R) {
                dp[L][R] = 0;
            }
            else {
                dp[L][R] = INF;
                ll s = sum(L, R);
                for(int i = L; i <= R - 1; ++i) {
                    dp[L][R] = min(dp[L][R], dp[L][i] + dp[i+1][R] + s);
                }
            }
        }
    }
    
    printf("%lld\n", dp[0][n-1]);
}

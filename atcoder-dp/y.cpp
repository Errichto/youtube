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

const int nax = 2e5 + 5;
int fac[nax], inv_fac[nax];

int mul(int a, int b) {
    return (ll) a * b % mod;
}
int my_pow(int a, int b) {
    int r = 1;
    while(b) {
        if(b % 2) {
            r = mul(r, a);
        }
        a = mul(a, a);
        b /= 2;
    }
    return r;
}
int my_inv(int a) {
    return my_pow(a, mod - 2);
}

int binomial(int a, int b) {
    if(a < 0 || b < 0 || b > a) {
        return 0;
    }
    return mul(fac[a], mul(inv_fac[b], inv_fac[a-b]));
}

int f(int a, int b) {
    int tmp = binomial(a + b, b);
    //~ debug() << imie(a) imie(b) imie(tmp);
    return tmp;
}

int sub(int a, int b) {
    return (a - b + mod) % mod;
}

int main() {
    fac[0] = inv_fac[0] = 1;
    for(int i = 1; i < nax; ++i) {
        fac[i] = mul(fac[i-1], i);
        inv_fac[i] = my_inv(fac[i]);
    }
    int h, w, n;
    scanf("%d%d%d", &h, &w, &n);
    vector<pair<int,int>> in(n);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", &in[i].first, &in[i].second);
    }
    sort(in.begin(), in.end(), [&](pair<int,int> a, pair<int,int> b) {
        return a.first + a.second < b.first + b.second;
    });
    // dp[i] - the number of paths to vertex in[i] such that it's the first
    // forbidden vertex
    
    in.emplace_back(h, w);
    
    vector<int> dp(n + 1);
    for(int i = 0; i <= n; ++i) {
        int tmp = f(in[i].first - 1, in[i].second - 1);
        debug() << imie(tmp);
        for(int j = 0; j < i; ++j) {
            if(in[j].first <= in[i].first && in[j].second <= in[i].second) {
                tmp = sub(tmp, mul(dp[j], f(in[i].first - in[j].first, in[i].second-in[j].second)));
            }
        }
        dp[i] = tmp;
    }
    debug() << imie(dp);
    printf("%d\n", dp[n]);
}

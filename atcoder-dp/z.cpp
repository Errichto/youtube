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

// a * x + b = a2 * x + b2
// x = (b2 - b) / (a - a2)

// ax+b
struct Line {
    ll a, b;
    ll value(ll x) {
        return a * x + b;
    }
    pair<ll,ll> inter(const Line& he) const {
        ll one = he.b - b;
        ll two = a - he.a;
        if(two < 0) {
            one *= -1;
            two *= -1;
        }
        assert(two > 0);
        return {one, two};
    }
};

ll square(ll a) {
    return a * a;
}

int main() {
    int n;
    scanf("%d", &n);
    ll C;
    scanf("%lld", &C);
    vector<int> h(n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &h[i]);
    }
    vector<Line> lines;
    int start = 0;
    for(int i = 0; i < n; ++i) {
        
        while(start <= (int) lines.size() - 2) {
            Line A = lines[start];
            Line B = lines[start+1];
            if(A.value(h[i]) >= B.value(h[i])) {
                ++start;
            }
            else {
                break;
            }
        }
        
        ll best = 0; // dp[i]
        if(i != 0) {
            best = lines[start].value(h[i]) + square(h[i]) + C;
        }
        Line line{-2 * h[i], best + square(h[i])};
        
        while(start <= (int) lines.size() - 2) {
            Line A = lines.end()[-2];
            Line B = lines.end()[-1]; // .back()
            pair<ll,ll> one = A.inter(B);
            pair<ll,ll> two = B.inter(line);
            // one.first/one.second < two.first/two.second
            if((__int128) one.first * two.second >= (__int128) one.second * two.first) {
                lines.pop_back(); // removes B
            }
            else {
                break;
            }
        }
        lines.push_back(line);
        
        if(i == n - 1) {
            printf("%lld\n", best);
        }
    }
}

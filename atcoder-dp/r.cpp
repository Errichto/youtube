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

void add_self(int&a, int b) {
    a += b;
    if(a >= mod) {
        a -= mod;
    }
}
int mul(int a, int b) {
    return (ll) a * b % mod;
}

int n;

struct M {
    vector<vector<int>> t;
    M() {
        t.resize(n, vector<int>(n));
    }
    M operator* (const M& b) const {
        M c = M();
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                for(int k = 0; k < n; ++k) {
                    add_self(c.t[i][k], mul(t[i][j], b.t[j][k]));
                }
            }
        }
        return c;
    }
};

int main() { // O(K * N^2)
    ll k;
    scanf("%d%lld", &n, &k);
    vector<vector<int>> can(n, vector<int>(n));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            scanf("%d", &can[i][j]);
        }
    }
    M answer = M();
    for(int i = 0; i < n; ++i) {
        answer.t[i][i] = 1;
    }
    M m = M();
    m.t = can;
    while(k) {
        if(k % 2) {
            answer = answer * m;
        }
        m = m * m;
        k /= 2;
    }
    int total = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            add_self(total, answer.t[i][j]);
        }
    }
    printf("%d\n", total);
    return 0;
    
    vector<int> dp(n, 1);
    // dp[i] - the number of ways we got to vertex 'i' so far
    for(ll step = 0; step < k; ++step) {
        vector<int> new_dp(n);
        for(int a = 0; a < n; ++a) {
            for(int b = 0; b < n; ++b) {
                if(can[a][b]) {
                    add_self(new_dp[b], dp[a]);
                }
            }
        }
        dp = new_dp;
    }
    //~ int answer = 0;
    //~ for(int i = 0; i < n; ++i) {
        //~ add_self(answer, dp[i]);
    //~ }
    //~ printf("%d\n", answer);
}

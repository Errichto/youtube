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

// O(N * K^2)

void add_self(int& a, int b) {
    a += b;
    if(a >= mod) {
        a -= mod;
    }
}
void sub_self(int& a, int b) {
    a -= b;
    if(a < 0) {
        a += mod;
    }
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<int> dp(k + 1);
    // dp[i] - the number of ways such that we used i candies so far
    dp[0] = 1;
    for(int child = 0; child < n; ++child) {
        int up_to;
        scanf("%d", &up_to);
        vector<int> fake(k + 1);
        for(int used = k; used >= 0; --used) {
            int tmp = dp[used];
            int L = used + 1;
            int R = used + min(up_to, k - used);
            if(L <= R) {
                add_self(fake[L], tmp);
                if(R + 1 <= k) {
                    sub_self(fake[R+1], tmp);
                }
            }
            //~ for(int i = L; i <= R; ++i) {
                //~ add_self(dp[i], tmp);
            //~ }
        }
        int prefix_sum = 0;
        for(int i = 0; i <= k; ++i) {
            add_self(prefix_sum, fake[i]);
            add_self(dp[i], prefix_sum);
        }
    }
    printf("%d\n", dp[k]);
}

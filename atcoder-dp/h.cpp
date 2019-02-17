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

const int nax = 1005;
char sl[nax][nax];

const int mod = 1e9 + 7;

void add_self(int& a, int b) {
    a += b;
    if(a >= mod) {
        a -= mod;
    }
}

int main() {
    int h, w;
    scanf("%d%d", &h, &w);
    for(int row = 0; row < h; ++row) {
        scanf("%s", sl[row]);
    }
    vector<vector<int>> dp(h, vector<int>(w));
    dp[0][0] = 1;
    for(int row = 0; row < h; ++row) {
        for(int col = 0; col < w; ++col) {
            for(int r2 : {row, row + 1}) {
                int c2 = col;
                if(r2 == row) {
                    c2 = col + 1;
                }
                if(r2 < h && c2 < w && sl[r2][c2] == '.') {
                    add_self(dp[r2][c2], dp[row][col]);
                }
            }
        }
    }
    printf("%d\n", dp[h-1][w-1]);
}

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

const int nax = 305;
double p[nax][nax][nax], ev[nax][nax][nax];
// ev[a][b][c] - the expected number of operations so far to get to state (a,b,c)
// easier: p-bility of getting to this state at all

int main() {
    int n;
    scanf("%d", &n);
    vector<int> cnt(4);
    for(int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        ++cnt[x];
    }
    p[cnt[1]][cnt[2]][cnt[3]] = 1;
    for(int c = n; c >= 0; --c) {
        for(int b = n; b >= 0; --b) {
            for(int a = n; a >= 0; --a) {
                if(a == 0 && b == 0 && c == 0) {
                    continue;
                }
                if(a + b + c > n) {
                    continue;
                }
                // dp[a][b][c]
                
                double p_waste = (double) (n - (a + b + c)) / n;
                // p_waste + p_waste^2 + ... = S
                // 1 + S = S / p_waste
                double ev_waste = p_waste / (1 - p_waste) + 1;
                debug() << imie(a) imie(b) imie(c) imie(ev_waste);
                ev[a][b][c] += ev_waste * p[a][b][c];
                
                // remove 1 -> dp[a-1][b][c]
                // we will eventually choose one of a+b+c
                if(a != 0) {
                    double p_go = (double) a / (a + b + c);
                    p[a-1][b][c] += p[a][b][c] * p_go;
                    ev[a-1][b][c] += ev[a][b][c] * p_go;
                }
                
                // remove 2 -> dp[a+1][b-1][c]
                if(b != 0) {
                    double p_go = (double) b / (a + b + c);
                    p[a+1][b-1][c] += p[a][b][c] * p_go;
                    ev[a+1][b-1][c] += ev[a][b][c] * p_go;
                }
                
                // remove 3
                if(c != 0) {
                    double p_go = (double) c / (a + b + c);
                    p[a][b+1][c-1] += p[a][b][c] * p_go;
                    ev[a][b+1][c-1] += ev[a][b][c] * p_go;
                }
            }
        }
    }
    printf("%.10lf\n", ev[0][0][0]); // + cnt[1] + 2 * cnt[2] + 3 * cnt[3]);
}

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

const int nax = 1e5 + 5;
vector<int> edges[nax];

const int mod = 1e9 + 7;
int mul(int a, int b) {
    return (ll) a * b % mod;
}

// returns a pair {black, white}
pair<int,int> dfs(int a, int parent) {
    int all_white = 1; // means: my vertex can be painted black
    int sth_is_black = 0;
    for(int b : edges[a]) {
        if(b != parent) {
            pair<int,int> p = dfs(b, a);
            // p.first is the number of ways to color the subtree
            // such that 'b' is black
            int memo_all_white = all_white;
            all_white = mul(all_white, p.second);
            sth_is_black = (mul(memo_all_white, p.first)
                + mul(sth_is_black, p.first + p.second)) % mod;
        }
    }
    return make_pair(all_white, (all_white + sth_is_black) % mod);
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    pair<int,int> p = dfs(1, -1);
    int answer = (p.first + p.second) % mod;
    printf("%d\n", answer);
}

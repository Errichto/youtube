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

int mod;

int add(int a, int b) {
    return (a + b) % mod;
}
int mul(int a, int b) {
    return (ll) a * b % mod;
}

const int nax = 1e5 + 5;
vector<int> edges[nax], children[nax];
vector<pair<int,int>> downs[nax], pref[nax], suf[nax];
pair<int,int> down[nax], up[nax];
#define all_white first
#define sth_is_black second

pair<int,int> merge(const pair<int,int>& a, const pair<int,int>& b) {
    pair<int,int> p;
    p.all_white = mul(a.all_white, b.all_white);
    p.sth_is_black = add(
        mul(a.sth_is_black, add(b.all_white, b.sth_is_black)),
        mul(a.all_white, b.sth_is_black)
    );
    return p;
}

pair<int,int> process(pair<int,int> p) {
    return {p.all_white, add(p.sth_is_black, p.all_white)};
}

void dfs_one(int a, int parent) {
    pair<int,int> p{1, 0};
    for(int b : edges[a]) {
        if(b != parent) {
            children[a].push_back(b);
            dfs_one(b, a);
            p = merge(p, down[b]);
            downs[a].push_back(down[b]);
            //~ down[a].black = mul(down[a].black,  add(down[b].black, down[b].white) );
            //~ down[a].white = mul(down[a].white, down[b].white);
        }
    }
    down[a] = process(p);
}

void dfs_two(int a, int parent) {
    for(int i = 0; i < (int) children[a].size(); ++i) {
        pair<int,int> p{1, 0};
        if(i != 0) {
            p = merge(p, pref[a][i-1]);
        }
        if(i != (int) downs[a].size() - 1) {
            p = merge(p, suf[a][i+1]);
        }
        if(a != 1) {
            p = merge(p, up[a]);
        }
        int b = children[a][i];
        up[b] = process(p);
        dfs_two(b, a);
    }
}

int main() {
    int n;
    scanf("%d%d", &n, &mod);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    dfs_one(1, -1);
    for(int a = 1; a <= n; ++a) {
        int k = downs[a].size(); // children[a].size
        assert(k == (int) children[a].size());
        pair<int,int> p{1, 0};
        for(int i = 0; i < k; ++i) {
            p = merge(p, downs[a][i]);
            pref[a].push_back(p);
        }
        p = {1, 0};
        for(int i = k - 1; i >= 0; --i) {
            p = merge(p, downs[a][i]);
            suf[a].push_back(p);
        }
        reverse(suf[a].begin(), suf[a].end());
    }
    dfs_two(1, -1);
    for(int a = 1; a <= n; ++a) {
        pair<int,int> p{1, 0};
        if(a != 1) {
            debug() << imie(a) imie(up[a]);
            p = merge(p, up[a]);
        }
        if(!children[a].empty()) {
            debug() << imie(a) imie(pref[a].back());
            p = merge(p, pref[a].back());
        }
        p = process(p);
        printf("%d\n", p.sth_is_black);
    }
}

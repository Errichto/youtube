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

const int nax = 2e5 + 5;
vector<pair<int,int>> intervals[nax];
const ll INF = 1e18L + 5;

// add to the prefix
// give the min of everything

struct S {
    ll small, lazy;
    void merge(const S& a, const S& b) {
        small = min(a.small, b.small);
        assert(lazy == 0);
    }
    void add(ll x) {
        small += x;
        lazy += x;
    }
};
vector<S> tree;

const int TYPE_ADD = 1, TYPE_MIN = 2;
void rec(int id, int low, int high, int q_low, int q_high, int type, ll& x) {
    if(high < q_low || q_high < low) {
        return;
    }
    if(q_low <= low && high <= q_high) {
        if(type == TYPE_ADD) {
            tree[id].add(x);
        }
        else if(type == TYPE_MIN) {
            x = min(x, tree[id].small);
        }
        else {
            assert(false);
        }
        return;
    }
    for(int b : {2 * id, 2 * id + 1}) {
        tree[b].add(tree[id].lazy);
    }
    tree[id].lazy = 0;
    
    int last_left = (low + high) / 2;
    rec(2 * id, low, last_left, q_low, q_high, type, x);
    rec(2 * id + 1, last_left + 1, high, q_low, q_high, type, x);
    
    tree[id].merge(tree[2*id], tree[2*id+1]);
}
        

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    ll sum_of_scores = 0;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        intervals[b].emplace_back(a, c);
        sum_of_scores += c;
    }
    ll answer = 0;
    
    int base = 1;
    while(base <= n + 1) {
        base *= 2;
    }
    tree.resize(2 * base, {INF, 0});
    
    ll whatever = 0 - INF;
    rec(1, 0, base - 1, 0, 0, TYPE_ADD, whatever);
    for(int i = 1; i <= n + 1; ++i) {
        // I want to put '1' here
        for(pair<int,int> p : intervals[i-1]) {
            whatever = p.second;
            rec(1, 0, base - 1, 0, p.first - 1, TYPE_ADD, whatever);
        }
        ll best = INF;
        rec(1, 0, base - 1, 0, base - 1, TYPE_MIN, best);
        if(i == n + 1) {
            answer = best;
        }
        whatever = best - INF;
        rec(1, 0, base - 1, i, i, TYPE_ADD, whatever);
    }
    
    
    printf("%lld\n", sum_of_scores - answer);
}

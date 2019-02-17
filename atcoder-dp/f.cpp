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

template <typename T> void max_self(T& a, T b) {
    a = max(a, b);
}

// dp[n][m]

bool first_row_or_column(pair<int,int> p) {
    return p.first == 0 || p.second == 0;
}

const int INF = 1e9 + 5;

int main() {
    string a, b;
    cin >> a >> b;
    vector<vector<pair<int,pair<int,int>>>> dp(a.length() + 1,
        vector<pair<int,pair<int,int>>>(b.length() + 1, {-INF,{0,0}}));
    dp[0][0] = {0, {0,0}};
    // dp[i][j] - the max total length so far
    for(int i = 0; i < (int) a.length(); ++i) {
        for(int j = 0; j < (int) b.length(); ++j) {
            if(a[i] == b[j]) {
                max_self(dp[i+1][j+1], make_pair(dp[i][j].first + 1, make_pair(i,j)));
            }
            max_self(dp[i+1][j], make_pair(dp[i][j].first, make_pair(i,j)));
            max_self(dp[i][j+1], make_pair(dp[i][j].first, make_pair(i,j)));
        }
    }
    pair<int,pair<int,int>> answer = {0,{0,0}};
    for(int i = 0; i <= (int) a.length(); ++i) {
        for(int j = 0; j <= (int) b.length(); ++j) {
            max_self(answer, make_pair(dp[i][j].first, make_pair(i, j)));
        }
    }
    string s;
    pair<int,int> cur = answer.second;
    while(!first_row_or_column(cur)) {
        int i = cur.first;
        int j = cur.second;
        pair<int,int> previous = dp[i][j].second; // a cell from which we came to (i,j)
        debug() << imie(cur) imie(previous);
        if(previous == make_pair(i - 1, j - 1)) {
            assert(a[i-1] == b[j-1]);
            s += a[i-1];
        }
        cur = previous;
    }
    //~ debug() << answer;
    reverse(s.begin(), s.end());
    cout << s << endl;
}

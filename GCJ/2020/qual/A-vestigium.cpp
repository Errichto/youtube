// GCJ Qual 2020 A. Vestigium https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/000000000020993c
// by Errichto
#include <bits/stdc++.h>
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

int grid[1005][1005];

void test_case() {
	int n;
	scanf("%d", &n);
	vector<set<int>> row(n + 1), col(n + 1);
	long long trace = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			scanf("%d", &grid[i][j]);
			row[i].insert(grid[i][j]);
			col[j].insert(grid[i][j]);
			if(i == j) {
				trace += grid[i][j];
			}
		}
	}
	int bad_rows = 0, bad_cols = 0;
	for(int r = 1; r <= n; ++r) {
		if((int) row[r].size() != n) {
			++bad_rows;
		}
		if((int) col[r].size() != n) {
			++bad_cols;
		}
	}
	printf("%lld %d %d\n", trace, bad_rows, bad_cols);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int nr = 1; nr <= T; nr++) {
		printf("Case #%d: ", nr);
		test_case();
	}
}

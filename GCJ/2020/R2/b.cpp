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

typedef long long ll;


void test_case() {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<int> X(n + 1);
	for(int i = 2; i <= n; ++i) {
		scanf("%d", &X[i]);
	}
	vector<int> order(n + 1);
	vector<int> taken(n + 1);
	order[1] = 1;
	for(int pos = 2; pos <= n; ++pos) {
		for(int a = 2; a <= n; ++a) {
			if(!taken[a] && X[a] < 0 && -X[a] < pos) {
				order[pos] = a;
				taken[a] = pos;
				break;
			}
		}
		if(!order[pos]) {
			int best = -1;
			for(int a = 2; a <= n; ++a) {
				if(!taken[a] && X[a] > 0 && (best == -1 || X[a] < X[best])) {
					best = a;
				}
			}
			assert(best != -1);
			taken[best] = pos;
			order[pos] = best;
		}
	}
	debug() << imie(order);
	// edges.clear();
	vector<vector<pair<int,int>>> edges;
	edges.resize(n + 1);
	for(int i = 0; i < m; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		assert(a < b);
		if(taken[a] < taken[b]) {
			edges[b].emplace_back(a, i);
		}
		else {
			edges[a].emplace_back(b, i);
		}
		// edges[a].emplace_back(b, i);
		// edges[b].emplace_back(a, i);
	}
	vector<int> when(n + 1);
	vector<int> answer(m);
	for(int i = 1; i <= n; ++i) {
		int a = order[i];
		if(X[a] > 0) {
			when[a] = X[a];
		}
		else {
			when[a] = when[order[i-1]];
			if(taken[a] == -X[a] + 1) {
				when[a]++;
			}
			for(int j = 1; j < i; ++j) {
				if(X[order[j]] < 0 && -X[order[j]] < -X[a]) {
					when[a] = max(when[a], when[order[j]] + 1);
				}
			}
		}
		bool achieved = false;
		for(pair<int,int> edge : edges[a]) {
			int b = edge.first;
			// int id = edge.second;
			if(when[b] < when[a]) {
				achieved = true;
			}
		}
		for(pair<int,int> edge : edges[a]) {
			int b = edge.first;
			// int id = edge.second;
			if(!achieved && when[b] == when[a]) {
				debug() << "increase for " imie(a);
				when[a]++;
			}
		}
		for(pair<int,int> edge : edges[a]) {
			int b = edge.first;
			int id = edge.second;
			int cost = when[a] - when[b];
			assert(cost >= 0);
			// if(cost == 0) {
				// debug() << imie(b) imie(a) imie(when[b]) imie(when[a]);
				// cost = 1;
				// when[a]++;
			// }
			answer[id] = max(1, cost);
		}
		if(X[a] > 0) {
			assert(X[a] == when[a]);
		}
	}
	debug() << imie(when);
	for(int id = 0; id < m; ++id) {
		printf(" %d", answer[id]);
	}
	puts("");
}

int main() {
	int T;
	scanf("%d", &T);
	for(int nr = 1; nr <= T; ++nr) {
		printf("Case #%d:", nr);
		test_case();
	}
}

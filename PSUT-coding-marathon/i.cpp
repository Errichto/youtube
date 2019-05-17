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

const int MAX_N = 1e6 + 5;
vector<int> edges[MAX_N];
int preorder[MAX_N];
bool visited[MAX_N];
int parent[MAX_N][20]; // O(N*log(N)) memory
int depth[MAX_N];
// binary pointers / jump pointers / binary lifting
void add_edge(int a, int b) {
	edges[a].push_back(b);
	edges[b].push_back(a);
}

int T = 0;
void dfs(int a) {
	preorder[a] = T++;
	assert(!visited[a]);
	visited[a] = true;
	for(int b : edges[a]) {
		if(!visited[b]) {
			depth[b] = depth[a] + 1;
			parent[b][0] = a;
			for(int i = 1; i < 20; ++i) {
				parent[b][i] = parent[ parent[b][i-1] ][i-1];
			}
			dfs(b);
		}
	}
}

int get_lca(int a, int b) {
	if(depth[a] < depth[b]) {
		swap(a, b);
	}
	for(int i = 19; i >= 0; --i) {
		if(depth[a] >= depth[b] + (1 << i)) {
			a = parent[a][i];
		}
	}
	assert(depth[a] == depth[b]);
	for(int i = 19; i >= 0; --i) {
		if(parent[a][i] != parent[b][i]) {
			a = parent[a][i];
			b = parent[b][i];
		}
	}
	if(a != b) {
		a = parent[a][0];
		b = parent[b][0];
	}
	assert(a == b);
	return a;
}

int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	vector<vector<int>> queries(q);
	for(int i = 0; i < n; ++i) {
		int proj;
		scanf("%d", &proj);
		queries[proj-1].push_back(i);
	}
	for(int i = 0; i < n; ++i) {
		int p;
		scanf("%d", &p);
		--p;
		if(p != -1) {
			add_edge(i, p);
		}
	}
	dfs(0);
	for(vector<int> query : queries) {
		sort(query.begin(), query.end(), [&](int a, int b) {
			return preorder[a] < preorder[b];
		});
		int answer = depth[query[0]] + 1;
		for(int i = 1; i < (int) query.size(); ++i) {
			int a = query[i-1];
			int b = query[i];
			int lca = get_lca(a, b);
			answer += depth[b] - depth[lca];
		}
		printf("%d ", answer);
	}
	puts("");
}

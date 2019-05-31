// B. Pairs, CF #562 (Div. 2)
// https://codeforces.com/contest/1169/problem/B
// O(n)
#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> pairs;

bool ok(int x, int y) {
	for(pair<int,int> p : pairs) {
		if(p.first != x && p.first != y && p.second != x && p.second != y) {
			return false;
		}
	}
	return true;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		pairs.emplace_back(a, b);
	}
	for(int x : {pairs[0].first, pairs[0].second}) {
		if(ok(x, -1)) { // maybe x is enough
			puts("YES");
			return 0;
		}
		for(int i = 1; i < m; ++i) {
			if(pairs[i].first != x && pairs[i].second != x) {
				// y must be an element of pairs[i]
				if(ok(x, pairs[i].first) || ok(x, pairs[i].second)) {
					puts("YES");
					return 0;
				}
				break; // prevents from O(M^2) complexity
			}
		}
	}
	puts("NO");
}

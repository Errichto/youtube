// C. And Reachability, CF #562 (Div. 1)
// https://codeforces.com/contest/1168/problem/C
// O(n*log^2(MAX_A))
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 3e5 + 5;
int a[MAX_N];
int nxt[MAX_N][19];
int recent[19];
/*
nxt[i][b] - smallest index j that:
	1) j is reachable from i, and
	2) a[j] has b-th bit on

recent[b] - while we iterate from N-1 to 0, most recent position j
	such that a[j] has b-th bit on
*/
int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	for(int bit = 0; bit < 19; ++bit) {
		recent[bit] = n;
	}
	for(int i = n - 1; i >= 0; --i) {
		for(int bit = 0; bit < 19; ++bit) {
			nxt[i][bit] = n;
		}
		for(int bit = 0; bit < 19; ++bit) {
			if(a[i] & (1 << bit)) {
				int where = recent[bit];
				if(where != n) {
					nxt[i][bit] = min(nxt[i][bit], where);
					for(int b2 = 0; b2 < 19; ++b2) {
						nxt[i][b2] = min(nxt[i][b2], nxt[where][b2]);
					}
				}
				recent[bit] = i;
			}
		}
	}
	while(q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		--x; // change numbering from [1,N] to [0,N-1]
		--y;
		bool ok = false;
		for(int bit = 0; bit < 19; ++bit) {
			if(a[y] & (1 << bit)) {
				if(nxt[x][bit] <= y) {
					ok = true;
					break;
				}
			}
		}
		puts(ok ? "Shi" : "Fou");
	}
}

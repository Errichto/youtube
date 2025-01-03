#include <bits/stdc++.h>
using namespace std;

const int MOD = 1 << 24;
void f(long long& x) {
	x ^= x * 64;
	x %= MOD;
	x ^= x / 32;
	x %= MOD;
	x ^= x * 2048LL;
	x %= MOD;
}

int vis[21][21][21][21];
int m[21][21][21][21];
// map<vector<int>, int> m;

int main() {
	long long x;
	int id = 0;
	while (scanf("%lld", &x) != EOF) {
		id++;
		vector<int> v;
		int n = 2000;
		v.push_back(x % 10);
		// set<vector<int>> s;
		for (int i = 1; i <= n; i++) {
			f(x);
			v.push_back(x % 10);
			if (i >= 4) {
				int d[4];
				for (int j = 0; j < 4; j++) {
					d[j] = v[i-4+1+j] - v[i-4+j];
				}
				if (vis[d[0]+10][d[1]+10][d[2]+10][d[3]+10] != id) {
					vis[d[0]+10][d[1]+10][d[2]+10][d[3]+10] = id;
					m[d[0]+10][d[1]+10][d[2]+10][d[3]+10] += x % 10;
					// m[d] += x % 10;
				}
			}
		}
	}
	int answer = 0;
	for (int i = 0; i <= 20; i++) { 
		for (int j = 0; j <= 20; j++) {
			for (int k = 0; k <= 20; k++) {
				for (int l = 0; l <= 20; l++) {
					answer = max(answer, m[i][j][k][l]);
				}
			}
		}
	}
	// for (auto p : m) {
		// answer = max(answer, p.second);
	// }
	printf("%d\n", answer);
}

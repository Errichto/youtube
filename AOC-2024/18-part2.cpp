#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 5;

const int S = 71;
bool vis[S][S];

// O(N^2), linear Dijkstra to maximize ids of blocked cells used

int main() {
	vector<pair<int,int>> in;
	const int N = 3450;
	vector<vector<int>> value(S, vector<int>(S, N+1));
	vector<vector<int>> dist(S, vector<int>(S, 0));
	for (int i = 0; i < N; i++) {
		int x, y;
		scanf(" %d,%d", &x, &y);
		in.emplace_back(x, y);
		value[x][y] = i + 1;
	}
	
	// for (int i = 0; i < S; i++) {
		// for (int j = 0; j < S; j++) {
			// printf("%d ", value[i][j]);
		// }
		// puts("");
	// }
	
	vector<pair<int,int>> inv[N+3];
	dist[0][0] = value[0][0];
	inv[dist[0][0]].emplace_back(0, 0);
	
	for (int v = N + 1; v >= 0; v--) {
		for (int z = 0; z < (int) inv[v].size(); z++) {
			pair<int,int> me = inv[v][z];
			int r = me.first;
			int c = me.second;
			if (dist[r][c] != v) {
				continue;
			}
			for (pair<int,int> dir : vector<pair<int,int>>{{-1,0},{1,0},{0,1},{0,-1}}) {
				int r2 = r + dir.first;
				int c2 = c + dir.second;
				if (0 <= min(r2, c2) && max(r2, c2) < S) {
					int x = min(v, value[r2][c2]);
					if (x > dist[r2][c2]) {
						dist[r2][c2] = x;
						inv[x].emplace_back(r2, c2);
					}
				}
			}
		}
	}
	int id = dist[S-1][S-1] - 1;
	cerr << "id = " << id << "\n"; // 0-based
	printf("%d,%d\n", in[id].first, in[id].second);
}

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 5;

const int S = 71;
bool vis[S][S];

int main() {
	for (int i = 0; i < 1024; i++) {
		int x, y;
		scanf(" %d,%d", &x, &y);
		vis[x][y] = true;
	}
	assert(!vis[0][0]);
	vector<vector<int>> dist(S, vector<int>(S, INF));
	vector<pair<int,int>> q;
	q.emplace_back(0, 0);
	dist[0][0] = 0;
	vis[0][0] = true;
	for (int i = 0; i < (int) q.size(); i++) {
		int r = q[i].first;
		int c = q[i].second;
		for (pair<int,int> dir : vector<pair<int,int>>{{-1,0},{1,0},{0,1},{0,-1}}) {
			int r2 = r + dir.first;
			int c2 = c + dir.second;
			if (0 <= min(r2, c2) && max(r2, c2) < S && !vis[r2][c2]) {
				vis[r2][c2] = true;
				dist[r2][c2] = dist[r][c] + 1;
				q.emplace_back(r2, c2);
			}
		}
	}
	printf("%d\n", dist[S-1][S-1]);
}

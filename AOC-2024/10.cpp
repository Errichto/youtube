#include <bits/stdc++.h>
using namespace std;

char a[505][505];
vector<pair<int,int>> dirs{{-1,0},{1,0},{0,-1},{0,1}};
int W, H;
bool vis[505][505];
int dp[505][505];

bool inside(int row, int col) {
	return 0 <= row && row < H && 0 <= col && col < W;
}

// O(H*W)

int dfs(int row, int col) {
	if (vis[row][col]) {
		return dp[row][col];
	}
	vis[row][col] = true;
	if (a[row][col] == '9') {
		return dp[row][col] = 1;
	}
	int total = 0;
	for (pair<int,int> dir : dirs) {
		int r2 = row + dir.first;
		int c2 = col + dir.second;
		if (inside(r2, c2) && a[r2][c2] == a[row][col]+1) {
			total += dfs(r2, c2);
		}
	}
	return dp[row][col] = total;
}

int main() {
	for (int row = 0; scanf("%s", a[row]) != EOF; row++) {
		H = row + 1;
		W = strlen(a[row]);
	}
	int answer = 0;
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			if (a[row][col] == '0') {
				answer += dfs(row, col);
			}
		}
	}
	cout << answer << "\n";
}

#include <bits/stdc++.h>
using namespace std;
char s[1005][1005];
bool vis[1005][1005];
int H, W;
vector<pair<int,int>> dirs{{-1,0},{0,1},{1,0},{0,-1}};

bool inside(int row, int col) {
	return 0 <= row && row < H && 0 <= col && col < W;
}

void dfs(int row, int col, int& area, int& per) {
	vis[row][col] = true;
	area++;
	
	auto good = [&](pair<int,int> dir) {
		int r2 = row + dir.first;
		int c2 = col + dir.second;
		return inside(r2, c2) && s[r2][c2] == s[row][col];
	};
	
	for (int i = 0; i < 4; i++) {
		pair<int,int> dir = dirs[i];
		pair<int,int> dir2 = dirs[(i+1)%4];
		if (!good(dir) && !good(dir2)) {
			per++;
		}
		if (good(dir) && good(dir2) && !good(make_pair(dir.first+dir2.first, dir.second+dir2.second))) {
			per++;
		}
	}
	
	for (pair<int,int> dir : dirs) {
		int r2 = row + dir.first;
		int c2 = col + dir.second;
		if (good(dir) && !vis[r2][c2]) {
			dfs(r2, c2, area, per);
		}
	}
}

int main() {
	for (int row = 0; scanf("%s", s[row]) != EOF; row++) {
		H = row + 1;
		W = strlen(s[row]);
	}
	long long answer = 0;
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			if (!vis[row][col]) {
				int area = 0, per = 0;
				dfs(row, col, area, per);
				answer += area * per;
			}
		}
	}
	printf("%lld\n", answer);
}

#include <bits/stdc++.h>
using namespace std;

const int NAX = 142;
char a[NAX][NAX];
int H, W;
const int INF = 1e9 + 5;
vector<pair<int,int>> dirs{{-1,0},{0,1},{1,0},{0,-1}};

bool inside(int row, int col) {
	return 0 <= row && row < H && 0 <= col && col < W;
}

vector<vector<int>> bfs(pair<int,int> start) {
	vector<vector<int>> d(H, vector<int>(W, INF));
	d[start.first][start.second] = 0;
	vector<pair<int,int>> q;
	q.push_back(start);
	for (int z = 0; z < (int) q.size(); z++) {
		int r = q[z].first;
		int c = q[z].second;
		if (a[r][c] == '#') {
			continue;
		}
		for (pair<int,int> dir : dirs) {
			int r2 = r + dir.first;
			int c2 = c + dir.second;
			if (inside(r2, c2) && d[r2][c2] == INF) {
				d[r2][c2] = d[r][c] + 1;
				q.emplace_back(r2, c2);
			}
		}
	}
	return d;
}

int main() {
	for (int row = 0; scanf("%s", a[row]) != EOF; row++) {
		H = row + 1;
		W = strlen(a[row]);
	}
	pair<int,int> start, end;
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			// printf("%c%c", a[row][col], a[row][col]);
			if (a[row][col] == 'S') {
				start = {row, col};
				a[row][col] = '.';
			}
			if (a[row][col] == 'E') {
				end = {row, col};
				a[row][col] = '.';
			}
		}
		// puts("");
	}
	
	vector<vector<int>> A = bfs(start), B = bfs(end);
	
	int normal = A[end.first][end.second];
	int answer = 0;
	map<int,int> freq;
	for (int r = 0; r < H; r++) {
		for (int c = 0; c < W; c++) {
			if (a[r][c] != '.') {
				continue;
			}
			// if (a[r][c] == '#') {
			const int M = 20;
			for (int r2 = max(0, r - M); r2 <= min(H - 1, r + M); r2++) {
				for (int c2 = max(0, c - M); c2 <= min(W - 1, c + M); c2++) {
					if (abs(r-r2) + abs(c-c2) <= M) {
						if (inside(r2, c2) && a[r2][c2] != '#') {
							int here = A[r][c] + B[r2][c2] + abs(r-r2) + abs(c-c2);
							++freq[normal-here];
							// if (normal - here == 76) {
								// cout << r << " " << c << " " << r2 << " " << c2 << "\n";
							// }
							if (here <= normal - 100) {
								answer++;
							}
						}
					}
				}
			}
			// }
		}
	}
	// for (auto [x,y] : freq) {
		// printf("%d: %d\n", x, y);
	// }
	printf("%d\n", answer);
}
// .................
// .................
// .................
// .................
// .................
// ...Ax............
// ....x............
// ....xxxx.........
// .......B.........
// .................
// .................

// my understanding: start of a cheat is the first (wall) visited

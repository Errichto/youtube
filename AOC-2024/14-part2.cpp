#include <bits/stdc++.h>
using namespace std;
long long ans[2][2];
int main() {
	vector<pair<int,int>> pos, vel;
	const int W = 101;
	const int H = 103;
	// p=57,29 v=-7,-96
	int px, py, vx, vy;
	while (scanf(" p=%d,%d v=%d,%d", &px, &py, &vx, &vy) != EOF) {
		pos.emplace_back(px, py);
		vel.emplace_back(vx, vy);
		// printf("%d..%d\n", px, vy);
		// px = ((px + vx * 100) % W + W) % W;
		// py = ((py + vy * 100) % H + H) % H;
		// if (px != W / 2 && py != H / 2) {
			// ans[px>W/2][py>H/2]++;
		// }
	}
	int turn = 0;
	while (true) {
		turn++;
		vector<string> a(H, string(W, ' '));
		for (int i = 0; i < (int) pos.size(); i++) {
			int& x = pos[i].first;
			int& y = pos[i].second;
			x += vel[i].first;
			x = ((x % W) + W) % W;
			y += vel[i].second;
			y = ((y % H) + H) % H;
			a[x][y] = 'X';
		}
		int cnt = 0;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (j < W-1-j && a[i][j] == 'X' && a[i][W-1-j] == 'X') {
					cnt++;
				}
			}
		}
		if (cnt >= 50) {
			printf("%d ", turn);
			for (int y = 0; y < W; y++) {
				for (int x = 0; x < H; x++) {
					printf("%c", a[x][y]);
				}
				puts("");
			}
			puts("");
			fflush(stdout);
			return 0;
		}
	}
			
	// printf("%lld\n", ans[0][0] * ans[0][1] * ans[1][0] * ans[1][1]);
}

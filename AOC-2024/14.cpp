#include <bits/stdc++.h>
using namespace std;
long long ans[2][2];
int main() {
	const int W = 101;
	const int H = 103;
	// p=57,29 v=-7,-96
	int px, py, vx, vy;
	while (scanf(" p=%d,%d v=%d,%d", &px, &py, &vx, &vy) != EOF) {
		// printf("%d..%d\n", px, vy);
		px = ((px + vx * 100) % W + W) % W;
		py = ((py + vy * 100) % H + H) % H;
		if (px != W / 2 && py != H / 2) {
			ans[px>W/2][py>H/2]++;
		}
	}
	printf("%lld\n", ans[0][0] * ans[0][1] * ans[1][0] * ans[1][1]);
}

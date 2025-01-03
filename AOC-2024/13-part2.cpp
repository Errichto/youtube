#include <bits/stdc++.h>
using namespace std;
int main() {
	char s[105];
	long long answer = 0;
	while (scanf("%s", s) != EOF) {
		scanf(" %s", s);
		int ax, ay, bx, by;
		scanf(" X+%d, ", &ax);
		scanf(" Y+%d", &ay);
		scanf(" %s", s);
		scanf(" %s", s);
		scanf(" X+%d, ", &bx);
		scanf(" Y+%d", &by);
		scanf(" %s", s);
		long long px, py;
		scanf(" X=%lld, ", &px);
		scanf(" Y=%lld", &py);
		px += 10000000000000LL;
		py += 10000000000000LL;
		// printf("%d %d\n", ax, ay);
		// printf("%d %d\n", bx, by);
		
		// i * ax + j * bx = px
		// i = (px - j * bx) / ax
		// i * ay + j * by = py
		// (px - j * bx) / ax * ay + j * by = py
		// (px - j * bx) * ay + j * by * ax = py * ax
		// px * ay - j * bx * ay + j * by * ax = py * ax
		// j * (by * ax - bx * ay) = py * ax - px * ay
		
		long long j = (py * ax - px * ay) / (by * ax - bx * ay);
		long long i = (py * bx - px * by) / (ay * bx - ax * by);
		if (i * ax + j * bx == px) {
			if (i * ay + j * by == py) {
				answer += 3 * i + j;
			}
		}
		// for (int i = 0; i * ax <= px; i++) {
			// assert(bx != 0);
			// int j = (px - i * ax) / bx;
			// if (i * ax + j * bx == px) {
				// if (i * ay + j * by == py) {
					// assert(i <= 100 && j <= 100);
					// answer += 3 * i + j;
					// assert(j == (py * ax - px * ay) / (by * ax - bx * ay));
					// assert(i == (py * bx - px * by) / (ay * bx - ax * by));
				// }
			// }
		// }
	}
	printf("%lld\n", answer);
}

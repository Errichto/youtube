#include <bits/stdc++.h>
using namespace std;
int main() {
	char s[105];
	int answer = 0;
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
		int px, py;
		scanf(" X=%d, ", &px);
		scanf(" Y=%d", &py);
		printf("%d %d\n", ax, ay);
		printf("%d %d\n", bx, by);
		for (int i = 0; i * ax <= px; i++) {
			assert(bx != 0);
			int j = (px - i * ax) / bx;
			if (i * ax + j * bx == px) {
				if (i * ay + j * by == py) {
					assert(i <= 100 && j <= 100);
					answer += 3 * i + j;
				}
			}
		}
	}
	printf("%d\n", answer);
}

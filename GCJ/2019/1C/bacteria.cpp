#include <bits/stdc++.h>
using namespace std;
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
	*this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
// debug & operator << (debug & dd, P p) { dd << "(" << p.x << ", " << p.y << ")"; return dd; }

char grid[17][17];
int dp[17][17][17][17];

int get(int r1, int c1, int r2, int c2) {
	if(r1 <= r2 && c1 <= c2) {
		return dp[r1][c1][r2][c2];
	}
	else {
		return 0;
	}
}

void test_case() {
	int h, w;
	scanf("%d%d", &h, &w);
	for(int row = 0; row < h; ++row) {
		scanf("%s", grid[row]);
	}
	// O(N^6)
	for(int r1 = h - 1; r1 >= 0; --r1) {
		for(int c1 = w - 1; c1 >= 0; --c1) {
			// top left corner at (r1, c1)
			for(int r2 = r1; r2 < h; ++r2) {
				for(int c2 = c1; c2 < w; ++c2) {
					int ways = 0;
					set<int> possible;
					// bottom right corner at (r2, c2)
					for(int row = r1; row <= r2; ++row) {
						// check if this row of subrectangle is empty
						bool ok = true;
						for(int c = c1; c <= c2; ++c) {
							if(grid[row][c] == '#') {
								ok = false;
								break;
							}
						}
						if(ok) {
							int can = get(r1, c1, row - 1, c2) ^ get(row + 1, c1, r2, c2);
							if(can == 0) {
								ways += c2 - c1 + 1;
							}
							possible.insert(can);
						}
					}
					for(int col = c1; col <= c2; ++col) {
						// check if this column of subr. is empty
						bool ok = true;
						for(int r = r1; r <= r2; ++r) {
							if(grid[r][col] == '#') {
								ok = false;
								break;
							}
						}
						if(ok) {
							int can = get(r1, c1, r2, col - 1) ^ get(r1, col + 1, r2, c2);
							if(can == 0) {
								ways += r2 - r1 + 1;
							}
							possible.insert(can);
						}
					}
					int x = 0;
					while(possible.count(x)) {
						x++;
					}
					dp[r1][c1][r2][c2] = x;
					if(r1 == 0 && c1 == 0 && r2 == h - 1 && c2 == w - 1) {
						printf("%d\n", ways);
					}
				}
			}
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int z = 1; z <= T; z++) {
		printf("Case #%d: ", z);
		test_case();
	}
}

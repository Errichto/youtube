// solution for N <= 5 subtask for E
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

int n, k;
bool done;
int grid[105][105];

void rec(int row, int col) {
	if(col == n) {
		col = 0;
		row++;
	}
	if(row == n) {
		int trace = 0;
		for(int i = 0; i < n; ++i) {
			trace += grid[i][i];
		}
		if(trace == k && !done) {
			puts("POSSIBLE");
			for(int r = 0; r < n; ++r) {
				for(int c = 0; c < n; ++c) {
					printf("%d ", grid[r][c]);
				}
				puts("");
			}
			done = true;
		}
		// cout << trace << " ";
		return;
	}
	for(int value = 1; value <= n; ++value) {
		bool ok = true;
		for(int r = 0; r < row; ++r) {
			if(grid[r][col] == value) {
				ok = false;
				break;
			}
		}
		for(int c = 0; c < col; ++c) {
			if(grid[row][c] == value) {
				ok = false;
				break;
			}
		}
		if(ok) {
			grid[row][col] = value;
			rec(row, col + 1);
		}
	}
}

void test_case() {
	scanf("%d", &n);
	scanf("%d", &k);
	done = false;
	rec(0, 0);
	if(!done) {
		puts("IMPOSSIBLE");
	}
	// cout << endl;
	/*
	vector<vector<int>> grid(n, vector<int>(n));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			grid[i][j] = (i - j + n) % n;
		}
	}
	
	set<int> possible;
	for(int a = 0; a < n; ++a) {
		for(int b = a; b < n; ++b) {
			swap(grid[a], grid[b]);
			for(int shift = 0; shift < n; ++shift) {
				int sum = 0;
				for(int i = 0; i < n; ++i) {
					sum += grid[i][(i+shift)%n] + 1;
				}
				if(sum == k) {
					puts("POSSIBLE");
					int got = 0;
					for(int i = 0; i < n; ++i) {
						for(int j = 0; j < n; ++j) {
							int x = grid[i][(j+n+shift)%n] + 1;
							printf("%d ", x);
							if(i == j) got += x;
						}
						
						puts("");
					}
					assert(got == k);
					return;
				}
				possible.insert(sum);
			}
			// for(vector<int> v : grid) {
				// debug() << v;
			// }
			// debug();
			swap(grid[a], grid[b]);
		}
	}
	puts("IMPOSSIBLE");
	debug() << imie(possible);
	*/
	
}

int main() {
	int T;
	scanf("%d", &T);
	for(int nr = 1; nr <= T; nr++) {
		printf("Case #%d: ", nr);
		test_case();
	}
}

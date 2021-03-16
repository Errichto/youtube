// Router placements, Hash Code 2017 finals
// https://storage.googleapis.com/coding-competitions.appspot.com/HC/2017/hashcode2017_final_task.pdf
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

int H, W, R;
int cable_cost, router_cost, B;
pair<int,int> start;

const int MAX_N = 1005;
char grid[MAX_N][MAX_N];
int covered[MAX_N][MAX_N];
int count_covered;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

bool inside(int row, int col) {
	return 0 <= row && row < H && 0 <= col && col < W;
}

int cost;
vector<pair<int,int>> cables, routers;

void clear_everything() {
	cost = 0;
	cables.clear();
	routers.clear();
	count_covered = 0;
	for(int row = 0; row < H; ++row) {
		for(int col = 0; col < W; ++col) {
			covered[row][col] = 0;
		}
	}
}

void add_cable(int row, int col) {
	if(start == make_pair(row, col)) {
		return;
	}
	cost += cable_cost;
	cables.emplace_back(row, col);
}
const int REAL = 0, TRIAL = 1, REMOVAL = 2;
void add_router(int row, int col, int type) {
	if(type == REAL) {
		cost += router_cost;
		routers.emplace_back(row, col);
	}
	for(int r2 = row - R; r2 <= row + R; ++r2) {
		for(int c2 = col - R; c2 <= col + R; ++c2) {
			if(inside(r2, c2) && grid[r2][c2] == '.' /* && !covered[r2][c2] */ ) {
				bool ok = true;
				for(int i = min(row, r2); i <= max(row, r2); ++i) {
					for(int j = min(col, c2); j <= max(col, c2); ++j) {
						if(grid[i][j] == '#') {
							ok = false;
						}
					}
				}
				if(ok) {
					if(type == REAL || type == TRIAL) {
						if(covered[r2][c2]++ == 0) {
							++count_covered;
						}
					}
					else {
						assert(type == REMOVAL);
						if(--covered[r2][c2] == 0) {
							--count_covered;
						}
					}
				}
			}
		}
	}
}

void try_gap(int GAP, bool random = false) {
	// vertical lines
	{
		int col = start.second;
		// while(col - GAP >= 0) {
			// col -= GAP;
		// }
		for(; col < W; col += GAP) {
			bool anything = false;
			for(int row = 0; row < H; ++row) {
				if(grid[row][col] == '.') {
					anything = true;
					break;
				}
			}
			if(!anything) {
				continue;
			}
			int previous_router = 0;
			for(int row = 0; row < H; ++row) {
				add_cable(row, col);
				if(grid[row][col] == '.' && previous_router + 2 * R < row) {
					add_router(row, col, REAL);
					previous_router = row;
				}
			}
			break;
		}
	}
	// horizontal lines
	{
		int row = start.first;
		while(row - GAP >= 0) {
			row -= GAP;
		}
		for(; row < H; row += GAP) {
			int first_dot = start.second, last_dot = start.second;
			bool anything = false;
			for(int col = 0; col < W; ++col) {
				if(grid[row][col] == '.') {
					first_dot = min(first_dot, col);
					last_dot = max(last_dot, col);
					anything = true;
					// break;
				}
			}
			if(!anything) {
				continue;
			}
			int previous_router = first_dot - R;
			for(int col = first_dot; col <= last_dot; ++col) {
				add_cable(row, col);
				if(grid[row][col] == '.' && previous_router + 2 * R + (random ? rand() % 5 : 2) < col) {
					add_router(row, col, REAL);
					previous_router = col;
				}
			}
		}
	}
}

int main() {
	scanf("%d%d%d", &H, &W, &R);
	scanf("%d%d%d", &cable_cost, &router_cost, &B);
	scanf("%d%d", &start.first, &start.second);
	for(int row = 0; row < H; ++row) {
		scanf("%s", grid[row]);
	}
	
	int low = 1, high = H + W;
	while(low < high) {
		int gap = (low + high) / 2;
		try_gap(gap);
		if(cost > B) {
			low = gap + 1;
		}
		else {
			high = gap;
		}
		clear_everything();
	}
	int gap = (low + high) / 2;
	srand(time(NULL));
	try_gap(gap, true);
	
	
	vector<vector<bool>> is_cable(H, vector<bool>(W));
	for(pair<int,int> p : cables) {
		is_cable[p.first][p.second] = true;
	}
	for(int rep = 0; rep < 25; ++rep) {
		for(pair<int,int>& p : routers) {
			vector<int> order{0,1,2,3};
			random_shuffle(order.begin(), order.end());
			for(int dir : order) {
				int row = p.first + dx[dir];
				int col = p.second + dy[dir];
				if(inside(row, col) && (is_cable[row][col] || cost + cable_cost <= B) && grid[row][col] == '.') {
					int memo_covered = count_covered;
					add_router(p.first, p.second, REMOVAL);
					add_router(row, col, TRIAL);
					if(count_covered > memo_covered) {
						if(!is_cable[row][col]) {
							add_cable(row, col);
							is_cable[row][col] = true;
						}
						p = {row, col};
						break;
					}
					add_router(row, col, REMOVAL);
					add_router(p.first, p.second, TRIAL);
				}
			}
		}
	}
	
	printf("%d\n", (int) cables.size());
	for(pair<int,int> cell : cables) {
		printf("%d %d\n", cell.first, cell.second);
	}
	printf("%d\n", (int) routers.size());
	for(pair<int,int> cell : routers) {
		printf("%d %d\n", cell.first, cell.second);
	}
	
	cerr << "budget: " << cost << " / " << B << endl;
	int count_dots = 0;
	for(int row = 0; row < H; ++row) {
		for(int col = 0; col < W; ++col) {
			if(grid[row][col] == '.') {
				++count_dots;
			}
		}
	}
	cerr << "coverage: " << count_covered << " / " << count_dots << endl;
	int score = 1000LL * count_covered + (B - cost);
	cerr << "score = " << score << endl;
}





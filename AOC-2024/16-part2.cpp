#include <bits/stdc++.h>
using namespace std;
char a[505][505];

const int MAGIC = 150*150;

vector<pair<int,int>> dirs = {{0,1},{-1,0},{0,-1},{1,0}};

struct State {
	int row, col, dir;
	bool operator <(const State& he) const {
		return make_pair(row, make_pair(col, dir)) < make_pair(he.row, make_pair(he.col, he.dir));
	}
};

int get(int row, int col) {
	return row * 150 + col;
}

int main() {
	// 'S' and 'E'
	int H, W;
	pair<int,int> start, target;
	for (int row = 0; scanf("%s", a[row]) != EOF; row++) {
		H = row + 1;
		W = strlen(a[row]);
		for (int col = 0; col < W; col++) {
			if (a[row][col] == 'S') {
				a[row][col] = '.';
				start = {row, col};
			}
			if (a[row][col] == 'E') {
				a[row][col] = '.';
				target = {row, col};
			}
		}
	}
	// Dijkstra
	set<pair<int, State>> s;
	map<State, pair<int,bitset<MAGIC>>> dist;
	State starting_state{start.first, start.second, 0};
	bitset<MAGIC> tmp;
	tmp[get(start.first,start.second)] = 1;
	dist[starting_state] = make_pair(0,tmp);
	s.insert(make_pair(0, starting_state));
	while (!s.empty()) {
		State state = s.begin()->second;
		s.erase(s.begin());
		// printf("%d %d %d %d\n", state.row, state.col, state.dir, maybe);
		for (int i = 0; i < 3; i++) {
			int maybe = dist[state].first;
			bitset<MAGIC> b = dist[state].second;
			State s2 = state;
			if (i == 0) {
				s2.row += dirs[s2.dir].first;
				s2.col += dirs[s2.dir].second;
				if (a[s2.row][s2.col] == '#') {
					continue;
				}
				if (!(0 <= s2.row && s2.row < H && 0 <= s2.col && s2.col < W)) {
					assert(false);
				}
				b[get(s2.row,s2.col)] = 1;
				maybe++;
			}
			else if (i == 1) {
				s2.dir = (s2.dir + 1) % 4;
				maybe += 1000;
			}
			else {
				s2.dir = (s2.dir + 3) % 4;
				maybe += 1000;
			}
			if (!dist.count(s2) || dist[s2].first > maybe) {
				if (dist.count(s2)) {
					s.erase(make_pair(dist[s2].first, s2));
				}
				dist[s2] = make_pair(maybe,b);
				s.insert(make_pair(maybe, s2));
			}
			else if (dist[s2].first == maybe) {
				dist[s2].second |= b; // error?
			}
		}
	}
	int ans = INT_MAX;
	bitset<MAGIC> b;
	for (int i = 0; i < 4; i++) {
		State t{target.first, target.second, i};
		if (dist.count(t)) {
			if (dist[t].first < ans) {
				ans = dist[t].first;
				b = dist[t].second;
			}
			else if (dist[t].first == ans) {
				b |= dist[t].second;
			}
			// ans = min(ans, dist[t]);
		}
	}
	printf("%d\n", (int) b.count());
}


// alternative linear solution:
// for every state, store best possible last move leading you here
		// it should be a vector of possible last state
		
		
// (5,8,0) <- (5,7,0), (5,8,3)

// (50,60,0/1/2/3) -> (H,W,0)

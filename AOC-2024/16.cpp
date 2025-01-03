#include <bits/stdc++.h>
using namespace std;
char a[505][505];

vector<pair<int,int>> dirs = {{0,1},{-1,0},{0,-1},{1,0}};

struct State {
	int row, col, dir;
	bool operator <(const State& he) const {
		return make_pair(row, make_pair(col, dir)) < make_pair(he.row, make_pair(he.col, he.dir));
	}
};

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
	map<State, int> dist;
	State starting_state{start.first, start.second, 0};
	dist[starting_state] = 0;
	s.insert(make_pair(0, starting_state));
	while (!s.empty()) {
		State state = s.begin()->second;
		s.erase(s.begin());
		// printf("%d %d %d %d\n", state.row, state.col, state.dir, maybe);
		for (int i = 0; i < 3; i++) {
			int maybe = dist[state];
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
			if (!dist.count(s2) || dist[s2] > maybe) {
				if (dist.count(s2)) {
					s.erase(make_pair(dist[s2], s2));
				}
				dist[s2] = maybe;
				s.insert(make_pair(maybe, s2));
			}
		}
	}
	int ans = INT_MAX;
	for (int i = 0; i < 4; i++) {
		State t{target.first, target.second, i};
		if (dist.count(t)) {
			ans = min(ans, dist[t]);
		}
	}
	printf("%d\n", ans);
}

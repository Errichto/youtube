#include <bits/stdc++.h>
using namespace std;

char a[105][105];
int id[105][105], tmp[105][105];

// <<^^<>>^v^<v^vv<>v
pair<int,int> getDir(char c) {
	if (c == '^') return {-1, 0};
	if (c == 'v') return {1, 0};
	if (c == '>') return {0, 1};
	if (c == '<') return {0, -1};
	assert(false);
}

int main() {
	int H, W;
	string moves;
	for (int row = 0; true; row++) {
		scanf("%s", a[row]);
		W = strlen(a[row]);
		if (W == 0 || W == 1 || (row >= 1 && W != (int) strlen(a[row-1]))) {
			H = row;
			W = strlen(a[row-1]);
			moves += string(a[row]);
			while (scanf("%s", a[row]) != EOF) {
				moves += string(a[row]);
			}
			break;
		}
	}
	// printf("%d %d\n", H, W);
	// printf("%d\n", (int) moves.length());
	pair<int,int> me{-1,-1}; // row, column
	int next_id = 1;
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			if (a[row][col] == '@') {
				me = {row, col};
				a[row][col] = '.';
			}
		}
		for (int col = 2 * W - 1; col >= 0; col--) {
			a[row][col] = a[row][col/2];
			if (a[row][col/2] == 'O') {
				id[row][col] = next_id;
				if (col % 2 == 0) {
					next_id++;
				}
			}
		}
	}
	W *= 2;
	// for (int row = 0; row < H; row++) {
		// for (int col = 0; col < W; col++) {
			// printf("%d ", id[row][col]);
		// }
		// puts("");
	// }
	// return 0;
	
	// me.first *= 2;
	me.second *= 2;
	assert(me.first != -1);
	for (char move : moves) {
		pair<int,int> dir = getDir(move);
		vector<pair<int,int>> boxes; // BFS queue
		set<int> vis;
		boxes.push_back(me);
		bool anyBlocked = false;
		for (int i = 0; i < (int) boxes.size(); i++) {
			int row = boxes[i].first + dir.first;
			int col = boxes[i].second + dir.second;
			if (a[row][col] == '#') {
				anyBlocked = true;
				break;
			}
			if (a[row][col] == 'O') {
				if (!vis.count(id[row][col])) {
					vis.insert(id[row][col]);
					boxes.emplace_back(row, col);
					for (int c : {col - 1, col + 1}) {
						if (id[row][col] == id[row][c]) {
							boxes.emplace_back(row, c);
						}
					}
				}
			}
		}
		if (anyBlocked) {
			continue;
		}
		me.first += dir.first;
		me.second += dir.second;
		boxes.erase(boxes.begin());
		for (pair<int,int> p : boxes) {
			a[p.first][p.second] = '.';
			tmp[p.first][p.second] = id[p.first][p.second];
			id[p.first][p.second] = 0;
		}
		for (pair<int,int> p : boxes) {
			id[p.first+dir.first][p.second+dir.second] = tmp[p.first][p.second];
			a[p.first+dir.first][p.second+dir.second] = 'O';
		}
	}
	int answer = 0;
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			if (a[row][col] == 'O' && id[row][col] != id[row][col-1]) {
				answer += 100 * row + col;
			}
		}
	}
	printf("%d\n", answer);
}

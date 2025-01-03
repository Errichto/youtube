#include <bits/stdc++.h>
using namespace std;

char a[105][105];

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
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			if (a[row][col] == '@') {
				me = {row, col};
				a[row][col] = '.';
			}
		}
	}
	assert(me.first != -1);
	for (char move : moves) {
		pair<int,int> dir = getDir(move);
		vector<pair<int,int>> boxes;
		int row = me.first;
		int col = me.second;
		bool emptySpace = false;
		while (true) {
			row += dir.first;
			col += dir.second;
			if (a[row][col] == '#') {
				break;
			}
			if (a[row][col] == '.') {
				emptySpace = true;
				break;
			}
			assert(a[row][col] == 'O');
			boxes.emplace_back(row, col);
		}
		if (!emptySpace) {
			continue;
		}
		me.first += dir.first;
		me.second += dir.second;
		for (pair<int,int> p : boxes) {
			a[p.first][p.second] = '.';
		}
		for (pair<int,int> p : boxes) {
			a[p.first+dir.first][p.second+dir.second] = 'O';
		}
	}
	int answer = 0;
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			if (a[row][col] == 'O') {
				answer += 100 * row + col;
			}
		}
	}
	printf("%d\n", answer);
}

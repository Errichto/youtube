#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};

int main() {
	int H = 130;
	vector<string> a(H);
	for (int i = 0; i < H; i++) {
		cin >> a[i];
	}
	int W = a[0].length();
	
	pair<int,int> me{-1, -1};
	int dir = 0;
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			if (a[row][col] == '^') {
				me = {row, col};
				a[row][col] = '.';
			}
		}
	}
	set<pair<int,int>> vis;
	while (true) {
		vis.insert(me);
		int r2 = me.first + dirs[dir].first;
		int c2 = me.second + dirs[dir].second;
		if (!(0 <= r2 && r2 < H && 0 <= c2 && c2 < W)) {
			break; // outside
		}
		if (a[r2][c2] == '.') {
			me = {r2, c2};
		}
		else {
			dir = (dir + 1) % 4;
		}
	}
	cout << vis.size() << "\n";
}


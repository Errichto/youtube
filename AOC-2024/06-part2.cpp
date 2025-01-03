#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};

// O((H*W)^2)

int main() {
	int H = 130;
	vector<string> a(H);
	for (int i = 0; i < H; i++) {
		cin >> a[i];
	}
	int W = a[0].length();
	
	pair<int,int> start_me{-1, -1};
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			if (a[row][col] == '^') {
				start_me = {row, col};
				a[row][col] = '.';
			}
		}
	}
	
	auto solveCycle = [&]() {
		pair<int,int> me = start_me;
		int dir = 0;
		
		vector<bool> vis(H * W * 4);
		// int turns = 0;
		while (true) {
			// turns++;
			// if (turns == H * W * 4) {
				// return true;
			// }
			int hash = (me.first * W + me.second) * 4 + dir;
			if (vis[hash]) {
				return true;
			}
			vis[hash] = true;
			int r2 = me.first + dirs[dir].first;
			int c2 = me.second + dirs[dir].second;
			if (!(0 <= r2 && r2 < H && 0 <= c2 && c2 < W)) {
				return false; // outside
			}
			if (a[r2][c2] == '.') {
				me = {r2, c2};
			}
			else {
				dir = (dir + 1) % 4;
			}
		}
	};
	
	int answer = 0;
	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			if (a[row][col] == '.' && start_me != make_pair(row, col)) {
				// cout << row << " " << col << endl;
				a[row][col] = '#';
				if (solveCycle()) {
					// cout << row << " " << col << endl;
					answer++;
				}
				a[row][col] = '.';
			}
		}
	}
	cout << answer << "\n";
}


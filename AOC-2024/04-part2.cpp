#include <bits/stdc++.h>
using namespace std;

const vector<pair<int,int>> dirs = {{-1,-1},{-1,1},{1,1},{1,-1}}; // order important

int main() {
	int H = 140;
	vector<string> a(H);
	for (string& row : a) {
		cin >> row;
	}
	int W = (int) a[0].length();
	
	int answer = 0;
	for (int row = 1; row < H - 1; row++) {
		for (int col = 1; col < W - 1; col++) {
			if (a[row][col] == 'A') {
				string s;
				for (pair<int,int> dir : dirs) {
					s += a[row+dir.first][col+dir.second];
				}
				if (s == "MMSS" || s == "MSSM" || s == "SSMM" || s == "SMMS") {
					answer++;
				}
			}
		}
	}
	cout << answer << "\n";
}

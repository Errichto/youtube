#include <bits/stdc++.h>
using namespace std;

void rotate(vector<string>& a) {
	int n = a.size();
	vector<string> b(n, string(n, '?'));
	for(int row = 0; row < n; ++row) {
		for(int col = 0; col < n; ++col) {
			b[row][col] = a[col][n-1-row];
		}
	}
	a = b;
}
void flip(vector<string>& a) {
	int n = a.size();
	for(int row = 0; row < n; ++row) {
		for(int col = 0; col < n / 2; ++col) {
			swap(a[row][col], a[row][n-1-col]);
		}
	}
}
const string monster[3] = {
	"                  # ",
	"#    ##    ##    ###",
	" #  #  #  #  #  #   "
};
void find_monsters(vector<string> sea) {
	const int h = 3;
	const int w = monster[0].length();
	const int n = sea.size();
	// for(int ro = 0; ro < 4; ++ro) {
		// rotate(sea);
		// for(int f = 0; f < 2; ++f) {
			// flip(sea);
			for(int row = 0; row + h - 1 < n; ++row) {
				for(int col = 0; col + w - 1 < n; ++col) {
					// consider a monster with top-left corner at (row, col)
					bool can_be = true;
					for(int r = 0; r < h; ++r) {
						for(int c = 0; c < w; ++c) {
							if(monster[r][c] == '#' && sea[row+r][col+c] == '.') {
								can_be = false;
							}
						}
					}
					if(!can_be) {
						continue;
					}
					for(int r = 0; r < h; ++r) {
						for(int c = 0; c < w; ++c) {
							if(monster[r][c] == '#') {
								sea[row+r][col+c] = 'O';
							}
						}
					}
				}
			}
			int roughness = 0;
			for(string s : sea) {
				// cout << s << endl;
				for(char& c : s) {
					if(c == '#') {
						roughness++;
					}
					cout << (c == 'O' ? 'O' : ',');
				}
				cout << endl;
			}
			cout << endl;
			cout << "roughness = " << roughness << endl;
		// }
	// }
}

const int S = 10; // TILE SIZE

struct Tile {
	int id;
	vector<string> cells; // cells[S][S]
	
	bool read() { // returns false if End Of File
		if(scanf(" Tile %d:", &id) == EOF) {
			return false;
		}
		for(int row = 0; row < S; ++row) {
			static char tmp[105];
			scanf("%s", tmp);
			cells.push_back(string(tmp));
		}
		return true;
	}
	bool can_below(const Tile& b) const {
		return cells[S-1] == b.cells[0];
	}
	bool can_right(const Tile& b) const {
		for(int row = 0; row < S; ++row) {
			if(cells[row][S-1] != b.cells[row][0]) {
				return false;
			}
		}
		return true;
	}
};

vector<Tile> tiles; // all 8*N available tiles
Tile grid[20][20];
int GRID_SIZE = -1;

void remove_frames() {
	vector<string> sea;
	for(int row = 0; row < GRID_SIZE * S; ++row) {
		if(row % S == 0 || row % S == S - 1) {
			continue;
		}
		string new_row;
		for(int col = 0; col < GRID_SIZE * S; ++col) {
			if(col % S == 0 || col % S == S - 1) {
				continue;
			}
			char cell = grid[row/S][col/S].cells[row%S][col%S];
			new_row += cell;
		}
		sea.push_back(new_row);
	}
	find_monsters(sea);
}

void search(int row, int col, set<int>& visited) {
	if(row == GRID_SIZE) {
		remove_frames();
		printf("product = %lld\n", (long long) grid[0][0].id * grid[GRID_SIZE-1][0].id
				* grid[0][GRID_SIZE-1].id * grid[GRID_SIZE-1][GRID_SIZE-1].id);
		exit(0);
		return;
	}
	for(const Tile& tile : tiles) {
		if(!visited.count(tile.id)) {
			// check if this new tile matches adjacent tiles above and on the left
			if(row > 0 && !grid[row-1][col].can_below(tile)) {
				continue;
			}
			if(col > 0 && !grid[row][col-1].can_right(tile)) {
				continue;
			}
			grid[row][col] = tile;
			visited.insert(tile.id);
			if(col == GRID_SIZE - 1) {
				search(row + 1, 0, visited);
			}
			else {
				search(row, col + 1, visited);
			}
			visited.erase(tile.id);
		}
	}
}

int main() {
	while(true) { // read until EOF
		Tile tile;
		if(!tile.read()) { // EOF
			break;
		}
		for(int f = 0; f < 2; ++f) {
			for(int r = 0; r < 4; ++r) {
				tiles.push_back(tile);
				rotate(tile.cells);
			}
			flip(tile.cells);
		}
	}
	GRID_SIZE = llround(sqrt(tiles.size() / 8));
	set<int> visited;
	search(0, 0, visited);
}

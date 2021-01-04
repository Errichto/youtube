#include <bits/stdc++.h>
#include <unistd.h>
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

const int S = 10; // TILE SIZE

struct Tile {
	int id;
	vector<string> cells; // cells[S][S]
	
	// returns false if End Of File
	bool read() {
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

void print(pair<int,int> last_cell) {
	printf("\033[2J\033[1;1H"); // reset terminal
	puts("");
	for(int row = 0; row <= (last_cell.first + 1) * S; ++row) {
		// if(row % S == 0 || row % S == S - 1) {
			// continue;
		// }
		printf(" ");
		for(int col = 0; col < GRID_SIZE * S; ++col) {
			if(make_pair(row / S, col / S) > last_cell) {
				continue;
			}
			char cell = grid[row/S][col/S].cells[row%S][col%S];
			// if(min(row % S, col % S) == 0 || max(row % S, col % S) == S - 1) {
				printf("\033[1;%dm", 31 + (row / S + col / S) % 7); // start color
				printf("%c", cell);
				printf("\033[0m"); // end color
			// }
			// else {
				// printf(" ");
			// }
		}
		puts("");
	}
	puts("");
	fflush(stdout);
	if(GRID_SIZE == 3) {
		usleep(200123); // sample test
	}
	else {
		usleep(12123 * min(2, last_cell.first + 1));
	}
	// printf("product = %lld\n", (long long) grid[0][0].id * grid[GRID_SIZE-1][0].id
			// * grid[0][GRID_SIZE-1].id * grid[GRID_SIZE-1][GRID_SIZE-1].id);
}

void rec(int row, int col, set<int>& visited) {
	static int operations = 0;
	++operations;
	if(row == GRID_SIZE) {
		printf("%d recursive calls\n", operations);
		exit(0);
		return;
	}
	for(const Tile& tile : tiles) {
		if(!visited.count(tile.id)) {
			if(row > 0 && !grid[row-1][col].can_below(tile)) {
				continue;
			}
			if(col > 0 && !grid[row][col-1].can_right(tile)) {
				continue;
			}
			grid[row][col] = tile;
			print(make_pair(row, col));
			visited.insert(tile.id);
			if(col == GRID_SIZE - 1) {
				rec(row + 1, 0, visited);
			}
			else {
				rec(row, col + 1, visited);
			}
			visited.erase(tile.id);
		}
	}
}

int main() {
	while(true) {
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
	rec(0, 0, visited);
}

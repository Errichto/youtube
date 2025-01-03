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
// debug & operator << (debug & dd, P p) { dd << "(" << p.x << ", " << p.y << ")"; return dd; }


vector<vector<int>> numpad = {
	{7,8,9},
	{4,5,6},
	{1,2,3},
	{-1,0,10} // 10=A
};
char getChar(int value) {
	if (0 <= value && value < 10) {
		return '0' + value;
	}
	if (value == 10) {
		return 'A';
	}
	return false;
}
const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3, HIT = 4;
pair<int,int> dirs[4] = {{-1,0}, {0,-1}, {1,0}, {0,1}};
vector<vector<int>> keypad = {
	{-1, UP, HIT},
	{LEFT, DOWN, RIGHT}
};

pair<int,int> f(pair<int,int> me, int dir) {
	assert(0 <= dir && dir < 4);
	return {me.first + dirs[dir].first, me.second + dirs[dir].second};
}

const int INF = 1e9 + 5;
int dist[5][5][5][11];
bool vis[5][5][5][11];

const char MOVEMENT = '$';
const char ERROR = '@';

char makeMove(int mv, int& x, vector<vector<int>> pad) {
	assert(0 <= mv && mv < 4);
	int H = pad.size();
	int W = pad[0].size();
	for (int r = 0; r < H; r++) {
		for (int c = 0; c < W; c++) {
			if (pad[r][c] == x) {
				r += dirs[mv].first;
				c += dirs[mv].second;
				if (0 <= r && r < H && 0 <= c && c < W && pad[r][c] != -1) {
					x = pad[r][c];
					return MOVEMENT;
				}
				else {
					return ERROR;
				}
			}
		}
	}
	assert(false);
}

// returns char printed OR info_nothing_printed OR error
char apply(int mv, int i, vector<int>& v) {
	assert((int) v.size() == 3);
	assert(0 <= i && i < 3);
	if (mv == HIT) {
		if (i == 2) {
			return getChar(v[2]);
		}
		return apply(v[i], i+1, v);
	}
	// movement
	return makeMove(mv, v[i], (i == 2 ? numpad : keypad));
}

int solve(string s) {
	
	memset(vis, 0, sizeof(vis));
	memset(dist, 0, sizeof(vis));

	
	debug() << imie(s);
	// state: (chars_printed, r1, r2, r3)
	dist[0][HIT][HIT][10] = 0;
	vis[0][HIT][HIT][10] = true;
	vector<vector<int>> q;
	q.push_back({0, HIT, HIT, 10});
	
	// vector<int> vv{HIT,HIT,10};
	// debug() << apply(HIT, 0, vv);
	// return 0;
	
	for (int z = 0; z < (int) q.size(); z++) {
		debug() << imie(q[z]);
		int chars = q[z][0], r1 = q[z][1], r2 = q[z][2], r3 = q[z][3];
		if (chars == (int) s.length()) {
			return dist[chars][r1][r2][r3];
		}
		for (int mv = 0; mv < 5; mv++) {
			vector<int> v = q[z];
			v.erase(v.begin());
			// v stores 3 robots
			char pr = apply(mv, 0, v);
			if (pr == ERROR) {
				continue;
			}
			if (pr != MOVEMENT) {
				if (pr != s[chars]) {
					continue;
				}
			}
			int s1 = chars + (pr != MOVEMENT);
			int s2 = v[0];
			int s3 = v[1];
			int s4 = v[2];
			if (!vis[s1][s2][s3][s4]) {
				vis[s1][s2][s3][s4] = true;
				dist[s1][s2][s3][s4] = dist[chars][r1][r2][r3] + 1;
				q.push_back({s1,s2,s3,s4});
			}
		}
	}
	assert(false);
}

int main() {
	
	int answer = 0;
	for (int rep = 0; rep < 5; rep++) {
		string s;
		cin >> s;
		// s = "319A";
		int x = solve(s);
		cout << x << "\n";
		s.pop_back();
		answer += x * stoi(s);
	}
	cout << answer << "\n";
}

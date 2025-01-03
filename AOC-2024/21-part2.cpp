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

#define int long long

vector<vector<int>> numpad = {
	{7,8,9},
	{4,5,6},
	{1,2,3},
	{-1,0,10} // 10=A
};
int getInt(char c) {
	if (isdigit(c)) return c - '0';
	if (c == 'A') return 10;
	assert(false);
}
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

const int INF = 1e18 + 5;
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


const int M = 25; // number of robots using keypads

int dp[M+2][11][11];
void preprocess() {
	// dp[robot_id][from][to] -- assuming that previous robots are set to 'A', min number of moves to move this robot 'from' -> 'to'
	// dp[0][...] = 0
	for (int id = 1; id <= M + 1; id++) {
		const int X = (id == M + 1 ? 11 : 5);
		for (int from = 0; from < X; from++) {
			// small[prv][me]
			vector<vector<int>> small(5, vector<int>(11, INF));
			small[HIT][from] = 0;
			set<pair<int, pair<int,int>>> pq;
			pq.insert({0, {HIT,from}});
			
			auto consider = [&](int prv, int me, int maybe) {
				debug() << imie(prv) imie(me) imie(maybe);
				if (maybe < small[prv][me]) {
					pq.erase({small[prv][me], {prv,me}});
					small[prv][me] = maybe;
					pq.insert({maybe, {prv,me}});
				}
			};
			
			while (!pq.empty()) {
				int my_dist = pq.begin()->first;
				int prv = pq.begin()->second.first;
				int me = pq.begin()->second.second;
				pq.erase(pq.begin());
				for (int prv2 = 0; prv2 < 5; prv2++) {
					int maybe = my_dist + dp[id-1][prv][prv2];
					consider(prv2, me, maybe);
				}
				if (prv != HIT) {
					// char makeMove(int mv, int& x, vector<vector<int>> pad) {
					if (MOVEMENT == makeMove(prv, me, (id == M + 1 ? numpad : keypad))) {
						consider(prv, me, my_dist + 1);
					}
				}
			}
			for (int to = 0; to < (id == M + 1 ? 11 : 5); to++) {
				dp[id][from][to] = small[HIT][to];
				debug() << imie(id) imie(from) imie(to) imie(dp[id][from][to]);
			}
			// exit(0);
		}
		debug() << imie(id) imie(dp[id][0][1]);
	}
	// cout << dp[3][7][10] << "\n";
}

// Given an array of numbers, count ways to split it into subarrays so that every subarray (of length K) would be a permutation of numbers 1 through K.
// Modulo 1e9+7.            O(N)


int solve(string s) {
	char prv = 'A';
	int total = 0;
	for (char c : s) {
		total += dp[M+1][getInt(prv)][getInt(c)] + 1;
		prv = c;
	}
	return total;
}

int32_t main() {
	preprocess();
	int answer = 0;
	for (int rep = 0; rep < 5; rep++) {
		string s;
		cin >> s;
		int x = solve(s);
		cout << x << "\n";
		s.pop_back();
		answer += x * stoi(s);
	}
	cout << answer << "\n";
}

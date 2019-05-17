#include "bits/stdc++.h"
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

using ll = long long;

const int MAX_N = 3e5 + 5;
vector<pair<int,int>> edges[MAX_N]; // (b, cost)
bool visited[MAX_N];
int degree[MAX_N];
const int INF = 1e9 + 5;

pair<int,int> other(int a) {
	for(pair<int,int> edge : edges[a]) {
		if(!visited[edge.first]) {
			return edge;
		}
	}
	return make_pair(-1, -1);
}

void make_pref(vector<int>& vec) {
	int n = vec.size();
	vector<int> pref(n + 1);
	for(int i = 1; i <= n; ++i) {
		pref[i] = pref[i-1] + vec[i-1];
	}
	vec = pref;
}

int main() {
	int n, e, teleport;
	scanf("%d%d%d", &n, &e, &teleport);
	for(int i = 0; i < e; ++i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		degree[a]++;
		degree[b]++;
		edges[a].emplace_back(b, c);
		edges[b].emplace_back(a, c);
	}
	vector<vector<vector<int>>> blocks;
	int cur = 1;
	while(cur != n) {
		vector<int> path;
		if(blocks.empty()) {
			path.push_back(0);
		}
		visited[cur] = true;
		do {
			pair<int,int> edge = other(cur);
			cur = edge.first;
			path.push_back(edge.second);
			visited[cur] = true;
			//~ path.push_back(cur);
		} while(degree[cur] == 2);
		blocks.push_back({path, path});
		debug() << "push backing " imie(path);
		if(cur != n) {
			assert(degree[cur] == 3);
			int starting = cur;
			vector<vector<int>> block;
			int last_vertex = -1;
			for(int rep = 0; rep < 2; ++rep) {
				cur = starting;
				vector<int> tmp_path;
				do {
					pair<int,int> edge = other(cur);
					if(edge.first == -1) {
						break;
					}
					cur = edge.first;
					tmp_path.push_back(edge.second);
					visited[cur] = true;
				} while(degree[cur] == 2);
				block.push_back(tmp_path);
				if(rep == 0) {
					last_vertex = cur;
				}
			}
			assert(last_vertex != -1);
			visited[last_vertex] = false;
			pair<int,int> edge = other(cur);
			cur = edge.first;
			block[1].push_back(edge.second);
			visited[cur] = true;
			debug() << "push backing " imie(block);
			blocks.push_back(block);
		}
	}
	for(vector<vector<int>> something : blocks) {
		debug() << imie(something);
	}
	vector<vector<vector<int>>> prefs = blocks;
	for(vector<vector<int>>& tmp : prefs) {
		for(vector<int>& vec : tmp) {
			make_pref(vec);
		}
	}
	debug() << "prefs:";
	for(vector<vector<int>> sth_pref : prefs) {
		debug() << sth_pref;
	}
	vector<vector<vector<int>>> dp = blocks;
	vector<int> total_pref{0};
	for(vector<vector<int>> block : prefs) {
		int block_size = min(block[0].back(), block[1].back());
		total_pref.push_back(total_pref.back() + block_size);
	}
	debug() << imie(total_pref);
	int answer = INF;
	for(int i = 0; i < (int) dp.size(); ++i) {
		assert((int) dp[i].size() == 2);
		for(int j = 0; j < (int) dp[i].size(); ++j) {
			for(int k = 0; k < (int) dp[i][j].size(); ++k) {
				int& update = dp[i][j][k];
				if(i == 0 && k == 0) {
					update = 0;
					continue;
				}
				update = INF;
				//~ #warning maybe we do not jump at all?
				if(k != 0) {
					update = dp[i][j][k-1] + 2 * blocks[i][j][k];
				}
				else {
					assert(i != 0);
					for(int j2 : {0, 1}) {
						update = min(update, dp[i-1][j2].back() + 2 * blocks[i][j][k]);
					}
				}
				int best = update;
				// binary search the block from which we can jump here
				int low_block = 0, high_block = i;
				while(low_block < high_block) {
					int block = (low_block + high_block) / 2;
					int distance = total_pref[i] - total_pref[block+1] + prefs[i][j][k+1];
					if(i == 3 && j == 0 && k == 0) {
						debug() << imie(block) imie(distance);
					}
					if(distance > teleport) {
						low_block = block + 1;
					}
					else {
						high_block = block;
					}
				}
				int block = low_block;
				//~ debug() << imie(i) imie(j) imie(k) imie(block);
				if(block == i) {
					int low = 0, high = k;
					while(low < high) {
						int v = (low + high) / 2;
						int distance = prefs[i][j][k+1] - prefs[i][j][v+1];
						if(distance > teleport) {
							low = v + 1;
						}
						else {
							high = v;
						}
					}
					int from = low;
					debug() << imie(i) imie(j) imie(k) imie(from);
					if(from != k) {
						//~ if(i == 0 && j == 0 && k == 4) {
							//~ debug() << imie(dp[i][j][from]) imie(prefs[i][j][k
						best = min(best, dp[i][j][from] + prefs[i][j][k+1] - prefs[i][j][from+1]);
					}
				}
				else {
					for(int j2 : {0, 1}) {
						int low = 0, high = (int) blocks[block][j2].size() - 1;
						// binary search from which vertex from that path we can jump
						while(low < high) {
							int v = (low + high) / 2;
							int distance = total_pref[i] - total_pref[block+1]
								+ prefs[i][j][k+1] + prefs[block][j2].back() - prefs[block][j2][v+1];
							if(distance > teleport) {
								low = v + 1;
							}
							else {
								high = v;
							}
						}
						int v = low;
						int maybe = dp[block][j2][v] + total_pref[i] - total_pref[block+1]
								+ prefs[i][j][k+1] + prefs[block][j2].back() - prefs[block][j2][v+1];
						if(maybe < best) {
							best = maybe;
							debug() << imie(i) imie(j) imie(k) imie(block) imie(j2) imie(v) imie(best);
						}
					}
				}
				//~ debug() << imie(i) imie(j) imie(k) imie(best) imie(update);
				int maybe = best + 2 * (total_pref.back() - total_pref[i+1] + prefs[i][j].back() - prefs[i][j][k+1]);
				if(answer > maybe) {
					answer = maybe;
					debug() << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " imie(i) imie(j) imie(k) imie(answer);
				}
			}
		}
	}
	printf("%d\n", answer);
}

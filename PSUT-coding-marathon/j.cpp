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

const int MAX_N = 2e5 + 5;
vector<int> edges[MAX_N];
bool visited[MAX_N];
int degree[MAX_N];
int append[MAX_N];

//~ int other(int a, int b) {
	//~ for(int x : edges[a]) {
		//~ if(x != b) {
			//~ return x;
		//~ }
	//~ }
	//~ return -1;
//~ }
int other(int a) {
	for(int x : edges[a]) {
		if(!visited[x]) {
			return x;
		}
	}
	return -1;
}

int is_special(int a) {
	int cnt = 0;
	int leaf = -1;
	for(int b : edges[a]) {
		if(!visited[b]) {
			++cnt;
			if(degree[b] == 1) {
				leaf = b;
			}
		}
	}
	assert(cnt <= 2);
	if(cnt == 2 && leaf != -1) {
		return leaf;
	}
	return -1;
}

bool is_in_block(int a) {
	//~ if(degree[a] == 1) {
		//~ return false;
	//~ }
	//~ int cnt = 0;
	//~ for(int b : edges[a]) {
		//~ if(degree[b] >= 2) {
			//~ ++cnt;
		//~ }
	//~ }
	//~ if(cnt < 2) {
		//~ return false;
	//~ }
	for(int b : edges[a]) {
		for(int c : edges[a]) {
			if(b < c) {
				for(int d : edges[b]) {
					for(int e : edges[c]) {
						if(d == e && d != a) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
	// ##.##.
	// #####.
}

int answer[2][MAX_N];

int row, col;

void put_path(vector<int> path, bool is_last_thing_ever) {
	if(answer[row][col] != path[0]) {
		row ^= 1;
	}
	assert(answer[row][col] == path[0]);
	for(int i = 1; i < (int) path.size(); ++i) {
		int r2 = row ^ 1;
		bool must_append = false;
		for(int j = i - 1; j <= i + 1 && j < (int) path.size(); ++j) {
			if(append[path[j]] != -1) {
				must_append = true;
			}
		}
		if(must_append) {
			col++;
		}	
		else if(answer[r2][col] == 0 && (is_last_thing_ever || i < (int) path.size() - 2) &&  (col == 0 || answer[r2][col-1] == 0)) {
			row = r2;
		}
		else {
			col++;
		}
		answer[row][col] = path[i];
		if(append[path[i]] != -1) {
			answer[row^1][col] = append[path[i]];
		}
	}
}

void put_block(vector<int> block) {
	assert(block.back() == -1);
	block.pop_back();
	answer[row][col] = block[0];
	answer[row^1][col] = block[1];
	for(int i = 2; i < (int) block.size(); i += 2) {
		int C = block[i], D = block[i+1];
		bool flag = false;
		for(int x : edges[C]) {
			if(x == answer[0][col]) {
				flag = true;
			}
		}
		if(!flag) {
			swap(C, D);
		}
		col++;
		answer[0][col] = C;
		answer[1][col] = D;
	}
}

int main() {
	int L, n, e;
	scanf("%d%d%d", &L, &n, &e);
	for(int i = 0; i <= n; ++i) {
		append[i] = -1;
	}
	for(int i = 0; i < e; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for(int i = 1; i <= n; ++i) {
		degree[i] = edges[i].size();
	}
	
	if(n == 1) {
		for(int i = 0; i < 2; ++i) {
			for(int j = 0; j < L; ++j) {
				if(i == 0 && j == 0) {
					printf("1 ");
				}
				else {
					printf("0 ");
				}
			}
			puts("");
		}
		return 0;
	}
	
	//~ #warning n can be 1
	//~ #warning it is incorrect to start from any leaf
	//~ #warning maybe I will not find a leaf
	
	int leaf = -1;
	for(int i = 1; i <= n; ++i) {
		
		if(degree[i] == 1) {
			int that = edges[i][0];
			if(is_in_block(that) || degree[that] <= 2) {
				leaf = i;
				break;
			}
		}
	}
	vector<vector<int>> blocks;
	int cur = leaf;
	int starting_block = -1;
	if(leaf == -1) {
		for(int a = 1; a <= n; ++a) {
			if(degree[a] == 2 && is_in_block(a)) {
				int b = -1;
				for(int x : edges[a]) {
					if(is_in_block(x) && degree[x] == 2) {
						b = x;
					}
				}
				if(b != -1) {
					starting_block = a;
				}
			}
		}
		assert(starting_block != -1);
	}
	while(true) {
		if(cur != -1) {
			vector<int> path{cur};
			visited[cur] = true;
			
			while(cur == path[0] || degree[cur] == 2 || is_special(cur) != -1) {
				int nxt;
				
				int special = is_special(cur);
				if(special != -1) {
					visited[special] = true;
					append[cur] = special;
				}
				
				nxt = other(cur);
				path.push_back(nxt);
				//~ prv = cur;
				cur = nxt;
				visited[cur] = true;
			}
			blocks.push_back(path);
			debug() << "push_backing " imie(path);
			if(degree[cur] == 1) {
				break;
			}
		}
		else {
			cur = starting_block;
			visited[cur] = true;
		}
		debug() << "finding a block for " imie(cur);
		//~ assert(degree[cur] == 3);
		int A = cur;
		int B = -1;
		for(int x : edges[A]) {
			if(!visited[x] && degree[x] == 2) {
				B = x;
			}
		}
		if(B == -1) {
			debug() << imie(blocks) imie(A);
		}
		assert(B != -1);
		vector<int> ladder;
		ladder.push_back(A);
		ladder.push_back(B);
		visited[A] = visited[B] = true;
		do {
			int C = other(A);
			int D = other(B);
			assert(C != -1);
			assert(D != -1);
			A = C;
			B = D;
			visited[A] = visited[B] = true;
			ladder.push_back(A);
			ladder.push_back(B);
		} while(degree[A] >= 3 && degree[B] >= 3);
		ladder.push_back(-1); // denotes a ladder
		blocks.push_back(ladder);
		debug() << "push backing " imie(ladder);
		if(degree[A] == 2 && degree[B] == 2) {
			break;
		}
		cur = (degree[A] == 3 ? A : B);
		assert(degree[cur] == 3);
	}
	for(vector<int> block : blocks) {
		debug() << block;
	}
	answer[row][col] = blocks[0][0];
	for(int i = 0; i < (int) blocks.size(); ++i) {
		vector<int> something = blocks[i];
		if(something.back() == -1) {
			put_block(something);
		}
		else {
			put_path(something, i == (int) blocks.size() - 1);
		}
	}
	for(int r = 0; r < 2; ++r) {
		for(int c = 0; c < L; ++c) {
			printf("%d ", answer[r][c]);
		}
		puts("");
	}
}

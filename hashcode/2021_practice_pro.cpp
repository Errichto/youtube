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

map<string, int> mapping;

struct Pizza {
	int id;
	vector<int> ings;
	void read(int _id) {
		id = _id;
		int cnt;
		scanf("%d", &cnt);
		for(int i = 0; i < cnt; ++i) {
			static char arr[105];
			scanf("%s", arr);
			string s = string(arr);
			if(!mapping.count(s)) {
				int k = mapping.size();
				mapping[s] = k;
			}
			ings.push_back(mapping[s]);
		}
	}
};

vector<Pizza> pizzas;
int m;
vector<bool> used;

vector<int> find_good(int size) {
	static vector<bool> already(mapping.size());
	
	pair<int, vector<int>> best_delivery;
	best_delivery.first = -1;
	
	vector<int> ids;
	for(int id = 0; id < m; ++id) {
		if(!used[id]) {
			ids.push_back(id);
		}
	}
	for(int tries = 0; tries < 1; ++tries) {
		random_shuffle(ids.begin(), ids.end());
		vector<int> delivery;
		for(int x = 0; x < size; ++x) {
			pair<int,int> best{-1, -1};
			// int tested = 0;
			for(int id : ids) {
				if(!used[id]) {
					// if(++tested == 2000) {
						// break;
					// }
					int improvement = 0;
					for(int s : pizzas[id].ings) {
						if(!already[s]) {
							improvement++;
						}
					}
					int magic = 0;
					if(x == size - 1) {
						magic = 0;
					}
					else if(x == size - 2) {
						magic = 0;
					}
					else if(x == size - 3) {
						magic = 0;
					}
					else if(x == size - 4) {
						magic = 0;
					}
					if(best.first == -1 || improvement > best.first + magic) {
						best = {improvement, id};
					}
					// best = max(best, make_pair(improvement, id));
				}
			}
			assert(best.second != -1);
			int id = best.second;
			delivery.push_back(id);
			used[id] = true;
			for(int s : pizzas[id].ings) {
				already[s] = true;
			}
		}
		int count_ings = 0;
		for(int id : delivery) {
			used[id] = false;
			for(int s : pizzas[id].ings) {
				if(already[s]) {
					count_ings++;
					already[s] = false;
				}
			}
		}
		best_delivery = max(best_delivery, make_pair(count_ings, delivery));
	}
	assert(best_delivery.first != -1);
	for(int id : best_delivery.second) {
		used[id] = true;
	}
	return best_delivery.second;
}
int get_score(vector<int> delivery) {
	static vector<bool> already(mapping.size());
	int size = 0;
	for(int id : delivery) {
		for(int ing : pizzas[id].ings) {
			if(!already[ing]) {
				++size;
				already[ing] = true;
			}
		}
	}
	for(int id : delivery) {
		for(int ing : pizzas[id].ings) {
			already[ing] = false;
		}
	}
	return size * size;
}

int main() {
	int t[5];
	scanf("%d", &m);
	for(int s = 2; s <= 4; ++s) {
		scanf("%d", &t[s]);
	}
	pizzas.resize(m);
	for(int i = 0; i < m; ++i) {
		pizzas[i].read(i);
	}
	used.resize(m);
	int count_used = 0;
	vector<vector<int>> output;
	for(int size = 4; size >= 2; --size) {
		for(int rep = 0; rep < t[size]; ++rep) {
			if(count_used + size <= (int) pizzas.size()) {
				if(rand() % 10 == 0) {
					cerr << (double) count_used * 100 / pizzas.size() << "%   ";
				}
				count_used += size;
				// I have enough pizzas to serve this team
				vector<int> delivery = find_good(size);
				output.push_back(delivery);
			}
		}
	}
	
	for(int rep = 1; true; ++rep) {
		vector<int>& A = output[rand() % output.size()];
		vector<int>& B = output[rand() % output.size()];
		if(A == B) {
			continue;
		}
		int was = get_score(A) + get_score(B);
		int a = rand() % A.size();
		int b = rand() % B.size();
		swap(A[a], B[b]);
		int is = get_score(A) + get_score(B);
		if(was <= is) {
			// leave this change
			if(was < is) {
				cerr << was << " -> " << is << "  (+" << is - was << ")       rep=" << rep << "\n";
			}
		}
		else {
			swap(A[a], B[b]);
		}
		if(rep % 1'000'000 == 0) {
			int which = rep / 1'000'000;
			string file = "out/c" + to_string(which) + ".out";
			freopen(file.c_str(), "w", stdout);
			printf("%d\n", (int) output.size());
			long long score = 0;
			for(vector<int> delivery : output) {
				printf("%d", (int) delivery.size());
				set<int> set;
				for(int id : delivery) {
					for(int s : pizzas[id].ings) {
						set.insert(s);
					}
					printf(" %d", id);
				}
				puts("");
				score += (int) set.size() * set.size();
			}
			cerr << imie(score) << endl;
		}
	}
}

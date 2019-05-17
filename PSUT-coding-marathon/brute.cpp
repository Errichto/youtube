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

// 333467811233
// not ok: 3377

// 222222 333 555 888 1111 2222 3333
//             S             E

const int MAX_N = 3e5 + 5;
char a[MAX_N];

const int dx[9] = {-999, 0, 1, 1, 1, 0, -1, -1, -1};
const int dy[9] = {-999, 1, 1, 0, -1, -1, -1, 0, 1};

int main() {
	int n;
	scanf("%d", &n);
	scanf("%s", a);
	assert(n == (int) strlen(a));
	vector<pair<int,int>> intervals;
	for(int i = 0; i < n; ++i) {
		int cnt = 1;
		while(i + 1 < n && a[i] == a[i+1]) {
			++i;
			++cnt;
		}
		intervals.emplace_back(a[i] - '0', cnt);
	}
	debug() << imie(intervals);
	vector<int> should[2];
	for(int rep = 0; rep < 2; ++rep) {
		for(int i = 1; i <= 8; ++i) {
			should[0].push_back(i);
		}
		for(int i = 8; i >= 1; --i) {
			should[1].push_back(i);
		}
	}
	debug() << imie(should[0]);
	debug() << imie(should[1]);
	
	long long answer = 0;
	
	for(int S = 0; S < (int) intervals.size(); ++S) {
		for(int E = S + 2; E < min(S + 10, (int) intervals.size()); ++E) {
			vector<int> dirs;
			for(int i = S; i <= E; ++i) {
				dirs.push_back(intervals[i].first);
			}
			bool ok = false;
			for(int type : {0, 1}) {
				int pos = 0;
				while(should[type][pos] != dirs[0]) {
					++pos;
				}
				int starting_pos = pos;
				for(int dir : dirs) {
					while(should[type][pos] != dir) {
						++pos;
						if(pos == (int) should[type].size()) {
							break;
						}
					}
					if(pos == (int) should[type].size()) {
						break;
					}
				}
				if(pos <= starting_pos + 8) {
					ok = true;
				}
			}
			if(ok) {
				debug() << imie(dirs);
				int x = 0, y = 0;
				for(int i = S + 1; i <= E - 1; ++i) {
					x += dx[intervals[i].first] * intervals[i].second;
					y += dy[intervals[i].first] * intervals[i].second;
				}
				int dir1 = intervals[S].first;
				int dir2 = intervals[E].first;
				int cnt1 = intervals[S].second;
				int cnt2 = intervals[E].second;
				for(int first = 1; first <= cnt1; ++first) {
					for(int sec = 1; sec <= cnt2; ++sec) {
						if(x + dx[dir1] * first + dx[dir2] * sec == 0
						&& y + dy[dir1] * first + dy[dir2] * sec == 0) {
							++answer;
						}
					}
				}
			}
		}
	}
	printf("%lld\n", answer);
}






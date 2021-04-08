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

char query(int pos) {
	printf("%d\n", pos);
	fflush(stdout);
	char c;
	scanf(" %c", &c);
	return c;
}

void test_case() {
	vector<vector<int>> groups;
	for(int i = 1; i <= 591; i += 5) {
		vector<int> group;
		for(int j = 0; j < 5; j++) {
			group.push_back(i + j);
		}
		groups.push_back(group);
	}
	// 1 2 3 4 5
	// 6 7 8 9 10
	// ...
	set<char> remaining{'A', 'B', 'C', 'D', 'E'};
	string answer;
	for(int rep = 0; rep < 5; rep++) {
		map<char, int> freq;
		map<char, vector<vector<int>>> in_that_case;
		for(vector<int> group : groups) {
			char c = query(group[0]);
			freq[c]++;
			group.erase(group.begin());
			in_that_case[c].push_back(group);
		}
		pair<int, char> best{INT_MAX, '?'};
		for(char c : remaining) {
			best = min(best, make_pair(freq[c], c));
		}
		// (23, 'C')
		answer += best.second;
		remaining.erase(best.second);
		groups = in_that_case[best.second];
	}
	printf("%s\n", answer.c_str());
	fflush(stdout);
	char c;
	scanf(" %c", &c);
	assert(c == 'Y');
}

int main() {
	int T;
	scanf("%d", &T);
	int F;
	scanf("%d", &F);
	for(int z = 1; z <= T; z++) {
		// printf("Case #%d: ", z);
		test_case();
	}
}

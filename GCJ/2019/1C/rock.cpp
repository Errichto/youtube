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

string read() {
	static char s[1005];
	scanf("%s", s);
	return string(s);
}

void test_case() {
	int n;
	scanf("%d", &n);
	vector<string> they(n);
	for(int i = 0; i < n; i++) {
		they[i] = read();
	}
	string moves;
	for(int pos = 0; true; ++pos) {
		set<int> chars;
		for(string s : they) {
			chars.insert(s[pos%s.length()]);
		}
		if((int) chars.size() == 3) {
			puts("IMPOSSIBLE");
			return;
		}
		if(chars.count('R') && chars.count('S')) {
			moves += "R";
		}
		else if(chars.count('R') && chars.count('P')) {
			moves += "P";
		}
		else if(chars.count('S') && chars.count('P')) {
			moves += "S";
		}
		else if(chars.count('S')) {
			moves += "R";
		}
		else if(chars.count('R')) {
			moves += "P";
		}
		else if(chars.count('P')) {
			moves += "S";
		}
		else {
			assert(false);
		}
		vector<string> remaining;
		for(string s : they) {
			char his = s[pos%s.length()];
			if(his == moves.back()) {
				remaining.push_back(s);
			}
		}
		if(remaining.empty()) {
			printf("%s\n", moves.c_str());
			return;
		}
		they = remaining;
	}
	assert(false);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int z = 1; z <= T; z++) {
		printf("Case #%d: ", z);
		test_case();
	}
}

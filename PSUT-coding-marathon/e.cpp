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

// you get to the same cell only if L=R and U=D

const int MAX_N = 1e6 + 5;
char a[MAX_N];

int main() {
	// LRRRLRLLRLLLLL
	// 0, -1, 0, 1, 2, ...
	int n;
	scanf("%d", &n);
	scanf("%s", a);
	assert(n == (int) strlen(a));
	vector<pair<int,int>> pref;
	int x = 0, y = 0;
	pref.emplace_back(x, y);
	for(int i = 0; i < n; ++i) {
		if(a[i] == 'L') {
			x--;
		}
		else if(a[i] == 'R') {
			x++;
		}
		else if(a[i] == 'U') {
			y++;
		}
		else if(a[i] == 'D') {
			y--;
		}
		else {
			assert(false); // unknown character
		}
		pref.emplace_back(x, y);
	}
	
	// two pointers / caterpillar
	
	// _ S _ _ _ E
	
	debug() << imie(pref);
	
	int start = 0;
	int answer = 0;
	set<pair<int,int>> in_substring;
	for(int end = 0; end < (int) pref.size(); ++end) {
		// pref[end] is the last position visited
		while(in_substring.count(pref[end])) {
			in_substring.erase(pref[start]);
			start++;
		}
		in_substring.insert(pref[end]);
		answer = max(answer, end - start);
	}
	printf("%d\n", answer);
}




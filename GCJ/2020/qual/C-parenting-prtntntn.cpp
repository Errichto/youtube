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



void test_case() {
	int n;
	scanf("%d", &n);
	vector<pair<pair<int,int>,int>> all;
	for(int i = 0; i < n; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		all.emplace_back(make_pair(l, r), i);
	}
	sort(all.begin(), all.end());
	string answer(n, '?');
	int A = 0, B = 0;
	for(auto pp : all) {
		int low = pp.first.first;
		int high = pp.first.second;
		int id = pp.second;
		if(A <= low) {
			A = high;
			answer[id] = 'C';// += 'C';
		}
		else if(B <= low) {
			B = high;
			answer[id] = 'J';
			// answer += 'J';
		}
		else {
			puts("IMPOSSIBLE");
			return;
		}
	}
	printf("%s\n", answer.c_str());
}

int main() {
	int T;
	scanf("%d", &T);
	for(int nr = 1; nr <= T; nr++) {
		printf("Case #%d: ", nr);
		test_case();
	}
}

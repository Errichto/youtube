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
	char s[105];
	scanf("%s", s);
	int n = strlen(s);
	string answer;
	int depth = 0;
	for(int i = 0; i < n; ++i) {
		int digit = s[i] - '0';
		for(int i = 0; i < max(0, digit - depth); ++i) {
			printf("(");
		}
		for(int i = 0; i < max(0, depth - digit); ++i) {
			printf(")");
		}
		printf("%d", digit);
		depth = digit;
	}
	for(int i = 0; i < depth; ++i) {
		printf(")");
	}
	puts("");
}

int main() {
	int T;
	scanf("%d", &T);
	for(int nr = 1; nr <= T; nr++) {
		printf("Case #%d: ", nr);
		test_case();
	}
}

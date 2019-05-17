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

// (2 4) (5 7) (7 6) (3 1)

// (5 9)  (7 20)

int main() {
	int n;
	scanf("%d", &n);
	n /= 2;
	vector<pair<int,int>> a;
	for(int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(x > y) {
			swap(x, y);
		}
		a.emplace_back(x, y);
	}
	sort(a.begin(), a.end());
	vector<pair<int,int>> one, two;
	// one: (2, 4), (5, 7) 
	// two: (3, 6)
	// 
	for(pair<int,int> interval : a) {
		if(one.empty() || one.back().second <= interval.first) {
			one.push_back(interval);
		}
		else if(two.empty() || two.back().second <= interval.first) {
			two.push_back(interval);
		}
		else {
			puts("-1");
			return 0;
		}
	}
	for(pair<int,int> interval : one) {
		printf("%d %d ", interval.first, interval.second);
	}
	reverse(two.begin(), two.end());
	for(pair<int,int> interval : two) {
		printf("%d %d ", interval.second, interval.first);
	}
	puts("");
}









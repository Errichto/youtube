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

// 8221
// 829...

int main() {
	int n, base;
	scanf("%d%d", &n, &base);
	vector<int> a(n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	set<int> available;
	for(int i = 0; i < base; ++i) {
		available.insert(i);
	}
	int best_pref = -1;
	for(int pref = 0; pref < n; ++pref) {
		assert(!available.empty());
		if(a[pref] < *available.rbegin()) {
			best_pref = pref;
		}
		if(!available.count(a[pref])) {
			break;
		}
		available.erase(a[pref]);
	}
	if(best_pref == -1) {
		vector<int> r(n + 1);
		for(int i = 0; i < n + 1; ++i) {
			r[i] = i;
		}
		swap(r[0], r[1]);
		for(int x : r) {
			printf("%d ", x);
		}
		puts("");
		return 0;
	}
	
	
	available.clear();
	for(int i = 0; i < base; ++i) {
		available.insert(i);
	}
	for(int i = 0; i < best_pref; ++i) {
		assert(!available.empty());
		assert(available.count(a[i]));
		available.erase(a[i]);
	}
	a[best_pref]++;
	while(!available.count(a[best_pref])) {
		++a[best_pref];
	}
	available.erase(a[best_pref]);
	for(int i = best_pref + 1; i < n; ++i) {
		assert(!available.empty());
		a[i] = *available.begin();
		available.erase(available.begin());
	}
	for(int x : a) {
		printf("%d ", x);
	}
	puts("");
}




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

// 1 2 3 4 5 6 7

// 1 3 5 7 2 4 6


// 1 2 3 4 5 6 7 8
// 1 3 5 7 2 4 8 6

// 1 2 3 4 5 6
// 1 3 5 2 6 4

int main() {
	int n;
	scanf("%d", &n);
	vector<int> a(n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
		a[i]--;
	}
	
	if(n <= 4) {
		puts("-1");
		return 0;
	}
	
	
	
	vector<int> r;
	for(int i = 0; i < n; i += 2) {
		r.push_back(a[i]);
	}
	for(int i = 1; i < n; i += 2) {
		r.push_back(a[i]);
	}
	assert((int) r.size() == n);
	if(n % 2 == 0) {
		swap(r[n-1], r[n-2]);
	}
	
	
	for(int x : r) {
		printf("%d ", x + 1);
	}
	puts("");
	
	
	set<pair<int,int>> neigh;
	for(int i = 0; i < n; ++i) {
		neigh.insert(make_pair(a[i], a[(i+1)%n]));
		neigh.insert(make_pair(a[(i+1)%n], a[i]));
	}
	bool ok = true;
	for(int i = 0; i < n; ++i) {
		if(neigh.count(make_pair(r[i], r[(i+1)%n]))) {
			ok = false;
			break;
		}
	}
	assert(ok);
	
	
	//~ vector<int> b(n);
	//~ for(int i = 0; i < n; ++i) {
		//~ b[i] = i;
	//~ }
	
	
	//~ do {
		//~ // check if permutation b is ok
		//~ bool ok = true;
		//~ for(int i = 0; i < n; ++i) {
			//~ if(neigh.count(make_pair(b[i], b[(i+1)%n]))) {
				//~ ok = false;
				//~ break;
			//~ }
		//~ }
		//~ if(ok) {
			//~ puts("OK");
			//~ return 0;
		//~ }
	//~ } while(next_permutation(b.begin(), b.end()));
	//~ puts("-1");
}











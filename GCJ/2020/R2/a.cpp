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

typedef long long ll;

void test_case() {
	long long L, R;
	scanf("%lld%lld", &L, &R);
	long long low = 0, high = 2e9;
	// pair<ll,ll> memo = {L, R};
	ll nxt = 1;
	// while(L >= nxt || R >= nxt) {
		// if(L >= R) L -= nxt;
		// else R -= nxt;
		// nxt++;
	// }
	if(L != R) {
		while(low < high) {
			long long mid = (low + high + 1) / 2;
			long long total = mid * (mid + 1) / 2;
			if(total <= abs(L - R)) {
				low = mid;
			}
			else {
				high = mid - 1;
			}
		}
		ll eaten = low * (low + 1) / 2;
		nxt = low + 1;
		if(L > R) {
			L -= eaten;
			assert(L >= R);
			assert(L - nxt < R);
		}
		else {
			R -= eaten;
			assert(R >= L);
			assert(R - nxt < L);
		}
	}
	debug() << imie(nxt);
	low = 0, high = 1e9 + 50;
	while(low < high) {
		long long mid = (low + high + 1) / 2;
		long long one = mid * (nxt + nxt + 2 * (mid - 1)) / 2;
		long long two = one + mid;
		bool ok;
		if(L >= R) {
			ok = (L >= one && R >= two);
		}
		else {
			ok = (R >= one && L >= two);
		}
		if(ok) {
			low = mid;
		}
		else {
			high = mid - 1;
		}
	}
	long long mid = low;
	long long one = mid * (nxt + nxt + 2 * (mid - 1)) / 2;
	long long two = one + mid;
	if(L >= R) {
		L -= one;
		R -= two;
	}
	else {
		L -= two;
		R -= one;
	}
	nxt += 2 * mid;
	assert(L >= 0 && R >= 0);
	if(L >= R && L >= nxt) {
		L -= nxt;
		nxt++;
	}
	else if(R > L && R >= nxt) {
		R -= nxt;
		nxt++;
	}
	assert(L < nxt && R < nxt);
	debug() << imie(L) imie(R);
	printf("%lld %lld %lld\n", nxt - 1, L, R);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int nr = 1; nr <= T; ++nr) {
		printf("Case #%d: ", nr);
		test_case();
	}
}

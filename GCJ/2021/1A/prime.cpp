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



void test_case() {
	int m;
	scanf("%d", &m);
	vector<pair<int,long long>> in(m);
	long long sum_all = 0;
	for(pair<int,long long>& pair : in) {
		scanf("%d%lld", &pair.first, &pair.second);
		sum_all += pair.second * pair.first;
	}
	for(int sum = 2; sum <= 1'000; sum++) {
		long long product = sum_all - sum;
		if(product <= 1) {
			break;
		}
		bool ok = true;
		long long we_got_sum = 0;
		for(pair<int, long long> pair : in) {
			int p = pair.first;
			long long freq = pair.second;
			
			int cnt = 0;
			while(product % p == 0) {
				product /= p;
				cnt++;
			}
			if(cnt > freq) {
				ok = false;
				break;
			}
			we_got_sum += (long long) cnt * p;
		}
		if(!ok) {
			continue;
		}
		if(product == 1 && we_got_sum == sum) {
			printf("%lld\n", sum_all - sum);
			return;
		}
	}
	puts("0");
}

int main() {
	int T;
	scanf("%d", &T);
	for(int z = 1; z <= T; z++) {
		printf("Case #%d: ", z);
		test_case();
	}
}



// 1000 x 2
// 2500 x 3



// p1 * p2 * p3 * p4 = SUM - p1 - p2 - p3 - p4
                          // <--------------->
                               // small
                                // <= 200

// SUM <= 10^17   50'000

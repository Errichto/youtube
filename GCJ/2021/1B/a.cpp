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
	vector<long long> in(3);
	for(int i = 0; i < 3; ++i) {
		scanf("%lld", &in[i]);
	}
	const long long M = 360 * 12 * 10LL * 1000 * 1000 * 1000;
	do {
		long long diff = in[1] - in[0];
		if(diff < 0) {
			diff += M;
		}
		// 11 * x == diff
		for(int rep = 0; rep < 12; ++rep) {
			// 11 * x == rep * M + diff
			long long tmp = rep * M + diff;
			if(tmp % 11 == 0) {
				long long x = tmp / 11;
				long long shift = in[0] - x;
				if(shift < 0) {
					shift += M;
				}
				bool ok = true;
				for(int i = 0; i < 3; ++i) {
					if((vector<int>{1, 12, 720}[i] * x + shift) % M != in[i]) {
						ok = false;
					}
				}
				if(ok) {
					vector<long long> answer;
					answer.push_back(x % 1'000'000'000);
					x /= 1'000'000'000;
					answer.push_back(x % 60);
					x /= 60;
					answer.push_back(x % 60);
					x /= 60;
					answer.push_back(x);
					reverse(answer.begin(), answer.end());
					if(answer[0] < 12) {
						for(long long x : answer) {
							printf(" %lld", x);
						}
						puts("");
						return;
						// debug() << imie(answer);
					}
				}
			}
		}
	} while(next_permutation(in.begin(), in.end()));
	assert(false);
}


// M = 360 * 12 * 10^10

// x+shift = 123
// 12*x+shift = 52000
// 720*x+shift = 491052340

int main() {
	int T;
	scanf("%d", &T);
	for(int z = 1; z <= T; z++) {
		printf("Case #%d:", z);
		test_case();
	}
}

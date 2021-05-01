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

// dp[15s][14s][13s][small]
double dp[21][21][21][21];
int action[21][21][21][21][10];
int t, n, b;
long long p;

void test_case() {
	int zero = 0, one = 0, two = 0, small = 0;
	vector<int> h(n + 1);
	for(int rep = 0; rep < n * b; ++rep) {
		int digit;
		scanf("%d", &digit);
		for(int i = 1; i <= n; ++i) {
			if(h[i] == action[zero][one][two][small][digit]) {
				printf("%d\n", i);
				fflush(stdout);
				if(h[i] == 14) {
					zero++;
					one--;
				}
				else if(h[i] == 13) {
					one++;
					two--;
				}
				else {
					assert(h[i] == small);
					small++;
					if(small == 13) {
						two++;
						small = 0;
					}
				}
				assert(one >= 0 && two >= 0);
				h[i]++;
				break;
			}
			assert(i != n); // not found
		}
	}
}

int main() {
	scanf("%d%d%d%lld", &t, &n, &b, &p);
	assert(n == 20);
	for(int zero = n; zero >= 0; --zero) {
		for(int one = n - zero; one >= 0; --one) {
			for(int two = n - one - zero; two >= 0; --two) {
				for(int small = b - 3; small >= 0; --small) {
					if(zero + one + two == n && small != 0) {
						continue;
					}
					for(int digit = 0; digit < 10; ++digit) {
						double best = -1;
						if(one != 0) {
							double tmp = dp[zero+1][one-1][two][small] + 0.1 * digit;
							if(tmp > best) {
								best = tmp;
								action[zero][one][two][small][digit] = 14;
							}
						}
						if(two != 0) {
							double tmp = dp[zero][one+1][two-1][small] + 0.01 * digit;
							if(tmp > best) {
								best = tmp;
								action[zero][one][two][small][digit] = 13;
							}
						}
						if(zero + one + two != n) {
							if(small == b - 3) {
								double tmp = dp[zero][one][two+1][0] + 0.001 * digit;
								if(tmp > best) {
									best = tmp;
									action[zero][one][two][small][digit] = small;
								}
							}
							else {
								double tmp = dp[zero][one][two][small+1] + (small == b - 4 ? 0.0001 * digit : 0);
								if(tmp > best) {
									best = tmp;
									action[zero][one][two][small][digit] = small;
								}
							}
						}
						dp[zero][one][two][small] += best / 10;
					}
					debug() << imie(zero) imie(one) imie(two) imie(small) << " " << dp[zero][one][two][small];
				}
			}
		}
	}
	while(t--) {
		test_case();
	}
	// debug() << imie(dp[0][0][0][0]);
	// int T;
	// scanf("%d", &T);
	// for(int z = 1; z <= T; z++) {
		// printf("Case #%d: ", z);
		// test_case();
	// }
}

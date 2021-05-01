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

const int nax = 5e6 + 5;
int v[nax], memo[nax];
const int INF = 1e9 + 5;

void add(int& a, int b) {
	a = min(a + b, INF);
}

void test_case() {
	int n, a, b;
	scanf("%d%d%d", &n, &a, &b);
	int g = __gcd(a, b);
	vector<int> u(n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &u[i]);
	}
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			if(u[i] > 0 && u[j] > 0 && (j - i) % g != 0) {
				puts("IMPOSSIBLE");
				return;
			}
		}
	}
	reverse(u.begin(), u.end());
	v[0] = 1;
	for(int start = 0; start < nax - 100; ++start) {
		// maybe v[start] is Un = U[0]
		// cout << v[start] << " ";
		bool ok = true;
		for(int i = 0; i <= n + b; ++i) {
			memo[start+i] = v[start+i];
		}
		for(int i = 0; i < n; ++i) {
			if(v[start+i] < u[i]) {
				ok = false;
				break;
			}
			int extra = v[start+i] - u[i];
			add(v[start+i+a], extra);
			add(v[start+i+b], extra);
		}
		if(ok) {
			printf("%d\n", start + n);
			for(int i = 0; i <= start + b + 1 + n; ++i) {
				v[i] = 0;
			}
			return;
		}
		// rollback
		for(int i = 0; i <= n + b; ++i) {
			v[start+i] = memo[start+i];
			memo[start+i] = 0;
		}
		add(v[start+a], v[start]);
		add(v[start+b], v[start]);
	}
	assert(false);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int z = 1; z <= T; z++) {
		printf("Case #%d: ", z);
		test_case();
	}
}


// 1 0 0 0 0 
// 0 1 0 1 0
// 0 0 1 1 1 0 0 0
// 0 0 0 2 1 1 0 0
// 0 0 0 ^ 
      // Un

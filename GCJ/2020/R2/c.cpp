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

struct P {
	ll x, y;
	void read() {
		scanf("%lld%lld", &x, &y);
	}
	P operator -(P b) {
		return P{x - b.x, y - b.y};
	}
	void normalize() {
		if(x < 0) {
			x *= -1;
			y *= -1;
		}
		if(x == 0 && y < 0) {
			y *= -1;
		}
		if(x == 0) y = 1;
		if(y == 0) x = 1;
		if(x != 0 && y != 0) {
			ll g = __gcd(abs(x), abs(y));
			x /= g;
			y /= g;
		}
	}
};

void test_case() {
	int n;
	scanf("%d", &n);
	vector<P> points(n);
	for(int i = 0; i < n; ++i) {
		points[i].read();
	}
	map<pair<ll,ll>, vector<pair<int,int>>> m;
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			P dir = points[i] - points[j];
			// if(i == 0) debug() << imie(dir.x) imie(dir.y);
			dir.normalize();
			// if(i == 0) debug() << imie(dir.x) imie(dir.y);
			m[{dir.x, dir.y}].emplace_back(i, j);
		}
	}
	int answer = min(n, 2);
	for(auto scenario : m) {
		vector<pair<int,int>> pairs = scenario.second;
		vector<int> group(n, n);
		for(pair<int,int> edge : pairs) {
			int a = edge.first;
			int b = edge.second;
			group[a] = min(group[a], min(a, b));
			group[b] = min(group[b], min(a, b));
		}
		vector<int> cnt(n);
		for(int x : group) {
			if(x < n) {
				cnt[x]++;
			}
		}
		debug() << imie(cnt);
		int total = 0;
		int odd = 0;
		for(int x : cnt) {
			total += x / 2 * 2;
			if(x % 2) {
				odd++;
			}
		}
		total += odd / 2 * 2;
		total = min(n, total + 2);
		answer = max(answer, total);
		// debug() << imie(scenario.first) imie(cnt) imie(group) imie(pairs);
	}
	printf("%d\n", answer);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int nr = 1; nr <= T; ++nr) {
		printf("Case #%d: ", nr);
		test_case();
	}
}

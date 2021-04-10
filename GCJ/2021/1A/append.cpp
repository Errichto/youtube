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

bool is_prefix(string a, string b) {
	return a.length() <= b.length() && b.substr(0, a.size()) == a;
}

string inc(string s) {
	for(int i = (int) s.length() - 1; i >= 0; --i) {
		if(s[i] != '9') {
			s[i]++;
			return s;
		}
		s[i] = '0';
	}
	return "1" + s;
}

/*
5723
57    ->  prv+1

5799
57    -> 5700



*/

void test_case() {
	int n;
	scanf("%d", &n);
	// long long prv = 0;
	string prv = "0";
	int operations = 0;
	for(int i = 0; i < n; ++i) {
		long long tmp;
		scanf("%lld", &tmp);
		string nxt = to_string(tmp);
		int init_length = nxt.length();
		string a = prv; //to_string(prv);
		string b = nxt;
		if(is_prefix(b, a)) {
			if(is_prefix(b, inc(a))) { // to_string(prv + 1))) {
				nxt = inc(a);
			}
			else {
				while(a.length() >= b.length()) {
					b += '0';
				}
				nxt = b;
				// nxt = stoi(b);
			}
		}
		else {
			// keep adding zeros
			while(nxt.length() < prv.length() || (nxt.length() == prv.length() && nxt <= prv)) {
			// while(nxt <= prv) {
				nxt += "0";
			}
		}
		operations += nxt.length() - init_length;
		prv = nxt;
		// cerr << "a[i] = " << nxt << endl;
	}
	printf("%d\n", operations);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int z = 1; z <= T; z++) {
		printf("Case #%d: ", z);
		test_case();
	}
}


// 5823
// 58

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

int B;

int query(int i) {
	cout << i << endl;
	int r;
	scanf("%d", &r);
	return r;
}

void test_case() {
	vector<int> answer(B + 1);
	int L = 1, R = B;
	for(int nr = 1; true; nr += 2) {
		if(nr % 10 == 1 && nr != 1) {
			int found = -1;
			int found_diff = -1;
			for(int i = 1; i < L; ++i) {
				if(answer[i] == answer[B+1-i]) {
					found = i;
				}
				else {
					found_diff = i;
				}
			}
			if(found == -1) {
				int new_value = query(1);
				query(1);
				if(new_value != answer[1]) {
					for(int i = 1; i <= L; ++i) {
						answer[i] ^= 1;
					}
					for(int i = R; i <= B; ++i) {
						answer[i] ^= 1;
					}
				}
			}
			else {
				int one = query(found);
				if(one != answer[found]) {
					for(int i = 1; i <= L; ++i) {
						answer[i] ^= 1;
					}
					for(int i = R; i <= B; ++i) {
						answer[i] ^= 1;
					}
				}
				if(found_diff == -1) {
					query(found);
				}
				else {
					if(query(found_diff) != answer[found_diff]) {
						reverse(answer.begin() + 1, answer.end());
					}
				}
			}
			nr += 2;
		}
		answer[L] = query(L);
		answer[R] = query(R);
		L++;
		R--;
		if(L > R) {
			for(int i = 1; i <= B; ++i) {
				cout << answer[i];
			}
			cout << endl;
			string response;
			cin >> response;
			assert(response == "Y");
			return;
		}
	}
}

int main() {
	int T;
	scanf("%d%d", &T, &B);
	for(int nr = 1; nr <= T; nr++) {
		// printf("Case #%d: ", nr);
		test_case();
	}
}

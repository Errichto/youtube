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

// 4 / 8 / 5 / 6 / 2 / 9
// 2 / 2 / 2 / 2 / 2
// 5 / 3  1 / 4 / 8
// ... 3 1 3 1 3
// 1 1 / 1 1 / 1 1  -> 8
// 1 1 1 / 1 1 1 -> 9 
// 12 x 1 -> 81
// a sequence of 1's should be splitted into triples
// 1 3 / 1 2 1 / 4 1 / 5 1
// for a sequence 1 X 1 X 1 X 1 ->
//	find the smallest X and connect it with two 1's

// if there are two adjacent big numbers, split them
// 1 1 1 1 1 1 1 X 1 1 X 1 1 1 X 1 X 1 X
// "1 1 / X" is not worse than "1 1 X"
// because 2*x >= x+2

// X 1 1 X 1 X

// X / 1 1 1 / X       X 1 / 1 1 X              X=2
// x*3*x     3x vs (x+1)*(x+2)  x^2+3x+2

// X / 1 1 / X   X 1 / 1 X
// 2*x*x         (x+1)(x+1)   x^2+2x+1

// 2 1 / 1 1 / 1 2 -> 18
										// 2 1 \ 3+ ...
										// 6 1 \ 7+
											// 1 1 \ 3+

										// 3+ \ 1 1 \ 3+

// still possible
// 1 1 1 1 1 1 1
// 2 1 1 1 1 2 1 1 1 2 1 1 1 1 2 1
										// 1 6 1 6 1 6 1 6 1

const int MAX_N = 3e5 + 5;
int a[MAX_N];
bool split_after[MAX_N];

bool one(int i) {
	return a[i] == 1;
}
bool two(int i) {
	return a[i] >= 2;
}
bool three(int i) {
	return a[i] >= 3;
}

void solve(int L, int R) {
	if(L > R) {
		return;
	}
	if(L == R) {
		return;
	}
	if(L + 1 == R) {
		if(a[L] >= 2 && a[R] >= 2) {
			split_after[L] = true;
		}
		return;
	}
	if(a[L] >= 2 && a[L+1] >= 2) {
		split_after[L] = true;
		solve(L + 1, R);
		return;
	}
	if(a[L+1] >= 2 && a[L+2] >= 2) {
		split_after[L+1] = true;
		solve(L, L+1);
		solve(L+2, R);
		return;
	}
	assert(a[L] == 1 || a[L+1] == 1);
	if(a[L] == 1 && a[L+1] == 1 && a[L+2] >= 3) {
		split_after[L+1] = true;
		solve(L + 2, R);
		return;
	}
	if(a[L] >= 3 && a[L+1] == 1 && a[L+2] == 1) { // 3 1 1
		split_after[L] = true;
		solve(L + 1, R);
		return;
	}
	
	// 6 1 \ 6+
	if(two(L) && one(L+1) && a[L] <= a[L+2]) {
		split_after[L+1] = true;
		solve(L + 2, R);
		return;
	}
	// 7+ \ 1 6
	if(one(L+1) && two(L+2) && a[L] > a[L+2]) {
		split_after[L] = true;
		solve(L + 1, R);
		return;
	}
	// 1 6 1 / 7
	if(one(L) && two(L+1) && one(L+2) && R - L + 1 >= 4) {
		if(a[L+1] + 1 <= a[L+3]) {
			split_after[L+2] = true;
			solve(L + 3, R);
			return;
		}
		else {
			split_after[L+1] = true;
			solve(L+2, R);
			return;
		}
	}
	
	
	// 1 1 1
	// 1 X 1
	
	// 1 1 X
						// 1 X X
	// X 1 1
	// X 1 X
	
	if(R - L + 1 >= 4 && three(L) && one(L+1) && one(L+2) && three(L+3)) {
		split_after[L] = true;
		split_after[L+2] = true;
		solve(L + 3, R);
		return;
	}
	
	
	assert(a[L] == 1 || a[L+1] == 1);
	
	// 1 6 1 |
	if(one(L) && one(L+2) && two(L+1) && R == L + 2) {
		return;
	}
	
						// 1 6 1 6 1 6 _
						// 1 6 1 7
	
	// 6 1 / 6+
	
	// 1 1 1 1 1
	int pref_ones = 0;
	for(int i = L; i <= R && one(i) && pref_ones <= 6; ++i) {
		++pref_ones;
	}
	if(pref_ones == 3 || pref_ones >= 5) {
		if(R - L + 1 > 3) {
			split_after[L+2] = true;
		}
		solve(L + 3, R);
		return;
	}
	// 1 1 1 1
	if(pref_ones == 4 && R - L + 1 == 4) {
		split_after[L+1] = true;
		return;
	}
	// 1 1 1 1 X
	if(pref_ones == 4) {
		// 1 1 1 1 3+
		if(three(L+4)) {
			split_after[L+3] = true;
			solve(L, L + 3);
			solve(L + 4, R);
			return;
		}
		// 1 1 1 1 2 ...
		// are you sure?
		split_after[L+2] = true;
		solve(L + 3, R);
		return;
	}
	
											// 1 2 2
		
	
	// 1's and 2's
	
	if(R - L + 1 == 3) {
		if(a[L] == 2 && a[L+1] == 1 && a[L+2] == 2) {
			split_after[L] = true;
		}
		return;
	}
	assert(R - L + 1 >= 4);
	
	// 1 2 1 \ 3+
	assert(a[L] <= 2 && a[L+1] <= 2 && a[L+2] <= 2);
	if(one(L) && two(L+1) && one(L+2) && three(L+3)) {
		split_after[L+2] = true;
		solve(L + 3, R);
		return;
	}
	// 1 2 \ 1 12
	if(one(L) && two(L+1) && one(L+2)) {
		split_after[L+1] = true;
		solve(L + 2, R);
		return;
	}
	
	// 2 1 1 ?
	if(two(L) && one(L+1) && one(L+2)) {
		if(a[L+3] >= 3) {
			split_after[L+2] = true;
			solve(L + 3, R);
			return;
		}
		split_after[L+1] = true;
		solve(L + 2, R);
		return;
	}
	
	if(two(L+2) && three(L+3)) {
		split_after[L+2] = true;
		solve(L, L + 2);
		solve(L + 3, R);
		return;
	}
	
	if(one(L) && one(L+1) && two(L+2)) {
		split_after[L+1] = true;
		solve(L + 2, R);
		return;
	}
	
	//~ assert(R - L + 1 >= 3);
	printf("unknown: ");
	for(int i = L; i <= R; ++i) {
		printf("%d ", a[i]);
	}
	puts("");
	assert(false);
	
	
	//~ int x = max(a[L], a[L+1]);
	//~ if(x >= 2) {
		//~ int up_to = L + 1;
		//~ while(up_to + 1 <= R && a[up_to+1] == a[up_to-1]) {
			//~ up_to++;
		//~ }
	//~ }
}

int n;
long long score() {
	long long last_sum = 0;
	long long answer = 1;
	for(int i = 1; i <= n; ++i) {
		last_sum += a[i];
		if(i == n || split_after[i]) {
			answer *= last_sum;
			last_sum = 0;
		}
	}
	return answer;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	solve(1, n);
	
	for(int i = 1; i <= n; ++i) {
		printf("%d ", a[i]);
		if(split_after[i]) {
			printf("/ ");
		}
	}
	puts("");
	long long mine = score();
	cerr << mine << " ";
	
	
	long long best = 0;
	for(int mask = 0; mask < (1 << (n - 1)); ++mask) {
		for(int i = 1; i < n; ++i) {
			split_after[i] = bool(mask & (1 << (i - 1)));
		}
		best = max(best, score());
	}
	cerr << best << endl;
	assert(mine == best);
}















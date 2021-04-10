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

struct Guy {
	vector<bool> a;
	int score;
	void read(int q) {
		static char s[1005];
		scanf("%s", s);
		assert(q == (int) strlen(s));
		for(int i = 0; i < q; ++i) {
			a.push_back(s[i] == 'T');
		}
		scanf("%d", &score);
	}
};

void print(__int128 x) {
	if(x == 0) {
		printf("0");
		return;
	}
	string s;
	while(x != 0) {
		s += '0' + x % 10;
		x /= 10;
	}
	reverse(s.begin(), s.end());
	printf("%s", s.c_str());
}

const int MAX_Q = 125;
__int128 arr[MAX_Q][MAX_Q][MAX_Q];
__int128 C[MAX_Q][MAX_Q];

void test_case() {
	int n, q;
	scanf("%d%d", &n, &q);
	// #warning TODO, if some score is 0 then print the opposite with probability 1/1
	vector<Guy> guys(n);
	for(Guy& bro : guys) {
		bro.read(q);
	}
	while(n < 3) {
		guys.push_back(guys[0]);
		n++;
	}
	assert(n == 3);
	for(Guy bro : guys) {
		if(bro.score == 0) {
			for(bool x : bro.a) {
				printf(x ? "F" : "T");
			}
			printf(" %d/1\n", q);
			return;
		}
	}
	vector<bool> flip = guys[0].a;
	for(Guy& bro : guys) {
		for(int i = 0; i < q; i++) {
			if(flip[i]) {
				bro.a[i] = !bro.a[i];
			}
		}
	}
	// guys[0] says F only
	vector<vector<int>> cnt(2, vector<int>(2));
	for(int i = 0; i < q; i++) {
		cnt[guys[1].a[i]][guys[2].a[i]]++;
	}
	
	auto get_ways = [&]() {
		// cnt[0][0], cnt[0][1]
		for(int a = 0; a <= cnt[0][0]; a++) {
			// a is the number of correct T's among type[0][0]
			for(int b = 0; b <= cnt[0][1]; b++) {
				// b is T's among type[0][1]
				int g0 = cnt[0][0] - a + cnt[0][1] - b;
				int g1 = cnt[0][0] - a + cnt[0][1] - b;
				int g2 = cnt[0][0] - a + b;
				arr[g0][g1][g2] += C[cnt[0][0]][a] * C[cnt[0][1]][b];
			}
		}
		// cnt[1][0], cnt[1][1]
		__int128 ways = 0;
		for(int a = 0; a <= cnt[1][0]; ++a) {
			for(int b = 0; b <= cnt[1][1]; ++b) {
				int g0 = cnt[1][0] - a + cnt[1][1] - b;
				int g1 = a + b;
				int g2 = cnt[1][0] - a + b;
				if(g0 <= guys[0].score && g1 <= guys[1].score && g2 <= guys[2].score) {
					ways += arr[guys[0].score-g0][guys[1].score-g1][guys[2].score-g2] * C[cnt[1][0]][a] * C[cnt[1][1]][b];
				}
			}
		}
		for(int g0 = 0; g0 <= cnt[0][0] + cnt[0][1]; ++g0) {
			for(int g2 = 0; g2 <= cnt[0][0] + cnt[0][1]; ++g2) {
				arr[g0][g0][g2] = 0;
			}
		}
		return ways;
	};
	
	__int128 total = get_ways();
	__int128 EV = 0;
	vector<bool> answer(q);
	for(int x = 0; x < 2; ++x) {
		for(int y = 0; y < 2; ++y) {
			if(cnt[x][y] == 0) {
				continue;
			}
			// (F, x, y)
			// cnt[x][y]
			cnt[x][y]--;
			if(x) {
				guys[1].score--;
			}
			if(y) {
				guys[2].score--;
			}
			
			__int128 ways_true = get_ways(); // on remaining Q-1 questions
			__int128 ways_false = total - ways_true;
			for(int i = 0; i < q; ++i) {
				if(guys[1].a[i] == x && guys[2].a[i] == y) {
					answer[i] = (ways_true >= ways_false);
					EV += max(ways_true, ways_false);
				}
			}
			
			cnt[x][y]++;
			if(x) {
				guys[1].score++;
			}
			if(y) {
				guys[2].score++;
			}
		}
	}
	for(int i = 0; i < q; ++i) {
		bool x = answer[i];
		if(flip[i]) {
			x = !x;
		}
		printf(x ? "T" : "F");
	}
	printf(" ");
	__int128 g = __gcd(EV, total);
	EV /= g;
	total /= g;
	print(EV);
	printf("/");
	print(total);
	puts("");
	// printf("%lld/%lld\n", (long long) EV, (long long) total);
}

int main() {
	for(int i = 0; i < MAX_Q; i++) {
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; ++j) {
			C[i][j] = C[i-1][j-1] + C[i-1][j];
		}
	}
	int T;
	scanf("%d", &T);
	for(int z = 1; z <= T; z++) {
		printf("Case #%d: ", z);
		test_case();
	}
}
/*
N = 2
Q = 8
TTFFFFFT
TFFFTTTT
12334441

TT -> T / F
TF -> agree with first guy? Y/N
FT -> agree with first guy? Y/N
FF -> T / F

2^4 ways I can answer
if N = 3 then 2^8 ways I can answer



score = 2

I guess FFTTTTT

dp[i][c1][c2][c3]


TFFFFFFF     7 / 10
FFFFFFFF     8 / 10
^
F


FFF
TTT

FTT
TFF

1000 ways to achieve (30, 40, 42)

dp[30][40][42] = 1000

O(Q^2)

...

O(Q^2)

dp2[20][10][8]


4 * Q^2


TFTF
FFFT
TTTT

TTTT
FTFF
TFTF

answer = TFFF
          ^ ^
         TTFT

*/

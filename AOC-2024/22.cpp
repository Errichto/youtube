#include <bits/stdc++.h>
using namespace std;

const int MOD = 1 << 24;
void f(long long& x) {
	x ^= x * 64;
	x %= MOD;
	x ^= x / 32;
	x %= MOD;
	x ^= x * 2048LL;
	x %= MOD;
}

int main() {
	long long x;
	long long sum = 0;
	while (scanf("%lld", &x) != EOF) {
		for (int i = 0; i < 2000; i++) {
			f(x);
		}
		sum += x;
	}
	cout << sum << "\n";
}

// E. Two Arrays and Sum of Functions, CF #560 (Div. 3)
// https://codeforces.com/contest/1165/problem/E
// O(n*log(n))
#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
int main() {
	int n;
	scanf("%d", &n);
	vector<long long> a(n);
	for(int i = 0; i < n; ++i) {
		scanf("%lld", &a[i]);
		a[i] = a[i] * (i + 1) * (n - i);
		// don't apply modulo here because sort would be incorrect!
	}
	vector<int> b(n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &b[i]);
	}
	sort(a.begin(), a.end()); // sort increasingly
	sort(b.rbegin(), b.rend()); // sort decreasingly
	int answer = 0;
	for(int i = 0; i < n; ++i) {
		a[i] %= MOD; // to avoid overflow in multiplication
		answer = (answer + a[i] * b[i]) % MOD;
	}
	printf("%d\n", answer);
}

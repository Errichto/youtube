// O(N log(N))
#include <bits/stdc++.h>
using namespace std;
void test_case() {
	int n;
	scanf("%d", &n);
	vector<int> cnt(2 * n + 1);
	int must_remove = 0;
	for(int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		if(x <= 2 * n) {
			++cnt[x];
		}
		else {
			++must_remove;
		}
	}
	vector<int> dp(2 * n + 1);
	for(int value = 1; value <= 2 * n; ++value) {
		vector<int> dp2(2 * n / value + 1);
		int suffix_min = dp.back();
		for(int i = (int) dp.size() - 1; i >= 0; --i) {
			suffix_min = min(suffix_min, dp[i]);
			if(i < (int) dp2.size()) {
				dp2[i] = suffix_min + abs(i - cnt[value]);
			}
		}
		dp = dp2;
	}
	int answer = INT_MAX;
	for(int x : dp) {
		answer = min(answer, x);
	}
	printf("%d\n", answer + must_remove);
}
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		test_case();
	}
}

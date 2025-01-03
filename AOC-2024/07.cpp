#include <bits/stdc++.h>
using namespace std;


void rec(int i, long long sum, long long target, const vector<int>& v, bool& ok) {
	if (i == (int) v.size()) {
		if (sum == target) {
			ok = true;
		}
		return;
	}
	rec(i + 1, sum + v[i], target, v, ok);
	rec(i + 1, sum * v[i], target, v, ok);
	rec(i + 1, stoll(to_string(sum) + to_string(v[i])), target, v, ok);
}

int main() {
	long long res;
	long long total_answer = 0;
	while (scanf("%lld: ", &res) != EOF) {
		vector<int> v;
		while (true) {
			int x;
			scanf("%d", &x);
			v.push_back(x);
			char c;
			scanf("%c", &c);
			if (c == ' ') {
				continue;
			}
			else {
				break;
			}
		}
		// cout << res << " ";
		bool ok = false;
		rec(1, v[0], res, v, ok);
		if (ok) {
			total_answer += res;
		}
	}
	printf("%lld\n", total_answer);
}

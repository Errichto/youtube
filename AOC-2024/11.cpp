#include <bits/stdc++.h>
using namespace std;

// bool isOdd(long long x) {
	// return to_string(x).length() % 2 == 1;
// }

int main() {
	// INPUT * 2024 * 2024
	
	// for (long long x = 1; x <= 100'000'000; x++) {
		
		// if (isOdd(x) && isOdd(x * 2024) && isOdd(x * 2024 * 2024)) {
			// cout << x << " ";
		// }
	// }
	// cout << "NONE";
	// return 0;
	
	
	map<long long, long long> v;
	int tmp;
	while (scanf("%d", &tmp) != EOF) {
		v[tmp]++;
	}
	for (int rep = 0; rep < 1000; rep++) {
		map<long long, long long> newV;
		for (auto [x,cnt] : v) {
			if (x == 0) {
				newV[1] += cnt;
			}
			else if (to_string(x).length() % 2 == 0) {
				string s = to_string(x);
				int k = s.length();
				newV[stoll(s.substr(0, k/2))] += cnt;
				newV[stoll(s.substr(k/2, k/2))] += cnt;
			}
			else {
				newV[x * 2024] += cnt;
			}
		}
		v = newV;
		// cout << rep << " " << v.size() << " " << *max_element(v.begin(), v.end()) << "\n";
	}
	// for (long long x : v) {
		// cout << x << " ";
	// }
	
	long long total = 0;
	for (auto pp : v) {
		total += pp.second;
	}
	printf("%lld\n", total);
	cerr << v.size() << "\n";
}

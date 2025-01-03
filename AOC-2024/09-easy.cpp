#include <bits/stdc++.h>
using namespace std;

struct Block {
	int id, size, pos;
};

int main() {
	string s;
	cin >> s;
	int n = s.length();
	vector<int> v;
	vector<int> avail;
	for (int i = 0; i < n; i++) {
		int digit = s[i] - '0';
		for (int rep = 0; rep < digit; rep++) {
			if (i % 2 == 0) {
				v.push_back(i / 2);
			}
			else {
				avail.push_back(v.size());
				v.push_back(0);
			}
		}
	}
	reverse(avail.begin(), avail.end());
	for (int i = (int) v.size() - 1; i >= 0; i--) {
		if (v[i]) {
			if (!avail.empty() && avail.back() < i) {
				v[avail.back()] = v[i];
				v[i] = 0;
				avail.pop_back();
			}
		}
	}
	
	long long answer = 0;
	for (int i = 0; i < (int) v.size(); i++) {
		answer += v[i] * i;
	}
	cout << answer << "\n";
}

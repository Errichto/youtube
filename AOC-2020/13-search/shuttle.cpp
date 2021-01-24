#include <bits/stdc++.h>
using namespace std;
int main() {
	int start;
	cin >> start;
	string s;
	cin >> s;
	vector<int> a{0};
	for(int i = 0; i < (int) s.length(); ++i) {
		if(s[i] == ',') {
			a.push_back(0);
		}
		if(isdigit(s[i])) {
			a.back() = 10 * a.back() + (s[i] - '0');
		}
	}
	pair<int,int> answer{INT_MAX, INT_MAX};
	for(int x : a) {
		if(x != 0) {
			int when = (start + x - 1) / x * x; // ceil(start / x) * x
			answer = min(answer, make_pair(when, x * (when - start)));
		}
	}
	printf("%d %d\n", answer.first, answer.second);
}

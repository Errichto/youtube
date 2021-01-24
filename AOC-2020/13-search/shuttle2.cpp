#include <bits/stdc++.h>
using namespace std;

vector<int> read() {
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
	return a;
}

int main() {
	vector<int> buses = read(); // every x is replaced with 0
	long long t = 0;
	long long product = 1;
	for(int i = 0; i < (int) buses.size(); ++i) {
		if(buses[i] != 0) {
			while((t + i) % buses[i] != 0) {
				t += product;
			}
			product *= buses[i];
		}
	}
	printf("%lld\n", t);
}

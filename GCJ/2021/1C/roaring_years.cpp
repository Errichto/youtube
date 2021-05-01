// Roaring Years
// https://codingcompetitions.withgoogle.com/codejam/round/00000000004362d7/00000000007c0f01
#include <bits/stdc++.h>
using namespace std;

void test_case() {
	long long y;
	scanf("%lld", &y);
	string helper = to_string(y);
	int len = helper.length();
	
	__int128 answer = -1;
	
	auto test = [&](__int128 x) {
		if(x > 5'000'000'000'000'000'000LL) {
			return;
		}
		if(x < 1) {
			return;
		}
		__int128 value = x;
		do {
			x++;
			
			__int128 tmp = x;
			while(tmp > 0) {
				value *= 10;
				tmp /= 10;
			}
			value += x;
		} while(value <= y);
		if(answer == -1 || value < answer) {
			answer = value;
		}
	};
	
	__int128 ten = 1;
	for(int pref = 1; pref <= len; pref++) {
		long long x = atoll(helper.substr(0, pref).c_str());
		test(x);
		test(x + 1);
		test(ten);
		ten *= 10;
		for(int i = 1; i <= 30; i++) {
			test(ten - i);
		}
	}
	assert(answer > 0);
	string s;
	while(answer > 0) {
		s += '0' + answer % 10;
		answer /= 10;
	}
	reverse(s.begin(), s.end());
	printf("%s\n", s.c_str());
}

int main() {
	int T;
	scanf("%d", &T);
	for(int nr = 1; nr <= T; ++nr) {
		printf("Case #%d: ", nr);
		test_case();
	}
}

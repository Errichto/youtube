#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
struct M {
	int a[2][2] = {{0, 0}, {0, 0}};
	M operator *(const M& other) const {
		M product;
		for(int i : {0, 1}) {
			for(int j : {0, 1}) {
				for(int k : {0, 1}) {
					product.a[i][k] = (product.a[i][k]
							+ (long long) a[i][j] * other.a[j][k]) % mod;
				}
			}
		}
		return product;
	}
};
M expo_power(M a, long long n) {
	M res;
	res.a[0][0] = res.a[1][1] = 1;
	while(n) {
		if(n % 2) {
			res = res * a;
		}
		n /= 2;
		a = a * a;
	}
	return res;
}
int main() {
	long long n;
	cin >> n;
	M single;
	single.a[0][0] = 0;
	single.a[0][1] = 1;
	single.a[1][0] = 1;
	single.a[1][1] = 1;
	cout << expo_power(single, n).a[1][0] << endl;
}

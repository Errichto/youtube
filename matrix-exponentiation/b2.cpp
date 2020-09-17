#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
#define REP(i, n) for(int i = 0; i < (n); i++)
struct Matrix {
	long long a[2][2];
	Matrix() {
		REP(i, 2) {
			REP(j, 2) {
				a[i][j] = 0;
			}
		}
	}
	Matrix operator *(Matrix other) {
		Matrix product = Matrix();
		REP(i, 2) {
			REP(j, 2) {
				REP(k, 2) {
					product.a[i][k] += a[i][j] * other.a[j][k];
					product.a[i][k] %= mod;
				}
			}
		}
		return product;
	}
};
Matrix expo_power(Matrix a, long long n) {
	Matrix res = Matrix();
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
	Matrix single = Matrix();
	single.a[0][0] = 19;
	single.a[0][1] = 7;
	single.a[1][0] = 6;
	single.a[1][1] = 20;
	Matrix total = expo_power(single, n);
	cout << total.a[0][0] << endl;
}

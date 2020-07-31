#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i = 0; i < (n); i++)
const int mod = 1e9 + 7;
struct Matrix {
	int a[2][2] = {{0,0},{0,0}};
	Matrix operator *(const Matrix& other) {
		Matrix product;
		REP(i,2)REP(j,2)REP(k,2) {
			product.a[i][k] = (product.a[i][k] + (long long) a[i][j] * other.a[j][k]) % mod;
		}
		return product;
	}
};
Matrix expo_power(Matrix a, long long k) {
	Matrix product;
	REP(i,2) product.a[i][i] = 1;
	while(k > 0) {
		if(k % 2) {
			product = product * a;
		}
		a = a * a;
		k /= 2;
	}
	return product;
}
int main() {
	// C. Fibonacci
	long long n;
	cin >> n;
	Matrix single;
	single.a[0][0] = 0;
	single.a[0][1] = 1;
	single.a[1][0] = 1;
	single.a[1][1] = 1;
	Matrix total = expo_power(single, n);
	cout << total.a[1][0] << endl;
}

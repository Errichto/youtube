#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i = 0; i < (n); i++)
struct Matrix {
	double a[2][2] = {{0,0},{0,0}};
	Matrix operator *(const Matrix& other) {
		Matrix product;
		REP(i,2)REP(j,2)REP(k,2) {
			product.a[i][k] += a[i][j] * other.a[j][k];
		}
		return product;
	}
};
Matrix expo_power(Matrix a, int k) {
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
	// A. Random Mood
	int n;
	double p;
	cin >> n >> p;
	Matrix single;
	single.a[0][0] = 1 - p;
	single.a[0][1] = p;
	single.a[1][0] = p;
	single.a[1][1] = 1 - p;
	Matrix total = expo_power(single, n);
	cout << setprecision(10) << fixed << total.a[0][0] << endl;
}

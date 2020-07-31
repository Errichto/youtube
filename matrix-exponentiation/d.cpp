#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i = 0; i < (n); i++)
const int mod = 1e9 + 7;
int n;
struct Matrix {
	vector<vector<int>> a = vector<vector<int>>(n, vector<int>(n));
	Matrix operator *(const Matrix& other) {
		Matrix product;
		vector<vector<long long>> tmp(n, vector<long long>(n));
		REP(i,n)REP(j,n)REP(k,n) {
			tmp[i][k] += (long long) a[i][j] * other.a[j][k];
			if(tmp[i][k] >= 8LL * mod * mod) {
				tmp[i][k] %= mod;
			}
			// product.a[i][k] = (product.a[i][k] + (long long) a[i][j] * other.a[j][k]) % mod;
		}
		REP(i,n)REP(j,n) product.a[i][j] = tmp[i][j] % mod;
		return product;
	}
};
Matrix expo_power(Matrix a, long long k) {
	Matrix product;
	REP(i,n) product.a[i][i] = 1;
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
	// D. Count Paths
	int m;
	long long k;
	cin >> n >> m >> k;
	Matrix single;
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		single.a[u-1][v-1] = 1;
	}
	Matrix total = expo_power(single, k);
	int answer = 0;
	REP(i, n) REP(j, n) {
		answer = (answer + total.a[i][j]) % mod;
	}
	cout << answer << endl;
}

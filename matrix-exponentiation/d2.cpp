#include <bits/stdc++.h>
using namespace std;
int n;
const int mod = 1e9 + 7;
struct Matrix {
	vector<vector<int>> a = vector<vector<int>>(n, vector<int>(n));
	void operator *=(const Matrix& other) {
		vector<vector<int>> product(n, vector<int>(n));
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				for(int k = 0; k < n; ++k) {
					product[i][k] = (product[i][k] + (long long) a[i][j] * other.a[j][k]) % mod;
				}
			}
		}
		a = product;
	}
};
Matrix expo_power(Matrix a, int k) {
	Matrix res;
	for(int i = 0; i < n; ++i) {
		res.a[i][i] = 1;
	}
	while(k) {
		if(k % 2) {
			res *= a;
		}
		k /= 2;
		a *= a;
	}
	return res;
}
int main() {
	int m, k;
	scanf("%d%d%d", &n, &m, &k);
	Matrix base;
	for(int i = 0; i < m; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		base.a[a-1][b-1]++;
	}
	Matrix total = expo_power(base, k);
	int answer = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			answer = (answer + total.a[i][j]) % mod;
		}
	}
	printf("%d\n", answer);
}
	
